#include "Enseignant.h"

enseignant::enseignant()
{
nom="";
prenom="";
subject="";
}
enseignant::enseignant(int cin,QString nom,QString prenom,QString subject)
{
this->cin=cin;
this->nom=nom;
this->prenom=prenom;
this->subject=subject;
}
bool enseignant::ajouter(){
    QSqlQuery query;
    QString res= QString::number(cin);

    query.prepare("INSERT INTO enseignant (cin,nom, prenom, subject) "
                  "VALUES(:cin ,:nom,:prenom ,:subject)");

    query.bindValue(":cin", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":subject",subject);
    return query.exec();
}


QSqlQueryModel * enseignant::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select cin from enseignant");
    return model;
}

bool enseignant::modifier(){
    QSqlQuery query;
    QString res= QString::number(cin);

    query.prepare("UPDATE enseignant SET nom=:nom , prenom=:prenom , subject=:subject WHERE (cin =:cin)");

    query.bindValue(":cin", res);
    query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":subject",subject);

    return query.exec();
}

QSqlQueryModel*enseignant::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from enseignant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("subject"));




    return model;
}
bool enseignant::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("Delete from enseignant where cin=:cin");
    query.bindValue(":cin", res);
    return query.exec();
}


QSqlQueryModel * enseignant::recherche(QString val)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("Select * from enseignant WHERE NOM||prenom||subject LIKE '%"+val+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("subject"));
    return model;
}

QSqlQueryModel *  enseignant::trier(QString critere ,QString mode)
{
   QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("Select * from enseignant order by "+critere+" "+mode+"");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("subject"));
 return model;
}

QVector<QString> enseignant::getinforamation(QString id) {
    QSqlQuery query;
    QString nom, prenom,subject;
    QVector<QString> information;
    query.prepare("SELECT * FROM enseignant WHERE cin=:id");
    query.bindValue(":cin", id);
    query.exec();

    if (query.next()) {
        nom = query.value(1).toString();
        prenom = query.value(2).toString();
        subject = query.value(3).toString();
    }

    information.push_back(nom);
    information.push_back(prenom);
    information.push_back(subject);
    qDebug() << information;

    return information;
}

