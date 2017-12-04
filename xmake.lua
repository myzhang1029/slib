-- debug mode
if is_mode("debug") then
	
	-- enable the debug symbols
	set_symbols("debug")

	-- disable optimization
	set_optimize("none")
end

-- release mode
if is_mode("release") then

	-- set the symbols visibility: hidden
	set_symbols("hidden")

	-- enable fastest optimization
	set_optimize("fastest")

	-- strip all symbols
	set_strip("all")
end

-- add target
target("sbl")

	-- set kind
	set_kind("$(kind)")

	-- add cflags
	add_cflags("-Iinclude")

	-- add install
	add_headers("(include/**)")

	-- add files
	add_files("src/*.c")

