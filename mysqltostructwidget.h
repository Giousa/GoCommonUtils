#ifndef MYSQLTOSTRUCTWIDGET_H
#define MYSQLTOSTRUCTWIDGET_H

#include <QWidget>
#include "httputil.h"

namespace Ui {
class MysqlToStructWidget;
}

class MysqlToStructWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MysqlToStructWidget(QWidget *parent = nullptr);
    ~MysqlToStructWidget();

    httpUtil *t;

    QString path;

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void responseMysqlToStructResult(QString result);

private:
    Ui::MysqlToStructWidget *ui;
};

#endif // MYSQLTOSTRUCTWIDGET_H
