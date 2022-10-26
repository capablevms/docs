# Recommended CHERI Reading list from the point of the CapableVMs team

Now before you start reading first clone this repo: https://github.com/CTSRD-CHERI/cheribuild and
run `./cheribuild.py run-riscv64-purecap -d -f`, you probably would have finished reading before it
has finished building.

This most important thing that is needed would ideally be the [CHERI Instruction-Set Architecture]
spec from Cambridge. Even when working on Morello it explains the motivation behind all the work. I
would recommend starting with the Design Goals [p. 19] then reading through the chapter on the CHERI
Protection Model [p. 41] until the end of Architectural Capabilities [p. 59]. Most of the other
stuff can be read later.

The next thing to go through is the [CHERI C/C++ Programming Guide]. Its main purpose is to explain
how CHERI capabilities can be used in C/C++, but all the examples are very basic. This document
describes the functions defined in the [llvm header files] but it is also recommended to check the
ones described in the [CheriBSD repo].

The last thing would be to go back to the ISA specification for the arch you will target ([Morello],
[CHERI Instruction-Set Architecture]) and see which instructions are not represented by the
intrinsics in the header files.

If you are interested in the evolution of the project over the last 10 years, I would recommend
reading these in order:
 - [The first 5 years of the project]
 - [Efficient Tagged Memory]: The citations here are particularly interesting to trace the origins
   of tagged memory as a whole.
 - Go through the `Version History` section in each of the CHERI ISA spec document versions, all of
   which can be found here: [techreports]. There you can also find the [Introduction To CHERI]
   (which isn't a very good place to start).

[CHERI Instruction-Set Architecture]: https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-951.pdf
[CHERI C/C++ Programming Guide]: https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-947.pdf
[llvm header files]: https://github.com/CTSRD-CHERI/llvm-project/blob/master/clang/lib/Headers/cheriintrin.h
[CheriBSD repo]: https://github.com/CTSRD-CHERI/cheribsd
[Morello]: https://developer.arm.com/documentation/ddi0606/ak/?lang=en
[The first 5 years of the project]: http://www.csl.sri.com/users/neumann/20140925-ctsrd-pimeeting.pdf
[Introduction To CHERI]: https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-941.pdf
[Efficient Tagged Memory]: https://www.cl.cam.ac.uk/research/security/ctsrd/pdfs/201711-iccd2017-efficient-tags.pdf
[techreports]: https://www.cl.cam.ac.uk/techreports
