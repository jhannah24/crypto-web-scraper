/** worker.h
 *  Header file for the worker class, which manages fetching cryptocurrency data in a separate thread
 *  @author Josh Hannah
 */

#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "curlobj.h"
#include "data.h"

// Class to manage fetching cryptocurrency data in a separate thread
class Worker : public QObject {
    Q_OBJECT

public:
    // Constructor initalizing with a URL and optional parent
    explicit Worker(const QString &url, QObject *parent = nullptr);

public slots:
    // Slot to start data fetching
    void fetchData();

signals:
    void dataFetched(const std::vector<CryptoData> &cryptoList);    // Signaled when cryptocurrency data is fetched and parsed
    void errorOccurred(const QString &errorMsg);                    // Signaled when error occurs during fetching or parsing

private:
    QString m_url; // URL being fetched
};

#endif // WORKER_H
