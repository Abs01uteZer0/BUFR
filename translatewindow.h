#ifndef TRANSLATEWINDOW_H
#define TRANSLATEWINDOW_H
#include <QDialog>
namespace Ui {
class TranslateWindow;
}

class TranslateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TranslateWindow(QWidget *parent = 0);
    ~TranslateWindow();

private slots:
    void on_CloseButton_clicked();

    void on_DoButton_clicked();

    void on_pushButton_2_clicked();

    void on_InputButton_clicked();

    void on_OutputButton_clicked();

private:
    Ui::TranslateWindow *ui;
};

#endif // TRANSLATEWINDOW_H
