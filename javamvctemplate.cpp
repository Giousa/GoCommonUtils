#include "javamvctemplate.h"
#include "ui_javamvctemplate.h"
#include "toolsmenuwidget.h"
#include <QMessageBox>
#include <QFileDialog>

JavaMVCTemplate::JavaMVCTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JavaMVCTemplate)
{
    ui->setupUi(this);

    ht = new httpUtil(this);

    connect(ht,&httpUtil::responseGet,this,&JavaMVCTemplate::responseJavaTemplateResult);

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
        return;
    }


    QMap<QString,QString> params;
    params.insert("storageAddress",path);
    params.insert("packageName",package);
    params.insert("classNames",classList);
    params.insert("resultBody",returnBody);
    params.insert("author",author);
    params.insert("email",email);

    ht->get("http://localhost:8282/buildJavaMVCTemplate/",params);

}

void JavaMVCTemplate::responseJavaTemplateResult(QString result)
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
