# Five Lessons from Simple CHERI Allocator Implementations

In an initial exploration of how memory allocation works in CHERI, we implemented a series of trivial dynamic memory allocators. This was definitely a [plan to throw one away](https://wiki.c2.com/?PlanToThrowOneAway) strategy, but we made some useful discoveries in the process. We have documented these here, hoping they might be useful for other CHERI newbies like ourselves.

## Structs are Larger in CHERI-land

If a memory cell is going to store an address (now a capability) then the cell will need to be at least 16 bytes long. This applies to C unions and structs that include pointer fields. It also applies to segregated freelists that contain embedded ```next``` pointers, so the minimum size of a cell in a freelist is 16 bytes.

## Compressed Capabilities are Complicated

Because a capability occupies 128 bits / 16 bytes (only twice the raw pointer width on 64-bit architectures), there is some compression to fit in all the base and bounds information. This means:
* some addresses need to be rounded (so the base value is capability-aligned)
* some capabilities have imprecise bounds (ideally we should overestimate bounds to avoid multiple independent capability ranges intersecting)

There are compiler intrinsics like ```cheri_representable_alignment_mask(sizet len)```  that allow us to increase the alignment of an allocation so base and bounds can be precise. This is what we used in a simple bump pointer allocator implementation at https://github.com/capablevms/cheri-examples/blob/master/example_allocators/bump_allocator/bump_alloc.c 

Observation: for memory allocations that are smaller than 4KiB, bounds are *precise* so we can have a special-case fast path that avoids alignment checks and re-calculations.


## Allocation Metadata can be Managed with Capabilities

It is feasible to use capability mechanisms to manage memory allocator metadata. For example, we can set precise bounds on side-bitmaps that we use for marking
blocks of memory. The capability bounds checking facilities give us increased confidence in the correctness of our bitmap handling code.

See how we use the ```bitmap``` data structure in https://github.com/jeremysinger/cheri-examples/blob/master/example_allocators/bitmap_allocator/bitmap_alloc.c for instance.


## Allocation Metadata can be Embedded within Capabilities

It is feasible to use CHERI metadata facilities to encode general allocator metadata. For instance, in a segregated freelist allocator, the size of an allocated cell needs to be stored as part of the cell. In a traditional implementation, this size is stored in a hidden field in the allocated cell. In a CHERI implementation, the size could be stored directly
in the capability bounds information. (This assumes that the memory allocator client will preserve the unmodified capability value to pass to the corresponding ```free``` call.

See this approach in https://github.com/jeremysinger/cheri-examples/blob/freelist_alloc_example/example_allocators/freelist_allocator/freelist_allocator.h with the ```GET_SIZE``` and ```SET_SIZE``` macros.


## Does ```malloc``` Need API Changes?

In CHERI, we can specify whether individual memory allocations should have particular properties, such as read/write/execute permissions. Could ```malloc``` calls embed the
properties the client wants, directly? I don't think this is the best idea, since it would have backwards compatibility issues. Also,
```mmap``` and ```mprotect``` manage these
permissions bits directly, and can be translated directly into CHERI semantics.

However, I notice that ```malloc``` in the [RLBox](https://arxiv.org/pdf/2003.00572.pdf) sandboxing framework does have some changes ... such as specifying in which isolated region the memory should be allocated. This is an API change that affects client code, so it needs thinking about carefully.



---
Jeremy Singer
25 March 2021