#include "su.h"
#include "ui_su.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <string>
#include <iostream>

SU::SU(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SU)
{
    ui->setupUi(this);
}

SU::~SU()
{
    delete ui;
}

void SU::on_alterarSU_clicked()
{
    QString NSusuario=ui->box_Susuario->text();
    QString NSsenha=ui->box_Ssenha->text();

    QString nome="SU.jg";
    QString msg ="Caso e esqueça qual modificação feita no SuperUsuário, não será possível acessar esse painel para reverte-la. Deseja continuar?";
    QMessageBox::StandardButton resposta=QMessageBox::question(this,"AVISO",msg);
    if(resposta==QMessageBox::Yes)
    {
        msg = "Deseja alterar o SuperUsuário?";
        QMessageBox::StandardButton resposta=QMessageBox::question(this,"AVISO",msg);
        if(resposta==QMessageBox::Yes)

        {
            //apagando todos os dados
            QFile arquivoSU(nome);
            arquivoSU.open(QFile::ReadWrite|QFile::Truncate);

            //atualizando dados
            QTextStream entrada(&arquivoSU);
            QString acessos = entrada.readAll();
            entrada << NSusuario+"\n"+NSsenha;
            arquivoSU.flush();
            arquivoSU.close();
        }
    }
}
