workspace "MyOpenGL_Engine 2.0"
    architecture "x64"
    configurations{
        "Debug",
        "Release"
    }

project "MyOpenGL_Engine 2.0"
    location"MyOpenGL_Engine 2.0"
    kind "ConsoleApp"
    language "C++"
    targetdir ("$(SolutionDir)$(Platform)/$(Configuration)/")
    objdir ("$(Platform)/")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.inl"
    }

    includedirs{
        "$(SolutionDir)dependencer/GLFW/include",
        "$(SolutionDir)dependencer/GLEW/include",
        "$(SolutionDir)%{prj.name}/src/extra",
        "$(SolutionDir)%{prj.name}/src"
    }

    defines{
        "GLEW_STATIC"
    }

    libdirs{
        "dependencer/GLFW/lib-vc2022",
        "dependencer/GLEW/lib/Release/x64"
    }

    links{
        "glew32s.lib",
        "glfw3.lib",
        "opengl32.lib"
    }

