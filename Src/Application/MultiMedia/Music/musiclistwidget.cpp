#include "musiclistwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "musiclistitem.h"
#include "Src/CommonUserWidget/BmpButton.h"
#include <QTextCodec>
#include <QDebug>
#include <QListWidget>
#include <QStandardItemModel>
#include <QListView>
#include <QScrollBar>
#include <QList>


class MusicListWidgetPrivate {
    Q_DISABLE_COPY(MusicListWidgetPrivate)
public:
    explicit MusicListWidgetPrivate(MusicListWidget *parent, int type);
    ~MusicListWidgetPrivate();
private slots:
    void onItemClick(int index);
    void onPrev();
    void onNext();
    void onMainDir();
    void onUpDir();
    void onAllList();

private:
    Q_DECLARE_PUBLIC(MusicListWidget)
    MusicListWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent, int type);
    void initializeDirView(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeListView(QWidget *parent);
    void setTextSize(QWidget *text);
    void addItemList();
    void flipOver(bool isNext);
    void flipOverIndex(int moveIndex);
    void appendListView(QString path);
    void clearListView();
    void refreshItemView(int index);
    void computeItemIndex();
    void scanBaseFiles(int queryMode, QString dirPath);

    MusicListItem *mDirItem = NULL;
    QListWidget *mListView = NULL;
    QList<MusicListItem*> mListItem;

    int mSelectItemIndex = -1;
    int mDeviceType = -1;
    int mQueryMode = -1;
    int mMediaType = -1;

    QString mDirPath;
    QString mRootPath;
    QString mCurrentPlayPath;
    const int PAGE_MAX_SIZE = 5;
    const int ITEM_WIDTH = 600;
    const int ITEM_HEIGHT = 46;
};


MusicListWidgetPrivate::MusicListWidgetPrivate(MusicListWidget *parent, int type)
    : q_ptr(parent)
{
    initializeBasicWidget(parent, type);
}


MusicListWidget::MusicListWidget(QWidget *parent, int type)
    : QWidget(parent)
    , d_ptr(new MusicListWidgetPrivate(this, type))
{
    setFixedSize(QSize(800, 435));
}


void MusicListWidgetPrivate::initializeBasicWidget(QWidget *parent, int type) {
    this->mMediaType = type;
    initializeDirView(parent);
    initializeClickView(parent);
    initializeListView(parent);
}

void MusicListWidgetPrivate::initializeDirView(QWidget *parent)
{
    mDirItem = new MusicListItem(parent);
    mDirItem->setSize(18);
    mDirItem->setFixedSize(QSize(600, 30));
    mDirItem->initItem("nothing", ":/Res/drawable/multimedia/music_file_icon.png");
    mDirItem->setGeometry(93, 30, 0, 0);
}

void MusicListWidgetPrivate::initializeClickView(QWidget *parent) {
    QWidget *mClickListWidget = new QWidget(parent);
    mClickListWidget->setFixedSize(QSize(800, 60));
    mClickListWidget->setGeometry(0, 324, 0, 0);

    mClickListWidget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = mClickListWidget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(":/Res/drawable/multimedia/music_list_click_bg.png")
                            .scaled(mClickListWidget->size(),
                                    Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation)));
    mClickListWidget->setPalette(palette);

    QHBoxLayout *mClickListLayout = new QHBoxLayout;
    mClickListWidget->setLayout(mClickListLayout);
    mClickListLayout->setContentsMargins(0, 0, 0, 0);


    BmpButton *prevBtn = new BmpButton(mClickListWidget);
    prevBtn->setFixedSize(QSize(200, 60));
    prevBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_list_prev_normal.png");
    prevBtn->setPressBmpPath(":/Res/drawable/multimedia/music_list_prev_focus.png");
    prevBtn->setGeometry(-2, 0, 0, 0);

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

    BmpButton *mainDirBtn = new BmpButton(mClickListWidget);
    mainDirBtn->setFixedSize(QSize(200, 60));
    setTextSize(mainDirBtn);
    mainDirBtn->setText(QString::fromLocal8Bit("主文件夹"));
    mainDirBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_list_click_normal.png");
    mainDirBtn->setPressBmpPath(":/Res/drawable/multimedia/music_list_click_focus.png");
    mainDirBtn->setGeometry(199, 0, 0, 0);

    BmpButton *upDirBtn = new BmpButton(mClickListWidget);
    upDirBtn->setFixedSize(QSize(200, 60));
    setTextSize(upDirBtn);
    upDirBtn->setText(QString::fromLocal8Bit("上一文件夹"));
    upDirBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_list_click_normal.png");
    upDirBtn->setPressBmpPath(":/Res/drawable/multimedia/music_list_click_focus.png");
    upDirBtn->setGeometry(399, 0, 0, 0);

    BmpButton *nextBtn = new BmpButton(mClickListWidget);
    nextBtn->setFixedSize(QSize(200, 60));
    nextBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_list_next_normal.png");
    nextBtn->setPressBmpPath(":/Res/drawable/multimedia/music_list_next_focus.png");
    nextBtn->setGeometry(601, 0, 0, 0);



    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(prevBtn, SIGNAL(released()), parent, SLOT(prevFile()), type);
    QObject::connect(nextBtn, SIGNAL(released()), parent, SLOT(nextFile()), type);
    QObject::connect(mainDirBtn, SIGNAL(released()), parent, SLOT(mainDir()), type);
    QObject::connect(upDirBtn, SIGNAL(released()), parent, SLOT(upDir()), type);
}

void MusicListWidget::prevFile()
{
    Q_D(MusicListWidget);
    d->onPrev();
}

void MusicListWidget::nextFile()
{
    Q_D(MusicListWidget);
    d->onNext();
}

void MusicListWidget::mainDir()
{
    Q_D(MusicListWidget);
    d->onMainDir();
}

void MusicListWidget::upDir()
{
    Q_D(MusicListWidget);
    d->onUpDir();
}


void MusicListWidgetPrivate::onPrev()
{
    flipOver(false);
}

void MusicListWidgetPrivate::onNext()
{
    flipOver(true);
}

void MusicListWidgetPrivate::flipOver(bool isNext)
{
    //QPoint(300, 25)这个给一个item大小的范围内就可以了，最好给item的中心点位置，用于计算获取当前显示的最前面的位置
    int currentFirstIndex = mListView->indexAt(QPoint(ITEM_WIDTH/2, ITEM_HEIGHT/2)).row();
    //这个获取当前滑动的距离用来计算滑动了几个item，ITEM_HEIGHT是item的高度
    //    int verticalOffset = mListView->verticalScrollBar()->value();
    //    int slideIndex = verticalOffset/ITEM_HEIGHT;

    int currentLastIndex = currentFirstIndex + PAGE_MAX_SIZE;
    int moveIndex = 0;
    if (isNext) {
        moveIndex = currentLastIndex + PAGE_MAX_SIZE - 1;
    }else {
        moveIndex = currentFirstIndex - PAGE_MAX_SIZE;
    }

    flipOverIndex(moveIndex);
}

void MusicListWidgetPrivate::flipOverIndex(int moveIndex)
{
    moveIndex = moveIndex >= (mListView->count()-1) ?
                (mListView->count()-1) : moveIndex;
    moveIndex = moveIndex < 0 ? 0 : moveIndex;

    if (mListView->currentRow() == moveIndex) {//防止滑动后currentRow没变无法导致翻页功能
        mListView->setCurrentRow(-1, QItemSelectionModel::Select);
    }
    mListView->setCurrentRow(moveIndex, QItemSelectionModel::Select);
}

void MusicListWidgetPrivate::onMainDir()
{
    if (mDirPath.length() < 1) {
        return;
    }
    scanBaseFiles(MediaUtils::QUERY_Main_Dir, "");
}

void MusicListWidget::showAllList()
{
    Q_D(MusicListWidget);
    d->onAllList();
}


void MusicListWidgetPrivate::onUpDir()
{
    if (mDirPath.length() < 1) {
        return;
    }

    scanBaseFiles(MediaUtils::QUERY_Current_Dir, MediaUtils::getUpperPath(mDirPath));
}

void MusicListWidgetPrivate::onAllList()
{
    if (mDirPath.length() < 1) {
        return;
    }
    scanBaseFiles(MediaUtils::QUERY_All_Files, mRootPath);
}

void MusicListWidgetPrivate::scanBaseFiles(int queryMode, QString dirPath)
{
    if (mRootPath.length() < 2) {
        return;
    }

    if (MediaUtils::QUERY_All_Files == queryMode
            && MediaUtils::QUERY_All_Files == mQueryMode) {
        return;
    }

    if (MediaUtils::QUERY_Main_Dir == queryMode
            &&  MediaUtils::QUERY_Main_Dir == mQueryMode) {
        return;
    }

    if (MediaUtils::QUERY_Current_Dir == queryMode
            && MediaUtils::QUERY_All_Files == mQueryMode) {
        return;
    }

    if (MediaUtils::QUERY_Current_Dir == queryMode
            && dirPath.length() < mRootPath.length()) {
        queryMode = MediaUtils::QUERY_All_Files;
        dirPath = mRootPath;
    }

    if (MediaUtils::QUERY_Current_Dir == queryMode
            && !mRootPath.compare(dirPath)) {
        queryMode = MediaUtils::QUERY_Main_Dir;
    }

    Q_Q(MusicListWidget);
    int type = mMediaType;
    if (MediaUtils::MUSIC_LIST == mMediaType || MediaUtils::MUSIC == mMediaType) {
        type = MediaUtils::MUSIC;
    }else if (MediaUtils::VIDEO_LIST == mMediaType || MediaUtils::VIDEO == mMediaType) {
        type = MediaUtils::VIDEO;
    }

    emit q->queryFiles(mDeviceType, type, queryMode, dirPath);
}


void MusicListWidgetPrivate::initializeListView(QWidget *parent)
{
    mSelectItemIndex = -1;
    mListView = new QListWidget(parent);

    mListView->setFixedSize(QSize(710, 230));
    mListView->setStyleSheet("background-color:transparent;");
    mListView->setGeometry(42, 70, 0, 0);

    mListView->setMovement(QListView::Static);
    mListView->setViewMode(QListView::IconMode);
    mListView->setFlow(QListView::LeftToRight);
    mListView->setFrameShape(QListView::NoFrame);
    mListView->setSelectionMode(QAbstractItemView::SingleSelection);
    mListView->setHorizontalScrollMode(QListView::ScrollPerPixel);
    mListView->setEditTriggers(QListView::NoEditTriggers);
    mListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mListView->verticalScrollBar()->setStyleSheet(
                //进度条背景样式
                "QScrollBar:vertical"
                "{"
                "background:#383838;"
                "width:8px;"
                "margin:0px,0px,0px,0px;"
                "padding-top:0px; padding-bottom:0px;"
                "border-radius:4px;"
                "}"

                //进度条滑动时的背景样式
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                "{"
                "background:#383838;"
                "width:8px;"
                "margin:0px,0px,0px,0px;"
                "padding-top:0px; padding-bottom:0px;"
                "border-radius:4px;"
                "}"

                "QScrollBar::handle:vertical" //滑动条
                "{"
                "background:#2997fc;"
                "width:8px;"
                "min-height:121;"
                "border-radius:4px;"
                "}"

                "QScrollBar::handle:vertical:hover" //滑动条有焦点的时候hover
                "{"
                "background:#2997fc;"
                "width:8px;"
                "min-height:121;"
                "border-radius:4px;"
                "}"

                "QScrollBar::add-line:vertical"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:bottom;"//这个是设置下箭头的
                "}"

                "QScrollBar::add-line:vertical:hover"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:bottom;"
                "}"

                "QScrollBar::sub-line:vertical"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:top;" //顶部的往上图标
                "}"

                "QScrollBar::sub-line:vertical:hover"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:top;"
                "}"
                );


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mListView, SIGNAL(clicked(QModelIndex)), parent, SLOT(itemClick(QModelIndex)), type);

    //    addItemList();
}

void MusicListWidgetPrivate::addItemList()
{
    QListWidgetItem *item = NULL;
    MusicListItem *infoItem = NULL;
    mSelectItemIndex = 1;
    for(int i = 0; i < 30; i++) {
        item = new QListWidgetItem;
        item->setSizeHint(QSize(ITEM_WIDTH, ITEM_HEIGHT));

        infoItem = new MusicListItem(NULL, mMediaType);
        infoItem->setFixedSize(QSize(ITEM_WIDTH, ITEM_HEIGHT));
        infoItem->initItem("fileName_" + QString::number(i));

        if (i == mSelectItemIndex) {
            infoItem->refreshItem(true);
        }

        mListView->addItem(item);
        mListView->setItemWidget(item, infoItem);
        mListItem.append(infoItem);
    }
}

void MusicListWidgetPrivate::appendListView(QString path)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(ITEM_WIDTH, ITEM_HEIGHT));

    MusicListItem *infoItem = NULL;
    if (MediaUtils::isDirPath(path)) {
        infoItem = new MusicListItem(NULL, MediaUtils::DIR_LIST);
    }else {
        infoItem = new MusicListItem(NULL, mMediaType);
    }

    infoItem->setFixedSize(QSize(ITEM_WIDTH, ITEM_HEIGHT));
    infoItem->initItem(path);

    mListView->addItem(item);
    mListView->setItemWidget(item, infoItem);
    mListItem.append(infoItem);
}

void MusicListWidgetPrivate::clearListView()
{
    mSelectItemIndex = -1;
    mDeviceType = -1;
    mDirPath = "";
    mListView->clear();
    int size = mListItem.size();
    for (int i = 0; i < size; i++) {
        delete mListItem.at(i);
    }
    mListItem.clear();
}


void MusicListWidget::itemClick(QModelIndex index)
{
    Q_D(MusicListWidget);
    d->onItemClick(index.row());
}

void MusicListWidget::setPlayNext(bool isNext)
{
    Q_D(MusicListWidget);
    int index = d->mSelectItemIndex;
    index = isNext ? (index+1) : (index-1);
    d->onItemClick(index);
}

void MusicListWidgetPrivate::onItemClick(int index) {
    if (index < 0 || index >= mListItem.size()
            || index == mSelectItemIndex) {
        return;
    }

    if (MediaUtils::isDirPath(mListItem.at(index)->getPath())) {
        scanBaseFiles(false, mListItem.at(index)->getPath());
    }else {
        Q_Q(MusicListWidget);
        mCurrentPlayPath = mListItem.at(index)->getPath();
        emit q->selectItem(mDeviceType, mCurrentPlayPath);
        refreshItemView(index);
        onAllList();
    }
}

void MusicListWidget::refreshItem(int index)
{
    Q_D(MusicListWidget);
    d->refreshItemView(index);
}

void MusicListWidgetPrivate::refreshItemView(int index)
{
    if (mSelectItemIndex >= 0) {
        mListItem.at(mSelectItemIndex)->refreshItem(false);
    }
    mSelectItemIndex = index;
    mListItem.at(mSelectItemIndex)->refreshItem(true);
}

void MusicListWidgetPrivate::computeItemIndex()
{
    if (mSelectItemIndex >= 0 && mSelectItemIndex < mListItem.size()) {
        mListItem.at(mSelectItemIndex)->refreshItem(false);
    }

    if (mCurrentPlayPath.length() < 2) {
        mSelectItemIndex = -1;
        return;
    }

    int size = mListItem.size();
    for (int i = 0; i < size; i++) {
        if (!mCurrentPlayPath.compare(mListItem.at(i)->getPath())) {
            mSelectItemIndex = i;
            mListItem.at(mSelectItemIndex)->refreshItem(true);
            flipOverIndex(i);
            return;
        }
    }
}


void MusicListWidget::updateList(int deviceType, int queryMode, QString &dirPath, QStringList &pathList)
{
    Q_D(MusicListWidget);

    d->clearListView();
    d->mDeviceType = deviceType;
    d->mQueryMode = queryMode;
    d->mDirPath = dirPath;
    d->mDirItem->setName(dirPath);

    if (MediaUtils::QUERY_All_Files == queryMode) {
        d->mRootPath = dirPath;
    }

    if (pathList.size() > 0) {
        int size = pathList.size();
        for (int i = 0; i < size; i++) {
            d->appendListView(pathList.at(i));
        }
    }

    d->computeItemIndex();
}



void MusicListWidgetPrivate::setTextSize(QWidget *text) {
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(18);
    text->setFont(ft);

    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    text->setPalette(pa);
}




MusicListWidgetPrivate::~MusicListWidgetPrivate(){

}

MusicListWidget::~MusicListWidget() {

}






