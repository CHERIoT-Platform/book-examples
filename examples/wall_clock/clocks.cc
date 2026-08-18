#include <debug.hh>
#include <time.h>

using Debug = ConditionalDebug<true, "Clock example">;

void __cheriot_compartment("clocks") entry()
{
	// gettime#begin
	int update = clock_update_wall_clock(TimeoutWaitForever);
	Debug::Assert(update == 0,
	              "Failed to update wall-clock time: {}",
	              update);
	while (true)
	{
		timeval tv;
		int     ret = gettimeofday(&tv, nullptr);
		Debug::Assert(
		  ret == 0, "Failed to get time of day: {}", ret);
		auto *timeUTC = gmtime(&tv.tv_sec);
		Debug::log(
		  "Current UNIX epoch time: {} {}-{}-{} {}:{}:{} UTC",
		  tv.tv_sec,
		  timeUTC->tm_year + 1900,
		  timeUTC->tm_mon + 1,
		  timeUTC->tm_mday,
		  timeUTC->tm_hour,
		  timeUTC->tm_min,
		  timeUTC->tm_sec);
		Timeout t(MS_TO_TICKS(1000));
		thread_sleep(&t, ThreadSleepNoEarlyWake);
	}
	// gettime#end
}
