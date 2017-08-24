#include "QF_String.h"

#include <iostream>

mbstate_t in_cvt_state;
mbstate_t out_cvt_state;

const std::wstring s2ws(const std::string& s)
{
    std::locale sys_loc("");

    const char* src_str = s.c_str();
    const size_t BUFFER_SIZE = s.size() + 1;

    wchar_t* intern_buffer = new wchar_t[BUFFER_SIZE];
    wmemset(intern_buffer, 0, BUFFER_SIZE);

    const char* extern_from = src_str;
    const char* extern_from_end = extern_from + s.size();
    const char* extern_from_next = 0;
    wchar_t* intern_to = intern_buffer;
    wchar_t* intern_to_end = intern_to + BUFFER_SIZE;
    wchar_t* intern_to_next = 0;

    typedef std::codecvt<wchar_t, char, mbstate_t> CodecvtFacet;

    CodecvtFacet::result cvt_rst =
        std::use_facet<CodecvtFacet>(sys_loc).in(
            in_cvt_state,
            extern_from, extern_from_end, extern_from_next,
            intern_to, intern_to_end, intern_to_next);
    if (cvt_rst != CodecvtFacet::ok) {
        switch (cvt_rst) {
        case CodecvtFacet::partial:
            std::cerr << "partial";
            break;
        case CodecvtFacet::error:
            std::cerr << "error";
            break;
        case CodecvtFacet::noconv:
            std::cerr << "noconv";
            break;
        default:
            std::cerr << "unknown";
        }
        std::cerr << ", please check in_cvt_state."
            << std::endl;
    }
    std::wstring result = intern_buffer;

    delete[]intern_buffer;

    return result;
}

const std::string ws2s(const std::wstring& ws)
{
    std::locale sys_loc("");

    const wchar_t* src_wstr = ws.c_str();
    const size_t MAX_UNICODE_BYTES = 4;
    const size_t BUFFER_SIZE =
        ws.size() * MAX_UNICODE_BYTES + 1;

    char* extern_buffer = new char[BUFFER_SIZE];
    memset(extern_buffer, 0, BUFFER_SIZE);

    const wchar_t* intern_from = src_wstr;
    const wchar_t* intern_from_end = intern_from + ws.size();
    const wchar_t* intern_from_next = 0;
    char* extern_to = extern_buffer;
    char* extern_to_end = extern_to + BUFFER_SIZE;
    char* extern_to_next = 0;

    typedef std::codecvt<wchar_t, char, mbstate_t> CodecvtFacet;

    CodecvtFacet::result cvt_rst =
        std::use_facet<CodecvtFacet>(sys_loc).out(
            out_cvt_state,
            intern_from, intern_from_end, intern_from_next,
            extern_to, extern_to_end, extern_to_next);
    if (cvt_rst != CodecvtFacet::ok) {
        switch (cvt_rst) {
        case CodecvtFacet::partial:
            std::cerr << "partial";
            break;
        case CodecvtFacet::error:
            std::cerr << "error";
            break;
        case CodecvtFacet::noconv:
            std::cerr << "noconv";
            break;
        default:
            std::cerr << "unknown";
        }
        std::cerr << ", please check out_cvt_state."
            << std::endl;
    }
    std::string result = extern_buffer;

    delete[]extern_buffer;

    return result;
}

std::string&  str_replace_all(std::string& str, const std::string&  old_value, const std::string&  new_value)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
    {
        if ((pos = str.find(old_value, pos)) != std::string::npos)
            str.replace(pos, old_value.length(), new_value);
        else   break;
    }
    return   str;
}

void splitString(std::string& inStr, std::vector<std::string>& outStrVec, std::string sep)
{
    std::string temp = inStr.c_str();
    char* result = NULL;
    result = strtok((char*)temp.data(), (char*)sep.data());
    while (result != NULL)
    {
        outStrVec.push_back(result);
        result = strtok(NULL, (char*)sep.data());
    }
}

void splitpath(const char*path, std::string& drive, std::string& dir, std::string& fname, std::string& ext)
{
    std::string temp = path;
    str_replace_all(temp, "\\", "/");
    std::vector<std::string> v;
    splitString(temp, v, "/");
    int size = v.size();
    if (size <= 1)
    {
        dir = temp;
        fname = "";
        ext = "";
    }
    else
    {
        fname = v.at(size - 1);
        if (fname.find(".") != std::string::npos)
        {
            int index = fname.find_first_of(".");
            ext = fname.substr(index + 1, fname.size() - 1);
            fname = fname.substr(0, index);
        }
        if (temp.find(":") != std::string::npos)
        {
            int i = temp.find_first_of(":");
            drive = temp.substr(0, i + 1);
        }
        else
        {
            drive = "";
        }
        dir = temp;
        if (temp.find("/") != std::string::npos)
        {
            int j = dir.find_last_of("/");
            dir = dir.substr(0, j + 1);
        }
    }
}

const char* remove_comment(const std::string& input,std::string& result)
{
    enum {
    literal,
    single,
    multiple,
    string
  } mode = literal;
  char last = 0, current;
  result.clear();

  for (int i=0;i<input.size();i++)
  {
      current = input.at(i);
      switch (mode) {
      case single: {
          if (last != '\\' && (current == '\n' || current == '\r')) {
              result.append(1,current);
              current = 0;
              mode = literal;
          }
      } break;
      case multiple: {
          if (last == '*' && current == '/') {
              current = 0;
              mode = literal;
          }
      } break;
      case string: {
          if (last == '\\') {
              result.append(1, last);
              result.append(1, current);
          }
          else if (current != '\\') {
              result.append(1, current);
              if (current == '"') {
                  mode = literal;
              }
          }
      } break;
      default: {
          if (last == '/') {
              if (current == '/') {
                  mode = single;
              }
              else if (current == '*') {
                  mode = multiple;
              }
              else {
                  result.append(1, last);
                  result.append(1, current);
              }
          }
          else if (current != '/') {
              result.append(1, current);
              if (current == '"') {
                  mode = string;
              }
          }
      } break;
      }
      last = current;
  }
  return result.c_str();

}