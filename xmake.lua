set_languages("cxx17")
add_rules("mode.debug", "mode.release")
add_requires("catch2")

target("tests")
    set_kind("binary")
    add_packages("catch2")
    add_files("tests/*.cpp")

target("examples")
    set_kind("binary")
    add_files("examples/*.cpp")
