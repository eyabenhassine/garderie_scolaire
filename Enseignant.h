#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QDebug>
#include <QDateEdit>


class enseignant
{
private:
    int cin;
    QString prenom,nom,subject;
public:
    enseignant();
    enseignant(int,QString,QString,QString);
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

#endif // ENSEIGNANT_H
