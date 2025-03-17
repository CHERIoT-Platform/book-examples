#!/usr/bin/env bash

# Generate compile commands files for all known projects in this repo


. "$(dirname $0)"/../cheriot-rtos/scripts/common.sh

find_sdk $1

echo "Using SDK=$SDK"

# Generate compile_commands.json for all of the extra tests and examples.
for dir in examples/* ; do
	if [ -f "$dir/xmake.lua" ] ;  then
		echo Generating compile_commands.json for $dir
		(cd $dir && xmake f --sdk="${SDK}" && xmake project -k compile_commands)
	fi
done

# Generate the top-level compile-commands.json
cd cheriot-rtos/tests && xmake f --sdk="${SDK}" && xmake project -k compile_commands ..
