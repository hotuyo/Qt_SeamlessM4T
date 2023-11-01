#ifndef TEXTANALYSE
#define TEXTANALYSE

#include <QByteArray>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QString>

#include "recorddatabase.h"



class TextAnalyse: public QObject
{
  Q_OBJECT
  QML_ELEMENT

 public:
  explicit TextAnalyse(QObject *parent = nullptr);
  ~TextAnalyse();
  TextAnalyse(const TextAnalyse&) = delete;
  TextAnalyse& operator=(const TextAnalyse&) = delete;
  TextAnalyse(TextAnalyse&&) = delete;
  Q_INVOKABLE void PostSrcText(const QString text, const QString type, const QString target, const QString src);
  Q_INVOKABLE void OpenDialog();

 signals:
  void signals_ProcessedText(QString translate_result);

 public slots:
  void ClearTranslateRecodes();
 private:
  RecordDataBase record;
  QVariantList m_history_records;
};

#endif // TEXTANALYSE
