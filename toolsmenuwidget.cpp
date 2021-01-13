#include "toolsmenuwidget.h"
#include "ui_toolsmenuwidget.h"

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

}
