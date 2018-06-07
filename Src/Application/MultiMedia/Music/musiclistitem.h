#ifndef MUSICLISTITEM_H
#define MUSICLISTITEM_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include <QListWidgetItem>


class MusicListItemPrivate;
class MusicListItem : public QWidget
{
    Q_OBJECT
public:
    explicit MusicListItem(QWidget *parent = nullptr);
    ~MusicListItem();
    void setItemInfo(QString iconPath, QString title);
    void setItemInfo(QString iconPath, QString title, QString linePath);
    void setItemFile(QString iconPath, QString linePath, QString filePath);
    void refreshItemFile(bool isFocus);

    void setSize(int size);
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
