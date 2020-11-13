# Recommended CHERI Reading list from the point of the CapableVMs team

Now first before you start reading first clone this repo: https://github.com/CTSRD-CHERI/cheribuild. 
And run `./cheribuild.py run-riscv64-purecap -d -f`, you probably would have finished reading before 
it has finished building.

This first most important thing that is needed would ideally be the CHERI ISA spec from Cambridge.
Even when working on Morello it explains the motivation behind all the work: [link](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-951.pdf).
I would recommend starting with the Design Goals [p. 19] then reading through the chapter on 
the CHERI Protection Model [p. 41] until the end of Architectural Capabilities [p. 59]. Most of the other stuff can be read later. 

The next thing to go through is: [link](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-947.pdf).
It's main purpose is to explain how CHERI capabilities can be used in C/C++, but all the examples
are very basic. This document describes the functions defined in the llvm header files ([link](https://github.com/CTSRD-CHERI/llvm-project/blob/master/clang/lib/Headers/cheriintrin.h)) but it is also recommended to check the ones described in the cheribsd repo ([link](https://github.com/CTSRD-CHERI/llvm-project/blob/master/clang/lib/Headers/cheriintrin.h)).

The last thing would be then to go back to the ISA specification for the arch you will target
([Morello](https://documentation-service.arm.com/static/5f8da6fef86e16515cdb861e) [Cheri](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-951.pdf))
and see which instruction are not represented by the intrinsics in the header files. 

If you are interested about the different trains of thought throughout the 10 year life of the project
I would recommend reading this in that order:
 - [The first 5 years of the project](http://www.csl.sri.com/users/neumann/20140925-ctsrd-pimeeting.pdf)
 - [Efficient Tagged Memory](https://www.cl.cam.ac.uk/research/security/ctsrd/pdfs/201711-iccd2017-efficient-tags.pdf) The citations here are particularly interesting to trace the origins of tagged memory as a whole.
 - Go thought the `Version History` section in each of the CHERI ISA spec document versions, all of them can be found here: [techreports](https://www.cl.cam.ac.uk/techreports). There can also be found the [Introduction To CHERI](https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-941.pdf) which isn't a very good place to start.
