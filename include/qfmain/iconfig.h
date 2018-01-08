#ifndef iconfig_h__
#define iconfig_h__

//
#ifndef  BUILD_INTERFACE
#define BUILD_INTERFACE(INTERFACE_NAME) \
public:     \
    virtual ~##INTERFACE_NAME(){}       //防止在接口中用户通过delete删除接口指针导致实现类析构函数未调用的问题，还可以通过IQF_Object的release()接口解决
#endif
#endif // iconfig_h__