solution ("SufferEngine")
	configurations { "Debug", "Release" }
	platforms { "x32", "x64" }
	language "C++"
	location ("build")	
	
	projects = { "SufferCore" }

	for i, prj in ipairs(projects) do 
		project (prj)
		targetname (prj)
		language "C++"
		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)
	
        flags { "ExtraWarnings" }

		defines { 	
			"_CRT_SECURE_NO_WARNINGS",
			}
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

project "SufferCore"

	kind "ConsoleApp"
	
	includedirs{
		"./src/deps/GLFW/include/GLFW/",
		"./src/deps/GLFW/include/",
		"./src/deps/GLFW/deps/glad/",
		"./src/deps/glew/include/",
		"./src/deps/imgui/",
		"./include/",
		"./deps/glm/",
		"./deps/sokol/",
		"./deps/pplux/",
		"./deps/include/",
	}

	--Common files
	files{
		--SufferEngine
		"./include/*.h",
		"./include/Memory_Management*.h",
		"./src/*.cc",

		--GLFW
		"./src/deps/GLFW/src/context.c",
		"./src/deps/GLFW/src/init.c",
		"./src/deps/GLFW/src/input.c",
		"./src/deps/GLFW/src/monitor.c",
		"./src/deps/GLFW/src/vulkan.c",
		"./src/deps/GLFW/src/window.c",
		"./src/deps/GLFW/src/internal.h",
		"./src/deps/GLFW/src/mappings.h",
		"./src/deps/GLFW/include/GLFW/glfw3.h",
		"./src/deps/GLFW/include/GLFW/glfw3native.h",
		
		--GLM
		"./deps/glm/*.h",
		"./deps/glm/*.hpp",

		--Sokol
		"./deps/sokol/*.h",

		--PpluX
		"./deps/pplux/*.h",

		--ImGui
		"./src/deps/imgui/imgui.cpp",
		"./src/deps/imgui/imgui.h",
		"./src/deps/imgui/imgui_demo.cpp",
		"./src/deps/imgui/imgui_draw.cpp",
		"./src/deps/imgui/imgui_widgets.cpp",
		"./src/deps/imgui/imgui_impl_glfw.cpp",
		"./src/deps/imgui/imgui_impl_opengl3.cpp",
		"./src/deps/imgui/imgui_internal.h",
		"./src/deps/imgui/imstb_rectpack.h",
		"./src/deps/imgui/imstb_textedit.h",
		"./src/deps/imgui/imstb_truetype.h",
		
		--GLEW
		"./src/deps/glew/include/GL/glew.h",
		"./src/deps/glew/include/GL/wglew.h",
		"./src/deps/glew/src/glew.c",

	}

	--Windows files
	configuration "vs*"
		files {
		--GLFW
		"./src/deps/GLFW/src/win32_platform.h", 
		"./src/deps/GLFW/src/win32_joystick.h", 
		"./src/deps/GLFW/src/wgl_context.h", 
		"./src/deps/GLFW/src/egl_context.h", 
		"./src/deps/GLFW/src/osmesa_context.h",
		"./src/deps/GLFW/src/win32_init.c", 			
		"./src/deps/GLFW/src/win32_joystick.c",
		"./src/deps/GLFW/src/win32_monitor.c",	
		"./src/deps/GLFW/src/win32_time.c",
		"./src/deps/GLFW/src/win32_thread.c",
		"./src/deps/GLFW/src/win32_window.c",
		"./src/deps/GLFW/src/wgl_context.c",
		"./src/deps/GLFW/src/egl_context.c",
		"./src/deps/GLFW/src/osmesa_context.c",
		}
		defines { 	
			"GLEW_STATIC",
			"_GLFW_WIN32",
			"WIN32",
			"_WIN32",
			"_WINDOWS",
			"SOKOL_IMPL",
			"PX_SCHED_IMPLEMENTATION",
		}
		links{
			"opengl32"
		}
	--Linux files
	configuration "linux"
		files{
		
		}
	configuration {}
