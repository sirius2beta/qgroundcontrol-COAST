#include "autoconnecttool.h"
#include <QQmlEngine>
#include <QtQml>
AutoConnectTool::AutoConnectTool(QObject *parent)
    : QObject{parent},
      _targetIP("192.168.0.1"),
      linkManager(qgcApp()->toolbox()->linkManager())
{
    qmlRegisterUncreatableType<AutoConnectTool>("QGroundControl.custom", 1, 0, "AutoConnectTool", "Reference only");

}

AutoConnectTool::~AutoConnectTool()
{

}

bool AutoConnectTool::addLink(LinkConfiguration* link, QString ip)
{
    if(!_linkList.contains(link) && (ip != QString())){
        _linkList.insert(link, ip);
        qDebug()<<"AutoConnectTool::addLink, IP:"<<ip<<", name:"<<link->name();
    }else{
        qDebug()<<"AutoConnectTool::addLink, Failed"<<ip;
        return false;
    }
    return true;

}

bool AutoConnectTool::deleteLink(LinkConfiguration* link)
{
    if(_linkList.contains(link)){
        _linkList.remove(link);
        qDebug()<<"AutoConnectTool::deleteLink";
    }else{
        qDebug()<<"AutoConnectTool::deleteLink, Failed";
        return false;
    }
    return true;

}

bool AutoConnectTool::editLink(LinkConfiguration* link, QString ip)
{
    if(_linkList.contains(link) && (ip != QString())){
         _linkList[link] = ip;
        qDebug()<<"AutoConnectTool::editLink, IP:"<<ip<<", name:"<<link->name();
    }else{
        qDebug()<<"AutoConnectTool::editLink, Failed"<<ip;
        return false;
    }
    return true;

}

void AutoConnectTool::setTargetIP(QString ip)
{
    _targetIP = ip;
    emit targetIPChanged(ip);
}

void AutoConnectTool::connect(){
    qDebug()<<"AutoConnectTool::connect:"<<_targetIP;
}

QString AutoConnectTool::getIP(LinkConfiguration* link)
{
    if(_linkList.contains(link) && link){
         return _linkList[link];
            qDebug()<<"AutoConnectTool::getIP";
    }else{
        qDebug()<<"AutoConnectTool::getIP, Failed";
    }
    return QString();
}
