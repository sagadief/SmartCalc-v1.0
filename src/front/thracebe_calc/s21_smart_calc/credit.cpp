#include "credit.h"
#include "credit.c"
#include <QDate>
#include "ui_credit.h"

credit::credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
}

credit::~credit()
{
    delete ui;
}

void credit::on_radioButton_diff_clicked()
{

}

void credit::on_radioButton_ann_clicked()
{
    types = true;
}

void credit::on_pushButton_calc_clicked()
{
      double sum = ui->label_sum_credit->value();
      int period = ui->label_period->value();
      double precent = ui->label_precent->value();

      if (types) {
        double month = month_ann(sum, period, precent);
        double total = month * period;
        double overpayment = total - sum;

        ui->label_month->setText(QString("%L1").arg(month, 0, 'f', 2));
        ui->label_total->setText(QString("%L1").arg(total, 0, 'f', 2));
        ui->label_over->setText(QString("%L1").arg(overpayment, 0, 'f', 2));
      } else {
        QDate date_current = QDate::currentDate();
//        QDate date_finish = date_current.addMonths(period);

        double sp = sum / period;
        double payment = sp + sum * precent / 100 *
                                  (date_current.daysInYear() / 12.0) /
                                  date_current.daysInYear();
        double total = payment;
        double first = payment;
        for (int i = 1; i < period; i++) {
          payment = sp + (sum - i * sp) * precent / 100 * (date_current.daysInYear() / 12.0) / date_current.daysInYear();
          date_current = date_current.addMonths(1);
          total += payment;
        }

        double last = payment;
        ui->label_month->setText(QString("%L1").arg(first, 0, 'f', 2) + ".." + QString("%L1").arg(last, 0, 'f', 2));
        ui->label_total->setText(QString("%L1").arg(total, 0, 'f', 2));
        ui->label_over->setText(QString("%L1").arg(total - sum, 0, 'f', 2));
      }
    }
