// Copyright Microsoft and CHERIoT
// Contributors.
// SPDX-License-Identifier: MIT

#include <riscvreg.h>
#include <stdio.h>
#include <thread.h>
#include <time.h>

// entry#begin
/// Thread entry point.
void __cheriot_compartment("current") entry()
{
	clock_t start = platform_monotonic_time_read();
	for (int i = 0; i < 4; i++)
	{
		clock_t nextWake =
		  start + (20000 * ((i * 2) + thread_id_get()));
		printf("Current thread: %d of %d woke at %lld, next "
		       "wake at %lld\n",
		       thread_id_get(),
		       thread_count(),
		       platform_monotonic_time_read(),
		       nextWake);
		thread_sleep(nextWake, ThreadSleepNoEarlyWake);
	}
}
// entry#end
