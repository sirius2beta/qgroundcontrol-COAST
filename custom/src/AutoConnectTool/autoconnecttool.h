#ifndef AUTOCONNECTTOOL_H
#define AUTOCONNECTTOOL_H

#include <QObject>
#include <QMap>
#include "QGCToolbox.h"
#include "LinkInterface.h"

class LinkInterface;

class AutoConnectTool : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString targetIP READ targetIP WRITE setTargetIP NOTIFY targetIPChanged)

    Q_INVOKABLE void connect();
    Q_INVOKABLE bool addLink(SharedLinkInterfacePtr link, QString ip);
    Q_INVOKABLE bool deleteLink(SharedLinkInterfacePtr link);
    Q_INVOKABLE bool editLink(SharedLinkInterfacePtr link, QString ip);

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
    QMap<SharedLinkInterfacePtr, QString> _linkList;

};

#endif // AUTOCONNECTTOOL_H
