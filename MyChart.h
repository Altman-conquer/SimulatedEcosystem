#ifndef CHART_H
#define CHART_H

#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <QMainWindow>


class MyChart : public QMainWindow
{
    Q_OBJECT
    QChart* qchart;
    QChartView* chartview;
    QVector<QSplineSeries*> series_Vector;

    QHBoxLayout* layout;
    QValueAxis* axisX;
    QValueAxis* axisY;

    QString chartname;
    //坐标轴参数
    QString xname;
    qreal xmin;
    qreal xmax;
    int xtickc;
    QString yname;
    qreal ymin;
    qreal ymax;
    int ytickc;

public:
    MyChart(QWidget* parent = NULL, QString _chartname = "曲线图");
    ~MyChart() {}
    void setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, \
        QString _yname, qreal _ymin, qreal _ymax, int _ytickc);
    void buildChart(QVector<QList<QPointF>> pointlist);

};
#endif // CHART_H

