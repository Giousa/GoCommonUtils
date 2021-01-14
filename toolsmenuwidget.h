#ifndef TOOLSMENUWIDGET_H
#define TOOLSMENUWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ToolsMenuWidget; }
QT_END_NAMESPACE

class ToolsMenuWidget : public QWidget
{
    Q_OBJECT

public:
    ToolsMenuWidget(QWidget *parent = nullptr);
    ~ToolsMenuWidget();

private slots:
    void on_btnJavaMVC_clicked();

    void on_btnMysqlStruct_clicked();

private:
    Ui::ToolsMenuWidget *ui;
};
#endif // TOOLSMENUWIDGET_H
