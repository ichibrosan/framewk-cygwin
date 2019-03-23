/*
A README for the assembler.

3/12/2011 dwg - Added warnings, g_iWarningNo & asoutwrn.hpp.

3/9/2011 dwg - I made it half way throug the as8085 directory
adding comprehensive error detection to each g_szOpcode handler.
A though M are done. It took hours and I will get to the other
half when I recover :-) I also added a new string directive
that sets the high order bit on the first byte, called dstrb,
which stands for, "define string for BASIC". This is to handle
Joel's basic.asm and basic2.asm.

3/8/2011 dwg - I improved the error detection and reporting 
system today. Previously, the error that was being reported 
was an undefined g_szOpcode. But I was aware of places in the 
code where I knw other problems had been encountered, such
as no parameter supplied, or no valid register name...

3/7/2011 dwg - Added support for binary output. The new
"binary" directive causes output of <program>.bin file.
Subtle bug fixed in cpostfix.hpp, now reliable. See note
in wiki about coding standards.

3/3/2011 dwg - Some additions to the Z80 support, jp, call
got more sophisticated code handlers for all modes.
testz8jp.asm and testzcal.asm are the test programs for these.

2/27/2011 dwg - Major fixes to the equ and calc routines.
Now the test program "mixed.asm" shows things are working
very well. There was a problem that the calc directive was 
storing a 16 value with the offset of the calc, and this
would be a problem if you were doing a calc16. Now equ and 
calc both store the value but not the offset. This is as 
it should be. Careful examination of mixed.lst shows things
are very nice now. Some progress on testeval, which will 
eventually provide what we need to make expression evaluation
work.
 
2/24/2011 dwg - Added automatic inclusion of code handlers
in all the processor and directive subdirectories. The
makemake program was enhanced to support the new flow of
information required for all this to work seamlessly.
Also the postfix code from Luiz Roberto Meier was integrated
into the framework in the form of a c++ class called CPostfix
which is in a file called cpostfix.hpp. Thanks Luiz.
The makefile clean target was enhanced to remove all generated
files from all the code handler directories except the .ini
files which are often used to suppress the Banner support in
the version handler. There is one prime copy of makedeco.mk
which is copied into the handler directories and renamed
Makefile. Also there is one prime copy of the makedeco program
which is called makedeco.ccp and which is copied into the 
handler directories prior to the compilation of the decoders.
 
2/23/2011 dwg - added support for 68000, and test68k.asm
for simple g_szOpcodes. Also added storage oriented equates
to the common directives. EQU8, EQU16, EQU32 and EQU64.
These equates assure that the symb ols type is correct,
TYPE_U8,TYPE_U16,TYPE_U32 and TYPE_U64. Also added to the
8085 g_szOpcodes are Intel endian specific defines, DW, DD
and DQ. Also added are the stubs for 68000 assembly with
a few g_szOpcodes to show things are on their way to working.
In the astests directory are more test programs that show
today's progress. Specifically, the all8085 now has DD 
and DQ examples, as well as EQU8, EQU16, EQU32 and EQU64. 
The extended precision support was installed in all 
subsystems, including the symbols table at the end of the 
listing file. There is also a test68k.asm file that has
a number of 68000 g_szOpcodes.


2/22/2011 dwg - added getu8 member funtion to CSymbols
and symbtest.cpp test program which exercises u8,u16,str
Added mixed processor support, 8085 and 6502 with "proc"
directive. Implemented short short branch logic for 6502.

2/21/2011 dwg - assemble.cpp cleanup
The global variables have for the most part been renamed
with a leading g_ now and also hungarian notation where
possible. Also a new program called document.cpp causes
the documents in the doc folder to be included in the HTML
provided by gpath/hpath.

2/20/2011 dwg - Lots more enhancements...
The versbind.hpp now uses the CEnvironment class to retreive
MACHTYPE, OSTYPE, PWD and USER from the environment and adds
them to a new section in each program's ini file.
The old decode.hpp which was included in each pass, has been
changed into two new functions, decode_directives() and
decode_8085() which are now called from each pass. Also as 
an optimization, after the decode_directives() has been called
the linetype is checked before calling the processor g_szOpcodes.
If the current g_szOpcode was a directive, this saves a long linear
search in each pass.

2/19/2011 dwg - Lots of enhancements...
The makemake program now has full dependencies for the
assembler. All header files in the common and 8085 
directories are listed as dependenices in the makefile.
The versbind.hpp has been enhanced to reflect the machine
type in the full banner. The mktoday.cpp and the makevers.cpp
programs have been made multi-platform in as much as the user
pathnames are different between Mac OS X and Linux. Pathnames
are customized to the users, doug and luiz. To the best of my 
knowledge, the entire framework and assembler is now multi-
platform and can be compiled without changes on both my local
Macs, and the Scientific Linux running on server.goodall.com.


2/18/2011 dwg - add CSource class for include handler
Ten levels of include are configured in ths version
Changes to as.cpp includes.hpp common/include.hpp. The
new class is defined in srcclass.hpp.
 
2/13/2011 dwg - Fixed bug in main module where "spaces"
wasn't being initialized. "program" now being handled 
correctly in listing header.

2/12/2011 dwg - Major enhancements to 8085 code handlers
A* through MOV. Added automatic page break before symbols
in listing file. Fixed bug in pagewidth handler. Added 
pagetest.asm to asmtests.

2/10/2011 dwg - 
A code review showed there are is a lot of junk code in the code
handlers that still needs to be sorted out. Some improovements
were made today, such as the addition of the "end" directive.
It terminates the assembly  even if further text exists in the 
source file. It still needs a hook into the hex generator to
add a startupp record to the hex file with the address from the
parameter provided. That should not be difficult. All the code
handlers in the 8085 directory now have up to date log generators
and the log syntax has been cleaned up quite a bit. When an error
occurs in the assembly, the hex file is deleted, which causes 
further invocations of make to rebuilt that target. It also keeps
you from assuming the existence of the hex file means things went
well with the assembly.

2/9/2011 dwg - 
In order to make things easier for assembly develoment, a new program
called "asmall" can be run, which creates a new Makefile that can 
build all the .asm programs in the directory. It also creates a .mak
file for each program in case you want to assemble just one program
instead of them all. Syntax like... "make -f test2.mak" does the job.
Otherwise just running ./asmall will build the Makefile and run it, 
and subsequently just running "make" will update any programs needing
a reassembly.

The test programs help verify the proper operation of the assembler. 
Here are the current test programs and what they test for.

test.asm	Verifies the opertion of the "radix" directive as
		well as the "org" directive, and the ability of the
		assembler to collect labels into the symbol table.
test2.asm	Similat to test.asm.

test3.asm	Verifies the operation of the "rb" directive.

test4.asm	Verifies the ability of the assembler to create
		the classic "hello world" program suitable for
		us with CP/M-80.

test5.asm	Verifies the operation of the "mvi"  and "lxi"
		operation codes (8085), as well as the ability 
		of the assembler to deal with backward references.

test6.asm	Verifies the operation of the "in" and "out"
		operation codes, used with an 8-bit operand,
		numeric literal or symbolic. Althought the binary
		of the g_szOpcodes are not verified yet.

test7.asm	Verifies the proper functionality of the new 
		string directives, "dstr" "dstr4" and "dstrz".
		The "dstr" assembles a string into a sequence
		of ascii characters. The "dstr4" assembles
		a string into a sequence of ASCII characters
		with the high order bit of the last byte set,
		as is required when building a forth kernel.
		The "dstrz" assembles a string into a sequence
		of ASCII characters, terminated with a zero byte.

test8.asm	Verifies the use of the $ parameter which 
		evaluates to the current value of the program
		counter.
*/
 
