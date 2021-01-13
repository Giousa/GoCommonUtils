#include "javamvctemplate.h"
#include "ui_javamvctemplate.h"
#include "toolsmenuwidget.h"

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
    //TODO 请求接口

    QString path = ui->editPath->text();
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
}
