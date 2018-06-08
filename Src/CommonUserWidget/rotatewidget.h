#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QTimer>
#include <QResizeEvent>
#include <QList>

class RotateWidgetPrivate;
class RotateWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(RotateWidget)
public:
    explicit RotateWidget(QWidget *parent = nullptr);
    ~RotateWidget();

protected:
   void paintEvent(QPaintEvent *event);
   void resizeEvent(QResizeEvent *event);

signals:

public slots:
   void init(QList<QString> list);
   void init(QString path);
   void start(QString path);
   void start();
   void stop();
   void setAniTime(int time);
private slots:
   void onTimeout();
private:
   Q_DECLARE_PRIVATE(RotateWidget)
   RotateWidgetPrivate* const d_ptr;



};

#endif // ROTATEWIDGET_H
