#ifndef QF_Plugin_h__
#define QF_Plugin_h__

#pragma once

#include <map>
#include <string>
#include "iqf_observer.h"

class R;
class QWidget;
#define WndHandle QWidget*

namespace QF
{
    class IQF_Main;
    class QF_Plugin : public IQF_Observer
    {
    public:
        virtual void InitResource() = 0;
        virtual void SetMainPtr(QF::IQF_Main* pMain) = 0;
        virtual void SetupResource() = 0;
        virtual WndHandle GetPluginHandle() = 0;
        void SetAttributes(const std::map<std::string, std::string>& attribute)
        {
            m_attributes = attribute;
        }
        void SetAttribute(const std::string& key,const std::string& value)
        {
            m_attributes[key] = value;
        }
    protected:
        std::map<std::string, std::string> m_attributes;
    };
}

#endif // QF_Plugin_h__
