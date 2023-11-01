// 用来数据库操作的类

#ifndef RECORDDATABASE_H
#define RECORDDATABASE_H

#include <QtSql>

struct TranslateRecord {
    QString src_text;
    QString tar_text;
    QString timestamp;
};

class RecordDataBase
{
 public:
  RecordDataBase();
  bool OpenDatabase();
  bool InsertTranslateRecord(const QString& src,
                             const QString& tar,
                             const QString& src_text,
                             const QString& tar_text,
                             const QString& timestamp);
  QList<TranslateRecord> GetTranslateRecords();
  bool ClearTranslateRecords();
//  bool InsertItemRecord(const QString& item_uuid, const QString& item_title);
//  bool DeleteItemRecord(const QString& item_uuid);
  bool CloseDatabase();
 private:
  void InitDataBase();
 private:
  QString database_path_;
  QSqlDatabase database_;

};

#endif // RECORDDATABASE_H

