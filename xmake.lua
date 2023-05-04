add_rules("mode.debug", "mode.release")

add_headerfiles("src/mocutils")

target("mocutils")
    set_kind("static")
    add_files("src/mocutils.cc")

target("moctest")
  set_kind("binary")
  add_files("src/test.cc")
  add_deps("mocutils")
