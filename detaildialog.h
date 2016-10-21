#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>

namespace Ui {
class DetailDialog;
}

class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(QWidget *parent = 0);
    ~DetailDialog();

    void setDefault(QString , QString);

private slots:
    void on_selectBtn_clicked();

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

signals:
    void saveClicked(QString, QString);

private:
    Ui::DetailDialog *ui;
    QString dir;
    QString username;
    QString p_username;
    QString p_dir;
};

#endif // DETAILDIALOG_H