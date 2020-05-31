test:
	gcc mainFrame.c ./cyf_kbRead.so  -o test.exe
.PHONY : so run
so: #first step
	gcc cyf_kbRead.c -fPIC -shared -o cyf_kbRead.so
run: #second step
	gcc mainFrame.c ./cyf_kbRead.so  -o test.exe
	sudo ./test.exe
