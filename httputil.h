#ifndef HTTPUTIL_H
#define HTTPUTIL_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QtDebug>
#include <QPixmap>

class httpUtil : public QObject
{
    Q_OBJECT
public:
    explicit httpUtil(QObject *parent = nullptr);

    QNetworkAccessManager *manager;


    void get(QString url,QMap<QString,QString> params);

    void post(QString url,QMap<QString,QString> params);

    void postBody(QString url,QJsonObject jsonObject);

    void loadUrlPic(QString url);

    void downLoadFile(QString url,QMap<QString,QString> params);



signals:

    void responseGet(QString result);

    void responsePost(QString result);

    void responsePic(QPixmap *pix);

    void responseDownloadFile(QByteArray result);

};

#endif // HTTPUTIL_H
