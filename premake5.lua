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
    systemversion "latest"
    targetdir ("$(SolutionDir)$(Platform)/$(Configuration)/")
    objdir ("$(Platform)/$(Configuration)/")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "$(SolutionDir)dependencer/GLFW/include",
        "$(SolutionDir)dependencer/GLEW/include",
        "$(SolutionDir)MyOpenGL_Engine 2.0/src/extra",
        "$(SolutionDir)MyOpenGL_Engine 2.0/src"
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

