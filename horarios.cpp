#include "horarios.h"
#include "ui_horarios.h"
#include <QMessageBox>
#include <QPixmap>

Horarios::Horarios(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Horarios)
{
    ui->setupUi(this);
}

Horarios::~Horarios()
{
    delete ui;
}

void Horarios::on_commandLinkButton_clicked()
{
    QLabel lblImage;

    QString nome = "horarios.png";
    QPixmap horarios(nome);
    ui->horarioimagem->setPixmap(horarios);
}

void Horarios::on_help_clicked()
{
    QString msg = "Copie um arquivo de imagem para o diretório do programa com o nome de 'horarios.png' para alterar a imagem dos horários.";
    QMessageBox::information(this," ",msg);
}
