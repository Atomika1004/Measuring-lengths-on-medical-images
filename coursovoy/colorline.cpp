#include "colorline.h"
#include "ui_colorline.h"

ColorLine::ColorLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorLine)
{
    ui->setupUi(this);
    currentLineColor = Qt::black;
}

ColorLine::~ColorLine()
{
    delete ui;
}

bool ColorLine::isRadioButtonActive()
{
    // Проверяем, активен ли хотя бы один из RadioButton
    return ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked();
}

QColor ColorLine::getCurrentLineColor()
{
    // Возвращаем текущий цвет линии
    return currentLineColor;
}

void ColorLine::on_radioButton_toggled(bool checked)
{
    if (checked) {
        QColor selectedColor = QColor(0, 255, 0, 128);
        emit colorChanged(selectedColor);
    }
}


void ColorLine::on_radioButton_2_toggled(bool checked)
{
    if (checked) {
        QColor selectedColor = QColor(0, 255, 255, 128);  // Замените на вашу логику выбора цвета
        emit colorChanged(selectedColor);
    }
}

void ColorLine::on_radioButton_3_toggled(bool checked)
{
    if (checked) {
        QColor selectedColor = QColor(255, 0, 0, 128);  // Замените на вашу логику выбора цвета
        emit colorChanged(selectedColor);
    }
}

