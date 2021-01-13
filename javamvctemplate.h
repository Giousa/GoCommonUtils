#ifndef JAVAMVCTEMPLATE_H
#define JAVAMVCTEMPLATE_H

#include <QWidget>
#include "httputil.h"

namespace Ui {
class JavaMVCTemplate;
}

class JavaMVCTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit JavaMVCTemplate(QWidget *parent = nullptr);
    ~JavaMVCTemplate();

     httpUtil *ht;

     QString path;

private slots:
    void on_back_clicked();

    void on_buildTemplate_clicked();

     void responseJavaTemplateResult(QString result);

private:
    Ui::JavaMVCTemplate *ui;
};

#endif // JAVAMVCTEMPLATE_H
