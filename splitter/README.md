The Splitter Project
====================

1. How it come to be.
2. What is it's purpose.
3. Components
 - Extracting LLVM Bitcode.
 - Splitting the bitcode files.
 - Using a gadget analyzer.
 - Joining safe bitcode files.
4. Future


## How did the splitter come into existence.

The main reason behind the creation of the splitter was the 
realization that the $PCC on CHERI is no longer just a 
simple address, but it is a memory range with its own set
of permissions. I initially wanted to exploit this effect 
to gain security in the case of object oriented systems,
but the process was cumbersome, and it would require 
creating instructions during the program runtime. Then it 
was found that dynamic libraries `.so` have an interesting 
property. Each library has different memory range and 
therefore its own capability. This means that when calling 
functions from other libraries they will switch the $PCC 
which is also used to load static data and a local .got.
This means that if each function of a program is in it's
own shared library its data wont be accessible. Also this
means that if an attacker theoretically gains access to 
that bit of the program he will be able to jump only to
the places that this function would need. The last bit of
the puzzle is the fact that all of the values in the .got
are sentries (sealed entries) that make the pointers opaque
to everything other then jumping to them.

## What is the purpose of the splitter.

To increase security of course. The one thing it protects
against is control flow attacks. With the one that we 
initially focused on being ROP like attacks. Because 
control flow attacks are what we protect against there
needs to be a system that can check if the improvements
made by the splitter are actually tangible. To do that
VIXL can be used to disassemble the code and do simple 
analysis on the control flow to detect dangerous functions
and patters. That would allow both for detecting which 
functions can be joined back together, as well as saying
how many dangerous functions were encapsulated and can are
less dangerous.

## The main components of the system. 

### Generating bitcode files that can be split.

To do that [wllvm]() is used. It allows a project that 
generates a single statically linked binary to extract the
bitcode used to build it when it was compiled with clang.
This was used for cPython and mir(ruby). However the build 
system and its flags may still need to be adjusted and the 
correct combination of flags found. For example to build 
cPython I had to use this:
`LLVM_COMPILER="clang" CC="wllvm" ./configure --with-lto --with-hash-algorithm=fnv`
##also a debug build fails to split properly. 

### Splitting the produced bitcode file.

The program to do that can be found [here](https://github.com/capablevms/llvm-function-split).
This program splits the resulting bitcode file from the 
previous stage into a collection of smaller bitcode files
that can then be build into shared objects and linked
with the main function. 

### Analyzing the functions.

The last stage is the analyze the result. To do that a 
disassembler is needed, VIXL is used at the moment but
this should be changeable. Firstly a simple version will
be needed to detect what functions contain dangerous 
instructions. Then a more complicated version will be
needed that will detect the dangerous instructions but will
also be able to differentiate between the ones that load 
things from the $PCC and ones that load values from the 
heap for example. 

### Join back the functions.

This is very simple and can be done with llvm-link. If the
split version is already working, joining would just 
increase the performance. Only the safe functions can be 
combined and their bitcode files will need to be compiled
and linked with main.

## Future

The main thing this tool allows us to test, is how much 
security can one get from putting every function into its 
own capability that perfectly wraps it. This can be used 
to showcase how such feature will impact JITs, and how it
will play with `C` integration. There also is an 
interesting opportunity to combine this with stack
protection. That would allow for the perfect control flow
integrity preservation. 

