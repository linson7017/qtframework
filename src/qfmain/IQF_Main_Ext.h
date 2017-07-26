/********************************************************************
	filename: 	IQF_Main_Ext.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef IQF_Main_Ext_h__
#define IQF_Main_Ext_h__
#pragma once

#pragma once
#include "IQF_Main.h"

class R;
QF_BEGIN_NAMESPACE(QF)

class IQF_Main_Ext : public IQF_Main
{
public:
    virtual void RegisterResource(R* pR) = 0;
    virtual void ResourceConstructed(R* pR) = 0;
};


QF_END_NAMESPACE;



#endif // IQF_Main_h__