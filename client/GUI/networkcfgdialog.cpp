#include "networkcfgdialog.h"
#include "ui_networkcfgdialog.h"

NetworkCfg::NetworkCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetworkCfg)
{
    ui->setupUi(this);
    move(QApplication::desktop()->geometry().width() / 2 - this->geometry().width() / 2,
             QApplication::desktop()->geometry().height() / 2 - this->geometry().height() / 2);
    QIntValidator *validator = new QIntValidator(0, 65535);
    ui->mainPortEdit->setValidator(validator);
    ui->filesPortEdit->setValidator(validator);
    on_cancelButton_clicked();
}

NetworkCfg::~NetworkCfg()
{
    delete ui;
}

void NetworkCfg::on_applyButton_clicked()
{
    QSettings settings("session", QSettings::IniFormat);
    settings.setValue("address", ui->IPEdit->text());
    settings.setValue("main_port", ui->mainPortEdit->text());
    settings.setValue("files_port", ui->filesPortEdit->text());
    hide();
}

void NetworkCfg::on_cancelButton_clicked()
{
    QSettings settings("session", QSettings::IniFormat);
    ui->IPEdit->setText(settings.value("address", "localhost").toString());
    ui->mainPortEdit->setText(settings.value("main_port", "33034").toString());
    ui->filesPortEdit->setText(settings.value("files_port", "33035").toString());
    hide();
}
