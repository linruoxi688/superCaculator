#ifndef JUZHEN_H
#define JUZHEN_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class juzhen;
}

class juzhen : public QWidget
{
    Q_OBJECT

private slots:
    void on_pushButton_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_delete_clicked();

public:
    explicit juzhen(QWidget *parent = 0);
    ~juzhen();
private:
    Ui::juzhen *ui;
    QString Qsjuzhen;
    QString jieguo;
    QString a1[99]={0};
    QString a2[99]={0};
    QString a3[99]={0};
    int m = 2;
    int n = 2;
    int b1[99]={0};
    int b2[99]={0};
    int num1[99][99]={{0}};
};

#endif // JUZHEN_H
