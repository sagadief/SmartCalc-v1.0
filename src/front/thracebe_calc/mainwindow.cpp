#include "mainwindow.h"
#include "head.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multi, SIGNAL(clicked()), this, SLOT(math_operations()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::digit_numbers()
{
    QPushButton *button =  (QPushButton *) sender();

    double all_numbers;
    QString new_label;
    all_numbers = (ui->resultat->text() + button->text()).toDouble();
    new_label = QString::number(all_numbers, 'g', 15);

    ui->resultat->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->resultat->text().contains('.')))
        ui->resultat->setText(ui->resultat->text() + '.');
}


void MainWindow::operations()
{
    QPushButton *button =  (QPushButton *) sender();
    double all_numbers;
    QString new_label;
    if (button-> text() == '%') {
        all_numbers = (ui->resultat->text() + button->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers, 'g', 15);

        ui->resultat->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton *button =  (QPushButton *) sender();

    button->setChecked(true);
    double all_numbers;
    QString new_label;
    if (button-> text() == '%') {
        all_numbers = (ui->resultat->text() + button->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers, 'g', 15);

        ui->resultat->setText(new_label);
    }
}










void MainWindow::on_pushButton_AC_clicked()
{

}


void MainWindow::on_pushButton_equals_clicked()
{
    t_stack* postfix = NULL;
    QString infix = ui->resultat->text();
    QByteArray infixBytes = infix.toLatin1();
    char* infixChar = infixBytes.data();
    infixToPostfix(infixChar, &postfix);
}




























