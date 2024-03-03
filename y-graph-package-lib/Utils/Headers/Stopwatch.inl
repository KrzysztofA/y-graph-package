#ifndef Y_UTILS_STOPWATCH_INL
#define Y_UTILS_STOPWATCH_INL

#include <chrono>;

namespace yasuzume::utils
{
  class Stopwatch
  {
  public:
    static void start()
    {
      start_time = std::chrono::high_resolution_clock::now();
    }

    static double end()
    {
      const std::chrono::duration<double> duration( std::chrono::high_resolution_clock::now() - start_time );
      last_end_time = duration.count();
      return last_end_time;
    }

    [[nodiscard]] static double last_record()
    {
      return last_end_time;
    }

  private:
    static std::chrono::high_resolution_clock::time_point start_time;
    static double last_end_time;
  };

  double Stopwatch::last_end_time{ 0 };
  std::chrono::high_resolution_clock::time_point Stopwatch::start_time{ };
}

#endif // !Y_UTILS_STOPWATCH_INL