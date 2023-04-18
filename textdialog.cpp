// textdialog.cpp

#include "textdialog.h"
#include "ui_textdialog.h"
#include <mainwindow.h>
TextDialog::TextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDialog)
{
    ui->setupUi(this);
}

TextDialog::~TextDialog()
{
    delete ui;
}

QString TextDialog::getText() const
{
    return m_text;
}

void TextDialog::on_buttonBox_accepted()
{
    // Accept the text entered by the user and close the dialog
    m_text = ui->textEdit->toPlainText();
    accept();
}

void TextDialog::on_buttonBox_rejected()
{
    // Cancel the user's input and close the dialog
    reject();
}
