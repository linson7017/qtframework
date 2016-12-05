#pragma once
#include <vector>
class sl_VectorContainer
{
public:
	sl_VectorContainer(void);
	~sl_VectorContainer(void);
	void addChild(void* pChild){_childVector.push_back(pChild);}
	void* getChild(int iIndex){return _childVector.at(iIndex);}
	int size(){_childVector.size();}
private:
	std::vector<void*> _childVector;
};

