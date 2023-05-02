#include <iostream>
#include "osx.h"
using path = std::filesystem::path;

void searchAppRoots(std::vector<path>& appRoots, path searchingPath, int depth) {
    if (depth > 5) return;
    for (auto& p : std::filesystem::directory_iterator(searchingPath)) {
        if (p.is_directory()) {
            auto pathString = p.path().string();
            if (pathString.ends_with(".app")) {
                appRoots.push_back(p.path());
            } else {
                searchAppRoots(appRoots, p.path(), depth + 1);
            }
        }
    }
}

std::vector<ChromiumInfo> isElectronApp(path appRoot) {
    auto frameworks = appRoot / "Contents" / "Frameworks";
    std::vector<ChromiumInfo> ret;
    if (exists(frameworks)) {
        for (auto& p: std::filesystem::directory_iterator(frameworks)) {
            if (p.is_directory()) {
                auto pathString = p.path().string();
                // to lowercase
                std::transform(pathString.begin(), pathString.end(), pathString.begin(), ::tolower);
                if (pathString.find("electron") != std::string::npos) {
                    std::cout << "Calculating size of " << appRoot << std::endl;
                    ret.emplace_back(appRoot, appRoot.filename().string(), ChromiumInfo::Type::Electron,
                                        ChromiumInfo::Confidence::Definitely, "Found electron framework.",
                                        calculateSize(p));
                }
                if (pathString.find("microsoft edge") != std::string::npos) {
                    std::cout << "Calculating size of " << appRoot << std::endl;
                    ret.emplace_back(appRoot, appRoot.filename().string(), ChromiumInfo::Type::Edge,
                                        ChromiumInfo::Confidence::Definitely, "Found edge framework.",
                                        calculateSize(p));
                }
                if (pathString.find("google chrome") != std::string::npos) {
                    std::cout << "Calculating size of " << appRoot << std::endl;
                    ret.emplace_back(appRoot, appRoot.filename().string(), ChromiumInfo::Type::Chrome,
                                        ChromiumInfo::Confidence::Definitely, "Found chrome framework.",
                                        calculateSize(p));
                }
                if (pathString.find("chromium embedded framework") != std::string::npos) {
                    std::cout << "Calculating size of " << appRoot << std::endl;
                    ret.emplace_back(appRoot, appRoot.filename().string(), ChromiumInfo::Type::CEF,
                                        ChromiumInfo::Confidence::Definitely, "Found CEF framework.",
                                        calculateSize(p));
                }
            }
        }
    }
    return ret;
}

std::vector<ChromiumInfo> searchChromiumMacOS() {
    path searchPath = "/Applications";
    std::vector<path> appRoots;
    searchAppRoots(appRoots, searchPath, 0);

    for (const auto& item: appRoots) {
        std::cout << "Found app: " << item << std::endl;
    }

    std::vector<ChromiumInfo> results;

    for (auto& appRoot : appRoots) {
        auto result = isElectronApp(appRoot);
        results.insert(results.end(), result.begin(), result.end());
    }

    return results;
}
