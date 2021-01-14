#include "toolsmenuwidget.h"
#include "ui_toolsmenuwidget.h"
#include "javamvctemplate.h"
#include "mysqltostructwidget.h"

ToolsMenuWidget::ToolsMenuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToolsMenuWidget)
{
    ui->setupUi(this);
}

ToolsMenuWidget::~ToolsMenuWidget()
{
    delete ui;
}


void ToolsMenuWidget::on_btnJavaMVC_clicked()
{
    JavaMVCTemplate *j = new JavaMVCTemplate();
    j->show();
    this->hide();
}

void ToolsMenuWidget::on_btnMysqlStruct_clicked()
{
    MysqlToStructWidget *m = new MysqlToStructWidget();
    m->show();
    this->hide();
}
