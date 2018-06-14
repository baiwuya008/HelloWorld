#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

class CustomWidgetPrivate;
class CustomWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CustomWidget)
public:
    explicit CustomWidget(QWidget *parent = NULL);
    ~CustomWidget();
    void setBackgroundBmpPath(const QString &path);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QScopedPointer<CustomWidgetPrivate> m_Private;
};

#endif // CUSTOMWIDGET_H
