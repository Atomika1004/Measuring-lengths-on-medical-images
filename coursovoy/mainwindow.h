#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QPoint>
#include <QWidget>
#include <QPen>
#include <QLineEdit>
#include "sizeline.h"
#include "colorline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_toggled(bool checked);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void updateLineWidth(int newLineWidth);

    void onLineColorChanged(const QColor& newColor);

    void on_action_4_triggered();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject* obj, QEvent* event) override;
    int calculateDistance(const QPoint& p1, const QPoint& p2,bool useLineEditValue);
    void drawGrid(QPainter& painter, int imageWidth, int imageHeight);
private:
    Ui::MainWindow *ui;
    QString inagePath;
    QPixmap currentImage;
    SizeLine *sizeLine;
    int currentLineWidth;
    ColorLine *colorLine;
    QColor currentLineColor;

struct Line
{
    QPoint start;
    QPoint end;
};

QVector<Line> lines;
Line currentLine;
};

#endif // MAINWINDOW_H
