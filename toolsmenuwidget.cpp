#include "toolsmenuwidget.h"
#include "ui_toolsmenuwidget.h"
#include "javamvctemplate.h"

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
