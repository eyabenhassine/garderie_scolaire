#include "stat.h"
#include <QDebug>
#include <algorithm>
using namespace  std;
Stat::Stat()
{



}
QChartView * Stat::Preparechart()
{
    QSqlQuery query;
    QMap<QString, int> countMap;

    if (query.exec("SELECT subject, COUNT(*) FROM enseignant GROUP BY subject")) {
        while (query.next()) {
            QString date = query.value(0).toString();
            int count = query.value(1).toInt();
            countMap[date] = count;
        }
    }

    QPieSeries* series = new QPieSeries();
    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelOutside);

    for (auto it = countMap.begin(); it != countMap.end(); ++it) {
        QString label = QString("%1 (%2)").arg(it.key()).arg(it.value());
        QPieSlice* slice = series->append(label, it.value());
        slice->setLabelVisible();
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("le nombre de enseignant per sujet");
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QChart::ChartTheme theme = QChart::ChartThemeBlueIcy;
    chartView->chart()->setTheme(theme);

    return chartView;}






