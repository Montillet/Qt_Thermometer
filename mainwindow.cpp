#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui_mainwindow.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_grid.h>
#include <QDebug>
#include <QTimer>
#include "rs232.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    j=0;
    ui->graph->setAxisTitle(QwtPlot::xBottom,QString("Temps en s"));
    ui->graph->setAxisTitle(QwtPlot::yLeft,QString("Temperature °C "));
    ui->graph->setTitle(QString("Thermometre"));
    ui->graph->setCanvasBackground( Qt::white );
    ui->graph2->setCanvasBackground( Qt::white );
    ui->graph2->setAxisTitle(QwtPlot::xBottom,QString("temps en s"));
    ui->graph2->setAxisTitle(QwtPlot::yLeft,QString("humiditer en %"));
    courbe2->setPen(Qt::blue,1);
    courbe2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    macourbe->setPen( Qt::green, 1 );
    macourbe->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    ui->graph->replot();
    ui->graph2->replot();
    zoom = new QwtPlotZoomer(ui->graph->canvas());
    zoom->setTrackerMode(QwtPicker::AlwaysOn);
    zoom->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton,Qt::ControlModifier);
    zoom->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);
    zoom2 = new QwtPlotZoomer(ui->graph2->canvas());
    zoom2->setTrackerMode(QwtPicker::AlwaysOn);
    zoom2->setMousePattern(QwtEventPattern::MouseSelect2,Qt::RightButton,Qt::ControlModifier);
    zoom2->setMousePattern(QwtEventPattern::MouseSelect3,Qt::RightButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reception(){

    hey=usart.recevoir();
    /*if(i==0){
        tmp=hey[2];
    }*/
    /*if(abs(tmp.toDouble()-hey.toDouble())>15.0){
        hey=tmp;
    }*/
    if(hey[0]=="0"&& hey.size()> 3){
        //qDebug()<< hey.size();
        y1.append(hey[2].toDouble());
        y2.append(hey[1].toDouble());
        i++;
        x1.append(i);
        courbe2->setSamples(x1.data(),y2.data(),x1.size());
        macourbe->setSamples(x1.data(),y1.data(),x1.size());
        macourbe->attach(ui->graph);
        courbe2->attach(ui->graph2);
        ui->graph2->replot();
        ui->graph->replot();
    }
}

void MainWindow::moteur_debug(){

    hey=usart.recevoir();
   // qDebug()<<"code :"<<i<<"humidite"<<hey[1]<<"temperature"<<hey[2];
}


void MainWindow::afficher(){

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(reception()));
    timer->start(1000);
}

void MainWindow::on_enregister_clicked()
{
    QFile file("temprature.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream flux(&file);
    flux.setCodec("UTF-8");

    for(int i=0;i<y1.size();i++){
        flux<<y1.at(i)<<" "<<y2.at(i)<<""<<"\n";
    }
    file.close();
}

void MainWindow::on_grille_toggled(bool checked)
{
    if (checked){
       grid->attach( ui->graph );
       grid->show();
       grid2->attach(ui->graph2);
       grid2->show();
       ui->graph->replot();
       ui->graph2->replot();
    }
    else{
        grid->hide();
        grid2->hide();
        ui->graph->replot();
        ui->graph2->replot();
    }
}

void MainWindow::zoomrect()
{
    QRectF rect=zoom->zoomRect();
    zoom->zoom(rect);
    ui->graph->setAxisScale(QwtPlot::xBottom,rect.left(),rect.right());
    ui->graph->setAxisScale(QwtPlot::yLeft,rect.bottom(),rect.top());
    ui->graph->replot();
}

void MainWindow::on_mode_auto_clicked()
{
    ui->mode_auto->setEnabled(false);
    afficher();
}

void MainWindow::on_arret_clicked()
{
    timer->stop();
    ui->mode_auto->setEnabled(true);
}

void MainWindow::on_exporter_clicked()
{
    QwtPlotRenderer renderer;
    //renderer.renderDocument(ui->graph,"teperature.pdf");
   // renderer.renderDocument(ui->graph2,"temperature.pdf");
    renderer.exportTo( ui->graph, "temperature.pdf" );


}

void MainWindow::on_moteur_clicked()
{
    j++;
    if (j==1){
        usart.envoi_chaine("a");
        qDebug()<<"Qt"<<j;
    }
    else if (j==2){
        usart.envoi_chaine("5");
        qDebug()<<"Qt"<<j;
    }
    else {
        usart.envoi_chaine("x");
        qDebug()<<"Qt"<<j;
    }


}


void MainWindow::on_serie_clicked()
{
    afficher();
}
