#include "OpenMapDialog.h"
#include "ui_OpenMapDialog.h"
#include <QDebug>
OpenMapDialog::OpenMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenMapDialog),
    returnName(plugs)
{
    this->returnName = returnName;
    ui->setupUi(this);
}

OpenMapDialog::OpenMapDialog(QWidget *parent, QVector<QString> maps, QString &returnName) :
    QDialog(parent),
    ui(new Ui::OpenMapDialog),
    returnName(returnName)
{
    ui->setupUi(this);

    for(int i=0;i<maps.size();i++) {
        ui->listWidget->addItem(maps[i]);
    }

    this->returnName = returnName;
}


OpenMapDialog::~OpenMapDialog()
{
    delete ui;
}

void OpenMapDialog::on_pushButton_clicked()
{
    returnName = ui->listWidget->currentIndex().data().toString();
    qDebug() << returnName;
    close();
}

void OpenMapDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
    returnName = ui->listWidget->currentIndex().data().toString();
    qDebug() << returnName;
    close();
}
