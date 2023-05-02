#ifndef INFINITY_CHROMIUM_COMMON_H
#define INFINITY_CHROMIUM_COMMON_H

#include <string>
#include <filesystem>

class ChromiumInfo {
public:
    enum Type {
        Electron,
        Edge,
        Chrome,
        CEF,
    };
    enum Confidence {
        Definitely,
        Probably,
        None
    };
    ChromiumInfo(std::filesystem::path path,
                 std::string name,
                 Type type,
                 Confidence confidence,
                 std::string detail,
                 long totalSize);

    std::filesystem::path path;
    std::string name;
    Type type;
    Confidence confidence;
    std::string detail;
    long totalSize;
};

std::ostream& operator<<(std::ostream& os, ChromiumInfo::Type type);

long calculateSize(const std::filesystem::path& path);

#endif //INFINITY_CHROMIUM_COMMON_H
