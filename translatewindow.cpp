#include "translatewindow.h"
#include "ui_translatewindow.h"
#include "decoder.h"
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>

TranslateWindow::TranslateWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranslateWindow)
{
    ui->setupUi(this);
}

TranslateWindow::~TranslateWindow()
{
    delete ui;
}

void TranslateWindow::on_CloseButton_clicked()
{
    hide();
}

void TranslateWindow::on_DoButton_clicked()
{
    QString Input = ui->InputLine->text();
    QString Output = ui->OutputLine->text();
    std::string IN = Input.toUtf8().constData();
    std::string OUT = Output.toUtf8().constData();
    char input[50],output[50];
    strcpy(input,IN.c_str());
    strcpy(output,OUT.c_str());
    decoder a (input,output);
    QMessageBox::information(this,"Attention", "Translation started");
    a.FinalPoint();
    QMessageBox::information(this,"Attention", "Translation completed");
    hide();
}

void TranslateWindow::on_InputButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    ui->InputLine->setText(str);
}

void TranslateWindow::on_OutputButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
    ui->OutputLine->setText(str);
}
