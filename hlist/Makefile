test:
	gcc mainFrame.c ./cyf_hlist.so  -o test.exe
.PHONY : so run
so: #first step
	gcc cyf_hlist.c -fPIC -shared -o cyf_hlist.so
run: #second step
	gcc mainFrame.c ./cyf_hlist.so  -o test.exe
	./test.exe
