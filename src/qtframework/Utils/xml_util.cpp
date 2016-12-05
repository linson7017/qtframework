#include <Utils/xml_util.h>
#include <Uicreator/ui_node.h>

xml_util::xml_util(void)
{
}


xml_util::~xml_util(void)
{
}

bool xml_util::relate(ui_node* node,xmlNodePtr xmlNode)
{
	if (!node->hasAttribute("name"))
	{
		return false;
	}
	xmlNodeSetName(xmlNode,(const xmlChar*)node->getName());
	xmlNodeSetContent(xmlNode,(const xmlChar*)node->getContent());
	ui_node::AttributeMapType attributeMap = node->getAttributeMap();
	typedef ui_node::AttributeMapType::iterator ItorType;
	for (ItorType it = attributeMap.begin();it!=attributeMap.end();++it)
	{
		xmlSetProp(xmlNode,(const xmlChar*)it->first.c_str(),(const xmlChar*)it->second.c_str());
	}
	return true;
}

void xml_util::parseTree(ui_node* node,xmlNodePtr xmlNode)
{
	relate(node,xmlNode);
	if (node->getChildNum() != 0)
	{
		for(int i=0; i < node->getChildNum(); i++)
		{
			ui_node* child_node = node->getChild(i);
			xmlNodePtr child_xmlNode= xmlNewNode(NULL,(const xmlChar*)child_node->getName());
			xmlAddChild(xmlNode,child_xmlNode);		
			parseTree(child_node,child_xmlNode);	
		}
	}
}

void xml_util::convertToXMLTree(ui_node* root,xmlNodePtr xmlRoot)
{
	parseTree(root,xmlRoot);
}

bool xml_util::writeToFile(xmlNodePtr xmlRoot,const char* filename)
{
	if (!xmlRoot)
	{
		return false;
	}
	xmlDocPtr doc= xmlNewDoc(BAD_CAST"1.0");
	xmlDocSetRootElement(doc,xmlRoot);
	xmlSaveFormatFileEnc(filename,doc,"UTF-8",1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	return true;
}

bool xml_util::writeToFile(ui_node* root,const char* filename)
{
	xmlNodePtr xmlRoot = xmlNewNode(NULL,(const xmlChar*)root->getName());
	xml_util::convertToXMLTree(root,xmlRoot);
	return xml_util::writeToFile(xmlRoot,filename);
}
