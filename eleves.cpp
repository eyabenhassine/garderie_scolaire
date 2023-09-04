#include "eleves.h"

Eleves::Eleves()
{
nom="";
prenom="";
classe="";
}
Eleves::Eleves(int id,QString nom,QString prenom,QString classe)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->classe=classe;
}
bool Eleves::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("INSERT INTO eleves (id,nom, prenom, classe) "
                  "VALUES(:id ,:nom,:prenom ,:classe)");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":classe",classe);
    return query.exec();
}


QSqlQueryModel * Eleves::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select id from eleves");
    return model;
}

bool Eleves::modifier(){
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("UPDATE eleves SET nom=:nom , prenom=:prenom , classe=:classe WHERE (id =:id)");

    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":classe",classe);

    return query.exec();
}

QSqlQueryModel*Eleves::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from eleves");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("classe"));




    return model;
}
bool Eleves::supprimer(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("Delete from eleves where id = :id");
    query.bindValue(":id", res);
    return query.exec();
}


QSqlQueryModel * Eleves::recherche(QString val)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("Select * from eleves WHERE NOM||prenom||classe LIKE '%"+val+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("classe"));
     return model;
}

QSqlQueryModel *  Eleves::trier(QString critere ,QString mode)
{
   QSqlQueryModel * model= new QSqlQueryModel();

   model->setQuery("Select * from eleves order by "+critere+" "+mode+"");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("classe"));
 return model;
}

QVector<QString> Eleves::getinforamation(QString id) {
    QSqlQuery query;
    QString nom, prenom,classe;
    QVector<QString> information;
    query.prepare("SELECT * FROM eleves WHERE id=:id");
    query.bindValue(":cin", id);
    query.exec();

    if (query.next()) {
        nom = query.value(1).toString();
        prenom = query.value(2).toString();
        classe = query.value(3).toString();
    }

    information.push_back(nom);
    information.push_back(prenom);
    information.push_back(classe);
    qDebug() << information;

    return information;
}

