/*

[cursoredes@localhost P2]$ cat /proc/locks
1: POSIX  ADVISORY  WRITE 1578 fd:00:53013121 0 EOF
2: POSIX  ADVISORY  WRITE 1571 fd:00:53013120 0 EOF
3: POSIX  ADVISORY  WRITE 1564 fd:00:53012991 0 EOF
4: POSIX  ADVISORY  WRITE 1554 fd:00:53012987 0 EOF
5: POSIX  ADVISORY  WRITE 1351 00:13:21364 0 EOF
6: FLOCK  ADVISORY  WRITE 1314 fd:00:17458434 0 EOF
7: FLOCK  ADVISORY  WRITE 1314 fd:00:30831 0 EOF
8: FLOCK  ADVISORY  WRITE 1046 00:13:19967 0 EOF
9: POSIX  ADVISORY  WRITE 1045 00:13:19949 0 EOF
10: POSIX  ADVISORY  WRITE 784 00:13:16343 0 EOF
12: POSIX  ADVISORY  WRITE 480 00:13:12778 0 EOF


Each lock has its own line which starts with a unique number. 
The second column refers to the class of lock used, with FLOCK signifying the older-style UNIX file locks
 from a flock system call and POSIX representing 
the newer POSIX locks from the lockf system call.
The third column can have two values: ADVISORY or MANDATORY. 
ADVISORY means that the lock does not prevent other people from accessing the data; it only prevents other 
attempts to lock it. MANDATORY means that no other access to the data is permitted while the lock is held. 
The fourth column reveals whether the lock is allowing the holder READ or WRITE access to the file. 
The fifth column shows the ID of the process holding the lock. The sixth column shows the ID of the file being locked, 
in the format of MAJOR-DEVICE:MINOR-DEVICE:INODE-NUMBER. The seventh and eighth column shows the start and end of the file's locked region.


*/