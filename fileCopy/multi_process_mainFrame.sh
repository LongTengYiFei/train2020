#multi_process_mainFrame.c
#only multi-process can acclerate copy rate
#two different process can use different open pointer

#because multi-thread share the file table,they have same file open pointer
#you can not actually use multi-thread

#fork also can not,because parent and child have same file table
#只需要调用两次copy unit后台执行就行了
#传入copy unit的参数就是文件名1，文件名2，0或1
./copy_unit testFile1 dest 0 &
./copy_unit testFile1 dest 1 &
