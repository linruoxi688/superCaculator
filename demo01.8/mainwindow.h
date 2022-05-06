#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <QMainWindow>
#include <QStack>
#include <QVector>
#include <string.h>
#include <jinzhi.h>
#include <juzhen.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void on_kuohao_1_clicked();
    void on_kuohao_2_clicked();
    void on_pushButton_j_clicked();
    void on_pushButton_jian_clicked();
    void on_pushButton_c_clicked();
    void on_pushButton_chu_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_d_clicked();
    void on_pushButton_jinzhi_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_juzhen_clicked();

private:
    Ui::MainWindow *ui;
    QString expression;

};

#endif // MAINWINDOW_H
