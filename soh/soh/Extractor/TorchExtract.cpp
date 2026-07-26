#include "TorchExtract.h"

#include <chrono>
#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "soh/Diag.h"

#include "Companion.h"
#include "factories/BaseFactory.h"

namespace fs = std::filesystem;

// Profiling branch: the phase callback fires once per yml file, so recording a timestamp there
// gives a per-file cost breakdown. Samples are kept in memory and written after the run so the
// measurement doesn't pay for file IO on every file.
namespace {
struct PhaseSample {
    std::chrono::steady_clock::time_point at;
    std::string file;
};

void WriteProfile(const std::vector<PhaseSample>& samples, std::chrono::steady_clock::time_point start,
                  std::chrono::steady_clock::time_point end) {
    static int run = 0;
    run++;

    const bool needsHeader = !fs::exists("extraction-profile.csv");
    std::ofstream csv("extraction-profile.csv", std::ios::app);
    if (!csv) {
        return;
    }
    if (needsHeader) {
        csv << "run,index,elapsed_ms,delta_ms,file\n";
    }

    auto ms = [](auto from, auto to) {
        return std::chrono::duration_cast<std::chrono::microseconds>(to - from).count() / 1000.0;
    };

    auto previous = start;
    for (size_t i = 0; i < samples.size(); i++) {
        csv << run << ',' << i << ',' << ms(start, samples[i].at) << ',' << ms(previous, samples[i].at) << ','
            << samples[i].file << '\n';
        previous = samples[i].at;
    }
    // Everything after the last file: the remaining exports plus zipping and saving the archive.
    csv << run << ',' << samples.size() << ',' << ms(start, end) << ',' << ms(previous, end) << ",<finish>\n";
}
} // namespace

namespace SohTorch {

size_t CountAssetFiles(const std::string& ymlDir) {
    std::error_code ec;
    if (!fs::is_directory(ymlDir, ec)) {
        return 0;
    }

    size_t count = 0;
    for (fs::recursive_directory_iterator it(ymlDir, ec), end; it != end; it.increment(ec)) {
        if (ec) {
            break;
        }
        if (it->is_regular_file(ec) && it->path().extension() == ".yml") {
            count++;
        }
    }
    return count;
}

std::string Extract(const std::string& romPath, const std::string& srcDir, const std::string& destDir,
                    const std::string& portVersion, std::atomic<size_t>* progress) {
    std::string archiveName;

    std::vector<PhaseSample> samples;
    samples.reserve(4096);

    try {
        SOH_DIAG("Torch: constructing Companion");
        // Companion::Instance is a raw global with no getter; factories dereference it.
        auto companion = std::make_unique<Companion>(fs::path(romPath), ArchiveType::O2R, false, srcDir, destDir);
        Companion::Instance = companion.get();
        companion->SetVersion(portVersion);
        companion->SetPhaseCallback([progress, &samples](int) {
            if (progress != nullptr) {
                (*progress)++;
            }
            // Runs on the extraction thread, where Companion::Instance is live.
            samples.push_back({ std::chrono::steady_clock::now(), Companion::Instance->GetCurrentDirectory() });
        });

        // Init is the whole run; it calls Process() internally.
        SOH_DIAG("Torch: Init(Binary) starting");
        const auto start = std::chrono::steady_clock::now();
        companion->Init(ExportType::Binary);
        SOH_DIAG("Torch: Init(Binary) returned");
        WriteProfile(samples, start, std::chrono::steady_clock::now());
        SOH_DIAG("Torch: profile written ({} samples)", samples.size());

        // config.yml names the archive per rom; ask rather than guess, and ask before the
        // companion goes away.
        archiveName = fs::path(companion->GetOutputPath()).filename().string();

        // Companion holds every parsed asset, so don't leak it into the game's lifetime.
        companion.reset();
        Companion::Instance = nullptr;
    } catch (const std::exception& e) {
        SOH_DIAG("Torch: threw std::exception: {}", e.what());
        SPDLOG_ERROR("Torch extraction failed: {}", e.what());
        Companion::Instance = nullptr;
        return "";
    } catch (...) {
        SOH_DIAG("Torch: threw an unknown exception");
        SPDLOG_ERROR("Torch extraction failed with an unknown exception");
        Companion::Instance = nullptr;
        return "";
    }

    // Process() returns void and several fatal paths only log and return, so confirm the
    // archive is really there rather than trusting the run.
    std::error_code ec;
    if (archiveName.empty() || !fs::exists(fs::path(destDir) / archiveName, ec)) {
        SOH_DIAG("Torch: no archive '{}' in {}", archiveName, destDir);
        SPDLOG_ERROR("Torch produced no archive in {}", destDir);
        return "";
    }

    return archiveName;
}

} // namespace SohTorch
