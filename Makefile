build: src/*.cc
	g++ -c src/*.cc
	ar r mocutils.a *.o

install: build
	cp src/*.h /usr/include/
	cp mocutils.a /usr/lib/

clean:
	rm -rf *.o
	rm -rf *.a
