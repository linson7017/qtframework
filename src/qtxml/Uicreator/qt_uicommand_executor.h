/*!
 * \file qt_uicommand_executor.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once

class ui_node;
class xml_node;

/*!
 * \class qt_uicommand_executor
 *
 * \brief qt_uicommand_executor��
 *			����UI����Ϣ
 *
 * \author ����
 * \date ���� 2016
 */
class qt_uicommand_executor
{
public:
	//���캯��
	//��������
	//����ֵ����
	qt_uicommand_executor(void);
	//��������
	//��������
	//����ֵ����
	~qt_uicommand_executor(void);
	//ִ��xml_node��������
	//������
	//		node: xml_node����ָ��
	//����ֵ���Ƿ�ִ�гɹ�
	static bool executeCommand(xml_node* node);
    //ִ������
    //������
    //		uicommand: uicommand���ͽڵ�ָ��
    //		sender: ��Ϣ������
    //����ֵ���Ƿ�ִ�гɹ�
    static bool execute(xml_node* uicommand, ui_node* sender);
	
};

