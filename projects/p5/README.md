# Userland Memory Management

## Partner rules

Solo work.

## Overview

In this project you will implement two userland memory allocation algorithms.

* First Fit

* Slab

The output of your program is deterministic and will be graded letter-for-letter by scripts to which you will have access.

This is not the most difficult of OS projects, but it IS intricate. Pay attention to the specification.

The simulated heap must be allocated by "malloc" (the real one). Yes, we could have designed a project where just the data structures were implemented with no actual memory, but this project will *read and write specific addresses* and expect correct values. Specific address will be overwritten possibly causing specific corruption in your data structures.

## Command line arguments

| option | argument | meaning | default |
| ------ | -------- | ------- | ------- |
| z | number | Specifies the size in KB of all user allocatable Heap space.</br>Minimum is 64 | 64 |
| s | number | Specifies the size in bytes of a slab unit.</br>Maximum is 256 | 256 | 
| c | number | Specifies the number of slabs to be allocated at a time.</br>Maximum is 16 | 8 |

## Critical - addresses are printed and entered as offsets

To make the results more understandable you must remember the address returned to you by ```malloc()``` (the real one) when your initial simulated heap is allocated. Thereafter, every address must be *printed* as offsets from this value. You are likely to keep addresses as 64 bit addresses as normal - but printing them (and entering them) is zero-based.

Make macros or functions to do this for you.

A ```nullptr``` must be special cased to print ```nullptr```.

## void * and casting

You may find yourself using ```void *```. This is a pointer to anything. That's the good news. The bad news is that you cannot do address arithmetic with these because a void has no defined size. 

Expect to do **massive** amounts of casting in this project, likely more than you have ever done before in a single program.

## Slab allocator

The slab allocator's memory is taken from the heap like any other "malloc". When a "slaballoc" command is executed, if no slabs are currently available, a number of new slabs must be allocated via your "malloc". In a real slab allocator, many slabs would be allocated in a single ```malloc()```. For reasons of simplification, you should repeatedly call your "malloc" to allocate slabs.

Once a number of slabs are allocated, they are doled out by the slab allocator in response to "slaballoc" commands. 

Assuming the default options, after initializing your heap, eight 256 slabs are available to be allocated via "slaballoc" commands.

Any data structures used to keep track of slabs are NOT included in the simulated heap. That is, you may use STL containers for example.

Slabs can be freed in one of two ways.

* They can be reclaimed by the slab allocator using "slabfree".

* They can be freed using the standard "free" command.

## The free list

Is to be implemented as it would be for reelz, in "free memory."

```c++
struct FreeListNode {
    uint32_t MAGIC_1;
    uint32_t size;
    FreeListNode * next;
    uint32_t MAGIC_2;
};
```

You must use this struct for your program to function correctly.

## The "malloc" header

```c++
struct MallocHeader {
	uint32_t MAGIC_1;
	uint32_t size;
	uint32_t MAGIC_2;
};
```

You must use this struct for your program to function correctly.

Notice it is 12 bytes long.

## Commands

All addresses are in hex for both input and output. *All sizes are in decimal*.

| command | argument | argument | meaning | 
| ------- | ---------- | ---------- | ------- | 
| # | | | Ignore the line - treat as comment |
| slaballoc | | | attempts to allocate one slab |
| slabfree | address | | returns the slab to the available slab list - it is an error if the address does not correspond to an allocated slab |
| malloc | size | | attempts to allocate count bytes (given in DECIMAL) - if needed count should be rounded up to the next 32 byte boundary | 
| free | address | | attempts to return the indicated memory to the free list - if the address matches an unallocated slab, remove it from the list of free slabs before freeing it |
| freelist | | | prints the free list (both heap and slabs) | |
| probe | address | | tells whether the indicated address is free or allocated | print FREE or ALLOCATED |
| read | address | | returns the uint32_t at the indicated address | A 32 bit hex number or ERROR |
| write | address | value | writes the uint32_t (in hex) at the specified address | See output |
| quit | | | terminates the program - the program should also terminate on end-of-file on ```stdin``` |

### freelist

All addresses are printed in hex.

The status of the slab free list is printed first. If the slab free list is currently empty, print "Empty".
No more than 8 addresses are printed per line. Addresses on the same line are comma separated except for the last address.
After each address print either '+' or '-' signifying if the MallocHeader magic numbers are intact.

The main free list prints 4 items per free node with a maximum of 2 nodes per line. If there are two nodes on a line, then first node ends in a comma.

The items to be printed per node have the following format. Parenthesis and spacing are required.

```address (size)(next)S```

Where:

| field | meaning |
| ----- | ------- |
| address | the hex address of the node |
| size | the decimal size of the node |
| next | the hex address of the next node |
| S | if the magic numbers check out, print '+' </br> otherwise print '-' and enjoy |

Remember that address are zero-based.

Here is a sample of a freshly initialized default-setting heap as printed by "freelist":

```
Free slabs:
0x0000000c+, 0x0000012c+, 0x0000024c+, 0x0000036c+, 0x0000048c+, 0x000005ac+, 0x000006cc+, 0x000007ec+
Free memory:
0x00000900 (63232)(nullptr)+
There are: 1 free blocks.
Largest free block: 63232
Smallest free block: 63232
```

How to read this:

* that there are 8 (the default number) of slabs already **ready** to be allocated starting at address 0xC.

* 0xC is 12. This is the size of the ```MallocHeader```. Technically, the memory belonging to a slab begins ```sizeof(MallocHeader)``` bytes before the address reported to you (just like all results from your "malloc").

* the ready slabs are each 256 bytes in length - but you see their addresses incrementing by 0x120 (0x120 is 288). Adding 256 bytes for the slab, 12 bytes for the MallocHeader you get 268. Then, 268 is rounded upward to the next multiple of 32 - or 288.

* that there are 2304 bytes (8 * 288) missing from the heap. You can tell this because at this point the first free area has an 0x900 byte offset (0x900 is 2304).

The remainder of the output is self-explanatory.

### probe

With a reasonable amount of specificity, the "probe" command will print what kind of space the provided address is. The address is specified in hex, which you'll need to convert back to decimal. Google this - the method is obvious once you see it. It is OK to iterpret non-hex as zero - don't make this an error.

This is a tedious command to implement.

| message | meaning |
| ------- | ------- |
| Error: missing address | There was no address argument |
| Error: address outside heap | Self-explanatory |
| Address: 0xSOMEADDR is located | This is the **prefix** to the remaining possibilities |
| ... in a free slab | The address is found in a defined slab that is on the slab free list |
| ... in an allocated slab | The address is found in a slab that has been doled out by a previous "slaballoc" |
| ... in a free block | The address is part of a part of the "heap" which is unallocated |
| ... in an allocated non-slab block | The address didn't trigger any of the above so it must be allocated heap-space |

Remember that the address specified is zero-based.

### read

The "read" command prints the ```uint32_t``` found at the specified address (specified in hex) or an error message if the address is too large.

Assuming a fresh default initialization here are results from several "read" commands:

```
read,0
Address: 0x00000000 contains (uint32_t): 0xccc0
read,4
Address: 0x00000004 contains (uint32_t): 0x120
read,8
Address: 0x00000008 contains (uint32_t): 0xccc0
read,FFFFFFFFFF
Error: address outside heap
```

The uint32_t at address 0 contains the magic number because it is the first magic number in the ```MallocHeader``` in front of the first slab.

The uint32_t at address 4 contains 0x120 because it is the first magic number in the ```MallocHeader``` in front of the first slab.

The uint32_t at address 8 contains the magic number because it is the second magic number in the ```FreeListNode``` in front of the first slab.

The uint32_t at address 0xFFFFFFFFFF cannot be accessed because it is beyond the simulated heap.

Remember that the address specified is zero-based.

Use this for testing purposes.

### write

The "write" command sets the ```uint32_t``` at the address (specified in hex and zero-based) to the given value (specified in hex).

Here is a sample output of operation without errors:

```
slaballoc
Allocated a slab at: 0x0000070c
read,720
Address: 0x00000720 contains (uint32_t): 0x0
write,720,ff
Address: 0x00000720 set to (uint32_t): 0xff
read,720
Address: 0x00000720 contains (uint32_t): 0xff
```

Here are some errors you should handle - this assumes a freshly initialized 64K system:

```
write
Error: missing address
write,100
Error: missing value
write,fffffff,0
Error: address outside heap
```

Use this command for testing. For example, you can overwrite a MallocHeader to see if your free code handles it properly.

### slaballoc

This command allocates a slab from the slab allocator. The slab allocator maintains what *could* be a stack of free slabs. Thereafter, "slaballoc" removes one slab each time it is called. If you run out of slabs, you should allocate (using "malloc") another set of slabs.

It is required that you "malloc" the number of free slabs in one go. Suppose there are 8 slabs being allocated at once - a major point of the slab allocator is that all of these are "malloced" together (in one "malloc"). If each slab was defined as 256 bytes, then 8 * (256 + 12) bytes would be asked of your "malloc". Notice that each of the 8 get a ```MallocHeader``` so they can be passed to "free" or to "slabfree".

If passed to "free", they are freed like any other memory you have allocated.

If passed to "slabfree", they are added back to the data structure used to keep track of free slabs.

In this sample, you see that 8 slabs are available. One is allocated. You can see that it came from the back of the free slab list.

You are reminded that the data structures you use to *keep track* of slabs is NOT included in the simulated heap. You may construct any data structures you see fit to manage the slab allocator provided that slab blocks are indeed allocated from the simulated heap.

```
freelist
Free slabs:
0x0000000c+, 0x0000012c+, 0x0000024c+, 0x0000036c+, 0x0000048c+, 0x000005ac+, 0x000006cc+, 0x000007ec+
Free memory:
0x00000900 (63232)(nullptr)+
There are: 1 free blocks.
Largest free block: 63232
Smallest free block: 63232
slaballoc
Allocated a slab at: 0x000007ec
freelist
Free slabs:
0x0000000c+, 0x0000012c+, 0x0000024c+, 0x0000036c+, 0x0000048c+, 0x000005ac+, 0x000006cc+
Free memory:
0x00000900 (63232)(nullptr)+
There are: 1 free blocks.
Largest free block: 63232
Smallest free block: 63232
```

Here is a sample of using up the available slabs requiring another slab block to be allocated.

```
slaballoc
Allocated a slab at: 0x000007ec
slaballoc
Allocated a slab at: 0x000006cc
slaballoc
Allocated a slab at: 0x000005ac
slaballoc
Allocated a slab at: 0x0000048c
slaballoc
Allocated a slab at: 0x0000036c
slaballoc
Allocated a slab at: 0x0000024c
slaballoc
Allocated a slab at: 0x0000012c
slaballoc
Allocated a slab at: 0x0000000c
slaballoc
Malloc dividing: 63232 at: 0x00000900 into: 288 and: 62944
Malloc returning: 0x0000090c
Malloc dividing: 62944 at: 0x00000a20 into: 288 and: 62656
Malloc returning: 0x00000a2c
Malloc dividing: 62656 at: 0x00000b40 into: 288 and: 62368
Malloc returning: 0x00000b4c
Malloc dividing: 62368 at: 0x00000c60 into: 288 and: 62080
Malloc returning: 0x00000c6c
Malloc dividing: 62080 at: 0x00000d80 into: 288 and: 61792
Malloc returning: 0x00000d8c
Malloc dividing: 61792 at: 0x00000ea0 into: 288 and: 61504
Malloc returning: 0x00000eac
Malloc dividing: 61504 at: 0x00000fc0 into: 288 and: 61216
Malloc returning: 0x00000fcc
Malloc dividing: 61216 at: 0x000010e0 into: 288 and: 60928
Malloc returning: 0x000010ec
Allocated a slab at: 0x000010ec
```

Notice the output from "malloc" showing that the memory for the next slab block was indeed allocated off the simulated heap.

### slabfree

"slabfree" attempts to return the slab at the indicated address (given in hex). It is an error if the address is not an allocated slab.

In the sample below, the different output from "slabfree" is shown including three error states.

```
slaballoc
Allocated a slab at: 0x000007ec
slabfree
Error: missing address
slabfree,ffffffff
Error: address outside heap
slabfree,7ec
Reclaimed slab at: 0x000007ec
```

Note the reference implementation assumes stack-like behavior managing free slabs. That is, last-in-first-out ordering.

If a slab address is provided to "free" rather than "slabfree" it is not recycled but instead is actually freed.

Note: you CAN free an unallocated slab since it has a valid MallocHeader. Check all addresses to be freed against the unallocated slabs first and remove any matches as demonstrated below:

```
freelist
Free slabs:
0x0000000c+, 0x0000012c+, 0x0000024c+, 0x0000036c+, 0x0000048c+, 0x000005ac+, 0x000006cc+, 0x000007ec+
Free memory:
0x00000900 (63232)(nullptr)+
There are: 1 free blocks.
Largest free block: 63232
Smallest free block: 63232
free,c     
Free delinked unallocated slab
Free replace head_ptr with: 0x00000000 with size: 288
```

If what otherwise appears to be a valid slab has a bad MallocHeader, print an error and leave it alone. Example:

```text
slaballoc
Allocated a slab at: 0x000007ec
write,7e8,ff
Address: 0x000007e8 set to (uint32_t): 0xff
slabfree,7ec
Error: memory at 0x000007ec is corrupt or not a MallocHeader
write,7e8,ccc0
Address: 0x000007e8 set to (uint32_t): 0xccc0
slabfree,7ec
Reclaimed slab at: 0x000007ec
```


### malloc

"malloc" attempts to allocate the indicated number of bytes (given in DECIMAL) using First Fit.

Here is an example of the output of a successful "malloc" called internally during initializtion of the heap - specifically, in preallocating the initial free slabs:

```
Mode: ff
Heap (KB): 64
Slab Size (B): 256
Slabs Alloced At One Time: 8
Heap initialized with: 65536 bytes
Malloc dividing: 65536 at: 0x00000000 into: 288 and: 65248
Malloc returning: 0x0000000c
Malloc dividing: 65248 at: 0x00000120 into: 288 and: 64960
Malloc returning: 0x0000012c
Malloc dividing: 64960 at: 0x00000240 into: 288 and: 64672
Malloc returning: 0x0000024c
Malloc dividing: 64672 at: 0x00000360 into: 288 and: 64384
Malloc returning: 0x0000036c
Malloc dividing: 64384 at: 0x00000480 into: 288 and: 64096
Malloc returning: 0x0000048c
Malloc dividing: 64096 at: 0x000005a0 into: 288 and: 63808
Malloc returning: 0x000005ac
Malloc dividing: 63808 at: 0x000006c0 into: 288 and: 63520
Malloc returning: 0x000006cc
Malloc dividing: 63520 at: 0x000007e0 into: 288 and: 63232
Malloc returning: 0x000007ec
Free slabs:
0x0000000c+, 0x0000012c+, 0x0000024c+, 0x0000036c+, 0x0000048c+, 0x000005ac+, 0x000006cc+, 0x000007ec+
Free memory:
0x00000900 (63232)(nullptr)+
There are: 1 free blocks.
Largest free block: 63232
Smallest free block: 63232
```

Remember that a real slab allocator use one call to ```malloc()``` rather than one for each slab. This project deviates from reality for simplicity.

### free

"free" attempts to free the block at the specified address. The address is checked to ensure that a ```MallocHeader``` comes immediately before it. The address is also checked against your list of free slabs. If you attempt to "free" a free slab, go ahead but remember to also remove it from your free slab data structure.

Here is sample output from various scenarios:

```
free
Error: missing address
free,ffffffff
Error: address outside heap
free,17
Error: memory at 0x00000017 is corrupt or not a MallocHeader
free,12c
Free delinked unallocated slab
Free replace head_ptr with: 0x00000120 with size: 288
malloc,600
Malloc dividing: 63232 at: 0x00000900 into: 640 and: 62592
Malloc returning: 0x0000090c
free,90c
Free added: 0x00000900 size: 640 to free list.
Coallescing: 0x00000900 size: 640 into: 0x00000b80 size: 62592 making size: 63232
```

Your implementation of "free" must do appropriate coallescing as indicated above.


### quit

Exits the program. End-of-file on ```stdin``` also ends the program.

## Magic number

![Say the secret word](./ybyl.jpg)

The magic number is of type uint32_t and has a value of ```0xCCC0```.

## ```cout``` and ```cerr```

Send all output to cout - none to cerr.

