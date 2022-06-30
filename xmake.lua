set_project("CustomRasterizer")
set_version("0.0.1")

set_languages("c99", "c++17")

add_requires("fmt 8.0.1", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("spdlog v1.9.0", {system = false, configs = {shared = false, debug = true, fmt_external = true, cxflags = "-fPIC"}})
add_requires("glad v0.1.34", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("yaml-cpp 0.7.0", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("eigen 3.4.0", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("glfw 3.3.4", {system = false, glfw_include = "none", configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("tinygltf v2.5.0", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})
add_requires("stb", {system = false, configs = {shared = false, debug = true, cxflags = "-fPIC"}})

add_includedirs(
    "./"
)

target("CustomRasterizer")
    set_kind("binary")
    add_files(
        "*.cpp",
        "Log/*.cpp",
        "Platform/*.cpp",
        "Rasterizer/*.cpp",
        "Utils/*.cpp"
    )
    add_packages(
        "glfw", 
        "glad", 
        "eigen", 
        "yaml-cpp", 
        "spdlog", "fmt", 
        --"nlohmann_json",
        "tinygltf",
        "stb",
        {public = true}
    )
target_end()