#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "searchwindow.h"
#include "translatewindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_about_triggered()
{
    QMessageBox::about(this, "about", "BUFR language translator. The program was carried out by a student of the IS-B19 group, Pshenichny Andrey.");
}

void MainWindow::on_help_triggered()
{
    QMessageBox::about(this, "help", "To translate the file, click on the <Translate> button. If you already have a translated file and you want to find the data you are interested in, then click the <Search> button");
}

void MainWindow::on_quit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_Exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_MenuTranslate_triggered()
{
    TranslateWindow TransWindow;
    TransWindow.setModal(true);
    TransWindow.setWindowTitle("Decoder function");
    TransWindow.exec();
}

void MainWindow::on_MenuSearch_triggered()
{
    SearchWindow SearWindow;
    SearWindow.setModal(true);
    SearWindow.setWindowTitle("Search function");
    SearWindow.exec();
}

void MainWindow::on_Translate_clicked()
{
    TranslateWindow TransWindow;
    TransWindow.setModal(true);
    TransWindow.setWindowTitle("Decoder function");
    TransWindow.exec();
}

void MainWindow::on_Search_clicked()
{
    SearchWindow SearWindow;
    SearWindow.setModal(true);
    SearWindow.setWindowTitle("Search function");
    SearWindow.exec();
}
