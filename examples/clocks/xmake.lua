set_project("CHERIoT example")

sdkdir = os.getenv("CHERIOT_SDK") or
	"../../cheriot-rtos/sdk/"
includes(sdkdir)

option("board")
	set_default("ibex-safe-simulator")

compartment("clocks")
	add_deps("wall_clock")
	add_files("clocks.cc")

firmware("clocks_example")
	add_deps("clocks", "debug")
	on_load(function(target)
		target:values_set("threads", {
			{
				compartment = "clocks",
				priority = 1,
				entry_point = "entry",
				stack_size = 0x400,
				trusted_stack_frames = 3
			}
		}, {expand = false})
	end)


