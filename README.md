# Custom OS Game

This project contains a WIP implementation of an OS that runs a game. The OS uses GRUB to handle the switch to protected mode and graphics mode, and the STB image library implementation to convert images to C structures. Everything else is made from scratch, including the memory and string libraries, memory (de)allocation, graphics, input handling, etc. 

## Compilation

The compilation of the OS requires an i686 cross compiler to be located in the `~/opt/cross/bin` directory, as well as support for C++ 20, and the `grub-mkrescue` command. Once all of that has been setup, run `make` in the root project directory (directory where this README is located), which will build the image conversion tool, convert images to C files, and build the iso file in the `bin` directory.