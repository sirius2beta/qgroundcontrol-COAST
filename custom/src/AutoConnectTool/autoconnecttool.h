#ifndef AUTOCONNECTTOOL_H
#define AUTOCONNECTTOOL_H

#include <QObject>
#include <QMap>
#include "QGCToolbox.h"
#include "LinkInterface.h"
#include "QGCApplication.h"
#include "LinkManager.h"
class LinkInterface;
class LinkManager;


class AutoConnectTool : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString targetIP READ targetIP WRITE setTargetIP NOTIFY targetIPChanged)

    Q_INVOKABLE void connect();
    Q_INVOKABLE bool addLink(LinkConfiguration *link, QString ip);
    Q_INVOKABLE bool deleteLink(LinkConfiguration* link);
    Q_INVOKABLE bool editLink(LinkConfiguration* link, QString ip);
    Q_INVOKABLE QString getIP(LinkConfiguration* link);

    explicit AutoConnectTool(QObject *parent = nullptr);
    ~AutoConnectTool();
    void setToolBox(QGCToolbox* toolbox){   _toolbox = toolbox;};
    QString targetIP()  {    return _targetIP;  };
    void setTargetIP(QString ip);
signals:
    void targetIPChanged(QString ip);
private:
    QString _targetIP;
    QGCToolbox* _toolbox;
    QMap<LinkConfiguration*, QString> _linkList;
    LinkManager* linkManager;

};

#endif // AUTOCONNECTTOOL_H
