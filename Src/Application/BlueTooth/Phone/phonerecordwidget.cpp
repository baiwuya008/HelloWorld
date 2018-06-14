#include "phonerecordwidget.h"
#include <QLabel>
#include <QString>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <QAbstractItemView>
#include <QList>
#include <QListWidgetItem>
#include <QColor>
#include <QModelIndex>
#include <QItemSelectionModel>

PhoneRecordWidgetPrivate::PhoneRecordWidgetPrivate(PhoneRecordWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}


PhoneRecordWidget::PhoneRecordWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new PhoneRecordWidgetPrivate(this))
{
    setFixedSize(QSize(800, 386));
    Q_D(PhoneRecordWidget);
    d->setWidgetBackground(this);
}

void PhoneRecordWidgetPrivate::setWidgetBackground(PhoneRecordWidget *parent){
    //设置背景图片
    parent->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = parent->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/img/Common/img_wap_bg.png").scaled(// 缩放背景图.
                parent->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    parent->setPalette(palette);                           // 给widget加上背景图

}

void PhoneRecordWidgetPrivate::initializeBasicWidget(QWidget *parent) {

    //系统背景
    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSystem->setGeometry(0,0,800,435);

    m_ListWidget = new QListWidget(mBmpSystem);
    m_ListWidget->setStyleSheet("background-color:transparent");
    m_ListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ListWidget->setFrameShape(QListWidget::NoFrame);
    m_ListWidget->setMovement(QListView::Static);
    m_ListWidget->setViewMode(QListView::IconMode);
    m_ListWidget->setFlow(QListView::LeftToRight);
    m_ListWidget->setHorizontalScrollMode(QListView::ScrollPerPixel);
    m_ListWidget->setEditTriggers(QListView::NoEditTriggers);
    m_ListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScorllBarStye(m_ListWidget);
    m_ListWidget->setGeometry(20,23,760,270);
    //绑定槽函数
    connect(m_ListWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(onitemClick(QModelIndex)));

    mReCordToolbarWidget = new BmpWidget(mBmpSystem);
    mReCordToolbarWidget->setBackgroundBmpPath(":/res/blu/phone_toolbar_bg.png");
    mReCordToolbarWidget->setGeometry(0,326,800,60);
    preBtn = new BmpButton(mReCordToolbarWidget);
    preBtn->setNormalBmpPath(":/res/blu/prephonepage_normal.png");
    preBtn->setPressBmpPath(":/res/blu/prephonepage_press.png");
    preBtn->setGeometry(0,0,159,60);
    connect(preBtn,SIGNAL(released()),this,SLOT(onClickPre()));

    downloadbtn = new BmpButton(mReCordToolbarWidget);
    downloadbtn->setText(tr("下载"));
    initToolbarText(downloadbtn,true);
    downloadbtn->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
    downloadbtn->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
    downloadbtn->setGeometry(161,0,159,60);
    connect(downloadbtn,SIGNAL(released()),this,SLOT(onClickDownLoad()));

    deleteAllBtn = new BmpButton(mReCordToolbarWidget);
    deleteAllBtn->setText(tr("全部删除"));
    initToolbarText(deleteAllBtn,false);
    deleteAllBtn->setEnabled(false);
    deleteAllBtn->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
    deleteAllBtn->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
    deleteAllBtn->setGeometry(323,0,159,60);
    connect(deleteAllBtn,SIGNAL(released()),this,SLOT(onClickDelete()));

    manualsettingBtn = new BmpButton(mReCordToolbarWidget);
    manualsettingBtn->setText(tr("手动设置"));
    initToolbarText(manualsettingBtn,true);
    manualsettingBtn->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
    manualsettingBtn->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
    manualsettingBtn->setGeometry(484,0,159,60);
    connect(manualsettingBtn,SIGNAL(released()),this,SLOT(onClickSetting()));

    nextBtn = new BmpButton(mReCordToolbarWidget);
    nextBtn->setNormalBmpPath(":/res/blu/nextphonepage_normal.png");
    nextBtn->setPressBmpPath(":/res/blu/nextphonepage_press.png");
    nextBtn->setGeometry(645,0,159,60);
    connect(nextBtn,SIGNAL(released()),this,SLOT(onClickNext()));

    initDeletePhoneDialog();

    QList<itemBean> mlist;
    for(int i=0;i<20;i++){
        itemBean bean = {QString("张三李 %1").arg(i),getImagePath(i%3)};
        mlist.append(bean);
    }
    setListWidgetData(mlist,mBmpSystem);

}

PhoneRecordWidgetPrivate::~PhoneRecordWidgetPrivate(){

}

PhoneRecordWidget::~PhoneRecordWidget() {

}

//设置list数据
void PhoneRecordWidgetPrivate::setListWidgetData(QList<itemBean> mlist,QWidget *parent)
{
    for(int i=0;i<mlist.length();i++){
        QString iconpath = mlist.at(i).path;
        QString text = mlist.at(i).name;
        phoneListwidgetItem *listItemWidget = new phoneListwidgetItem(parent);
        QListWidgetItem *m_ListWidgetItem = new QListWidgetItem;
        listItemWidget->setItemInfo(iconpath,text);
        m_ListWidgetItem->setSizeHint(QSize(750,45));
        m_ListWidget->addItem(m_ListWidgetItem);
        m_ListWidget->setItemWidget(m_ListWidgetItem,listItemWidget);
        mListItem.append(listItemWidget);
        //删除按键被点击
        connect(listItemWidget,SIGNAL(deleteBtnOnclick()),this,SLOT(deleteBtnOnclick()));
    }

    //更新删除按钮状态
    if(m_ListWidget->count() > 0){
        deleteAllBtn->setStyleSheet("color:white;");
        deleteAllBtn->setEnabled(true);
    }else{
        deleteAllBtn->setStyleSheet("color:gray;");
        deleteAllBtn->setEnabled(false);
    }

}

QString PhoneRecordWidgetPrivate::getImagePath(int type)
{
    QString path = NULL;
    switch (type) {
    case 0://拨出
        path = ":/res/blu/dialing.png";
        break;
    case 1://来电
        path = ":/res/blu/incoming.png";
        break;
    case 2://未接
        path = ":/res/blu/missed_calls.png";
        break;
    }
    return path;
}

void PhoneRecordWidgetPrivate::setScorllBarStye(QListWidget *listWidget)
{
    //设置样式，直接在函数中设置
    listWidget->verticalScrollBar()->setStyleSheet(
                //进度条背景样式
                                "QScrollBar:vertical"
                                "{"
                                "background:#383838;"
                                "width:8px;"
                                "margin:0px,0px,0px,0px;"
                                "padding-top:0px; padding-bottom:0px;"
                                "border-radius:4px;"
                                "}"

                                //进度条滑动时的背景样式
                                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                "{"
                                "background:#383838;"
                                "width:8px;"
                                "margin:0px,0px,0px,0px;"
                                "padding-top:0px; padding-bottom:0px;"
                                "border-radius:4px;"
                                "}"

                                "QScrollBar::handle:vertical" //滑动条
                                "{"
                                "background:#2997fc;"
                                "width:8px;"
                                "min-height:121;"
                                "border-radius:4px;"
                                "}"

                                "QScrollBar::handle:vertical:hover" //滑动条有焦点的时候hover
                                "{"
                                "background:#2997fc;"
                                "width:8px;"
                                "min-height:121;"
                                "border-radius:4px;"
                                "}"

                                "QScrollBar::add-line:vertical"
                                "{"
                                "height:0px;"
                                "width:0px;"
                                "subcontrol-position:bottom;"//这个是设置下箭头的
                                "}"

                                "QScrollBar::add-line:vertical:hover"
                                "{"
                                "height:0px;"
                                "width:0px;"
                                "subcontrol-position:bottom;"
                                "}"

                                "QScrollBar::sub-line:vertical"
                                "{"
                                "height:0px;"
                                "width:0px;"
                                "subcontrol-position:top;" //顶部的往上图标
                                "}"

                                "QScrollBar::sub-line:vertical:hover"
                                "{"
                                "height:0px;"
                                "width:0px;"
                                "subcontrol-position:top;"
                                "}"
                    );

}

void PhoneRecordWidgetPrivate::initDeletePhoneDialog()
{
        QPalette pl;
        pl.setColor(QPalette::WindowText,Qt::white);
        QFont font("Microsoft YaHei");
        font.setPointSize(16);

        const int DIALOG_W = 300;
        const int DIALOG_H = 180;
        mDeleteDialog = new QDialog(mBmpSystem);
        mDeleteDialog->setGeometry(250,50,DIALOG_W,DIALOG_H);
        mDeleteDialog->setStyleSheet("border-image: url(:/img/Common/img_dialog_bg.png);");
        mDeleteDialog->setWindowFlags(Qt::FramelessWindowHint);
        mDeleteDialog->hide();

        //文字
        QLabel * mLabel = new QLabel(mDeleteDialog);
        mLabel->setText(tr("是否删除？"));
        mLabel->setPalette(pl);
        mLabel->setGeometry(100,30,200,100);
        mLabel->setFont(font);

        //确定
        BmpButton * mBmpDialogOk = new BmpButton(mDeleteDialog);
        mBmpDialogOk->setNormalBmpPath(":/img/Common/img_dialog_ok_bg_a.png");
        mBmpDialogOk->setPressBmpPath(":/img/Common/img_dialog_ok_bg_b.png");
        mBmpDialogOk->setText(tr("确定"));
        //mBmpDialogOk->setFont(font);
        mBmpDialogOk->setGeometry(0,120,150,80);
        //mBmpDialogOk->setTextColor(Qt::white);
        initToolbarText(mBmpDialogOk,true);
        connect(mBmpDialogOk,SIGNAL(released()),this,SLOT(onDeleteDialogOkPressed()));

        //取消
        BmpButton * mBmpDialogNo = new BmpButton(mDeleteDialog);
        mBmpDialogNo->setNormalBmpPath(":/img/Common/img_dialog_no_bg_a.png");
        mBmpDialogNo->setPressBmpPath(":/img/Common/img_dialog_no_bg_b.png");
        mBmpDialogNo->setText(tr("取消"));
        //mBmpDialogNo->setFont(font);
        initToolbarText(mBmpDialogNo,true);
        mBmpDialogNo->setGeometry(152,120,150,80);
        connect(mBmpDialogNo,SIGNAL(released()),this,SLOT(onDeleteDialogNoPressed()));
}

void PhoneRecordWidgetPrivate::initToolbarText(BmpButton *text,bool isEnable) {
    //设置字号
    QFont ft("Microsoft YaHei");;
    ft.setPointSize(18);
    text->setFont(ft);
    //设置颜色
//    QPalette pa;
    if(isEnable){
        //pa.setColor(QPalette::WindowText,Qt::white);
        text->setStyleSheet("color:white;");
    }else{
        //pa.setColor(QPalette::WindowText,Qt::gray);
         text->setStyleSheet("color:gray;");
    }
    //text->setPalette(pa);
}


//上一页
void PhoneRecordWidgetPrivate::onClickPre()
{
    //获取视图中间显示的item的位置
    //m_listwidget->indexAt(m_listwidget->viewport()->contentsRect().center()).row();
    //获取当前显示的item的第一个位置
    int mFirstVisiblePosition = m_ListWidget->indexAt(QPoint(375,20)).row();
    qDebug() << "mFirstVisiblePosition==" << mFirstVisiblePosition << endl;
    if((mFirstVisiblePosition) > 0){
        //如果当前显示的item位置不是第一个，则表示可以翻页
        //先设置当前的焦点，在设置要翻页的位置焦点
        if(mFirstVisiblePosition < 6){
            //翻页数据item小于6
            m_ListWidget->setCurrentRow(mFirstVisiblePosition,QItemSelectionModel::Select);
            m_ListWidget->setCurrentRow(0,QItemSelectionModel::Select);
        }else{
            m_ListWidget->setCurrentRow(mFirstVisiblePosition,QItemSelectionModel::Select);
            m_ListWidget->setCurrentRow(mFirstVisiblePosition-6,QItemSelectionModel::Select);
        }
    }
}

//下载
void PhoneRecordWidgetPrivate::onClickDownLoad()
{
    qDebug() << "onClickDownLoad()" << endl;
}

//删除全部
void PhoneRecordWidgetPrivate::onClickDelete()
{
    isDeleteAllData = true;
    qDebug() << "onClickDelete()" << endl;
    mDeleteDialog->show();

}

//手动设置
void PhoneRecordWidgetPrivate::onClickSetting()
{
    qDebug() << "onClickSetting()" << endl;
}

//下一页
void PhoneRecordWidgetPrivate::onClickNext()
{
    qDebug() << "onClickNext()" << endl;  
    int mLastVisiblePosition = m_ListWidget->indexAt(QPoint(375,250)).row();
    qDebug() << "mLastVisiblePosition==" << mLastVisiblePosition << endl;
    if((mLastVisiblePosition) < m_ListWidget->count()-1){
        //如果当前显示的item位置不是最后一个，则表示可以翻页
        //先设置当前的焦点，在设置要翻页的位置焦点
        if((mLastVisiblePosition+7) > m_ListWidget->count()){
            //翻页数据最后一页
            m_ListWidget->setCurrentRow(mLastVisiblePosition-5,QItemSelectionModel::Select);
            m_ListWidget->setCurrentRow(m_ListWidget->count()-1,QItemSelectionModel::Select);
        }else{
            m_ListWidget->setCurrentRow(mLastVisiblePosition-5,QItemSelectionModel::Select);
            m_ListWidget->setCurrentRow(mLastVisiblePosition+6,QItemSelectionModel::Select);
        }
    }
}

void PhoneRecordWidgetPrivate::onitemClick(QModelIndex index)
{
    qDebug() << "index.row()==" << index.row() << endl;
    if (mSelectItemIndex == index.row()) {
            return;
    }
    if(mSelectItemIndex >= 0 && mSelectItemIndex < mListItem.size()){
           mListItem.at(mSelectItemIndex)->refreshItemBgImage(false);
    }
    mSelectItemIndex = index.row();
    mListItem.at(mSelectItemIndex)->refreshItemBgImage(true);
}

void PhoneRecordWidgetPrivate::deleteBtnOnclick()
{
    qDebug() << "deleteBtnOnclick===" << mSelectItemIndex << endl;
    qDebug() << "CurrentOnclickIndex===" << m_ListWidget->currentIndex().row() << endl;
    isDeleteAllData = false;
    mDeleteDialog->show();


}

void PhoneRecordWidgetPrivate::onDeleteDialogOkPressed()
{
       if(isDeleteAllData){
           if(m_ListWidget->count() > 0){
               m_ListWidget->clear();
               mListItem.clear();
               mSelectItemIndex = -1;//删除当前行后设置选中行为空
           }
       }else{
           if(mSelectItemIndex >= 0 && mSelectItemIndex < mListItem.size()){
                mListItem.at(mSelectItemIndex)->refreshItemBgImage(false);
           }
           int CurrentOnclickIndex = m_ListWidget->currentIndex().row();
           QListWidgetItem *item = m_ListWidget->takeItem(CurrentOnclickIndex);
           delete item;
           mListItem.removeAt(CurrentOnclickIndex);
           mSelectItemIndex = -1;//删除当前行后设置选中行为空
       }

       if(m_ListWidget->count() > 0){
           deleteAllBtn->setStyleSheet("color:white;");
           deleteAllBtn->setEnabled(true);
       }else{
           deleteAllBtn->setStyleSheet("color:gray;");
           deleteAllBtn->setEnabled(false);
       }

       mDeleteDialog->hide();
}

void PhoneRecordWidgetPrivate::onDeleteDialogNoPressed()
{
       mDeleteDialog->hide();
}

