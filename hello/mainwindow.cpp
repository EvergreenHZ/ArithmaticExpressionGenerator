#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ArithmaticExpression.h"
#include "Evaluation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>
#include <cstdlib>
#include <cstdio>
using namespace std;

const char* QUANTITY_TYPE[5] = {\
        "25 x 2", "22 x 2", "18 x 2", "15 x 2", "11 x 2"};
const char* RANGE_TYPE[4]    = {\
        "100", "1000", "10000", "100000" };
const char* EXPRESSION_TYPE[3] = {\
        "a op b", "a op b op c", "mix"};
const int INT_QUANTITY_TYPE[5] = {\
        50, 44, 36, 30, 22, };
const int INT_RANGE_TYPE[4]    = {\
        100, 1000, 10000, 100000, };
//const int INT_EXPRESSION_TYPE[3] = { no need


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        quantity = 0;
        range    = 0;
        type     = 0;
        saved_name = string("result");

        QWidget *widget = new QWidget;
        this-> setCentralWidget(widget);
        this-> setFixedSize(this->width(), this->height());

        // quantity
        label_quantity = new QLabel(tr("Quantity:"));
        combobox_quantity = new QComboBox;
        combobox_quantity->addItem(tr("25 x 2"));
        combobox_quantity->addItem(tr("22 x 2"));
        combobox_quantity->addItem(tr("18 x 2"));
        combobox_quantity->addItem(tr("15 x 2"));
        combobox_quantity->addItem(tr("11 x 2"));


        // range
        label_range = new QLabel(tr("Range:"));
        combobox_range = new QComboBox;
        combobox_range->addItem(tr("100"));
        combobox_range->addItem(tr("1000"));
        combobox_range->addItem(tr("10000"));
        combobox_range->addItem(tr("100000"));

        // type
        label_type = new QLabel(tr("Type:"));
        combobox_type = new QComboBox;
        combobox_type->addItem(tr("a op b"));
        combobox_type->addItem(tr("a op b op c"));
        combobox_type->addItem(tr("mix"));

        // title
        label_title = new QLabel(tr("Title"));
        line_edit_title = new QLineEdit(tr("Quiz 1"));

        // button
        button_confirm = new QPushButton("confirm");
        button_cancel = new QPushButton("cancel");
        button_preview = new QPushButton("preview");
        button_gen_ans = new QPushButton("answer");

        // layout
        QGridLayout *layout = new QGridLayout(this);

        layout->addWidget(label_quantity, 0, 0);
        layout->addWidget(combobox_quantity, 0, 1);

        layout->addWidget(label_range, 1, 0);
        layout->addWidget(combobox_range, 1, 1);

        layout->addWidget(label_type, 2, 0);
        layout->addWidget(combobox_type, 2, 1);

        layout->addWidget(label_title, 3, 0);
        layout->addWidget(line_edit_title, 3,1);

        layout->addWidget(button_confirm, 4, 0);
        layout->addWidget(button_cancel, 4, 1);
        layout->addWidget(button_preview, 5, 0);
        layout->addWidget(button_gen_ans, 5, 1);

        connect(combobox_quantity, SIGNAL(currentIndexChanged(const QString&)),\
                        this, SLOT(comboboxQuantity(const QString&)));
        connect(combobox_range   , SIGNAL(currentIndexChanged(const QString&)),\
                        this, SLOT(comboboxRange(const QString&)));
        connect(combobox_type    , SIGNAL(textChanged(const QString&)),\
                        this, SLOT(comboboxType(const QString&)));
        connect(line_edit_title, SIGNAL(currentIndexChanged(const QString&)),\
                        this, SLOT(lineEditTitle(const QString&)));

        connect(button_confirm, SIGNAL(clicked()), this, SLOT(buttonConfirmClicked()));
        connect(button_cancel, SIGNAL(clicked()), this, SLOT(buttonCancelClicked()));
        // use system to evince the pdf file
        connect(button_preview, SIGNAL(clicked()), this, SLOT(buttonPreviewClicked()));
        connect(button_gen_ans, SIGNAL(clicked()), this, SLOT(buttonGenAnsClicked()));
        widget->setLayout(layout);
}

void MainWindow::buttonConfirmClicked()
{
        // generate equation using quantity, range, type
        // I need ArithmaticExpression and Evaluation
        qInfo()<< "touch the confirm button" << endl;
        if (createExpressions()) {
                saveResult();
                qInfo()<< "save succeed" << endl;

        }

}

void MainWindow::buttonCancelClicked()
{
        QApplication *app;
        app->exit(0);
}

void MainWindow::buttonPreviewClicked()
{
        system("rm result && gedit result");
}

void MainWindow::buttonGenAnsClicked()
{
        // actually I can generate the answer at the same time
        vector<int> ans;
        createAnswers(ans);
}

void MainWindow::comboboxQuantity(const QString& quantity)
{
        string str_quantity = quantity.toStdString();
        const char* data = str_quantity.c_str();
        cout << data << endl;
        for (int i = 0; i < 5; i++) {  // here is 5
                qInfo() << QUANTITY_TYPE[i] << endl;
                if (strcmp(data, QUANTITY_TYPE[i]) == 0) {
                        this->quantity = i;
                        break;
                }
        }
}

void MainWindow::comboboxRange(const QString& range)
{
        string str_range = range.toStdString();
        const char *data = str_range.c_str();
        //string str_range = range.toUtf8().constData();

        for (int i = 0; i < 4; i++) {  // here is 5
                if (strcmp(data, RANGE_TYPE[i]) == 0) {
                        this->range = i;
                        break;
                }
        }
}

void MainWindow::comboboxType(const QString& type)
{
        string str_type = type.toStdString();
        const char *data = str_type.c_str();

        for (int i = 0; i < 3; i++) {  // here is 5
                if (strcmp(data, EXPRESSION_TYPE[i]) == 0) {
                        this->type = i;
                        break;
                }
        }
}

void MainWindow::lineEditTitle(const QString & title)
{
        string tmp_title = title.toStdString();
        this->title = tmp_title;
}


MainWindow::~MainWindow()
{
        delete ui;
}

bool MainWindow::createExpressions()
{
        int  int_quantity = INT_QUANTITY_TYPE[quantity];
        int int_range    = INT_RANGE_TYPE[range];


        qInfo() << "int_quantity: " << int_quantity <<endl;

        // create a expression generator
        ArithmaticExpression aexp_gen(int_range);

        //vector< vector<string> > exps;
        //vector<string> str_exps;

        if (type == 0) {  // just a op b
                for (int i = 0; i < int_quantity; i++) {
                        vector<string> tmp_exp;
                        while (!aexp_gen.gen_a_op_b(tmp_exp)) {
                                tmp_exp.clear();
                        }
                        string tmp_str_exp;
                        if (aexp_gen.convert_to_string_expression(tmp_exp, tmp_str_exp)) {
                                str_exps.push_back(tmp_str_exp);
                        }
                }
        } else if (type == 1) {  // a op b op c
                for (int i = 0; i < int_quantity; i++) {
                        vector<string> tmp_exp;
                        tmp_exp = aexp_gen.gen_a_op_b_op_c();
                        while (tmp_exp.size() == 0) {
                                tmp_exp.clear();
                                tmp_exp = aexp_gen.gen_a_op_b_op_c();
                        }
                        string tmp_str_exp;
                        if (aexp_gen.convert_to_string_expression(tmp_exp, tmp_str_exp)) {
                                str_exps.push_back(tmp_str_exp);
                        }
                }
        } else {  // type == 2  mix
                for (int i = 0; i < int_quantity; i++) {
                        if (aexp_gen.cast_coin()) {
                                vector<string> tmp_exp;
                                while (!aexp_gen.gen_a_op_b(tmp_exp)) {
                                        tmp_exp.clear();
                                }
                                string tmp_str_exp;
                                if (aexp_gen.convert_to_string_expression(tmp_exp, tmp_str_exp)) {
                                        str_exps.push_back(tmp_str_exp);
                                }
                        } else {
                                vector<string> tmp_exp;
                                tmp_exp = aexp_gen.gen_a_op_b_op_c();
                                while (tmp_exp.size() == 0) {
                                        tmp_exp.clear();
                                        tmp_exp = aexp_gen.gen_a_op_b_op_c();
                                }
                                string tmp_str_exp;
                                if (aexp_gen.convert_to_string_expression(tmp_exp, tmp_str_exp)) {
                                        str_exps.push_back(tmp_str_exp);
                                }
                        }
                }
        }
        if (str_exps.size() != int_quantity) {
                return false;
        }
        return true;
}

bool MainWindow::saveResult()
{
        ofstream file(saved_name.c_str(), ios::app);
        // write files
        
        int cols = 2;
        int int_quantity = INT_QUANTITY_TYPE[quantity];
        int rows = int_quantity / 2;
        for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                        file << str_exps[i * cols + j] << '\t';
                        cout  << str_exps[i * cols + j] << '\t';
                }
                cout << endl;
                file << endl;
        }
        return true;
}

bool MainWindow::createAnswers(vector<int> &ans)
{
        // generate an evaluator
        if (str_exps.size() == 0) {
                return false;
        }

        Evaluation evaluator;
        for (int i = 0; i < str_exps.size(); i++) {
                ans.push_back(evaluator.solution(str_exps[i]));
        }

        return true;
}











