// The main program (provided by the course), hw1 of TIE-20100/TIE-20106
//
// DO ****NOT**** EDIT THIS FILE!
// (Preferably do not edit this even temporarily. And if you still decide to do so
//  (for debugging, for example), DO NOT commit any changes to git, but revert all
//  changes later. Otherwise you won't be able to get any updates/fixes to this
//  file from git!)

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "mainprogram.hh"

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void update_view();
    void output_text(std::ostringstream &output);

    bool check_stop_pressed() const;

public slots:
    void execute_line();
    void cmd_selected(int idx);
    void number_selected(QString number);
    void select_file();
    void clear_input_line();
    void fit_view();
    void scene_selection_change();
    void clear_selection();

private:
    Ui::MainWindow *ui = nullptr;

    QGraphicsScene* gscene_ = nullptr;

    MainProgram mainprg_;

    bool stop_pressed_ = false;

    bool selection_clear_in_progress = false;
};


// Class for drawing an arrow
#include <QGraphicsLineItem>
#include <QRectF>
#include <QPainterPath>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPolygonF>
#include <QPointF>

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 1 };

    Arrow(QPointF start, QPointF end, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    QPointF start;
    QPointF end;
    QPolygonF arrowHead;
};

#endif // MAINWINDOW_HH
