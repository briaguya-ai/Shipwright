#ifndef SOH_DIAG_H
#define SOH_DIAG_H

// Diagnostics branch only. Breadcrumbs for the window before OTRGlobals::Initialize() runs
// InitLogging and InitCrashHandler, where spdlog has no file sink, Windows release has no console
// sink either, and no crash handler is installed — so a crash there leaves nothing behind.
//
// This writes straight to <appdir>/soh-diag.log and closes the file after every line, so whatever
// was written survives a hard crash.

#include <string>
#include <utility>
#include <fmt/format.h>

namespace SohDiag {
void Write(const std::string& message);

template <typename... Args> void Log(fmt::format_string<Args...> format, Args&&... args) {
    Write(fmt::format(format, std::forward<Args>(args)...));
}
} // namespace SohDiag

#define SOH_DIAG(...) SohDiag::Log(__VA_ARGS__)

#endif
