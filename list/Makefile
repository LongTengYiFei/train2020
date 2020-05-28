test:
	gcc mainFrame.c ./cyf_list.so  -o test.exe
.PHONY : so run
so: #first step
	gcc cyf_list.c -fPIC -shared -o cyf_list.so
run: #second step
	gcc mainFrame.c ./cyf_list.so  -o test.exe
	./test.exe
