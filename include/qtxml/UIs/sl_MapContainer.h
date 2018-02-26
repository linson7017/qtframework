#pragma once
#include <map>
class sl_MapContainer
{
public:
	sl_MapContainer(void);
	~sl_MapContainer(void);
	void addChild(int iKey,void* pChild){_childMap[iKey]=pChild;}
	void* getChild(int iKey)
	{
		std::map<int,void*>::iterator it = _childMap.find(iKey);
		if (it != _childMap.end())
		{
			return it->second;
		}else
		{
			return NULL;
		}
	}
	int size(){return _childMap.size();}
private:
	std::map<int,void*> _childMap;
};

