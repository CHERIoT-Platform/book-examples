// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <debug.hh>
#include <fail-simulator-on-error.h>
#include <futex.h>
#include <queue.h>
#include <timeout.hh>
#include <token.h>

using Debug =
  ConditionalDebug<true, "Delegated Allocation">;

MessageQueue *queue;

using namespace CHERI;

/**
 * Run the producer thread, sending integers to the
 * consumer.
 */
void __cheriot_compartment("allocate") run()
{
	struct MessageQueue *__sealed_capability queue;
	// queue_allocate#begin
	// Create a capability that can allocate and free, but
	// nothing else
	auto allocateCapability = allocator_permissions_and(
	  MALLOC_CAPABILITY, AllocatorPermitAllocate);
	// Make sure that the callee can't capture this pointer
	allocateCapability =
	  Capability{allocateCapability}.without_global();
	// Allocate the queue passing the minimum set of
	// permissions
	int ret = queue_create_sealed(TimeoutNoWait,
	                              allocateCapability,
	                              &queue,
	                              sizeof(int),
	                              16);
	Debug::Assert(
	  ret == 0, "Queue creation failed: {}", ret);
	// Create a capability that can free and nothing else
	auto freeCapability =
	  allocator_permissions_and(allocateCapability, 0);
	queue_destroy_sealed(
	  TimeoutNoWait, freeCapability, queue);
	Debug::Assert(
	  ret == 0, "Queue destruction failed: {}", ret);
	// queue_allocate#end
}
