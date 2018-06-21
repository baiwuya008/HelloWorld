#ifndef MEDIADB_H
#define MEDIADB_H

#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>
#include <QFileInfo>
#include "mediadbentity.h"

class MediaDbPrivate;
class MediaDb : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MediaDb)
#define g_MediaDb (MediaDb::instance())
public:
    inline static MediaDb* instance() {
        static MediaDb* mediaDb(new MediaDb(qApp));
        return mediaDb;
    }

    void initialize();
    void deleteAll();
    void deleteData(QString filePath);
    void deleteData(int deviceType);
    void insert(int deviceType, int mediaType, QFileInfo file);
    MediaDbEntity* query(QString filePath);
    void queryAll(int deviceType);
    void updateData();


signals:

public slots:
private:
    explicit MediaDb(QObject *parent = nullptr);
    ~MediaDb();
    void initializePrivate();
    friend class MediaDbPrivate;
    QScopedPointer<MediaDbPrivate> m_Private;
};

#endif // MEDIADB_H
