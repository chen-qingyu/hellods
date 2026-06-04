set_project("hellods")
set_version("2.11.0")
set_languages("cxx23")
set_encodings("utf-8")

add_rules("mode.debug", "mode.release")
add_requires("catch2")
if is_plat("windows") then -- disable permissive mode for strict standard compliance
    add_cxflags("/permissive-")
end

target("test")
    set_kind("binary")
    add_packages("catch2")
    add_files("tests/*.cpp")

target("example")
    set_kind("binary")
    add_files("examples/*.cpp")
