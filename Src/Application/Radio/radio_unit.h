#ifndef RADIO_UNIT_H
#define RADIO_UNIT_H

#include <QVariant>

class RadioUnit
{
public:
    RadioUnit();
};

//-------------
class PresetVariant
{
public:
    enum BtnStatus {
        B_Normal = 0,
        B_Press = 1,
    };
    enum BtnIcon {
        SaveIcon = 0,
        RemoveIcon = 1,
    };
    PresetVariant();
    ~PresetVariant();
    double mFrequency;
    PresetVariant::BtnStatus m_SaveIconSta;
    PresetVariant::BtnStatus m_RemoveIconSta;
    PresetVariant::BtnIcon m_ActiveIcon;
};

Q_DECLARE_METATYPE(PresetVariant)
//--------------
class ListVariant
{
public:
    ListVariant();
    ~ListVariant();
    double mFrequency;
};
Q_DECLARE_METATYPE(ListVariant)


#endif // RADIO_UNIT_H
