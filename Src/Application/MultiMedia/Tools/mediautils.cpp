#include "mediautils.h"

MediaUtils::MediaUtils()
{

}

QString MediaUtils::getLastToName(QString path)
{
    return path.mid(path.lastIndexOf('\\')+1);
}

