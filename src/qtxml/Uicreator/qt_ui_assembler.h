/*!
 * \file qt_ui_assembler.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once
#include "ui_node.h"

class xml_ui_paser;
class event_handler;
class sl_MutexButtonBox;
class AView;
namespace QF
{
    class QF_Plugin;
}
/*!
 * \class qt_ui_assembler
 *
 * \brief qt_ui_assembler��
 *
 * \author ����
 * \date ���� 2016
 */
class qt_ui_assembler
{
public:
	//���캯��
	//������
	//		root: �ڵ����ĸ��ڵ�
	//����ֵ����
	qt_ui_assembler();
	//��������
	//��������
	//����ֵ����
	~qt_ui_assembler(void);
	//��װ
	//��������
	//����ֵ����
	void assemble();
	//��ø��ڵ��������
	//��������
	//����ֵ�����ڵ��������
	void* getRootObject();
	//��ø��ڵ����
	//��������
	//����ֵ�����ڵ����
	ui_node* getUINodeTreeRoot(){return _root;}
	//��ø��ڵ�����
	//��������
	//����ֵ���ڵ�����
	ui_node::NodeType getRootType();
	//��ö���ָ��
	//������
	//		id: ����id
	//����ֵ������ָ��
	void* getObjectByID(const char* id);
	//����¼�������
	//��������
	//����ֵ���¼�������ָ��
	void* getEventHandler();
    void setupUITree(ui_node* node);
protected:
	//�����ڵ���
	//������
	//	node: ���ڵ�ָ��
	//����ֵ����
	void parseUITree(ui_node* node);
    void assembleUITree(ui_node* node);
    
	//����ÿ���ڵ��ʵ��
	//������
	//	node: ���ڵ�ָ��
	//����ֵ����
	bool createUI(ui_node* node);										//����ÿ���ڵ��ʵ��
	//����Widget���ͽڵ�Ĺ�������
	//������
	//	node: ���ڵ�ָ��
	//����ֵ����
	void ParseWidgetCommonAttribute(ui_node* node);						//����Widget���ͽڵ�Ĺ�������
	//����Layout���ͽڵ�Ĺ�������
	//������
	//	node: ���ڵ�ָ��
	//����ֵ����
	void ParseLayoutCommonAttribute(ui_node* node);						//����Layout���ͽڵ�Ĺ�������
	//�����ڵ��QProperty
	//������
	//	node: ���ڵ�ָ��
	//����ֵ����
	void ParseObjectProperty(ui_node* node);							//�����ڵ��QProperty


	//װ���ӽڵ�͸��ڵ�
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleNodes(ui_node* father,ui_node* child);					
	//װ��Layout��Widget����Layout��Layout
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleLayoutAndWidgetOrLayout(ui_node* father,ui_node* child);	//װ��Layout��Widget����Layout��Layout
	//װ��Widget��Layout
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleWidgetAndLayout(ui_node* father,ui_node* child);			//װ��Widget��Layout
	//װ��Container��Widget
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleContainerAndWidget(ui_node* father,ui_node* child);		//װ��Container��Widget
	//װ��Widget��Widget
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleWidgetAndWidget(ui_node* father,ui_node* child);			//װ��Widget��Widget
	//װ��Widget��Items
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleWidgetAndItems(ui_node* father,ui_node* child);			//װ��Widget��Items
	//װ��Widget��Item
	//������
	//		father: ���ڵ�ָ��
	//		child: �ӽڵ�
	//����ֵ����
	void assembleWidgetAndItem(ui_node* father,ui_node* child);			//װ��Widget��Item

	//��ui_node�ڵ��object����
	//������
	//		object:object����ָ��
	//		node: �ڵ�ָ��
	//����ֵ���Ƿ�����ɹ�
	bool bindObjectWithNode(void* object,ui_node* node);					//��ui_node�ڵ��object����
	//IDע��
	//������
	//		node: �ڵ�ָ��
	//����ֵ����
	void registerID(ui_node* node);
	
	

private:
	ui_node* _root;
	event_handler* _event_handler;
	typedef std::map<std::string, void*> IDObjectMapType;
	IDObjectMapType _IDMap;

    typedef std::map<std::string, QF::QF_Plugin*> PluginMapType;
    PluginMapType _pluginMap;
};



