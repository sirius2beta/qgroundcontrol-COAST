﻿#include "autoconnecttool.h"
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

bool AutoConnectTool::addLink(SharedLinkInterfacePtr link, QString ip)
{
    if(!_linkList.contains(link)){
        _linkList.insert(link, ip);
        qDebug()<<"AutoConnectTool::addLink, IP:"<<ip;
    }else{
        return false;
    }
    return true;
}

bool AutoConnectTool::deleteLink(SharedLinkInterfacePtr link)
{
    if(!_linkList.contains(link)){
        _linkList.remove(link);
        qDebug()<<"AutoConnectTool::deleteLink";
    }else{
        return false;
    }
    return true;
}

bool AutoConnectTool::editLink(SharedLinkInterfacePtr link, QString ip)
{
    if(!_linkList.contains(link)){
        _linkList[link] = ip;
    }else{
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
