/********************************************************************
	FileName:    sys.h
	Author:        Ling Song
	Date:           Month 1 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef sys_util_h__
#define sys_util_h__
#include <sys/stat.h>

class sys_util
{
public:
    sys_util();
    ~sys_util();
    static time_t GetFileLastChangeTime(const char* filename);

};
#endif // sys_h__