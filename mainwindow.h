#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_about_triggered();

    void on_help_triggered();

    void on_quit_triggered();

    void on_Exit_clicked();

    void on_Translate_clicked();

    void on_Search_clicked();

    void on_MenuTranslate_triggered();

    void on_MenuSearch_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
