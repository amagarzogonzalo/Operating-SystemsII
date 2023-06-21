/*
[cursoredes@localhost practica2.2]$ sleep 100&
[1] 13807

[cursoredes@localhost practica2.2]$ kill 13807
[1]+  Terminated              sleep 100

[cursoredes@localhost practica2.2]$ kill -s SIGINT 13876
[1]+  Interrupt               sleep 100

[cursoredes@localhost practica2.2]$ kill -s SIGHUP 13837
[1]+  Hangup                  sleep 100

*/