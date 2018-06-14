#include "mediautils.h"

MediaUtils::MediaUtils()
{

}


QString MediaUtils::changePathToName(QString &path)
{
    return path.mid(path.lastIndexOf('\\')+1);
}

QString MediaUtils::changeDirPath(QString &path)
{
    return path.left(path.lastIndexOf('\\'));
}

QString MediaUtils::getDirName(QString &path)
{
    return changePathToName(changeDirPath(path));
}

