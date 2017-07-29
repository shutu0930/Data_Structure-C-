
class Timer{
public:
	Timer();
	double elapsed_time();
	void reset();
private:
	clock_t start_time;
};

Timer::Timer()
{
	start_time=clock();
}

double Timer::elapsed_time()
{
	clock_t end_time=clock();
	return((double)(end_time-start_time))/((double)CLK_TCK);
}

void Timer::reset()
{
	start_time=clock();
}