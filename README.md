# "mehl"-server

mehl-server is the first and only open source implementation of a mehl-server.

# Building from source

```
$ git clone https://github.com/disco-stu/mehl-server
$ cd mehl-server
$ make
gcc -c -Wall --pedantic -g mehl.c -o mehl.o
gcc -c -Wall --pedantic -g list.c -o list.o
gcc -c -Wall --pedantic -g parser.c -o parser.o
gcc -lpthread -g mehl.o list.o parser.o -o mehl-server
```

# Running

After building the server, starting the server is easy as:
```
./mehl-server
```

# Connect

To connect to your own instance of mehl-server you user e.g. telnet:

```
telnet localhost 6363
```

# License

This project uses the MIT license.
