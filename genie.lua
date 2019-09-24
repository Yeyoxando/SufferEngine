solution ("SufferEngine" .. _ACTION)
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	language "C++"
	location ("build")	
	
	projects = { "Core", "GLFW" }

	for i, prj in ipairs(projects) do 
		project (prj)
		targetname (prj)
		language "C++"
		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)
	
	    defines { "_CRT_SECURE_NO_WARNINGS" }
        flags { "ExtraWarnings" }

		configuration "vs2017"
			windowstargetplatformversion "10.0.17134.0"

		configuration "Debug"
			defines { "DEBUG" }
			targetdir ("./bin")
			targetsuffix "_d"
			objdir ("./build/Debug")
			flags { "Symbols", "NoPCH" }

		configuration "Release"
			targetdir ("./bin")
			objdir ("./build/Release")
			flags { "Optimize", "NoPCH" }

	end

project "Core"

	kind "ConsoleApp"
	files {
		"./include/*.h",
		"./src/*.cc",
	}
	includedirs{
		"./deps/GLFW/include/GLFW/",
		"./deps/GLFW/deps/glad/",
		"./include/",
		"./deps/include/",
	}
	libdirs{
		"./bin/"
	}
	links{
		"GLFW_d"
	}	
		
project "GLFW"
kind "StaticLib"
	--Common files
	files{
		"./deps/GLFW/src/context.c",
		"./deps/GLFW/src/init.c",
		"./deps/GLFW/src/input.c",
		"./deps/GLFW/src/monitor.c",
		"./deps/GLFW/src/vulkan.c",
		"./deps/GLFW/src/window.c",
		"./deps/GLFW/src/internal.h",
		"./deps/GLFW/src/mappings.h",
		"./deps/GLFW/include/GLFW/glfw3.h",
		"./deps/GLFW/include/GLFW/glfw3native.h",
	}
	includedirs{
		"./deps/GLFW/include/GLFW/",
		"./deps/GLFW/deps/",
	}
	--Windows files
	configuration "vs*"
		files {
		"./deps/GLFW/src/win32_platform.h", 
		"./deps/GLFW/src/win32_joystick.h", 
		"./deps/GLFW/src/wgl_context.h", 
		"./deps/GLFW/src/egl_context.h", 
		"./deps/GLFW/src/osmesa_context.h",
		"./deps/GLFW/src/win32_init.c", 			
		"./deps/GLFW/src/win32_joystick.c",
		"./deps/GLFW/src/win32_monitor.c",	
		"./deps/GLFW/src/win32_time.c",
		"./deps/GLFW/src/win32_thread.c",
		"./deps/GLFW/src/win32_window.c",
		"./deps/GLFW/src/wgl_context.c",
		"./deps/GLFW/src/egl_context.c",
		"./deps/GLFW/src/osmesa_context.c",
		}
		defines { 	
			"_GLFW_WIN32",
			"WIN32",
			"_WINDOWS",
		}
	--Linux files
	configuration "linux"
		files{
		
		}
	configuration {}
