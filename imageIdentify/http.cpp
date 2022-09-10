#include "http.h"

Http::Http()
{

}

bool Http::post_sync(QString Url, QMap<QString, QString> header, QByteArray &requestData, QByteArray &replyData)
{
    QNetworkAccessManager manager;     //发送请求的动作

    QNetworkRequest request;           //请求的内容（包含url和头）
    request.setUrl(Url);
    QMapIterator<QString, QString> it(header);
    while (it.hasNext())
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(), it.value().toLatin1());
    }

    QNetworkReply *reply = manager.post(request, requestData);
    QEventLoop l;
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();                             //死循环

    if (reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        return true;
    }
    else
    {
        return false;
    }

}
