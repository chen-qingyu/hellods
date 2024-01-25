add_rules("mode.debug", "mode.release")
set_languages("c17")
add_requires("catch2")

target("tests")
    set_kind("binary")
    add_files("sources/**.c")
    add_files("tests/*.cpp")
    add_packages("catch2")
