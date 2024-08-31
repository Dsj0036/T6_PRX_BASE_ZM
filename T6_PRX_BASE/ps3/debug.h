#pragma once
#include "System.h"
#include "FileSystem.h"
#include "define.h"
// Created by josh, addresses by stankey or something like that.

#if ___DEBUG___
#define __DEBUG__
#ifndef TRACEPATH 
#define TRACEPATH "/dev_hdd0/tmp/bo2.log"
#endif
#endif


#if ___DEBUG___
namespace Debug {
	// Initializes again an empty log file, without keeping stream open, for reading.
	bool initialize() {
		FS_MKDIR(HOMEDIR);
		FS_RECREATE(TRACEPATH);
		FS_APPEND_STRING(TRACEPATH, "bo2.log");
		return FS_GETSIZE(TRACEPATH) != -1;
	}
	void cout(char* txt) {
		FS_APPEND_STRING(TRACEPATH, txt);
	}
	void coutl(char* txt) {		
		FS_APPEND_STRING(TRACEPATH, txt);
		FS_APPEND_STRING(TRACEPATH, "\n");
	}
	template <typename ...Arguments>
	void coutf(char* frm, Arguments...arg) {
		char buffer[0x100];
		s_snprintf(buffer, 0x100, frm, arg...);
		cout(buffer);
	}

}
#endif


#if ___DEBUG___
#define __print Debug::cout
#define __printl Debug::coutl
#define __printf Debug::coutf
#define IM_HERE __print((char*)__PRETTY_FUNCTION__)

#else
#define __print (void)0
#define __printl (void)0
#define __printf (void)0
#define IM_HERE 
#endif

#define DEBUG_ONCE(logicalName)\
namespace __debugOnce									  \
{														  \
	bool once_##logicalName;							  \
}														  \
void once_##logicalName() {								  \
	if (!__debugOnce::once_##logicalName) {					  \
		__debugOnce::once_##logicalName = true;			  \
		__print("DEBUG_ONCE " #logicalName "was called"); \
	}													  \
}														  \



