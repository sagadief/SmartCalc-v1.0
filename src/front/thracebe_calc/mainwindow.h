#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>

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


private slots:
    void digit_numbers();

    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_AC_clicked();
    void on_pushButton_equals_clicked();
    void math_operations();
    void brackets();
};

#endif // MAINWINDOW_H
