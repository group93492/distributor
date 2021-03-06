#ifndef NETWORKCFGDIALOG_H
#define NETWORKCFGDIALOG_H

#include <QWidget>
#include <QIntValidator>
#include <QSettings>
#include <QDesktopWidget>

namespace Ui {
class NetworkCfg;
}

class NetworkCfg : public QWidget
{
    Q_OBJECT
    
public:
    explicit NetworkCfg(QWidget *parent = 0);
    ~NetworkCfg();
    
private slots:
    void on_applyButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::NetworkCfg *ui;
};

#endif // NETWORKCFGDIALOG_H
