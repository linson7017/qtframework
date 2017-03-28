#pragma once

#include "IQF_Subject.h"
#include <list>
#include <map>

QF_BEGIN_NAMESPACE(QF)


class IQF_Observer;

typedef struct
{
    IQF_Observer* pObserver;
    int	CheckValue;
    bool IsValid;
} SQF_ObserverItem;

typedef std::list<SQF_ObserverItem> CQF_ObserverList;
typedef std::map<const char*, CQF_ObserverList*> CQF_MsgObserverMap;

class CQF_Subject : public IQF_Subject
{
public:
    CQF_Subject();
    ~CQF_Subject();

    void Attach(IQF_Observer* pObserver, const char* szMessage = "");
    void Detach(IQF_Observer* pObserver, const char* szMessage = "");
    void DetachAll();
    void Notify(const char* szMessage, int iValue = 0, void* pValue = 0);

    void Release();

private:
    bool HasObserver(IQF_Observer* pObserver, CQF_ObserverList* pObserverList);

    //##ModelId=3FFA6254004C
    CQF_MsgObserverMap m_MsgObserverMap;

    //##ModelId=3FFA628702EE
    CQF_ObserverList m_BroadcastObservers;

    //	bool m_IsBeingNotify ;
    int m_NotifyLevel;
};

QF_END_NAMESPACE

