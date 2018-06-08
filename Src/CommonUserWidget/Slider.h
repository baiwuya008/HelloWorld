#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>
#include <QCommonStyle>

class Slider : public QSlider
{
    Q_OBJECT
    Q_DISABLE_COPY(Slider)
public:
    explicit Slider(QWidget* parent = NULL);
    ~Slider();
protected:
    bool event(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
signals:
    void sliderPressed(const int value);
    void sliderMoved(const int value);
    void sliderReleased(const int value);
private:
    QCommonStyle mStyle;
};

#endif // SLIDER_H
