// ---------------------------------------------------
// README.TXT   22-Feb-11   Running on Mac OS X 10.6.6
// S/n 2011-1042-654321  Written by Douglas W. Goodall
// Copyright(c)2011 Douglas W. Goodall, United States.
// ---------------------------------------------------
// This file is part of Vintage Modern Assembler Plus Tools.
//
// VMAPT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// VMAPT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with VMAPT.  If not, see <http://www.gnu.org/licenses/>.
//

To enter the appropriate development directory,
do "make" then ". today". 

The today script will assure there is a working 
directory for today and change to there.

If it is a new day, it will copy the source tree
from the last day work was performed.

The "scrpback" directory has backups of the critical 
startup files for using the framework. Specifically
the mktoday.cpp and Makefile.

IMPORTANT:

The auto-archiving feature implemented by the mktoday
program is a little tricky to set up. There are pathnames
in the mktoday.cpp programs that have to be right for it
to work. As presented here, it is set up to work for me
at home on my Mac, and also remotely on my Linux server.
Inside the numbered source directory is another program
called makevers.cpp which also has pathnames in it.

The basic concepts are as follows. Each time you are in
a numbered directory, and you use the Makefile to build
the distribution, a script called "copylast" is written
into the bin directory at the top of the source tree.
Then when you run the "mktoday" program, it creates a
"today" script file that creates a new numbered directory
for today, and if necessary, copies the latest previous
source code into it (based on the copylast script in bin).

The "makevers" program creates the "version.hpp" which is
included in all other programs by virtue of being part of
"includes.hpp". Once makevers has been built and run, you 
can build and run "makemake" which cleverly (IMHO) creates
a Makefile to build everything. If you are having trouble
building the distribution because of a missing "Makefile",
you can use the "./bootmake" script which should get things
going again. When you run the makemake program, it not only 
creates the main Makefile, but also .mak files for each 
program so you can compile a specific program either by
invoking make with a program name like "make dump" of with
a makefile name like "make -f dump.mak". The "makevers.mk"
and "makemake.mk" files are to be left alone and are used
by "bootmake" to initially (or as necessary) establish all 
the makefiles.

When it comes to building the test programs for the 
assembler, there is a program called "asmall" which
is copied into the astests directory during the build
and once you are in the astests directory, you can 
recreate the Makefile with "./asmall" or use the
existing Makefile by simply doing "make".

Once you get mktodayand makevers running smoothly,
you will get a new source directory every day by
simply doing a "make" at the top, then using ". today"
which leaves you in the most current working directory.

Douglas

