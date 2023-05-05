add_rules("mode.debug", "mode.release")

target("mocutils")
    set_kind("static")
    add_files("src/mocutils.cc")
    add_files("src/strings.cc")

target("moctest")
  set_kind("binary")
  add_files("src/*.cc")
  add_deps("mocutils")
