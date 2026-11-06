# O-Level Master Toolkit

A TI-Nspire CX/CX CAS application built for Ndless. The interface uses the
official SDK's native calculator dialogs; it has no external runtime resource
dependencies.

## Current features

- Native main menu, submenus, validated numerical input, and result dialogs.
- Quadratic equation roots with discriminant and formula working.
- Simultaneous linear equations, percentage, HCF/LCM, Pythagoras, and circle
	calculations.
- Denary-to-binary conversion and AND, OR, XOR, NAND, NOR, and NOT gates.
- A six-entry formula reference and a scored quadratic practice question.
- Settings/about screens.

This is an initial usable release, not the entire syllabus or a symbolic CAS.
Numerical solver answers are approximations where appropriate. The app has not
been run on physical calculator hardware.

## Build

Install the official Ndless SDK for Linux and ensure `nspire-gcc`, `nspire-ld`,
`genzehn`, and `make-prg` are on `PATH`. Then run:

```sh
make clean
make
make test
```

The build produces `dist/O-Level-Master-Toolkit.tns`. `genzehn` wraps the ARM
executable in the Ndless Zehn format, and the official `make-prg` tool adds the
Ndless loader used for calculator program documents. The `.tns` is an Ndless
program, not a TI-Nspire native document or a `.prg.tns` file.

## Install

With Ndless already installed on the TI-Nspire CX CAS, transfer
`dist/O-Level-Master-Toolkit.tns` to the calculator using TI-Nspire Computer
Link or a compatible file-transfer method. Open the transferred document from
the calculator's file browser. No additional application data files are
required. Hardware launch compatibility has not been tested here.