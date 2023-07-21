#include "mainwindow.h"
#include "head.h"
#include "./ui_mainwindow.h"
#include "backend.c"
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

//    button->setChecked(true);
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




//void MainWindow::on_pushButton_plus_clicked()
//{
////    QPushButton *button =  (QPushButton *) sender();
////    ui->resultat->text() + button->text();
////    ui->resultat->setText(new_label);
//    ui->resultat->setText("Hello everybody");
//}

void MainWindow::brackets()
{
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);

    QString currentText = ui->resultat->text();

//    int openBracketCount = currentText.count('(');
//    int closeBracketCount = currentText.count(')');

//    if (openBracketCount > closeBracketCount) {
//        ui->resultat->setText(currentText + ')');
//    } else {
//        ui->resultat->setText(currentText + '(');
//    }
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
////    QPushButton *button = (QPushButton *)sender();
////    QString currentText = ui->resultat->text();

////    ui->resultat->setText(currentText + 'y');
    QPushButton *button = (QPushButton *)sender();
    button->setChecked(true);
    QString new_label;
    new_label = (ui->resultat->text() + 'y');

    QString currentText = ui->peremen_y->text();

    y_value = currentText.toDouble(); // Преобразование строки в double

    ui->resultat->setText(new_label);

//    y_equal_clicked = true; // Установка флага в true после первого нажатия
}





void MainWindow::on_pushButton_equals_clicked()
{
    t_stack* postfix = NULL;
    double y = 0;
    QString infix = ui->resultat->text();
    QByteArray infixBytes = infix.toLatin1();
    char* infixChar = infixBytes.data();
    if (!(valide_str(infixChar))) {
        ui->resultat->setText("ERROR");
    } else {
        y = y_value;
        infixToPostfix(infixChar, y, &postfix);
        QString myString = QString::number(evaluatePostfix(&postfix, y));
        ui->resultat->setText(myString);


//        QVector<double> x(101), y(101); // initialize with entries 0..100
//        for (int i=0; i<101; ++i)
//        {
//          x[i] = i/50.0 - 1; // x goes from -1 to 1
//          y[i] = evaluatePostfix(&postfix, x[i]);
////          y[i] = x[i]*x[i]; // let's plot a quadratic function
//        }
//        // create graph and assign data to it:
//        customPlot->addGraph();
//        customPlot->graph(0)->setData(x, y);
//        // give the axes some labels:
//        customPlot->xAxis->setLabel("x");
//        customPlot->yAxis->setLabel("y");
//        // set axes ranges, so we see all data:
//        customPlot->xAxis->setRange(-1, 1);
//        customPlot->yAxis->setRange(0, 1);
//        customPlot->replot();



    }
}











void MainWindow::on_pushButton_degree_clicked()
{
    ui->resultat->setText(ui->resultat->text() + "^(");
}

