#include <iostream>

#include "osx.h"

int main() {
    std::vector<ChromiumInfo> results;

    std::cout << "Congratulations! We have found " << results.size() << " apps that based on Chromium!" << std::endl;
    long totalSize = 0;
    for (auto& result: results) {
        std::cout << result.name << "(" << result.type << "): " << result.detail
            << ", which used " << result.totalSize / 1024 / 1024 << "MB of your disk!" << std::endl;
        totalSize += result.totalSize;
    }
    std::cout << "Total size: " << totalSize / 1024 / 1024 << "MB" << std::endl;
    return 0;
}
