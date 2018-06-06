#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>


class MusicListWidgetPrivate;
class MusicListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListWidget(QWidget *parent = nullptr);
    ~MusicListWidget();

signals:

public slots:
private:
    Q_DECLARE_PRIVATE(MusicListWidget)
    MusicListWidgetPrivate* const d_ptr;
};

#endif // MUSICLISTWIDGET_H
