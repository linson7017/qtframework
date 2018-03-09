#include "IQF_Main.h"
#include "CQF_Main.h"
#include <assert.h>
QF_BEGIN_NAMESPACE(QF)

IQF_Main*  QF_CreateMainObject(const char* szEnterName,const char* szLibraryPath, bool bInit)
{
    IQF_Main* p = new CQF_Main(szEnterName, szLibraryPath, bInit);
    assert(p);

    return p;
}

QF_END_NAMESPACE