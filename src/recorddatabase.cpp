#include "recorddatabase.h"

#include <QMessageBox>

RecordDataBase::RecordDataBase() { InitDataBase(); }

void RecordDataBase::InitDataBase() {
  database_ = QSqlDatabase::addDatabase("QSQLITE");
  QString appDirPath = QCoreApplication::applicationDirPath();
  database_path_ = appDirPath + "/record.db3";
  database_.setDatabaseName(database_path_);
  if (!database_.open()) {
    qDebug() << "无法打开数据库: " << database_.lastError().text();
    return;
  } else {
    if (!database_.tables().contains("translate_records")) {
      QSqlQuery query(database_);
      QString create_table_translate_records =
          "CREATE TABLE translate_records ("
          "timestamp TEXT PRIMARY KEY, "
          "src TEXT, "
          "src_text TEXT,"
          "tar TEXT, "
          "tar_text TEXT)";
      if (query.exec(create_table_translate_records)) {
        qDebug() << "成功创建 translate_records 表";
      } else {
        qDebug() << "创建表translate_records 失败: "
                 << query.lastError().text();
      }
      query.clear();
      database_.close();
    } else {
      qDebug() << "translate_records 表已存在";
      database_.close();
    }
  }
  if (!OpenDatabase()) {
    QMessageBox::warning(nullptr, "警告",
                         "无法打开数据库 recorddatabase.cpp 44",
                         QMessageBox::Ok);
    return;
  }
}

bool RecordDataBase::OpenDatabase() {
  if (database_.isOpen()) {
    return true;
  } else if (database_.open()) {
    return true;
  } else {
    QMessageBox::information(nullptr, "通知",
                             "无法打开数据库 recorddatabase.cpp 48");
    return false;
  }
}

bool RecordDataBase::CloseDatabase() {
  if (database_.isOpen()) {
    database_.close();
    return true;
  } else {
    return false;
  }
}

bool RecordDataBase::InsertTranslateRecord(const QString& src,
                                           const QString& tar,
                                           const QString& src_text,
                                           const QString& tar_text,
                                           const QString& timestamp) {
  database_.open();
  if (!database_.isOpen()) {
    QMessageBox::information(nullptr, "通知",
                             "无法打开数据库 recorddatabase.cpp 68");
    return false;
  }
  QSqlQuery query;
  query.prepare(
      "INSERT INTO translate_records (src, src_text, tar, tar_text, timestamp) "
      "VALUES (:src, :src_text, :tar, :tar_text, :timestamp)");
  query.bindValue(":src", src);
  query.bindValue(":tar", tar);
  query.bindValue(":src_text", src_text);
  query.bindValue(":tar_text", tar_text);
  query.bindValue(":timestamp", timestamp);
  qDebug() << "73:" << src << tar << src_text << tar_text << timestamp;

  if (query.exec()) {
    return true;
  } else {
    return false;
  }
}

QList<TranslateRecord> RecordDataBase::GetTranslateRecords() {
  QList<TranslateRecord> translate_records;
  database_.open();
  if (!database_.isOpen()) {
    return translate_records;
  }
  QSqlQuery query;
  query.prepare("SELECT src_text, tar_text, timestamp FROM translate_records");
  if (query.exec()) {
    while (query.next()) {
      TranslateRecord record;
      record.timestamp = query.value("timestamp").toString();
      record.src_text = query.value("src_text").toString();
      record.tar_text = query.value("tar_text").toString();
      translate_records.append(record);
    }
  } else {
    qDebug() << "查询历史记录失败:" << query.lastError().text();
  }
  database_.close();
  return translate_records;
}

bool RecordDataBase::ClearTranslateRecords() {
  database_.open();
  if (!database_.isOpen()) {
    return false;
  }
  QSqlQuery query;
  query.prepare("DELETE FROM translate_records");
  if (query.exec()) {
    qDebug() << "成功清空 translate_records 表";
    database_.close();
    return true;
  } else {
    qDebug() << "清空表translate_records失败: " << query.lastError().text();
    database_.close();
    return false;
  }
}