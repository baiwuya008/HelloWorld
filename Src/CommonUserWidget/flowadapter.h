#ifndef FLOWADAPTER_H
#define FLOWADAPTER_H

#include <QString>
#include <QList>
#include <QObject>

class FlowAdapter : public QObject
{
    Q_OBJECT
     Q_DISABLE_COPY(FlowAdapter)
public:
    explicit FlowAdapter(QObject *parent = NULL);
    ~FlowAdapter();

    int getLeftPosition();
    int getRightPosition();
    int getCenterPosition();
    int getCount();
    bool isLastPosition();
    int getHalfMaxCount();
    int getMaxCount();
    int getTotalLength();
    void moveNext();
    void movePrev();
    void movePosition(int position);
    QString getPath(int position);

    void setSelection(int position);
    void setInfoList(QList<QString> &list);
    void notifyDataSetChanged();

signals:
    void notifyData();

private:
    void computeCenterPosition();
    int mSelectionPosition = 0;
    int mCenterPosition = 0;
    const int HALF_MAX_LENGTH = 2;//一半最大的显示数量
    int startPosition = 0;
    QList<QString> mList;

};

#endif // FLOWADAPTER_H
