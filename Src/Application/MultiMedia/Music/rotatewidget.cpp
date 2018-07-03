#include "rotatewidget.h"
#include <QTransform>
#include <QDebug>
#include <QBitmap>

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
    QPixmap pixmapToRound(int radius);
    QTimer* mRotateTimer = NULL;


    QList<QString> mList;
    bool isList = false;
    bool isPixmap = false;
    QPixmap *mPixmap = NULL;
    int position = 0;
    int aniTime = 100;
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

    if (d->isPixmap && NULL == d->mPixmap) {
        return;
    }

    if (!d->isList && !d->isPixmap && d->mPath.length() < 2) {
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
    if (isPixmap && mPixmap != NULL) {
        painter.drawPixmap(0, 0, pixmapToRound(currentWidth/2));
    }else {
        painter.drawPixmap(0, 0, getPixmap(mPath));
    }
}


QPixmap RotateWidgetPrivate::pixmapToRound(int radius)
{
    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 180, 180);

    QPixmap image = mPixmap->scaled(size);
    image.setMask(mask);
    return image;
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
    isPixmap = false;
    position = 0;
}


void RotateWidget::init(QString path) {
    Q_D(RotateWidget);
    d->mPath = path;
    d->isPixmap = false;
    d->isList = false;
    if (d->mPixmap != NULL) {
        d->mPixmap = NULL;
    }
    stop();
}

void RotateWidget::setPixmap(QPixmap *pixmap)
{
    Q_D(RotateWidget);
    d->isPixmap = true;
    d->isList = false;
    d->mPath = "";
    d->mPixmap = pixmap;
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

void RotateWidget::setAniTime(int time)
{
    Q_D(RotateWidget);
    d->aniTime = time;
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
        if (mList.size() > 0) {
            position = position % (mList.size());
        }

        currentRotateAngle += 3;
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

    mRotateTimer->start(aniTime);
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
