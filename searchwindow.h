#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

private slots:
    void on_CloseButton_clicked();

    void on_DoButton_clicked();

    void on_InputBut_clicked();

    void on_OutputBut_clicked();

    void on_ValueBut_clicked();

private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
