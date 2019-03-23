/*

Regarding the framework components and utility programs...

This code is meant to compile and run at the command line of
an Apple Mac OS X system with the Xcode development package
loaded at installation time. It uses the GNU c++ compiler
and the programs are generic (portable) and should run with
a simple recompile on any *nix system with minimal changes.

Many of these concepts and programs were implemented first
on Borland C++ 4.1 running under the DOSBox on my MacBook Pro.

Goals:

	1. Version handling and banner generation (done)

	2. Ini file handling, with version integration (done)

	3. Daily version saving with easly saved directories (done)

	4. Automatic Makefile generation for cpp files (done)

	5. Establishment of Internet wiki location for archives (done)

	6. Porting of assembler and utils

	7. Programs which help with group editing

	8. Symbol table handler class and test program

----------------------------------------------------------------------
2011/02/22 dwg - Added symbtest.cpp program to test asymbols.hpp
Fixed bug in asymbols.hpp returning u8 values.

2011/02/15 dwg - Removed uses of DARWIN macros so things will compile
on server.goodall.com which is basically a RedHat.

2011/02/08 dwg - Major work done on makevers and makemake. Dependencies
are working perfectly now. With the caviat that any change to any
include file will trigger the rebuild of all binaries. Better to be
on the safe side though, and not miss a rebuild over a missing
dependency. The build is so fast in any case it hardly matters.
Makevers banner now reflects the current timedate group and is
consistant with all other banner syntax. This is a very good change.
The reason I have been creating object pointers and allocating the
objects with the "new" keywork at runtime was to provide more 
control over when the DTOR would run, but I have decided in some
cases, such as the CVersion class, and the CAlloc class, it isn't
necessary. Others still have advantages, but this change simplifies
many of the short and simple programs. Also a "checken and egg"
situation has developed regrding dependencies and build components,
and should the Makefile be lost at the same time as the "makemake"
utility, a new "bootmake" script will re-create the complete set
of build files, so that "make clean" and "make" will work as 
expected, as well as the individual .mak files for quick rebuilds.
When the makemake program runs, it not only creates the new Makefile
which rebuilds all .cpp files present in the directory, it writes
a program.mak file for each which can be run with "make -f pgm.mak".  
The "editall" program creates a script called "editthem" which 
invokes the vi editor for each of the cpp and hpp files present.

Regarding the configuration system, each program that instanciates
a version object, also accesses the configuration functionality.
If a configuration file does not exist, a default configuration 
file is created that looks like this...

[Options]
Banner=Full
Debug=False
Language=English
Logging=False
Monitor=False
[End]

If Options:Banner is Full, the complete banner is displayed. The
Debug, Logging, and Monitor keys can be used by any program to 
control debug code without requiring a recompile. By default,
programs pass their own name to the version CTOR, and that causes
the configuration code to access the program's own ini file.
It is also possible to have other configuration files, and other
sections other than "Options", as the inibind.hpp classes can be
used directly. Also the dwgalloc.hpp file has an extra function
that allocates a string dynamically to contain the value from
an ini file key lookup.

char * ini_read(inifilebase,section,key);

ini-read returns either a NULL if the key is not found, or a 
pointer to the result string containing the value from the ini
file. The actual configuration filename is a basename with an
extension of .ini. An example of a general purpose ini file
would be one like this...

"general.ini"
[Section1]
Key1=Value1
Key2=Value2
[Section2]
Key1=Value1
[End]

To read and use the values, code like this would be used.

if(0 == strcmp("True",ini_read("general","Section1","Key1"))) {

}


2011/02/04 dwg - Initially the source was being held on an external
drive and the code related to it as /Volumes/unixdevo/src/framewk.
Then to work portably I created a real directory in /Volumes
called unixdevo. Enhancements were made to the software while away,
but upon my return, when the external drive was thoughtlessly
plugged back in, the mounting of the real external drive blew away
the real directory, and for reasons unknown, the external drive
became unreadable as well. Good backups saved my butt and I only 
lost some last minute changes, thankfully. I created a new home for
the development in /Users/doug/Desktop/framewk. This will allow my
work to be backup up by "Time Machine", which was not happening 
previously because the external drive partition was case sensitive
and could not be backup up by Time Machine on it's drive which was
not case sensitive. Anyway, lesson learned.

2011/02/01 dwg - fixed bug in makevers that was messing up the year
in the "/Volumes/unixdevo/src/framewk/bin/copylast" script. Now
makevers also has a dynamically generated banner with the current
date.


Douglas W. Goodall aka doug@goodall.com February 2011
*/

