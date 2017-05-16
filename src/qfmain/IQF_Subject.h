/********************************************************************
	filename: 	IQF_Subject.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef IQF_Subject_h__
#define IQF_Subject_h__
#pragma once

#include "QF_Config.h"


QF_BEGIN_NAMESPACE(QF)
class IQF_Observer;
class IQF_Subject;

QF_API IQF_Subject* QF_CreateSubjectObject();
QF_API void QF_ReleaseSubjectObject(IQF_Subject *pSubject);

class IQF_Subject
{
public:
    virtual void Attach(IQF_Observer* pObserver, const char* szMessage = "") = 0;
    virtual void Detach(IQF_Observer* pObserver, const char* szMessage = "") = 0;
    virtual void DetachAll() = 0;
    virtual void Notify(const char* szMessage, int iValue = 0, void* pValue = 0) = 0;
};

QF_END_NAMESPACE;

#endif // IQF_Subject_h__
