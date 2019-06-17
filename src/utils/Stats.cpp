#include "utils/Stats.hpp"
#include <algorithm>
#include <iomanip>

std::unordered_map<std::string, struct sStat> Stats::stats = {};

Stats::Stats() {
}

Stats::~Stats() {
}

void    Stats::printStats() {
    for (auto const &stat : stats) {
        std::cout << stat.first << ":" << std::endl;

        std::cout << "\tfunction called " << stat.second.nbCalls << " times" << std::endl;
        std::cout << "\ttotal exec time " << std::fixed << std::setprecision(8) << stat.second.totalExecTime.count() << "s" << std::endl;
        std::cout << "\taverage " << std::fixed << std::setprecision(8) << stat.second.avgExecTime.count() << "s" << std::endl;
        if (stat.second.minExecTime != std::chrono::duration<double>::max())
            std::cout << "\tmin " << std::fixed << std::setprecision(8) << stat.second.minExecTime.count() << "s" << std::endl;
        if (stat.second.maxExecTime != std::chrono::duration<double>::min())
            std::cout << "\tmax " << std::fixed << std::setprecision(8) << stat.second.maxExecTime.count() << "s" << std::endl;
    }
}

void	Stats::startStats(std::string funcName) {
    if (Stats::stats.find(funcName) == Stats::stats.end()) {
        struct sStat stats;
        stats.nbCalls = 0;
        stats.totalExecTime = std::chrono::duration<double>(0);
        stats.avgExecTime = std::chrono::duration<double>(0);
        stats.minExecTime = std::chrono::duration<double>::max();
        stats.maxExecTime = std::chrono::duration<double>::min();
        Stats::stats[funcName] = stats;
    }
    ++(Stats::stats[funcName].nbCalls);
    Stats::stats[funcName].startExecTime = std::chrono::high_resolution_clock::now();
}

void	Stats::endStats(std::string funcName) {
    if (Stats::stats.find(funcName) == Stats::stats.end()
    || Stats::stats[funcName].startExecTime == std::chrono::high_resolution_clock::time_point::min())
        return;
    std::chrono::duration<double> execTime = std::chrono::duration_cast<std::chrono::duration<double> >(
        std::chrono::high_resolution_clock::now() - Stats::stats[funcName].startExecTime);
    Stats::stats[funcName].totalExecTime += execTime;
    Stats::stats[funcName].avgExecTime = Stats::stats[funcName].totalExecTime / Stats::stats[funcName].nbCalls;
    Stats::stats[funcName].minExecTime = std::min(Stats::stats[funcName].minExecTime, execTime);
    Stats::stats[funcName].maxExecTime = std::max(Stats::stats[funcName].maxExecTime, execTime);
    // reset startExecTime
    Stats::stats[funcName].startExecTime = std::chrono::high_resolution_clock::time_point::min();
}
