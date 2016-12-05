#include "res_style.h"

#include <Uicreator/xml_node.h>
#include "Common/app_env.h"
#include "Utils/util.h"
//构造函数
//参数：无
//返回值：无
res_style::res_style(void)
{
	string styleDir = app_env::getDir(app_env::STYLE_RESOURCE);
	std::vector<std::string> files;
	getAllFilesInCurrentDir(styleDir,files,"*.xml");
	std::vector<std::string>::const_iterator it;

	for (it = files.begin(); it != files.end(); ++it )
	{
		string filepath = styleDir;
		filepath.append(*it);
		parseStyleXML(filepath.c_str());
	}
}

//析构函数
//参数：无
//返回值：无
res_style::~res_style(void)
{
}
//解析内容
//参数：icontent 输入内容, ocontent 输出内容, name 节点Name
//返回值：输出字符
const char* res_style::parseContent(string& ocontent,const char* icontent,const char* name)
{
	if (strcmp(name,"border-image")==0||strcmp(name,"background-image")==0)
	{
		ocontent="url(";
		std::string temp;
		getResImageOrIconUrl(temp,icontent);
		ocontent.append(temp.c_str());
		ocontent.append(")");
		return ocontent.c_str();
	}else
	{
		return icontent;
	}
}
//解析配置文件xml
//参数：filename 文件路径
//返回值：无
const char* res_style::parseStyleXML(const char* filename)
{
	xmlKeepBlanksDefault(0);
	xmlDocPtr doc;
	doc = xmlReadFile(filename,"utf-8",XML_PARSE_READER);
	if (doc == NULL)
	{
		xmlFreeDoc(doc);
		return "";
	}
	xmlNodePtr curXMLNode = xmlDocGetRootElement(doc);
	if (strcmp((const char*)curXMLNode->name,"styles")==0)
	{
		xmlNodePtr style = curXMLNode->children;
		while(style!=NULL)
		{
			//判断是不是注释节点或者空白节点，是的话不处理
			if (style->type != XML_ELEMENT_NODE)
			{
				style = style->next;
				continue;
			}
			xml_node styleNode;
			styleNode.relateXMLNode(style);
			string style_str="";
			if (strcmp((const char*)style->name,"style")==0&&styleNode.hasAttribute("id"))
			{
				xmlNodePtr item = style->children;
				while(item!=NULL)
				{
					//判断是不是注释节点或者空白节点，是的话不处理
					if (item->type != XML_ELEMENT_NODE)
					{
						item = item->next;
						continue;
					}
					xml_node itemNode;
					itemNode.relateXMLNode(item);
					style_str.append(parseName(itemNode.getName()));
					if (itemNode.hasAttribute("sub-controls"))
					{
						style_str.append("::");
						style_str.append(itemNode.getAttribute("sub-controls"));
					}
					if (itemNode.hasAttribute("states"))
					{
						style_str.append(":");
						style_str.append(itemNode.getAttribute("states"));
					}
					//以content形式组织属性,每个节点的content为属性内容，property为属性名称，每个节点只能指定一个控件的
					//一种属性，获得的字符串如下：
					//QLabel { border-color: red }   
					//QLabel { border-width: 12 } 
					//QLabel { background-color: blue } 
					if (itemNode.hasAttribute("property"))
					{
						string name = itemNode.getAttribute("property");
						style_str.append("{");
						style_str.append(name);
						style_str.append(":");
						string content;
						style_str.append(parseContent(content,itemNode.getContent(),name.c_str()));
						style_str.append("}");
					}else
					{
						//以attribute形式组织属性，节点的每个属性和属性内容代表控件的属性和属性内容，每个节点可以指定
						//一个控件一种状态的多种属性，获得的字符串如下：
						/*QFrame {
							background-image: url(:/images/header.png);
							background-position: top left;
							background-origin: content;
						}*/
						style_str.append("{");
						xml_node::AttributeMapType attributeMap = itemNode.getAttributeMap();
						xml_node::AttributeMapType::const_iterator itor = attributeMap.begin();
						while(itor != attributeMap.end())
						{
							if (strcmp(itor->first.c_str(),"states")&&strcmp(itor->first.c_str(),"sub-controls"))
							{
								style_str.append(itor->first);
								style_str.append(":");
								string content;
								style_str.append(parseContent(content,itor->second.c_str(),itor->first.c_str()));
								style_str.append(";");	
							}
							++itor;
						}
						style_str.append("}");
					}
					style_str.append(" ");
					item = item->next;
				}
				string id = styleNode.getAttribute("id");
				if (!_res_map.count(id))
				{
					_res_map[id] = style_str;
				}
			}
			style = style->next;
		}
	}
	else
	{
		return "";
	}
}
//获得Application的样式
//参数：无
//返回值：资源
const char* res_style::getMainStyle()
{
	StyleMapType::iterator it = _res_map.find("MainStyle");
	if (it != _res_map.end())
	{
		string temp = it->second;
		int s = it->second.find_first_of(":");
		int e = it->second.find_last_of("}");
		it->second = it->second.substr(s+1,e-s-1);
		return it->second.c_str();
	}else
	{
		return "WindowsXP";
	}
}
//获得Style资源
//参数：id ID
//返回值：资源
const char* res_style::getStyleRes(const char* id)
{
	StyleMapType::iterator it = _res_map.find(id);
	if (it != _res_map.end())
	{
		return it->second.c_str();
	}else
	{
		return "";
	}
}

//解析节点Name
//参数：str 节点Name
//返回值：输出字符
const char* res_style::parseName(const char* str)
{
	if (strcmp(str,"Button")==0)			{return "QPushButton";}
	else if (strcmp(str,"LineEdit")==0)	{return "QLineEdit";}
	else if (strcmp(str,"Label")==0)		{return "QLabel";}
	else if (strcmp(str,"ComboBox")==0)	{return "QCombobox";}
	else if (strcmp(str,"TextEdit")==0)	{return "QTextEdit";}
	else if (strcmp(str,"Spinner")==0)		{return "QSpinBox";}
	else if (strcmp(str,"Tabs")==0)		{return "QTabWidget";}
	else if (strcmp(str,"Tab")==0)			{return "QWidget";}
	else if (strcmp(str,"TabBar")==0)		{return "QTabBar";}
	else if (strcmp(str,"GroupBox")==0)	{return "QGroupBox";}
	else if (strcmp(str,"RadioButton")==0)	{return "QRadioButton";}
	else if (strcmp(str,"TableWidget")==0)	{return "QTableWidget";} 
	else if (strcmp(str,"Table")==0)		{return "QTableWidget";}   
	else if (strcmp(str,"HeaderView")==0)  {return "QHeaderView";}
	else if (strcmp(str,"CheckBox")==0)	{return "QCheckBox";}
	else if (strcmp(str,"ListWidget")==0)	{return "QListWidget";}
	else if (strcmp(str,"Menu")==0)		{return "QMenu";}
	else if (strcmp(str,"MenuBar")==0)		{return "QMenuBar";}
	else if (strcmp(str,"MessageBox")==0)	{return "QMessageBox";}
	else if (strcmp(str,"ProgressBar")==0)	{return "QProgressBar";}
	else if (strcmp(str,"ScrollBar")==0)	{return "QScrollBar";}
	else if (strcmp(str,"Slider")==0)		{return "QSlider";}
	else if (strcmp(str,"SpinBox")==0)		{return "QSpinBox";}
	else if (strcmp(str,"Splitter")==0)	{return "QSplitter";}
	else if (strcmp(str,"StatusBar")==0)	{return "QStatusBar";}
	else if (strcmp(str,"TimeEdit")==0)	{return "QTimeEdit";}
	else if (strcmp(str,"ToolBar")==0)		{return "QToolBar";}
	else if (strcmp(str,"ToolButton")==0)	{return "QToolButton";}
	else if (strcmp(str,"ToolBox")==0)		{return "QToolBox";}
	else if (strcmp(str,"ToolTip")==0)		{return "QToolTip";}
	else if (strcmp(str,"TreeWidget")==0)	{return "QTreeWidget";}
	else if (strcmp(str,"Widget")==0)		{return "QWidget";}
	else									
	{
		std::string temp = str;
		if (!temp.empty()&&strcmp(temp.substr(0,1).c_str(),"Q")==0)
		{
			return str;
		}
		else
		{
			std::string temp = "Q";
			temp.append(str);
			return temp.c_str();
		}
	}
}