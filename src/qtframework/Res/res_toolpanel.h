#pragma once
#include <map>
#include <string>
using namespace std;
class ui_node;
class res_toolpanel
{
public:
	res_toolpanel(void);
	~res_toolpanel(void);

	ui_node* getToolpanelRes(const char* id);
private:
	typedef map<string,ui_node*> ResMapType;
	ResMapType _res_map;
};

