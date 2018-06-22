#include "multimediautils.h"

MultimediaUtils::MultimediaUtils()
{

}

QString MultimediaUtils::getLastToName(QString path)
{
    return path.mid(path.lastIndexOf('\\')+1);
}
