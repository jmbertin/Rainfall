### Download binary
``scp -P4242 bonus3@192.168.31.170:/home/user/bonus3/bonus3 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

In the main function we see that the binary open the file that contain our flag, unfortunately if we try to inspect it in memory using gdb, the open fails. So we can't just open the value in memory, to see the pass.
To get our flag we only need to pass a strcmp() between our input (argv[1])and the flag. We don't know the pass, but we see ``local_98[index] = 0``. That means put a '\0' at the index, and the index is just an atoi(argv[1]).
If we send a empty string to atoi, it will send back 0. So if our input is empty this will allways pass (the pass will be only '\0' so that our argv).

----

### Building the payload

We just have to write ``./bonus3 ""``

----

#### Getting the flag

``bonus3@RainFall:~$ ./bonus3 ""``
>$

``cat /home/user/end/.pass``
>3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
