#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QWidget>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();
    
private:
    Ui::AuthDialog *ui;
};

#endif // AUTHDIALOG_H
