//#include <QApplication>
//#include <QVBoxLayout>
//#include <QLineEdit>
//#include <QPushButton>
//#include <QLabel>
//#include <QProcess>
#include "mainwindow.h"
#include <QApplication>
//class CalculatorApp : public QWidget {
//    Q_OBJECT
//public:
//    CalculatorApp(QWidget *parent = nullptr) : QWidget(parent) {
//        layout = new QVBoxLayout(this);

//        // Поле ввода для строки калькулятора
//        inputLineEdit = new QLineEdit(this);
//        layout->addWidget(inputLineEdit);

//        // Кнопка для отправки запроса на выполнение расчетов
//        calculateButton = new QPushButton("Calculate", this);
//        layout->addWidget(calculateButton);

//        // Метка для отображения результата
//        resultLabel = new QLabel(this);
//        layout->addWidget(resultLabel);

//        // Установка соединений сигналов и слотов
//        connect(calculateButton, &QPushButton::clicked, this, &CalculatorApp::executeCalculation);
//    }

//public slots:
//    void executeCalculation() {
//        // Получение строки из поля ввода
//        QString expression = inputLineEdit->text();

//        // Вызов бекендного кода exx.c с использованием QProcess
//        QProcess process;
//        process.start("gcc", QStringList() << "-Wall" << "-o" << "exx" << "exx.c" << "-lm");
//        process.waitForFinished();
//        process.start("../../back/.exx");
//        process.waitForStarted();
//        process.write(expression.toUtf8());
//        process.closeWriteChannel();
//        process.waitForFinished();
//        QByteArray resultData = process.readAll();

//        // Преобразование ответа в строку
//        QString resultString(resultData);

//        // Отображение результата
//        resultLabel->setText("Result: " + resultString.trimmed());
//    }

//private:
//    QVBoxLayout *layout;
//    QLineEdit *inputLineEdit;
//    QPushButton *calculateButton;
//    QLabel *resultLabel;
//};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
