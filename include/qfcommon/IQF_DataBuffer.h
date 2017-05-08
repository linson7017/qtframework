#ifndef QF_IQF_DATABUFFER_H__
#define QF_IQF_DATABUFFER_H__

#include <qf_config.h>

QF_BEGIN_NAMESPACE(QF)

/// \brief 数据缓存区接口
///
/// 数据缓存区接口。
///
/// \note 通过全局函数QF_CreateDataBufferObject()创建一个IQF_DataBuffer对象。
///
//##ModelId=3F9CF3CD0253
class IQF_DataBuffer
{
  public:
	/// \brief 释放数据缓存区对象。
	/// 
	/// 释放数据缓存区对象
	///
	/// \return 无
	///
	/// \param 无
	///
	//##ModelId=3F9CF3CD0276
    virtual void Release() = 0;

	/// \brief 获取数据缓存区大小。
	/// 
	/// 获取数据缓存区大小，单位为字节。
	///
	/// \return 数据缓存区大小
	///
	/// \param 无
	///
    //##ModelId=3F9CF3CD0272
    virtual int GetSize() = 0;

	/// \brief 设置数据缓存区大小。
	/// 
	/// 设置数据缓存区大小，并进行内存重分配。缓存区原有内存区将失效且原有数据将丢失。
	///
	/// \return 如果设置成功且内存分配成功，则返回true；否则返回false。
	///
	/// \param iSize：数据缓存区大小，单位为字节。如果iSize == 0，则清除原有内存区，且使得GetBufferPtr() == NULL。
	///
    //##ModelId=3F9CF3CD0261
    virtual bool SetSize(int iSize) = 0;

	/// \brief 获取指向数据缓存区内存首地址的指针。
	/// 
	/// 获取指向数据缓存区内存首地址的指针。
	///
	/// \return 指向数据缓存区内存首地址的指针。如果尚未进行内存分配，则返回NULL。
	///
	/// \param 无
	///
    //##ModelId=3F9CF3CD0274
    virtual char* GetBufferPtr() = 0;

	/// \brief 赋值运算
	///
	/// 将给定数据缓存区内容赋给当前数据缓存区
	///
	/// \return 当前数据缓存区的引用
	///
	/// \param right：赋值运算右操作数
	///
    //##ModelId=3FA4C7290085
    virtual IQF_DataBuffer& operator=(const IQF_DataBuffer& right) = 0;

	/// \brief 相等运算
	///
	/// 判断给定数据缓存区内容是否与当前数据缓存区内容相等
	///
	/// \return 如果相等，则返回1；否则，返回0。
	///
	/// \param right：相等运算右操作数
	///
    //##ModelId=3FA4C7290112
    virtual int operator==(const IQF_DataBuffer& right) = 0;

	/// \brief 不相等运算
	///
	/// 判断给定数据缓存区内容是否与当前数据缓存区内容不相等
	///
	/// \return 如果不相等，则返回1；否则，返回0。
	///
	/// \param right：不相等运算右操作数
	///
    //##ModelId=3FA4C729017F
    virtual int operator!=(const IQF_DataBuffer& right) = 0;

};

//extern "C"
//{
	/// \brief 工厂方法。创建一个数据缓存区对象
	/// 
	/// 创建一个数据缓存区对象，并根据初始大小进行内存分配。
	/// 
	/// \return 如果创建成功，则返回数据缓存区对象的指针；否则返回NULL
	/// 
	/// \param iSize：数据缓存区的初始大小。如果iSize == 0，则不进行内存分配，且GetBufferPtr() == NULL。
	///
	QF_API IQF_DataBuffer* QF_CreateDataBufferObject(int iSize);
//}

/// \brief 数据缓存区的智能指针
/// 
/// 数据缓存区的智能指针。封装了数据缓存区对象的创建和释放，可以作为局部自动变量使用
/// 
class IQF_DataBufferPtr 
{
public :
	///	\brief 构造函数
	///
	/// 数据缓存区智能指针的构造函数
	///
	/// \param iSize：数据缓存区的初始大小。如果iSize == 0，则不进行内存分配，且GetBufferPtr() == NULL。
	///
	/// \note \e 静态连接库：QF_commontype.lib
	///	
	IQF_DataBufferPtr(int iSize)
	{
		m_ptr = QF_CreateDataBufferObject(iSize) ;
	}

	///	\brief 析构函数
	///
	/// 数据缓存区智能指针的析构函数
	///
	~IQF_DataBufferPtr()
	{
		if (m_ptr) m_ptr->Release() ;
	}

	///	\brief 指针操作符重载
	///
	/// 数据缓存区智能指针的指针操作符重载。
	///
	IQF_DataBuffer* operator->() const 
	{
		return m_ptr;
	}

	/// \brief 数据缓存区对象
	///
	/// public成员。数据缓存区智能指针的实际数据缓存区对象
	///
	IQF_DataBuffer * m_ptr ;

} ;

QF_END_NAMESPACE
#endif /* Z_QF_II_INCLUDE_IQF_DATABUFFER_H_HEADER_INCLUDED_C0630F69 */




