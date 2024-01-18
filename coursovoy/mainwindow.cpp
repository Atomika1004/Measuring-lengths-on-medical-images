#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <cmath>
#include <QLineEdit>
#include <QMessageBox>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);
    setMouseTracking(true);
    sizeLine = new SizeLine();
    colorLine = new ColorLine();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);

    QPixmap scaledImage = currentImage.scaled(ui->label->size(), Qt::KeepAspectRatio);
    painter.drawPixmap(ui->label->geometry().topLeft(), scaledImage);

    for (const auto& line : lines)
    {
        QPen pen(currentLineColor);
        if (sizeLine->isRadioButtonActive())
        {
            pen.setWidth(sizeLine->getCurrentLineWidth());
        }
        else
        {
            pen.setWidth(2);
        }

        painter.setPen(pen);

        QPoint scaledStart(line.start.x() * scaledImage.width() / currentImage.width(),
                           line.start.y() * scaledImage.height() / currentImage.height());

        QPoint scaledEnd(line.end.x() * scaledImage.width() / currentImage.width(),
                         line.end.y() * scaledImage.height() / currentImage.height());

        painter.drawLine(scaledStart, scaledEnd);

        double angle = atan2(line.end.y() - line.start.y(), line.end.x() - line.start.x());

        int tickLength = 5;

        QPoint tick1Start(scaledEnd.x() - tickLength * cos(angle + M_PI / 2),
                          scaledEnd.y() - tickLength * sin(angle + M_PI / 2));

        QPoint tick1End(scaledEnd.x() + tickLength * cos(angle + M_PI / 2),
                        scaledEnd.y() + tickLength * sin(angle + M_PI / 2));

        QPoint tick2Start(scaledStart.x() - tickLength * cos(angle + M_PI / 2),
                          scaledStart.y() - tickLength * sin(angle + M_PI / 2));

        QPoint tick2End(scaledStart.x() + tickLength * cos(angle + M_PI / 2),
                        scaledStart.y() + tickLength * sin(angle + M_PI / 2));

        painter.drawLine(tick1Start, tick1End);
        painter.drawLine(tick2Start, tick2End);

        QPoint midPoint((scaledStart.x() + scaledEnd.x()) / 2, (scaledStart.y() + scaledEnd.y()) / 2);
        QString distanceText = QString::number(calculateDistance(line.start, line.end,true));

        painter.drawText(midPoint.x(), midPoint.y() - 5, distanceText);
    }
    if (ui->checkBox->isChecked()) {
        drawGrid(painter, scaledImage.width(), scaledImage.height());
    }
    update();
}

int MainWindow::calculateDistance(const QPoint& p1, const QPoint& p2, bool useLineEditValue)
{
    int dx = p2.x() - p1.x();
    int dy = p2.y() - p1.y();

    if (useLineEditValue) {
        bool ok;
        int multiplier = ui->lineEdit->text().toInt(&ok);

        if (!ok || ui->lineEdit->text().isEmpty() || multiplier == 0 ) {
            multiplier = 1;
        }


        return sqrt(dx * dx + dy * dy) * multiplier;
    }

    return sqrt(dx * dx + dy * dy);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    currentLine.start = event->pos();
    currentLine.end = event->pos();
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    currentLine.end = event->pos();

    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    lines.append(currentLine);

    update();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label && event->type() == QEvent::Resize)
    {
        update();
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_pushButton_clicked()
{
    QString inagePath = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users/atomika/Documents/Waves", "All files (*.jpg)");
    currentImage.load(inagePath);
    currentImage = currentImage.scaled(ui->label->size(), Qt::KeepAspectRatio);
    lines.clear();
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    lines.clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    QPixmap snapshot(this->size());
    this->render(&snapshot);
    QString fileName = "screenshot_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".png";
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), fileName, tr("Images (*.png)"));
    if (!filePath.isEmpty()) {
        snapshot.save(filePath);
    }

}

void MainWindow::on_checkBox_toggled(bool checked)
{
    //update();
}

void MainWindow::drawGrid(QPainter& painter, int imageWidth, int imageHeight)
{
    // Интервал между линиями сетки
    int gridSize = 20;

    // Цвет линий сетки
    QPen gridPen(QColor(128, 128, 128, 128));
    gridPen.setWidth(1);  // Толщина линий

    painter.setPen(gridPen);

    // Рисуем горизонтальные линии
    for (int y = gridSize; y < imageHeight; y += gridSize)
    {
        painter.drawLine(0, y, imageWidth, y);
    }

    // Рисуем вертикальные линии
    for (int x = gridSize; x < imageWidth; x += gridSize)
    {
        painter.drawLine(x, 0, x, imageHeight);
    }
}


void MainWindow::on_action_triggered()
{

    QMessageBox msgBox;
    QPixmap iconPixmap("/Users/atomika/Documents/Waves/image.png");
    msgBox.setIconPixmap(iconPixmap);

    msgBox.setWindowTitle("Руководство для пользователя");
    msgBox.setText("Приложение, позволяющее врачам и специалистам измерять длины на изображениях с высокой точностью. Пользователям предоставляется возможность создавать отрезки, представляющие измеряемую линейку, указывая начальную и конечную точки на изображении. Длина отрезка измеряется в пикселях и затем конвертируется в миллиметры с использованием пользовательски задаваемого коэффициента.");

    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox msgBox;
    QPixmap iconPixmap("/Users/atomika/Documents/Waves/image1.png");
    msgBox.setIconPixmap(iconPixmap);

    msgBox.setWindowTitle("Справка");
    msgBox.setText("Автор столь чудесной программы - Алексей Попов. Студент группы бИВТ-223");

    msgBox.addButton(QMessageBox::Ok);
    msgBox.addButton(QMessageBox::Cancel);

    msgBox.exec();
}

void MainWindow::updateLineWidth(int newLineWidth)
{
    currentLineWidth = newLineWidth;
}

void MainWindow::on_action_3_triggered()
{
    sizeLine->setWindowTitle("Толщина линейки");
    sizeLine->show();
    connect(sizeLine, &SizeLine::lineWidthChanged, this, &MainWindow::updateLineWidth);
}

void MainWindow:: onLineColorChanged(const QColor& newColor)
{
    currentLineColor = newColor;
}
void MainWindow::on_action_4_triggered()
{
    colorLine->setWindowTitle("Цвет линейки");
    colorLine->show();
    connect(colorLine, &ColorLine::colorChanged, this, &MainWindow::onLineColorChanged);
}



