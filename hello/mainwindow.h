#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QTextCodec>
#include <QtCore/qmath.h>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QStack>
#include <string>

namespace Ui {
        class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

        public:
                explicit MainWindow(QWidget *parent = 0);
                ~MainWindow();

        private:
                Ui::MainWindow *ui;

                int quantity;  // 0, 1, 2, 3, 4
                int range;  // 0, 1, 2, 3
                int type;  // 0, 1, 2
                std::string title;
                std::string saved_name;
                std::vector<std::string> str_exps;

                // quantity
                QLabel *label_quantity;
                QComboBox *combobox_quantity;  // five

                // Range
                QLabel *label_range;
                QComboBox *combobox_range;  // 100, 1000, 10000

                // Expression Type
                QLabel *label_type;
                QComboBox *combobox_type;

                // Title
                QLabel *label_title;
                QLineEdit *line_edit_title;

                // confirm and cancel and preview
                QPushButton *button_confirm;
                QPushButton *button_cancel;
                QPushButton *button_preview;
                QPushButton *button_gen_ans;  // generate answer


                /* create expressions */
                bool createExpressions();
                bool createAnswers(std::vector<int> &);
                bool saveResult();

        private slots:
                void comboboxQuantity(const QString&);
                void comboboxRange(const QString&);
                void comboboxType(const QString&);
                void lineEditTitle(const QString&);

                void buttonConfirmClicked();
                void buttonCancelClicked();
                void buttonPreviewClicked();
                void buttonGenAnsClicked();
};

#endif // MAINWINDOW_H
