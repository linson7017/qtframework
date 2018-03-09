#ifndef iqf_activator_h__
#define iqf_activator_h__

#include "QF_Config.h"


class R;
QF_BEGIN_NAMESPACE(QF)

class IQF_Main;

class IQF_Activator
{
public:
    virtual bool Init() = 0;
    virtual const char* GetID() = 0;
    virtual void Register()=0;
    virtual void Constructed() = 0;
};


#ifdef __cplusplus
extern "C" {
#endif

    QF_API IQF_Activator* QF_CreatePluginActivator(IQF_Main* pMain);


#ifdef __cplusplus
}
#endif



QF_END_NAMESPACE

#endif // iqf_activator_h__
