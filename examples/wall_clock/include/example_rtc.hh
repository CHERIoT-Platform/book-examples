#pragma once
#include <debug.hh>
#include <fail-simulator-on-error.h>
#include <platform/concepts/wall_clock_source.hh>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

namespace
{
	/**
	 * Convert a month name from `__DATE__` into a number.
	 */
	int month_from_name(std::string_view monthName)
	{
		if (monthName == "Jan")
		{
			return 0;
		}
		if (monthName == "Feb")
		{
			return 1;
		}
		if (monthName == "Mar")
		{
			return 2;
		}
		if (monthName == "Apr")
		{
			return 3;
		}
		if (monthName == "May")
		{
			return 4;
		}
		if (monthName == "Jun")
		{
			return 5;
		}
		if (monthName == "Jul")
		{
			return 6;
		}
		if (monthName == "Aug")
		{
			return 7;
		}
		if (monthName == "Sep")
		{
			return 8;
		}
		if (monthName == "Oct")
		{
			return 9;
		}
		if (monthName == "Nov")
		{
			return 10;
		}
		if (monthName == "Dec")
		{
			return 11;
		}
		return -1;
	}

	/**
	 * Uses the `__DATE__` and `__TIME__` pre-defined macros to create a
	 * snapshot time value and reports this as the boot time.
	 */
	clock_t build_time()
	{
		struct tm tm;
		// Date is in the format "Aug 17 2026"
		char *date = const_cast<char *>(__DATE__);
		tm.tm_mon  = month_from_name({date, 3});
		tm.tm_mday = strtol(date + 3, &date, 10);
		tm.tm_year = strtol(date, nullptr, 10) - 1900;
		// Time is in the format "11:29:08"
		char *time = const_cast<char *>(__TIME__);
		char *end  = time + 2;
		tm.tm_hour = strtol(time, &end, 10);
		time += 3;
		end       = time + 2;
		tm.tm_min = strtol(time, &end, 10);
		time += 3;
		tm.tm_sec = strtol(time, nullptr, 10);
		// Seconds since the epoch
		time_t now = timegm(&tm);
		// Clock ticks since the epoch
		return now * CLOCKS_PER_SEC;
	}
} // namespace

// clocksource#begin
struct ExampleWallClockSource
{
	/// This example source does not support setting the time.
	static constexpr bool SupportsTimeSetting = false;
	/// This example source is quick to compute
	static constexpr bool IsCheap = true;
	/// Calculate the time, assume that boot time is build
	/// time
	int get_time(TimeoutArgument,
	             clock_t &outRealTime,
	             clock_t &outMonotonicTime,
	             int     &outPriority)
	{
		outMonotonicTime = 0;
		// Compute the time when this image was built
		outRealTime      = build_time();
		// This is a terrible time source
		outPriority = -5000;
		return 0;
	}
};
// clocksource#end
