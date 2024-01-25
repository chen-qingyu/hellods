set_languages("c17")
add_rules("mode.debug", "mode.release")
add_requires("catch2")

target("tests")
    set_kind("binary")
    add_packages("catch2")
    add_files("sources/**.c")
    add_files("tests/*.cpp")
