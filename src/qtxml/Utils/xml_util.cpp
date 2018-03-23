#include <Utils/xml_util.h>
#include <Uicreator/ui_node.h>

xml_util::xml_util(void)
{
}


xml_util::~xml_util(void)
{
}

bool xml_util::relate(ui_node* node, tinyxml2::XMLNode* xmlNode)
{
	if (node->TypeOfXMLNode!=xml_node::ELEMENT)
	{
		return false;
	}
    xmlNode->ToElement()->SetName(node->getName());
    xmlNode->ToElement()->SetText(node->getContent());
	ui_node::AttributeMapType attributeMap = node->getAttributeMap();
	typedef ui_node::AttributeMapType::iterator ItorType;
	for (ItorType it = attributeMap.begin();it!=attributeMap.end();++it)
	{
        xmlNode->ToElement()->SetAttribute(it->first.c_str(), it->second.c_str());
	}
	return true;
}

void xml_util::parseTree(ui_node* node, tinyxml2::XMLNode* xmlNode,tinyxml2::XMLDocument& xmlDoc)
{
	relate(node,xmlNode);
	if (node->getChildNum() != 0)
	{
		for(int i=0; i < node->getChildNum(); i++)
		{
			ui_node* child_node = node->getChild(i);
            tinyxml2::XMLNode*  newNode = nullptr;
            if (node->TypeOfXMLNode == xml_node::COMMENT)
            {
                newNode = xmlDoc.NewComment(child_node->getContent());
            }	
            else if (node->TypeOfXMLNode == xml_node::ELEMENT)
            {
                newNode = xmlDoc.NewElement(child_node->getName());
            }
            xmlNode->InsertEndChild(newNode);
            parseTree(child_node, newNode, xmlDoc);
		}
	}
}

void xml_util::convertToXMLDoc(ui_node* root, tinyxml2::XMLDocument& xmlDoc)
{
    if (!xmlDoc.RootElement())
    {
        xmlDoc.InsertFirstChild(xmlDoc.NewElement("EmptyElement"));
    }
	parseTree(root, xmlDoc.RootElement(),xmlDoc);
}

bool xml_util::writeToFile(tinyxml2::XMLDocument& xmlDoc,const char* filename)
{
    return xmlDoc.SaveFile(filename)==tinyxml2::XML_SUCCESS;
}

bool xml_util::writeToFile(ui_node* root,const char* filename)
{
    tinyxml2::XMLDocument doc;
	xml_util::convertToXMLDoc(root, doc);
	return xml_util::writeToFile(doc,filename);
}

//获得xml文件根节点
//参数：
//	filename:xml文件路径
//	root:xml根节点
//返回值：获得成功返回true,否则返回false
bool xml_util::getXMLFileRoot(const char* filename, xml_node* root)
{
    if (!root)
    {
        return false;
    }
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile(filename);
    if (error!=tinyxml2::XML_SUCCESS)
    {
        printf("Load xml file %s  failed! Error code: %s\n", filename ,doc.ErrorStr());
        return false;
    }
    root->relateXMLNode(doc.RootElement());
    return true;
}
