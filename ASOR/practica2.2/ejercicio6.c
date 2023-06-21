/* 
umask(mask) establece mascara a 777 AND mask 
Es 027 ya que usuario se deja en 0, grupo 2 porque es 10 y write se prohibe y otros 7 111 para prohibir todo.
[cursoredes@localhost P2]$ umask 027
[cursoredes@localhost P2]$ mkdir nuevaprueba
[cursoredes@localhost P2]$ ls -l
total 32
-rwxrwxr-x 1 cursoredes cursoredes 8496 Nov 21 10:03 ejercicio
-rw-rw-r-- 1 cursoredes cursoredes  421 Nov 21 09:24 ejercicio1.c
-rw-rw-r-- 1 cursoredes cursoredes  250 Nov 21 09:30 ejercicio2.c
-rw-rw-r-- 1 cursoredes cursoredes  182 Nov 21 09:45 ejercicio3.c
-rw-rw-r-- 1 cursoredes cursoredes  392 Nov 21 09:45 ejercicio4.c
-rw-rw-r-- 1 cursoredes cursoredes  973 Nov 21 10:04 ejercicio5.c
-rw-rw-r-- 1 cursoredes cursoredes    0 Nov 21 10:06 ejercicio6.c
drwxr-x--- 2 cursoredes cursoredes    6 Nov 21 10:16 nuevaprueba

*/
