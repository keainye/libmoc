add_rules("mode.debug", "mode.release")

target("mocutils")
    set_kind("static")
    add_files("src/mocutils.cc")
    add_files("src/strings.cc")
    add_files("src/serializable.cc")

target("testbyte")
  set_kind("binary")
  add_files("test/byte.cc", "src/mocutils.cc")
