#include "mainwindow.h"
#include "head.h"
#include "./ui_mainwindow.h"
#include "backend.c"
#include "qcustomplot.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    customPlot = new QCustomPlot();

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));


    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigon()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trigon()));



    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multi, SIGNAL(clicked()), this, SLOT(math_operations()));

    connect(ui->pushButton_bracket_left, SIGNAL(clicked()), this, SLOT(brackets()));
    connect(ui->pushButton_bracket_right, SIGNAL(clicked()), this, SLOT(brackets()));

    y_equal_clicked = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::digit_numbers()
{
    QPushButton *button =  (QPushButton *) sender();

    QString new_label;
    new_label = (ui->resultat->text() + button->text());
    ui->resultat->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->resultat->text().endsWith('.')))
        ui->resultat->setText(ui->resultat->text() + '.');
}


void MainWindow::math_operations()
{
    QPushButton *button =  (QPushButton *) sender();
    QString new_label;
    new_label = (ui->resultat->text() + button->text());
    ui->resultat->setText(new_label);
}


void MainWindow::trigon()
{
    QPushButton *button =  (QPushButton *) sender();

    QString new_label;
    new_label = (ui->resultat->text() + button->text() + '(');
    ui->resultat->setText(new_label);

}

void MainWindow::brackets()
{
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);

    QString currentText = ui->resultat->text();

    if (button-> text() == '(') {
        ui->resultat->setText(currentText + '(');
    }
    if (button-> text() == ')') {
        ui->resultat->setText(currentText + ')');
    }
}


void MainWindow::on_pushButton_del_clicked()
{
      QString current_text = ui->resultat->text();
      current_text.chop(1);
      ui->resultat->setText(current_text);
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->resultat->clear();
}



void MainWindow::on_y_equal_clicked()
{
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    QString new_label;
    new_label = (ui->resultat->text() + 'x');

    QString currentText = ui->peremen_y->text();

    x_value = currentText.toDouble();

    ui->resultat->setText(new_label);
}



void MainWindow::on_pushButton_equals_clicked()
{
    t_stack* postfix = NULL;
    double x = 0;
    QString infix = ui->resultat->text();
    QByteArray infixBytes = infix.toLatin1();
    char* infixChar = infixBytes.data();
    if (!(valide_str(infixChar))) {
        ui->resultat->setText("ERROR");
    } else {
        x = x_value;
        if (infixChar[0] == 'x' && infixChar[1] == '\0')
            ui->resultat->setText("ERROR");
        else {
            infixToPostfix(infixChar, x, &postfix);
            double result = evaluatePostfix(&postfix, x);
            QString myString = QString::number(result);
            ui->resultat->setText(myString);
        }
    }
}


void MainWindow::on_pushButton_build_clicked()
{
    t_stack* postfix = NULL;
    double x = 0;
    QString infix = ui->resultat->text();
    QByteArray infixBytes = infix.toLatin1();
    char* infixChar = infixBytes.data();
    if (!(valide_str(infixChar))) {
            ui->resultat->setText("ERROR");
        } else {
        x = x_value;
        infixToPostfix(infixChar, x, &postfix);
        double result = evaluatePostfix(&postfix, x);
        QString myString = QString::number(result);
        QVector<double> xx,yy;
        ui->customPlot->clearGraphs();
        xx.clear();
        yy.clear();
        xBegin = ui->x_min->text().toDouble();
        h = 0.1;
        double res = 0;
        xEnd = ui->x_max->text().toDouble() + h;
        ui->customPlot->xAxis->setRange(ui->x_min->text().toDouble(),
                                        ui->x_max->text().toDouble());
        ui->customPlot->yAxis->setRange(ui->y_min->text().toDouble(),
                                        ui->y_max->text().toDouble());
        X = xBegin;
        N = (xEnd - xBegin) / h + 2;
            for (X = xBegin; X <= xEnd; X += h) {
            xx.push_back(X);
            infixToPostfix(infixChar, X, &postfix);
            result = evaluatePostfix(&postfix, X);
            yy.push_back(result);
        }


            ui->customPlot->addGraph();
            ui->customPlot->graph(0)->addData(xx, yy);
            ui->customPlot->replot();
    }
}


void MainWindow::on_pushButton_degree_clicked()
{
    ui->resultat->setText(ui->resultat->text() + "^(");
}


void MainWindow::on_pushButton_credit_clicked()
{
    credit.show();
}

