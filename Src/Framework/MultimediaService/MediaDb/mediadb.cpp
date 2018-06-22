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
    void initialize();
    QSqlDatabase db;
private:
    MediaDb* m_Parent;

    void createDb();
    void createTable();
    void connectAllSlots();
    void close();
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
    qDebug() << "MediaDbPrivate::createTable prepare result = "<< result;
    result = query.exec();
    if (!result) {
        qDebug() << "MediaDbPrivate::createTable lastError = " << query.lastError();
    }
}


void MediaDb::initialize()
{
    m_Private->initialize();
}

void MediaDb::deleteAll()
{
    QSqlQuery query(m_Private->db);
    query.exec("delete from scan_files_table");
}

void MediaDb::deleteData(int deviceType)
{
    QSqlQuery query(m_Private->db);
    query.exec("delete from scan_files_table where deviceType = "+QString::number(deviceType));
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
    query.addBindValue(QDateTime::currentMSecsSinceEpoch()/1000);
    query.exec();
}

MediaDbEntity* MediaDb::query(QString filePath) {
    QSqlQuery query(m_Private->db);
    //    QString select = "SELECT * FROM scan_files_table where filePath = "+filePath;
    QString select = "SELECT * FROM scan_files_table where fileName = '" + filePath + "'";

    MediaDbEntity *entity = NULL;
    if (query.exec(select)) {
        while (query.next()) {
            entity = new MediaDbEntity();
            entity->id = query.value(0).toInt();
            entity->deviceType = query.value(1).toInt();
            entity->mediaType = query.value(2).toInt();
            entity->filePath = query.value(3).toString();
            entity->fileName = query.value(4).toString();
            entity->name = query.value(5).toString();
            entity->dirPath = query.value(6).toString();
            entity->dirName = query.value(7).toString();
            entity->suffix = query.value(8).toString();
            entity->modifiedTime = query.value(9).toInt();
            entity->scanTime = query.value(10).toInt();
            break;
        }
    }else {
        qDebug() << "MediaDb::queryData lastError = " << query.lastError();
    }

    //    query.clear();
    //    query.finish();
    return entity;
}

void MediaDb::queryAll(int deviceType) {
    QSqlQuery query(m_Private->db);
    QString select = "SELECT * FROM scan_files_table where deviceType = " + QString::number(deviceType);
    if (query.exec(select)) {
        int nameIndex = query.record().indexOf("name");
        while (query.next()) {
            QString name = query.value(nameIndex).toString();
            int id = query.value(0).toInt();
            qDebug() << "queryAll name = " << name << "; id = " << id;
        }
    }else {
        qDebug() << "queryAll lastError = " << query.lastError();
    }
}

void MediaDb::updateData() {
    QSqlQuery query(m_Private->db);
    QString update = "UPDATE scan_files_table set name = :name where id = :id";
    query.prepare(update);
    query.bindValue(":name", "xiaoli_haollo");
    query.bindValue(":id", 11);
    bool result = query.exec();
    qDebug() << "updateData result = "<< result;
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


void MediaDbPrivate::close() {
    db.close();
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
}

MediaDbPrivate::~MediaDbPrivate()
{
    close();
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
        connectAllSlots();
    }else {
        qDebug() << "DatabaseTest lastError result = " << db.lastError();
    }
}



void MediaDbPrivate::connectAllSlots()
{

}
