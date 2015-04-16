#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_zoomer.h>
#include <QVector>
#include <qwt_plot_grid.h>
#include "rs232.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    RS232 usart;
    void afficher();
    QwtPlotCurve *macourbe =new QwtPlotCurve;
    QwtPlotCurve *courbe2 =new QwtPlotCurve;
    QwtPlotGrid *grid = new QwtPlotGrid();
    QwtPlotGrid *grid2 = new QwtPlotGrid();
    QwtPlotZoomer * zoom2;
    QTimer * timer;
    QwtPlotZoomer * zoom;
    QVector<double> x1;
    QVector<double> y1;
    QVector<double> y2;
    QStringList hey;
    int i=0;
    QString tmp;
    int j;
    void zoomrect();

    
private slots:
    void on_mode_auto_clicked();
    void reception();
    void moteur_debug();
    void on_arret_clicked();

    void on_exporter_clicked();

    void on_moteur_clicked();

    void on_enregister_clicked();

    void on_grille_toggled(bool checked);

    void on_serie_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
