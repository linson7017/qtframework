#include <Utils/variant.h>


variant::variant() :_type(UnKnown), _sdata(""),_content("")
{
    _data.iValue = FLT_MAX;
    _data.bValue = false;
    _data.dValue = FLT_MAX;
    _data.pValue = NULL;
}


variant::~variant()
{
}

