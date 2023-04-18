// textdialog.h

#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>

namespace Ui {
class TextDialog;
}

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDialog(QWidget *parent = nullptr);
    ~TextDialog();
    QString getText() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::TextDialog *ui;
    QString m_text;
};

#endif // TEXTDIALOG_H
