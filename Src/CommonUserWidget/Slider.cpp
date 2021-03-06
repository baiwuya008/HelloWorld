#include "Slider.h"
#include <QDebug>
#include <QMouseEvent>


Slider::Slider(QWidget *parent)
    : QSlider(Qt::Horizontal, parent)
{
    mStyle;
}

Slider::~Slider()
{
}

bool Slider::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::KeyPress:
    case QEvent::KeyRelease: {
        event->accept();
        return true;
        break;
    }
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove: {
        event->ignore();
        break;
    }
    default: {
        break;
    }
    }
    return QSlider::event(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    int value = mStyle.sliderValueFromPosition(minimum(), maximum(), event->pos().x(), width());
    setValue(value);
    setSliderDown(true);
    emit sliderPressed(value);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    int value = mStyle.sliderValueFromPosition(minimum(), maximum(), event->pos().x(), width());
    setValue(value);
    emit sliderMoved(value);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    int value = mStyle.sliderValueFromPosition(minimum(), maximum(), event->pos().x(), width());
    setValue(value);
    setSliderDown(false);
    emit sliderReleased(value);
}
