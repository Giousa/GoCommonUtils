#include "httputil.h"

httpUtil::httpUtil(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
}


QString getRealUrl(QString url, QMap<QString, QString> params);
QByteArray getQByteArrayData(QMap<QString, QString> params);
QString getSuffixParams(QMap<QString, QString> params);
QJsonObject parseRequestResult(QByteArray resultArray);

void httpUtil::get(QString url, QMap<QString, QString> params)
{
    QString realUrl = getRealUrl(url,params);
    qDebug() << "GET请求地址：" << realUrl;
    connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *reply){
        if (reply->error() == QNetworkReply::NoError){
             QByteArray bytes = reply->readAll();
             if(bytes != ""){
//                 qDebug() << "get 返回结果：" << QString(bytes);
//                 QJsonObject result = parseRequestResult(bytes);
//                 qDebug() << result;
                 responseGet(QString(bytes));

             }

         }else{
             qDebug()<<"get connect error";
         }
         reply->deleteLater();

    });

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json")); //设置数据类型


    request.setUrl(QUrl(realUrl));

    manager->get(request);
}

void httpUtil::post(QString url, QMap<QString, QString> params)
{
    qDebug() << "POST请求地址：" << url;
    connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *reply){
        if (reply->error() == QNetworkReply::NoError){
             QByteArray bytes = reply->readAll();
             if(bytes != ""){
//                 QJsonObject result = parseRequestResult(bytes);
//                 qDebug() << result;
                 responsePost(QString(bytes));

             }

         }else{
             qDebug()<<"post connect error";
         }
         reply->deleteLater();

    });

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(QUrl(getRealUrl(url,params)));

    manager->post(request,"");
}

void httpUtil::postBody(QString url, QJsonObject jsonObject)
{
    qDebug() << "POST Body请求地址：" << url;
   connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *reply){
       if (reply->error() == QNetworkReply::NoError){
            QByteArray bytes = reply->readAll();
//            qDebug() << "POST Body 返回： " << bytes;
            if(bytes != ""){
//                QJsonObject result = parseRequestResult(bytes);
                responsePost(QString(bytes));

            }

        }else{
            qDebug()<<"post body 请求失败";
        }
        reply->deleteLater();

   });

   QNetworkRequest request;
   request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
//   request.setRawHeader("Content-Type", "application/json");

   request.setUrl(url);

   manager->post(request,QJsonDocument(jsonObject).toJson());
}

void httpUtil::loadUrlPic(QString url)
{
    if(url == NULL){
            qDebug() << "请求图片地址不能为空";
            return;
        }

    qDebug() << "图片加载地址：" << url;

    connect(manager, &QNetworkAccessManager::finished,[=](QNetworkReply *reply){
        if (reply->error() == QNetworkReply::NoError){
             qDebug() << "加载图片成功";
             QByteArray bytes = reply->readAll();
//             qDebug() << "加载图片返回结果: " << bytes;
             if(bytes != ""){

                 QPixmap *pix = new QPixmap();
                 pix->loadFromData(bytes);
                 pix->save("./"+url);

                 responsePic(pix);
             }

         }else{
             qDebug()<<"图片加载失败";
         }
         reply->deleteLater();

    });
//    QUrl qUrl(url);
    QNetworkRequest request;
//    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(url);


    qDebug() << "开始请求：";

    manager->get(request);
}


QString getRealUrl(QString url, QMap<QString, QString> params){

    if(params.size() > 0){
        QString suffixParams = "?";
        int count = 1;
        for(QMap<QString,QString>::iterator it = params.begin();it != params.end();it++,count++){
            qDebug() << "参数：key = " << it.key()  << ", value = " << it.value();

            if(count == 1){
                suffixParams.append(it.key());
            }else{
                suffixParams.append("&").append(it.key());
            }
            suffixParams.append("=").append(it.value());
        }

        url = url+suffixParams;

    }

    qDebug() << "真实请求地址：" << url;
    return url;
}


QString getSuffixParams(QMap<QString, QString> params){

    QString suffixParams;
    if(params.size() > 0){
        suffixParams.append("?");
        int count = 1;
        for(QMap<QString,QString>::iterator it = params.begin();it != params.end();it++,count++){
            qDebug() << *it;
            qDebug() << "参数：key = " << it.key()  << ", value = " << it.value();
            qDebug() << count;

            if(count == 1){
                suffixParams.append(it.key());
            }else{
                suffixParams.append("&").append(it.key());
            }
            suffixParams.append("=").append(it.value());
        }

    }

    qDebug() << "真实后缀：" << suffixParams;
    return suffixParams;
}



QByteArray getQByteArrayData(QMap<QString, QString> params){

    QByteArray byteArray;

    if(params.size() > 0){

        QJsonObject obj;
        for(QMap<QString,QString>::iterator it = params.begin();it != params.end();it++){
            qDebug() << "参数：key = " << it.key()  << ", value = " << it.value();
            obj.insert(it.key(), it.value());
        }

        byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);

    }

    qDebug() << "post QByteArray格式：" << byteArray;

    return byteArray;
}

QJsonObject parseRequestResult(QByteArray resultArray){
//    QString result = QString::fromStdString(resultArray.toStdString()).toUtf8();
    QString result = QString(resultArray);
    QJsonDocument document;
    QJsonParseError ParseError;
    document = QJsonDocument::fromJson(result.toUtf8(), &ParseError);

    QJsonObject dataObj;

    if (!document.isNull() && ParseError.error == QJsonParseError::NoError)
    {
        if (document.isObject())
        {
            QJsonObject Object = document.object(); //获取文档对象
            dataObj = Object;
//            if (!Object.isEmpty())
//            {
//                QJsonValue codeVal = Object.value("code");
//                QJsonValue dataVal = Object.value("data");
//                QJsonValue msgVal = Object.value("message");

//                if (codeVal.toInt() == 0)
//                {
//                    dataObj = dataVal.toObject();
//                    return dataObj;
//                }else{
//                    return Object.value("message").toObject();
//                }
//            }
        }
    }


    return dataObj;
}
