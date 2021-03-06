# HackVM from Nand2Tetris

### Readme:
###### You may look at the code, but you should not use it. Don’t deprive yourself of the opportunity to write the assembler yourslf as part of the nand2tetris course.

**Build Instructions and Usage**: Simply typing `make -j[N]` where `-j[N]` is the number of threads you want to build with (the more threads, the faster it compiles; the Makefile supports incremental builds) builds the core project. Once the project has been built, the executable will be placed in the `target/` directory with a name of `hackvm`. In order to run the VM simply type `./target/hackvm [filename]`. The VM will accept any path anywhere in the filesystem and will place the translated `.asm` file in the same directory location. For example, if you invoked the assembler as such: `./target/hackvm ../07/MemoryAccess/BasicTest BasicTest.vm` the resulting `.asm` file would be created as `.../07/MemoryAccess/BasicTest/BasicTest.asm`.

**Dependencies**: The project depends on a C++11 compliant compiler with a C++11 compliant STL. It uses the `std::regex` library from the STL. It also depends on the Boost.Filesystem library as well. This requires the installation of the Boost libraries. In order to link correctly with the Boost libraries, the Makefile assumes you have a $BOOST_LIBS environment variable  pointing to the root directory of the Boost library installation. For example, on my machine it’s set to `/usr/local/Cellar/boost/1.57.0`.

**Build Notes**: The project was developed on a 15” Retina Macbook Pro running Mac OSX Yosemite and compiled with Clang 3.5. The project has been test built an an Ubuntu 14.04 virtual machine running GCC 4.9 and no extra libraries (the core project builds fine without the Boost libraries). Let me know if you have any unseen difficulties building the project.
