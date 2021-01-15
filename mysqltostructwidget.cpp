#include "mysqltostructwidget.h"
#include "ui_mysqltostructwidget.h"
#include "toolsmenuwidget.h"
#include <QMessageBox>
#include <QFileDialog>
#include "fileutils.h"

MysqlToStructWidget::MysqlToStructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysqlToStructWidget)
{
    ui->setupUi(this);

    t = new httpUtil();
    t_down = new httpUtil();

    connect(t,&httpUtil::responseGet,this,&MysqlToStructWidget::responseMysqlToStructResult);

    connect(t_down,&httpUtil::responseDownloadFile,this,&MysqlToStructWidget::responseDownloadResult);
}

MysqlToStructWidget::~MysqlToStructWidget()
{
    delete ui;
}

void MysqlToStructWidget::on_toolButton_clicked()
{
    ToolsMenuWidget *t = new ToolsMenuWidget();
    t->show();
    this->close();
}

void MysqlToStructWidget::on_pushButton_clicked()
{
    QString filePath = ui->editPath->text();
    QString fileName = ui->editFileName->text();
    QString ip = ui->editIp->text();
    QString root = ui->editRoot->text();
    QString password = ui->editPassword->text();
    QString dbName = ui->editDbName->text();

    if(filePath == "" || ip == "" || root == "" || password == "" || dbName == ""){
        qDebug() << "必填参数不能为空";
        QMessageBox msgBox;
        msgBox.setText("必填参数不能为空");
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

//    path = filePath;
//    if (fileName == ""){
//        fileName = "mysqlToStruct.go";
//    }
//    this->fileName = fileName;

    QMap<QString,QString> params;
    params.insert("storageAddress",filePath);
    params.insert("fileName",fileName);
    params.insert("ip",ip);
    params.insert("root",root);
    params.insert("password",password);
    params.insert("dbName",dbName);

//    t->get("http://localhost:8282/mysqlToStruct",params);
     t->get("http://139.224.46.106:8282/mysqlToStruct",params);

}

void MysqlToStructWidget::responseMysqlToStructResult(QString result)
{
    qDebug() << "请求结果：" << result;
    QString path = ui->editPath->text();
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

void MysqlToStructWidget::responseDownloadResult(QByteArray result)
{

    QString path = ui->editPath->text();
    QString fileName = ui->editFileName->text();
    if (fileName == ""){
        fileName = "mysqlToStruct.go";
    }

    qDebug() << "mysql转struct本地存储地址:" << path;
    FileUtils::createFile(path,"/"+fileName);
    QString filePath = path+"/"+fileName;
    qDebug() << "mysql转struct本地文件路径:" << filePath;

    QFile file(filePath);
    bool flag = file.open(QIODevice::ReadWrite);
    if (!flag) {
        file.open(QIODevice::ReadWrite);
    }
    file.write(result);
}

void MysqlToStructWidget::on_selectDir_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "选择目录","/");

    ui->editPath->setText(path);
}

void MysqlToStructWidget::on_btnDown_clicked()
{
    QMap<QString,QString> params;
    QString fileName = ui->editFileName->text();
    if (fileName == ""){
        fileName = "mysqlToStruct.go";
    }

    params.insert("fileName",fileName);
    t_down->downLoadFile("http://139.224.46.106:8282/downloadBuildFile",params);
}
