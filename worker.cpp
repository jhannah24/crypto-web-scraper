/** worker.cpp
 *  Implementation file for the Worker class, which manages fetching cryptocurrency data in a separate thread
 *  The Worker class uses CurlObj to fetch raw data from a given URL and Data to parse it into a usable format
 *  @author by Josh Hannah
 */

#include "worker.h"

// Constructor initializing the Worker with a URL and optional parent
Worker::Worker(const QString &url, QObject *parent)
    : QObject(parent), m_url(url) {}

// Slot to fetch cryptocurrency data from the provided URL
void Worker::fetchData() {
    try {
        CurlObj curlObj(m_url.toStdString());   // Create a CurlObj to fetch data from URL
        Data data(curlObj.getData());           // Parse the fetched data into cryptocurrency information

        emit dataFetched(data.getCryptoList()); // Signaled when cryptocurrency data is fetched and parsed
    } catch (const std::exception &e) {
        emit errorOccurred(e.what());           // Signaled when error occurs during fetching or parsing
    }
}
