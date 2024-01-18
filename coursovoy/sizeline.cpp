#include "sizeline.h"
#include "ui_sizeline.h"
#include <QPainter>
SizeLine::SizeLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SizeLine)
{
    ui->setupUi(this);

}

SizeLine::~SizeLine()
{
    delete ui;
}

bool SizeLine::isRadioButtonActive()
{
    // Проверяем, активен ли хотя бы один из RadioButton
    return ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked();
}

int SizeLine::getCurrentLineWidth()
{
    // Возвращаем текущую толщину линии
    return currentLineWidth;
}

void SizeLine::on_radioButton_3_toggled(bool checked)
{
    if (checked)
    {
        currentLineWidth = 1;
        emit lineWidthChanged(currentLineWidth);
    }
}


void SizeLine::on_radioButton_2_toggled(bool checked)
{
    if (checked)
    {
        currentLineWidth = 2;
        emit lineWidthChanged(currentLineWidth);
    }
}


void SizeLine::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
        currentLineWidth = 3;
        emit lineWidthChanged(currentLineWidth);
    }
}
