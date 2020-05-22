.PHONY : sotest so clean
sotest: 
	gcc fifo.c -fPIC -shared -o fifo.so
	gcc main.c ./fifo.so -o sotest.exe
	mkdir build
	mv fifo.so ./build
	mv sotest.exe ./build
so:
	gcc fifo.c -fPIC -shared -o fifo.so
	mkdir build
	mv fifo.so ./build
clean:
	rm -fr build/
