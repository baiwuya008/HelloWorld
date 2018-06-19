#ifndef RADIO_UNIT_H
#define RADIO_UNIT_H

#include <QVariant>
#include <QMouseEvent>
#include "Src/CommonUserWidget/CustomListView.h"

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



//----------
class RadioListView :public CustomListView
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioListView)
public:
    explicit RadioListView(QWidget* parent = NULL);
    ~RadioListView();
    void pageUpOrDown(bool pageup);
protected:
     void mouseMoveEvent(QMouseEvent* event);

};


#endif // RADIO_UNIT_H
