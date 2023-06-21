/*
Se puede usar stat -f o stat -L con el fichero para ver la siguiente información:
[cursoredes@localhost P2]$ ls -i
3125623 ejercicio       30896 ejercicio2.c    30822 ejercicio4.c  3125627 ejercicio6.c  3125629 ejercicio8.c
  30893 ejercicio1.c    30901 ejercicio3.c  3125606 ejercicio5.c  3125626 ejercicio7.c  3125628 prueba7.txt
[cursoredes@localhost P2]$ stat ejercicio7.c -L
  File: ‘ejercicio7.c’
  Size: 1152      	Blocks: 8          IO Block: 4096   regular file
Device: fd00h/64768d	Inode: 3125626     Links: 1
Access: (0664/-rw-rw-r--)  Uid: ( 1000/cursoredes)   Gid: ( 1000/cursoredes)
Access: 2022-11-21 10:24:23.085687572 +0100
Modify: 2022-11-21 10:31:00.951585139 +0100
Change: 2022-11-21 10:31:00.951585139 +0100
 Birth: -
[cursoredes@localhost P2]$ stat ejercicio7.c -f
  File: "ejercicio7.c"
    ID: fd0000000000 Namelen: 255     Type: xfs
Block size: 4096       Fundamental block size: 4096
Blocks: Total: 4452864    Free: 3150712    Available: 3150712
Inodes: Total: 8910848    Free: 8680166
*/