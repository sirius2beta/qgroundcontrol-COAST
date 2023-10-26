﻿#ifndef AUTOCONNECTTOOL_H
#define AUTOCONNECTTOOL_H

#include <QObject>
#include "QGCToolbox.h"

class AutoConnectTool : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString targetIP READ targetIP WRITE setTargetIP NOTIFY targetIPChanged)

    Q_INVOKABLE void connect();
    explicit AutoConnectTool(QObject *parent = nullptr);
    ~AutoConnectTool();
    void setToolBox(QGCToolbox* toolbox){   _toolbox = toolbox;};
    QString targetIP();
    void setTargetIP(QString ip);
signals:
    void targetIPChanged(QString ip);
private:
    QString _targetIP;
    QGCToolbox* _toolbox;

};

#endif // AUTOCONNECTTOOL_H
