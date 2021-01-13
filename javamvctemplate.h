#ifndef JAVAMVCTEMPLATE_H
#define JAVAMVCTEMPLATE_H

#include <QWidget>

namespace Ui {
class JavaMVCTemplate;
}

class JavaMVCTemplate : public QWidget
{
    Q_OBJECT

public:
    explicit JavaMVCTemplate(QWidget *parent = nullptr);
    ~JavaMVCTemplate();

private slots:
    void on_back_clicked();

    void on_buildTemplate_clicked();

private:
    Ui::JavaMVCTemplate *ui;
};

#endif // JAVAMVCTEMPLATE_H
