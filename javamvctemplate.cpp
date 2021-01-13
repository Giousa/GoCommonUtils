#include "javamvctemplate.h"
#include "ui_javamvctemplate.h"
#include "toolsmenuwidget.h"

JavaMVCTemplate::JavaMVCTemplate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JavaMVCTemplate)
{
    ui->setupUi(this);

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
}
