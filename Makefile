build: src/*.cc
	g++ -c src/*.cc
	ar r mocutils.a *.o

clean:
	rm -rf *.o
	rm -rf *.a
