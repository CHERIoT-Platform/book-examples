#include <debug.hh>
#include <time.h>

using Debug = ConditionalDebug<true, "Clocks Example">;

void __cheriot_compartment("clocks") entry()
{
	// gettime-begin
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	Debug::log("Monotonic time: {} seconds, {} nanoseconds",
	           ts.tv_sec,
	           static_cast<int>(ts.tv_nsec));
	clock_gettime(CLOCK_REALTIME, &ts);
	Debug::log("Wall-clock time: {} seconds, {} nanoseconds",
	           ts.tv_sec,
	           static_cast<int>(ts.tv_nsec));
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
	Debug::log("Thread CPU time: {} seconds, {} nanoseconds",
	           ts.tv_sec,
	           static_cast<int>(ts.tv_nsec));
	// gettime-end
}
