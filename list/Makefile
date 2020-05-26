test:
	gcc mainFrame.c ./cyf_list.so  -o test.exe
.PHONY : so run
so:
	gcc cyf_list.c -fPIC -shared -o cyf_list.so
run:
	gcc mainFrame.c ./cyf_list.so  -o test.exe
	./test.exe
