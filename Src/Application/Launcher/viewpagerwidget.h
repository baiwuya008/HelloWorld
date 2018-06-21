#ifndef VIEWPAPERWIDGET_H
#define VIEWPAPERWIDGET_H

#include <QWidget>
#include "Src/CommonUserWidget/CustomItemDelegate.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <QListView>
#include <QTimer>


class ViewPagerWidgetPrivate;
class ViewPagerWidget : public QListView
{
    Q_OBJECT
    Q_DISABLE_COPY(ViewPagerWidget)
    Q_PROPERTY(int horizontalOffset READ horizontalOffset WRITE setHorizontalOffset)
public:
    explicit ViewPagerWidget(QWidget *parent = NULL);
    ~ViewPagerWidget();

signals:
    void changeViewPager(int index);
    void itemClick(int index);
protected:
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public slots:
private:
    Q_DECLARE_PRIVATE(ViewPagerWidget)
    ViewPagerWidgetPrivate* const d_ptr;
    void setHorizontalOffset(int value);
    bool mFinish = true;
};


class ViewPagerItemDelegate : public CustomItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(ViewPagerItemDelegate)
public:
    explicit ViewPagerItemDelegate(QObject *parent = NULL);
    ~ViewPagerItemDelegate();

signals:
     void itemClick(int index);
protected:
    void paint(QPainter* painter,const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    void mousePressEvent(QMouseEvent* event,
                         QAbstractItemModel *model,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index);
    void mouseMoveEvent(QMouseEvent* event,
                        QAbstractItemModel *model,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index);
    void mouseReleaseEvent(QMouseEvent* event,
                           QAbstractItemModel *model,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index);
private slots:
    void clickTimeout();

private:
    void startCheckClick();
    void stopCheckClick();
    void initClickData();

    const int ICON_WIDTH = 100;
    const int ICON_HEIGHT = 100;
    const int PADDING_LEFT = 87;
    const int PADDING_TOP = 31;
    const int SPACE_WIDTH = 75;
    const int SPACE_HEIGHT = 76;
    const int TEXT_SIZE = 20;
    const int TEXT_SPACE_HEIGHT = 14;
    const int COLUMN_NUMBER = 4;
    const int ON_CLICK_TIME_OUT = 500;//按下的超时时间
    const int MIN_MOVE_X = 10;

    QTimer *mClickTimer = NULL;
    QPoint mStartMovePoint;
    bool mOnClick = false;
    int mCurrentPressIndex = -1;
    int mCurrentPressPageIndex = -1;
};


#endif // VIEWPAPERWIDGET_H
