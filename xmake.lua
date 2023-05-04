add_rules("mode.debug", "mode.release")

target("mocutils")
    set_kind("static")
    add_files("src/mocutils.cpp")

target("moctest")
  set_kind("binary")
  add_files("src/test.cpp")
  add_deps("mocutils")
