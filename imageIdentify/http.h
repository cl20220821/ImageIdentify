#ifndef HTTP_H
#define HTTP_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QObject>

class Http : public QObject
{
    Q_OBJECT
public:
    Http();
    static bool post_sync(QString Url, QMap<QString, QString> header, QByteArray &requestData, QByteArray &replyData);
};

#endif // HTTP_H
