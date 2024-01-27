#include "mainwindow.h"
#include "./ui_mainwindow.h"

//double num_first;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_wtf, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
//    ui->pushButton_divide->setCheckable(true);
//    ui->pushButton_multiply->setCheckable(true);
//    ui->pushButton_minus->setCheckable(true);
//    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_equal->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    if (ui->pushButton_equal->isChecked()) {
        ui->func->setText("");
        ui->result->setText("");
        ui->pushButton_equal->setChecked(false);
    }
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    if (ui->result->text().contains(".") &&  button->text() == "0") {
        ui->result->setText(ui->result->text() + button->text());
    } else {
        all_numbers = (ui->result->text() + button->text()).toDouble();
        ui->result->setText(QString::number(all_numbers, 'g', 13));
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->result->text().contains('.'))) {
        ui->result->setText(ui->result->text() + ".");
    }
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    double all_numbers;
    if (button->text() == "+/-") {
        all_numbers = (ui->result->text()).toDouble();
        all_numbers *= -1;
        ui->result->setText(QString::number(all_numbers, 'g', 13));
    } else if (button->text() == "%") {
        all_numbers = (ui->result->text()).toDouble();
        all_numbers *= 0.01;
        ui->result->setText(QString::number(all_numbers, 'g', 13));
    }

}

void MainWindow::math_operations()
{
//    ui->pushButton_plus->setChecked(false);
//    ui->pushButton_minus->setChecked(false);
//    ui->pushButton_divide->setChecked(false);
//    ui->pushButton_multiply->setChecked(false);

    if (ui->pushButton_equal->isChecked()) {
        if (ui->result->text() == "Division by 0") {
            ui->func->setText("0");
        } else {
            ui->func->setText(ui->result->text());
        }
        ui->result->setText("");
        ui->pushButton_equal->setChecked(false);
    }

    QPushButton *button = (QPushButton *)sender();

    if (ui->func->text() == "") {
        if (ui->result->text()[0] == '-') {
            ui->func->setText('(' + ui->result->text() + ')' + button->text());
        } else {
            ui->func->setText(ui->result->text() + button->text());
        }
    } else {
        if (QString("÷×+-").contains(ui->func->text().back())) {
            if (ui->result->text() == "") {
                ui->func->setText(ui->func->text().chopped(1));
                ui->func->setText(ui->func->text() + button->text());
            }
            else {
                if (ui->result->text()[0] == '-') {
                    ui->func->setText(ui->func->text() + '(' + ui->result->text() + ')' + button->text());
                } else {
                    ui->func->setText(ui->func->text() + ui->result->text() + button->text());
                }
            }
        } else {
            if (ui->result->text()[0] == '-') {
                ui->func->setText(ui->func->text() + '(' + ui->result->text() + ')' + button->text());
            } else {
                ui->func->setText(ui->func->text() + ui->result->text() + button->text());
            }
        }
    }

//    num_first = ui->result->text().toDouble();
    ui->result->setText("");
//    button->setChecked(true);
}

void MainWindow::on_pushButton_AC_clicked()
{
//    ui->pushButton_plus->setChecked(false);
//    ui->pushButton_minus->setChecked(false);
//    ui->pushButton_divide->setChecked(false);
//    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_equal->setChecked(false);
    ui->result->setText("0");
    ui->func->setText("");
}

void MainWindow::on_pushButton_equal_clicked()
{
    if (ui->func->text() != "" && QString("÷×+-").contains(ui->func->text().back()) && ui->result->text() == "") {
        ui->func->setText(ui->func->text().chopped(1));
    }
    if (ui->func->text().contains("=") == false && ui->result->text() != "Division by 0") {
        ui->func->setText(ui->func->text() + ui->result->text());
    }
    QString _func = ui->func->text();
    _func = _func.remove("(");
    _func = _func.remove(")");
    _func.replace("--", "+");
    _func.replace("-+", "-");
    _func.replace("+-", "-");
    while (true) {
        while (_func.contains("×") || _func.contains("÷")) {
            int i;
            if (_func.indexOf("×") < _func.indexOf("÷") && _func.indexOf("×") != -1 && _func.indexOf("÷") != -1) {
                i = _func.indexOf("×");
            } else if (_func.indexOf("×") != -1 && _func.indexOf("÷") != -1) {
                i = _func.indexOf("÷");
            } else if (_func.indexOf("×") != -1) {
                i = _func.indexOf("×");
            } else {
                i = _func.indexOf("÷");
            }
            int j = i;
            int k = i;
            QString num1 = "";
            QString num2 = "";
            while (_func[j+1].isDigit() || _func[j+1] == "." || (_func[j+1] == "-" && j + 1 == i + 1)) {
                j++;
                num2 = num2 + _func[j];
            }
            while (k - 1 >= 0 && (_func[k-1].isDigit() || _func[k-1] == "." || _func[k-1] == "-" || _func[k-1] == "+")) {
                k--;
                num1 = _func[k] + num1;
                if (_func[k] == "-" || _func[k] == "+") {
                    break;
                }
            }
//            qDebug() << k << " " << i << " " << j;
//            qDebug() << num1 << " " << num2;
            double newnum;
            if (_func[i] == "×") {
                newnum = num1.toDouble() * num2.toDouble();
            } else {
                if (num2.toDouble() == 0) {
                    ui->result->setText("Division by 0");
                    ui->pushButton_equal->setChecked(true);
                    return;
                }
                newnum = num1.toDouble() / num2.toDouble();
            }
            if (num1.toDouble() * num2.toDouble() >= 0 && k != 0) {
                _func.replace(k, j - k + 1, "+" + QString::number(newnum, 'g', 13));
            } else {
                _func.replace(k, j - k + 1, QString::number(newnum, 'g', 13));
            }
//            qDebug() << _func;
        }
//        while (_func.contains("--") || _func.contains("-+") || _func.contains("++")) {
//            _func.replace("--", "+");
//            _func.replace("-+", "-");
//            _func.replace("++", "+");
//        }
        while (_func.contains("+")) {
            int i = _func.indexOf("+");
            int j = i;
            int k = i;
            QString num1 = "";
            QString num2 = "";
            while (_func[j+1].isDigit() || _func[j+1] == ".") {
                j++;
                num2 = num2 + _func[j];
            }
            while (k - 1 >= 0 && (_func[k-1].isDigit() || _func[k-1] == "." || _func[k-1] == "-")) {
                k--;
                num1 = _func[k] + num1;
                if (_func[k] == "-") {
                    break;
                }
            }
//            qDebug() << k << " " << i << " " << j;
//            qDebug() << num1 << " " << num2;
            double newnum = num1.toDouble() + num2.toDouble();
            if (newnum >= 0 && k != 0) {
                _func.replace(k, j - k + 1, "+" + QString::number(newnum, 'g', 13));
            } else {
                _func.replace(k, j - k + 1, QString::number(newnum, 'g', 13));
            }
//            qDebug() << _func;
        }
        while (_func.contains("-")) {
            int i = _func.lastIndexOf("-");
            int j = i;
            int k = i;
            QString num1 = "";
            QString num2 = "";
            while (_func[j+1].isDigit() || _func[j+1] == ".") {
                j++;
                num2 = num2 + _func[j];
            }
            while (k - 1 >= 0 && (_func[k-1].isDigit() || _func[k-1] == "." || _func[k-1] == "-")) {
                k--;
                num1 = _func[k] + num1;
                if (_func[k] == "-") {
                    break;
                }
            }
            if (num1 == "") {
                break;
            }
//            qDebug() << k << " " << i << " " << j;
//            qDebug() << num1 << " " << num2;
            double newnum = num1.toDouble() - num2.toDouble();
            if (newnum >= 0 && k != 0) {
                _func.replace(k, j - k + 1, "+" + QString::number(newnum, 'g', 13));
            } else {
                _func.replace(k, j - k + 1, QString::number(newnum, 'g', 13));
            }
//            qDebug() << _func;
        }
        break;
    }
    if (ui->func->text().contains("=") == false && ui->result->text() != "Division by 0") {
        ui->func->setText(ui->func->text() + "=");
        ui->result->setText(_func);
    }
    ui->pushButton_equal->setChecked(true);


//    double labelNumber, num_second;
//    num_second = ui->result->text().toDouble();
//    if(ui->pushButton_plus->isChecked()) {
//        labelNumber = num_first + num_second;
//        ui->result->setText(QString::number(labelNumber, 'g', 13));
//        ui->pushButton_plus->setChecked(false);
//    } else if(ui->pushButton_minus->isChecked()) {
//        labelNumber = num_first - num_second;
//        ui->result->setText(QString::number(labelNumber, 'g', 13));
//        ui->pushButton_minus->setChecked(false);
//    } else if(ui->pushButton_divide->isChecked()) {
//        if (num_second == 0) {
//             ui->result->setText("0");
//        } else {
//            labelNumber = num_first / num_second;
//            ui->result->setText(QString::number(labelNumber, 'g', 13));
//        }
//        ui->pushButton_divide->setChecked(false);
//    } else if(ui->pushButton_multiply->isChecked()) {
//        labelNumber = num_first * num_second;
//        ui->result->setText(QString::number(labelNumber, 'g', 13));
//        ui->pushButton_multiply->setChecked(false);
//    }
}
