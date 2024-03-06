build: src/*.cc
	g++ -c src/*.cc
	ar r libmocutils.a *.o

install: build
	@-mkdir /usr/include/mocutils
	@-mkdir /usr/lib/mocutils
	cp src/*.h /usr/include/mocutils/
	cp libmocutils.a /usr/lib/mocutils/

clean:
	rm -rf *.o
	rm -rf *.a
