#ifndef Y_BENCHMARKS_LIB_HPP
#define Y_BENCHMARKS_LIB_HPP

#include <chrono>
#include <functional>

namespace yasuzume::utils 
{
	template<typename R, typename... ARGS>
	double measure_execution_time(std::function<R(ARGS...)> func, ARGS... args);
}

#endif // Y_BENCHMARKS_LIB_HPP
