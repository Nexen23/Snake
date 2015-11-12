#ifndef OPENMAPDIALOG_H
#define OPENMAPDIALOG_H

#include <QDialog>

namespace Ui {
class OpenMapDialog;
}

class OpenMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenMapDialog(QWidget *parent = 0);
    explicit OpenMapDialog(QWidget *parent, QVector<QString> maps, QString &returnName);
    ~OpenMapDialog();

private slots:
    void on_pushButton_clicked();
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::OpenMapDialog *ui;
    QString &returnName;
    QString plugs;
};

#endif // OPENMAPDIALOG_H
