#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QDebug>

class MusicListWidgetPrivate;
class MusicListWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicListWidget)
public:
    explicit MusicListWidget(QWidget *parent = nullptr);
    ~MusicListWidget();

signals:
    void selectItem(QString path, int index);

public slots:
private slots:
    void itemClick(QModelIndex index);
    void prevFile();
    void nextFile();
    void mainDir();
    void upDir();


private:
    Q_DECLARE_PRIVATE(MusicListWidget)
    MusicListWidgetPrivate* const d_ptr;
};

#endif // MUSICLISTWIDGET_H
