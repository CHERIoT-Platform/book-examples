-- Copyright Microsoft and CHERIoT Contributors.
-- SPDX-License-Identifier: MIT

set_project("CHERIoT example")

sdkdir = os.getenv("CHERIOT_SDK") or
	"../../cheriot-rtos/sdk/"
includes(sdkdir)

set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

compartment("allocate")
    add_deps("freestanding", "message_queue", "debug")
    add_files("allocate.cc")

-- Firmware image for the example.
firmware("delegated-allocation")
    add_deps("allocate")
    on_load(function(target)
        target:values_set("board", "$(board)")
        target:values_set("threads", {
            {
                compartment = "allocate",
                priority = 1,
                entry_point = "run",
                stack_size = 0x400,
                trusted_stack_frames = 3
            }
        }, {expand = false})
    end)
