#ifndef qf_log_h__
#define qf_log_h__
/********************************************************************
	FileName:    qf_log
	Author:        Ling Song
	Date:           Month 5 ; Year 2018
	Purpose:	     
*********************************************************************/

#include "spdlog.h"
#include <sstream>
#include <iostream>

namespace QF{


class Stream
{
protected:
    bool disabled;
    std::stringstream ss;
    spdlog::level::level_enum level;
public:
    inline Stream(spdlog::level::level_enum level, const char *filePath, int lineNumber, const char *functionName)
        : disabled(false), ss(std::stringstream::out)
    {
        //spd::set_level(level); // Set global log level to info
        this->level = level;
    }

    /** \brief The message which is stored in the member ss is written to the backend. */
    inline ~Stream()
    {
        if (!disabled)
        {
            Distribute(ss.str());
        }
    }
    inline void Distribute(std::string str)
    {
        try
        {
            auto console = spdlog::get("qfconsole");
            if (!console)
            {
                console = spdlog::stdout_color_mt("qfconsole");
            }
            switch (this->level)
            {
            case spdlog::level::info:
                console->info(str);
                break;
            case spdlog::level::debug:
                console->debug(str);
                break;
            case spdlog::level::err:
                console->error(str);
                break;
            case spdlog::level::warn:
                console->warn(str);
                break;
            default:
                break;
            }
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }  
    }

    template <class T>
    inline Stream &operator<<(const T &data)
    {
        if (!disabled)
        {
            std::locale C("C");
            std::locale originalLocale = ss.getloc();
            ss.imbue(C);
            ss << data;
            ss.imbue(originalLocale);
        }
        return *this;
    }

    template <class T>
    inline Stream &operator<<(T &data)
    {
        if (!disabled)
        {
            std::locale C("C");
            std::locale originalLocale = ss.getloc();
            ss.imbue(C);
            ss << data;
            ss.imbue(originalLocale);
        }
        return *this;
    }

    inline Stream &operator<<(std::ostream &(*func)(std::ostream &))
    {
        if (!disabled)
        {
            std::locale C("C");
            std::locale originalLocale = ss.getloc();
            ss.imbue(C);
            ss << func;
            ss.imbue(originalLocale);
        }
        return *this;
    }

    inline Stream &operator()(bool enabled)
    {
        disabled |= !enabled;
        return *this;
    }
};
}


#define QF_INFO            QF::Stream(spdlog::level::info, __FILE__, __LINE__, __FUNCTION__)
#define QF_DEBUG        QF::Stream(spdlog::level::debug, __FILE__, __LINE__, __FUNCTION__)
#define QF_WARN          QF::Stream(spdlog::level::warn, __FILE__, __LINE__, __FUNCTION__)
#define QF_ERROR        QF::Stream(spdlog::level::err, __FILE__, __LINE__, __FUNCTION__)


#endif // qf_log_h__