#ifndef BMPWIDGET_H
#define BMPWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include <QMouseEvent>

class BmpWidgetPrivate;
class BmpWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(BmpWidget)
public:
    explicit BmpWidget(QWidget *parent = NULL);
    ~BmpWidget();
    void setBackgroundBmpPath(const QString &path);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void mouseMove(QMouseEvent*e);
    void mousePress(QMouseEvent*e);
    void mouseRelease(QMouseEvent*e);

private:
    QScopedPointer<BmpWidgetPrivate> m_Private;
};

#endif // BMPWIDGET_H
