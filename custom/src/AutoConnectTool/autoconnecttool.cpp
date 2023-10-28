#include "autoconnecttool.h"
#include <QQmlEngine>
#include <QtQml>
#include <QHostAddress>
#include <QSettings>

AutoConnectTool::AutoConnectTool(QGCApplication *app, QGCToolbox *toolbox)
    : QGCTool(app, toolbox),
      _targetIP("192.168.0.1"),
      _linkManager(nullptr)
{
    qmlRegisterUncreatableType<AutoConnectTool>("QGroundControl.custom", 1, 0, "AutoConnectTool", "Reference only");


}

AutoConnectTool::~AutoConnectTool()
{

}

void AutoConnectTool::setToolbox(QGCToolbox* toolbox)
{
       QGCTool::setToolbox(toolbox);

       _linkManager = _toolbox->linkManager();
       _socket = new QUdpSocket(this);
       _socket->bind(50008,QUdpSocket::ShareAddress);

       _gcsHeartbeatTimer.setInterval(1000);
       _gcsHeartbeatTimer.setSingleShot(false);

       connect(&_gcsHeartbeatTimer, &QTimer::timeout, this, &AutoConnectTool::_sendGCSHeartbeat);
       _gcsHeartbeatTimer.start();
}

bool AutoConnectTool::addLink(LinkConfiguration* link, QString ip)
{
    if(!_linkList.contains(link) && (ip != QString())){
        _linkList.insert(link, ip);
        qDebug()<<"AutoConnectTool::addLink, IP:"<<ip<<", name:"<<link->name();
        QSettings settings;
        int trueCount = 0;

        for (int i = 0; i < _linkManager->configs().count(); i++) {
            SharedLinkConfigurationPtr linkConfig = _linkManager->configs()[i];
            if (linkConfig) {
                if (!linkConfig->isDynamic()) {
                    if(link == linkConfig.get()){
                        QString root = AutoConnectTool::settingsRoot();
                        root += QString("/Link%1").arg(trueCount);
                        settings.setValue(root + "/targetIP", ip);
                        qDebug()<<"AutoConnectTool::addLink: setting++"<<trueCount;
                    }
                    trueCount++;
                }
            } else {
                qWarning() << "Internal error for link configuration in LinkManager";
            }
        }




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
        QSettings settings;
        for (int i = 0; i < _linkManager->configs().count(); i++) {
            SharedLinkConfigurationPtr linkConfig = _linkManager->configs()[i];
            if(link == linkConfig.get()){
                QString root = AutoConnectTool::settingsRoot();
                root += QString("/Link%1").arg(i);
                settings.remove(root);
            }
        }
        qDebug()<<"AutoConnectTool::deleteLink";
    }else{
        qDebug()<<"AutoConnectTool::deleteLink, Failed";
        return false;
    }
    return true;

}

bool AutoConnectTool::editLink(LinkConfiguration* link, QString ip)
{
    if(_linkList.contains(link)){
         _linkList[link] = ip;
        qDebug()<<"AutoConnectTool::editLink, IP:"<<ip<<", name:"<<link->name();
        QSettings settings;
        int trueCount = 0;

        for (int i = 0; i < _linkManager->configs().count(); i++) {
            SharedLinkConfigurationPtr linkConfig = _linkManager->configs()[i];
            if (linkConfig) {
                if (!linkConfig->isDynamic()) {
                    if(link == linkConfig.get()){
                        QString root = AutoConnectTool::settingsRoot();
                        root += QString("/Link%1").arg(trueCount);
                        settings.setValue(root + "/targetIP", ip);
                        qDebug()<<"AutoConnectTool::addLink: setting++"<<trueCount;
                    }
                    trueCount++;
                }
            } else {
                qWarning() << "Internal error for link configuration in LinkManager";
            }
        }
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


QString AutoConnectTool::getIP(LinkConfiguration* link)
{

    if(_linkList.contains(link)){
            qDebug()<<"AutoConnectTool::getIP"<<_linkList[link];
         return _linkList[link];

    }else{
        qDebug()<<"AutoConnectTool::getIP, Failed";
    }
    return QString();
}

void AutoConnectTool::sentMsg(QString ip, const QByteArray data)
{
    if (!_socket) {
        return;
    }

    QHostAddress target(ip);
    if(target == QHostAddress()){
        return;
    }
    if(_socket->writeDatagram(data, target, 50006) < 0) {
        qWarning() << "Error writing to" << ip;
    }else{
        qDebug()<<"AutoConnectTool::HB: "<<ip;
    }
}

void AutoConnectTool::loadSettings(){



    QSettings settings;
    // Is the group even there?
    if(settings.contains(AutoConnectTool::settingsRoot() + "/count")) {
        // Find out how many configurations we have

    }
    int count = _linkManager->configs().count();
    qDebug()<<count;
    for(int i = 0; i < count; i++) {
        QString root(AutoConnectTool::settingsRoot());
        root += QString("/Link%1").arg(i);
        if(settings.contains(root + "/targetIP")) {
            QString ip = settings.value(root + "/targetIP").toString();
            _linkList[_linkManager->configs()[i].get()]= ip;
            qDebug()<<"cof::"<<_linkManager->configs()[i].get();
        }else{
            settings.setValue(root + "/targetIP","");
            _linkList[_linkManager->configs()[i].get()]= "";
            qDebug()<<"cof::"<<_linkManager->configs()[i].get();
        }

    }

    // Enable automatic Serial PX4/3DR Radio hunting
}

void AutoConnectTool::_sendGCSHeartbeat(void)
{
    for (auto i:_linkList.keys()) {
        // Skip it if it's part of the session clients below
        sentMsg(_linkList[i],"HB");
    }
}
