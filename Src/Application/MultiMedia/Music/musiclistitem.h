#ifndef MUSICLISTITEM_H
#define MUSICLISTITEM_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>


class MusicListItemPrivate;
class MusicListItem : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListItem(QWidget *parent = nullptr);
    ~MusicListItem();
    void setItemInfo(QString iconPath, QString title);
    void setItemInfo(QString iconPath, QString title, QString linePath);
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
private:
    Q_DECLARE_PRIVATE(MusicListItem)
    MusicListItemPrivate* const d_ptr;
};

#endif // MUSICLISTITEM_H
