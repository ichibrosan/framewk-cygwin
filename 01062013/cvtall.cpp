// $Log$
//

// ---------------------------------------------------
// cvtall.cpp   17-Apr-11   Running on Mac OS X 10.6.6
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
//#define __TRACE

static char szCvtallCpp[] = "$Id$";


#include "asdefs.hpp"
#define DWGALLOC
#define INIBIND
#define DIRCLASS
#include "includes.hpp"
#include <assert.h>
#include <sys/types.h>
#include <sys/dir.h>

#include <errno.h>
#include <unistd.h>

//#define SHOW_NAMLEN
//#define SHOW_TYPE
//#define SHOW_SIZE_BEFORE
//#define SHOW_ERRNO
#define SHOW_NAME
#define SHOW_SIZE_AFTER
#define SHOW_NEWLINE

/*
 * The dirent structure defines the format of directory entries.
 *
 * A directory entry has a struct dirent at the front of it, containing its
 * inode number, the length of the entry, and the length of the name
 * contained in the entry.  These are followed by the name padded to a 4
 * byte boundary with null g_ucBytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN when 32-bit
 * ino_t is in effect; (MAXPATHLEN - 1) when 64-bit ino_t is in effect.
 */

//#define __DARWIN_MAXPATHLEN	1024

//#define __DARWIN_STRUCT_DIRENTRY { \
//	__uint64_t  d_ino;      /* file number of entry */ \
//	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
//	__uint16_t  d_reclen;   /* length of this record */ \
//	__uint16_t  d_namlen;   /* length of string in d_name */ \
//	__uint8_t   d_type;     /* file type, see below */ \
//	char      d_name[__DARWIN_MAXPATHLEN]; 
//} dirent;

//#define	MAXNAMLEN	__DARWIN_MAXNAMLEN

//*
//* File types
//*
//#define	DT_UNKNOWN	 0
//#define	DT_FIFO		 1
//#define	DT_CHR		 2
//#define	DT_DIR		 4
//#define	DT_BLK		 6
//#define	DT_REG		 8
//#define	DT_LNK		10
//#define	DT_SOCK		12
//#define	DT_WHT		14

int main(int argc,char **argv)
{
	Version(argv[0]);

//	This works on Mac OS X
//	char g_szBuffer2[__DARWIN_MAXPATHLEN];

	// This works anywhere
	char g_szBuffer2[1024];
	
	FILE * fd = fopen("cvtthem","w");
	fprintf(fd,"#!/bin/sh\n");

	CDir *  dir = new CDir(".");
	int rc = dir->read();
	while(EXIT_SUCCESS == rc) {
		dir->getname(g_szBuffer2);
		if(4 < strlen(g_szBuffer2)) {
			if(0 == strcmp(".cpp",&g_szBuffer2[strlen(g_szBuffer2)-4])){
				fprintf(fd,"cvt %s\n",g_szBuffer2);
			}
		}
		rc = dir->read();
	}
	delete dir;

        dir = new CDir(".");
        rc = dir->read();
        while(EXIT_SUCCESS == rc) {
                dir->getname(g_szBuffer2);
                if(4 < strlen(g_szBuffer2)) {
                        if(0 == strcmp(".hpp",&g_szBuffer2[strlen(g_szBuffer2)-4])){
                                fprintf(fd,"cvt %s\n",g_szBuffer2);
                        }
                }
                rc = dir->read();
        }
        delete dir;

        dir = new CDir(".");
        rc = dir->read();
        while(EXIT_SUCCESS == rc) {
                dir->getname(g_szBuffer2);
                if(4 < strlen(g_szBuffer2)) {
                        if(0 == strcmp(".asm",&g_szBuffer2[strlen(g_szBuffer2)-4])){
                                fprintf(fd,"cvt %s\n",g_szBuffer2);
                        }
                }
                rc = dir->read();
        }
        delete dir;


	fclose(fd);
	system("chmod +x cvtthem");
	system("./cvtthem");	
	
	return EXIT_SUCCESS;
}

