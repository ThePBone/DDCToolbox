#ifndef GRAPH_H
#define GRAPH_H
#include <QObject>
#include <cmath>
#include "qcustomplot.h"

class Graph
{
public:
    static void drawMagnitudeResponse(QCustomPlot* graph,std::vector<float> table,int bandCount=8192){
        if (table.size()<=0)
            return;

        float max = 24.0f;
        float min = -24.0f;

        for (size_t i = 0; i < (size_t)bandCount; i++){
            if (table.at(i) > max)
                max = table.at(i);
            if (table.at(i) < min)
                min = table.at(i);
        }

        graph->yAxis->setRange(QCPRange(min, max));
        QCPGraph *plot = graph->addGraph();
        plot->setAdaptiveSampling(false);

        for (size_t m = 0; m < (size_t)bandCount; m++)
        {
            double num3 = (44100.0 / 2.0) / ((double) bandCount);
            plot->addData(num3 * (m + 1.0),(double)table.at(m));
            graph->xAxis->setRange(QCPRange(20, num3 * (m + 1.0)));
        }
        graph->replot();
    }
    static void drawGroupDelayGraph(QCustomPlot* graph,std::vector<float> table,int bandCount=8192){
        if (table.size()<=0)
            return;

        float max_gd = 12.0f;
        float min_gd = -12.0f;

        for (size_t i = 0; i < (size_t)table.size(); i++){
            if (table.at(i) > max_gd)
                max_gd = table.at(i);
            if (table.at(i) < min_gd)
                min_gd = table.at(i);
        }
        if(std::isinf(min_gd))min_gd=-12.0;
        if(std::isinf(max_gd))max_gd=12.0;

        graph->yAxis->setRange(QCPRange(min_gd, max_gd));
        QCPGraph *plot_gd = graph->addGraph();
        plot_gd->setAdaptiveSampling(false);

        for (size_t m = 0; m < (size_t)bandCount; m++)
        {
            double num3 = (44100.0 / 2.0) / ((double) bandCount);
            plot_gd->addData(num3 * (m + 1.0),(double)table.at(m));
            graph->xAxis->setRange(QCPRange(20, num3 * (m + 1.0)));
        }
        graph->replot();
    }
};

#endif // GRAPH_H
