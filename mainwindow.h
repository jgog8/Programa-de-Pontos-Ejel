#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "info.h"
#include "cadastro_membros.h"
#include "horarios.h"
#include "su.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ok_clicked();

    void on_actionDetalhes_triggered();

    void on_actionQT_Creator_triggered();

    void on_box_usuario_textEdited(const QString &arg1);

    void on_box_senha_textEdited(const QString &arg1);

    void on_actionSuperUsuario_triggered();

    void on_actionCadastro_de_membros_triggered();

    void on_actionHorarios_triggered();

private:
    Ui::MainWindow *ui;
    Info *form2;
    Cadastro_Membros *form3;
    Horarios *form4;
    SU *form5;

};

#endif // MAINWINDOW_H
