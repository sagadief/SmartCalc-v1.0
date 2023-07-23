#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

namespace Ui {
class credit;
}

class credit : public QWidget
{
    Q_OBJECT

public:
    explicit credit(QWidget *parent = nullptr);
    ~credit();

private slots:
    void on_radioButton_ann_clicked();
    void on_radioButton_diff_clicked();
    void on_pushButton_calc_clicked();

private:
    Ui::credit *ui;
    bool types = false;
};

#endif // CREDIT_H
