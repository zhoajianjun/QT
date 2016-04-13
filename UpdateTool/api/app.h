#ifndef APP_H
#define APP_H

class QString;

class App
{
public:
    static QString AppName;             //应用程序英文名称
    static QString AppPath;             //应用程序路径
    static int DeskWidth;               //运行环境桌面宽度
    static int DeskHeight;              //运行环境桌面高度

    static int IcoMain;                 //左上角图标
    static int IcoMenu;                 //下来菜单图标
    static int IcoMin;                  //最小化图标
    static int IcoMax;                  //最大化图标
    static int IcoNormal;               //正常图标
    static int IcoClose;                //关闭图标

    static bool UseTray;                //启用托盘
    static bool SaveLog;                //输出日志文件
    static bool UseStyle;               //启用样式
    static QString StyleName;           //应用程序样式
    static int FontSize;                //应用程序字体大小
    static QString FontName;            //应用程序字体名称

    static int UpdatePort;              //升级程序端口
    static QString SearchIP;            //广播搜索IP
    static int SearchPort;              //广播搜索端口

    static void ReadConfig();           //读取配置文件,在main函数最开始加载程序载入
    static void WriteConfig();          //写入配置文件,在更改配置文件程序关闭时调用
    static void NewConfig();            //以初始值新建配置文件
    static bool CheckConfig();          //校验配置文件

    static void WriteError(QString str);//写入错误信息
    static void WriteStartTime();       //写入启动时间
    static void NewDir(QString dirName);//新建目录

};

#endif // APP_H
