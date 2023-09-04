#ifndef ELEVES_H
#define ELEVES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>
#include <QDateEdit>

class Eleves
{
private:
    int id;
    QString prenom,nom,classe;
public:
    Eleves();
    Eleves(int,QString,QString,QString);
    //Les fonctions CRUD
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * combo_box();
    //Recherche + trie
    QSqlQueryModel * trier(QString,QString);
    QSqlQueryModel * recherche(QString);
    QVector <QString> getinforamation(QString);

};

#endif // ELEVES_H
