#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QSqlError>
#include <QMessageBox>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

#include<QString>

#include <QIcon>
#include <QIntValidator>
#include "QSqlQuery"
#include "QStringListModel"
#include<QFileDialog>
#include<QTextDocument>
#include<QTextStream>
#include<QGraphicsView>
#include<QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QSystemTrayIcon>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QDate>
#include <QTime>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QtPrintSupport/QPrinter>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QCoreApplication>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_5->setIcon((QIcon(":/images/refresh1.png")));
    ui->pushButton_5->setIconSize(ui->pushButton_5->size());
    ui->pushButton_5->setCheckable(true);
    ui->pushButton_8->setIcon((QIcon(":/images/refresh1.png")));
    ui->pushButton_8->setIconSize(ui->pushButton_8->size());
    ui->pushButton_8->setCheckable(true);
ui->lineEdit_7->setVisible(false);

display_listes();


}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::notification(QString msg)
{
    qDebug() << "Notification message: " << msg;

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon(this);
    if (notifyIcon->isSystemTrayAvailable()) {
        qDebug() << "System tray is available";
        notifyIcon->setIcon(QIcon(":/icon.png")); // Replace with the path to your icon
        notifyIcon->show();
        notifyIcon->showMessage("News", msg, QSystemTrayIcon::Information, 15000);
    } else {
        qDebug() << "System tray is not available";
    }
}

void MainWindow::display_listes()
{
    ui->lineEditadres->clear();
    ui->lineEditadres_2->clear();
    ui->tabevent->setModel(ev.afficher());
    ui->id_chmo->setModel(ev.combo_box());
    ui->ad_chmo->clear();
    ui->sup_id->clear();
    mainLayout=new QVBoxLayout ;
    mainLayout->addWidget(s.Preparechart());
    ui->widget->setLayout(mainLayout);
    ui->tabevent_4->setModel(ele.afficher());
    ui->id_chmo_4->setModel(ele.combo_box());
refresh_stat();
refresh_statv();
mainLayout2=new QVBoxLayout ;
mainLayout2->addWidget(se.Preparechart());
ui->widget_4->setLayout(mainLayout2);
refresh_statv();


}
void MainWindow::refresh_statv()
{
    if ( ui->widget_4->layout() != NULL )
    {
    QLayoutItem* item;
    while ( ( item = ui->widget_4->layout()->takeAt( 0 ) ) != NULL )
    {
    delete item->widget();
    delete item;
    }
    delete ui->widget_4->layout();
    }
    mainLayout2 = new QVBoxLayout;
    mainLayout2->addWidget(se.Preparechart());
    ui->widget_4->setLayout(mainLayout2);
}

void MainWindow::on_pushButton_clicked()
{
    int cin=ui->lineEditadres->text().toInt();
    QString nom=ui->lineEditadres_2->text();
    QString prenom=ui->lineEditadres_4->text();
    QString subject= ui->lineEditadres_3->text();
    enseignant c(cin,nom,prenom,subject);


    if ((nom!='\0')&&(prenom!='\0')&&(subject!='\0'))
    {

        bool test = c.ajouter();

    if(test)

    {

        notification("enseignant ajouté !");
        display_listes();


        QMessageBox::information(nullptr,("Ajout enseignant"),("enseignant ajouté"));}
else
     {QMessageBox::warning(nullptr,("Ajout enseignant"),("enseignant non ajouté"));}
    }

    else QMessageBox::warning(nullptr,("Ajout enseignant"),("pas de données"));


}


void MainWindow::on_modifierchantier_clicked()
{
    int cin=ui->id_chmo->currentText().toInt();
    QString nom=ui->ad_chmo_2->text();

    QString prenom=ui->ad_chmo->text();
    QString subject= ui->ad_chmo_3->text();
    enseignant c(cin,nom,prenom,subject);
    bool test=c.modifier();

    if ((subject!='\0'))
    {

    if(test)

    {
        display_listes();


        notification("enseignant modifier !");
        QMessageBox::information(nullptr,("modifier enseignant"),("enseignant modifier"));}
else
     {QMessageBox::warning(nullptr,("modifier enseignant"),("enseignant non modifier"));}
    }

    else QMessageBox::warning(nullptr,("modifier enseignant"),("pas de données"));

}


void MainWindow::on_id_chmo_activated(const QString &)
{
    QString a=ui->id_chmo->currentText();
      QSqlQuery query;
      query.prepare("select * from enseignant where cin =:cin");
      query.bindValue(":cin", a);

      if (query.exec())
      {

          while (query.next()) {

               ui->id_chmo->setCurrentText(query.value(0).toString());
               ui->ad_chmo_2->setText(query.value(1).toString());
                ui->ad_chmo->setText(query.value(2).toString());
                ui->ad_chmo_3->setText(query.value(3).toString());


          }
      }
}


void MainWindow::on_supprimerchantier_clicked()
{
    int a=ui->sup_id->text().toInt();
    bool test=ev.supprimer(a);

    if (a!='\0'){
    QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {

        if(test)
        {
            display_listes();
            QMessageBox::information(nullptr, QObject::tr("Supprimer un enseignant"),
                        QObject::tr("enseignant supprimé.\n"
                                    "Click Ok to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un enseignant"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else  return;}


}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1!="Select"){
        if (ui->radioButton_7->isChecked())
        {
            ui->tabevent->setModel(ev.trier(arg1,"ASC"));

        }
        else if (ui->radioButton_8->isChecked())
        {
            ui->tabevent->setModel(ev.trier(arg1,"DESC"));

        }else{
             ui->tabevent->setModel(ev.trier(arg1,"DESC"));
        }
    }else{
        ui->tabevent->setModel(ev.afficher());
    }

}


void MainWindow::on_pb_ok1_clicked()
{
    QString type= ui->lineEdit_18->text() ;
    ui->tabevent->setModel(ev.recherche(type));
}


void MainWindow::on_tabevent_activated(const QModelIndex &index)
{
    QString a=ui->tabevent->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from enseignant where cin=:id");
    query.bindValue(":id", a);

    if (query.exec())
    {
        while (query.next()) {
            ui->sup_id->setText(query.value(0).toString());
                     ui->lineEdit_7->setText(query.value(0).toString());
        }
    }
}


void MainWindow::on_pushButton_5_toggled(bool checked)
{
    if (checked){
        ui->pushButton_5->setIcon((QIcon(":/images/refresh2.png")));
        ui->pushButton_5->setIconSize(ui->pushButton_5->size());
        display_listes();


    }
   else  {
        ui->pushButton_5->setIcon((QIcon(":/images/refresh1.png")));
        ui->pushButton_5->setIconSize(ui->pushButton_5->size());
        display_listes();
    }
}



void MainWindow::refresh_stat()
{
    if ( ui->widget->layout() != NULL )
    {
    QLayoutItem* item;
    while ( ( item = ui->widget->layout()->takeAt( 0 ) ) != NULL )
    {
    delete item->widget();
    delete item;
    }
    delete ui->widget->layout();
    }
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(s.Preparechart());
    ui->widget->setLayout(mainLayout);
}

void MainWindow::on_pushButton_4_clicked()
{
    int id=ui->lineEditadres_13->text().toInt();
    QString nom=ui->lineEditadres_14->text();
    QString prenom=ui->lineEditadres_16->text();
    QString classe= ui->lineEditadres_15->text();
    Eleves c(id,nom,prenom,classe);


    if ((nom!='\0')&&(prenom!='\0')&&(classe!='\0'))
    {

    bool test = c.ajouter();
    notification("eleves ajouté !");

    if(test)

    {
        display_listes();


        QMessageBox::information(nullptr,("Ajout eleves"),("eleves ajouté"));}
else
     {QMessageBox::warning(nullptr,("Ajout eleves"),("eleves non ajouté"));}
    }

    else QMessageBox::warning(nullptr,("Ajout eleves"),("pas de données"));


}


void MainWindow::on_modifierchantier_4_clicked()
{
    int id=ui->id_chmo_4->currentText().toInt();
    QString nom=ui->ad_chmo_11->text();
    QString prenom=ui->ad_chmo_10->text();
    QString classe= ui->ad_chmo_12->text();
    Eleves c(id,nom,prenom,classe);
    bool test=c.modifier();

    if ((classe!='\0'))
    {

    if(test)

    {
        display_listes();


        notification("eleves modifier !");
        QMessageBox::information(nullptr,("modifier eleves"),("eleves modifier"));}
else
     {QMessageBox::warning(nullptr,("modifier eleves"),("eleves non modifier"));}
    }

    else QMessageBox::warning(nullptr,("modifier eleves"),("pas de données"));

}


void MainWindow::on_supprimerchantier_4_clicked()
{
    int a=ui->sup_id_4->text().toInt();
    bool test=ele.supprimer(a);

    if (a!='\0'){
    QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {

        if(test)
        {
            display_listes();
            QMessageBox::information(nullptr, QObject::tr("Supprimer un eleve"),
                        QObject::tr("eleve supprimé.\n"
                                    "Click Ok to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Supprimer un eleve"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else  return;}


}


void MainWindow::on_id_chmo_4_activated(const QString &)
{
    QString a=ui->id_chmo_4->currentText();
      QSqlQuery query;
      query.prepare("select * from eleves where id =:id");
      query.bindValue(":id", a);

      if (query.exec())
      {

          while (query.next()) {

               ui->id_chmo_4->setCurrentText(query.value(0).toString());
               ui->ad_chmo_11->setText(query.value(1).toString());


                ui->ad_chmo_10->setText(query.value(2).toString());
                ui->ad_chmo_12->setText(query.value(3).toString());


          }
      }
}


void MainWindow::on_tabevent_4_activated(const QModelIndex &index)
{
    QString a=ui->tabevent_4->model()->data(index).toString();
    QSqlQuery query;
    query.prepare("select * from eleves where id=:id");
    query.bindValue(":id", a);

    if (query.exec())
    {
        while (query.next()) {
            ui->sup_id_4->setText(query.value(0).toString());
        }
    }
}


void MainWindow::on_pb_ok1_4_clicked()
{
    QString type= ui->lineEdit_21->text() ;
    ui->tabevent_4->setModel(ele.recherche(type));
}


void MainWindow::on_comboBox_4_activated(const QString &arg1)
{
    if(arg1!="Select"){
        if (ui->radioButton_13->isChecked())
        {
            ui->tabevent_4->setModel(ele.trier(arg1,"ASC"));
        }
        else if (ui->radioButton_14->isChecked())
        {
            ui->tabevent_4->setModel(ele.trier(arg1,"DESC"));
        }else{
             ui->tabevent_4->setModel(ele.trier(arg1,"DESC"));
        }
    }else{
        ui->tabevent_4->setModel(ele.afficher());
    }
}


void MainWindow::on_pushButton_8_toggled(bool checked)
{
    if (checked){
        ui->pushButton_8->setIcon((QIcon(":/images/refresh2.png")));
        ui->pushButton_8->setIconSize(ui->pushButton_8->size());
        display_listes();


    }
   else  {
        ui->pushButton_8->setIcon((QIcon(":/images/refresh1.png")));
        ui->pushButton_8->setIconSize(ui->pushButton_8->size());
        display_listes();
    }
}

