build: src/*.cc
	g++ -c src/*.cc
	ar r mocutils.a *.o

install: build
	cp src/*.h /usr/include/mocutils/
	cp mocutils.a /usr/lib/mocutils/

clean:
	rm -rf *.o
	rm -rf *.a
