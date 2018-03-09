/*!
 * \file qt_command_executor.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once

#include <QtCore/QObject>
class ui_node;
class xml_node;

/*!
 * \class qt_command_executor
 *
 * \brief qt_command_executor��
	����������Ϣ
 *
 * \author ����
 * \date ���� 2016
 */
namespace QF
{
    class IQF_Properties;
    class IQF_Main_Ext;
}

class qt_command_executor : public QObject
{
	Q_OBJECT
public:
	//���캯��
	//��������
	//����ֵ����
	qt_command_executor(void);
	//��������
	//��������
	//����ֵ����
	~qt_command_executor(void);
	//ִ��ui_node��������
	//������
	//		node: ui_node����ָ��
	//����ֵ���Ƿ�ִ�гɹ�
	//static bool executeCommand(ui_node* node);
	//ִ��xml_node��������
	//������
	//		node: xml_node����ָ��
	//����ֵ���Ƿ�ִ�гɹ�
	static bool executeCommand(xml_node* node);

private:
    static void parseCommandProperty(xml_node* commandNode, QF::IQF_Properties* properties,xml_node* sender);
    static void setProperty(QF::IQF_Properties* properties,const char* name, const QVariant& v);
};

