// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include "monotonic_counter.hh"
#include <fail-simulator-on-error.h>
#include <stdio.h>

// Declare and define a counter for this to use.
DECLARE_AND_DEFINE_COUNTER(aCounter)

void __cheriot_compartment("caller") entry()
{
	// reduce_permissions#begin
	// Get a pointer to the valid counter and two
	// restricted-permission views
	auto omnipotentCounter = STATIC_SEALED_VALUE(aCounter);
	auto incrementOnlyCounter =
	  monotonic_counter_permissions_and(
	    omnipotentCounter, CounterPermitIncrement);
	auto readOnlyCounter = monotonic_counter_permissions_and(
	  omnipotentCounter, CounterPermitRead);
	// reduce_permissions#end

	// use_capabilities#begin
	// Try to increment with the three handles
	printf("Counter increment with omnipotent capability "
	       "returned %lld\n",
	       monotonic_counter_increment(omnipotentCounter));
	printf("Counter increment with increment-only capability "
	       "returned %lld\n",
	       monotonic_counter_increment(incrementOnlyCounter));
	printf("Counter increment with read-only capability "
	       "returned %lld\n",
	       monotonic_counter_increment(readOnlyCounter));
	printf("Reading counter with read-only counter returned "
	       "%lld\n",
	       monotonic_counter_get(readOnlyCounter));
	printf("Reading counter with increment-only counter "
	       "returned %lld\n",
	       monotonic_counter_get(incrementOnlyCounter));
	// use_capabilities#end
}
