# as<proc>/Makefile

decoincl.hpp:	makedeco
	./makedeco
	cp decoincl.hpp  decoincl.sav

makedeco:	makedeco.cpp
	g++ -I .. -w makedeco.cpp -o makedeco

makedeco.cpp:	../makedeco.ccp
	cp ../makedeco.ccp makedeco.cpp

