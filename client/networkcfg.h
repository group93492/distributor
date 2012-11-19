#ifndef NETWORKCFG_H
#define NETWORKCFG_H

#include <QWidget>
#include <QIntValidator>
#include <QSettings>

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

#endif // NETWORKCFG_H
