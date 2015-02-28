# HackVM Project 7 Readme

1. Eric Dattore
2. No one else assisted me with this assignment
3. Probably 5-6 hours
4. The Makefile has a few different targets. Simply typing `make -j[N]` where `-j[N]` is the number of threads
    you want to build with (the more threads, the faster it compiles; the Makefile supports incremental builds)
    builds the core project. The core project
    only relies on a C++11 compliant compiler with the latest STL (support `std::regex`). Once the project has been
    built, the executable will be placed in the `target/` directory with a name of `hackasm`. In order to run the
    assembler simply type `./target/hackvm [filename]`. The VM will accept any path anywhere in the
    filesystem and will place the translated `.asm` file in the same directory location. For example, if you
    invoked the assembler as such: `./target/hackvm ../07/MemoryAccess/BasicTest/BasicTest.vm` the resulting `.asm` file would be
    created in `.../07/MemoryAccess/BasicTest/BasicTest.asm`.

    The other targets pertain to testing and experimental code. The assembler comes with a battery of unit tests
    written with the helpt of the Boost Unit Test Framework. These, while not necessary to build, are built with
    the `tester` target. When compiling the tests, an environment variable `$BOOST_LIBS` is required to be set
    and point to the root directory where the Boost libraries are installed. The `experimental` target
    doesn't require anything other than a standard C++11 compliant compiler.

    The project was developed on a 15" Retina Macbook Pro running Mac OSX Yosemite and compiled with Clang 3.5.
    The project has been test built an an Ubuntu 14.04 virtual machine running GCC 4.9 and no extra libraries
    (the core project builds fine without the Boost libraries). Let me know if you have any unseen difficulties
    building the project.
