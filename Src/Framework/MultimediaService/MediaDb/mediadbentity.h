#ifndef MEDIADBENTITY_H
#define MEDIADBENTITY_H

#include <QString>

class MediaDbEntity
{
public:
    MediaDbEntity();
    ~MediaDbEntity();
    int deviceType;
    int mediaType;
    QString filePath;
    QString fileName;
    QString name;
    QString dirPath;
    QString dirName;
    QString suffix;
    int modifiedTime;
    int scanTime;
    QString parentPath;

};

#endif // MEDIADBENTITY_H
