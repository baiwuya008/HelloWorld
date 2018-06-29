#ifndef IMAGEPLAYER_H
#define IMAGEPLAYER_H

#include <QObject>
#include "Src/Framework/MultimediaService/multimediautils.h"


class ImagePlayerPrivate;
class ImagePlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ImagePlayer)
public:
    explicit ImagePlayer(QObject *parent = NULL);
    ~ImagePlayer();
    QStringList* getPathList(int deviceType);
    void clearPathList(int deviceType);
    QString getPlayPath(int deviceType, int index);
    void setDeviceType(int deviceType);
    int getScanStatus();
    void setScanStatus(int status);
    void startPlay(int deviceType, QString path);

signals:
protected slots:
    void scanImageFilePath(int deviceType, const QString &filePath);
public slots:
private:
    friend class ImagePlayerPrivate;
    QScopedPointer<ImagePlayerPrivate> m_Private;
};

#endif // IMAGEPLAYER_H
