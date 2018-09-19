#include "qt_standard.h"
#include <QApplication>
#include <QStyle>
#include <QtCore/QtCore>
#include "Utils/util.h"

std::map<Qt::Key,std::string> qt_standard::_keyMap;
std::map<Qt::KeyboardModifiers,std::string> qt_standard::_modifiersMap;
bool qt_standard::_bKeyBoardMaped=false;
//构造函数
//参数：无
//返回值：无
qt_standard::qt_standard(void)
{
}

//析构函数
//参数：无
//返回值：无
qt_standard::~qt_standard(void)
{
}
//获得标准CheckState实例
//参数：
//		name:输入
//返回值：CheckState实例
Qt::CheckState qt_standard::getCheckState(const char* name)
{
	if(strcmp(name,"Unchecked")==0)
		return Qt::Unchecked;
	else if(strcmp(name,"PartiallyChecked")==0)
		return Qt::PartiallyChecked;
	else if(strcmp(name,"Checked")==0)
		return Qt::Checked;
	else
		return (Qt::CheckState)STR_TO_INT(name);
}
//获得标准EchoMode实例
//参数：
//		name:输入
//返回值：EchoMode实例
QLineEdit::EchoMode qt_standard::getEchoMode(const char* name)
{
	if(strcmp(name,"Normal")==0)
		return QLineEdit::Normal;
	else if(strcmp(name,"NoEcho")==0)
		return QLineEdit::NoEcho;
	else if(strcmp(name,"Password")==0)
		return QLineEdit::Password;
	else if(strcmp(name,"PasswordEchoOnEdit")==0)
		return QLineEdit::PasswordEchoOnEdit;
	else
		return (QLineEdit::EchoMode)STR_TO_INT(name);
}
//获得标准TabPosition实例
//参数：
//		name:输入
//返回值：TabPosition实例
QTabWidget::TabPosition qt_standard::getTabPosition(const char* name)
{
	if(strcmp(name,"North")==0)
		return QTabWidget::North;
	else if(strcmp(name,"South")==0)
		return QTabWidget::South;
	else if(strcmp(name,"West")==0)
		return QTabWidget::West;
	else if(strcmp(name,"East")==0)
		return QTabWidget::East;
	else
		return QTabWidget::North;
}
//获得标准Shape实例
//参数：
//		name:输入
//返回值：Shape实例
QFrame::Shape qt_standard::getFrameShape(const char* name)
{
	if(strcmp(name,"NoFrame")==0)
		return QFrame::NoFrame;
	else if(strcmp(name,"Box")==0)
		return QFrame::Box;
	else if(strcmp(name,"Panel")==0)
		return QFrame::Panel;
	else if(strcmp(name,"StyledPanel")==0)
		return QFrame::StyledPanel;
	else if(strcmp(name,"HLine")==0)
		return QFrame::HLine;
	else if(strcmp(name,"VLine")==0)
		return QFrame::VLine;
	else if(strcmp(name,"WinPanel")==0)
		return QFrame::WinPanel;
	else
		return QFrame::NoFrame;
}
//获得标准Shadow实例
//参数：
//		name:输入
//返回值：Shadow实例
QFrame::Shadow qt_standard::getFrameShadow(const char* name)
{
	if(strcmp(name,"Plain")==0)
		return QFrame::Plain;
	else if(strcmp(name,"Raised")==0)
		return QFrame::Raised;
	else if(strcmp(name,"Sunken")==0)
		return QFrame::Sunken;
	else
		return QFrame::Plain;
}
//获得标准Alignment实例
//参数：
//		name:输入
//返回值：Alignment实例
Qt::Alignment qt_standard::getAlignment(const char* name)
{
	if(strcmp(name,"AlignLeft")==0)
		return Qt::AlignLeft;
	else if(strcmp(name,"AlignRight")==0)
		return Qt::AlignRight;
	else if(strcmp(name,"AlignHCenter")==0)
		return Qt::AlignHCenter;
	else if(strcmp(name,"AlignTop")==0)
		return Qt::AlignTop;
	else if(strcmp(name,"AlignBottom")==0)
		return Qt::AlignBottom;
	else if(strcmp(name,"AlignVCenter")==0)
		return Qt::AlignVCenter;
	else if(strcmp(name,"AlignCenter")==0)
		return Qt::AlignCenter;
	else if(strcmp(name,"left")==0)
		return Qt::AlignLeft;
	else if(strcmp(name,"right")==0)
		return Qt::AlignRight;
	else if(strcmp(name,"hcenter")==0)
		return Qt::AlignHCenter;
	else if(strcmp(name,"top")==0)
		return Qt::AlignTop;
	else if(strcmp(name,"bottom")==0)
		return Qt::AlignBottom;
	else if(strcmp(name,"vcenter")==0)
		return Qt::AlignVCenter;
	else if(strcmp(name,"center")==0)
		return Qt::AlignCenter;
	else 
		return (Qt::Alignment)STR_TO_INT(name);
}
//获得标准ToolButtonStyle实例
//参数：
//		name:输入
//返回值：ToolButtonStyle实例
Qt::ToolButtonStyle qt_standard::getToolButtonStyle(const char* name)
{
	if(strcmp(name,"ToolButtonIconOnly")==0)
		return Qt::ToolButtonIconOnly;
	else if(strcmp(name,"ToolButtonTextOnly")==0)
		return Qt::ToolButtonTextOnly;
	else if(strcmp(name,"ToolButtonTextBesideIcon")==0)
		return Qt::ToolButtonTextBesideIcon;
	else if(strcmp(name,"ToolButtonTextUnderIcon")==0)
		return Qt::ToolButtonTextUnderIcon;
	else
		return (Qt::ToolButtonStyle)STR_TO_INT(name);
}
//获得标准ToolBar位置
//参数：
//		name:输入
//返回值：ToolButtonStyle实例
Qt::ToolBarArea qt_standard::getToolBarArea(const char* name)
{
    if (strcmp(name, "LeftToolBarArea") == 0)
        return Qt::LeftToolBarArea;
    else if (strcmp(name, "RightToolBarArea") == 0)
        return Qt::RightToolBarArea;
    else if (strcmp(name, "TopToolBarArea") == 0)
        return Qt::TopToolBarArea;
    else if (strcmp(name, "BottomToolBarArea") == 0)
        return Qt::BottomToolBarArea;
    else if (strcmp(name, "AllToolBarAreas") == 0)
        return Qt::AllToolBarAreas;
    else if (strcmp(name, "NoToolBarArea") == 0)
        return Qt::NoToolBarArea;
    else
        return (Qt::ToolBarArea)STR_TO_INT(name);
}


Qt::DockWidgetArea qt_standard::getDockWidgetArea(const char* name)
{
    if (strcmp(name, "LeftDockWidgetArea") == 0 || strcmp(name, "Left") == 0)
        return Qt::LeftDockWidgetArea;
    else if (strcmp(name, "RightDockWidgetArea") == 0 || strcmp(name, "Right") == 0)
        return Qt::RightDockWidgetArea;
    else if (strcmp(name, "TopToolBarArea") == 0 || strcmp(name, "Top") == 0)
        return Qt::TopDockWidgetArea;
    else if (strcmp(name, "BottomDockWidgetArea") == 0 || strcmp(name, "Bottom") == 0)
        return Qt::BottomDockWidgetArea;
    else if (strcmp(name, "AllDockWidgetAreas") == 0 || strcmp(name, "All") == 0)
        return Qt::AllDockWidgetAreas;
    else if (strcmp(name, "NoDockWidgetArea") == 0 || strcmp(name, "No") == 0)
        return Qt::NoDockWidgetArea;
    else
        return (Qt::DockWidgetArea)STR_TO_INT(name);
}

QTabWidget::TabShape qt_standard::getTabShape(const char* name)
{
    if (strcmp(name, "Rounded") == 0|| strcmp(name, "R") == 0)
        return QTabWidget::Rounded;
    else if (strcmp(name, "Triangular") == 0|| strcmp(name, "T") == 0)
        return QTabWidget::Triangular;
    else
        return (QTabWidget::TabShape)STR_TO_INT(name);
}

QTabWidget::TabPosition qt_standard::GetTabPosition(const char* name)
{
    if (strcmp(name, "North") == 0|| strcmp(name, "Top") == 0)
        return QTabWidget::North;
    else if (strcmp(name, "South") == 0 || strcmp(name, "Bottom") == 0)
        return QTabWidget::South;
    if (strcmp(name, "West") == 0 || strcmp(name, "Left") == 0)
        return QTabWidget::West;
    else if (strcmp(name, "East") == 0 || strcmp(name, "Right") == 0)
        return QTabWidget::East;
    else
        return (QTabWidget::TabPosition)STR_TO_INT(name);
}

QDockWidget::DockWidgetFeature qt_standard::getDockWidgetFeature(const char* name)
{
    if (strcmp(name, "DockWidgetClosable") == 0)
        return QDockWidget::DockWidgetClosable;
    else if (strcmp(name, "DockWidgetMovable") == 0)
        return QDockWidget::DockWidgetMovable;
    else if (strcmp(name, "DockWidgetFloatable") == 0)
        return QDockWidget::DockWidgetFloatable;
    else if (strcmp(name, "DockWidgetVerticalTitleBar") == 0)
        return QDockWidget::DockWidgetVerticalTitleBar;
    else if (strcmp(name, "AllDockWidgetFeatures") == 0)
        return QDockWidget::AllDockWidgetFeatures;
    else if (strcmp(name, "NoDockWidgetFeatures") == 0)
        return QDockWidget::NoDockWidgetFeatures;
    else
        return QDockWidget::AllDockWidgetFeatures;
}

QDockWidget::DockWidgetFeatures qt_standard::getDockWidgetFeatures(const char* name)
{
    QDockWidget::DockWidgetFeatures flags = QDockWidget::NoDockWidgetFeatures;
    QStringList flagsStr = QString(name).split("|");
    for (int i=0;i<flagsStr.size();i++)
    {
        flags |= getDockWidgetFeature(flagsStr.at(i).toStdString().c_str());
    }
    return flags;
}


Qt::Orientation qt_standard::getOrientation(const char* name)
{
    if (strcmp(name, "Horizontal") == 0)
        return Qt::Horizontal;
    else if (strcmp(name, "Vertical") == 0)
        return Qt::Vertical;
    else
        return Qt::Horizontal;
}

//获得标准Icon实例
//参数：
//		name:输入
//返回值：QIcon实例
QIcon qt_standard::getStandardIcon(const char* name)
{
	if (strcmp(name,"MediaPlay")==0)
		return QApplication::style()->standardIcon(QStyle::SP_MediaPlay);
	else if (strcmp(name,"MediaPause")==0)
		return QApplication::style()->standardIcon(QStyle::SP_MediaPause);
	else if (strcmp(name,"DialogOpenButton")==0)
		return QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton);
	else if (strcmp(name,"MediaSkipBackward")==0)
		return QApplication::style()->standardIcon(QStyle::SP_MediaSkipBackward);
	else if (strcmp(name,"MediaSkipForward")==0)
		return QApplication::style()->standardIcon(QStyle::SP_MediaSkipForward);
	else if (strcmp(name,"MediaStop")==0)
		return QApplication::style()->standardIcon(QStyle::SP_MediaStop);
	else
		return QApplication::style()->standardIcon(QStyle::SP_CustomBase);
}

//获得标准WindowFlags实例
//参数：
//		name:输入
//返回值：WindowFlags实例
Qt::WindowFlags qt_standard::getWindowType(const char* name)
{
	if (strcmp(name,"FixedSize")==0)
	{
		return Qt::MSWindowsFixedSizeDialogHint;
	}
	else if (strcmp(name,"Frameless")==0)
	{
		return Qt::FramelessWindowHint;
	}
	else if (strcmp(name,"Customize")==0)
	{
		return Qt::CustomizeWindowHint;
	}
	else if (strcmp(name,"MinMaxButton")==0)
	{
		return Qt::WindowMinMaxButtonsHint;
	}
	else if (strcmp(name,"MinimizeButton")==0)
	{
		return Qt::WindowMinimizeButtonHint;
	}
	else if (strcmp(name,"MaximizeButton")==0)
	{
		return Qt::WindowMaximizeButtonHint;
	}
	else if (strcmp(name,"StayOnTop")==0)
	{
		return Qt::WindowStaysOnTopHint;
	}
	else if (strcmp(name,"StayOnBottom")==0)
	{
		return Qt::WindowStaysOnBottomHint;
	}
	else if (strcmp(name,"SystemMenu")==0)
	{
		return Qt::WindowSystemMenuHint;
	}
	else if (strcmp(name,"WindowTitle")==0)
	{
		return Qt::WindowTitleHint;
	}
	else
	{
		return Qt::Widget;
	}
}

//获得标准ResizeMode实例
//参数：
//		name:输入
//返回值：ResizeMode实例
QHeaderView::ResizeMode qt_standard::getHeaderResizeMode(const char* name)
{
	if (strcmp(name,"Interactive")==0)
	{
		return QHeaderView::Interactive;
	}
	else if (strcmp(name,"Fixed")==0)
	{
		return QHeaderView::Fixed;
	}
	else if (strcmp(name,"Stretch")==0)
	{
		return QHeaderView::Stretch;
	}
	else if (strcmp(name,"ResizeToContents")==0)
	{
		return QHeaderView::ResizeToContents;
	}
	else
		return QHeaderView::Interactive;
}
//获得按键对应的值
//参数：
//		key:按键
//返回值：值
const char* qt_standard::getKeySymbol(Qt::Key key)
{
	if (!_bKeyBoardMaped)
	{
		reMapKeyBoard();
	}
	std::map<Qt::Key,std::string>::iterator it = _keyMap.find(key);
	if (it != _keyMap.end())
	{
		return it->second.c_str();
	}else
	{
		return "";
	}
}
//获得辅助键按键对应的值
//参数：
//		m:辅助键
//返回值：值
const char* qt_standard::getModifiersSymbol(Qt::KeyboardModifiers m)
{
	if (!_bKeyBoardMaped)
	{
		reMapKeyBoard();
	}
	std::map<Qt::KeyboardModifiers,std::string>::iterator it = _modifiersMap.find(m);
	if (it != _modifiersMap.end())
	{
		return it->second.c_str();
	}else
	{
		return "";
	}
}
//获得标准QFont实例
//参数：
//		name:输入
//返回值：QFont实例
QFont qt_standard::getStandardFont(const char* name)
{
	std::vector<std::string> fontStrVec;
	std::string fontStr = name;
	splitString(fontStr,fontStrVec,";;");
	QFont font;
	int size = fontStrVec.size();
	switch (size)
	{
	case 4:
		font.setFamily(fontStrVec[3].c_str());
	case 3:
		font.setItalic(STR_TO_BOOL(fontStrVec[2].c_str()));
	case 2:
		font.setBold(STR_TO_BOOL(fontStrVec[1].c_str()));
	case 1:
		font.setPixelSize(STR_TO_INT(fontStrVec[0].c_str()));
	}
	return font;
}

#ifndef RECOGNIZE_QPORPERTY_DISABLED
bool qt_standard::exchangProperty(QVariant& property, variant& varient)
{
    switch (property.type())
    {
    case QVariant::Int:
        varient.setInt(property.value<int>());
        return true;
    case QVariant::Double:
        varient.setDouble(property.value<double>());
        return true;
    case QVariant::Bool:
        varient.setBool(property.value<bool>());
        return true;
    case QVariant::String:
        varient.setString(property.value<QString>().toStdString().c_str());
        return true;
    default:
        return false;
    }
}

QPalette::ColorGroup qt_standard::GetPaletteColorGroup(const QString& groupStr)
{
    if (groupStr.compare("Disabled") == 0)
    {
        return QPalette::Disabled;
    }
    else if (groupStr.compare("Active") == 0|| groupStr.compare("Normal") == 0)
    {
        return QPalette::Active;
    }
    else if (groupStr.compare("Inactive") == 0)
    {
        return QPalette::Inactive;
    }
    else if (groupStr.compare("NColorGroups") == 0)
    {
        return QPalette::NColorGroups;
    }
    else if (groupStr.compare("Current") == 0)
    {
        return QPalette::Current;
    }
    else 
    {
        return QPalette::All;
    }
}

QPalette::ColorRole qt_standard::GetPaletteColorRole(const QString& roleStr)
{
    if (roleStr.compare("alternate-base") == 0)
    {
        return QPalette::AlternateBase;
    }
    else if (roleStr.compare("base") == 0)
    {
        return QPalette::Base;
    }
    else if (roleStr.compare("bright-text") == 0)
    {
        return QPalette::BrightText;
    }
    else if (roleStr.compare("button") == 0)
    {
        return QPalette::Button;
    }
    else if (roleStr.compare("button-text") == 0)
    {
        return QPalette::ButtonText;
    }
    else if (roleStr.compare("dark") == 0)
    {
        return QPalette::Dark;
    }
    else if (roleStr.compare("highlight") == 0)
    {
        return QPalette::Highlight;
    }
    else if (roleStr.compare("highlighted-text") == 0)
    {
        return QPalette::HighlightedText;
    }
    else if (roleStr.compare("light") == 0)
    {
        return QPalette::Light;
    }
    else if (roleStr.compare("link") == 0)
    {
        return QPalette::Link;
    }
    else if (roleStr.compare("link-visited") == 0)
    {
        return QPalette::LinkVisited;
    }
    else if (roleStr.compare("mid") == 0)
    {
        return QPalette::Mid;
    }
    else if (roleStr.compare("midlight") == 0)
    {
        return QPalette::Midlight;
    }
    else if (roleStr.compare("shadow") == 0)
    {
        return QPalette::Shadow;
    }
    else if (roleStr.compare("text") == 0)
    {
        return QPalette::Text;
    }
    else if (roleStr.compare("window") == 0)
    {
        return QPalette::Window;
    }
    else if (roleStr.compare("window-text") == 0)
    {
        return QPalette::WindowText;
    }
    else
    {
        return QPalette::NoRole;
    }
}

//获得属性值
//参数：
//		name:输入
//		v: 
//返回值：Shadow实例
bool qt_standard::getProperty(const char* name,QVariant& v)
{
	QString str = name;
	int i = str.indexOf(":");
	if (i!=-1)
	{
		QString typeStr = str.left(i);
		QString valueStr = str.mid(i+1);
		QVariant::Type type = QVariant::nameToType(typeStr.toLocal8Bit().constData());
		switch (type)
		{
		case QVariant::Int:
			v.setValue(valueStr.toInt());
			break;
		case QVariant::Double:
			v.setValue(valueStr.toDouble());
			break;
		case QVariant::Bool:
			v.setValue(STR_TO_BOOL(valueStr.toLocal8Bit().constData()));
			break;
		case QVariant::String:
			v.setValue(valueStr);
			break;
		case QVariant::StringList:
			{
				QStringList strlist = valueStr.split(";;");
				v.setValue(strlist);
			}
			break;
		case QVariant::Size:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QSize size(strlist.at(0).toInt(),strlist.at(1).toInt());
					v.setValue(size);
				}
			}
			break;
		case QVariant::Point:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QPoint point(strlist.at(0).toInt(),strlist.at(1).toInt());
					v.setValue(point);
				}
			}
			break;
		case QVariant::SizeF:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QPointF pointf(strlist.at(0).toDouble(),strlist.at(1).toDouble());
					v.setValue(pointf);
				}
			}
			break;
		case QVariant::PointF:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QSizeF sizef(strlist.at(0).toDouble(),strlist.at(1).toDouble());
					v.setValue(sizef);
				}
			}
			break;
		case QVariant::Rect:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QRect rect(strlist.at(0).toInt(),strlist.at(1).toInt(),
						strlist.at(2).toInt(),strlist.at(3).toInt());
					v.setValue(rect);
				}
			}
			break;
		case QVariant::RectF:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QRectF rectf(strlist.at(0).toDouble(),strlist.at(1).toDouble(),
						strlist.at(2).toDouble(),strlist.at(3).toDouble());
					v.setValue(rectf);
				}
			}
			break;
		case QVariant::Region:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==2)
				{
					QRegion region(strlist.at(0).toInt(),strlist.at(1).toInt(),
						strlist.at(2).toInt(),strlist.at(3).toInt());
					v.setValue(region);
				}
			}
			break;
		case QVariant::Font:
			{
				QFont font;
				QStringList strlist = valueStr.split(",");
				int size = strlist.size();
				switch (size)
				{
				case 4:
					font.setFamily(strlist.at(3));
				case 3:
					font.setPointSize(strlist.at(2).toInt());
				case 2:
					font.setWeight(strlist.at(1).toInt());
				case 1:
					font.setBold(STR_TO_BOOL(strlist.at(0).toLocal8Bit().constData()));
				default:
					break;
				}
				v.setValue(font);
			}
			break;
		case QVariant::Icon:
			{
				QIcon icon;
				if (fileOrPahtExist(valueStr.toLocal8Bit().constData()))
				{
					icon.addFile(valueStr);
				}
				else
				{
					std::string iconUrl;
					getResImageOrIconUrl(iconUrl,valueStr.toStdString());
					icon.addFile(iconUrl.c_str());
				}
				v.setValue(icon);
			}
			break;
		case QVariant::Pixmap:
			{
				QPixmap pixMap;
				if (fileOrPahtExist(valueStr.toLocal8Bit().constData()))
				{
					pixMap.load(valueStr);
				}
				else
				{
					std::string iconUrl;
					getResImageOrIconUrl(iconUrl,valueStr.toStdString());
					pixMap.load(iconUrl.c_str());
				}
				v.setValue(pixMap);
			}
			break;
		case QVariant::Image:
			{
				QImage image;
				if (fileOrPahtExist(valueStr.toLocal8Bit().constData()))
				{
					image.load(valueStr);
				}
				else
				{
					std::string iconUrl;
					getResImageOrIconUrl(iconUrl,valueStr.toStdString());
					image.load(iconUrl.c_str());
				}
				v.setValue(image);
			}
			break;
		case QVariant::Palette:
			{
				QStringList strlist = valueStr.split(",");
				QColor color;
				int size = strlist.size();
				switch (size)
				{
				case 4:
					color.setAlpha(strlist.at(3).toUInt());
				case 3:
					color.setBlue(strlist.at(2).toUInt());
				case 2:
					color.setGreen(strlist.at(1).toUInt());
				case 1:
					color.setRed(strlist.at(0).toUInt());
				default:
					break;
				}
				QPalette palette(color);
				v.setValue(palette);
			}
			break;
		case QVariant::Locale:
			{
				QLocale locale(valueStr);
				v.setValue(locale);
			}
			break;
		case QVariant::Date:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==3)
				{
					QDate date(strlist.at(0).toInt(),strlist.at(1).toInt(),strlist.at(2).toInt());
					v.setValue(date);
				}
			}
			break;
		case QVariant::Time:
			{
				QStringList strlist = valueStr.split(",");
				if (strlist.size()==3)
				{
					QTime time(strlist.at(0).toInt(),strlist.at(1).toInt(),strlist.at(2).toInt(),0);
					v.setValue(time);
				}
			}
			break;
		case QVariant::UInt:
			v.setValue(valueStr.toUInt());
			break;
		case QVariant::Invalid:
			return false;
		default:
			return false;
		}
	}
    else
    {
        return false;
    }
	return true;
}
#endif


//重新映射键盘的键值
//参数：无
//返回值：无
void qt_standard::reMapKeyBoard()
{
	
	_keyMap[Qt::Key_Escape]="Key_Escape";
	_keyMap[Qt::Key_Tab]="Key_Tab";
	_keyMap[Qt::Key_Backtab]="Key_Backtab";
	_keyMap[Qt::Key_Backspace]="Key_Backspace";
	_keyMap[Qt::Key_Return]="Key_Return";
	_keyMap[Qt::Key_Enter]="Key_Enter";
	_keyMap[Qt::Key_Insert]="Key_Insert";
	_keyMap[Qt::Key_Delete]="Key_Delete";
	_keyMap[Qt::Key_Pause]="Key_Pause";
	_keyMap[Qt::Key_Print]="Key_Print";
	_keyMap[Qt::Key_SysReq]="Key_SysReq";
	_keyMap[Qt::Key_Clear]="Key_Clear";
	_keyMap[Qt::Key_Home]="Key_Home";
	_keyMap[Qt::Key_End]="Key_End";
	_keyMap[Qt::Key_Left]="Key_Left";
	_keyMap[Qt::Key_Up]="Key_Up";
	_keyMap[Qt::Key_Right]="Key_Right";
	_keyMap[Qt::Key_Down]="Key_Down";
	_keyMap[Qt::Key_PageUp]="Key_PageUp";
	_keyMap[Qt::Key_PageDown]="Key_PageDown";
	_keyMap[Qt::Key_Shift]="Key_Shift";
	_keyMap[Qt::Key_Control]="Key_Control";
	_keyMap[Qt::Key_Meta]="Key_Meta";
	_keyMap[Qt::Key_Alt]="Key_Alt";
	_keyMap[Qt::Key_AltGr]="Key_AltGr";
	_keyMap[Qt::Key_CapsLock]="Key_CapsLock";
	_keyMap[Qt::Key_NumLock]="Key_NumLock";
	_keyMap[Qt::Key_ScrollLock]="Key_ScrollLock";
	_keyMap[Qt::Key_F1]="Key_F1";
	_keyMap[Qt::Key_F2]="Key_F2";
	_keyMap[Qt::Key_F3]="Key_F3";
	_keyMap[Qt::Key_F4]="Key_F4";
	_keyMap[Qt::Key_F5]="Key_F5";
	_keyMap[Qt::Key_F6]="Key_F6";
	_keyMap[Qt::Key_F7]="Key_F7";
	_keyMap[Qt::Key_F8]="Key_F8";
	_keyMap[Qt::Key_F9]="Key_F9";
	_keyMap[Qt::Key_F10]="Key_F10";
	_keyMap[Qt::Key_F11]="Key_F11";
	_keyMap[Qt::Key_F12]="Key_F12";
	_keyMap[Qt::Key_F13]="Key_F13";
	_keyMap[Qt::Key_F14]="Key_F14";
	_keyMap[Qt::Key_F15]="Key_F15";
	_keyMap[Qt::Key_F16]="Key_F16";
	_keyMap[Qt::Key_F17]="Key_F17";
	_keyMap[Qt::Key_F18]="Key_F18";
	_keyMap[Qt::Key_F19]="Key_F19";
	_keyMap[Qt::Key_F20]="Key_F20";
	_keyMap[Qt::Key_F21]="Key_F21";
	_keyMap[Qt::Key_F22]="Key_F22";
	_keyMap[Qt::Key_F23]="Key_F23";
	_keyMap[Qt::Key_F24]="Key_F24";
	_keyMap[Qt::Key_F25]="Key_F25";
	_keyMap[Qt::Key_F26]="Key_F26";
	_keyMap[Qt::Key_F27]="Key_F27";
	_keyMap[Qt::Key_F28]="Key_F28";
	_keyMap[Qt::Key_F29]="Key_F29";
	_keyMap[Qt::Key_F30]="Key_F30";
	_keyMap[Qt::Key_F31]="Key_F31";
	_keyMap[Qt::Key_F32]="Key_F32";
	_keyMap[Qt::Key_F33]="Key_F33";
	_keyMap[Qt::Key_F34]="Key_F34";
	_keyMap[Qt::Key_F35]="Key_F35";
	_keyMap[Qt::Key_Super_L]="Key_Super_L";
	_keyMap[Qt::Key_Super_R]="Key_Super_R";
	_keyMap[Qt::Key_Menu]="Key_Menu";
	_keyMap[Qt::Key_Hyper_L]="Key_Hyper_L";
	_keyMap[Qt::Key_Hyper_R]="Key_Hyper_R";
	_keyMap[Qt::Key_Help]="Key_Help";
	_keyMap[Qt::Key_Direction_L]="Key_Direction_L";
	_keyMap[Qt::Key_Direction_R]="Key_Direction_R";
	_keyMap[Qt::Key_Space]="Key_Space";
	_keyMap[Qt::Key_Any]="Key_Space";
	_keyMap[Qt::Key_Exclam]="Key_Exclam";
	_keyMap[Qt::Key_QuoteDbl]="Key_QuoteDbl";
	_keyMap[Qt::Key_NumberSign]="Key_NumberSign";
	_keyMap[Qt::Key_Dollar]="Key_Dollar";
	_keyMap[Qt::Key_Percent]="Key_Percent";
	_keyMap[Qt::Key_Ampersand]="Key_Ampersand";
	_keyMap[Qt::Key_Apostrophe]="Key_Apostrophe";
	_keyMap[Qt::Key_ParenLeft]="Key_ParenLeft";
	_keyMap[Qt::Key_ParenRight]="Key_ParenRight";
	_keyMap[Qt::Key_Asterisk]="Key_Asterisk";
	_keyMap[Qt::Key_Plus]="Key_Plus";
	_keyMap[Qt::Key_Comma]="Key_Comma";
	_keyMap[Qt::Key_Minus]="Key_Minus";
	_keyMap[Qt::Key_Period]="Key_Period";
	_keyMap[Qt::Key_Slash]="Key_Slash";
	_keyMap[Qt::Key_0]="Key_0";
	_keyMap[Qt::Key_1]="Key_1";
	_keyMap[Qt::Key_2]="Key_2";
	_keyMap[Qt::Key_3]="Key_3";
	_keyMap[Qt::Key_4]="Key_4";
	_keyMap[Qt::Key_5]="Key_5";
	_keyMap[Qt::Key_6]="Key_6";
	_keyMap[Qt::Key_7]="Key_7";
	_keyMap[Qt::Key_8]="Key_8";
	_keyMap[Qt::Key_9]="Key_9";
	_keyMap[Qt::Key_Colon]="Key_Colon";
	_keyMap[Qt::Key_Semicolon]="Key_Semicolon";
	_keyMap[Qt::Key_Less]="Key_Less";
	_keyMap[Qt::Key_Equal]="Key_Equal";
	_keyMap[Qt::Key_Greater]="Key_Greater";
	_keyMap[Qt::Key_Question]="Key_Question";
	_keyMap[Qt::Key_At]="Key_At";
	_keyMap[Qt::Key_A]="Key_A";
	_keyMap[Qt::Key_B]="Key_B";
	_keyMap[Qt::Key_C]="Key_C";
	_keyMap[Qt::Key_D]="Key_D";
	_keyMap[Qt::Key_E]="Key_E";
	_keyMap[Qt::Key_F]="Key_F";
	_keyMap[Qt::Key_G]="Key_G";
	_keyMap[Qt::Key_H]="Key_H";
	_keyMap[Qt::Key_I]="Key_I";
	_keyMap[Qt::Key_J]="Key_J";
	_keyMap[Qt::Key_K]="Key_K";
	_keyMap[Qt::Key_L]="Key_L";
	_keyMap[Qt::Key_M]="Key_M";
	_keyMap[Qt::Key_N]="Key_N";
	_keyMap[Qt::Key_O]="Key_O";
	_keyMap[Qt::Key_P]="Key_P";
	_keyMap[Qt::Key_Q]="Key_Q";
	_keyMap[Qt::Key_R]="Key_R";
	_keyMap[Qt::Key_S]="Key_S";
	_keyMap[Qt::Key_T]="Key_T";
	_keyMap[Qt::Key_U]="Key_U";
	_keyMap[Qt::Key_V]="Key_V";
	_keyMap[Qt::Key_W]="Key_W";
	_keyMap[Qt::Key_X]="Key_X";
	_keyMap[Qt::Key_Y]="Key_Y";
	_keyMap[Qt::Key_Z]="Key_Z";
	_keyMap[Qt::Key_BracketLeft]="Key_BracketLeft";
	_keyMap[Qt::Key_Backslash]="Key_Backslash";
	_keyMap[Qt::Key_BracketRight]="Key_BracketRight";
	_keyMap[Qt::Key_AsciiCircum]="Key_AsciiCircum";
	_keyMap[Qt::Key_Underscore]="Key_Underscore";
	_keyMap[Qt::Key_QuoteLeft]="Key_QuoteLeft";
	_keyMap[Qt::Key_BraceLeft]="Key_BraceLeft";
	_keyMap[Qt::Key_Bar]="Key_Bar";
	_keyMap[Qt::Key_BraceRight]="Key_BraceRight";
	_keyMap[Qt::Key_AsciiTilde]="Key_AsciiTilde";
	_keyMap[Qt::Key_nobreakspace]="Key_nobreakspace";
	_keyMap[Qt::Key_exclamdown]="Key_exclamdown";
	_keyMap[Qt::Key_cent]="Key_cent";
	_keyMap[Qt::Key_sterling]="Key_sterling";
	_keyMap[Qt::Key_currency]="Key_currency";
	_keyMap[Qt::Key_yen]="Key_yen";
	_keyMap[Qt::Key_brokenbar]="Key_brokenbar";
	_keyMap[Qt::Key_section]="Key_section";
	_keyMap[Qt::Key_diaeresis]="Key_diaeresis";
	_keyMap[Qt::Key_copyright]="Key_copyright";
	_keyMap[Qt::Key_ordfeminine]="Key_ordfeminine";
	_keyMap[Qt::Key_guillemotleft]="Key_guillemotleft";
	_keyMap[Qt::Key_notsign]="Key_notsign";
	_keyMap[Qt::Key_hyphen]="Key_hyphen";
	_keyMap[Qt::Key_registered]="Key_registered";
	_keyMap[Qt::Key_macron]="Key_macron";
	_keyMap[Qt::Key_degree]="Key_degree";
	_keyMap[Qt::Key_plusminus]="Key_plusminus";
	_keyMap[Qt::Key_twosuperior]="Key_twosuperior";
	_keyMap[Qt::Key_threesuperior]="Key_threesuperior";
	_keyMap[Qt::Key_acute]="Key_acute";
	_keyMap[Qt::Key_mu]="Key_mu";
	_keyMap[Qt::Key_paragraph]="Key_paragraph";
	_keyMap[Qt::Key_periodcentered]="Key_periodcentered";
	_keyMap[Qt::Key_cedilla]="Key_cedilla";
	_keyMap[Qt::Key_onesuperior]="Key_onesuperior";
	_keyMap[Qt::Key_masculine]="Key_masculine";
	_keyMap[Qt::Key_guillemotright]="Key_guillemotright";
	_keyMap[Qt::Key_onequarter]="Key_onequarter";
	_keyMap[Qt::Key_onehalf]="Key_onehalf";
	_keyMap[Qt::Key_threequarters]="Key_threequarters";
	_keyMap[Qt::Key_questiondown]="Key_questiondown";
	_keyMap[Qt::Key_Agrave]="Key_Agrave";
	_keyMap[Qt::Key_Aacute]="Key_Aacute";
	_keyMap[Qt::Key_Acircumflex]="Key_Acircumflex";
	_keyMap[Qt::Key_Atilde]="Key_Atilde";
	_keyMap[Qt::Key_Adiaeresis]="Key_Adiaeresis";
	_keyMap[Qt::Key_Aring]="Key_Aring";
	_keyMap[Qt::Key_AE]="Key_AE";
	_keyMap[Qt::Key_Ccedilla]="Key_Ccedilla";
	_keyMap[Qt::Key_Egrave]="Key_Egrave";
	_keyMap[Qt::Key_Eacute]="Key_Eacute";
	_keyMap[Qt::Key_Ecircumflex]="Key_Ecircumflex";
	_keyMap[Qt::Key_Ediaeresis]="Key_Ediaeresis";
	_keyMap[Qt::Key_Igrave]="Key_Igrave";
	_keyMap[Qt::Key_Iacute]="Key_Iacute";
	_keyMap[Qt::Key_Icircumflex]="Key_Icircumflex";
	_keyMap[Qt::Key_Idiaeresis]="Key_Idiaeresis";
	_keyMap[Qt::Key_ETH]="Key_ETH";
	_keyMap[Qt::Key_Ntilde]="Key_Ntilde";
	_keyMap[Qt::Key_Ograve]="Key_Ograve";
	_keyMap[Qt::Key_Oacute]="Key_Oacute";
	_keyMap[Qt::Key_Ocircumflex]="Key_Ocircumflex";
	_keyMap[Qt::Key_Otilde]="Key_Otilde";
	_keyMap[Qt::Key_Odiaeresis]="Key_Odiaeresis";
	_keyMap[Qt::Key_multiply]="Key_multiply";
	_keyMap[Qt::Key_Ooblique]="Key_Ooblique";
	_keyMap[Qt::Key_Ugrave]="Key_Ugrave";
	_keyMap[Qt::Key_Uacute]="Key_Uacute";
	_keyMap[Qt::Key_Ucircumflex]="Key_Ucircumflex";
	_keyMap[Qt::Key_Udiaeresis]="Key_Udiaeresis";
	_keyMap[Qt::Key_Yacute]="Key_Yacute";
	_keyMap[Qt::Key_THORN]="Key_THORN";
	_keyMap[Qt::Key_ssharp]="Key_ssharp";
	_keyMap[Qt::Key_division]="Key_division";
	_keyMap[Qt::Key_ydiaeresis]="Key_ydiaeresis";
	_keyMap[Qt::Key_Multi_key]="Key_Multi_key";
	_keyMap[Qt::Key_Codeinput]="Key_Codeinput";
	_keyMap[Qt::Key_SingleCandidate]="Key_SingleCandidate";
	_keyMap[Qt::Key_MultipleCandidate]="Key_MultipleCandidate";
	_keyMap[Qt::Key_PreviousCandidate]="Key_PreviousCandidate";
	_keyMap[Qt::Key_Mode_switch]="Key_Mode_switch";
	_keyMap[Qt::Key_Kanji]="Key_Kanji";
	_keyMap[Qt::Key_Muhenkan]="Key_Muhenkan";
	_keyMap[Qt::Key_Henkan]="Key_Henkan";
	_keyMap[Qt::Key_Romaji]="Key_Romaji";
	_keyMap[Qt::Key_Hiragana]="Key_Hiragana";
	_keyMap[Qt::Key_Katakana]="Key_Katakana";
	_keyMap[Qt::Key_Hiragana_Katakana]="Key_Hiragana_Katakana";
	_keyMap[Qt::Key_Zenkaku]="Key_Zenkaku";
	_keyMap[Qt::Key_Hankaku]="Key_Hankaku";
	_keyMap[Qt::Key_Zenkaku_Hankaku]="Key_Zenkaku_Hankaku";
	_keyMap[Qt::Key_Touroku]="Key_Touroku";
	_keyMap[Qt::Key_Massyo]="Key_Massyo";
	_keyMap[Qt::Key_Kana_Lock]="Key_Kana_Lock";
	_keyMap[Qt::Key_Kana_Shift]="Key_Kana_Shift";
	_keyMap[Qt::Key_Eisu_Shift]="Key_Eisu_Shift";
	_keyMap[Qt::Key_Eisu_toggle]="Key_Eisu_toggle";
	_keyMap[Qt::Key_Hangul]="Key_Hangul";
	_keyMap[Qt::Key_Hangul_Start]="Key_Hangul_Start";
	_keyMap[Qt::Key_Hangul_End]="Key_Hangul_End";
	_keyMap[Qt::Key_Hangul_Hanja]="Key_Hangul_Hanja";
	_keyMap[Qt::Key_Hangul_Jamo]="Key_Hangul_Jamo";
	_keyMap[Qt::Key_Hangul_Romaja]="Key_Hangul_Romaja";
	_keyMap[Qt::Key_Hangul_Jeonja]="Key_Hangul_Jeonja";
	_keyMap[Qt::Key_Hangul_Banja]="Key_Hangul_Banja";
	_keyMap[Qt::Key_Hangul_PreHanja]="Key_Hangul_PreHanja";
	_keyMap[Qt::Key_Hangul_PostHanja]="Key_Hangul_PostHanja";
	_keyMap[Qt::Key_Hangul_Special]="Key_Hangul_Special";
	_keyMap[Qt::Key_Dead_Grave]="Key_Dead_Grave";
	_keyMap[Qt::Key_Dead_Acute]="Key_Dead_Acute";
	_keyMap[Qt::Key_Dead_Circumflex]="Key_Dead_Circumflex";
	_keyMap[Qt::Key_Dead_Tilde]="Key_Dead_Tilde";
	_keyMap[Qt::Key_Dead_Macron]="Key_Dead_Macron";
	_keyMap[Qt::Key_Dead_Breve]="Key_Dead_Breve";
	_keyMap[Qt::Key_Dead_Abovedot]="Key_Dead_Abovedot";
	_keyMap[Qt::Key_Dead_Diaeresis]="Key_Dead_Diaeresis";
	_keyMap[Qt::Key_Dead_Abovering]="Key_Dead_Abovering";
	_keyMap[Qt::Key_Dead_Doubleacute]="Key_Dead_Doubleacute";
	_keyMap[Qt::Key_Dead_Caron]="Key_Dead_Caron";
	_keyMap[Qt::Key_Dead_Cedilla]="Key_Dead_Cedilla";
	_keyMap[Qt::Key_Dead_Ogonek]="Key_Dead_Ogonek";
	_keyMap[Qt::Key_Dead_Iota]="Key_Dead_Iota";
	_keyMap[Qt::Key_Dead_Voiced_Sound]="Key_Dead_Voiced_Sound";
	_keyMap[Qt::Key_Dead_Semivoiced_Sound]="Key_Dead_Semivoiced_Sound";
	_keyMap[Qt::Key_Dead_Belowdot]="Key_Dead_Belowdot";
	_keyMap[Qt::Key_Dead_Hook]="Key_Dead_Hook";
	_keyMap[Qt::Key_Dead_Horn]="Key_Dead_Horn";
	_keyMap[Qt::Key_Back]="Key_Back";
	_keyMap[Qt::Key_Forward]="Key_Forward";
	_keyMap[Qt::Key_Stop]="Key_Stop";
	_keyMap[Qt::Key_Refresh]="Key_Refresh";
	_keyMap[Qt::Key_VolumeDown]="Key_VolumeDown";
	_keyMap[Qt::Key_VolumeMute]="Key_VolumeMute";
	_keyMap[Qt::Key_VolumeUp]="Key_VolumeUp";
	_keyMap[Qt::Key_BassBoost]="Key_BassBoost";
	_keyMap[Qt::Key_BassUp]="Key_BassUp";
	_keyMap[Qt::Key_BassDown]="Key_BassDown";
	_keyMap[Qt::Key_TrebleUp]="Key_TrebleUp";
	_keyMap[Qt::Key_TrebleDown]="Key_TrebleDown";
	_keyMap[Qt::Key_MediaPlay]="Key_MediaPlay";
	_keyMap[Qt::Key_MediaStop]="Key_MediaStop";
	_keyMap[Qt::Key_MediaPrevious]="Key_MediaPrevious";
	_keyMap[Qt::Key_MediaNext]="Key_MediaNext";
	_keyMap[Qt::Key_MediaRecord]="Key_MediaRecord";
	_keyMap[Qt::Key_MediaPause]="Key_MediaPause";
	_keyMap[Qt::Key_MediaTogglePlayPause]="Key_MediaTogglePlayPause";
	_keyMap[Qt::Key_HomePage]="Key_HomePage";
	_keyMap[Qt::Key_Favorites]="Key_Favorites";
	_keyMap[Qt::Key_Search]="Key_Search";
	_keyMap[Qt::Key_Standby]="Key_Standby";
	_keyMap[Qt::Key_OpenUrl]="Key_OpenUrl";
	_keyMap[Qt::Key_LaunchMail]="Key_LaunchMail";
	_keyMap[Qt::Key_LaunchMedia]="Key_LaunchMedia";
	_keyMap[Qt::Key_Launch0]="Key_Launch0";
	_keyMap[Qt::Key_Launch1]="Key_Launch1";
	_keyMap[Qt::Key_Launch2]="Key_Launch2";
	_keyMap[Qt::Key_Launch3]="Key_Launch3";
	_keyMap[Qt::Key_Launch4]="Key_Launch4";
	_keyMap[Qt::Key_Launch5]="Key_Launch5";
	_keyMap[Qt::Key_Launch6]="Key_Launch6";
	_keyMap[Qt::Key_Launch7]="Key_Launch7";
	_keyMap[Qt::Key_Launch8]="Key_Launch8";
	_keyMap[Qt::Key_Launch9]="Key_Launch9";
	_keyMap[Qt::Key_LaunchA]="Key_LaunchA";
	_keyMap[Qt::Key_LaunchB]="Key_LaunchB";
	_keyMap[Qt::Key_LaunchC]="Key_LaunchC";
	_keyMap[Qt::Key_LaunchD]="Key_LaunchD";
	_keyMap[Qt::Key_LaunchE]="Key_LaunchE";
	_keyMap[Qt::Key_LaunchF]="Key_LaunchF";
	_keyMap[Qt::Key_LaunchG]="Key_LaunchG";
	_keyMap[Qt::Key_LaunchH]="Key_LaunchH";
	_keyMap[Qt::Key_MonBrightnessUp]="Key_MonBrightnessUp";
	_keyMap[Qt::Key_MonBrightnessDown]="Key_MonBrightnessDown";
	_keyMap[Qt::Key_KeyboardLightOnOff]="Key_KeyboardLightOnOff";
	_keyMap[Qt::Key_KeyboardBrightnessUp]="Key_KeyboardBrightnessUp";
	_keyMap[Qt::Key_KeyboardBrightnessDown]="Key_KeyboardBrightnessDown";
	_keyMap[Qt::Key_PowerOff]="Key_PowerOff";
	_keyMap[Qt::Key_WakeUp]="Key_WakeUp";
	_keyMap[Qt::Key_Eject]="Key_Eject";
	_keyMap[Qt::Key_ScreenSaver]="Key_ScreenSaver";
	_keyMap[Qt::Key_WWW]="Key_WWW";
	_keyMap[Qt::Key_Memo]="Key_Memo";
	_keyMap[Qt::Key_LightBulb]="Key_LightBulb";
	_keyMap[Qt::Key_Shop]="Key_Shop";
	_keyMap[Qt::Key_History]="Key_History";
	_keyMap[Qt::Key_AddFavorite]="Key_AddFavorite";
	_keyMap[Qt::Key_HotLinks]="Key_HotLinks";
	_keyMap[Qt::Key_BrightnessAdjust]="Key_BrightnessAdjust";
	_keyMap[Qt::Key_Finance]="Key_Finance";
	_keyMap[Qt::Key_Community]="Key_Community";
	_keyMap[Qt::Key_AudioRewind]="Key_AudioRewind";
	_keyMap[Qt::Key_BackForward]="Key_BackForward";
	_keyMap[Qt::Key_ApplicationLeft]="Key_ApplicationLeft";
	_keyMap[Qt::Key_ApplicationRight]="Key_ApplicationRight";
	_keyMap[Qt::Key_Book]="Key_Book";
	_keyMap[Qt::Key_CD]="Key_CD";
	_keyMap[Qt::Key_Calculator]="Key_Calculator";
	_keyMap[Qt::Key_ToDoList]="Key_ToDoList";
	_keyMap[Qt::Key_ClearGrab]="Key_ClearGrab";
	_keyMap[Qt::Key_Close]="Key_Close";
	_keyMap[Qt::Key_Copy]="Key_Copy";
	_keyMap[Qt::Key_Cut]="Key_Cut";
	_keyMap[Qt::Key_Display]="Key_Display";
	_keyMap[Qt::Key_DOS]="Key_DOS";
	_keyMap[Qt::Key_Documents]="Key_Documents";
	_keyMap[Qt::Key_Excel]="Key_Excel";
	_keyMap[Qt::Key_Explorer]="Key_Explorer";
	_keyMap[Qt::Key_Game]="Key_Game";
	_keyMap[Qt::Key_Go]="Key_Go";
	_keyMap[Qt::Key_iTouch]="Key_iTouch";
	_keyMap[Qt::Key_LogOff]="Key_LogOff";
	_keyMap[Qt::Key_Market]="Key_Market";
	_keyMap[Qt::Key_Meeting]="Key_Meeting";
	_keyMap[Qt::Key_MenuKB]="Key_MenuKB";
	_keyMap[Qt::Key_MenuPB]="Key_MenuPB";
	_keyMap[Qt::Key_MySites]="Key_MySites";
	_keyMap[Qt::Key_News]="Key_News";
	_keyMap[Qt::Key_OfficeHome]="Key_OfficeHome";
	_keyMap[Qt::Key_Option]="Key_Option";
	_keyMap[Qt::Key_Paste]="Key_Paste";
	_keyMap[Qt::Key_Phone]="Key_Phone";
	_keyMap[Qt::Key_Calendar]="Key_Calendar";
	_keyMap[Qt::Key_Reply]="Key_Reply";
	_keyMap[Qt::Key_Reload]="Key_Reload";
	_keyMap[Qt::Key_RotateWindows]="Key_RotateWindows";
	_keyMap[Qt::Key_RotationPB]="Key_RotationPB";
	_keyMap[Qt::Key_RotationKB]="Key_RotationKB";
	_keyMap[Qt::Key_Save]="Key_Save";
	_keyMap[Qt::Key_Send]="Key_Send";
	_keyMap[Qt::Key_Spell]="Key_Spell";
	_keyMap[Qt::Key_SplitScreen]="Key_SplitScreen";
	_keyMap[Qt::Key_Support]="Key_Support";
	_keyMap[Qt::Key_TaskPane]="Key_TaskPane";
	_keyMap[Qt::Key_Terminal]="Key_Terminal";
	_keyMap[Qt::Key_Tools]="Key_Tools";
	_keyMap[Qt::Key_Travel]="Key_Travel";
	_keyMap[Qt::Key_Video]="Key_Video";
	_keyMap[Qt::Key_Word]="Key_Word";
	_keyMap[Qt::Key_Xfer]="Key_Xfer";
	_keyMap[Qt::Key_ZoomIn]="Key_ZoomIn";
	_keyMap[Qt::Key_ZoomOut]="Key_ZoomOut";
	_keyMap[Qt::Key_Away]="Key_Away";
	_keyMap[Qt::Key_Messenger]="Key_Messenger";
	_keyMap[Qt::Key_WebCam]="Key_WebCam";
	_keyMap[Qt::Key_MailForward]="Key_MailForward";
	_keyMap[Qt::Key_Pictures]="Key_Pictures";
	_keyMap[Qt::Key_Music]="Key_Music";
	_keyMap[Qt::Key_Battery]="Key_Battery";
	_keyMap[Qt::Key_Bluetooth]="Key_Bluetooth";
	_keyMap[Qt::Key_WLAN]="Key_WLAN";
	_keyMap[Qt::Key_UWB]="Key_UWB";
	_keyMap[Qt::Key_AudioForward]="Key_AudioForward";
	_keyMap[Qt::Key_AudioRepeat]="Key_AudioRepeat";
	_keyMap[Qt::Key_AudioRandomPlay]="Key_AudioRandomPlay";
	_keyMap[Qt::Key_Subtitle]="Key_Subtitle";
	_keyMap[Qt::Key_AudioCycleTrack]="Key_AudioCycleTrack";
	_keyMap[Qt::Key_Time]="Key_Time";
	_keyMap[Qt::Key_Hibernate]="Key_Hibernate";
	_keyMap[Qt::Key_View]="Key_View";
	_keyMap[Qt::Key_TopMenu]="Key_TopMenu";
	_keyMap[Qt::Key_PowerDown]="Key_PowerDown";
	_keyMap[Qt::Key_Suspend]="Key_Suspend";
	_keyMap[Qt::Key_ContrastAdjust]="Key_ContrastAdjust";
	_keyMap[Qt::Key_MediaLast]="Key_MediaLast";
	_keyMap[Qt::Key_unknown]="Key_unknown";
	_keyMap[Qt::Key_Call]="Key_Call";
	_keyMap[Qt::Key_Camera]="Key_Camera";
	_keyMap[Qt::Key_CameraFocus]="Key_CameraFocus";
	_keyMap[Qt::Key_Context1]="Key_Context1";
	_keyMap[Qt::Key_Context2]="Key_Context2";
	_keyMap[Qt::Key_Context3]="Key_Context3";
	_keyMap[Qt::Key_Context4]="Key_Context4";
	_keyMap[Qt::Key_Flip]="Key_Flip";
	_keyMap[Qt::Key_Hangup]="Key_Hangup";
	_keyMap[Qt::Key_No]="Key_No";
	_keyMap[Qt::Key_Select]="Key_Select";
	_keyMap[Qt::Key_Yes]="Key_Yes";
	_keyMap[Qt::Key_ToggleCallHangup]="Key_ToggleCallHangup";
	_keyMap[Qt::Key_VoiceDial]="Key_VoiceDial";
	_keyMap[Qt::Key_LastNumberRedial]="Key_LastNumberRedial";
	_keyMap[Qt::Key_Execute]="Key_Execute";
	_keyMap[Qt::Key_Printer]="Key_Printer";
	_keyMap[Qt::Key_Play]="Key_Play";
	_keyMap[Qt::Key_Sleep]="Key_Sleep";
	_keyMap[Qt::Key_Zoom]="Key_Zoom";
	_keyMap[Qt::Key_Cancel]="Key_Cancel";
	//辅助键
	_modifiersMap[Qt::ShiftModifier]="Key_Shift+";
	_modifiersMap[Qt::ControlModifier]="Key_Control+";
	_modifiersMap[Qt::AltModifier]="Key_Alt+";
	_modifiersMap[Qt::AltModifier|Qt::ShiftModifier]="Key_Alt+Key_Shift+";
	_modifiersMap[Qt::AltModifier|Qt::ControlModifier]="Key_Alt+Key_Control+";
	_modifiersMap[Qt::ControlModifier|Qt::ShiftModifier]="Key_Shift+Key_Control+";
	_modifiersMap[Qt::AltModifier|Qt::ControlModifier|Qt::ShiftModifier]="Key_Alt+Key_Shift+Key_Control+";


	_bKeyBoardMaped = true;
}


#ifdef USE_QCUSTOM_PLOT
//获得标准Interactions实例
//参数：
//		name:输入
//返回值：Interactions实例
QCP::Interactions qt_standard::getQCPInteractions(const char* name)
{
	std::vector<std::string> fontStrVec;
	std::string fontStr = name;
	splitString(fontStr,fontStrVec,";;");

	QCP::Interactions qcpInteractions = 0x0000;
	for (int i=0;i<fontStrVec.size();i++)
	{
		qcpInteractions |= qt_standard::getQCPInteraction(fontStrVec.at(i).c_str());
	}
	return qcpInteractions;
}
//获得标准Interaction实例
//参数：
//		name:输入
//返回值：Interaction实例
QCP::Interaction qt_standard::getQCPInteraction(const char* name)
{
	if (strcmp(name,"RangeDrag")==0)
	{
		return QCP::iRangeDrag;
	}
	else if (strcmp(name,"RangeZoom")==0)
	{
		return QCP::iRangeZoom;
	}
	else if (strcmp(name,"MultiSelect")==0)
	{
		return QCP::iMultiSelect;
	}
	else if (strcmp(name,"SelectPlottables")==0)
	{
		return QCP::iSelectPlottables;
	}
	else if (strcmp(name,"SelectAxes")==0)
	{
		return QCP::iSelectAxes;
	}
	else if (strcmp(name,"SelectLegend")==0)
	{
		return QCP::iSelectLegend;
	}
	else if (strcmp(name,"SelectItems")==0)
	{
		return QCP::iSelectItems;
	}
	else if (strcmp(name,"SelectOther")==0)
	{
		return QCP::iSelectOther;
	}
	else
		return QCP::iRangeDrag;;
}

#endif 
