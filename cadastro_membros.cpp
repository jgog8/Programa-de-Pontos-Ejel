#include "cadastro_membros.h"
#include "ui_cadastro_membros.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <string>
#include <iostream>

Cadastro_Membros::Cadastro_Membros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cadastro_Membros)
{
    ui->setupUi(this);
}

Cadastro_Membros::~Cadastro_Membros()
{
    delete ui;
}

void Cadastro_Membros::on_atualizar2_clicked()
{
    QString nome="Membros.jg";
    QFile arquivologin(nome);

    //Ler e escrever na  tela os dados dos cadastrados
    if(arquivologin.open(QFile::ReadOnly|QFile::Text))
    {
        QTextStream entrada(&arquivologin);
        QString cadastros = entrada.readAll();

        ui->RegistroDeCadastro->setPlainText(cadastros);

        arquivologin.flush();
        arquivologin.close();
    }
}
void Cadastro_Membros::on_salvar2_clicked()
{
    //Recebendo Texto do registro no programa
    QString registro = ui->RegistroDeCadastro->toPlainText();

    //Salvando no Arquivo de Membros
    QString nome="Membros.jg";

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

void Cadastro_Membros::on_limpar2_clicked()
{
    QString nome="Membros.jg";

    QMessageBox::StandardButton resposta=QMessageBox::question(this,"AVISO","Deseja apagar TODO o registro dos membros?");
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
        ui->RegistroDeCadastro->setPlainText(acessos);
        arquivologin.flush();
        arquivologin.close();
        }
}
