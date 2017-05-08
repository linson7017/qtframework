#ifndef QF_CQF_DATABUFFER_H__
#define QF_CQF_DATABUFFER_H__

#include <qfcommon/IQF_databuffer.h>

QF_BEGIN_NAMESPACE(QF)

class IQF_DataBuffer;

// 数据缓冲区类。
//##ModelId=3F9CF3D1001F
class CQF_DataBuffer : public IQF_DataBuffer
{
  public:
    //##ModelId=3F9CF3D10031
    CQF_DataBuffer();

    //##ModelId=3F9CF3D10032
    ~CQF_DataBuffer();

    // 设置缓冲区大小，单位为字节。
    //##ModelId=3F9CF3D10033
    bool SetSize(int iSize);

    // 获取缓冲区大小，单位为字节。
    //##ModelId=3F9CF3D10035
    int GetSize();

    // 获取缓冲区指针。
    //##ModelId=3F9CF3D10036
    char* GetBufferPtr();

    // 释放内存。
    //##ModelId=3F9CF3D10037
    void Release();
    //##ModelId=3FA4C73200B4
    IQF_DataBuffer& operator=(const IQF_DataBuffer& right);


    //##ModelId=3FA4C7320122
    int operator==(const IQF_DataBuffer& right);

  
    //##ModelId=3FA4C732018F
    int operator!=(const IQF_DataBuffer& right);

  private:
    //##ModelId=3F9CF3D10038
    void Clear();

    //##ModelId=3F9CF3D1002F
    int m_iSize;

    //##ModelId=3F9CF3D10030
    char* m_pBuffer;

};

QF_END_NAMESPACE

#endif
