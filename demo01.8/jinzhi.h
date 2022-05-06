#ifndef JINZHI_H
#define JINZHI_H

#include <QWidget>
#include <mainwindow.h>
namespace Ui {
class jinzhi;
}

class jinzhi : public QWidget
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
    void on_pushButton_11_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_zhuan_clicked();

public:
    explicit jinzhi(QWidget *parent = 0);
    ~jinzhi();

private:
    Ui::jinzhi *ui;
    QString Qsjinzhi;
};

#endif // JINZHI_H
