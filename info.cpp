#include "info.h"
#include "ui_info.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <string>
#include <iostream>

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}

void Info::on_atualizar_clicked()
{
    QString nome="Logins.jg";
    QFile arquivologin(nome);

    //Ler e escrever n  tela os Acessos
    if(arquivologin.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream entrada(&arquivologin);
        QString acessos = entrada.readAll();

        ui->RegistroDePonto->setPlainText(acessos);

        arquivologin.flush();
        arquivologin.close();
    }
}
void Info::on_salvar_clicked()
{
    //Recebendo Texto do registro no programa
    QString registro = ui->RegistroDePonto->toPlainText();

    //Salvando no Arquivo de Logins
    QString nome="Logins.jg";

        QMessageBox::StandardButton resposta=QMessageBox::question(this,"AVISO","Deseja salvar as alterações?");
        if(resposta==QMessageBox::Yes)
        {
            QFile arquivologin(nome);
            arquivologin.open(QFile::ReadWrite|QFile::Truncate);
            QTextStream entrada(&arquivologin);
            QString acessos = entrada.readAll();
            entrada << registro;

            arquivologin.flush();
            arquivologin.close();
        }
}

void Info::on_limpar_clicked()
{
    QString nome="Logins.jg";

    QMessageBox::StandardButton resposta=QMessageBox::question(this,"AVISO","Deseja apagar todo o registro de acessos?");
    if(resposta==QMessageBox::Yes)
    {
        //apagando todos os dados
        QFile arquivologin(nome);
        arquivologin.open(QFile::ReadWrite|QFile::Truncate);
        arquivologin.flush();
        arquivologin.close();
        //atualizando tela
        QTextStream entrada(&arquivologin);
        QString acessos = entrada.readAll();
        ui->RegistroDePonto->setPlainText(acessos);
        arquivologin.flush();
        arquivologin.close();
        }
}
