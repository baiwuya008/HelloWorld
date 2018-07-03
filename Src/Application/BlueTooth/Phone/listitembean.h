#ifndef LISTITEMBEAN_H
#define LISTITEMBEAN_H

#include <QObject>
#include <QString>

class listitemBeanPrivate;
class listitemBean : public QObject
{
    Q_OBJECT
public:
    explicit listitemBean(QObject *parent = 0);
    ~listitemBean();
    void settype(int type);
    void setPhoneName(QString phoneName);
    void setPhoneNumber(QString phoneNumber);

    int getType();
    QString getPhoneName();
    QString getPhoneNumber();

    //listitemBean(const listitemBean &other );

private:
    Q_DECLARE_PRIVATE(listitemBean)
    listitemBeanPrivate* const d_ptr;


};

class listitemBeanPrivate :public QObject
{
    Q_OBJECT

public:
    listitemBeanPrivate(listitemBean* parent);
    ~listitemBeanPrivate();

    int type;
    QString phoneName;
    QString phoneNumber;

private:
    Q_DECLARE_PUBLIC(listitemBean)
    listitemBean* const q_ptr;



};

#endif // LISTITEMBEAN_H
