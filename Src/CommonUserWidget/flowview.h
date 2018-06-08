#ifndef FLOWVIEW_H
#define FLOWVIEW_H

#include <QWidget>
#include <QDebug>
#include <QImage>
#include <QVector>
#include <QPainter>
#include <QResizeEvent>
#include <math.h>
#include <QRect>
#include <QRectF>
#include <QList>
#include <QPropertyAnimation>
#include <QTimer>
#include "flowadapter.h"
#include <QMouseEvent>

class FlowViewPrivate;
class FlowView : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(FlowView)
    Q_PROPERTY(int moveX READ getMoveX WRITE setMoveAniX)
public:
    explicit FlowView(QWidget *parent = NULL);
    ~FlowView();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

signals:
    void itemClick(int position, QString path);
    void switchCenterView(int position);
private slots:
    void clickTimeout();
    void onFinished();
    void refreshView();

public slots:
    void setAdapter(FlowAdapter *adapter);
    void showPrevious();
    void showNext();
public slots:
private:
    Q_DECLARE_PRIVATE(FlowView)
    FlowViewPrivate* const d_ptr;


    void initializePropertyAnimation();
    int moveX = 0;
    int getMoveX();
    void setMoveAniX(int moveX);
    QPropertyAnimation* moveAnimation = NULL;
    bool isStartAni = false;
    void startAni(int fromX, int toX);
    void stopAni();
};

#endif // FLOWVIEW_H
