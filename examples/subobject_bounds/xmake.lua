set_project("CHERIoT example")

sdkdir = os.getenv("CHERIOT_SDK") or
	"../../cheriot-rtos/sdk/"
includes(sdkdir)

option("board")
	set_default("sail")

-- enforce_bounds#begin
compartment("bounds")
	add_rules("cheriot.subobject-bounds")
	add_files("bounds.cc")
-- enforce_bounds#end

firmware("subobject_bounds_example")
	add_deps("bounds", "stdio", "freestanding")
	on_load(function(target)
		target:values_set("threads", {
			{
				compartment = "bounds",
				priority = 1,
				entry_point = "entry",
				stack_size = 0x400,
				trusted_stack_frames = 3
			}
		}, {expand = false})
	end)


