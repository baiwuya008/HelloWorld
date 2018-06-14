#include "customwidget.h"

#include <QPainter>
#include <QFile>
#include <QScopedPointer>

class CustomWidgetPrivate
{
    Q_DISABLE_COPY(CustomWidgetPrivate)
public:
    explicit CustomWidgetPrivate(CustomWidget* parent);
    ~CustomWidgetPrivate();
    QScopedPointer<QPixmap> m_BackgroundPixmap;
private:
    CustomWidget* m_Parent;
};

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new CustomWidgetPrivate(this))
{
}

CustomWidget::~CustomWidget()
{
}

void CustomWidget::setBackgroundBmpPath(const QString &path)
{
    if (QFile::exists(path)) {
        m_Private->m_BackgroundPixmap.reset(new QPixmap(path));
        if (isVisible()) {
            update();
        }
    }
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!m_Private->m_BackgroundPixmap.isNull()) {
        int x = (width() - m_Private->m_BackgroundPixmap->width()) >> 1;
        int y = (height() - m_Private->m_BackgroundPixmap->height()) >> 1;
        painter.drawPixmap(x, y, *m_Private->m_BackgroundPixmap);
    }
    QWidget::paintEvent(event);
}

CustomWidgetPrivate::CustomWidgetPrivate(CustomWidget *parent)
    : m_Parent(parent)
{
}

CustomWidgetPrivate::~CustomWidgetPrivate()
{
}
