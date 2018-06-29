#ifndef MUSICLISTWIDGET_H
#define MUSICLISTWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QDebug>
#include "Src/Application/MultiMedia/Tools/mediautils.h"

class MusicListWidgetPrivate;
class MusicListWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicListWidget)
public:
    explicit MusicListWidget(QWidget *parent, int type = MediaUtils::MUSIC_LIST);
    ~MusicListWidget();
    void refreshItem(int index);
    void setPlayNext(bool isNext);
    void updateList(int deviceType, int queryMode, QString &dirPath, QStringList &pathList);
    void showAllList();

signals:
    void selectItem(int deviceType, QString path);
    void queryFiles(int deviceType, int mediaType, int queryMode, QString dirPath);

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
