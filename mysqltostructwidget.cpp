#include "mysqltostructwidget.h"
#include "ui_mysqltostructwidget.h"
#include "toolsmenuwidget.h"
#include <QMessageBox>
#include <QFileDialog>

MysqlToStructWidget::MysqlToStructWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MysqlToStructWidget)
{
    ui->setupUi(this);

    t = new httpUtil();

    connect(t,&httpUtil::responseGet,this,&MysqlToStructWidget::responseMysqlToStructResult);
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

    path = filePath;

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
    qDebug() << "路径地址：" << path;

    QString title = "是否打开路径目录？";
    QString info = "生成结果：成功！";
    if(result != "ok"){
        title = "文件生成失败!";
        info = "原因："+result;
    }

    QMessageBox msgBox;
    msgBox.setText(title);
    msgBox.setInformativeText(info);
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setStyleSheet("QLabel{"
                         "min-width:400px;"
                         "min-height:40px; "
                         "font-size:16px;"
                         "}");


    int re = msgBox.exec();
    switch (re){
        case QMessageBox::Yes:
            qDebug()<<"Yes";
            if(result == "ok"){
                //打开目录
                QFileDialog::getOpenFileName(this,"打开文件目录",path);
            }
            break;
        case QMessageBox::No:
            qDebug()<<"No";
            break;
        default:
            break;
    }
}
