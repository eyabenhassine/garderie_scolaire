#ifndef STATELEVES_H
#define STATELEVES_H
#include <QtCharts>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QSqlQuery>
#include <QString>

class StatEleves
{
    QChart *chart;
    QChartView *chartView;
public:
    StatEleves();
    QChartView * Preparechart();
};

#endif // STATELEVES_H
