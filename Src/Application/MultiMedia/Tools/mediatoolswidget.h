#ifndef MEDIATOOLSWIDGET_H
#define MEDIATOOLSWIDGET_H

#include <QWidget>
#include <QList>


class MediaToolsWidgetPrivate;
class MediaToolsWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MediaToolsWidget)
public:
    explicit MediaToolsWidget(QWidget *parent, QList<QString> titleList);
    ~MediaToolsWidget();

signals:
    void onItemClick(int index);

public slots:
    void setCurrentIndex(int index);
private slots:
    void onClick(bool checked);
private:
    Q_DECLARE_PRIVATE(MediaToolsWidget)
    MediaToolsWidgetPrivate* const d_ptr;
};

#endif // MEDIATOOLSWIDGET_H
