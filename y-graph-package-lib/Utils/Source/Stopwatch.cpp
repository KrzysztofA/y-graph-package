#include "../Headers/Stopwatch.hpp"

namespace yasuzume::utils 
{
	Stopwatch::Stopwatch() = default;
	Stopwatch::~Stopwatch() = default;

	void Stopwatch::start() 
	{
		start_time = std::chrono::high_resolution_clock::now();
	}

	double Stopwatch::end() 
	{
		std::chrono::duration<double> duration(std::chrono::high_resolution_clock::now() - start_time);
		last_end_time = duration.count();
		return last_end_time;
	}

	double Stopwatch::last_record() 
	{
		return last_end_time;
	}
}