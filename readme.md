This is the README file for Jual

### What is Jual?

Jual is an embeddable Virtual Machine (VM) that implements the JualScript language.  JualScript is a small programming language that is a subset of ECMA Script (or JavaScript).

The implementation is derived from Lua 5.3.  The source code is a drop-in replacement for Lua, with most of the changes in the lexer and parser components. An initialization script provides some key functions, while the rest of the API is the same as Lua.

A summary of the key language features and the base library functions is listed in the file jual_reference.txt.

More information can be found on the project website http://sajonoso.github.io/jual


### Building
The interpreter and compiler can be built by simply running your compiler on the amalgamated source code files that start with a number followed by an underscore. i.e.
```
  gcc -o jualc.exe 2_jualc.c
  gcc -o jual.exe 3_jual.c
```
Alternatively, run make with the included Makefile.

Note: The file jual_init.h containing the compiled initialization script was generated under a 32 bit environment.
To compile the program under a 64-bit environment will require the original source file.  Please contact the author through GitHub to obtain this source file.

### Running the test scripts
The test scripts are designed to compare the output of the Jual VM with another JavaScript engine to verify its correctness.  The Windows Scripting Host is the obvious choice in a Windows machine.

Run the batch file: *runtests_wsh.cmd* to execute the test suite.

Under Linux the Jual VM is compared with the NodeJS runtime.

### Try it for yourself
The included Windows 32-bit binaries are compiled using MingW (gcc version 4.8.1).  Simply download these from the bin folder and run. 
There are also binaries for Linux compiled under 32-bit RHEL 6.6

### Licensing
The software is licensed under the 3-clause BSD License.  Please see the file called LICENSE.txt

### Acknowledgements
The following software has been used in this project

[Lua](http://www.lua.org/)

[SQLite](http://sqlite.org/)
