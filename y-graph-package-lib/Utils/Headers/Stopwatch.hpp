#ifndef Y_STOPWATCH_LIB_HPP
#define Y_STOPWATCH_LIB_HPP

#include <chrono>;

namespace yasuzume::utils 
{
	class Stopwatch
	{
	public:
		Stopwatch();
		~Stopwatch();
		
		void start();
		double end();
		double last_record();
	private:
		std::chrono::high_resolution_clock::time_point start_time;
		double last_end_time = 0;
	};
}

#endif // Y_STOPWATCH_LIB_HPP