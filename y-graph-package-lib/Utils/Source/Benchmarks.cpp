#include "../Headers/Benchmarks.hpp"

namespace yasuzume::utils 
{
	template<typename R, typename... ARGS>
	double measure_execution_time(std::function<R(ARGS...)> func, ARGS... args) 
	{
		auto time_start = std::chrono::high_resolution_clock::now();
		func(args...);
		auto time_end = std::chrono::high_resolution_clock::now();
		return std::chrono::high_resolution_clock::duration(time_start, time_end);
	}
}