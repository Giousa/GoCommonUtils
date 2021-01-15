#include "javamvctemplate.h"
#include "ui_javamvctemplate.h"
#include "toolsmenuwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

void createFile(QString filePath,QString fileName);

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

    QString deskPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    qDebug() << "文件地址:" << deskPath;
    createFile(deskPath+"/temp/","javaTemplate.zip");
    QString filePath = deskPath+"/temp/javaTemplate.zip";

//    createFile(deskPath+"/temp/","javaTemplate.jpg");
//    QString filePath = deskPath+"/temp/javaTemplate.jpg";

    QFile file(filePath);
    file.open(QIODevice::ReadWrite);
    file.write(result);


}

void JavaMVCTemplate::on_btnDownload_clicked()
{
    QMap<QString,QString> params;
    //如：https://chdspine.oss-cn-shanghai.aliyuncs.com/ai/9b0360772bf44cbb87e269f543a59920.png
    t_down->downLoadFile("http://139.224.46.106:8282/downloadJavaMVCTemplate",params);
//    t_down->downLoadFile("https://chdspine.oss-cn-shanghai.aliyuncs.com/ai/9b0360772bf44cbb87e269f543a59920.png",params);

}


void createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        qDebug()<<QObject::tr("文件存在");
        return ;
    }
    //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
    }
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
    qDebug()<<tempDir.currentPath();
}
