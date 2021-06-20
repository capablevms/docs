# CHERI FIRST STEPS

Some easy steps to get you up and running with CHERI.

## Building CHERI and your Knowledge about it

Before you start, it is advisable to create a default SSH Ed25519 key (id_ed25519). The latter should prevent any issue you may have running the examples.

- ``git clone https://github.com/CTSRD-CHERI/cheribuild``
- ``cd cheribuild && ./cheribuild.py run-riscv64-purecap -d -f``

You will now build and run a pure-capability CheriBSD for RISC-V. Since you have to wait, go through the [reading list](https://github.com/capablevms/docs/blob/master/reading-list.md) to get some knowledge about CHERI and its **capabilities**. After you have read all the suggested documents, have a look at the [slides](https://www.cl.cam.ac.uk/research/security/ctsrd/cheri/cheri-publications.html) to double-check if you have got a good overview of CHERI.

## Running the Examples

- ``git clone https://github.com/capablevms/cheri-examples``
- check on which port your Qemu VM is running (``ss -l -p | grep qemu``) and change it (if needed) in the Makefile.
- put the following lines in your ``.ssh/config``, change ``10013`` if your port is different:

```
  Host cheribsd-riscv-purecap
    User root
    Port 10013
    HostName localhost
    ControlPath ~/.ssh/controlmasters/%r@%h:%p
    ControlMaster auto
    StrictHostKeyChecking no
```

To run an example simply do: ``make run-{example-name}`` where {example-name} is the name of the file without extension, e.g. make run-hello. If everything is correctly set up, you will see some output--in this case the program is supposed to crash. 

You may encounter some problems connecting to CheriBSD, e.g. getting access denied. As explained [here](https://github.com/CTSRD-CHERI/cheribuild#disk-image), you can customize the disk image by putting your files in ``~/cheri/extra-files``. When we ran the building process with ``-f`` we accepted all the default options but something could have changed from the time of writing this short document. Put your public key (with default name) in ``~/cheri/extra-files/root/.ssh/authorized_keys``. Then, re-build. It should now take a few minutes and you should be able to run the examples.

## Writing simple programs

You can start writing simple programs by checking the functions in ``cheri.h`` and ``cheric.h``.
Try with a simple exploration of the metadata, e.g. bounds, tag, permissions like the following:

- tag, ``cheri_gettag(pointer)``
- perms, ``cheri_getperm(pointer)``
- type, ``cheri_gettype(pointer)``

Then, read the examples starting from ``bounds.c``, ``set_bounds.c``, and ``allocate.c``.