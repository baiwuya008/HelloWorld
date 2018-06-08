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
  mFrequency = 87.5;
}

PresetVariant::~PresetVariant()
{

}

//-----------------
ListVariant::ListVariant()
{

}

ListVariant::~ListVariant()
{
  mFrequency = 87.5;
}
