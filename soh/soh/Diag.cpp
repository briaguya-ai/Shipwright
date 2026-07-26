#include "Diag.h"

#include <chrono>
#include <ctime>
#include <fstream>
#include <mutex>

#include <ship/Context.h>

namespace SohDiag {

static std::mutex sMutex;
static bool sTruncated = false;

void Write(const std::string& message) {
    std::lock_guard<std::mutex> lock(sMutex);

    // "soh" rather than OTRGlobals.h's appShortName, to keep this includable from anywhere.
    static const std::string path = Ship::Context::GetPathRelativeToAppDirectory("soh-diag.log", "soh");

    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif
    char stamp[16];
    std::strftime(stamp, sizeof(stamp), "%H:%M:%S", &tm);

    // Reopened and closed per line so nothing is buffered when the process dies.
    std::ofstream out(path, sTruncated ? std::ios::app : std::ios::trunc);
    sTruncated = true;
    if (!out) {
        return;
    }
    out << "[" << stamp << "." << fmt::format("{:03}", ms.count()) << "] " << message << "\n";
}

} // namespace SohDiag
