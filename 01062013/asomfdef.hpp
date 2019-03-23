// $Log: asomfdef.hpp,v $
// Revision 1.1  2011/04/14 15:13:09  doug
// Initial revision
//
//

// ---------------------------------------------------
// asomfdef.hpp  5-Apr-11   Running on Mac OS X 10.6.6
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

// unsigned char REC_TYPE
// 

typedef SegmentDefinitionRecord {
	unsigned char RecordType;
	unsigned int RecordLength;
	SegmentDefinition sd;
	CHKSUM cs;
};

typedef PublicDefinitionsRecord {


};

typedef ExternalDefinitionsRecord {
	unsigned char RecordType;
	unsigned int RecordLength;
	unsigned char IdBlk;
	unsigned char ExtIdl
	unsigned char SymInfo;
	...
	char ExternalName[];
	unsigned char ChkSum;
};

typedef struct ModuleHeaderRecord {
	

};

Typedef struct ScopeDefinition {
	unsigned char RecordType;
	unsigned int RecordLength;
	unsigned char BlkType;
	char BlockName[];
	unsigned char ChkSum;
};


typedef struct FixupRecord {
	unsigned char RecTyp;
	unsigned int RecordLength;
	struct Fixup {
		unsigned int ReferenceLocation;
        	unsigned char RefType
		Operand;
 	} fixup[];

	unsigned int ReferenceLocation;
	unsigned char RefType

};

typedef struct LibraryHeaderRecord {
	unsigned char RecType;
	unsigned int RecLength;
	unsigned int ModuleCount;
	unsigned int BlockNumber;
	unsigned int ByteNumber;
	unsigned char ChkSum;
};

typedef LibraryModuleLocationsRecord {
	unsigned char RecType;
	unsigned int RecordLength;
	unsigned int BlockNumber;
	unsigned int ByteNumber;
	unsigned char ChkSum;
};
                                    
typedef LibraryDictionaryRecord {
	unsigned char RecTyp;
	unsigned int RecordLength;
	char PublicName[];
	char ZeroByte;
	unsigned char ChkSum;
};


