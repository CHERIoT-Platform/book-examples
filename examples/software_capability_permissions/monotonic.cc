// Copyright CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include "monotonic_counter.hh"
#include <errno.h>
#include <token.h>

namespace
{
	// check_permissions#begin
	/**
	 * Helper to check that a counter has the required
	 * permissions.
	 */
	bool check_permissions(MonotonicCounter counter,
	                       int              permissions)
	{
		return (token_permissions_get(counter) & permissions) ==
		       permissions;
	}
	// check_permissions#end
} // namespace

// increment#begin
int64_t
monotonic_counter_increment(MonotonicCounter sealedCounter)
{
	if (!check_permissions(sealedCounter,
	                       CounterPermitIncrement))
	{
		return -EPERM;
	}
	if (auto *counter = token_unseal(
	      STATIC_SEALING_TYPE(CounterKey), sealedCounter))
	{
		auto result = ++(*counter);
		if (!check_permissions(sealedCounter,
		                       CounterPermitRead))
		{
			return 0;
		}
		return result;
	}
	return -EINVAL;
}
// increment#end

// get#begin
int64_t
monotonic_counter_get(MonotonicCounter sealedCounter)
{
	if (!check_permissions(sealedCounter, CounterPermitRead))
	{
		return -EPERM;
	}
	if (auto *counter = token_unseal(
	      STATIC_SEALING_TYPE(CounterKey), sealedCounter))
	{
		return counter->load();
	}
	return -EINVAL;
}
// get#end
