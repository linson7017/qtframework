/*!
 * \file qt_standard.h
 *
 * \author ����
 * \date ���� 2016
 *
 * 
 */
#pragma once

//#define USE_QCUSTOM_PLOT

#include <QIcon>
#include <QHeaderView>
#include <QLineEdit>
#include <QFrame>
#include <QDockWidget>
#ifdef USE_QCUSTOM_PLOT
#include <QCustomPlot.h>
#endif 
#include <map>
#include "Utils/variant.h"
/*!
 * \class qt_standard
 *
 * \brief qt_standard��
 *
 * \author ����
 * \date ���� 2016
 */
class qt_standard
{
public:
	//���캯��
	//��������
	//����ֵ����
	qt_standard(void);
	//��������
	//��������
	//����ֵ����
	~qt_standard(void);
	//��ñ�׼Iconʵ��
	//������
	//		name:����
	//����ֵ��QIconʵ��
	static QIcon getStandardIcon(const char* name);
	//��ñ�׼WindowFlagsʵ��
	//������
	//		name:����
	//����ֵ��WindowFlagsʵ��
	static Qt::WindowFlags getWindowType(const char* name);
	//��ñ�׼ResizeModeʵ��
	//������
	//		name:����
	//����ֵ��ResizeModeʵ��
	static QHeaderView::ResizeMode getHeaderResizeMode(const char* name);
	//��ð�����Ӧ��ֵ
	//������
	//		key:����
	//����ֵ��ֵ
	static const char* getKeySymbol(Qt::Key key);
	//��ø�����������Ӧ��ֵ
	//������
	//		m:������
	//����ֵ��ֵ
	static const char* getModifiersSymbol(Qt::KeyboardModifiers m);
	//��ñ�׼Alignmentʵ��
	//������
	//		name:����
	//����ֵ��Alignmentʵ��
	static Qt::Alignment getAlignment(const char* name);
	//��ñ�׼ToolButtonStyleʵ��
	//������
	//		name:����
	//����ֵ��ToolButtonStyleʵ��
	static Qt::ToolButtonStyle getToolButtonStyle(const char* name);
	//��ñ�׼CheckStateʵ��
	//������
	//		name:����
	//����ֵ��CheckStateʵ��
	static Qt::CheckState getCheckState(const char* name);
	//��ñ�׼QFontʵ��
	//������
	//		name:����
	//����ֵ��QFontʵ��
	static QFont getStandardFont(const char* name);
	//��ñ�׼EchoModeʵ��
	//������
	//		name:����
	//����ֵ��EchoModeʵ��
	static QLineEdit::EchoMode getEchoMode(const char* name);
	//��ñ�׼TabPositionʵ��
	//������
	//		name:����
	//����ֵ��TabPositionʵ��
	static QTabWidget::TabPosition getTabPosition(const char* name);
	//��ñ�׼Shapeʵ��
	//������
	//		name:����
	//����ֵ��Shapeʵ��
	static QFrame::Shape getFrameShape(const char* name);
	//��ñ�׼Shadowʵ��
	//������
	//		name:����
	//����ֵ��Shadowʵ��
	static QFrame::Shadow getFrameShadow(const char* name);

    static Qt::ToolBarArea getToolBarArea(const char* name);

    static Qt::DockWidgetArea getDockWidgetArea(const char* name);

    static QDockWidget::DockWidgetFeature getDockWidgetFeature(const char* name);

    static QDockWidget::DockWidgetFeatures getDockWidgetFeatures(const char* name);

    static Qt::Orientation getOrientation(const char* name);

    static QTabWidget::TabShape getTabShape(const char* name);

    static QTabWidget::TabPosition GetTabPosition(const char* name);

    static QPalette::ColorRole GetPaletteColorRole(const QString& roleStr);

    static QPalette::ColorGroup GetPaletteColorGroup(const QString& groupStr);

#ifdef USE_QCUSTOM_PLOT
	//��ñ�׼Interactionsʵ��
	//������
	//		name:����
	//����ֵ��Interactionsʵ��
	static QCP::Interactions getQCPInteractions(const char* name);
	//��ñ�׼Interactionʵ��
	//������
	//		name:����
	//����ֵ��Interactionʵ��
	static QCP::Interaction getQCPInteraction(const char* name);
#endif 

#ifndef RECOGNIZE_QPORPERTY_DISABLED
	//�������ֵ
	//������
	//		name:����
	//		v: 
	//����ֵ��Shadowʵ��
	static bool getProperty(const char* name,QVariant& v);

    static bool exchangProperty(QVariant& property,variant& varient);
#endif


private:
	//����ӳ����̵ļ�ֵ
	//��������
	//����ֵ����
	static void reMapKeyBoard();

	static std::map<Qt::Key,std::string> _keyMap;
	static std::map<Qt::KeyboardModifiers,std::string> _modifiersMap;
	static bool _bKeyBoardMaped;
};



