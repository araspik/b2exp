# b2exp
IEEE 754 base-2 exponential function.

Calculates `2^x` at exact (`1/2 ulp`) precision using a 1KB LUT table.

### Algorithm
The function first splits the input into whole and fractional parts, and for
each bit in the fractional part accumulates a product of iterative square roots.
The whole part of the input is inserted into the base-2 exponent of the result.

### Language
A (semi-)portable version of the function is written in C, and handwritten
assembly versions are written for various operating systems under various
architectures (found in `src/asm`).

### Layout
Each folder of the project contains a `about.txt` file describing the usage of
the folder and of all files and folders within it.

### Compilation
This project is setup on [Meson](https://mesonbuild.com). Once Meson is
installed, `b2exp` can be compiled like this:

```sh
mkdir -p build
meson build
ninja -C build
```
Instead of `build`, a different output folder can be used, like `output`.

Run `meson configure build` to see the Meson configuration and
`meson configure --help` to see how to change the configuration.

To install `b2exp`:

```sh
ninja -C build install
```

It may be necessary to prefix the command with `sudo`.

### Original Work
This project is based on the [LUT algorithm by Claude Baumann
(2004)] (https://www.convict.lu/Jeunes/ultimate_stuff/exp_ln_2.htm). Thanks!

### License
Copyright (C) 2019  ARaspiK

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
