 #include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include<QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;
    w.setWindowTitle("Gestion de evenement");
    w.setFixedSize(1000,702);
    bool test=c.createconnect();//etablir la connexion
    if(test) //si la connexion est établie
    {w.show();
        w.display_listes();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
