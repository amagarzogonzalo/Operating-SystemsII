/*

-----APARTADO 1-----
ln - make links between files
-s, --symbolic
              make symbolic links instead of hard links



[cursoredes@localhost P2]$ touch prueba10
[cursoredes@localhost P2]$ mkdir prueba10b
[cursoredes@localhost P2]$ ln -s prueba10 prueba10simbolico
[cursoredes@localhost P2]$ ln -s prueba10b prueba10bsimbolico
[cursoredes@localhost P2]$ ls -l
total 52
-rwxr-x--- 1 cursoredes cursoredes 8952 Nov 21 11:42 ejercicio
-rw-rw-r-- 1 cursoredes cursoredes  110 Nov 21 11:48 ejercicio10.c
-rw-rw-r-- 1 cursoredes cursoredes  421 Nov 21 09:24 ejercicio1.c
-rw-rw-r-- 1 cursoredes cursoredes  250 Nov 21 09:30 ejercicio2.c
-rw-rw-r-- 1 cursoredes cursoredes  182 Nov 21 09:45 ejercicio3.c
-rw-rw-r-- 1 cursoredes cursoredes  392 Nov 21 09:45 ejercicio4.c
-rw-rw-r-- 1 cursoredes cursoredes  973 Nov 21 10:04 ejercicio5.c
-rw-rw-r-- 1 cursoredes cursoredes  812 Nov 21 10:28 ejercicio6.c
-rw-rw-r-- 1 cursoredes cursoredes 1152 Nov 21 10:31 ejercicio7.c
-rw-rw-r-- 1 cursoredes cursoredes 1022 Nov 21 10:35 ejercicio8.c
-rw-rw-r-- 1 cursoredes cursoredes 1817 Nov 21 11:42 ejercicio9.c
-rw-r----- 1 cursoredes cursoredes    0 Nov 21 11:52 prueba10
drwxr-x--- 2 cursoredes cursoredes    6 Nov 21 11:52 prueba10b
lrwxrwxrwx 1 cursoredes cursoredes    9 Nov 21 11:52 prueba10bsimbolico -> prueba10b
lrwxrwxrwx 1 cursoredes cursoredes    8 Nov 21 11:52 prueba10simbolico -> prueba10
-rwxr-x--- 1 cursoredes cursoredes    0 Nov 21 10:27 prueba7.txt
[cursoredes@localhost P2]$ ls -i
3125623 ejercicio        30896 ejercicio2.c  3125606 ejercicio5.c  3125629 ejercicio8.c  3125636 prueba10b           3125628 prueba7.txt
3125634 ejercicio10.c    30901 ejercicio3.c  3125627 ejercicio6.c  3125630 ejercicio9.c  3125638 prueba10bsimbolico
  30893 ejercicio1.c     30822 ejercicio4.c  3125626 ejercicio7.c  3125635 prueba10      3125637 prueba10simbolico

Si se crean enlaces simbólicos, los inodos de cada fichero sin diferentes. 
Además con ls -l sale la l para enlaces simbólicos.

-----APARTADO 2-----
[cursoredes@localhost P2]$ touch prueba102
[cursoredes@localhost P2]$ mkdir prueba102b
[cursoredes@localhost P2]$ ln prueba102 prueba102duro
[cursoredes@localhost P2]$ ln prueba102b prueba102bduro
ln: ‘prueba102b’: hard link not allowed for directory
[cursoredes@localhost P2]$ ls -li
total 52
 3125623 -rwxr-x--- 1 cursoredes cursoredes 8952 Nov 21 11:42 ejercicio
 3125634 -rw-rw-r-- 1 cursoredes cursoredes 1842 Nov 21 11:54 ejercicio10.c
   30893 -rw-rw-r-- 1 cursoredes cursoredes  421 Nov 21 09:24 ejercicio1.c
   30896 -rw-rw-r-- 1 cursoredes cursoredes  250 Nov 21 09:30 ejercicio2.c
   30901 -rw-rw-r-- 1 cursoredes cursoredes  182 Nov 21 09:45 ejercicio3.c
   30822 -rw-rw-r-- 1 cursoredes cursoredes  392 Nov 21 09:45 ejercicio4.c
 3125606 -rw-rw-r-- 1 cursoredes cursoredes  973 Nov 21 10:04 ejercicio5.c
 3125627 -rw-rw-r-- 1 cursoredes cursoredes  812 Nov 21 10:28 ejercicio6.c
 3125626 -rw-rw-r-- 1 cursoredes cursoredes 1152 Nov 21 10:31 ejercicio7.c
 3125629 -rw-rw-r-- 1 cursoredes cursoredes 1022 Nov 21 10:35 ejercicio8.c
 3125630 -rw-rw-r-- 1 cursoredes cursoredes 1817 Nov 21 11:42 ejercicio9.c
 3125628 -rw-r----- 2 cursoredes cursoredes    0 Nov 21 12:00 prueba102
17153652 drwxr-x--- 2 cursoredes cursoredes    6 Nov 21 12:00 prueba102b
 3125628 -rw-r----- 2 cursoredes cursoredes    0 Nov 21 12:00 prueba102duro

NO se pueden crear enlaces duros para directorios.
Prueba102 y preuba102duro tienen el mismo inodo.
0
-----APARTADO 3-----
Para archivo, borrar duro o simbolico OK
[cursoredes@localhost P2]$ rm prueba102duro
[cursoredes@localhost P2]$ rm prueba1000simbolico
Para directorio, borrar simbolico OK
[cursoredes@localhost P2]$ rm -r prueba102bsimb

Además, borrar enlace simbolico disminuye los enlaces del archivo (fichero o directorio) 
Cuando se borra original el simbolico quda corrupto, en rojo

*/