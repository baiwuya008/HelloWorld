#include "multimediautils.h"


MultimediaUtils::MultimediaUtils()
{

}

QString MultimediaUtils::getLastToName(QString path)
{
    return path.mid(path.lastIndexOf('/')+1);
}


QString MultimediaUtils::changeWindowsPath(QString filePath)
{
    QStringList list = filePath.split("/");
    QString path;
    int size = list.size();
    for (int i = 0; i < size; i++) {
        if (i == size-1) {
            path.append(list.at(i));
        }else {
            path.append(list.at(i)+"\\");
        }
    }

    return path;
}
