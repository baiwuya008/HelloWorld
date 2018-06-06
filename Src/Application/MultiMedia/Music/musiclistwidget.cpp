#include "musiclistwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "musiclistitem.h"


class MusicListWidgetPrivate {
public:
    explicit MusicListWidgetPrivate(MusicListWidget *parent);
    ~MusicListWidgetPrivate();
private:
    Q_DECLARE_PUBLIC(MusicListWidget)
    MusicListWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
};


MusicListWidgetPrivate::MusicListWidgetPrivate(MusicListWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}


MusicListWidget::MusicListWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MusicListWidgetPrivate(this))
{
    setFixedSize(QSize(800, 435));

    QLabel *title = new QLabel(this);
    title->setFixedSize(QSize(100, 40));
    title->setText("列表");
    title->setGeometry(400, 200, 0, 0);
}


void MusicListWidgetPrivate::initializeBasicWidget(QWidget *parent) {

}

MusicListWidgetPrivate::~MusicListWidgetPrivate(){

}

MusicListWidget::~MusicListWidget() {

}
