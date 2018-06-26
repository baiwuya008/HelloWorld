#include "mediautils.h"
#include <QFileInfo>

MediaUtils::MediaUtils()
{

}

QString MediaUtils::getLastToName(QString path)
{
    return path.mid(path.lastIndexOf('/')+1);
}

QString MediaUtils::getUpperPath(QString path)
{
    return path.left(path.lastIndexOf('/'));
}

bool MediaUtils::isDirPath(QString path)
{
    if (path.length() < 1) {
        return false;
    }
    QFileInfo file(path);
    if (file.exists() && file.isDir()) {
        return true;
    }

    return false;
}


