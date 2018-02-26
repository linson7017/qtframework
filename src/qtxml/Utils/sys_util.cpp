#include "sys_util.h"


sys_util::sys_util()
{
}


sys_util::~sys_util()
{
}

time_t sys_util::GetFileLastChangeTime(const char* filename)
{
    struct _stat buf;
    int result;
    result = _stat(filename, &buf);
    if (result==0)
    {
        return buf.st_mtime;
    }
    else
    {
        return 0;
    }
}
