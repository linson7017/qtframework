#include "QF_Subject.h"
#include "IQF_Observer.h"

#include <assert.h>
QF_BEGIN_NAMESPACE(QF)

IQF_Subject* QF_CreateSubjectObject()
{
    IQF_Subject* psubject = new CQF_Subject;
    return psubject;
}

void QF_ReleaseSubjectObject(IQF_Subject *pSubject)
{
    if (pSubject)
        delete (CQF_Subject*)pSubject;
}


CQF_Subject::CQF_Subject()
{
}


CQF_Subject::~CQF_Subject()
{
    DetachAll();
}


void CQF_Subject::Release()
{
    delete this;
}

void CQF_Subject::Attach(IQF_Observer* pObserver, const char* szMessage)
{
    bool is_broadcast = false;

    is_broadcast = (strcmp(szMessage,"")==0);
    if (is_broadcast)
    {
        // 加入到广播列表中
        if (!HasObserver(pObserver, &m_BroadcastObservers))
        {
            //m_BroadcastObservers.push_back(pObserver) ;
            SQF_ObserverItem item;
            item.pObserver = pObserver;
            item.CheckValue = *((int*)pObserver);
            item.IsValid = true;

            m_BroadcastObservers.push_back(item);
        }
    }
    else
    {
        // 加入到指定消息所对应的Observer列表中

        // 如果该Observer已经在广播列表中,则不用再加入到特定Message的列表中
        if (HasObserver(pObserver, &m_BroadcastObservers))
            return;

        // 首先查找sz_message所对应的Observer列表
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.find(szMessage);

        CQF_ObserverList* p_observer_list = 0;

        // 如果找不到,则建立一个新的Observer列表,并加入到Map中
        if (iterator == m_MsgObserverMap.end())
        {
            p_observer_list = new CQF_ObserverList;

            // 拷贝消息字符串
            /*	char* sz_message = new char [strlen(szMessage) + 1] ;
            assert(sz_message) ;

            strcpy(sz_message, szMessage) ;

            m_MsgObserverMap[sz_message] = p_observer_list ;
            */
            m_MsgObserverMap[szMessage] = p_observer_list;
        }
        else
            p_observer_list = (*iterator).second;

        assert(p_observer_list);

        // 将指定的Observer对象加入到相应的Observer列表中
        if (p_observer_list)
        {
            if (!HasObserver(pObserver, p_observer_list))
            {
                SQF_ObserverItem item;
                item.pObserver = pObserver;
                item.CheckValue = *((int*)pObserver);
                item.IsValid = true;
                p_observer_list->push_back(item);
            }
        }

    }
}


void CQF_Subject::Detach(IQF_Observer* pObserver, const char* szMessage)
{
#ifndef _DEBUG
    try
    {
#endif	
        // 如果szMessage为空指针或空字符串，表示不再监听所有消息，则将其从所有列表中去除
        bool is_removeall = false;
        /*
        if (szMessage == NULL)
        is_removeall = true ;
        else if (strlen(szMessage) == 0)
        is_removeall = true ;
        else
        is_removeall = false ;
        */
        is_removeall = (strcmp(szMessage, "") == 0);

        CQF_MsgObserverMap::iterator iterator;
        CQF_ObserverList::iterator observer_iterator;

        // 如果不再监听指定消息，则首先找到该消息对应的Observer列表，然后从中将其删除
        if (!is_removeall)
        {
            iterator = m_MsgObserverMap.find(szMessage);

            // 如果找到,则从中将指定Observer删除
            if (iterator != m_MsgObserverMap.end())
            {
                CQF_ObserverList* p_observer_list = (*iterator).second;
                assert(p_observer_list);

                if (p_observer_list)
                {
                    //p_observer_list->remove(pObserver) ;
                    observer_iterator = p_observer_list->begin();
                    while (observer_iterator != p_observer_list->end())
                    {
                        if ((*observer_iterator).pObserver == pObserver)
                            break;
                        else
                            observer_iterator++;
                    }

                    if (observer_iterator != p_observer_list->end())
                    {
                        //					if (!m_IsBeingNotify)
                        if (m_NotifyLevel == 0)
                            p_observer_list->erase(observer_iterator);
                        else
                        {
                            SQF_ObserverItem item = *observer_iterator;
                            item.IsValid = false;
                            *observer_iterator = item;
                        }
                    }
                }
            }

        }
        else
        {
            // 如果不再监听所有消息，则从所有列表中将指定Observer删除

            // 首先删除广播列表
            //m_BroadcastObservers.remove(pObserver) ;
            observer_iterator = m_BroadcastObservers.begin();
            while (observer_iterator != m_BroadcastObservers.end())
            {
                if ((*observer_iterator).pObserver == pObserver)
                    break;
                else
                    observer_iterator++;
            }

            if (observer_iterator != m_BroadcastObservers.end())
            {
                //			if (!m_IsBeingNotify)
                if (m_NotifyLevel == 0)
                    m_BroadcastObservers.erase(observer_iterator);
                else
                {
                    SQF_ObserverItem item = *observer_iterator;
                    item.IsValid = false;
                    *observer_iterator = item;
                }
            }


            // 然后删除所有消息监听列表
            iterator = m_MsgObserverMap.begin();
            while (iterator != m_MsgObserverMap.end())
            {
                CQF_ObserverList* p_observer_list = (*iterator).second;
                assert(p_observer_list);

                if (p_observer_list)
                {
                    //p_observer_list->remove(pObserver) ;
                    observer_iterator = p_observer_list->begin();
                    while (observer_iterator != p_observer_list->end())
                    {
                        if ((*observer_iterator).pObserver == pObserver)
                            break;
                        else
                            observer_iterator++;
                    }

                    if (observer_iterator != p_observer_list->end())
                    {
                        //					if (!m_IsBeingNotify)
                        if (m_NotifyLevel == 0)
                            p_observer_list->erase(observer_iterator);
                        else
                        {
                            SQF_ObserverItem item = *observer_iterator;
                            item.IsValid = false;
                            *observer_iterator = item;
                        }
                    }
                }

                iterator++;
            }
        }

#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}
void CQF_Subject::DetachAll()
{
#ifndef _DEBUG
    try
    {
#endif	
        // 首先清除广播消息列表
        m_BroadcastObservers.clear();

        // 然后清除其它消息列表
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.begin();
        while (iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observer_list = (*iterator).second;
            assert(p_observer_list);

            //	char* sz_message = (char*)((*iterator).first) ;
            //	assert(sz_message);

            iterator++;

            if (p_observer_list)
            {
                p_observer_list->clear();
                delete p_observer_list;
            }

            //	if (sz_message)
            //		delete[] sz_message ;

        }

        m_MsgObserverMap.clear();

#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}

void CQF_Subject::Notify(const char* szMessage, int iValue, void* pValue)
{
#ifndef _DEBUG
    try
    {
#endif	

        //	m_IsBeingNotify = true ;
        m_NotifyLevel++;

        // 首先向广播队列中的Observer发送消息
        CQF_ObserverList::iterator observer_iterator;

        observer_iterator = m_BroadcastObservers.begin();
        while (observer_iterator != m_BroadcastObservers.end())
        {
            //IGIS_Observer* pobserver = *observer_iterator ;
            SQF_ObserverItem item = *observer_iterator;

            //pobserver->Update(szMessage, iValue, pValue) ;

            if (item.pObserver)
            {
                if (item.IsValid)
                {
                    if (item.CheckValue == *((int*)item.pObserver))
                    {
#ifndef _DEBUG
                        try
                        {
#endif	
                            item.pObserver->Update(szMessage, iValue, pValue);
#ifndef _DEBUG
                        }
                        catch (...)
                        {
                            std::cerr << "Error when execute message " << szMessage;
                        }
#endif	
                    }
                    else
                    {
                        item.IsValid = false;
                        *observer_iterator = item;
                    }
                }
            }

            observer_iterator++;

        }

        // 然后向指定消息队列中的Observer发送消息
        CQF_MsgObserverMap::iterator list_iterator = m_MsgObserverMap.find(szMessage);
        if (list_iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observerlist = (*list_iterator).second;
            assert(p_observerlist);

            if (p_observerlist)
            {
                observer_iterator = p_observerlist->begin();
                while (observer_iterator != p_observerlist->end())
                {
                    //IGIS_Observer* pobserver = *observer_iterator ;
                    //if (pobserver)
                    //	pobserver->Update(szMessage, iValue, pValue) ;

                    SQF_ObserverItem item = *observer_iterator;

                    if (item.pObserver)
                    {
                        if (item.IsValid)
                        {
                            if (item.CheckValue == *((int*)item.pObserver))
                            {
#ifndef _DEBUG
                                try
                                {
#endif	
                                    item.pObserver->Update(szMessage, iValue, pValue);
#ifndef _DEBUG
                                }
                                catch (...)
                                {
                                    std::cerr << "Error when execute message " << szMessage;
                                }
#endif	
                            }
                            else
                            {
                                assert(false && strcmp("Pointer to Observer is invalid, maybe is been deleted!", 0));
                                item.IsValid = false;
                                *observer_iterator = item;
                            }
                        }
                    } //if (item.pObserver)

                    observer_iterator++;

                } // while (observer_iterator != p_observerlist->end ())
            }
        }

        //	m_IsBeingNotify = false ;
        m_NotifyLevel--;
        if (m_NotifyLevel < 0)
            m_NotifyLevel = 0;

        // 清除所有在Notify过程中，被Detach方法设置为无效的Observer

        // 首先清除广播消息列表中的无效Observer
        observer_iterator = m_BroadcastObservers.begin();
        while (observer_iterator != m_BroadcastObservers.end())
        {
            SQF_ObserverItem item = *observer_iterator;

            CQF_ObserverList::iterator observer_iterator_tobe_delete = observer_iterator;

            observer_iterator++;

            if (!item.IsValid)
                m_BroadcastObservers.erase(observer_iterator_tobe_delete);
        }

        // 然后清除其它消息列表中的无效Observer
        CQF_MsgObserverMap::iterator iterator = m_MsgObserverMap.begin();
        while (iterator != m_MsgObserverMap.end())
        {
            CQF_ObserverList* p_observer_list = (*iterator).second;
            assert(p_observer_list);

            iterator++;

            if (p_observer_list)
            {
                observer_iterator = p_observer_list->begin();
                while (observer_iterator != p_observer_list->end())
                {
                    SQF_ObserverItem item = *observer_iterator;

                    CQF_ObserverList::iterator observer_iterator_tobe_delete = observer_iterator;

                    observer_iterator++;

                    if (!item.IsValid)
                        p_observer_list->erase(observer_iterator_tobe_delete);

                }
            }
        }
#ifndef _DEBUG
    }
    catch (...)
    {
    }
#endif	
}

bool CQF_Subject::HasObserver(IQF_Observer* pObserver, CQF_ObserverList* pObserverList)
{
    CQF_ObserverList::iterator observer_iterator;

    // 如果为空，则返回false
    if (pObserverList->size() == 0)
        return false;

    // 遍历查询指定的Observer
    observer_iterator = pObserverList->begin();
    while (observer_iterator != pObserverList->end())
    {
        // 先将当前指针前移，再发出消息。
        // 从而使观察家对象能够在消息处理过程中与本被观察对象脱钩
        SQF_ObserverItem item = *observer_iterator;
        observer_iterator++;

        //if (observer == pObserver)
        if (item.pObserver == pObserver)
            return true;
    }

    return false;
}

QF_END_NAMESPACE