#ifndef ECO2DSOLVERUI_H
#define ECO2DSOLVERUI_H

#include <QWidget>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>

#include <vector>
#include <list>
#include <iostream>
#include <shlobj.h>
#include <chrono>
#include <thread>

#include "eco2dsolver.h"
#include "reader.h"
#include "output.h"

namespace Ui {
class Eco2dSolverUI;
}

class Eco2dSolverUI : public QWidget
{
    Q_OBJECT

public:
    explicit Eco2dSolverUI(QWidget *parent = nullptr);
    ~Eco2dSolverUI();

private slots:
    void on_left_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Eco2dSolverUI *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem * rect;
    std::vector<QGraphicsRectItem *> rects;
    std::vector<QGraphicsTextItem *>rects_label;
    QGraphicsLineItem *x_axis;
    QGraphicsLineItem *y_axis;
    QBrush *red_brush;
    QBrush *blue_brush;
    QPen *black_pen;
    QPen *red_pen;
    int color;
    reader rd;
    Eco2dSolver es;
    reader r;
    output o;
    const int scale_factor = 6;
    std::list<Eco2dSolver::State>::iterator it_current_state;
    size_t current_state_number;
    size_t max_state_number;
    const std::vector<QBrush> colors = std::vector<QBrush>{
                                                            QBrush(QColor::fromRgb(43,0,212)), //Blue
                                                            QBrush(QColor::fromRgb(173, 172, 56)), //Yellow
                                                            QBrush(QColor::fromRgb(212, 43, 0)) //Red
                                                           };

    void solve_problem();
    void draw_state();
    void draw_rectangle();
    void draw_container();
    void set_pens_brushes();

};

#endif // ECO2DSOLVERUI_H
