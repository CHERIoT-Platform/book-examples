// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include "interface.h"
#include <stdio.h>

// callback#begin
int __cheriot_callback callback(int counter)
{
	printf("Counter value: %d\n", counter);
	return 0;
}
// callback#end

/// Thread entry point.
void __cheriot_compartment("entry") entry()
{
	// compartment_call#begin
	increment();
	monotonic(callback);
	monotonic(&callback);
	// compartment_call#end
}
