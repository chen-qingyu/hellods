set_project("hellods")
set_version("2.4.0")
set_languages("cxx17")

add_rules("mode.debug", "mode.release")
add_requires("catch2")

target("test")
    set_kind("binary")
    add_packages("catch2")
    add_files("tests/*.cpp")

target("example")
    set_kind("binary")
    add_files("examples/*.cpp")
