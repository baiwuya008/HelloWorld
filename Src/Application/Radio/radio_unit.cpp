#include "radio_unit.h"
#include <QScrollBar>

#define RADIO_PAGE_HIGHT 250

RadioUnit::RadioUnit()
{

}


//----------------
PresetVariant::PresetVariant()
{
  m_SaveIconSta = B_Normal;
  m_RemoveIconSta = B_Normal;
  m_ActiveIcon = RemoveIcon;
  mFrequency = 0; //not set use for check release the list item
}

PresetVariant::~PresetVariant()
{

}

//-----------------
ListVariant::ListVariant()
{
  mFrequency = 0; //not set use for check release the list item
}

ListVariant::~ListVariant()
{

}


//------------------
RadioListView::RadioListView(QWidget* parent)
    :CustomListView(parent)
{

}

RadioListView::~RadioListView()
{

}

void RadioListView::mouseMoveEvent(QMouseEvent* event){
    //Do Nothing here
}

void RadioListView::pageUpOrDown(bool pageup){
    if(pageup){
        //page up
         verticalScrollBar()->setValue(verticalOffset() - RADIO_PAGE_HIGHT);
    }else{
        //page down
         verticalScrollBar()->setValue(verticalOffset() + RADIO_PAGE_HIGHT);
    }
}
//------------------
