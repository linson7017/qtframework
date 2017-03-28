#ifndef IQF_Observer_h__
#define IQF_Observer_h__
#pragma once

#include "QF_Config.h"

QF_BEGIN_NAMESPACE(QF)

class IQF_Observer
{
public:
    virtual void Update(const char* szMessage, int iValue = 0, void* pValue = 0) = 0;
};

QF_END_NAMESPACE;

#endif // IQF_Observer_h__
