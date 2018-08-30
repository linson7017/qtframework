/*!
 * \file Activity.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#ifndef ACTIVITY_H
#define ACTIVITY_H

#pragma once
#include <QtGui>
#include <QWidget>
#include <string.h>
#include "Common/qtxml_com.h"
class ui_node;
class qt_ui_assembler;
class SplashWindow;
/*!
 * \class Activity
 *
 * \brief Activity��
 *
 * \author ����
 * \date ���� 2016
 */
class QTXML_EXPORT Activity : /*private*/public QWidget  //����˽�м̳У���װQt����
{
	Q_OBJECT
public:
	//��ʾģʽ
	enum ShowMode
	{
		NORMAL,
		MAXIMIZED,
		MINIMIZED,
		FULL_SCREEN,
		EXTERNAL_DEFINED
	};
	//λ��
	enum Alignment
	{
		LEFT,
		RIGHT,
		BOTTOM,
		TOP,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER
	};
	//���캯��
	//��������
	//����ֵ����
	Activity(void);
	//���캯��
	//������
	//		parent:������ָ��
	//����ֵ����
	Activity(Activity* parent);
	//���캯��
	//������
	//		id:����id
	//����ֵ����
	Activity(const char* id);
	//���캯��
	//������
	//		id:����id
	//		parent:������ָ��
	//����ֵ����
	Activity(const char* id, Activity* parent);
	//���캯��
	//������
	//		pSplashWindow:SplashWindow
	//����ֵ����
	Activity(SplashWindow* pSplashWindow);
	////��������
	//��������
	//����ֵ����
	virtual ~Activity(void);
	//���ô������ݶ�Ӧ��xml�ĵ�
	//������
	//		layout_filename:�����ļ�·��
	//����ֵ���Ƿ����óɹ�
	virtual bool setContentView(const char* layout_filename);	
	//�ڴ��ڴ���֮ǰ����Ϊ,��д��
	//��������
	//����ֵ���Ƿ����óɹ�
	virtual bool actionBeforeCreated(){return true;}
	//�ڴ��ڴ���֮�����Ϊ,��д��
	//��������
	//����ֵ���Ƿ����óɹ�
	virtual bool actionAfterCreated(){return true;}
	//�ڴ��ڼ���֮ǰ����Ϊ,��д��
	//��������
	//����ֵ���Ƿ����óɹ�
	virtual bool actionBeforeActived(){return true;}
	//�ڴ��ڼ���֮�����Ϊ,��д��
	//��������
	//����ֵ���Ƿ����óɹ�
	virtual bool actionAfterActived(){return true;}
	//�ڴ��ڹر�֮ǰ����Ϊ,��д��
	//��������
	//����ֵ���Ƿ����óɹ�
	virtual bool actionBeforeClosed(){return true;}
	//�����ʾģʽ
	//������
	//����ֵ����ʾģʽ
	ShowMode showMode(){return _showMode;}
	//������ʾģʽ
	//������
	//		mode����ʾģʽ
	//����ֵ����
	virtual void setShowMode(ShowMode mode){_showMode = mode;}
	//������ʾģʽ
	//������
	//		title�����ڱ���
	//����ֵ����
	virtual void setTitle(const char* title);
	//��ÿؼ�����
	//������
	//		id��ID
	//����ֵ���ؼ�����ָ��
	void* getViewByID(const char* id);
	//�������е�����
	//������
	//����ֵ����
	void activateAllContainers();
	//��������
	//������
	//		id������ID
	//����ֵ����
	void activateContainer(const char* id);
	//��������
	//��������
	//����ֵ��id
	const char* getID(){return _id.c_str();}
	//���ô���id
	//������
	//		id��ID
	//����ֵ����
	void setID(const char* id){_id = id;}
	//���ô���λ��
	//������
	//		align��λ��
	//����ֵ����
	void setAlignment(Alignment align);
	//��ô��ڳ�ʼ���
	//������
	//����ֵ����ʼ���
	int getInitWidth(){return _initWidth;}
	//��ô��ڳ�ʼ�߶�
	//������
	//����ֵ����ʼ�߶�
	int getInitHeight(){return _initHeight;}
	//����SplashWindow
	//������
	//		pSplashWindow��SplashWindow
	//		bShowSplashWindow���Ƿ�ʹ��SplashWindow
	//����ֵ����ʼ�߶�
	void setSplashWindow(SplashWindow* pSplashWindow,bool bShowSplashWindow = true)
	{
		_splashWindow = pSplashWindow;
		_bShowSplashWindow = bShowSplashWindow;
	}
    void setup();
	friend class SplashWindow;
public slots:
	//��ʾ����
	//��������
	//����ֵ����ʾ�ɹ�����true
	virtual bool active();
	//�����ʾ����
	//��������
	//����ֵ����
	virtual void activeMaximized();
	//��С����ʾ����
	//��������
	//����ֵ����
	virtual void activeMinimized();
	//��ʾ����
	//��������
	//����ֵ����
	virtual void activeNormal();
	//ȫ����ʾ����
	//��������
	//����ֵ����
	virtual void activeFullScreen();
protected:
	//�ر��¼�
	//������
	//		ev���¼�
	//����ֵ���Ƿ����óɹ�
    void closeEvent(QCloseEvent *ev);
	//��װ��������
	//��������
	//����ֵ����
	virtual void installContent();
	//׼��UI
	//��������
	//����ֵ���ɹ�����true,���򷵻�false
	bool prepareUI();
	//��ʾ����
	//������
	//		mode����ʾģʽ
	//����ֵ���ɹ�����true,���򷵻�false
	virtual bool active(ShowMode mode);
	//������ʾ֮ǰ�������ڵ����ʾ����
	//������
	//		attr���ڵ�ָ��
	//����ֵ����
	void parseShowModeBeforeActived(ui_node* attr);
	//void parseShowModeAfterActived(ui_node* attr);
	//��ʾ��ʾ��Ϣ
	//������
	//		szMessage:��ʾ��Ϣ
	//����ֵ����
	void showSplashMessage(const char* szMessage);

	ui_node* _content; //�������ݣ�������������
	qt_ui_assembler* _assembler;
	std::string _id;
	std::string _layout_filename;
	ShowMode _showMode;
	bool _bPrepared;
	bool _bParsed;
	int _initPosX;
	int _initPosY;
	int _initWidth;
	int _initHeight;

	SplashWindow* _splashWindow;
	bool _bShowSplashWindow;

};

#endif

