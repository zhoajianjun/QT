#include "app.h"
#include "myhelper.h"

QString App::AppName = "UpdateTool";
QString App::AppPath = "";
int App::DeskWidth = 1440;
int App::DeskHeight = 900;

int App::IcoMain = 0xf019;
int App::IcoMenu = 0xf0d7;
int App::IcoMin = 0xf068;
int App::IcoMax = 0xf079;
int App::IcoNormal = 0xf0b2;
int App::IcoClose = 0xf00d;

bool App::UseTray = false;
bool App::SaveLog = false;
bool App::UseStyle = false;
QString App::StyleName = ":/qss/gray.css";
int App::FontSize = 9;
QString App::FontName = "Microsoft YaHei";

int App::UpdatePort = 6904;
QString App::SearchIP = "224.0.0.17";
int App::SearchPort = 6905;

void App::ReadConfig()
{
    if (!CheckConfig()) {
        return;
    }

    QString fileName = QString("%1/%2_Config.ini").arg(App::AppPath).arg(App::AppName);
    QSettings set(fileName, QSettings::IniFormat);

    set.beginGroup("AppConfig");
    App::UseTray = set.value("UseTray").toBool();
    App::SaveLog = set.value("SaveLog").toBool();
    App::UseStyle = set.value("UseStyle").toBool();
    App::StyleName = set.value("StyleName").toString();
    App::FontSize = set.value("FontSize").toInt();
    App::FontName = set.value("FontName").toString();
    set.endGroup();

    set.beginGroup("Config");
    App::UpdatePort = set.value("UpdatePort").toInt();
    App::SearchIP = set.value("SearchIP").toString();
    App::SearchPort = set.value("SearchPort").toInt();
    set.endGroup();
}

void App::WriteConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(App::AppPath).arg(App::AppName);
    QSettings set(fileName, QSettings::IniFormat);

    set.beginGroup("AppConfig");
    set.setValue("UseTray", App::UseTray);
    set.setValue("SaveLog", App::SaveLog);
    set.setValue("UseStyle", App::UseStyle);
    set.setValue("StyleName", App::StyleName);
    set.setValue("FontSize", App::FontSize);
    set.setValue("FontName", App::FontName);
    set.endGroup();

    set.beginGroup("Config");
    set.setValue("UpdatePort", App::UpdatePort);
    set.setValue("SearchIP", App::SearchIP);
    set.setValue("SearchPort", App::SearchPort);
    set.endGroup();
}

void App::NewConfig()
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))

#endif
    WriteConfig();
}

bool App::CheckConfig()
{
    QString fileName = QString("%1/%2_Config.ini").arg(App::AppPath).arg(App::AppName);

    //如果配置文件大小为0,则以初始值继续运行,并生成配置文件
    QFile file(fileName);
    if (file.size() == 0) {
        NewConfig();
        return false;
    }

    //如果配置文件不完整,则以初始值继续运行,并生成配置文件
    if (file.open(QFile::ReadOnly)) {
        bool ok = true;
        while(!file.atEnd()) {
            QString line = file.readLine();
            line = line.replace("\r", "");
            line = line.replace("\n", "");
            QStringList list = line.split("=");
            if (list.count() == 2) {
                if (list.at(1) == "") {
                    ok = false;
                    break;
                }
            }
        }
        if (!ok) {
            NewConfig();
            return false;
        }
    } else {
        NewConfig();
        return false;
    }

    return true;
}

void App::WriteError(QString str)
{
    QString fileName = QString("%1/log/%2_Error_%3.txt").arg(App::AppPath).arg(App::AppName).arg(DATE);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << DATETIME << "  " << str << "\n";
}

void App::WriteStartTime()
{
    QString fileName = QString("%1/log/%2_Start_%3.txt").arg(App::AppPath).arg(App::AppName).arg(DATE);
    QFile file(fileName);
    QString str = QString("start time : %1").arg(DATETIME);
    file.open(QFile::WriteOnly | QIODevice::Append | QFile::Text);
    QTextStream stream(&file);
    stream << str << "\n";
}

void App::NewDir(QString dirName)
{
    dirName = QString("%1/%2").arg(App::AppPath).arg(dirName);
    QDir dir(dirName);
    if (!dir.exists()) {
        dir.mkpath(dirName);
    }
}
