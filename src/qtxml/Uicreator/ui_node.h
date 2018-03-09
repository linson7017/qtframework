/*!
 * \file ui_node.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once

//#include <string>
#include <list>
#include "Uicreator/xml_node.h"
//#include <map>


using namespace std;
/*!
 * \class ui_node
 *
 * \brief ui_node��
 *
 * \author ����
 * \date ���� 2016
 */
class ui_node : public xml_node
{
public:
	//�ڵ�����
	enum NodeType
	{
		WIDGET, //�ؼ�����
		LAYOUT, //��������
		ITEM,   //��Ŀ����
		ITEMS,  //��Ŀ��������
		CONTAINER, //��������
		CUSTOMER,  //�û��Զ�������
        UNKNOWN
	};
	//���캯��
	//��������
	//����ֵ����
	ui_node();
    //���ƹ��캯��
    //��������
    //����ֵ����
    ui_node(const ui_node& node);
	//��������
	//��������
	//����ֵ����
	~ui_node();
	//�ͷŽڵ㼰�ӽڵ�
	//��������
	//����ֵ����
	virtual void release(); //20150925
	//����ӽڵ�
	//������
	//		node: �ӽڵ�ָ��
	//����ֵ����
	virtual void addChild(ui_node* node);
	//����ӽڵ�
	//������
	//		index: �ӽڵ�����
	//����ֵ���ӽڵ�ָ��
	virtual ui_node* getChild(int index);
	//���ø��ڵ�
	//������
	//		node: ���ڵ�ָ��
	//����ֵ����
	virtual void setParent(ui_node* node);
	//��ø��ڵ�
	//��������
	//����ֵ�����ڵ�ָ��
	virtual ui_node* getParent();
	//����ӽڵ�����
	//��������
	//����ֵ���ӽڵ�����
	virtual int getChildNum(){return _uiChildren.size();}
	//���ýڵ�����
	//������
	//		type: �ڵ�����
	//����ֵ����
	virtual void setType(NodeType type){_type = type;}
	//��ýڵ�����
	//��������
	//����ֵ���ڵ�����
	virtual NodeType getType(){return _type;}
	//��ýڵ��������ָ��
	//��������
	//����ֵ����������ָ��
    virtual void* getObject(const char* name="");
	//���ýڵ��������ָ��
	//������
	//		object����������ָ��
	//����ֵ����
    virtual void setObject(void* object,const char* name="");
	//���ƽڵ�
	//������
	//		node: Ҫ���ƵĽڵ�ָ��
	//����ֵ����
	virtual void clone(ui_node* node);
protected:
	//�ϲ��������Ա�
	//������
	//		ta: Ŀ�����Ա�
	//		fa: Դ���Ա�
	//����ֵ����
	void mergeAttributes(AttributeMapType& ta,AttributeMapType& fa);

private:
	list<ui_node*> _uiChildren; 
	ui_node* _uiParent;
	NodeType _type;
    typedef std::map<std::string, void*> ObjectMapType;
    ObjectMapType _objects;
    std::string _uiName;
};

