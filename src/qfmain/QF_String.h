/********************************************************************
	FileName:    QF_String.h
	Author:        Ling Song
	Date:           Month 7 ; Year 2017
	Purpose:	     
*********************************************************************/
#ifndef QF_String_h__
#define QF_String_h__

#include <string>
#include <vector>

const std::wstring s2ws(const std::string& s);
const std::string ws2s(const std::wstring& s);

std::string&  str_replace_all(std::string& str, const std::string&  old_value, const std::string&  new_value);
void splitString(std::string& inStr, std::vector<std::string>& outStrVec, std::string sep);
void splitpath(const char*path, std::string& drive, std::string& dir, std::string& fname, std::string& ext);

const char* remove_comment(const std::string& input);

#endif // QF_String_h__
