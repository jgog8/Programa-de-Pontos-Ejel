#ifndef SU_H
#define SU_H

#include <QDialog>

namespace Ui {
class SU;
}

class SU : public QDialog
{
    Q_OBJECT

public:
    explicit SU(QWidget *parent = nullptr);
    ~SU();

private slots:
    void on_alterarSU_clicked();

private:
    Ui::SU *ui;
};

#endif // SU_H
