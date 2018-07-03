#include "viewpagerwidget.h"
#include <qDebug>
#include <QStandardItemModel>
#include <QList>
#include <QPainter>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QTextItem>


class ViewPagerVariant
{
public:
    ViewPagerVariant();
    ~ViewPagerVariant();

    int mPageIndex = -1;
    QList<QPixmap*> mNormalList;
    QList<QPixmap*> mPressList;
    QList<QString> mTitleList;
};
Q_DECLARE_METATYPE(ViewPagerVariant)


class ViewPagerWidgetPrivate {
    Q_DISABLE_COPY(ViewPagerWidgetPrivate)
public:
    explicit ViewPagerWidgetPrivate(ViewPagerWidget *parent);
    ~ViewPagerWidgetPrivate();

protected:
    bool mousePressEvent(QMouseEvent *event);
    bool mouseMoveEvent(QMouseEvent* event);
    bool mouseReleaseEvent(QMouseEvent* event);
private:
    Q_DECLARE_PUBLIC(ViewPagerWidget)
    ViewPagerWidget* const q_ptr;

    void initializeBasicWidget();
    void initFirstPager();
    void initSecondPager();
    void startAni(int fromX, int toX);
    void computeMovePagerIndex(int minMoveX, int moveX, bool isMove);


    inline QRect geometryFit(const int x, const int y, const int w, const int h) {
        return QRect(x, y, w, h);
    }

    const int ITEM_WIDTH = 800;
    const int ITEM_HEIGHT = 384;
    const int MOVE_ANI_TIME = 300;

    int mCurrentPageIndex = 0;
    ViewPagerItemDelegate *mViewPaperItemDelegate = NULL;
    QStandardItemModel *mStandardItemModel = NULL;
    QPoint mStartMovePoint;
    int mPressHorizontalOffset = 0;
    QPropertyAnimation *mMoveAnimation = NULL;
    QList<QStandardItem*> mPageList;
};


ViewPagerVariant::ViewPagerVariant() {

}

ViewPagerVariant::~ViewPagerVariant() {

}

ViewPagerWidget::ViewPagerWidget(QWidget *parent)
    : QListView(parent)
    , d_ptr(new ViewPagerWidgetPrivate(this))
{

}

ViewPagerWidget::~ViewPagerWidget()
{

}

ViewPagerWidgetPrivate::ViewPagerWidgetPrivate(ViewPagerWidget *parent) : q_ptr(parent)
{
    initializeBasicWidget();
}

ViewPagerWidgetPrivate::~ViewPagerWidgetPrivate()
{

}

void ViewPagerWidgetPrivate::startAni(int fromX, int toX) {
    Q_Q(ViewPagerWidget);
    if (NULL == mMoveAnimation) {
        mMoveAnimation = new QPropertyAnimation(q, QByteArray("horizontalOffset"));
    }
    mMoveAnimation->setDuration(MOVE_ANI_TIME);
    mMoveAnimation->setStartValue(fromX);
    mMoveAnimation->setEndValue(toX);
    mMoveAnimation->start();
}

/**
  * startAni 启动动画后的回调方法
  * QByteArray("horizontalOffset"))
 */
void ViewPagerWidget::setHorizontalOffset(int value) {
    QScrollBar* scrollBar = horizontalScrollBar();
    if (NULL != scrollBar) {
        if (value % width() == 0) {//移动动画结束
            Q_D(ViewPagerWidget);
            mFinish = true;
            //移动结束，发送切换viewpager的信号，修改外部界面显示
            emit changeViewPager(d->mCurrentPageIndex);
        }
        scrollBar->setValue(value);
    }
}


bool ViewPagerWidgetPrivate::mousePressEvent(QMouseEvent *event)
{
    Q_Q(ViewPagerWidget);
    if (q->rect().contains(event->pos())) {//这个是判断是否在控件内的滑动
        mStartMovePoint = event->pos();
        mPressHorizontalOffset = q->horizontalOffset();
        QModelIndex modelIndex = q->indexAt(event->pos());
        if (modelIndex.isValid()) {
            q->update(modelIndex);
        }
        return true;
    }

    return false;
}

bool ViewPagerWidgetPrivate::mouseMoveEvent(QMouseEvent *event)
{
    Q_Q(ViewPagerWidget);
    if (q->rect().contains(event->pos())) {
        //得到相对移动的距离，horizontalOffset()是listview移动的距离
        int relativeX = (mStartMovePoint-event->pos()).x();
        mStartMovePoint = event->pos();
        q->horizontalScrollBar()->setValue(q->horizontalOffset() + relativeX);
        computeMovePagerIndex(ITEM_WIDTH, q->horizontalOffset()+relativeX, true);
        return true;
    }

    return false;
}

bool ViewPagerWidgetPrivate::mouseReleaseEvent(QMouseEvent *event)
{
    Q_Q(ViewPagerWidget);
    computeMovePagerIndex(ITEM_WIDTH/3, q->horizontalOffset()-mPressHorizontalOffset, false);
    startAni(q->horizontalOffset(), mCurrentPageIndex*ITEM_WIDTH);
    return true;
}

void ViewPagerWidgetPrivate::computeMovePagerIndex(int minMoveX, int moveX, bool isMove)
{
    int pageIndex = mCurrentPageIndex;
    if (moveX > 0 && moveX > minMoveX) {//向左滑动超过一半
        pageIndex += 1;
    }else if (moveX < 0 && qAbs(moveX) > minMoveX) {//向右滑动超过一半
        pageIndex -= 1;
    }

    int maxRowCount = mStandardItemModel->invisibleRootItem()->rowCount() - 1;
    pageIndex = pageIndex < 0 ? 0 : pageIndex;
    pageIndex = pageIndex > maxRowCount ? maxRowCount : pageIndex;

    if (pageIndex != mCurrentPageIndex) {
        mCurrentPageIndex = pageIndex;
        if (isMove) {
            Q_Q(ViewPagerWidget);
            emit q->changeViewPager(mCurrentPageIndex);
        }
    }
}



void ViewPagerWidgetPrivate::initializeBasicWidget()
{
    Q_Q(ViewPagerWidget);
    q->setMovement(QListView::Static);
    q->setViewMode(QListView::IconMode);
    q->setFlow(QListView::TopToBottom);

    QPalette palette = q->palette();
    palette.setBrush(QPalette::Base, Qt::NoBrush);
    q->setPalette(palette);
    q->setFrameShape(QListView::NoFrame);
    q->setHorizontalScrollMode(QListView::ScrollPerPixel);
    q->setEditTriggers(QListView::NoEditTriggers);
    //该方法是设置无滑动条
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    mStandardItemModel = new QStandardItemModel(q);
    initFirstPager();
    initSecondPager();
    mViewPaperItemDelegate = new ViewPagerItemDelegate(q);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mViewPaperItemDelegate, &ViewPagerItemDelegate::itemClick, q, &ViewPagerWidget::itemClick, type);
    q->setItemDelegate(mViewPaperItemDelegate);
    q->setModel(mStandardItemModel);
}

void ViewPagerWidgetPrivate::initFirstPager() {
    ViewPagerVariant firstVariant;
    firstVariant.mPageIndex = 0;

    firstVariant.mNormalList.clear();
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_fm_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_am_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_music_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_video_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_elink_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_bt_music_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_img_a.png")));
    firstVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_setting_a.png")));


    firstVariant.mPressList.clear();
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_fm_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_am_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_music_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_video_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_elink_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_bt_music_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_img_b.png")));
    firstVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_setting_b.png")));


    firstVariant.mTitleList.clear();
    firstVariant.mTitleList.append(QString::fromLocal8Bit("FM"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("AM"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("音乐"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("视频"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("E-Link"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("蓝牙"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("图片"));
    firstVariant.mTitleList.append(QString::fromLocal8Bit("设置"));

    QStandardItem *firstItem = new QStandardItem();
    firstItem->setSizeHint(QSize(ITEM_WIDTH, ITEM_HEIGHT));//设置item的宽和高
    firstItem->setData(qVariantFromValue(firstVariant), Qt::UserRole);
    mStandardItemModel->setItem(mStandardItemModel->invisibleRootItem()->rowCount(), 0, firstItem);
    mPageList.append(firstItem);
}


void ViewPagerWidgetPrivate::initSecondPager() {
    ViewPagerVariant secondVariant;
    secondVariant.mPageIndex = 1;

    secondVariant.mNormalList.clear();
    secondVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_bt_music_a.png")));
    secondVariant.mNormalList.append(new QPixmap(QString(":/img/Launcher/img_launcher_am_a.png")));

    secondVariant.mPressList.clear();
    secondVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_bt_music_b.png")));
    secondVariant.mPressList.append(new QPixmap(QString(":/img/Launcher/img_launcher_am_b.png")));

    secondVariant.mTitleList.clear();
    secondVariant.mTitleList.append(QString::fromLocal8Bit("蓝牙音乐"));
    secondVariant.mTitleList.append(QString::fromLocal8Bit("TEST_2"));

    QStandardItem *secondItem = new QStandardItem();
    secondItem->setSizeHint(QSize(ITEM_WIDTH, ITEM_HEIGHT));
    secondItem->setData(qVariantFromValue(secondVariant), Qt::UserRole);
    mStandardItemModel->setItem(mStandardItemModel->invisibleRootItem()->rowCount(), 0, secondItem);
    mPageList.append(secondItem);
}

/**
 * 该方法是得到测量后控件大小的回调方法
 * event->size().width() 测量后的宽度
 * event->size().height() 测量后的高度
 */
void ViewPagerWidget::resizeEvent(QResizeEvent *event)
{
//    qDebug() << "ViewPagerWidget resizeEvent size().width() = " << event->size().width()
//             << "; size().height() = " << event->size().height();
}

void ViewPagerWidget::mousePressEvent(QMouseEvent *event)
{
    Q_D(ViewPagerWidget);
    if (d->mousePressEvent(event)) {
        //这里调用这个才能触发ViewPagerItemDelegate::mousePressEvent该方法的调用
        QListView::mousePressEvent(event);
    }
}

void ViewPagerWidget::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(ViewPagerWidget);
    if (d->mouseMoveEvent(event)) {
        QListView::mouseMoveEvent(event);
    }
}

void ViewPagerWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(ViewPagerWidget);
    if (d->mouseReleaseEvent(event)) {
        QListView::mouseReleaseEvent(event);
        this->update();
    }
}

ViewPagerItemDelegate::ViewPagerItemDelegate(QObject *parent) : CustomItemDelegate(parent)
{
    mOnClick = false;
    mClickTimer = new QTimer(this);
    connect(mClickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
}

ViewPagerItemDelegate::~ViewPagerItemDelegate()
{
}

void ViewPagerItemDelegate::mouseReleaseEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (mOnClick && mCurrentPressIndex >= 0 && mCurrentPressPageIndex >= 0) {
        emit itemClick(mCurrentPressPageIndex*8+mCurrentPressIndex);
    }
    initClickData();
}

void ViewPagerItemDelegate::clickTimeout()
{
    stopCheckClick();
}

void ViewPagerItemDelegate::startCheckClick() {
    if (!mOnClick) {
        mOnClick = true;
        mClickTimer->start(ON_CLICK_TIME_OUT);
    }
}

void ViewPagerItemDelegate::stopCheckClick() {
    if (mOnClick) {
        mOnClick = false;
        mClickTimer->stop();
    }
}

void ViewPagerItemDelegate::initClickData()
{
    mCurrentPressIndex = -1;
    mCurrentPressPageIndex = -1;
}

void ViewPagerItemDelegate::mouseMoveEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (qAbs(event->pos().x()-mStartMovePoint.x()) > MIN_MOVE_X) {
        stopCheckClick();
        initClickData();
    }
}

void ViewPagerItemDelegate::mousePressEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    ViewPagerVariant variant = qvariant_cast<ViewPagerVariant>(index.data(Qt::UserRole));
    int left = PADDING_LEFT + option.rect.x();
    int top = PADDING_TOP;
    int count = variant.mTitleList.size();
    for (int i = 0; i < count; ++i) {
        QRect rect(left, top, ICON_WIDTH, ICON_HEIGHT);
        if (rect.contains(event->pos())) {
            mStartMovePoint = event->pos();
            mCurrentPressIndex = i;
            mCurrentPressPageIndex = variant.mPageIndex;
            startCheckClick();
            break;
        }

        left += ICON_WIDTH + SPACE_WIDTH;
        if ((i+1) > 1 && 0 == (i+1)%COLUMN_NUMBER) {
            top += ICON_HEIGHT + SPACE_HEIGHT;
            left = PADDING_LEFT + option.rect.x();
        }
    }
}

void ViewPagerItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QFont ft("Microsoft YaHei");
    ft.setPointSize(TEXT_SIZE);
    painter->setFont(ft);
    painter->setPen(Qt::white);
    QFontMetrics fm(painter->font());

    ViewPagerVariant variant = qvariant_cast<ViewPagerVariant>(index.data(Qt::UserRole));


    int left = PADDING_LEFT + option.rect.x();
    int top = PADDING_TOP;
    int count = variant.mTitleList.size();
    int textLeft = 0;
    int textTop = 0;
    QString text;
    for (int i = 0; i < count; i++) {
        text = QObject::tr(variant.mTitleList.at(i).toLocal8Bit().constData());

        textLeft = left + (ICON_WIDTH-fm.boundingRect(text).width())/2;
        textTop = top + ICON_HEIGHT + TEXT_SPACE_HEIGHT + TEXT_SIZE;

        if (i == mCurrentPressIndex && mCurrentPressPageIndex == variant.mPageIndex) {
            painter->drawPixmap(left, top, *variant.mPressList.at(i));
        }else {
            painter->drawPixmap(left, top, *variant.mNormalList.at(i));
        }
        painter->drawText(textLeft, textTop, text);

        left += ICON_WIDTH + SPACE_WIDTH;
        if ((i+1) > 1 && 0 == (i+1)%COLUMN_NUMBER) {
            top += ICON_HEIGHT + SPACE_HEIGHT;
            left = PADDING_LEFT + option.rect.x();
        }
    }
}
