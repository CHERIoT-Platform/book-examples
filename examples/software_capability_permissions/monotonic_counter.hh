// Copyright Contributors.
// SPDX-License-Identifier: MIT

#include <atomic>
#include <compartment.h>
#include <token.h>

using MonotonicCounterState = std::atomic<int64_t>;

#define DECLARE_AND_DEFINE_COUNTER(name)                   \
	DECLARE_AND_DEFINE_STATIC_SEALED_VALUE(                  \
	  MonotonicCounterState, monotonic, CounterKey, name, 0)

typedef MonotonicCounterState
  *__sealed_capability MonotonicCounter;

// permissions#begin
/**
 * Permissions on a user-defined counter.
 */
enum [[clang::flag_enum]] MonotonicCounterPermissions
{
	CounterPermitRead = (1 << 0),
	CounterPermitIncrement = (1 << 1),
};

/**
 * Helper that returns a copy of `counter` with the subset
 * of permissions that are both already present in `counter`
 * and enumerated in `permissionsMask`. The permission mask
 * should be constructed by bitwise anding values from
 * `MonotonicCounterPermissions`.
 */
static inline MonotonicCounter
monotonic_counter_permissions_and(MonotonicCounter counter,
                                  int permissionsMask)
{
	return token_permissions_and(counter, permissionsMask);
}
// permissions#end

/**
 * Increments a monotonic counter and returns the new value.
 * This requires `CounterPermitIncrement` to increment.  If
 * `counter` does not have `CounterPermitRead` permission
 * then this will return 0 to indicate successful increment.
 *
 * Returns a negative value for errors.
 */
int64_t __cheriot_compartment("monotonic")
  monotonic_counter_increment(MonotonicCounter counter);

/**
 * Get the current value of a monotonic counter.
 *
 * Requires `CounterPermitRead` permission, returns an
 * `-EPERM` if this is not provided.
 */
int64_t __cheriot_compartment("monotonic")
  monotonic_counter_get(MonotonicCounter counter);
