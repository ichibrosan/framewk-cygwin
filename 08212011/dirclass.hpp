// ---------------------------------------------------
// dirclass.hpp 21-Feb-11   Running on Mac OS X 10.6.6
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

static char szDirclassHpp[] = "$Id: dirclass.hpp,v 1.1 2011/03/24 11:58:05 doug Exp $";

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

#ifdef DIRCLASS

class CDir {
	struct dirent * m_dirent;
	DIR * m_dd;
public:
	CDir(char *);
	int read();
	void rewind();
	void getname(char *);
	int  getnamlen(void);
	int gettype(void);
	~CDir();
};

CDir::CDir(char * szDirSpec)
{
	m_dd = opendir(szDirSpec);
}

int CDir::read(void)
{
	m_dirent = readdir(m_dd);
	if(NULL == m_dirent) {
		return(EXIT_FAILURE);
	} else {
		return(EXIT_SUCCESS);
	}
}

void CDir::rewind(void)
{
	rewinddir(m_dd);
}

// Get next filename from directory
void CDir::getname(char * szRecvName)
{
	strcpy(szRecvName,m_dirent->d_name);
}

int CDir::getnamlen(void)
{
	// This version is more generic and does
	// not require the presence of d_namlen.
	return(strlen(m_dirent->d_name));

	// This version worked fine on Mac OS X
	// but not on Scientific Linux (RedHat5).
	// return((int)m_dirent->d_namlen);
}

int CDir::gettype(void)
{
	return((int)m_dirent->d_type);
}

CDir::~CDir()
{
	if(NULL != m_dd) {
		closedir(m_dd);
	}
}

#endif

////////////////////////
// eof - dirclass.hpp //
////////////////////////
