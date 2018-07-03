#include "flowview.h"
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

class FlowViewPrivate {
    Q_DISABLE_COPY(FlowViewPrivate)
public:
    explicit FlowViewPrivate(FlowView *parent);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


    void paintLeft(QPainter &painter, float moveScale);
    void paintRight(QPainter &painter, float moveScale);
    void paintCenter(QPainter &painter, float moveScale);
public slots:
    void previous();
    void next();
    void selectPosition(int position);
    void setFlowAdapter(FlowAdapter *adapter);
private slots:
    void onClickTimeout();
private:
    Q_DECLARE_PUBLIC(FlowView)
    FlowView* const q_ptr;
    void initializeParent();

    FlowAdapter* mAdapter = NULL;

    void initBoundRight();
    void initBoundLeft();
    QPixmap getPixmap(QString path, int width, int height);


    void initMoveMark();
    inline int getCurrentMoveX() {
        return this->currentMoveX;
    }
    void setMoveX(int moveX);
    void setMoveAni(int moveX, bool isFinish);


    QTimer* mClickTimer = NULL;
    bool isOnClick = false;
    int mClickPosition = -1;
    void onClick();
    void startCheckClick(QPoint p);
    bool computeClickPosition(QPoint &p);
    void stopCheckClick();
    void refreshCenterView();



    const int MOVE_MIN_X = 5;//最小移动间距
    const int ON_CLICK_TIME_OUT = 500;//按下的超时时间
    const int MOV_ANI_TIME = 200;//移动动画的时间
    const int PICTURE_WIDTH = 250;//图片的宽度
    const int PICTURE_HEIGHT = 200;//图片的高度
    const float SIZE_SCALE = 0.2f;//控件大小等比缩放的比例
    const float OVERLAP_X = 0.2f;// 子控件X轴重叠的比例,
    const int OVERLAP_WIDTH = OVERLAP_X*PICTURE_WIDTH;//固定覆盖大小
    const QString CENTER_COLOR = "#0267fa";
    const QString NORMAL_COLOR = "#959596";


    QPoint downPoint;//按下时的坐标
    int width = 0;
    int height = 0;
    int currentMoveScaleWidth = 0;//移动一个图片的宽度
    int currentMoveX = 0;//当前X轴移动的距离
    float currentMoveScale = 0.0f;//当前移动缩放控件大小的比例
    int boundsLeft = 0;//左边边界的距离
    int boundsRight = 0;//右边边界距离
};

FlowViewPrivate::FlowViewPrivate(FlowView *parent) : q_ptr(parent)
{
    initializeParent();
}


void FlowView::initializePropertyAnimation() {
    moveAnimation = new QPropertyAnimation(this, QByteArray("moveX"));
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    connect(moveAnimation, SIGNAL(finished()), this,
            SLOT(onFinished()), type);
}

FlowView::FlowView(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new FlowViewPrivate(this))
{
    initializePropertyAnimation();
}

void FlowViewPrivate::initializeParent() {
    Q_Q(FlowView);

    //设置背景色
    //    QPalette pal = q->palette();
    //    pal.setColor(QPalette::Background, Qt::gray);
    //    q->setAutoFillBackground(true); //不继承父组件的背景色
    //    q->setPalette(pal);

    mClickTimer = new QTimer(q);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mClickTimer, SIGNAL(timeout()), q, SLOT(clickTimeout()), type);
}


void FlowView::refreshView() {
    update();
    Q_D(FlowView);
    d->refreshCenterView();
}

void FlowViewPrivate::refreshCenterView()
{
    Q_Q(FlowView);
    if (mAdapter != NULL) {
        q->switchCenterView(mAdapter->getCenterPosition(), mAdapter->getTotalLength());
    }
}

void FlowView::onFinished() {
    Q_D(FlowView);
    isStartAni = false;
    d->setMoveAni(moveX, true);
}

int FlowView::getMoveX() {
    Q_D(FlowView);
    return d->getCurrentMoveX();
}

void FlowView::clickTimeout() {
    Q_D(FlowView);
    d->onClickTimeout();
}

FlowView::~FlowView() {

}

bool FlowViewPrivate::computeClickPosition(QPoint &p) {
    if (width < 0 || height < 0) {
        return false;
    }


    int downX = p.x();
    int downY = p.y();

    int leftPosition = mAdapter->getLeftPosition();
    int count = mAdapter->getCount();
    int centerPosition = mAdapter->getCenterPosition();


    float scale = 0.0f;
    int left = 0;
    int top = 0;
    int displayWidth = 0;
    int childHeight = 0;


    if (leftPosition >= 0) {//计算左边控件点击
        scale = SIZE_SCALE;
        left = (width-PICTURE_WIDTH)/2;
        for (int i = centerPosition-1; i >= leftPosition; i--) {
            displayWidth = PICTURE_WIDTH*(1-scale) - OVERLAP_WIDTH;
            childHeight = PICTURE_HEIGHT * (1 - scale);
            left -= displayWidth;
            top = (height-childHeight)/2;


            if (downX > left && downX < left+displayWidth
                    && downY > top && downY < top + childHeight) {
                mClickPosition = i;
                return true;
            }


            scale += SIZE_SCALE;
        }

    }

    if (count > 1) {//计算右边控件点击
        scale = SIZE_SCALE;
        left = (width+PICTURE_WIDTH)/2;
        for (int i = centerPosition+1; i < count; i++) {
            displayWidth = PICTURE_WIDTH*(1-scale) - OVERLAP_WIDTH;
            childHeight = PICTURE_HEIGHT * (1 - scale);
            top = (height-childHeight)/2;

            if (downX > left && downX < left+displayWidth
                    && downY > top && downY < top + childHeight) {

                mClickPosition = i;
                return true;
            }

            left += displayWidth;
            scale += SIZE_SCALE;
        }
    }

    if (centerPosition >= 0) {//计算中间的点击
        left = (width-PICTURE_WIDTH)/2;
        top = (height-PICTURE_HEIGHT)/2;
        if (downX > left && downX < left+PICTURE_WIDTH
                && downY > top && downY < top + PICTURE_HEIGHT) {
            mClickPosition = centerPosition;
            return true;
        }
    }

    return false;
}


void FlowViewPrivate::startCheckClick(QPoint p) {
    if (!isOnClick && computeClickPosition(p)) {
        isOnClick = true;
        mClickTimer->start(ON_CLICK_TIME_OUT);
    }

}

void FlowViewPrivate::stopCheckClick() {
    if (isOnClick) {
        isOnClick = false;
        mClickTimer->stop();
    }
}



void FlowViewPrivate::onClickTimeout() {
    stopCheckClick();
    mClickPosition = -1;
}

void FlowViewPrivate::onClick() {
    if (isOnClick) {
        stopCheckClick();
        if (mClickPosition >= 0) {
            Q_Q(FlowView);
            selectPosition(mClickPosition);
            emit q->itemClick(mClickPosition, mAdapter->getPath(mClickPosition));
        }
    }

    mClickPosition = -1;
}


void FlowViewPrivate::selectPosition(int position) {
    if (position == mAdapter->getCenterPosition()) {
        return;
    }
}

void FlowView::startAni(int fromX, int toX) {
    Q_D(FlowView);
    if (NULL == d->mAdapter) {
        return;
    }

    isStartAni = true;
    int time = (1.0*abs(toX - fromX)/d->currentMoveScaleWidth)*d->MOV_ANI_TIME;
    moveAnimation->setDuration(time);
    moveAnimation->setStartValue(fromX);
    moveAnimation->setEndValue(toX);
    //设置动画效果，这里设置平滑移动效果
    moveAnimation->setEasingCurve(QEasingCurve::Linear);
    moveAnimation->start();
}

void FlowView::stopAni() {
    if (isStartAni) {
        isStartAni = false;
        moveAnimation->stop();
    }
}


void FlowViewPrivate::setMoveAni(int moveX, bool isFinish) {
    Q_Q(FlowView);
    if (isFinish) {
        if (currentMoveX > 0 && currentMoveX >= currentMoveScaleWidth/2) {
            mAdapter->movePosition(1);
        }else if (currentMoveX < 0 && abs(currentMoveX) >= currentMoveScaleWidth/2) {
            mAdapter->movePosition(1);
        }

        initMoveMark();
        refreshCenterView();
    }else {
        if (moveX == currentMoveScaleWidth) {
            mAdapter->movePosition(-1);
            refreshCenterView();
        }else if (moveX == -currentMoveScaleWidth) {
            mAdapter->movePosition(1);
            refreshCenterView();
        }
        setMoveX(moveX);
    }
}

void FlowView::setMoveAniX(int moveX) {
    if (moveAnimation->endValue() != 0 && 0 == moveX) {//防止调用动画第一次左右moveX为0的回调
        return;
    }

    Q_D(FlowView);
    d->setMoveAni(moveX, false);
    update();
}

void FlowViewPrivate::setMoveX(int moveX) {
    currentMoveX = moveX % currentMoveScaleWidth;
    currentMoveScale = (1.0*currentMoveX)/currentMoveScaleWidth;
    //这里防止moveScaleSize大于1的现象
    currentMoveScale = currentMoveScale > 1 ? 1 : currentMoveScale;
}

/**
     * 初始化触摸移动的数据
     */
void FlowViewPrivate::initMoveMark() {
    currentMoveX = 0;
    currentMoveScale = 0;
}

void FlowViewPrivate::initBoundRight() {
    if (width < 0) {
        return;
    }

    int count = mAdapter->getCount();
    if (count < 1) {
        return;
    }


    int centerPosition = mAdapter->getCenterPosition();
    float scale = SIZE_SCALE;
    int right = (width+PICTURE_WIDTH)/2;
    for (int i = centerPosition+1; i < count; i++) {
        right += PICTURE_WIDTH*(1-scale) - OVERLAP_WIDTH;

        scale += SIZE_SCALE;
    }

    boundsRight = right;

    //    qDebug() << "initBoundRight boundsRight = " << boundsRight;
}

void FlowViewPrivate::initBoundLeft() {
    if (width < 0) {
        return;
    }

    int leftPosition = mAdapter->getLeftPosition();
    if (leftPosition < 0) {
        return;
    }

    int centerPosition = mAdapter->getCenterPosition();
    float scale = SIZE_SCALE;
    int left = (width-PICTURE_WIDTH)/2;
    for (int i = centerPosition-1; i >= leftPosition; i--) {
        left -= PICTURE_WIDTH*(1-scale) - OVERLAP_WIDTH;

        scale += SIZE_SCALE;
    }


    boundsLeft = left;

    //    qDebug() << "initBoundLeft boundsLeft = " << boundsLeft;
}

QPixmap FlowViewPrivate::getPixmap(QString path, int width, int height) {
    QImage image;
    image.load(path);
    return  QPixmap::fromImage(image.scaled(QSize(width, height)));
}

void FlowViewPrivate::paintEvent(QPaintEvent *event) {
    Q_Q(FlowView);

    QPainter painter(q);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::SmoothPixmapTransform
                           | QPainter::TextAntialiasing);

    initBoundLeft();
    initBoundRight();

    float moveScale = currentMoveScale*SIZE_SCALE;
    if (currentMoveX > 0 && abs(currentMoveX) >= currentMoveScaleWidth/2) {//往右边滑动超过一半
        paintRight(painter, moveScale);
        paintCenter(painter, moveScale);
        paintLeft(painter, moveScale);
    }else if (currentMoveX < 0 && abs(currentMoveX) >= currentMoveScaleWidth/2) {//往左边滑动超过一半
        paintLeft(painter, moveScale);
        paintCenter(painter, moveScale);
        paintRight(painter, moveScale);
    }else {
        paintLeft(painter, moveScale);
        paintRight(painter, moveScale);
        paintCenter(painter, moveScale);
    }

}


void FlowViewPrivate::paintRight(QPainter &painter, float moveScale) {
    int left = 0;
    int top = 0;
    int childWidth = 0;
    int childMoveWidth = 0;
    int childHeight = 0;
    float scale = 0.0f;
    int startX = 0;
    int prevDisplayWidth = 0;
    int moveXOffset = 0;
    bool isPaint = true;


    int centerPosition = mAdapter->getCenterPosition();
    int rightPosition = mAdapter->getCount() -1;


    scale = (rightPosition - centerPosition) * SIZE_SCALE;

    //显示向左滑动超过一半，显示右边下一个控件
    if (!mAdapter->isLastPosition() && currentMoveX < 0 &&
            abs(currentMoveX) >= currentMoveScaleWidth/2) {
        childWidth = PICTURE_WIDTH * (1 - scale);//还需要保持最左边的一个初始宽度，防止初始值发生变化

        scale -= SIZE_SCALE;

        childMoveWidth = PICTURE_WIDTH * (1 - scale + moveScale);
        childHeight = PICTURE_HEIGHT * (1 - scale + moveScale);
        top = (height-childHeight)/2;

        startX = boundsRight - childWidth;
        moveXOffset = (1.0*childWidth/currentMoveScaleWidth)*currentMoveX;
        left = startX - childWidth - moveXOffset;

        scale += SIZE_SCALE;

        painter.drawPixmap(left, top, getPixmap(mAdapter->getPath(mAdapter->getCount()),
                                                childMoveWidth, childHeight));
        painter.setPen(QPen(QColor(FlowViewPrivate::NORMAL_COLOR), 2));
        painter.drawRect(left, top, childMoveWidth, childHeight);
    }


    startX = boundsRight;
    for (int i = rightPosition; i > centerPosition; i--) {
        isPaint = true;
        childWidth = PICTURE_WIDTH * (1 - scale);
        childMoveWidth = PICTURE_WIDTH * (1- scale - moveScale);
        childHeight = PICTURE_HEIGHT * (1 - scale - moveScale);
        top = (height-childHeight)/2;

        if (currentMoveX <= 0) {//往左边滑动,是上一个控件的显示宽度
            prevDisplayWidth = (1.0*PICTURE_WIDTH*(1-scale+SIZE_SCALE)) - OVERLAP_WIDTH;
            moveXOffset = (1.0*prevDisplayWidth/currentMoveScaleWidth)*currentMoveX;
            left = startX - childWidth + moveXOffset;
        }else {//往右边滑动, 就是本控件的宽度 - 下一个控件的覆盖宽度
            if (i == rightPosition) {
                if ((rightPosition - centerPosition) < mAdapter->getHalfMaxCount()) {//右边还可以多显示一个
                    moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
                    left = startX - childWidth + moveXOffset;
                } else if (currentMoveX >= currentMoveScaleWidth/2) {
                    isPaint = false;
                }else {
                    moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
                    left = boundsRight - childWidth - moveXOffset;
                }
            }else {
                //移动距离是本控件的宽度 - 下一个控件覆盖的宽度
                moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
                left = startX - childWidth + moveXOffset;
            }
        }

        if (isPaint) {
            painter.drawPixmap(left, top, getPixmap(mAdapter->getPath(i), childMoveWidth, childHeight));
            painter.setPen(QPen(QColor(FlowViewPrivate::NORMAL_COLOR), 2));
            painter.drawRect(left, top, childMoveWidth, childHeight);
        }


        startX -= childWidth - OVERLAP_WIDTH;
        scale -= SIZE_SCALE;
    }

}



void FlowViewPrivate::paintCenter(QPainter &painter, float moveScale) {
    int centerPosition = mAdapter->getCenterPosition();
    int childWidth = PICTURE_WIDTH * (1-abs(moveScale));
    int childHeight = PICTURE_HEIGHT * (1-abs(moveScale));
    int top = (height-childHeight)/2;
    int displayWidth = PICTURE_WIDTH*(1-SIZE_SCALE) - OVERLAP_WIDTH;
    int moveXOffset = 0;
    if (currentMoveX > 0) {//往右边滑动，是本控件的宽度 - 下一个控件覆盖的宽度
        moveXOffset = ((1.0*(PICTURE_WIDTH-OVERLAP_WIDTH))/currentMoveScaleWidth)*currentMoveX;
    }else {//往左滑动，是下一个控件的宽度 - 下一个控件覆盖的宽度
        moveXOffset = ((1.0*displayWidth)/currentMoveScaleWidth)*currentMoveX;
    }
    int left = (width-PICTURE_WIDTH)/2 + moveXOffset;


    painter.drawPixmap(left, top, getPixmap(mAdapter->getPath(centerPosition),
                                            childWidth,
                                            childHeight));

    painter.setPen(QPen(QColor(FlowViewPrivate::CENTER_COLOR), 2));
    painter.drawRect(left, top, childWidth, childHeight);
}



void FlowViewPrivate::paintLeft(QPainter &painter, float moveScale) {
    int left = 0;
    int top = 0;
    int childWidth = 0;
    int childMoveWidth = 0;
    int childHeight = 0;
    int nextDisplayWidth = 0;
    int moveXOffset = 0;
    bool isPaint = true;
    int startX = 0;

    int centerPosition = mAdapter->getCenterPosition();
    int leftPosition = mAdapter->getLeftPosition();


    //1.第一步绘制左边图片，从0开始
    float scale = (centerPosition - leftPosition) * SIZE_SCALE;

    //显示向右滑动超过一半，显示左边下一个控件
    if (leftPosition > 0 && currentMoveX >= currentMoveScaleWidth/2) {//往右边滑动超过一半,显示最左边一个
        childWidth = PICTURE_WIDTH * (1 - scale);//还需要保持最左边的一个初始宽度，防止初始值发生变化
        scale -= SIZE_SCALE;
        childMoveWidth = PICTURE_WIDTH * (1 - scale - moveScale);
        childHeight = PICTURE_HEIGHT * (1 - scale - moveScale);
        top = (height-childHeight)/2;

        startX = boundsLeft + (childWidth-OVERLAP_WIDTH);
        moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
        left = startX - moveXOffset;

        scale += SIZE_SCALE;

        painter.drawPixmap(left, top, getPixmap(mAdapter->getPath(mAdapter->getLeftPosition()-1),
                                                childMoveWidth, childHeight));
        painter.setPen(QPen(QColor(FlowViewPrivate::NORMAL_COLOR), 2));
        painter.drawRect(left, top, childMoveWidth, childHeight);
    }



    startX = boundsLeft;
    for (int i = leftPosition; i < centerPosition && i >= 0; i++) {
        isPaint = true;
        childWidth = PICTURE_WIDTH * (1 - scale);
        childMoveWidth = PICTURE_WIDTH * (1 - scale + moveScale);
        childHeight = PICTURE_HEIGHT * (1 - scale + moveScale);
        top = (height-childHeight)/2;


        if (currentMoveX <= 0) {//往左边滑动, 是缩小
            if (i == leftPosition) {
                if (centerPosition < mAdapter->getHalfMaxCount()
                        && mAdapter->getCount() > mAdapter->getHalfMaxCount()) {//左边还可以多显示一个
                    nextDisplayWidth = PICTURE_WIDTH*(1 - scale - SIZE_SCALE) - OVERLAP_WIDTH;
                    moveXOffset = (1.0*nextDisplayWidth/currentMoveScaleWidth)*currentMoveX;
                    left = boundsLeft + moveXOffset;
                }else if (abs(currentMoveX) >= currentMoveScaleWidth/2) {
                    isPaint = false;
                }else {
                    moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
                    left = boundsLeft - moveXOffset;
                }
            }else {
                moveXOffset = (1.0*nextDisplayWidth/currentMoveScaleWidth)*currentMoveX;
                left = startX + moveXOffset;
            }
        }else {//往右边滑动, 是放大
            moveXOffset = (1.0*(childWidth-OVERLAP_WIDTH)/currentMoveScaleWidth)*currentMoveX;
            left = startX + moveXOffset;
        }

        if (isPaint) {
            painter.drawPixmap(left, top, getPixmap(mAdapter->getPath(i), childMoveWidth, childHeight));
            painter.setPen(QPen(QColor(FlowViewPrivate::NORMAL_COLOR), 2));
            painter.drawRect(left, top, childMoveWidth, childHeight);
        }

        startX += childWidth - OVERLAP_WIDTH;
        nextDisplayWidth = childWidth  - OVERLAP_WIDTH;
        scale -= SIZE_SCALE;
    }

}


void FlowView::paintEvent(QPaintEvent *event) {
    Q_D(FlowView);

    if (NULL == d->mAdapter || d->mAdapter->getTotalLength() < 1) {
        return;
    }

    d->paintEvent(event);
}


void FlowView::mousePressEvent(QMouseEvent *event)
{
    if (rect().contains(event->pos())) {//这个是判断是否在控件内的滑动
        Q_D(FlowView);
        d->mousePressEvent(event);
    }
}

void FlowView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(FlowView);
    d->mouseReleaseEvent(event);
}

void FlowViewPrivate::mouseReleaseEvent(QMouseEvent *event)
{
    onClick();
    Q_Q(FlowView);
    if (abs(currentMoveX) > MOVE_MIN_X) {//大于最小移动距离在做动画效果
        if (abs(currentMoveX) >= currentMoveScaleWidth/2) {
            if (currentMoveX > 0) {
                q->startAni(currentMoveX, currentMoveScaleWidth);
            }else {
                q->startAni(currentMoveX, -currentMoveScaleWidth);
            }
        }else {
            q->startAni(currentMoveX, 0);
        }
    }else {
        initMoveMark();
        Q_Q(FlowView);
        q->update();
    }
}

void FlowView::mouseMoveEvent(QMouseEvent *event)
{
    if (rect().contains(event->pos())) {
        Q_D(FlowView);
        d->mouseMoveEvent(event);
    }
}

void FlowViewPrivate::mouseMoveEvent(QMouseEvent *event)
{
    int moveX = event->pos().x() - downPoint.x();
    if (abs(moveX) < MOVE_MIN_X) {
        return;
    }


    stopCheckClick();
    setMoveX(moveX);
    if (currentMoveX > 0 && mAdapter->getCenterPosition() <= 0) {//滑动到最左边了
        downPoint = event->pos();
        initMoveMark();
        return;
    }else if (currentMoveX < 0 && mAdapter->getCenterPosition() >= (mAdapter->getCount()-1)) {//滑动到最右边
        downPoint = event->pos();
        initMoveMark();
        return;
    }


    if (abs(moveX) >= currentMoveScaleWidth) {//滑动到下一个图片
        downPoint = event->pos();
        int moveRow = moveX < 0 ? 1 : -1;
        mAdapter->movePosition(moveRow);
        initMoveMark();
        refreshCenterView();
    }

    Q_Q(FlowView);
    q->update();
}


void FlowViewPrivate::mousePressEvent(QMouseEvent *event) {
    stopCheckClick();
    startCheckClick(event->pos());
    initMoveMark();
    downPoint = event->pos();
}

void FlowView::resizeEvent(QResizeEvent *event) {
    Q_D(FlowView);
    d->width = event->size().width();
    d->height = event->size().height();
    d->currentMoveScaleWidth = d->PICTURE_WIDTH - d->OVERLAP_WIDTH;

    qDebug() << "resizeEvent width = " << d->width
             << "; height = " << d->height
             << "; currentMoveScaleWidth = " << d->currentMoveScaleWidth;
}


void FlowViewPrivate::previous() {
    if (mAdapter->getCenterPosition() >= (mAdapter->getCount()-1)) {
        return;
    }

    Q_Q(FlowView);
    q->startAni(currentMoveX, -currentMoveScaleWidth);
}
void FlowViewPrivate::next() {
    if (mAdapter->getCenterPosition() <= 0) {
        return;
    }
    Q_Q(FlowView);
    q->startAni(currentMoveX, currentMoveScaleWidth);
}


void FlowView::setAdapter(FlowAdapter *adapter) {
    if (NULL == adapter) {
        return;
    }


    connect(adapter, SIGNAL(notifyData()), this, SLOT(refreshView()));
    Q_D(FlowView);
    d->setFlowAdapter(adapter);
    update();
}

void FlowViewPrivate::setFlowAdapter(FlowAdapter *adapter) {
    this->mAdapter = adapter;
}

void FlowView::showPrevious() {
    Q_D(FlowView);
    d->previous();
}

void FlowView::showNext() {
    Q_D(FlowView);
    d->next();
}
