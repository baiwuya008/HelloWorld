#include "phoneoptionswidget.h"
#include <QPalette>
#include <QBrush>
#include <QSize>
#include <QDebug>
#include <QFont>

PhoneOptionsWidget::PhoneOptionsWidget(QWidget *parent)
  : QWidget(parent) , d_ptr(new PhoneOptionsWidgetPrivate(this))
{
  //setFixedSize(QSize(800, 386));
  //Q_D(PhoneOptionsWidget);
  //d->setWidgetBackground(this);

}

PhoneOptionsWidget::~PhoneOptionsWidget()
{

}

PhoneOptionsWidgetPrivate::PhoneOptionsWidgetPrivate(PhoneOptionsWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
    initDeletePhoneDialog();
    initWidgetItemData();
}

PhoneOptionsWidgetPrivate::~PhoneOptionsWidgetPrivate()
{

}

void PhoneOptionsWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(13);
    //设置白颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    //系统背景
    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSystem->setGeometry(0,0,800,435);

    btSwitchLabel = new QLabel(mBmpSystem);
    btSwitchLabel->setFont(ft);
    btSwitchLabel->setPalette(pa);
    btSwitchLabel->setText("蓝牙/开");
    btSwitchLabel->setGeometry(150,30,150,44);

    btSwitchBtn = new BmpButton(mBmpSystem);
    btSwitchBtn->setNormalBmpPath(":/res/blu/bt_on.png");
    btSwitchBtn->setGeometry(590,41,49,22);

    line01 = new QLabel(mBmpSystem);
    line01->setPixmap(getPixmap(":/res/blu/phone_itemlin.png"));
    line01->setGeometry(80,74,639,2);

    pairTitleName = new QLabel(mBmpSystem);
    pairTitleName->setFont(ft);
    pairTitleName->setPalette(pa);
    pairTitleName->setText(tr("已配对的设备"));
    pairTitleName->setGeometry(150,76,150,46);

    line02 = new QLabel(mBmpSystem);
    line02->setPixmap(getPixmap(":/res/blu/phone_itemlin.png"));
    line02->setGeometry(80, 120, 639, 2);

    for(int i=0;i<5;i++){
        PhoneOptionWidgetItem *item = new PhoneOptionWidgetItem(mBmpSystem);
        switch (i) {
        case 0:
            item->setGeometry(5,122,750,46);
            break;
        case 1:
            item->setGeometry(5,168,750,46);
            break;
        case 2:
            item->setGeometry(5,214,750,46);
            break;
        case 3:
            item->setGeometry(5,260,750,46);
            break;
        case 4:
            item->setGeometry(5,306,750,46);
            break;
        }
        //item->refreshItemVisible(false);
        item->setWidgetIndex(i);
        mListPhonePairItem.append(item);
        connect(item,SIGNAL(deleteBtnOnclick()),this,SLOT(deleteBtnOnclick()));
        connect(item,SIGNAL(operationBtnOnClick()),this,SLOT(operationBtnOnclick()));
        connect(item,SIGNAL(widgetOnClick(int)),this,SLOT(widgetOnClick(int)));
    }
}

void PhoneOptionsWidgetPrivate::setWidgetBackground(PhoneOptionsWidget *parent)
{
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

//初始化dialog
void PhoneOptionsWidgetPrivate::initDeletePhoneDialog()
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
        mBmpDialogOk->setGeometry(0,120,150,80);
        mBmpDialogOk->setFont(font);
        mBmpDialogOk->setStyleSheet("color:white;");
        connect(mBmpDialogOk,SIGNAL(released()),this,SLOT(onDeleteDialogOkPressed()));

        //取消
        BmpButton * mBmpDialogNo = new BmpButton(mDeleteDialog);
        mBmpDialogNo->setNormalBmpPath(":/img/Common/img_dialog_no_bg_a.png");
        mBmpDialogNo->setPressBmpPath(":/img/Common/img_dialog_no_bg_b.png");
        mBmpDialogNo->setText(tr("取消"));
        mBmpDialogNo->setFont(font);
        mBmpDialogNo->setStyleSheet("color:white;");
        mBmpDialogNo->setGeometry(152,120,150,80);
        connect(mBmpDialogNo,SIGNAL(released()),this,SLOT(onDeleteDialogNoPressed()));
}

//初始item化数据
void PhoneOptionsWidgetPrivate::initWidgetItemData()
{

    mPhonePairListData << "xiaomi951" << "xiaomi952" << "xiaomi953" << "xiaomi954" << "xiaomi951" ;
    for(int i = 0; i < mListPhonePairItem.size(); i++){
        int dataCount = mPhonePairListData.size();//获取目前的数据个数
        if(i < dataCount){
           //更新数据
           mListPhonePairItem.at(i)->setItemInfo(mPhonePairListData.at(i),false);
           mListPhonePairItem.at(i)->refreshItemVisible(true);
        }else{
            //超过数据的item设置不可见
            mListPhonePairItem.at(i)->refreshItemVisible(false);
        }
    }
}

//获取item蓝牙连接状态
void PhoneOptionsWidgetPrivate::initBtConnectStatus()
{

}


//删除配对的蓝牙设备
void PhoneOptionsWidgetPrivate::deleteBtnOnclick()
{
    qDebug() << "deleteBtnOnclick" ;
    mDeleteDialog->show();
}

//连接、断开蓝牙设备
void PhoneOptionsWidgetPrivate::operationBtnOnclick()
{

}

void PhoneOptionsWidgetPrivate::widgetOnClick(int index)
{
    if(onClickWidgetIndex == index){
        //如果已经选中，就直接返回
        return ;
    }else{
        onClickWidgetIndex = index;
    }

    for(int i= 0; i < mListPhonePairItem.size(); i++){
        //获取item的位置
        int itemIndex = mListPhonePairItem.at(i)->getWidgetIndex();
        if(itemIndex == index){//点击的item和当前的item是同一个
            mListPhonePairItem.at(i)->refreshItemBgImage(true);
        }else{
            mListPhonePairItem.at(i)->refreshItemBgImage(false);
        }

    }
}

//dialog 删除事件
void PhoneOptionsWidgetPrivate::onDeleteDialogOkPressed()
{
     qDebug() << "onClickWidgetIndex" << onClickWidgetIndex;
     mPhonePairListData.removeAt(onClickWidgetIndex);//先删除数据
     for(int j=0;j<mPhonePairListData.size();j++){
         qDebug() << "data==" << mPhonePairListData.at(j);
     }
     int dataCount = mPhonePairListData.size();//获取目前的数据个数
      qDebug() << "dataCount==" << dataCount;


     for(int i = onClickWidgetIndex; i < mListPhonePairItem.size(); i++){
         if(i < dataCount){
            //更新数据
            mListPhonePairItem.at(i)->setItemInfo(mPhonePairListData.at(i),false);
         }else{
             //超过数据的item设置不可见
             mListPhonePairItem.at(i)->refreshItemVisible(false);
         }
     }
     onClickWidgetIndex = -1;//删除后默认不选中
     mDeleteDialog->hide();
}

void PhoneOptionsWidgetPrivate::onDeleteDialogNoPressed()
{
    mDeleteDialog->hide();
}



