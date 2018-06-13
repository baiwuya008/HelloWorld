#ifndef OMessage_H
#define OMessage_H
#include<qlabel.h>
#include "apptype.h"




class OMessage
{
    Q_DISABLE_COPY(OMessage)
public:
    explicit OMessage();

    AppType mToWhom;
    int mId;
    int mParam1;
    int mParam2;
    QObject mWhat;

};

#endif // OMessage_H
