#include "mediautils.h"


MediaUtils::MediaUtils()
{

}

void MediaUtils::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
}


void MediaUtils::setLabText(QWidget *text, int size)
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

bool MediaUtils::isDirPath(QString path)
{
    if (path.length() < 1) {
        return false;
    }
    QFileInfo file(path);
    if (file.exists() && file.isDir()) {
        return true;
    }

    return false;
}

