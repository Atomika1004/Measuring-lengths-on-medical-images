#ifndef COLORLINE_H
#define COLORLINE_H

#include <QWidget>

namespace Ui {
class ColorLine;
}

class ColorLine : public QWidget
{
    Q_OBJECT

public:
    explicit ColorLine(QWidget *parent = nullptr);
    ~ColorLine();
    bool isRadioButtonActive();
    QColor getCurrentLineColor();

signals:
    void colorChanged(const QColor& newColor);

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

private:
    Ui::ColorLine *ui;
    QColor currentLineColor;
};

#endif // COLORLINE_H
