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
	add_deps("clocks", "debug", "wall_clock", "strtol", "time", "freestanding")
	on_load(function(target)
		target:values_set("threads", {
			{
				compartment = "clocks",
				priority = 1,
				entry_point = "entry",
				stack_size = 0x900,
				trusted_stack_frames = 4
			}
		}, {expand = false})
	end)
	-- registerclocksource#begin
	-- Register the wall-clock source
	after_load(function(target)
		import("core.project.project")
		local wall_clock = project.target("wall_clock")
		wall_clock:add("includedirs", path.join(target:scriptdir(), "include"))
		wall_clock:add("cheriot.clock_source_includes", "example_rtc.hh")
		wall_clock:add("cheriot.clock_source_types", "ExampleWallClockSource")
	end)
	-- registerclocksource#end


