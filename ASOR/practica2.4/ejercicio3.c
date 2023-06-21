/*
mkfifo: Create named pipes (FIFOs) with the given NAMEs.
[cursoredes@localhost P4]$ mkfifo namepipe
[cursoredes@localhost P4]$ ls -l
total 24
-rwxrwxr-x 1 cursoredes cursoredes 8880 Dec 10 20:02 ejercicio1
-rw-rw-r-- 1 cursoredes cursoredes 1232 Dec 10 20:04 ejercicio1.c
-rw-rw-r-- 1 cursoredes cursoredes   62 Dec 10 20:06 ejercicio3.c
prw-rw-r-- 1 cursoredes cursoredes    0 Dec 10 20:07 namepipe
-rw-rw-r-- 1 cursoredes cursoredes    6 Dec 10 19:59 prueba353.txt
[cursoredes@localhost P4]$ echo "Prueba123" > pipe
[cursoredes@localhost P4]$ stat pipe
  File: ‘pipe’
  Size: 10        	Blocks: 8          IO Block: 4096   regular file
Device: fd00h/64768d	Inode: 51418464    Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2022-12-10 20:07:44.363822068 +0100
Modify: 2022-12-10 20:07:44.363822068 +0100
Change: 2022-12-10 20:07:44.363822068 +0100
 Birth: -
[cursoredes@localhost P4]$ cat pipe
Prueba123
*/