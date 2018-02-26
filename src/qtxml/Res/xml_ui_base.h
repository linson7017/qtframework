/********************************************************************
	FileName:    xml_ui_base.h
	Author:        Ling Song
	Date:           Month 2 ; Year 2018
	Purpose:	     
*********************************************************************/
#ifndef xml_ui_base_h__
#define xml_ui_base_h__
#include <map>
#include <string>

class ui_node;

class xml_ui_base
{
public:
    xml_ui_base(const char* dir);
    ~xml_ui_base();
    ui_node* getUIRootNode(const char* id);
protected:
    void parseXML(const char* dir);
private:
    typedef std::map< std::string, ui_node* > ResMapType;
    ResMapType _res_map;
    std::string _dir;
};
#endif // xml_ui_base_h__