# Plan: LAN Web Settings Server for SoH ("couch settings")

## Context

SoH has a huge number of settings, all stored as **CVars** in libultraship. While playing on a
couch, tweaking them means pulling up the in-game ImGui menu and navigating its many sections with a
controller. The goal is to let someone open a web page on a phone/tablet on the same LAN and change
settings live, turning the second device into a remote settings panel.

The key enabler is that the in-game menu already builds a complete, iterable metadata registry for
every setting (`WidgetInfo`: label, CVar name, widget type, min/max/step, combobox option maps,
tooltips, defaults). Serializing that registry to JSON lets a client auto-generate the form — no
hand-maintained second copy of the settings list.

**v1 delivers the JSON API only** (schema + read + write); the actual phone/tablet web page that
consumes it is a deliberate follow-up, so this plan is about the engine-side plumbing. It is
intentionally scoped: **off by default, LAN-bound, no auth**, and limited to the "easy" CVar-backed
widget types — establishing the seam so more widget types and a real UI can be added later.

## Approach

A new SoH module hosts an embedded HTTP server (cpp-httplib) on a background thread. The server
exposes a **JSON API only** — no bundled web UI. The endpoints are documented in a README so users
can drive them with `curl`, a browser, or a front-end of their own; a polished page is left to a
follow-up. The settings **schema is generated in memory at runtime** by walking the live menu
registry once (the same registry we already need for the apply path) and cached for the process
lifetime — no build-time codegen, no shipped artifact. Setting *reads* and the cached schema are
served from the server thread; setting *writes* are queued and applied on the **main game thread**
(via the `OnGameFrameUpdate` hook), running each widget's `callback` lambda.

We do **not** reuse the `Network` base class — that's an outbound TCP client. We mirror its
*lifecycle conventions* (singleton in `OTRGlobals`, `Enable`/`Disable`, CVar toggle in the Network
menu, frame-hook draining) but the server itself is cpp-httplib.

### 1. Dependency: cpp-httplib (header-only)

Available via vcpkg (`cpp-httplib`), Homebrew (`cpp-httplib`), and major Linux distros. Pulled from
the platform package manager only — **no FetchContent fallback**. The dependency is **optional**:
if it isn't found, the feature is simply not built (same graceful-degrade pattern SoH already uses
for `SDL2_net` in `soh/CMakeLists.txt`). A missing package never fails the build; it just omits the
settings server.

- `soh/CMakeLists.txt`: `find_package(httplib QUIET)`. If found, link `httplib::httplib` to the
  `soh` target and define a guard (`target_compile_definitions(... ENABLE_SETTINGS_SERVER)`). If not
  found, print a STATUS message and build without it. Keep SSL off (default; do **not** define
  `CPPHTTPLIB_OPENSSL_SUPPORT`).
- The module `.cpp`s under `soh/soh/Network/SettingsServer/` are already picked up by the existing
  `GLOB_RECURSE` over `soh/soh/` (`soh/CMakeLists.txt:135`), so they always compile. Their bodies —
  **and the `#include <httplib.h>`** — live under `#ifdef ENABLE_SETTINGS_SERVER`, so the file is an
  empty TU when the dep is absent. The `OTRGlobals` wiring and the menu toggle are guarded the same
  way.
- `libultraship/cmake/dependencies/windows-vcpkg.cmake`: add `cpp-httplib` to
  `vcpkg_install_packages(...)`.
- `linux-build-deps/{apt,dnf,zypper,pacman}.txt` and `flake.nix`: add the distro package name.
  Fedora confirmed: `cpp-httplib-devel` (0.38.0, ships a CMake config). vcpkg/brew/Arch use
  `cpp-httplib`; verify the apt name at implement time.
- README build-deps section (incl. the macOS `brew install` list): mention the new dep.

### 2. New module: `soh/soh/Network/SettingsServer/`

Mirror the CrowdControl/Anchor structure (`OTRGlobals.cpp:~1563` owns the singleton with `new`).

- `SettingsServer.h/.cpp`:
  - `static SettingsServer* Instance;`
  - `Enable()` / `Disable()`: start/stop the cpp-httplib server on a `std::thread`
    (`svr.listen(host, port)`). `Disable()` calls `svr.stop()` then joins. The schema/index are built
    later on the main thread via the drain hook (Section 3), not here.
  - `bool isEnabled;`
  - A mutex-protected `std::queue` of pending **main-thread requests** — writes `{cVar, type, value,
    promise}` and value-snapshot reads `{promise}` — so handlers block for and report results.
  - `ProcessIncomingQueue()` drained from the frame hook; it services each request (write or read
    snapshot) and fulfills its promise.
- New CVar prefix macro in `soh/soh/cvar_prefixes.h` next to the others:
  `#define CVAR_REMOTE_SETTINGS_SERVER(var) CVAR_REMOTE("SettingsServer." var)`
  for `Enabled`, `Host` (default `0.0.0.0`), `Port` (default e.g. `43385`).

### 3. Schema generation — runtime, in memory

The schema (the list of settings + their types/ranges/option labels) is **built in memory at
runtime** by walking the live menu registry once, then cached for the process lifetime. No build
tool, no shipped JSON, no resource load — the running game already holds the registry, so the schema
is just a second projection of data we're walking anyway (we build the apply index in the same pass).

**Build once on the main thread, then immutable.** Build the schema (and the apply index, Section 5)
on the **main thread** the first time the drain hook runs with `mSohMenu` present — *not*
unconditionally in `Enable()`, because `Enable()` can run at startup (Section 6) before the menu is
constructed, when `GetMenuEntries()` would be empty. Store the `.dump()`'d string (and keep the
parsed `nlohmann::json` for `/api/set` validation) and set a `ready` flag. After that it never
changes, so the server thread reads the cached string lock-free; handlers return `503` until
`ready`.

**Traversal/serializer.** Walk the menu registry
(`menuEntries` → `MainMenuEntry.sidebars` → `SidebarEntry.columnWidgets` → `WidgetInfo`;
`Menu.h:37`, structs in `MenuTypes.h`); the search loop in `Menu.cpp` (~200–274) already demonstrates
it. For each `WidgetInfo`, emit `label` (`name`), `cvar`, `type`, `tooltip`, plus type-specific
fields by `static_pointer_cast`-ing `options` per `WidgetType`:

- **WIDGET_CVAR_CHECKBOX** → bool, `defaultValue` (`CheckboxOptions`)
- **WIDGET_CVAR_COMBOBOX** → enum; iterate `ComboboxOptions::comboMap`
  (`std::map<int32_t,const char*>`) into value/label pairs; `defaultIndex`
- **WIDGET_CVAR_SLIDER_INT** → `min`/`max`/`step`/`defaultValue` (`IntSliderOptions`)
- **WIDGET_CVAR_SLIDER_FLOAT** → `min`/`max`/`step`/`defaultValue`/`isPercentage`
  (`FloatSliderOptions`)

**v1 scope:** only those four widget types. Skip buttons, window buttons, custom, text/separator,
btn-selector, color picker, and the audio/video-backend widgets. (Color picker — `.Value`/`.Rainbow`/
`.Locked` sub-CVars — and the runtime-populated combos (languages/ROM versions/backends), which
*are* knowable now that this runs at runtime, are natural follow-ups.)

**The schema contains only cvar-bound menu widgets.** Widgets with no `cvar` (buttons, text,
separators, window buttons) are never emitted, and the v1 type filter above further narrows it. This
is not an extra rule to enforce — it falls out of walking the menu registry. The consequence that
matters: `schema entries ⊆ cvar-bound menu widgets`, which is *exactly* the set the runtime gate
(Section 5) will accept. Schema and gate come from the same `AddWidget` registration *and the same
runtime walk*, so they cannot disagree about which cvars are writable.

`menuEntries` is `protected` on `Ship::Menu`; add a public accessor (e.g.
`const std::unordered_map<std::string, MainMenuEntry>& GetMenuEntries() const`), reached as
`SohGui::GetSohMenu()->GetMenuEntries()` (`SohMenu : public Ship::Menu`). Used by both the schema
build and the apply index.

### 4. HTTP endpoints (JSON API)

- `GET /api/schema` → the cached in-memory schema string (Section 3). Read lock-free on the server
  thread; returns `503` until the main thread has built it, then immutable.
- `GET /api/values` → the current value of **every cvar in the schema**, as one `{cvar: value}`
  object (each value in its natural JSON type per the schema). This is what a client needs to
  populate/refresh the whole panel. **Read on the main thread, not the server thread:** the CVar
  store is an `unordered_map` that game code can rehash mid-frame (it creates cvars at runtime), so a
  bulk read off-thread races that rehash. So `/api/values` marshals like `/api/set` — enqueue a
  snapshot request with a `promise`, the drain hook fills it on the main thread, return it (~1 frame).
  Because the read runs on the main thread with the live `WidgetInfo`, a later revision can cheaply
  fold per-cvar disabled/hidden state into this response (the `/api/state` idea).
- `POST /api/set` (body `{cvar, value}`) → **synchronous**. First-line validation on the server
  thread against the cached schema (cvar exists, value in range/type) → `400` on failure. Otherwise
  enqueue `{cvar, value, promise}` and **block on the future** until the main-thread applier reports
  the outcome (Section 5): `200` applied, `409`/`423` currently disabled/hidden/race-locked, `404`
  no live widget. This is how the client learns the apply-time gate's verdict; latency is ~1 frame,
  negligible for a settings panel. (cpp-httplib is thread-per-connection blocking, so parking the
  handler thread on the future is fine.)

**Cross-origin + error shape (so a browser front-end works).** The eventual web page will almost
certainly be a *different origin* than the game — at minimum a different port, likely a separately
hosted static page — so the server must send permissive CORS headers (`Access-Control-Allow-Origin`
plus `-Allow-Methods`/`-Allow-Headers`) and answer the `OPTIONS` preflight that a JSON
`POST /api/set` triggers. Error responses carry a structured JSON body
`{ "error": <code>, "reason": <text> }` with a machine-readable code (`unknown_cvar`, `out_of_range`,
`disabled`, `race_locked`, `hidden`, `server_stopping`) alongside the HTTP status, so a client can
branch on the cause. These are cheap in cpp-httplib and are real v1 server behavior even though the
page is a follow-up.

**Designed to fit a TanStack Query (React Query) front-end:** `/api/schema` → a query with infinite
`staleTime`; `/api/values` → a query with `refetchInterval` (bulk `{cvar: value}` = one cache entry,
sliced via `select`); `/api/set` → a mutation whose **synchronous** verdict drives optimistic-update
rollback on `409`/`423`. After a successful mutation the client invalidates `['values']` and
refetches — the bulk endpoint catches callback **cascades** (one widget's callback changing other
cvars) in a single request. The startup `503` self-heals via React Query's query retries.

No `GET /` HTML page is served in v1. Document these endpoints (request/response shapes, error codes,
example `curl`) in a README so the API is usable without a bundled front-end. A real web UI is a
deliberate follow-up.

### 5. Applying writes on the main thread (server-owned apply helper)

Register `COND_HOOK(OnGameFrameUpdate, isEnabled, [&]{ ProcessIncomingQueue(); })` (pattern from
`Network/Anchor/HookHandlers.cpp:105`). For each queued write, a **server-owned** apply helper
(e.g. `ApplyWidgetValue(WidgetInfo&, value)`) performs the same effective sequence the menu performs
on change:

1. `CVarSetInteger`/`CVarSetFloat(cvar, value)`
2. `...GetGui()->SaveConsoleVariablesNextFrame()` (thread-safe persist)
3. `ShipInit::Init(cvar)`
4. Invoke the widget's `callback(widgetInfo)` if present — **required**, since many settings have
   side-effects beyond the CVar (SDL hints, resolution, audio).

**This helper is deliberately not shared with the menu's `UIWidgets::CVar*` helpers.** Those are
immediate-mode UI functions tangled with per-frame redraw, `dirty` return values, and focus/
interaction state that are meaningless to a headless server. We mirror only the four effective
steps in a clean helper. The sequence is small and stable; the (accepted) cost is that if the menu's
apply behavior ever changes, this helper must be updated to match. (`ShipInit::Init` itself is the
shared piece that already centralizes most cvar-driven re-initialization.)

Step 4 needs the live registry: the callbacks are real lambdas that only exist in the running game.
Build a `cvar → WidgetInfo*` index in the **same main-thread pass that builds the schema** (Section
3), so the applier can find and run the right callback. The runtime coupling to `SohGui::mSohMenu` is
exactly this one lookup — steps 1–3 use only global CVar/bridge APIs.

**A live `WidgetInfo` is mandatory — no graceful fallback.** If a queued write's cvar has no entry
in the index, the write is **rejected and dropped, never applied**. We refuse to blind-`CVarSet` a
cvar with no defined safe-change semantics — doing so could leave the game in a state nothing knows
how to reconcile. So a missing widget is an error, not a degrade-to-steps-1–3. (`/api/set` rejects up
front against the cached schema; the applier re-checks the index at apply time since the request
crosses a thread/frame boundary.) Schema and index are built from the same walk, so the cached schema
is the client contract + first-line validation and the index is the authoritative apply-time gate.
The applier **fulfills each write's promise** with the outcome (applied / disabled / unknown), which
the blocked HTTP handler maps to the status code.

**The apply gate also honors live disabled/hidden/race state.** Running on the main thread with the
live `WidgetInfo`, the applier reuses the menu's own evaluation — the prologue of
`Menu::MenuDrawItem` (`Menu.cpp:289–312`): `ResetDisables()`, run `widget.preFunc(widget)`, then
reject the write if `widget.isHidden`, if `widget.activeDisables` is non-empty (context-disabled),
or if `widget.raceDisable && raceDisableActive` (race/run settings-lock,
`raceDisableActive = CVarGetInteger(CVAR_SETTING("DisableChanges"), 0)`). So the server can never
change a setting the menu would currently forbid. **Subtlety:** `preFunc` reads the per-frame
`disabledMap` (`Menu::GetDisabledMap()`), whose `.active` flags are refreshed in the menu's update
loop — to not depend on the menu being open, the applier should refresh those evaluations itself
before running `preFunc`. Both this and the draw loop run on the main thread, so mutating the shared
`WidgetInfo` here is safe (the next draw re-runs `ResetDisables`). A contextually-rejected write
returns a distinct status (e.g. `409`/`423`), separate from a `400` bad-cvar.

Unlike CrowdControl effects, settings don't need `IsPlayerInControl()` — they're valid any time.

### 6. Lifecycle wiring

- `OTRGlobals.cpp`: construct `SettingsServer::Instance = new SettingsServer();` next to the other
  remotes (~line 1563); call `Enable()` on startup if `CVAR_REMOTE_SETTINGS_SERVER("Enabled")`;
  `Disable()` on shutdown.
- `soh/soh/SohGui/SohMenuNetwork.cpp`: add a section with Host/Port inputs and an Enable/Disable
  toggle button, copying the CrowdControl widget block (`SohMenuNetwork.cpp:131–152`) — PreFunc
  flips the label and validates host/port; Callback sets the CVar + `SaveConsoleVariablesNextFrame`
  + calls `Enable()`/`Disable()`. Show the reachable URL (`http://<lan-ip>:<port>`) and a
  "anyone on your network can change settings" warning.

## Files to create / modify

- **New:** `soh/soh/Network/SettingsServer/SettingsServer.{h,cpp}` (server, queue, schema build +
  serve, apply path)
- **New:** registry→JSON serializer (e.g. `soh/soh/SohGui/SettingsSchema.{h,cpp}`) that builds the
  schema `nlohmann::json` + the `cvar → WidgetInfo*` index from `GetMenuEntries()`
- **New:** `soh/soh/Network/SettingsServer/README.md` — documents the three endpoints with
  request/response shapes and `curl` examples
- `soh/CMakeLists.txt` — optional cpp-httplib find + link + `ENABLE_SETTINGS_SERVER` define (module
  `.cpp`s are auto-globbed; no explicit source list needed)
- `libultraship/cmake/dependencies/windows-vcpkg.cmake` — add `cpp-httplib`
- `linux-build-deps/{apt,dnf,zypper,pacman}.txt`, `flake.nix`, `README.md` — dep names
- `soh/soh/cvar_prefixes.h` — `CVAR_REMOTE_SETTINGS_SERVER` macro
- `soh/soh/SohGui/Menu.h` — add public `GetMenuEntries()` accessor
- `soh/soh/OTRGlobals.cpp` — construct/enable/disable the singleton (under `ENABLE_SETTINGS_SERVER`)
- `soh/soh/SohGui/SohMenuNetwork.cpp` — enable toggle + host/port UI (under `ENABLE_SETTINGS_SERVER`)

## Key existing code to reuse

- CVar API: `libultraship/.../bridge/consolevariablebridge.h`
- Menu-change apply semantics: `UIWidgets::CVar{Checkbox,Combobox,SliderInt,SliderFloat}` in
  `soh/soh/SohGui/UIWidgets.hpp` (CVarSet + SaveConsoleVariablesNextFrame + ShipInit::Init)
- Registry traversal: search loop in `soh/soh/SohGui/Menu.cpp` (~200–274)
- Disabled/hidden/race evaluation: `Menu::MenuDrawItem` prologue (`Menu.cpp:289–312`) +
  `Menu::GetDisabledMap()` (already public, `Menu.h:31`); race lock is `CVAR_SETTING("DisableChanges")`
- Remote lifecycle + menu toggle template: `OTRGlobals.cpp` (~1563), `SohMenuNetwork.cpp`
  (131–152), frame-hook draining in `Network/Anchor/HookHandlers.cpp:105`
- `ShipInit::Init` in `soh/soh/ShipInit.hpp`
- JSON serialization: `nlohmann::json` (already a dependency, used throughout the Network remotes)

## Risks / notes

- **Threading:** the schema + apply index are built once on the main thread (first drain-hook tick),
  then immutable → the server thread reads the cached schema string lock-free. **All CVar access —
  `/api/set` writes *and* `/api/values` reads — is marshaled to the main thread** via the request
  queue + promise/future, so there's no off-thread access to the CVar `unordered_map` (which game
  code can rehash mid-frame). The server thread only ever touches the immutable schema string and the
  request queue.
- **Init order (menu vs `Enable`):** `Enable()` can run at startup (Section 6) before `mSohMenu`
  exists, so the schema/index are built lazily on the main thread (first drain-hook tick with the
  menu present), not in `Enable()`. HTTP handlers return `503` until a `ready` flag is set. Verify
  `OnGameFrameUpdate` fires early enough (including at the title screen, before a save is loaded)
  that the schema is available when you'd want to use it; if it only fires in-gameplay, pick an
  earlier main-thread hook for the one-time build.
- **Static schema vs live gate:** the *schema* is a one-time snapshot, so a client may show a control
  that's currently disabled/hidden. That's fine: the *apply gate* evaluates live
  disabled/hidden/race state on the main thread and rejects such writes (Section 5), so the server
  can't change anything the menu would currently forbid (incl. the race/run settings-lock). A future
  `/api/state` could surface per-widget enabled/hidden flags so a UI can grey controls out
  proactively; v1 just rejects with a distinct status.
- **Security:** open LAN port, no auth, by default off. Note `Host=0.0.0.0` binds *all* interfaces,
  not strictly the LAN; acceptable for home use, and the menu must warn. Also note the flip side of
  permissive CORS: any web page the user visits could reach the API if it knows the LAN IP+port
  (only game settings are at stake, but it's another reason for off-by-default and a future token /
  origin allowlist). Token/PIN auth and binding to a specific interface are future enhancements.
- **cpp-httplib clean shutdown:** ensure `svr.stop()` + thread join in `Disable()` and at app exit to
  avoid a hung socket thread. Because `/api/set` blocks on a promise, `Disable()` must also **fulfill
  any in-flight/queued promises** (with a "server stopping" result) so no handler thread hangs
  waiting on a future the drain hook will never reach.

## Verification

Builds run **inside the `soh` distrobox** (Bazzite host; container is a Fedora toolbox, image
`ghcr.io/ublue-os/fedora-toolbox`). Prefix build/configure/run commands with
`distrobox enter soh -- …` (or enter it interactively). Install the dep there first:
`sudo dnf install cpp-httplib-devel` (confirmed available, 0.38.0).

1. **Build** in the `soh` distrobox with the dep installed; confirm cpp-httplib resolves,
   `ENABLE_SETTINGS_SERVER` is defined, and `soh` links. Then reconfigure with the package absent
   (or forced not-found) and confirm the build still succeeds with the feature compiled out and a
   STATUS message explaining why.
2. **Run** SoH, open Network menu, set port, click Enable. Confirm log shows the server listening and
   no crash.
3. From another device (or same machine) `curl http://<host-ip>:<port>/api/schema` (served from the
   in-memory schema) and `/api/values` — both return well-formed JSON; spot-check a checkbox, a
   combobox, and both sliders are present in the schema.
4. `curl -X POST .../api/set` for a setting with an observable effect (e.g. a HUD/cosmetic checkbox,
   or "Menu Background Opacity" float slider); confirm the change applies live in-game **and** that
   its widget callback ran (pick a setting whose callback does visible work). Confirm an unknown or
   out-of-range cvar is rejected.
5. Confirm the change reflects in the in-game ImGui menu and persists across restart (CVarSave).
6. Click Disable; confirm the port closes and the server thread exits cleanly; confirm app exits
   without hanging.
