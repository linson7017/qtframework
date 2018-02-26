/********************************************************************
	filename: 	IQF_Command.h
	author:		Ling Song
	date: 		ÈýÔÂ 2017
*********************************************************************/
#ifndef IQF_Command_h__
#define IQF_Command_h__

QF_BEGIN_NAMESPACE(QF)
class IQF_Properties;

class IQF_Command
{
public:
	virtual bool ExecuteCommand(const char* szCommandID, IQF_Properties* pInParam, IQF_Properties* pOutParam) = 0;
	virtual int GetCommandCount() = 0;
	virtual const char* GetCommandID(int iIndex) = 0;
};

QF_END_NAMESPACE
#endif // IQF_Command_h__
