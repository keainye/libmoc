add_rules("mode.debug", "mode.release")

target("mocutils")
    set_kind("static")
    add_files("src/*.cc")

target("testbyte")
  set_kind("binary")
  add_deps("mocutils")
  add_files("test/byte.cc")

target("testchannel")
  set_kind("binary")
  add_deps("mocutils")
  add_files("test/channel.cc")
