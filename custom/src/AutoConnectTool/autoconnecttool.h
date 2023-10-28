#ifndef AUTOCONNECTTOOL_H
#define AUTOCONNECTTOOL_H

#include <QMap>
#include <QObject>
#include <QUdpSocket>

#include "QGCToolbox.h"
#include "LinkInterface.h"
#include "QGCApplication.h"
#include "LinkManager.h"
class LinkInterface;
class LinkManager;


class AutoConnectTool : public QGCTool
{
    Q_OBJECT
public:
    Q_PROPERTY(QString targetIP READ targetIP WRITE setTargetIP NOTIFY targetIPChanged)

    Q_INVOKABLE bool addLink(LinkConfiguration *link, QString ip);
    Q_INVOKABLE bool deleteLink(LinkConfiguration* link);
    Q_INVOKABLE bool editLink(LinkConfiguration* link, QString ip);
    Q_INVOKABLE QString getIP(LinkConfiguration* link);

    explicit AutoConnectTool(QGCApplication* app, QGCToolbox* toolbox);
    ~AutoConnectTool();
    // Override from QGCTool
    virtual void setToolbox(QGCToolbox *toolbox);
    static const QString settingsRoot() {return "AutoConnectTool";};
    QString targetIP()  {    return _targetIP;  };
    void setTargetIP(QString ip);
    void sentMsg(QString ip, const QByteArray data);
    void loadSettings();
signals:
    void targetIPChanged(QString ip);

public slots:
    void _sendGCSHeartbeat(void);
private:
    QString _targetIP;
    QMap<LinkConfiguration*, QString> _linkList;
    LinkManager* _linkManager;
    QUdpSocket*         _socket;
    QTimer _gcsHeartbeatTimer;

};

#endif // AUTOCONNECTTOOL_H
