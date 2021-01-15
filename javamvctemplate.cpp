#include "javamvctemplate.h"
#include "ui_javamvctemplate.h"
#include "toolsmenuwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include "fileutils.h"


JavaMVCTemplate::JavaMVCTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JavaMVCTemplate)
{
    ui->setupUi(this);

    ht = new httpUtil(this);
    t_down = new httpUtil(this);

    connect(ht,&httpUtil::responseGet,this,&JavaMVCTemplate::responseJavaTemplateResult);

    connect(t_down,&httpUtil::responseDownloadFile,this,&JavaMVCTemplate::responseDownloadResult);

}

JavaMVCTemplate::~JavaMVCTemplate()
{
    delete ui;
}

void JavaMVCTemplate::on_back_clicked()
{
    ToolsMenuWidget *t = new ToolsMenuWidget();
    t->show();
    this->close();
}

void JavaMVCTemplate::on_buildTemplate_clicked()
{

    path = ui->editPath->text();
    QString package = ui->editPackage->text();
    QString classList = ui->editClassList->text();
    QString returnBody = ui->editReturn->text();
    QString author = ui->editAuthor->text();
    QString email = ui->editEmail->text();

    if(path == "" || package == "" || classList == ""){
        qDebug() << "路径、包名、类名不能为空";
        QMessageBox msgBox;
        msgBox.setText("路径、包名、类名不能为空");
        msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.setStyleSheet("QLabel{"
                             "min-width:400px;"
                             "min-height:40px; "
                             "font-size:16px;"
                             "}");


        msgBox.exec();
        return;
    }


    QMap<QString,QString> params;
    params.insert("storageAddress",path);
    params.insert("packageName",package);
    params.insert("classNames",classList);
    params.insert("resultBody",returnBody);
    params.insert("author",author);
    params.insert("email",email);

//    ht->get("http://localhost:8282/buildJavaMVCTemplate/",params);
    ht->get("http://139.224.46.106:8282/buildJavaMVCTemplate/",params);

}

void JavaMVCTemplate::responseJavaTemplateResult(QString result)
{
    qDebug() << "请求结果：" << result;
    qDebug() << "路径地址：" << path;

    QString title = "成功！";
    if(result != "ok"){
        title = "失败："+result;
    }

    QMessageBox msgBox;
    msgBox.setText(title);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setStyleSheet("QLabel{"
                         "min-width:400px;"
                         "min-height:40px; "
                         "font-size:16px;"
                         "}");


    msgBox.exec();



}

void JavaMVCTemplate::responseDownloadResult(QByteArray result)
{
    qDebug() << "下载返回结果：";
    qDebug() << result;

//    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
//    qDebug() << "文件地址:" << deskPath;
//    createFile(deskPath+"/temp/","javaTemplate.zip");
//    QString filePath = deskPath+"/temp/javaTemplate.zip";

//    createFile(deskPath+"/temp/","javaTemplate.jpg");
//    QString filePath = deskPath+"/temp/javaTemplate.jpg";

    qDebug() << "本地存储地址:" << path;
    FileUtils::createFile(path,"/javaTemplate.zip");
//    createFile(path,"/javaTemplate.zip");
    QString filePath = path+"/javaTemplate.zip";
    qDebug() << "本地文件路径:" << filePath;

    QFile file(filePath);
    bool flag = file.open(QIODevice::ReadWrite);
    if (!flag) {
        file.open(QIODevice::ReadWrite);
    }
    file.write(result);


}

void JavaMVCTemplate::on_btnDownload_clicked()
{
    QMap<QString,QString> params;
    params.insert("fileName","files.zip");
    //如：https://chdspine.oss-cn-shanghai.aliyuncs.com/ai/9b0360772bf44cbb87e269f543a59920.png
    //    t_down->downLoadFile("https://chdspine.oss-cn-shanghai.aliyuncs.com/ai/9b0360772bf44cbb87e269f543a59920.png",params);
    t_down->downLoadFile("http://139.224.46.106:8282/downloadBuildFile",params);


}


void JavaMVCTemplate::on_selectDir_clicked()
{
//    QString path = QFileDialog::getOpenFileName(this,"打开文件","/");
    QString path = QFileDialog::getExistingDirectory(this, "选择目录","/");

    ui->editPath->setText(path);

}
