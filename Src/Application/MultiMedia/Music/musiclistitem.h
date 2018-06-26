#ifndef MUSICLISTITEM_H
#define MUSICLISTITEM_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include <QListWidgetItem>
#include "Src/Application/MultiMedia/Tools/mediautils.h"


class MusicListItemPrivate;
class MusicListItem : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListItem(QWidget *parent = NULL, int type = MediaUtils::MUSIC);
    ~MusicListItem();
    void initItem(QString title, QString iconPath = "", bool isFocus = false);
    void refreshItem(bool isFocus);

    void setSize(int size);
    void setName(QString name);
    QString getPath();
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
private:
    Q_DECLARE_PRIVATE(MusicListItem)
    MusicListItemPrivate* const d_ptr;
};

#endif // MUSICLISTITEM_H
