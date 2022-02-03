#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "searchengine.h"
#include <QMessageBox>
#include <QFileDialog>

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::on_CloseButton_clicked()
{
    hide();
}

void SearchWindow::on_DoButton_clicked()
{
    QString Input = ui->InputLi->text();
    QString Output = ui->OutputLi->text();
    QString Value = ui->ValueLi->text();
    std::string IN = Input.toUtf8().constData();
    std::string OUT = Output.toUtf8().constData();
    std::string VAL = Value.toUtf8().constData();
    char input[50],output[50], value[50];
    strcpy(input,IN.c_str());
    strcpy(output,OUT.c_str());
    strcpy(value,VAL.c_str());
    if (ui->radioButton->isChecked())
    {
        SearchEngine a (input, output, value, 1);
        QMessageBox::information(this,"Attention", "Search started");
        a.build();
        QMessageBox::information(this,"Attention", "Search completed");
        hide();
    }
    if (ui->radioButton_2->isChecked())
    {
        SearchEngine a (input, output, value, 2);
        QMessageBox::information(this,"Attention", "Search started");
        a.build();
        QMessageBox::information(this,"Attention", "Search completed");
        hide();
    }
    if (ui->radioButton_3->isChecked())
    {
        SearchEngine a (input, output, value, 3);
        QMessageBox::information(this,"Attention", "Search started");
        a.build();
        QMessageBox::information(this,"Attention", "Search completed");
        hide();
    }
    if (ui->radioButton_4->isChecked())
    {
        SearchEngine a (input, output, value, 4);
        QMessageBox::information(this,"Attention", "Search started");
        a.build();
        QMessageBox::information(this,"Attention", "Search completed");
        hide();
    }
}

void SearchWindow::on_InputBut_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    ui->InputLi->setText(str);
}

void SearchWindow::on_OutputBut_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    ui->OutputLi->setText(str);
}

void SearchWindow::on_ValueBut_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    ui->ValueLi->setText(str);
}
