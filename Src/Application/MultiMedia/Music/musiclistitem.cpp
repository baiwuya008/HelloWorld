#include "musiclistitem.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>


class MusicListItemPrivate {
public:
    explicit MusicListItemPrivate(MusicListItem *parent, int type);
    ~MusicListItemPrivate();
private:
    Q_DECLARE_PUBLIC(MusicListItem)
    MusicListItem* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initLabText(QLabel *text, int size);
    void initItemView(QString title, QString iconPath = "", bool isFocus = false);
    void refreshItemView(bool isFocus);
    void setFilePath(QString path);
    void setNameFocus(bool isFocus);
    void setIconFocus(bool isFocus);


    inline QPixmap getPixmap(QString path) {
        QImage image;
        image.load(path);
        return QPixmap::fromImage(image);
    }

    inline QPixmap getPixmap(QString path, int width, int height) {
        QImage image;
        image.load(path);
        QImage reulst = image.scaled(QSize(width, height)
                                     , Qt::KeepAspectRatio,Qt::SmoothTransformation);
        return QPixmap::fromImage(reulst);
    }

    int mWidth = 0;
    int mHeight = 0;
    QString mFilePath;
    QString mFileName;
    int mMediaType;

    QVBoxLayout *mainLayout = NULL;
    QHBoxLayout *infoLayout = NULL;
    QLabel *icon = NULL;
    QLabel *name = NULL;
    QLabel *line = NULL;

};

MusicListItem::MusicListItem(QWidget *parent, int type)
    : QWidget(parent)
    , d_ptr(new MusicListItemPrivate(this, type))
{

}


MusicListItemPrivate::MusicListItemPrivate(MusicListItem *parent, int type)
    : q_ptr(parent)
{
    this->mMediaType = type;
    initializeBasicWidget(parent);
}


void MusicListItem::setSize(int size)
{
    Q_D(MusicListItem);
    d->initLabText(d->name, size);
}

void MusicListItem::setName(QString name)
{
    Q_D(MusicListItem);
    d->name->setText(name);
}


void MusicListItemPrivate::initializeBasicWidget(QWidget *parent) {
    mainLayout = new QVBoxLayout();
    parent->setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);


    infoLayout = new QHBoxLayout();
    infoLayout->setContentsMargins(0, 0, 0, 0);
    icon = new QLabel(parent);
    name = new QLabel(parent);
    name->setContentsMargins(5, 0, 0, 0);

    infoLayout->addWidget(icon, 0, Qt::AlignVCenter);
    infoLayout->addWidget(name,  0, Qt::AlignVCenter);
    infoLayout->addStretch();

    line = new QLabel();
    line->setContentsMargins(0, 0, 0, 0);

    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(line);
    mainLayout->addStretch();



    if (mMediaType == MediaUtils::MUSIC) {
        initLabText(name, 15);
        line->setVisible(false);
    }else {
        infoLayout->setContentsMargins(51, 0, 0, 0);
        initLabText(name, 18);
        line->setPixmap(getPixmap(":/Res/drawable/multimedia/music_line.png"));
    }
}

void MusicListItemPrivate::initItemView(QString title, QString iconPath, bool isFocus)
{
    switch (mMediaType) {
    case MediaUtils::MUSIC_LIST:
    case MediaUtils::VIDEO_LIST:
    case MediaUtils::DIR_LIST:
        setFilePath(title);
        name->setText(mFileName);
        setIconFocus(isFocus);
        setNameFocus(isFocus);
        break;
    case MediaUtils::MUSIC:
        name->setText(title);
        icon->setPixmap(getPixmap(iconPath));
        break;
    }
}

void MusicListItemPrivate::setFilePath(QString path)
{
    this->mFilePath = path;
    this->mFileName = MediaUtils::getLastToName(path);
}

void MusicListItemPrivate::setIconFocus(bool isFocus)
{
    if (MediaUtils::MUSIC_LIST == mMediaType) {
        if (isFocus) {
            icon->setPixmap(getPixmap(":/Res/drawable/multimedia/music_list_music_icon_focus.png"));
        }else {
            icon->setPixmap(getPixmap(":/Res/drawable/multimedia/music_list_music_icon_normal.png"));
        }
    }else if (MediaUtils::VIDEO_LIST == mMediaType) {
        if (isFocus) {
            icon->setPixmap(getPixmap(":/Res/drawable/multimedia/music_list_video_icon_focus.png"));
        }else {
            icon->setPixmap(getPixmap(":/Res/drawable/multimedia/music_list_video_icon_normal.png"));
        }
    }else if (MediaUtils::DIR_LIST == mMediaType) {
        icon->setPixmap(getPixmap(":/Res/drawable/multimedia/music_file_icon.png"));
    }
}

void MusicListItemPrivate::refreshItemView(bool isFocus)
{
    setIconFocus(isFocus);
    setNameFocus(isFocus);
}

void MusicListItemPrivate::setNameFocus(bool isFocus)
{
    if (isFocus) {
        name->setStyleSheet("color:#03d396;");
    }else {
        name->setStyleSheet("color:white;");
    }
}



QString MusicListItem::getPath()
{
    Q_D(MusicListItem);
    return d->mFilePath;
}

void MusicListItemPrivate::initLabText(QLabel *text, int size)
{
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(size);
    text->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    text->setPalette(pa);
}

void MusicListItem::resizeEvent(QResizeEvent *event) {
    Q_D(MusicListItem);
    d->mWidth = event->size().width();
    d->mHeight = event->size().height();
}

void MusicListItem::initItem(QString title, QString iconPath, bool isFocus)
{
    Q_D(MusicListItem);
    d->initItemView(title, iconPath, isFocus);
}

void MusicListItem::refreshItem(bool isFocus)
{
    Q_D(MusicListItem);
    d->refreshItemView(isFocus);
}

MusicListItem::~MusicListItem() {
    if (d_ptr != NULL) {
        d_ptr->~MusicListItemPrivate();
    }
}

MusicListItemPrivate::~MusicListItemPrivate() {
    if (icon != NULL) {
        delete icon;
        icon = NULL;
    }

    if (name != NULL) {
        delete name;
        name = NULL;
    }

    if (line != NULL) {
        delete line;
        line = NULL;
    }

    if (infoLayout != NULL) {
        delete infoLayout;
        infoLayout = NULL;
    }

    if (mainLayout != NULL) {
        delete mainLayout;
        mainLayout = NULL;
    }

    mFilePath = "";
    mFileName = "";
}
