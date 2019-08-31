#ifndef INFO_H
#define INFO_H

#include <QDialog>

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

private slots:
    void on_atualizar_clicked();

    void on_salvar_clicked();

    void on_limpar_clicked();

private:
    Ui::Info *ui;
};

#endif // INFO_H
