#include "mediatoolswidget.h"
#include <QDebug>
#include <QPushButton>

class MediaToolsWidgetPrivate {
    Q_DISABLE_COPY(MediaToolsWidgetPrivate)
public:
    explicit MediaToolsWidgetPrivate(MediaToolsWidget *parent, QList<QString> titleList);
    ~MediaToolsWidgetPrivate();
private slots:
private:
    Q_DECLARE_PUBLIC(MediaToolsWidget)
    MediaToolsWidget* const q_ptr;
    void setWidgetBackground(QWidget *widget, QString path);
    void initText(QPushButton *text);
    void setBtnStyleSheet(QPushButton *text, bool isFocus);
    QList<QPushButton *> mBtnList;
    int mCurrentIndex = 0;

};


MediaToolsWidget::MediaToolsWidget(QWidget *parent, QList<QString> titleList)
    : QWidget(parent)
    , d_ptr(new MediaToolsWidgetPrivate(this, titleList))
{

}

MediaToolsWidgetPrivate::MediaToolsWidgetPrivate(MediaToolsWidget *parent, QList<QString> titleList)
    : q_ptr(parent)
{
    parent->setFixedSize(QSize(800, 50));
    setWidgetBackground(parent, ":/Res/drawable/multimedia/main_second_line.png");
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    mCurrentIndex = 0;


    int btnWidth = 144;
    int btnHeight = 50;
    int left = 0;
    QPushButton *btn = NULL;

    for (int i = 0; i < titleList.size(); i++) {
        btn = new QPushButton(parent);
        btn->setObjectName("tools_btn_"+QString::number(i+1));
        btn->setFixedSize(QSize(btnWidth, btnHeight));
        btn->setText(titleList.at(i));
        if (i == mCurrentIndex) {
            setBtnStyleSheet(btn, true);
        }else {
            setBtnStyleSheet(btn, false);
        }

        initText(btn);
        btn->setGeometry(left, 0, 0, 0);
        QObject::connect(btn, SIGNAL(clicked(bool)), parent, SLOT(onClick(bool)), type);

        left += btnWidth;
        mBtnList.append(btn);
    }
}

void MediaToolsWidget::onClick(bool checked)
{
    QPushButton *formBtn= qobject_cast<QPushButton*>(sender());
    Q_D(MediaToolsWidget);

    int size = d->mBtnList.size();
    QPushButton *toBtn = NULL;
    for (int i = 0; i < size; i++) {
        toBtn = d->mBtnList.at(i);
        if (!formBtn->objectName().compare(toBtn->objectName())) {
            setCurrentIndex(i);
            emit onItemClick(i);
            return;
        }
    }
}

void MediaToolsWidget::setCurrentIndex(int index)
{
    Q_D(MediaToolsWidget);
    if (d->mCurrentIndex == index) {
        return;
    }

    d->setBtnStyleSheet(d->mBtnList.at(d->mCurrentIndex), false);
    d->mCurrentIndex = index;
    d->setBtnStyleSheet(d->mBtnList.at(d->mCurrentIndex), true);
}

void MediaToolsWidgetPrivate::setBtnStyleSheet(QPushButton *btn, bool isFocus)
{
    if (isFocus) {
        btn->setStyleSheet(
                    "QPushButton{background-image:url(:/picture_test/media_tools_focus.png); "
                    "border: 0px groove transparent;"
                    "color: white;}"
                    "QPushButton:hover{background-color:transparent;}"
                    "QPushButton:hover{background-color:transparent;}"
                    );
    }else {
        btn->setStyleSheet(
                    "QPushButton{background-color:transparent; "
                    "color: white;}"
                    "QPushButton:hover{background-color:transparent;}"
                    "QPushButton:hover{background-color:transparent;}"
                    );
    }

}


void MediaToolsWidgetPrivate::initText(QPushButton *text) {
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(18);
    text->setFont(ft);
}


void MediaToolsWidgetPrivate::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
}

MediaToolsWidget::~MediaToolsWidget()
{

}


MediaToolsWidgetPrivate::~MediaToolsWidgetPrivate()
{

}

