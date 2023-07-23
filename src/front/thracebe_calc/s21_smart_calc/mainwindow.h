#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include "qcustomplot.h"
#include <credit.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    credit credit;

    double xBegin, xEnd, h, X;
    int N;
    bool buildButtonClicked = false;

private:
    bool y_equal_clicked;
    double x_value;

private slots:
    void digit_numbers();
    void on_pushButton_dot_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_equals_clicked();
    void math_operations();
    void brackets();
    void on_y_equal_clicked();
    void trigon();
    void on_pushButton_degree_clicked();
    void on_pushButton_credit_clicked();
    void on_pushButton_build_clicked();
    void on_pushButton_del_clicked();

};



#endif // MAINWINDOW_H
