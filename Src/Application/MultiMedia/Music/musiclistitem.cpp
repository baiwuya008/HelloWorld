#include "musiclistitem.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MusicListItemPrivate {
public:
    explicit MusicListItemPrivate(MusicListItem *parent);
    ~MusicListItemPrivate();
private:
    Q_DECLARE_PUBLIC(MusicListItem)
    MusicListItem* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initLabText(QLabel *text);
    void initLabText(QLabel *text, int size);
    void refreshItemView(QString iconPath, QString title, QString linePath);
    void initFileItem(QString iconPath, QString linePath, QString filePath);
    void refreshFileItem(bool isFocus);

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

    QVBoxLayout *mainLayout = NULL;
    QHBoxLayout *infoLayout = NULL;
    QLabel *icon = NULL;
    QLabel *name = NULL;
    QLabel *line = NULL;

};

MusicListItem::MusicListItem(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MusicListItemPrivate(this))
{

}


MusicListItemPrivate::MusicListItemPrivate(MusicListItem *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}

void MusicListItem::setItemInfo(QString iconPath, QString title) {
    setItemInfo(iconPath, title, "");
}

void MusicListItem::setItemInfo(QString iconPath, QString title, QString linePath) {
    Q_D(MusicListItem);
    d->refreshItemView(iconPath, title, linePath);
}

void MusicListItem::setItemFile(QString iconPath, QString linePath, QString filePath)
{
    Q_D(MusicListItem);
    d->initFileItem(iconPath, linePath, filePath);
}

void MusicListItem::setSize(int size)
{
    Q_D(MusicListItem);
    d->initLabText(d->name, size);
}




void MusicListItemPrivate::refreshItemView(QString iconPath, QString title, QString linePath) {
    icon->setPixmap(getPixmap(iconPath));
    name->setText(title);
    if (linePath.size() > 1) {
        line->setPixmap(getPixmap(linePath));
        line->setVisible(true);
    }else {
        line->setVisible(false);
    }
}



void MusicListItemPrivate::initializeBasicWidget(QWidget *parent) {
    mainLayout = new QVBoxLayout;
    parent->setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);


    infoLayout = new QHBoxLayout;
    infoLayout->setContentsMargins(0, 0, 0, 0);
    icon = new QLabel(parent);
    name = new QLabel(parent);
    name->setContentsMargins(5, 0, 0, 0);
    initLabText(name);
    infoLayout->addWidget(icon, 0, Qt::AlignVCenter);
    infoLayout->addWidget(name,  0, Qt::AlignVCenter);
    infoLayout->addStretch();

    line = new QLabel;
    line->setContentsMargins(0, 0, 0, 0);

    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(line);
    mainLayout->addStretch();
}

void MusicListItem::refreshItemFile(bool isFocus)
{
    Q_D(MusicListItem);
    d->refreshFileItem(isFocus);
}

QString MusicListItem::getPath()
{
    Q_D(MusicListItem);
    return d->mFilePath;
}

void MusicListItemPrivate::initFileItem(QString iconPath, QString linePath, QString filePath)
{
    this->mFilePath = filePath;
    this->mFileName = filePath;

    refreshItemView(iconPath, mFileName, linePath);
    initLabText(name, 18);
    refreshFileItem(false);
    infoLayout->setContentsMargins(51, 0, 0, 0);
}

void MusicListItemPrivate::refreshFileItem(bool isFocus)
{
    if (isFocus) {
        name->setStyleSheet("color:#03d396;");
    }else {
        name->setStyleSheet("color:white;");
    }
}


void MusicListItemPrivate::initLabText(QLabel *text) {
    initLabText(text, 15);
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

MusicListItem::~MusicListItem() {

}

MusicListItemPrivate::~MusicListItemPrivate() {

}
