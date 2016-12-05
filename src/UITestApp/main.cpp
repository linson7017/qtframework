#include <QApplication>

#include <Common/app_env.h>
#include <Common/qt_context.h>
#include <UIs/SplashWindow.h>
#include "TestActivity.h"
#include "Utils/Log.h"
#include <Res/R.h>
#include <Utils/variant.h>
#include <TableActivity.h>
#include <SimpleTable.h>
//#include "gise_config.h"
//#include "main/igis_main.h"
//#include <airtrack/imti_radarmanager.h>
//#include <..\ViceMonitor\IViceMonitor.h>
//#include <..\ViceMonitor\MonitorConfig.h>
//#include <windows.h>
#ifdef Q_WS_X11
#include <X11/Xlib.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /**************程序环境和Qt环境的初始化*******************/
    //初始化程序环境
    QString wk = qApp->applicationFilePath();
    app_env appenv(wk.toLocal8Bit().constData());
    //指定qtframework工作目录，没指定则自动设置为可执行程序路径下ui_qtframework/app_name/目录
    //app_env::setWorkDir("G:/Projects/ESonRad20160111/bin/ui_qtframework/UITestApp");
    //Log::Instance()->log(Log::LOG_INFO,"Work directory:%s",app_env::getWorkDir());
    //初始化qt环境
    qt_context context(&a);
    //设置qt程序编码
    qt_context::setApplicationCoding("UTF-8");
    //设置qt程序默认语言
    qt_context::setDefaultLanguage("Chinese");
    //设置qt程序风格
    qt_context::setApplicationStyle("Fusion");
    Log::Instance()->setEnabled(true);
    Log::Instance()->log(Log::LOG_INFO, "App Start！");
    Log::Instance()->log(Log::LOG_WARN, "Waring！");
    Log::Instance()->log(Log::LOG_ERROR, "Error！");

    //添加qt插件库的搜索路径
#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
    qt_context::addLibraryPath("G:/Projects/ESonRad20160428/ESonRad/bin/plugins/win32");
#else
    qt_context::addLibraryPath(wk.append("/plugins/linux").toLocal8Bit().constData());
#endif
    //在这里设置主控指针
    /*gise::IGIS_Main* pMain = (gise::IGIS_Main*)MTI_GetRadarManagerObject()->GetMainPtr();
    app_env::setMainPtr(pMain);*/
    //添加和修改配置项
    R::Instance()->addConfigResource("lallal", new variant(50));
    R::Instance()->addConfigResource("qweq", new variant("asd"));
    R::Instance()->addConfigResource("blkj", new variant(true));
    R::Instance()->addConfigResource("dfgdfg", new variant(1.23));

    R::Instance()->setConfigResource("ConfigDialogPosX", new variant(2314));
    R::Instance()->setConfigResource("RAD_PARAM_JD", new variant("lkslkdfl"));
    R::Instance()->setConfigResource("propertyBool", new variant(false));
    R::Instance()->setConfigResource("propertyDouble", new variant(1.23));

    R::Instance()->overWriteConfigFile();


    //QApplication::setStyle(new MyStyle());
    /********************初始化界面*************************************/
    //SplashWindow* splashWindow = new SplashWindow;
    //splashWindow->setContentView("splash_window.xml");
    //splashWindow->setMessageLabelID("splash_window.information");
    //splashWindow->setPixmap(QPixmap("G:\\Projects\\ESonRad20160428\\ESonRad\\bin\\ui_qtframework\\UITestApp\\res\\images\\test.png"));
    //splashWindow->show();
    //qApp->processEvents();
    TestActivity* mainActivity = new TestActivity();
    /*mainActivity->setShowMode(Activity::NORMAL);
    splashWindow->showMessage("finished");

    qApp->processEvents();
    long num=0;
    for (int i=0;i<1000000000;i++)
    {
    num += i;
    }
    splashWindow->showMessage("finished1");
    splashWindow->setBackground("@image/Sunset.jpg");
    qApp->processEvents();
    for (int i=0;i<1000000000;i++)
    {
    num += i;
    }
    splashWindow->showMessage("finished2");
    splashWindow->setBackground("@image/world.png");
    qApp->processEvents();
    for (int i=0;i<1000000000;i++)
    {
    num += i;
    }*/
    //splashWindow->setActivity(mainActivity);
    //splashWindow->setDelay(2);
    //splashWindow->start();
    /*IViceMonitor* iv = InitViceMonitor(R::Instance());
    DataType data;
    int s = sizeof(data);
    iv->RefreshBITSystem(&data);*/

    mainActivity->active();
    //splashWindow->finish(mainActivity);


    return a.exec();
}


