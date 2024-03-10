build: src/*.cc
	g++ -c src/*.cc
	ar -crv libmocutils.a *.o

install: build
	@-mkdir /usr/include/mocutils
	@-mkdir /usr/lib/mocutils
	@-mkdir /usr/lib/gcc/$(shell uname -m)-linux-gnu/mocutils
	cp src/*.h /usr/include/mocutils/
	cp libmocutils.a /usr/lib/mocutils/
	cp libmocutils.a /usr/lib/gcc/$(shell uname -m)-linux-gnu/mocutils/

clean:
	rm -rf *.o
	rm -rf *.a
