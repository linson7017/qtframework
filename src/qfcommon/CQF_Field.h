#ifndef QF_CQF_FIELD_H__
#define QF_CQF_FIELD_H__

#include <qfcommon/IQF_field.h>

QF_BEGIN_NAMESPACE(QF)

// 一个元数据字段的信息。
// 可以作为元数据表的一列的描述；
// 可以作为属性表的一列的描述。
//##ModelId=3F90F92C018D
class CQF_Field : public IQF_Field
{
  public:
    // 获取字段名称
    //##ModelId=3F90F92C01EA
    const char* GetName();

    // 获取字段数据库类型
    //##ModelId=3F90F92C01EB
    int GetType();

    // 获取字段种类
    //##ModelId=3F90F92C01EC
    const char* GetStereoType();

    // 获取字段的长度（字节数）。
    // 整型：4bytes
    // 浮点型：8bytes
    // 时戳型：sizeof(SQF_Time) bytes
    // 字符串：strlen + 1 bytes
    // 二进制：4bytes  //指针
    // 参数集：4bytes  //指针
    // 数组：4bytes  //指针
    //##ModelId=3F90F92C01ED
    unsigned int GetLength();

    // 判断字段值是否可以为空
    //##ModelId=3F90F92C01F8
    bool IsNullable();



    // 获取字段标题
    //##ModelId=3F90F92C01FB
    const char* GetCaption();

    // 获取字段描述
    //##ModelId=3F90F92C01FC
    const char* GetDesc();


    // 设置字段名称。
    // 
    // 《说明》
    // 字段名称不能修改，只能初始化
    //##ModelId=3F90F92C01FE
    bool SetName(const char* szName);

    // 设置字段类型。
    // 
    // 《说明》
    // 字段类型不能修改，只能初始化
    //##ModelId=3F90F92C0208
    bool SetType(int type);

    // 设置字段种类。
    // 
    // 《说明》
    // 字段种类不能修改，只能初始化
    //##ModelId=3F90F92C020A
    bool SetStereoType(const char* szStereoType);

    // 设置字段值是否能够为空。
    // 
    // 《说明》
    // 不能修改，只能初始化
    //##ModelId=3F90F92C020E
    bool SetNullable(bool bNullable = true);

    // 设置字段标题。
    // 
    // 《说明》
    // 字段标题可以修改
    //##ModelId=3F90F92C021A
    bool SetCaption(const char* szCaption);

    // 设置字段描述。
    // 
    // 《说明》
    // 字段描述可以修改。
    // 对于表达式，其定义是否允许修改？
    //##ModelId=3F90F92C021C
    bool SetDesc(const char* szDesc);

    // 获取字段的整数值。
    // 如果改值还未被设置，则返回0 。
    //##ModelId=3F90F92C0228
    int GetInt();

    // 获取字段的浮点数值。
    // 如果改值还未被设置，则返回0 。
    //##ModelId=3F90F92C0229
    double GetDouble();

    // 获取字段的字符串值。
    // 如果改值还未被设置，则返回空字符串""。
    //##ModelId=3F90F92C022A
    const char* GetString();

    // 以字符串的形式获取字段值。
    //##ModelId=3F90F92C022B
    bool GetValueAsString(char* szValueString,int iLength);

    // 设置字段的整数值。
    //##ModelId=3F90F92C022D
    bool SetInt(int iValue);

    // 设置字段的浮点数值。
    //##ModelId=3F90F92C0237
    bool SetDouble(double dValue);

    // 设置字段的字符串值。
    //##ModelId=3F90F92C0239
    bool SetString(const char* szValue);

    // 以字符串的形式设置字段值。
    //##ModelId=3F90F92C023B
    bool SetValueAsString(const char* szValueString);

    // 判断字段值是否为空。
    //##ModelId=3F90F92C023D
    bool IsNull();

    // 将字段值设为空值。
    //##ModelId=3F90F92C023E
    bool SetToNull(bool bIsNull = true);

    //##ModelId=3F90FD54013B
    CQF_Field();

    //##ModelId=3F90FD590199
    ~CQF_Field();

    //##ModelId=3F910CAD00FD
    void Release();

    //##ModelId=3F9CF4D6007D
 //   bool Archive(IQF_DataBuffer* pDataBuffer, int iMode, int iType);

    // 获取字段数据的外部类型。
    //##ModelId=3F9E33E0028F
    int GetExtType();

    // 设置字段外部类型。
    //##ModelId=3F9E33E002AE
    void SetExtType(int ExtType);

    //##ModelId=3FA4B94603E5
    IQF_Field& operator=(const IQF_Field& right);

    //##ModelId=3FA4B94700A9
    int operator==(const IQF_Field& right);

    //##ModelId=3FA4B9470154
    int operator!=(const IQF_Field& right);

    // 清除本对象的所有数据.
    //##ModelId=3FA4B9CB02B0
    void Clear();

    // 初始化.
    //##ModelId=3FA4BA0B0070
    void Init();

    // 获取字段的数组接口指针。
    // 如果改值还未被设置，则返回空。
    //##ModelId=3FA8EC2F0297
//    IQF_Array* GetArray();

    // 获取字段的属性集合接口指针。
    // 如果改值还未被设置，则返回空。
    //##ModelId=3FA8EC2F02F4
//    IQF_PropertySet* GetPropertySet();

    // 获取字段的二进制数据接口指针。
    // 如果改值还未被设置，则返回空。
    //##ModelId=3FACC22A01C8
//    IQF_DataBuffer* GetBinary();
    
	//##ModelId=4035D1E80251
//    bool ArchiveField(IQF_DataBuffer* pDataBuffer, int iMode, int iType);
    
	//##ModelId=4042A6800396
//    bool IsToBeArchive();

    //##ModelId=4042A69E02FB
//    bool SetToBeArchive(bool bToBeArchive = true);

    //##ModelId=4042A6D103E7
    bool GetBool();

    //##ModelId=4042A6E40119
    bool SetBool(bool bValue);

    //##ModelId=405AB05A014D
    bool IsDeletable();

    //##ModelId=405AB0A20381
    bool IsUpdatable();

    //##ModelId=405AB0740341
    bool IsIndexable();

    //##ModelId=405AB08E02F4
    bool IsIndex();

    //##ModelId=405AB1040076
    bool SetDeletable(bool bDeletable = true);

    //##ModelId=405AB17902DB
    bool SetUpdatable(bool bUpdatable = true);

    //##ModelId=405AB119023C
    bool SetIndexable(bool bIndexable = true);

    //##ModelId=405AB18F00A9
    bool SetToBeIndex(bool bToBeIndex = false);

    //##ModelId=40721588036B
//    SQF_Time GetTime();

    //##ModelId=4072159A008D
//    bool SetTime(SQF_Time sTime);

    // 设置字段定义长度。只能初始化，不能修改。
    //##ModelId=40BC28F30316
    bool SetDefLength(int iDefLength);

    // 获取字段定义长度。未设置时为0（缺省值）。
    //##ModelId=40BC28F30318
    int GetDefLength();

    //##ModelId=40C9A8EC0336
 //   const char* GetReferencedString(int* piType, int* piSubType);

    //##ModelId=40C9A91F027B
  //  bool SetReferencedString(int iType, int iSubType, const char* szPath);

  private:
    // 字段名称
    //##ModelId=3F90F92C019A
    char* m_szName;

    // 字段数据类型。
    //##ModelId=3F90F92C01AA
    int m_iType;

    // 字段种类，即字段表现给用户的逻辑类型。
    // 
    // 8bits整型
    // 0：基本数据类型，即数据类型同数据库列的数据类型，其真实数据直接存放在相应的列中；
    // 1：多媒体类型，即数据类型为int，值为多媒体项的mid，其真实数据存放于多媒体库中；
    // 2：表达式类型，即数据类型为string，值为NULL，其真实数据由表达式计算而得；表达式定义有字段描述决定；
    // 3-7预留。
    //##ModelId=3F90F92C01BA
    char* m_szStereoType;

/*
    // 字段的定义的最大长度（字节数）。
    // 
    // 仅对字符串和二进制流有效。
    // 
    // 整型：4bytes
    // 浮点型：8bytes
    // 时戳型：20bytes
    // 字符串：n bytes
    // 二进制：m bytes  //longraw、binary
    // 大字段：4bytes  //指针
    //##ModelId=3F90F92C01BB
    unsigned int m_uiLength;
*/




    // 字段标题
    //##ModelId=3F90F92C01D9
    char* m_szCaption;

    // 字段描述信息。
    // 对于表达式类型，该描述是表达式的定义。
    //##ModelId=3F90F92C01DA
    char* m_szDesc;


    //##ModelId=3F90F92C01E9
    void* m_pValue;
    // 字段外部数据类型。
    //##ModelId=3F9E340A0231
    int m_iExtType;
    // 包括所有bool型标志：
    // 0x 0000 0001: 是否能够为空
    // 0x 0000 0002: 是否为空
    // 0x 0000 0004: 是否能够作为索引
    // 0x 0000 0008: 是否作为索引
    // 0x 0000 0010: 是否能够被修改
    // 0x 0000 0020: 是否能够被删除
    // 0x 0000 0040: 是否需要被Achive
    //##ModelId=405AAF180076
    int m_iFlags;
    // 字段的定义的最大长度（字节数）。
    // 
    // 仅对字符串和二进制流有效。
    // 
    // 整型：4bytes
    // 浮点型：8bytes
    // 时戳型：20bytes
    // 字符串：n bytes
    // 二进制：m bytes  //longraw、binary
    // 大字段：4bytes  //指针
    //##ModelId=3F90F92C01BB
    unsigned int m_uiLength;

};

QF_END_NAMESPACE
#endif

