#ifndef QF_IQF_PROPERTYSET_H__
#define QF_IQF_PROPERTYSET_H__

#include <qf_config.h>
#include <IQF_Field.h>

QF_BEGIN_NAMESPACE(QF)

class IQF_Field;
class IQF_DataBuffer;

/// \brief 属性集合接口
///
/// 属性集合接口。封装了对属性集合中各个字段的添加、删除以及遍历等操作。
///
/// \note 通过全局函数QF_CreatePropertySetObject()创建一个IQF_PropertySet对象。
///
//##
class IQF_PropertySet
{
  public:
	/// \brief 释放属性集合对象。
	/// 
	/// 释放属性集合对象
	///
	/// \return 无
	///
	/// \param 无
	///
    virtual void Release() = 0;

	/// \brief 清除属性集合中的所有属性记录
	/// 
	/// 清除属性集合中的所有属性记录
	///
	/// \return 无
	///
	/// \param 无
	///
    virtual void Clear() = 0;

    /// \brief 获取属性集合中的字段个数。
	///
	/// 获取属性集合中的字段个数。
	///
	/// \return 属性集合中的字段个数
	///
	/// \param 无
	///
    virtual int GetCount() = 0;

    /// \brief 通过字段名称获取指定属性字段
	///
	/// 通过字段名称获取指定属性字段。
	///
	/// \return 指定属性字段对象的指针。如果没有给定名称的属性字段，则返回NULL。
	///
	/// \param szName：字段名称
	///
    virtual IQF_Field* GetPropertyPtr(const char* szName) = 0;

    /// \brief 获取属性集合中第一个属性字段对象
	///
	/// 获取属性集合中第一个属性字段对象。与GetNextPropertyPtr()配套使用，用于对属性集合进行遍历。
	///
	/// \return 第一个属性字段对象的指针。如果属性集合为空，则返回NULL。
	///
	/// \param 无
	///
    virtual IQF_Field* GetFirstPropertyPtr() = 0;

    /// \brief 获取属性集合中指定字段的下一个属性字段对象
	///
	/// 获取属性集合中指定字段的下一个属性字段对象。与GetFirstPropertyPtr()配套使用，用于对属性集合进行遍历。
	///
	/// \return 下一个属性字段对象的指针。如果属性集合为空，或当前属性字段不再属性集合中，或当前属性字段已经是属性集合的最后一个属性字段，则返回NULL。
	///
	/// \param pCurrentField：当前属性字段对象的指针
	///
    virtual IQF_Field* GetNextPropertyPtr(IQF_Field* pCurrentField) = 0;
    
    /// \brief 在属性集合中新建一个属性字段。
	///
	/// 根据给定名称、类型等信息在属性集合中新建一个属性字段。
	///
	/// \return 如果新建成功，则返回新建属性字段对象的指针；否则返回NULL。
	///
	/// \param szName：属性字段名称。属性字段名称将被转换为大写，且在同一属性集合中必须唯一。
	/// \param szCaption：属性字段标题。可以为NULL。
	/// \param iType：属性字段数据类型。参见QF_commondef.h中“数据类型”部分的相关定义。
	/// \param bToBeArchive：选项参数。为true表示在Archive()时该属性字段应归档到数据缓存区中；为false表示在Archive()时该属性字段将被忽略。缺省为true。
	///
    virtual  IQF_Field* AddProperty(const char* szName, const char* szCaption, int iType, bool bToBeArchive = true) = 0;

	/// \brief 添加一个属性字段。
	///
	/// 添加一个属性字段到属性集合中。如果添加成功，则给定字段的释放由属性集合负责，用户不能显式调用pField->Release()。
	///
	/// \return 如果添加成功，则返回true；否则返回false。如果属性集合中已存在同名属性字段，则返回false。
	///
	/// \param pField：带添加的属性字段。
	///
    virtual bool AddProperty(IQF_Field* pField) = 0;
    
    /// \brief 删除指定属性字段。
	///
	/// 根据给定的属性字段名称删除指定属性字段
	///
	/// \return 如果删除成功，则返回true；否则返回false。如果属性集合中不存在指定名称的属性字段，则返回false。
	///
	/// \param szName：要删除的属性字段的名称
	///
    virtual bool DeleteProperty(const char* szName) = 0;

    /// \brief 设置QF_INTEGER类型属性值
    ///
    /// 设置QF_INTEGER类型属性值。
	/// 如果该属性集合中已经有szName所指定的属性，并且类型为QF_INTEGER，则设置该属性的数值；如果数据类型不一致，则返回false。
    /// 如果该属性集合中没有szName所指定的属性，则根据szName，在本属性集合中新建一个属性，并设置属性值。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szName：属性字段名称。属性字段名称将被转换为大写，且在同一属性集合中必须唯一。
	/// \param iValue：要设置的字段值。
	/// \param bToBeArchive：选项参数。为true表示在Archive()时该属性字段应归档到数据缓存区中；为false表示在Archive()时该属性字段将被忽略。缺省为true。
	///
    virtual bool SetIntProperty(const char* szName, int iValue, bool bToBeArchive = true) = 0;

    /// \brief 设置QF_BOOL类型属性值
    ///
    /// 设置QF_BOOL类型属性值。
	/// 如果该属性集合中已经有szName所指定的属性，并且类型为QF_BOOL，则设置该属性的数值；如果数据类型不一致，则返回false。
    /// 如果该属性集合中没有szName所指定的属性，则根据szName，在本属性集合中新建一个属性，并设置属性值。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szName：属性字段名称。属性字段名称将被转换为大写，且在同一属性集合中必须唯一。
	/// \param bValue：要设置的字段值。
	/// \param bToBeArchive：选项参数。为true表示在Archive()时该属性字段应归档到数据缓存区中；为false表示在Archive()时该属性字段将被忽略。缺省为true。
	///
    virtual bool SetBoolProperty(const char* szName, bool bValue, bool bToBeArchive = true) = 0;

    /// \brief 设置QF_DOUBLE类型属性值
    ///
    /// 设置QF_DOUBLE类型属性值。
	/// 如果该属性集合中已经有szName所指定的属性，并且类型为QF_DOUBLE，则设置该属性的数值；如果数据类型不一致，则返回false。
    /// 如果该属性集合中没有szName所指定的属性，则根据szName，在本属性集合中新建一个属性，并设置属性值。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szName：属性字段名称。属性字段名称将被转换为大写，且在同一属性集合中必须唯一。
	/// \param dValue：要设置的字段值。
	/// \param bToBeArchive：选项参数。为true表示在Archive()时该属性字段应归档到数据缓存区中；为false表示在Archive()时该属性字段将被忽略。缺省为true。
	///
    virtual bool SetDoubleProperty(const char* szName, double dValue, bool bToBeArchive = true) = 0;

    /// \brief 设置QF_STRING类型属性值
    ///
    /// 设置QF_STRING类型属性值。
	/// 如果该属性集合中已经有szName所指定的属性，并且类型为QF_STRING，则设置该属性的数值；如果数据类型不一致，则返回false。
    /// 如果该属性集合中没有szName所指定的属性，则根据szName，在本属性集合中新建一个属性，并设置属性值。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szName：属性字段名称。属性字段名称将被转换为大写，且在同一属性集合中必须唯一。
	/// \param szValue：要设置的字段值。
	/// \param bToBeArchive：选项参数。为true表示在Archive()时该属性字段应归档到数据缓存区中；为false表示在Archive()时该属性字段将被忽略。缺省为true。
	///
    virtual bool SetStringProperty(const char* szName, const char* szValue, bool bToBeArchive = true) = 0;

	/// \brief 赋值运算
	///
	/// 将给定属性集合赋给当前属性集合
	///
	/// \return 当前属性集合对象的引用
	///
	/// \param right：赋值运算右操作数
	///
    virtual IQF_PropertySet& operator=(const IQF_PropertySet& right) = 0;

	/// \brief 相等运算
	///
	/// 判断给定属性集合是否与当前属性集合相等
	///
	/// \return 如果相等，则返回1；否则，返回0。
	///
	/// \param right：相等运算右操作数
	///
    virtual int operator==(const IQF_PropertySet& right) = 0;

	/// \brief 不相等运算
	///
	/// 判断给定属性集合是否与当前属性集合不相等
	///
	/// \return 如果不相等，则返回1；否则，返回0。
	///
	/// \param right：不相等运算右操作数
	///
    virtual int operator!=(const IQF_PropertySet& right) = 0;


};

//extern "C"
//{
	/// \brief 工厂方法。创建一个属性集合对象
	/// 
	/// 创建一个属性集合对象。
	/// 
	/// \return 如果创建成功，则返回属性集合对象的指针；否则返回NULL
	/// 
	/// \param 无
	///
	/// \note \e 静态连接库：common.lib
	///	
	QF_API IQF_PropertySet* QF_CreatePropertySetObject() ;
//}


/// \brief 属性集合的智能指针
/// 
/// 属性集合的智能指针。封装了属性集合对象的创建和释放，可以作为局部自动变量使用
/// 
class IQF_PropertySetPtr 
{
public :
	///	\brief 构造函数
	///
	/// 属性集合智能指针的构造函数
	///
	/// \param 无
	///
	IQF_PropertySetPtr()
	{
		m_ptr = QF_CreatePropertySetObject() ; 
	}

	///	\brief 析构函数
	///
	/// 属性集合智能指针的析构函数
	///
	~IQF_PropertySetPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief 指针操作符重载
	///
	/// 属性集合智能指针的指针操作符重载。
	///
	IQF_PropertySet* operator->() const
	{
		return m_ptr;
	}

	/// \brief 属性集合对象
	///
	/// public成员。属性集合智能指针的实际属性集合对象
	///
	IQF_PropertySet * m_ptr ;
} ;

QF_END_NAMESPACE
#endif

