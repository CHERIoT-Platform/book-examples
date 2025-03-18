CHERIoT Programmers' Guide Examples
===================================

This repository contains all of the examples that accompany the [CHERIoT Programmers' Guide](https://cheriot.org/book).

This includes a dev container configuration and so should provide an out-of-the-box experience in VS Code with the dev containers extension installed.
If you are not using VS Code, you will need to follow the Getting Started instructions in the book or the CHERIoT RTOS repository to ensure that you have a toolchain.
Make sure that you do a *recursive* clone of this repository.
If you didn't, you can fix the missing submodules with:

```console
$ git submodule update --init --recursive 
```

On startup, the dev container will run the [`./scripts/generate_compile_commands.sh`](scripts/generate_compile_commands.sh) script to ensure that syntax highlighting can work with the CHERIoT build of `clangd` (provided in the dev container).

The main branch of this repository tracks changes to CHERIoT RTOS and ongoing work on the online version of the book.

The first-edition tag is the version that accompanies the first edition.
The examples in the first edition of the book will exactly match this version.

The first-edition-updates branch is a periodically updated version that will bring in newer versions of the RTOS and address any incompatibilities.
Changes here (other than bumping RTOS and dev container versions) will be listed in the first-edition errata section of the book.
