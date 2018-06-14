#ifndef PHONERECORDWIDGET_H
#define PHONERECORDWIDGET_H

#include <QWidget>
#include "Src/Framework/Base/Core/activity.h"
#include <QListWidget>
#include <QString>
#include "phonelistwidgetitem.h"
#include <QDialog>

class PhoneRecordWidgetPrivate;
class PhoneRecordWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneRecordWidget)
public:
    explicit PhoneRecordWidget(QWidget *parent = nullptr);
    ~PhoneRecordWidget();

signals:


private:
    Q_DECLARE_PRIVATE(PhoneRecordWidget)
    PhoneRecordWidgetPrivate* const d_ptr;

};

class PhoneRecordWidgetPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneRecordWidgetPrivate)

public:
    explicit PhoneRecordWidgetPrivate(PhoneRecordWidget *parent);
    ~PhoneRecordWidgetPrivate();

    struct itemBean
    {
      //写个构造函数
      QString name;
      QString path;
    };
    void setListWidgetData(QList<itemBean> mlist,QWidget *parent);

private:
    Q_DECLARE_PUBLIC(PhoneRecordWidget)
    PhoneRecordWidget* const q_ptr;

    void initializeBasicWidget(QWidget *parent);
    void setWidgetBackground(PhoneRecordWidget *parent);
    void initToolbarText(BmpButton *text,bool isEnable);//设置按键字体和颜色
    QString getImagePath(int type);//根据电话类型 拨出 来电 未接 显示不听的图标
    void setScorllBarStye(QListWidget *listWidget);//设置ScorllBar样式
    void initDeletePhoneDialog();//初始化删除对话框

    BmpWidget *mReCordToolbarWidget;//工具栏
    BmpButton *preBtn;//上一页
    BmpButton *downloadbtn;//下载
    BmpButton *deleteAllBtn;//全部删除
    BmpButton *manualsettingBtn;//手动设置
    BmpButton *nextBtn;//下一页

    //系统背景
    BmpWidget *mBmpSystem;

    //定义ListWidget显示电话记录
    QListWidget *m_ListWidget;
    QList<phoneListwidgetItem*> mListItem;

    //标识当前选中的item位置,默认不选中
    int mSelectItemIndex = -1;
    //是否删除所有电话记录数据
    bool isDeleteAllData = false;

    //删除dialog
    QDialog *mDeleteDialog;


private slots:
    void onClickPre();
    void onClickDownLoad();
    void onClickDelete();
    void onClickSetting();
    void onClickNext();

    //item相应函数
    void onitemClick(QModelIndex index);
    void deleteBtnOnclick();

    void onDeleteDialogOkPressed();
    void onDeleteDialogNoPressed();

};

#endif // PHONERECORDWIDGET_H
