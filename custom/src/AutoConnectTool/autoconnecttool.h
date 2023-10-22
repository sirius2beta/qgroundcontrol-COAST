#ifndef AUTOCONNECTTOOL_H
#define AUTOCONNECTTOOL_H

#include <QObject>

class AutoConnectTool : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString targetIP READ targetIP WRITE setTargetIP)
    explicit AutoConnectTool(QObject *parent = nullptr);
    ~AutoConnectTool();

    QString targetIP();
    void setTargetIP(QString ip);
signals:

private:
    QString _targetIP;

};

#endif // AUTOCONNECTTOOL_H
