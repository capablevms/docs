# CHERI FIRST STEPS

Some easy steps to get you up and running with CHERI.

## Building CHERI and your Knowledge about it

Before you start, create the following config file in `~/.config/cheribsd.json`
(change the ports according to your needs): 

```
{
    "run-riscv64-purecap": {
        "ssh-forwarding-port": 10021
    },
    "run-morello-purecap": {
        "ssh-forwarding-port": 10085
    }
}
```

It is also advisable to create a default SSH Ed25519 key (id_ed25519) so
CheriBSD will recognise the key "out of the box" and you can use it to connect
to the VM without further steps. Then execute:

- ``git clone https://github.com/CTSRD-CHERI/cheribuild``
- ``cd cheribuild && ./cheribuild.py run-riscv64-purecap -d -f``

You will now build and run a pure-capability CheriBSD for RISC-V. Since you have
to wait, go through the [reading
list](https://github.com/capablevms/docs/blob/master/reading-list.md) to get
some knowledge about CHERI and its **capabilities**. After you have read all the
suggested documents, have a look at the
[slides](https://www.cl.cam.ac.uk/research/security/ctsrd/cheri/cheri-publications.html)
to double-check if you have got a good overview of CHERI.

You can build and run a pure-capability CheriBSD for Morello by substituting
`riscv64` with `morello`.
## Running the Examples

- ``git clone https://github.com/capablevms/cheri-examples``
- change the SSH port in the correct Makefile with your port
- put the following lines in your ``.ssh/config`` (change the ports if needed):

```
  Host cheribsd-riscv-purecap
    User root
    Port 10021
    HostName localhost
    ControlPath ~/.ssh/controlmasters/%r@%h:%p
    ControlMaster auto
    StrictHostKeyChecking no
  Host cheribsd-morello-purecap
    User root
    Port 10085
    HostName localhost
    ControlPath ~/.ssh/controlmasters/%r@%h:%p
    ControlMaster auto
    StrictHostKeyChecking no
```

To run an example simply do: ``make -f Makefile.{ARCH} run-{example-name}``
where `{ARCH}` is the architecture, e.g. riscv64, and `{example-name}` is the
name of the file without extension, e.g. make run-bounds. If everything is
correctly set up, you will see some output--in this case the program is supposed
to crash. 

You may encounter some problems connecting to CheriBSD, e.g. getting access
denied. As explained
[here](https://github.com/CTSRD-CHERI/cheribuild#disk-image), you can customize
the disk image by putting your files in ``~/cheri/extra-files``. When we ran the
building process with ``-f`` we accepted all the default options but something
could have changed from the time of writing this short document. Put your public
key (with default name) in ``~/cheri/extra-files/root/.ssh/authorized_keys``.
Then, re-build. It should now take a few minutes and you should be able to run
the examples.

## Writing simple programs

You can start writing simple programs by checking the functions in ``cheri.h``
and ``cheric.h``. Try with a simple exploration of the metadata, e.g. bounds,
tag, permissions like the following:

- tag, ``cheri_gettag(pointer)``
- perms, ``cheri_getperm(pointer)``
- type, ``cheri_gettype(pointer)``

Then, read the examples starting from ``bounds.c``, ``set_bounds.c``, and
``allocate.c``.