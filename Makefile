ifeq ($(OS), Windows_NT)
	rm = del
	cp = copy
	d  = \\
	mkdir = md
	INCLUDE_DIR = C:\include
	LIB_DIRS = C:\lib
else
	rm = rm
	cp = cp
	d  = /
	mkdir = mkdir
	INCLUDE_DIR = /usr/include
	LIB_DIRS = $(wildcard /usr/lib/gcc/$(shell uname -m)-linux-gnu/*)
endif

build: src/*.cc
	g++ -c src/*.cc
	ar -crv libmocutils.a *.o

install: build uninstall
	-$(mkdir) $(INCLUDE_DIR)$(d)mocutils
	$(cp) src$(d)*.h $(INCLUDE_DIR)$(d)mocutils$(d)
	-$(foreach dir, $(LIB_DIRS), $(mkdir) $(dir))
	$(foreach dir, $(LIB_DIRS), $(cp) libmocutils.a $(dir)$(d))
	@echo [ok] Installation finished.

uninstall:
	-$(rm) $(INCLUDE_DIR)$(d)mocutils
	-$(foreach dir, $(LIB_DIRS), $(rm) $(dir)$(d)libmocutils.a)

clean:
	$(rm) *.o
	$(rm) *.a
	$(rm) *.cc
	$(rm) *.h

copy:
	$(cp) src$(d)* .
