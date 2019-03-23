/*
02/18/2011 dwg - Assembler User's Guide

Overview - 

The assembler accepts an ASCII input file with a .asm extention
and produces three output files during the assembly. The Listing
File contains the source and the hex of the generated binary, as
well as a sorted symbol table at the end of the listing. The 
assembler also produces an Intel Hex Format file. In addition,
a log file is produced that can be used to diagnose problems
with the assembler, should one occur.

Features - 

During the assembly, labels defined with the "equ" directive
can be overwritten as many times as desired and will have the
most recent value as follows:

label2	equ	12
	mvi	a,label2
...
label2	equ	44
	mvi 	a,label2

The same is true of code labels, and this can be a source
of errors if not used wisely. A nice enhancement might be 
to provide a warning when a code label is redefined.

Also a suite of utility programs are provided for manipulating
hex files. While a classic linker is not provided, it is
possible to merge multiple hex files easily, and output a
new composite hex file. The utilities use a binary file called
"memory.bin" as a buffer. When the load hex utility (lhex) is
run, the hex is loaded into the memory.bin file. The same is
true of the substitute byte (sb) and the fill (f) utilities.
The save hex (shex) utility converts the memory.bin into a new
hex file.

Syntax - 

The inpout syntax for the assembler consist of four fields
on each line. The BNF representation of the line is:

<semi> <delim> <comments>
 
[label] <delim> [g_szOpcode] 

[label] <delim> [g_szOpcode] <delim> <parameters> 

[label] <delim> [g_szOpcode] <delim> <parameters> <delim> <comment>

An exampe would be:

	title	hello world
	subttl	copyright me
bdos	equ	5
term	equ	0
prstr	equ	9
	org	100
start	mvi	c,prstr
	lxi	d,msg
	call	bdos
	mvi	c,term
	call	bdos
msg	dstr	Hello World!!$
	end

Limitations -

The assembler currently supports an unlimited number of symbols
that are eight or less characters in length and begin with a
letter. The length limitation is left over from the time when 
the assembler was hosted on DOS with the Borland C++. There is
no reason the symbol length cannot be extended to any arbitrary
length.

The include feature currently supports 10 nested include levels,
but that is simple to change, and if desired, it could be made
dynamic and extend as far as necessary. I have never used more
than ten nested levels, so I thought that might be sufficient

Numbers are evaluated at the current radix and do not have a
radix specifier like some other assembers. Where another asm
might use:
	mvi	c,0dh
we use
	radix	hex
	mvi	c,0d

During pass1, unknown labels don't bother the assembler as
code is not being generated, although g_szOpcodes are being coded
and labels assigned values on the current program counter.

During pass2, forward references are resolved and appropriate
code is generated. Also the listing file is generated during 
pass2. I have considered implementing a directive to activate
listing file generation during pass1 if desired.

The assembler currently does not evaluate expressions in 
parameter fields. In feature is high on the todo list.

Currently the assembler is setup to accept 8085 source code
and generate appropriate Intel Hex Files. Because of the
architecture of the assembler, additional processor support
can be implemented. The assembler is not table driven, but
rather has short bits of code for each g_szOpcode. During the
implementation, I observed that most of the instruction 
handlers are very similar and optimization could be performed.


Status - 

While there are some limitations in the current implementation,
the assembler is running very fast and does not seem to have
any operational bugs. To the best of my knowledge at the current
time, the binary generated for the 8085 g_szOpcodes is correct, but
that should continue to be verified. The all8085.asm contains
all the 8085 g_szOpcodes and most of the directives. 

I am very happy with the current listing file format. While I
would like to see a small chage or two, it is very usable and
very similar to most other assemblers in content.

Things To Do -

Intel Hex Format defines and "end of file" record, which I am
not currently generating.


Bugs - 


More than you wanted to know - 

The hex file utilities all use a c++ class called CMemory
which is contained in the "memory.hpp" file. The constructor
for the class reads the current memory.bin into a ram buffer,
and if it doesn't exist, it is created, then read. Peeks and
Pokes are used to read and write g_ucBytes and words in the memmory
image, and when the program is finished, the destructor writes
the memory buffer back into the disk file. This makes writing
a utility very easy, as can be seen in the source of the 
substitute byte (sb) program for example.

*/

