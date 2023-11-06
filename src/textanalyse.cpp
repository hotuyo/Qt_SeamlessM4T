
#include "textanalyse.h"
#include <QDialog>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QPushButton>
TextAnalyse::TextAnalyse(QObject* parent): QObject(parent) {
  record = RecordDataBase();
}

TextAnalyse::~TextAnalyse() {

}

void TextAnalyse::PostSrcText(const QString text, const QString type, const QString target, const QString src) {
  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  QNetworkRequest request;
  // set server ip
  request.setUrl(QUrl("http://192.168.1.6:9979/translate"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=UTF-8");
  QString src_text = text;
  src_text.replace(" ", "");
  QJsonObject json_data;
  json_data["text"] = src_text;
  json_data["type"] = type;
  json_data["target"] = target;
  json_data["src"] = src;

  QJsonDocument json_document(json_data);
  QString json_string = QString::fromUtf8(json_document.toJson());
  QNetworkReply* reply = manager->post(request, json_string.toUtf8());
  QObject::connect(reply, &QNetworkReply::finished, [=](){
  QByteArray response_data = reply->readAll();
  QString result = QString::fromUtf8(response_data);
  result.replace("<unk>", "");
  result.replace("⁇", ".");
    if (result.isEmpty()){
      emit signals_ProcessedText("Error");
    }
    record.OpenDatabase();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDateTimeStr = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
    record.InsertTranslateRecord(src, target, src_text, result, currentDateTimeStr);
    emit signals_ProcessedText(result);
    reply->deleteLater();
  });
}

void TextAnalyse::ClearTranslateRecodes(){
  record.OpenDatabase();
  record.ClearTranslateRecords();
  record.CloseDatabase();
}

void TextAnalyse::OpenDialog() {
    QDialog* dialog = new QDialog();
    dialog->setWindowTitle("History Record");
    dialog->setFixedSize(600, 400);
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QListView* listView = new QListView();
    QStandardItemModel* model = new QStandardItemModel();
    QList<TranslateRecord> records = record.GetTranslateRecords();
    foreach (const TranslateRecord& record, records) {
        QStandardItem* item = new QStandardItem(
            QString("Time: %3\nsrc_text: %1\ntar_text: %2")
                .arg(record.src_text)
                .arg(record.tar_text)
                .arg(record.timestamp)
        );
        model->appendRow(item);
    }
    listView->setModel(model);
    QPushButton* clearButton = new QPushButton("clean");
    QObject::connect(clearButton, &QPushButton::clicked, this, &TextAnalyse::ClearTranslateRecodes);
    connect(clearButton, &QPushButton::clicked, [=]() {
            model->clear();
            QList<TranslateRecord> refreshedRecords = record.GetTranslateRecords();
            foreach (const TranslateRecord& refreshedRecord, refreshedRecords) {
                QStandardItem* refreshedItem = new QStandardItem(
                    QString("Time: %1\nsrc_text: %2\ntar_text: %3")
                        .arg(refreshedRecord.timestamp)
                        .arg(refreshedRecord.src_text)
                        .arg(refreshedRecord.tar_text)
                );
                model->appendRow(refreshedItem);
        }
    });
    layout->addWidget(listView);
    layout->addWidget(clearButton);
    dialog->exec();
}

