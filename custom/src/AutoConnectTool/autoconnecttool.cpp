#include "autoconnecttool.h"
#include <QQmlEngine>
#include <QtQml>
AutoConnectTool::AutoConnectTool(QObject *parent)
    : QObject{parent},
      _targetIP("192.168.0.1")
{
    qmlRegisterUncreatableType<AutoConnectTool>("QGroundControl.custom", 1, 0, "AutoConnectTool", "Reference only");

}

AutoConnectTool::~AutoConnectTool()
{

}

QString AutoConnectTool::targetIP()
{
    return _targetIP;
}

void AutoConnectTool::setTargetIP(QString ip)
{
    _targetIP = ip;
}
