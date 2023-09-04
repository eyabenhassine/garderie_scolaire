#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include "Enseignant.h"
#include "eleves.h"
#include <QVBoxLayout>
#include "stat.h"
#include "stateleves.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display_listes();

    void refresh_stat();
    void refresh_statv();

    void notification(QString);

private slots:
    void on_pushButton_clicked();

    void on_modifierchantier_clicked();

    void on_id_chmo_activated(const QString &);

    void on_supprimerchantier_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pb_ok1_clicked();

    void on_tabevent_activated(const QModelIndex &index);

    void on_pushButton_5_toggled(bool checked);

    void on_pushButton_11_clicked();

    void on_pushButton_4_clicked();

    void on_modifierchantier_4_clicked();

    void on_supprimerchantier_4_clicked();

    void on_id_chmo_4_activated(const QString &);

    void on_tabevent_4_activated(const QModelIndex &index);

    void on_pb_ok1_4_clicked();

    void on_comboBox_4_activated(const QString &arg1);

    void on_pushButton_8_toggled(bool checked);

private:
    Ui::MainWindow *ui;
      enseignant ev;
      Eleves ele;

      QVBoxLayout* mainLayout;
      Stat s;

      QVBoxLayout* mainLayout2;
      StatEleves se;
};

#endif // MAINWINDOW_H
