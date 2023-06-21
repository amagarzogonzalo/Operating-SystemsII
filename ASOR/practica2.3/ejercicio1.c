/*
[cursoredes@localhost ~]$ ps
  PID TTY          TIME CMD
 1896 pts/0    00:00:00 bash
 2462 pts/0    00:00:00 ps

[cursoredes@localhost ~]$ chrt -v -p 1896
pid 1896's current scheduling policy: SCHED_OTHER
pid 1896's current scheduling priority: 0

------
man chrt
-f, --fifo
    Set scheduling policy to SCHED_FIFO.
-o, --other
    Set policy scheduling policy to SCHED_OTHER.
-r, --rr
    Set  scheduling  policy to SCHED_RR.  When policy is not defined the SCHED_RR is used as default
------

[cursoredes@localhost ~]$ ps ax -o pid,ni,cmd
  PID  NI CMD
    1   0 /usr/lib/systemd/systemd --switched-root --system --deserialize 22
    2   0 [kthreadd]
    3   0 [ksoftirqd/0]
    4   0 [kworker/0:0]
    5 -20 [kworker/0:0H]
    7   - [migration/0]
    8   0 [rcu_bh]
    9   0 [rcu_sched]
   10 -20 [lru-add-drain]
   ... ... ...

[cursoredes@localhost ~]$ chrt -f -p 12 1896
[cursoredes@localhost ~]$ sudo nice -n -10 /bin/sh
sh-4.2# ps ax -o pid,ni,cmd
  PID  NI CMD
  ... ... ...
 2691   0 [kworker/0:3]
 2766   0 /bin/sh
 2792   0 sleep 60
 2793   0 /bin/sh
 2796   0 sudo nice -n -10 /bin/sh
 2797 -10 /bin/sh
 2798   0 [kworker/0:0]
 2799 -10 ps ax -o pid,ni,cmd

*/
