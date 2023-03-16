workspace "prokaryotic"
    architecture "x64"
    startproject "sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder(solution directory)
Include_dir = {}
Include_dir["glm"]   = "prokaryotic/vendor/glm-0.9.9.7"

project "prokaryotic"
    location "prokaryotic"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/vendor/glm-0.9.9.7/glm/**.hpp",
        "%{prj.name}/vendor/glm-0.9.9.7/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor",
        "%{Include_dir.glm}"
    }

    libdirs
    {
        "%{prj.name}/libs",
    }

    links
    {        
        "opengl32.lib",
        "shlwapi.lib",
        "glfw3.lib",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "PRKRTC_PLATFORM_WINDOWS",
            "PRKRTC_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/sandbox/\"")
        }

    filter "configurations:Debug"
        defines "PRKRTC_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PRKRTC_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "PRKRTC_DIST"
        runtime "Release"
        optimize "On"

project "sandbox"
    location "sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "prokaryotic/src",
        "prokaryotic/vendor/spdlog/include",
        "prokaryotic/vendor", 
        "%{Include_dir.glm}"       
    }

    links
    {
        "prokaryotic"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "PRKRTC_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "PRKRTC_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "PRKRTC_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        runtime "Release"
        optimize "On"















































    