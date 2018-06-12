#include "radio_unit.h"

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
