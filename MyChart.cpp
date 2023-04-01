#include "MyChart.h"

MyChart::MyChart(QWidget* parent, QString _chartname) {
    
    chartname = _chartname;
    qchart = new QChart();
    series_Vector.clear();
    chartview = new QChartView(qchart);
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);
    chartview->setParent(this);
    chartview->setGeometry(0, 0, 1020, 290);
    setParent(parent);
    /*setStyleSheet("QWidget{background-color: rgba(255, 25, 20,255);}");
    chartview->setStyleSheet("QChartview{background-color: rgba(255, 255, 255, 0);}");*/
    
    resize(QSize(600, 600));

    chartview->setRenderHint(QPainter::Antialiasing);
}

void MyChart::setAxis(QString _xname, qreal _xmin, qreal _xmax, int _xtickc, \
    QString _yname, qreal _ymin, qreal _ymax, int _ytickc) {
    xname = _xname; xmin = _xmin; xmax = _xmax; xtickc = _xtickc;
    yname = _yname; ymin = _ymin; ymax = _ymax; ytickc = _ytickc;

    axisX->setRange(xmin, xmax);    
    axisX->setLabelFormat("%u");   
   
    axisX->setGridLineVisible(true);   
    axisX->setTickCount(xtickc);       //the number of the grid
    axisX->setMinorTickCount(1);   
    axisX->setTitleText(xname);  
    axisY->setRange(ymin, ymax);
    axisY->setLabelFormat("%u");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(ytickc);
    axisY->setMinorTickCount(1);
    axisY->setTitleText(yname);
    qchart->addAxis(axisX, Qt::AlignBottom);
    qchart->addAxis(axisY, Qt::AlignLeft);
}

void MyChart::buildChart(QVector<QList<QPointF>> pointlist)
{
    QSplineSeries* series = new QSplineSeries(this);;
    
    series->setPen(QPen(Qt::red, 3, Qt::SolidLine));
    series->clear();
    series_Vector.append(series);
    for (int j = 0; j < pointlist.size(); j++) {
        for (int i = 0; i < pointlist[0].size(); i++)
            series_Vector[j]->append(pointlist[j].at(i).x(), pointlist[j].at(i).y());
    }
    

    qchart->setTitle(chartname);

    qchart->setAnimationOptions(QChart::SeriesAnimations);
    qchart->legend()->hide(); 
    
    //setData
    qchart->addSeries(series);
    qchart->setAxisX(axisX, series);
    qchart->setAxisY(axisY, series);
}

