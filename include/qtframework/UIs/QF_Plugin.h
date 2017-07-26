#ifndef QF_Plugin_h__
#define QF_Plugin_h__

#pragma once
#include <QObject>

class R;

namespace QF
{
    class IQF_Main;
    class QF_Plugin
    {
    public:
        virtual void InitResource(R* pR) = 0;
        virtual void SetMainPtr(QF::IQF_Main* pMain) = 0;
    };
}

#endif // QF_Plugin_h__
