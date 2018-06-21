#include "mediadb.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QDir>


class MediaDbPrivate {
    Q_DISABLE_COPY(MediaDbPrivate)
public:
    explicit MediaDbPrivate(MediaDb* parent);
    ~MediaDbPrivate();
    QSqlDatabase db;
private:
    MediaDb* m_Parent;
    void initialize();
    void createDb();
    void createTable();
    void connectAllSlots();
    const QString SQL_CONNECTION_NAME = "okl_media_default_connection";

};


void MediaDbPrivate::createTable()
{
    QSqlQuery query(db);
    QString table_sql = "create table if not exists scan_files_table "
                        "(id int primary key, deviceType int, mediaType int, filePath text not null unique,"
                        " fileName varchar(20), name varchar(20), dirPath text not null,"
                        " dirName varchar(20), suffix varchar(6), modifiedTime int,"
                        " scanTime int)";
    bool result = query.prepare(table_sql);
    qDebug() << "createTable prepare result = "<< result;
    result = query.exec();
    if (!result) {
        qDebug() << "lastError = " << query.lastError();
    }
}


void MediaDb::deleteAll()
{
    QSqlQuery query(m_Private->db);
    bool result = query.exec("delete from scan_files_table");
    qDebug() << "deleteAll result = "<< result;
}

void MediaDb::deleteData(int deviceType)
{
    QSqlQuery query(m_Private->db);
    bool result = query.exec("delete from scan_files_table where deviceType = "+QString::number(deviceType));
    qDebug() << "deleteData 222 result = "<< result;
}

void MediaDb::insert(int deviceType, int mediaType, QFileInfo file)
{
    QSqlQuery query(m_Private->db);
    query.prepare("INSERT INTO scan_files_table (deviceType, mediaType, filePath, fileName, "
                  "name, dirPath, dirName, suffix, modifiedTime, scanTime) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    query.addBindValue(deviceType);
    query.addBindValue(mediaType);
    query.addBindValue(file.absoluteFilePath());
    query.addBindValue(file.fileName());
    query.addBindValue(file.baseName());
    query.addBindValue(file.dir().absolutePath());
    query.addBindValue(file.dir().dirName());
    query.addBindValue(file.suffix());
    query.addBindValue(file.lastModified().toTime_t());
    query.addBindValue(QDateTime::currentSecsSinceEpoch());
    query.exec();
}

void MediaDb::deleteData(QString filePath)
{
    QSqlQuery query(m_Private->db);
    bool result = query.exec("delete from scan_files_table where filePath = "+filePath);
    qDebug() << "deleteData 111 result = "<< result;
}

MediaDb::MediaDb(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    initializePrivate();
}

MediaDb::~MediaDb()
{

}

void MediaDb::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new MediaDbPrivate(this));
    }
}

MediaDbPrivate::MediaDbPrivate(MediaDb *parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MediaDbPrivate::~MediaDbPrivate()
{

}

void MediaDbPrivate::initialize()
{
    createDb();
}

void MediaDbPrivate::createDb()
{
    if (QSqlDatabase::contains(SQL_CONNECTION_NAME)) {
        db = QSqlDatabase::database(SQL_CONNECTION_NAME);
        qDebug() << "MediaDbPrivate is already create---";
    }else {
        qDebug() << "MediaDbPrivate init create---";
        //QSQLITE这个driver必须是QT所支持的，不能是自定义，不然会报错
        //后面的connection可以不用，若不用就是系统默认的。
        QString driver = "QSQLITE";//是连接数据库的驱动名称，QT自带的名称
        db = QSqlDatabase::addDatabase(driver, SQL_CONNECTION_NAME);
        db.setDatabaseName("okl_media_database.db");
        db.setHostName("okl_media");
        db.setUserName("okl_media_user");
        db.setPassword("123456");
    }

    bool result = db.open();
    if (result) {
        createTable();
    }else {
        qDebug() << "DatabaseTest lastError result = " << db.lastError();
    }
}



void MediaDbPrivate::connectAllSlots()
{

}
