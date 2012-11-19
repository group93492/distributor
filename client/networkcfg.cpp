#include "networkcfg.h"
#include "ui_networkcfg.h"

NetworkCfg::NetworkCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkCfg)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(0, 65535);
    ui->portEdit->setValidator(validator);
}

NetworkCfg::~NetworkCfg()
{
    delete ui;
}

void NetworkCfg::on_applyButton_clicked()
{
    QSettings settings("session", QSettings::IniFormat);
    settings.setValue("address", ui->IPEdit->text());
    settings.setValue("port", ui->portEdit->text());
    hide();
}

void NetworkCfg::on_cancelButton_clicked()
{
    QSettings settings("session", QSettings::IniFormat);
    ui->IPEdit->setText(settings.value("address", "localhost").toString());
    ui->portEdit->setText(settings.value("port", "33034").toString());
    hide();
}
