#ifndef QF_IQF_FIELD_H__
#define QF_IQF_FIELD_H__

#include <qf_config.h>

QF_BEGIN_NAMESPACE(QF)

class IQF_Array;
class IQF_PropertySet;

/// \brief 字段接口
///
/// 字段接口。封装可对字段元数据和数据的访问。
///
/// \note 通过全局函数QF_CreateFieldObject()创建一个IQF_Field对象。
///
//##ModelId=3F90F98A02E4
class IQF_Field
{
  public:

	/// \brief 释放字段对象。
	/// 
	/// 释放字段对象
	///
	/// \return 无
	///
	/// \param 无
	///
    //##ModelId=3F90F98A02F4
    virtual void Release() = 0;

    /// \brief 获取字段名称
    ///
    /// 获取字段名称
	///
    /// \return 字段名称。
	///
	/// \param 无
	///
    //##ModelId=3F90F98A02F5
    virtual const char* GetName() = 0;

    /// \brief 设置字段名称
    ///
    /// 设置字段名称。不能修改，只能初始化。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szName：字段名称。
	///
    virtual bool SetName(const char* szName) = 0;

    /// \brief 获取字段数据类型
    ///
    /// 获取字段数据类型
	///
    /// \return 字段数据类型。
	///
	/// \param 无
	///
    virtual int GetType() = 0;

    /// \brief 设置字段类型
    ///
    /// 设置字段类型。不能修改，只能初始化。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param iType：字段类型。
	///
    virtual bool SetType(int iType) = 0;

    /// \brief 获取字段数据外部类型
    ///
    /// 获取字段数据外部类型
	///
    /// \return 字段数据外部类型。
	///
	/// \param 无
	///
    virtual int GetExtType() = 0;

    /// \brief 设置字段数据外部类型
    ///
    /// 设置字段数据外部类型。
	///
    /// \return 无
	///
	/// \param iExtType：字段数据外部类型。
	///
    virtual void SetExtType(int iExtType) = 0;

    /// \brief 获取字段种类
    ///
    /// 获取字段种类
	///
    /// \return 字段种类。
	///
	/// \param 无
	///
    virtual const char* GetStereoType() = 0;

    /// \brief 设置字段种类
    ///
    /// 设置字段种类。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szStereoType：字段种类。
	///
    virtual bool SetStereoType(const char* szStereoType) = 0;

    /// \brief 获取字段定义长度
    ///
    /// 获取字段定义长度。初始设置为0。
	///
    /// \return 字段定义长度。
	///
	/// \param 无
	///
    virtual int GetDefLength() = 0;

    /// \brief 设置字段定义长度
    ///
    /// 设置字段定义长度。不能修改，只能初始化。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param iDefLength：字段定义长度。
	///
    virtual bool SetDefLength(int iDefLength) = 0;

    /// \brief 获取字段标题
    ///
    /// 获取字段标题
	///
    /// \return 字段标题。
	///
	/// \param 无
	///
    virtual const char* GetCaption() = 0;

    /// \brief 设置字段标题
    ///
    /// 设置字段标题。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szCaption：字段标题。
	///
    virtual bool SetCaption(const char* szCaption) = 0;

    /// \brief 获取字段描述
    ///
    /// 获取字段描述
	///
    /// \return 字段描述。
	///
	/// \param 无
	///
    virtual const char* GetDesc() = 0;

    /// \brief 设置字段描述
    ///
    /// 设置字段描述。
	///
    /// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szDesc：字段描述。
	///
    virtual bool SetDesc(const char* szDesc) = 0;

    /// \brief 判断字段值是否标记为可以为空
	///
	/// 判断字段值是否标记为可以为空。初始设置为可以为空。
	///
	/// \return 如果字段值标记为可以为空，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsNullable() = 0;

    /// \brief 标记字段值是否可以为空
	///
	/// 标记字段值是否可以为空
	///
	/// \return 如果标记成功，则返回true；否则返回false。
	///
	/// \param bNullable：true表示要将字段值标记为可以为空；false表示要将字段值标记为不能为空。缺省为true。
	///
    virtual bool SetNullable(bool bNullable = true) = 0;

    /// \brief 判断字段是否标记为可以被删除
	///
	/// 判断字段是否标记为可以被删除。初始设置为可以被删除。
	///
	/// \return 如果字段标记为可以被删除，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsDeletable() = 0;

    /// \brief 标记字段是否可以被删除
	///
	/// 标记字段是否可以被删除
	///
	/// \return 如果标记成功，则返回true；否则返回false。
	///
	/// \param bDeletable：true表示要将字段标记为可以被删除；false表示要将字段标记为不能被删除。缺省为true。
	///
    virtual bool SetDeletable(bool bDeletable = true) = 0;

    /// \brief 判断字段是否标记为可以被修改
	///
	/// 判断字段是否标记为可以被修改。初始设置为可以被删除。
	///
	/// \return 如果字段标记为可以被修改，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsUpdatable() = 0;

    /// \brief 标记字段是否可以被修改
	///
	/// 标记字段是否可以被修改
	///
	/// \return 如果标记成功，则返回true；否则返回false。
	///
	/// \param bUpdatable：true表示要将字段标记为可以被修改；false表示要将字段标记为不能被修改。缺省为true。
	///
    virtual bool SetUpdatable(bool bUpdatable = true) = 0;

    /// \brief 判断字段是否标记为可以被索引
	///
	/// 判断字段是否标记为可以被索引。初始设置为可以被索引。
	///
	/// \return 如果字段标记为可以被索引，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsIndexable() = 0;

    /// \brief 标记字段是否可以被索引
	///
	/// 标记字段是否可以被索引
	///
	/// \return 如果标记成功，则返回true；否则返回false。
	///
	/// \param bIndexable：true表示要将字段标记为可以被索引；false表示要将字段标记为不能被索引。缺省为true。
	///
    virtual bool SetIndexable(bool bIndexable = true) = 0;

    /// \brief 判断字段是否标记为被索引
	///
	/// 判断字段是否标记为被索引。初始设置为没有被索引。
	///
	/// \return 如果字段标记为被索引，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsIndex() = 0;

    /// \brief 标记字段是否被索引
	///
	/// 标记字段是否被索引
	///
	/// \return 如果标记成功，则返回true；否则返回false。
	///
	/// \param bIndexable：true表示要将字段标记为被索引；false表示要将字段标记为没有被索引。缺省为false。
	///
    virtual bool SetToBeIndex(bool bToBeIndex = false) = 0;

    /// \brief 获取字段的实际长度，单位为字节数。
	///
	/// 获取字段的实际长度，单位为字节数。
	///
	/// \return 字段的实际长度，单位为字节数。
    /// \li 整型：sizeof(int)
    /// \li 布尔型：sizeof(char)
    /// \li 浮点型：sizeof(double)
    /// \li 字符串：strlen + 1
	///
	/// \param 无
	///
    virtual unsigned int GetLength() = 0;
	
    /// \brief 判断字段值是否为空。
	///
	/// 判断字段值是否为空。任何类型的字段均初始化为空。
	///
	/// \return 如果字段值为空，则返回true；否则返回false。
	///
	/// \param 无
	///
    virtual bool IsNull() = 0;

    /// \brief 设置字段值是否为空值
	///
	/// 设置字段值是否为空值
	///
	/// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param bIsNull：true表示设置字段值为空值；false表示设置字段值不为空。缺省为true。
	///
    virtual bool SetToNull(bool bIsNull = true) = 0;

    /// \brief 以字符串的形式获取字段值
	///
	/// 以字符串的形式获取字段值。
	/// 对于QF_INTEGER、QF_DOUBLE类型，获取的结果为数字字符串；
	/// 对于QF_BOOL类型，获取的结果为"TRUE"或"FALSE"；
	/// 对于QF_STRING类型，获取的结果即为字段值；
	/// 对于其他类型，获取的结果为空串""，并返回false。
	///
	/// \return 如果获取成功，则返回true；否则返回false。
	///
	/// \param szValueString：输出参数。如果获取成功，则内容为获取的结果；否则内容为空串""。
	/// \param iLength：指明szValueString可容纳的最大长度。
	///
    virtual bool GetValueAsString(char* szValueString, int iLength) = 0;

    /// \brief 以字符串的形式设置字段值
	///
	/// 以字符串的形式设置字段值。
	///
	/// \return 如果设置成功，则返回true；否则返回false。
	///
	/// \param szValueString：内容为字符串形式的字段值
	/// 对于QF_INTEGER、QF_DOUBLE类型，为数字字符串；
	/// 对于QF_BOOL类型，为"TRUE"或"FALSE"；
	/// 对于QF_STRING类型，为字段值；
	/// 对于其他类型，无意义，并返回false。
	///
    virtual bool SetValueAsString(const char* szValueString) = 0;

    /// \brief 获取QF_INTEGER类型字段值
    ///
    /// 获取QF_INTEGER类型字段值
	///
    /// \return 如果获取成功，则返回相应的值；否则返回INT_MIN。如果字段不为QF_INTEGER类型，或字段为空，则返回INT_MIN。
	///
	/// \param 无
	///1
    virtual int GetInt() = 0;

    /// \brief 设置QF_INTEGER类型字段值
    ///
    /// 设置QF_INTEGER类型字段值
	///
    /// \return 如果设置成功，则返回true；否则返回false。如果字段不为QF_INTEGER类型，则返回false。
	///
	/// \param iValue：要设置的字段值。
	///
    virtual bool SetInt(int iValue) = 0;

    /// \brief 获取QF_BOOL类型字段值
    ///
    /// 获取QF_BOOL类型字段值
	///
    /// \return 如果获取成功，则返回相应的值；否则返回false。如果字段不为QF_BOOL类型，或字段为空，则返回false。
	///
	/// \param 无
	///
    //##ModelId=4042A7B30017
    virtual bool GetBool() = 0;

    /// \brief 设置QF_BOOL类型字段值
    ///
    /// 设置QF_BOOL类型字段值
	///
    /// \return 如果设置成功，则返回true；否则返回false。如果字段不为QF_BOOL类型，则返回false。
	///
	/// \param bValue：要设置的字段值。
	///
    //##ModelId=4042A7B30026
    virtual bool SetBool(bool bValue) = 0;

    /// \brief 获取QF_DOUBLE类型字段值
    ///
    /// 获取QF_DOUBLE类型字段值
	///
    /// \return 如果获取成功，则返回相应的值；否则返回-DBL_MAX。如果字段不为QF_DOUBLE类型，或字段为空，则返回-DBL_MAX。
	///
	/// \param 无
	///
    //##ModelId=3F90F98A0343
    virtual double GetDouble() = 0;

    /// \brief 设置QF_DOUBLE类型字段值
    ///
    /// 设置QF_DOUBLE类型字段值
	///
    /// \return 如果设置成功，则返回true；否则返回false。如果字段不为QF_DOUBLE类型，则返回false。
	///
	/// \param dValue：要设置的字段值。
	///
    //##ModelId=3F90F98A0351
    virtual bool SetDouble(double dValue) = 0;

    /// \brief 获取QF_STRING类型字段值
    ///
    /// 获取QF_STRING类型字段值
	///
    /// \return 如果获取成功，则返回相应的值；否则返回空字符串""。如果字段不为QF_STRING类型，或字段为空，则返回空字符串""。
	///
	/// \param 无
	///
    //##ModelId=3F90F98A0345
    virtual const char* GetString() = 0;

    /// \brief 设置QF_STRING类型字段值
    ///
    /// 设置QF_STRING类型字段值
	///
    /// \return 如果设置成功，则返回true；否则返回false。如果字段不为QF_STRING类型，则返回false。
	///
	/// \param szValue：要设置的字段值。
	///
    //##ModelId=3F90F98A0354
    virtual bool SetString(const char* szValue) = 0;

	/// \brief 相等运算
	///
	/// 判断给定字段元数据和的数值是否与当前字段的元数据和数值相等
	///
	/// \return 如果相等，则返回1；否则，返回0。
	///
	/// \param right：相等运算右操作数
	///
    //##ModelId=3FA4B93B0154
    virtual int operator==(const IQF_Field& right) = 0;

	/// \brief 不相等运算
	///
	/// 判断给定字段元数据和的数值是否与当前字段的元数据和数值不相等
	///
	/// \return 如果不相等，则返回1；否则，返回0。
	///
	/// \param right：不相等运算右操作数
	///
    //##ModelId=3FA4B93B0210
    virtual int operator!=(const IQF_Field& right) = 0;

	/// \brief 赋值运算
	///
	/// 将给定字段的元数据和数值赋给当前字段
	///
	/// \return 当前字段对象的引用
	///
	/// \param right：赋值运算右操作数
	///
    //##ModelId=3FA4B93B0079
    virtual IQF_Field& operator=(const IQF_Field& right) = 0;

};

//extern "C"
//{
	/// \brief 工厂方法。创建一个字段对象
	/// 
	/// 创建一个字段对象。
	/// 
	/// \return 如果创建成功，则返回字段对象的指针；否则返回NULL
	/// 
	/// \param 无
	///
	/// \note \e 静态连接库：QF_commontype.lib
	///	
	QF_API IQF_Field* QF_CreateFieldObject() ;
//}

/// \brief 字段的智能指针
/// 
/// 字段的智能指针。封装了字段对象的创建和释放，可以作为局部自动变量使用
/// 
class IQF_FieldPtr 
{
public :
	///	\brief 构造函数
	///
	/// 字段智能指针的构造函数
	///
	/// \param 无
	///
	IQF_FieldPtr()
	{
		m_ptr = QF_CreateFieldObject() ; 
	}

	///	\brief 析构函数
	///
	/// 字段智能指针的析构函数
	///
	~IQF_FieldPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief 指针操作符重载
	///
	/// 字段智能指针的指针操作符重载。
	///
	IQF_Field* operator->() const
	{
		return m_ptr;
	}
	
	/// \brief 字段对象
	///
	/// public成员。字段智能指针的实际字段对象
	///
	IQF_Field* m_ptr ;
	
} ;

QF_END_NAMESPACE
#endif

