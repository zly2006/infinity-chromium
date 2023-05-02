#include <utility>

#include "common.h"

ChromiumInfo::ChromiumInfo(
        std::filesystem::path path, std::string  name, ChromiumInfo::Type type,
        ChromiumInfo::Confidence confidence, std::string detail, long totalSize):
        path(std::move(path)), name(std::move(name)), type(type), confidence(confidence), detail(std::move(detail)), totalSize(totalSize){

}

long calculateSize(const std::filesystem::path& path) {
    long size = 0;
    for (auto& p : std::filesystem::recursive_directory_iterator(path)) {
        if (p.is_regular_file()) {
            size += p.file_size();
        }
    }
    return size;
}

// output operator for ChromiumInfo::Type
std::ostream& operator<<(std::ostream& os, ChromiumInfo::Type type) {
    switch (type) {
        case ChromiumInfo::Type::Electron:
            os << "Electron";
            break;
        case ChromiumInfo::Type::Edge:
            os << "Edge";
            break;
        case ChromiumInfo::Type::Chrome:
            os << "Chrome";
            break;
        case ChromiumInfo::Type::CEF:
            os << "CEF";
            break;
    }
    return os;
}
