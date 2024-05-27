ifeq ($(OS), Windows_NT)
	rm = del
	cp = copy
	d  = \\
	mkdir = md
	INCLUDE_DIR = C:\include
	LIB_DIRS = C:\lib
	suffix = exe
else
	OS = Linux
	rm = rm
	force = -f
	recursion = -r
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
	-$(rm) $(recursion) $(INCLUDE_DIR)$(d)mocutils
	-$(foreach dir, $(LIB_DIRS), $(rm) $(dir)$(d)libmocutils.a)

clean:
	$(rm) $(force) *.o
	$(rm) $(force) *.a
	$(rm) $(force) *.cc
	$(rm) $(force) *.h
	$(rm) $(force) *.$(suffix)

t = test
test: build
	g++ -o $(t).$(suffix) test/$(t).cc -Isrc -L./ -lmocutils
	./$(t).$(suffix)

copy:
	$(cp) src$(d)* .

.PHONY: FORCE
FORCE:
