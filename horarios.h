#ifndef HORARIOS_H
#define HORARIOS_H

#include <QDialog>

namespace Ui {
class Horarios;
}

class Horarios : public QDialog
{
    Q_OBJECT

public:
    explicit Horarios(QWidget *parent = nullptr);
    ~Horarios();

private slots:
    void on_commandLinkButton_clicked();

    void on_help_clicked();

private:
    Ui::Horarios *ui;
};

#endif // HORARIOS_H
