#ifndef SIZELINE_H
#define SIZELINE_H

#include <QWidget>

namespace Ui {
class SizeLine;
}

class SizeLine : public QWidget
{
    Q_OBJECT

public:
    explicit SizeLine(QWidget *parent = nullptr);
    ~SizeLine();

    bool isRadioButtonActive(); // Новый метод для проверки активности RadioButton
    int getCurrentLineWidth(); // Новый метод для получения текущей толщины линии

signals:
    void lineWidthChanged(int newLineWidth);

public slots:
    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

private:
    Ui::SizeLine *ui;
    int currentLineWidth;
};

#endif // SIZELINE_H
