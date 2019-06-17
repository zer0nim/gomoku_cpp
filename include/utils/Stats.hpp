#ifndef STATS_HPP
# define STATS_HPP

# include <unordered_map>
#include <iostream>
# include <string>
#include <chrono>
#include <ctime>
#include <ratio>

struct sStat {
	int	nbCalls;
	std::chrono::duration<double>	totalExecTime;
	std::chrono::duration<double>	avgExecTime;
	std::chrono::duration<double>	minExecTime;
	std::chrono::duration<double>	maxExecTime;
	std::chrono::high_resolution_clock::time_point	startExecTime;
};

class Stats {
	public:
		Stats();
		~Stats();
		static void	startStats(std::string funcName);
		static void	endStats(std::string funcName);
		static void	printStats();
		static std::unordered_map<std::string, struct sStat> stats;
};

#endif
