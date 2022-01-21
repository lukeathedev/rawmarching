# Rawmarching

Rawmarching is my submission to [fullsail.edu](https://www.fullsail.edu/)'s scholarship program. Created in 3 days, it showcases (slightly rushed) code that sets up an x86-compatible computer from scratch, all the way to rendering a raymarching demo with VGA technology in 32-bit protected mode.

## Getting Started

### Recommended approach

Instead of setting up the build system manually, a [live web version](https://localhost) is available. Alongside a live emulator, it contains insights and explanations of the code that is hosted in this repository.

### Hard mode

It is advisable to obtain a [cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler) that targets i386-elf. The makefile must be edited to reflect the installed toolchain and emulator. If an emulator other than [QEMU](https://www.qemu.org/) is used, then some makefile rules will need to be altered.

> In the makefile:
> ```Makefile
> QEMU = <your-emulator-here>
> CC = <your-compiler-here>
> ...
> ```

In order to compile all the binaries and run the "operating system", type the following in a *nix compatible shell:

> In a *nix shell:
> ```shell
> make clean # just to be safe
> make run
> ```

## Inspiration

Switching from real to protected mode in x86 platforms can be quite the undertaking, and I wouldn't be able to do it alone. A massive thank you goes out to the following forums/institutions/websites/persons:

 - [OSDev Wiki](https://wiki.osdev.org/Main_Page) - for just about anything you might need regarding OS development
 - [os-dev PDF by Nick Blundell](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) - a great introduction to low-level development for dummies
 - [Ray Marching for Dummies!](https://www.youtube.com/watch?v=PGtv-dBi2wE) - an approachable introductory video to raymarching by Martijn Steinrucken

There are also other mentions scattered throughout the code, mostly of resources that helped me implement certain algorithms and functions. For a more thorough list of credits, refer to [the live demo website](http://localhost).

## What's missing

The tight deadline means that many wanted features were shunned. Of those, the most notable are:

 - 64-bit compatibility
 - Interrupt handling
 - LAPIC Support
 - Robust standard library
 - Robust error handling
 - Unit testing
 - Multithreading
