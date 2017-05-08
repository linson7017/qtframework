#ifndef IQF_Message_h__
#define IQF_Message_h__


QF_BEGIN_NAMESPACE(QF)

class IQF_Message
{
public:
    virtual int GetMessageCount() = 0;

    virtual const char* GetMessageID(int iIndex) = 0;

    virtual void OnMessage(const char* szMessage, int iValue, void *pValue) = 0;
};


QF_END_NAMESPACE

#endif // IQF_Message_h__
