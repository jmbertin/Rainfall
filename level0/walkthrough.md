### Download binary
``scp -P4242 level0@192.168.31.170:/home/user/level0/level0 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
Note that the program makes an atoi of argv[1]
And a condition calls a shell at level1 if the variable obtained is equal to **0x1a7 (423)**.

----

### Getting the flag

``./level0 423``

``cat /home/user/level1/.pass``
>1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
