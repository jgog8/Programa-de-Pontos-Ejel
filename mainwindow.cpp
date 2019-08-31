#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <string>
#include <iostream>
#include <QThread>
#include <QTime>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ok_clicked()
{
    //Recebendo nome e senha dos usuários
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Recebendo Hora e Data
    //QString horario = QTime::currentTime().toString();

    QString dia = QDate::currentDate().toString("dd/MM/yyyy");
    QString semana = QDate::currentDate().toString("ddd");
    QString horario = QTime::currentTime().toString("hh:mm");

    //Recebendo Entrada ou saída da pessoa
    QVector<bool>vponto;
    vponto.push_back(ui->rb_entrada->isChecked());
    vponto.push_back(ui->rb_saida->isChecked());
    QString ponto="";
    if(vponto[0]){ponto="entrada";}
    else if(vponto[1]){ponto="saida";}

    //Solicitação da senha e nome caso não sejam preenchidos
    if (usuario == "")
    {
        QMessageBox::StandardButton resposta=QMessageBox::warning(this,"AVISO","Insira o nome de Usuario!");
        if(resposta==QMessageBox::Ok)
        {
            ui->box_usuario->setFocus();
        }
    }else if(senha == "")
    {
        QMessageBox::StandardButton resposta=QMessageBox::warning(this,"AVISO","Insira a sua Senha!");
        if(resposta==QMessageBox::Ok)
        {
            ui->box_senha->setFocus();
        }
    }else if(ponto=="")
    {
        QMessageBox::warning(this,"AVISO","Informe se está chegando ou saindo!");
    }else
    {
        //Buscando Registro de Membros
        QString nome="Membros.jg";
        QFile arquivomembros(nome);
        if(arquivomembros.open(QIODevice::ReadOnly))
        {
            bool verificarponto=false;
            QTextStream entrada(&arquivomembros);
            while(!entrada.atEnd())
            {
                //Verificação dos dados inseridos
                QString linha = entrada.readLine();
                if(linha=="")
                {
                    QString linha = entrada.readLine();
                    if(usuario==linha)
                    {
                        QString linha = entrada.readLine();
                        if(senha==linha)
                        {
                            //Salvando logins
                            QString linha = entrada.readLine();
                            //Registro de entrada
                            if(ponto=="entrada")
                            {
                                verificarponto=true;
                                QString nome="Logins.jg";
                                QFile arquivologin(nome);

                                //salvar entrada do membro
                                if(arquivologin.open(QFile::ReadWrite|QFile::Text))
                                {
                                    QTextStream entrada(&arquivologin);
                                    QString acessos = entrada.readAll();
                                    entrada << "\n"+dia+"\t"+semana+"\t"+horario+"\t"+ponto+"\t\t"+usuario;

                                    QMessageBox::StandardButton resposta=QMessageBox::information(this,"AVISO",linha);
                                    if(resposta==QMessageBox::Ok)
                                    {
                                        arquivomembros.close();
                                        QApplication::quit();
                                    }
                                    arquivologin.flush();
                                    arquivologin.close();
                                }

                            //Registro de saida
                            }else if(ponto=="saida")
                            {
                                QString linha = entrada.readLine();
                                verificarponto=true;
                                QString nome="Logins.jg";
                                QFile arquivologin(nome);

                                //salvar saida do membro
                                if(arquivologin.open(QFile::ReadWrite|QFile::Text))
                                {
                                    QTextStream entrada(&arquivologin);
                                    QString acessos = entrada.readAll();

                                    entrada << "\n"+dia+"\t"+semana+"\t"+horario+"\t"+ponto+"\t\t"+usuario;

                                    QMessageBox::StandardButton resposta=QMessageBox::information(this,"AVISO",linha);
                                    if(resposta==QMessageBox::Ok)
                                    {
                                        arquivomembros.close();
                                        QApplication::quit();
                                    }
                                    arquivologin.flush();
                                    arquivologin.close();
                                }
                            }
                        }
                    }
                }
            }
            if(verificarponto==false)
            {
                //Mensagem de Login Inválido
                QMessageBox::StandardButton resposta=QMessageBox::warning(this,"AVISO","Senha e/ou Usuario incorreto(s)!");
                if(resposta==QMessageBox::Ok)
                {
                    ui->ok->setFocus();
                }
            }
            arquivomembros.close();
        }

    }
}


void MainWindow::on_actionDetalhes_triggered()
{
    //Verificando se é Super Usuario
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Buscando Registro de Membros
    QString nome="SU.jg";
    QFile arquivoSU(nome);
    if(arquivoSU.open(QIODevice::ReadOnly))
    {
        QTextStream entrada(&arquivoSU);
        while(!entrada.atEnd())
        {
            //Verificação dos dados inseridos
            QString linhaU = entrada.readLine();
            QString linhaS= entrada.readLine();
            if(linhaU==usuario and linhaS==senha)
            {
                    form2 = new Info(this);
                    form2->show();
            }else
            {
                QString msg = "Entre como SuperUsuario para ver mais detalhes!";
                QMessageBox::information(this," ",msg);
            }
        }
    }
}

void MainWindow::on_actionQT_Creator_triggered()
{
     QMessageBox::aboutQt(this,"QT Creator");
}



void MainWindow::on_box_usuario_textEdited(const QString &arg1)
{
    //Verificando se é Super Usuario
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Buscando Registro de Membros
    QString nome="SU.jg";
    QFile arquivoSU(nome);
    if(arquivoSU.open(QIODevice::ReadOnly))
    {
        QTextStream entrada(&arquivoSU);
        while(!entrada.atEnd())
        {
            //Verificação dos dados inseridos
            QString linha = entrada.readLine();
            if(linha==usuario)
            {
                QString linha = entrada.readLine();
                if(linha==senha)
                {
                    QString msg = "SuperUsuario Ativo";
                    ui->statusBar->showMessage(msg);
                }else {
                    ui->statusBar->showMessage("");
                }
            }
        }
    }
}

void MainWindow::on_box_senha_textEdited(const QString &arg1)
{
    //Verificando se é Super Usuario
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Buscando Registro de Membros
    QString nome="SU.jg";
    QFile arquivoSU(nome);
    if(arquivoSU.open(QIODevice::ReadOnly))
    {
        QTextStream entrada(&arquivoSU);
        while(!entrada.atEnd())
        {
            //Verificação dos dados inseridos
            QString linha = entrada.readLine();
            if(linha==usuario)
            {
                QString linha = entrada.readLine();
                if(linha==senha)
                {
                    QString msg = "SuperUsuario Ativo";
                    ui->statusBar->showMessage(msg);
                }else {
                    ui->statusBar->showMessage("");
                }
            }
        }
    }
}

void MainWindow::on_actionSuperUsuario_triggered()
{

    //Verificando se é Super Usuario
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Buscando Registro de Membros
    QString nome="SU.jg";
    QFile arquivoSU(nome);
    if(arquivoSU.open(QIODevice::ReadOnly))
    {
        QTextStream entrada(&arquivoSU);
        while(!entrada.atEnd())
        {
            //Verificação dos dados inseridos
            QString linhaU = entrada.readLine();
            QString linhaS= entrada.readLine();
            if(linhaU==usuario and linhaS==senha)
            {
                //abrindo Cadastro de Super Usuários
                form5 = new SU(this);
                form5->show();
            }else
            {
                QString msg = "Entre como SuperUsuario para ver mais detalhes!";
                QMessageBox::information(this," ",msg);
            }
        }
    }
}


void MainWindow::on_actionCadastro_de_membros_triggered()
{
    //Verificando se é Super Usuario
    QString usuario = ui->box_usuario->text();
    QString senha = ui->box_senha->text();

    //Buscando Registro de SU
    QString nome="SU.jg";
    QFile arquivoSU(nome);
    if(arquivoSU.open(QIODevice::ReadOnly))
    {
        QTextStream entrada(&arquivoSU);
        while(!entrada.atEnd())
        {
            //Verificação dos dados inseridos
            QString linhaU = entrada.readLine();
            QString linhaS= entrada.readLine();
            if(linhaU==usuario and linhaS==senha)
            {
                    //abrindo Cadastro de membros
                    form3 = new Cadastro_Membros(this);
                    form3->show();
            }else
            {
                QString msg = "Entre como SuperUsuario para ver mais detalhes!";
                QMessageBox::information(this," ",msg);
            }
        }
    }
}

void MainWindow::on_actionHorarios_triggered()
{
    form4 = new Horarios(this);
    form4->show();
}
