#ifndef MUSICPLAYWIDGET_H
#define MUSICPLAYWIDGET_H

#include <QWidget>


class MusicPlayWidgetPrivate;
class MusicPlayWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicPlayWidget)
public:
    explicit MusicPlayWidget(QWidget *parent = nullptr);
    ~MusicPlayWidget();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private slots:
 void onSwitchPlayMode(int mode);
 void onSwitchIndex(bool isNext);
 void onSwitchStatus(bool isPlay);
private:
    Q_DECLARE_PRIVATE(MusicPlayWidget)
    MusicPlayWidgetPrivate* const d_ptr;
};

#endif // MUSICPLAYWIDGET_H
