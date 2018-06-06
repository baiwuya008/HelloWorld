#include "rotatewidget.h"
#include <QTransform>
#include <QDebug>

class RotateWidgetPrivate {
    Q_DISABLE_COPY(RotateWidgetPrivate)
public:
    explicit RotateWidgetPrivate(RotateWidget *parent);
    ~RotateWidgetPrivate();


private slots:
    void onStart(QString path);
    void onStop();
    void initList(QList<QString> list);

private:
    Q_DECLARE_PUBLIC(RotateWidget)
    RotateWidget* const q_ptr;


    void paintEvent(QPainter &painter, QPaintEvent *event);
    bool rotate();


    QString mPath;
    bool isStart = false;
    int currentRotateAngle = 0;
    int currentWidth = 0;
    int currentHeight = 0;
    void rotatePicture(QPainter &painter, int angle);
    QPixmap getPixmap(QString path);
    QTimer* mRotateTimer = NULL;


    QList<QString> mList;
    bool isList = false;
    int position = 0;
};

RotateWidget::RotateWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new RotateWidgetPrivate(this))
{

}

RotateWidgetPrivate::RotateWidgetPrivate(RotateWidget *parent)
    : q_ptr(parent)
{
    mRotateTimer = new QTimer(parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mRotateTimer, SIGNAL(timeout()), parent, SLOT(onTimeout()), type);
}


RotateWidget::~RotateWidget() {

}

void RotateWidget::paintEvent(QPaintEvent *event)
{
    Q_D(RotateWidget);
    if (d->isList && d->mList.size() < 0) {
        return;
    }


    if (!d->isList && d->mPath.length() < 2) {
        return;
    }



    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::SmoothPixmapTransform
                           | QPainter::TextAntialiasing);


    d->paintEvent(painter, event);
}

void RotateWidgetPrivate::paintEvent(QPainter &painter, QPaintEvent *event)
{
    if (isList) {
        painter.drawPixmap(0, 0, getPixmap(mList.at(position)));
        return;
    }


    rotatePicture(painter, currentRotateAngle);
    painter.drawPixmap(0, 0, getPixmap(mPath));
}

void RotateWidget::resizeEvent(QResizeEvent *event)
{
    Q_D(RotateWidget);
    d->currentWidth = event->size().width();
    d->currentHeight = event->size().height();
}

void RotateWidget::init(QList<QString> list)
{
    Q_D(RotateWidget);
    d->initList(list);
    stop();
}

void RotateWidgetPrivate::initList(QList<QString> list) {
    mList = list;
    isList = true;
    position = 0;
}


void RotateWidget::init(QString path) {
    Q_D(RotateWidget);
    d->mPath = path;
    stop();
}

void RotateWidget::start()
{
    start("");
}

void RotateWidget::start(QString path) {
    Q_D(RotateWidget);
    d->onStart(path);
    update();
}

void RotateWidget::stop() {
    Q_D(RotateWidget);
    d->onStop();
    update();
}

void RotateWidget::onTimeout()
{
    Q_D(RotateWidget);
    if (d->rotate()) {
        update();
    }else {
        stop();
    }
}

bool RotateWidgetPrivate::rotate() {
    if (isStart) {
        position += 1;
        position = position % (mList.size()-1);
        currentRotateAngle += 5;
        currentRotateAngle = currentRotateAngle % 360;
    }else {
        currentRotateAngle = 0;
        position = 0;
    }

    return isStart;
}
void RotateWidgetPrivate::onStart(QString path)
{
    onStop();
    isStart = true;
    currentRotateAngle = 0;
    if (path.length() > 2) {
        mPath = path;
    }

    mRotateTimer->start(100);
}


void RotateWidgetPrivate::onStop()
{
    position = 0;
    if (isStart) {
        isStart = false;
        currentRotateAngle = 0;
        mRotateTimer->stop();
    }
}



QPixmap RotateWidgetPrivate::getPixmap(QString path) {
    QImage image;
    image.load(path);
    return  QPixmap::fromImage(image.scaled(QSize(currentWidth, currentHeight)));
}

void RotateWidgetPrivate::rotatePicture(QPainter &painter, int angle)
{
    QTransform form;
    form.translate(currentWidth/2, currentHeight/2);
    form.rotate(angle);
    form.translate(-currentWidth/2, -currentHeight/2);
    painter.setTransform(form);
}


RotateWidgetPrivate::~RotateWidgetPrivate()
{

}
