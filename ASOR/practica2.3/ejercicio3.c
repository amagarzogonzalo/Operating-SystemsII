/*
[cursoredes@localhost Documents]$ ./ejercicoi2 
Sched: FIFO.
Valor Maximo: 99.
Valor Minimo: 1.
Prioridad 10.
[cursoredes@localhost Documents]$ ps
  PID TTY          TIME CMD
 3049 pts/1    00:00:00 bash
11120 pts/1    00:00:00 ps
[cursoredes@localhost Documents]$ sudo chrt -f -p 12 3049
[cursoredes@localhost Documents]$ sudo nice -n -10 /bin/sh
sh-4.2# ls
ejercicio2.c  ejercicio3.c  ejercicoi2
sh-4.2# ./ejercicoi2 
Sched: FIFO.
Valor Maximo: 99.
Valor Minimo: 1.
Prioridad 12.
*/
