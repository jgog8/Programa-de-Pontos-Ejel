#ifndef CADASTRO_MEMBROS_H
#define CADASTRO_MEMBROS_H

#include <QDialog>

namespace Ui {
class Cadastro_Membros;
}

class Cadastro_Membros : public QDialog
{
    Q_OBJECT

public:
    explicit Cadastro_Membros(QWidget *parent = nullptr);
    ~Cadastro_Membros();

private slots:
    void on_atualizar2_clicked();

    void on_salvar2_clicked();

    void on_limpar2_clicked();

private:
    Ui::Cadastro_Membros *ui;
};

#endif // CADASTRO_MEMBROS_H
