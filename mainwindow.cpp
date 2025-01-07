/** mainwindow.cpp
 *  Implementation for the MainWindow class, which manages the application's main window and UI interactions
 *  Handles displaying cryptocurrency data and managing periodic data fetching
 *  @author Josh Hannah
 */

#include "mainwindow.h"

// Constructor initializing the main window and setting up components
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker(new Worker("https://coinmarketcap.com/")),
    workerThread(new QThread(this)),
    fetchTimer(new QTimer(this)) {

    ui->setupUi(this);

    // Register custom type for use in signals and slots
    qRegisterMetaType<std::vector<CryptoData>>("std::vector<CryptoData>");

    // Move the worker instance to a separate thread
    worker->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

    // Connect worker signals to MainWindow slots
    connect(worker, &Worker::dataFetched, this, &MainWindow::displayData);
    connect(worker, &Worker::errorOccurred, this, &MainWindow::showError);

    // Start the worker thread
    workerThread->start();

    // Set up periodic data fetching using a timer
    connect(fetchTimer, &QTimer::timeout, worker, &Worker::fetchData);
    fetchTimer->start(5000); // Fetch data every 5 seconds

    // Trigger an initial data fetch
    QMetaObject::invokeMethod(worker, "fetchData", Qt::QueuedConnection);
}

// Destructor to stop fetch timer, quit thread, and clean up resources
MainWindow::~MainWindow() {
    fetchTimer->stop();
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

// Slot to display cryptocurrency data in the UI
void MainWindow::displayData(const std::vector<CryptoData>& cryptoList) {
    const std::array<QTextEdit*, 10> largerTextEdits = {
        ui->name_1, ui->name_2, ui->name_3, ui->name_4,
        ui->name_5, ui->name_6, ui->name_7, ui->name_8,
        ui->name_9, ui->name_10
    };

    const std::array<QTextEdit*, 10> smallerTextEdits = {
        ui->price_1, ui->price_2, ui->price_3, ui->price_4,
        ui->price_5, ui->price_6, ui->price_7, ui->price_8,
        ui->price_9, ui->price_10
    };

    const std::array<QProgressBar*, 10> progressBars = {
        ui->market_cap_1, ui->market_cap_2, ui->market_cap_3, ui->market_cap_4,
        ui->market_cap_5, ui->market_cap_6, ui->market_cap_7, ui->market_cap_8,
        ui->market_cap_9, ui->market_cap_10
    };

    // Exit if no data is available
    if (cryptoList.empty()) return;

    // Parse the baseline market cap from the first item
    double baselineMarketCap = 0.0;
    try {
        std::string cleanedBaselineMarketCap = cryptoList[0].marketCap;
        cleanedBaselineMarketCap.erase(std::remove_if(cleanedBaselineMarketCap.begin(), cleanedBaselineMarketCap.end(),
                                                      [](char c) { return !(std::isdigit(c) || c == '.'); }), cleanedBaselineMarketCap.end());
        baselineMarketCap = std::stod(cleanedBaselineMarketCap);
        if (baselineMarketCap <= 0) throw std::invalid_argument("Baseline market cap must be positive");
    } catch (const std::exception& e) {
        std::cerr << "Error parsing baseline market cap: " << e.what() << std::endl;
        QMessageBox::warning(this, "Invalid Market Cap", "Failed to parse baseline market cap. Progress bars will not display percentages.");
        return;
    }

    // Update the UI components with the fetched data
    for (size_t i = 0; i < cryptoList.size() && i < largerTextEdits.size(); ++i) {
        // Set names in the larger text boxes
        largerTextEdits[i]->setText(QString::fromStdString(cryptoList[i].name));

        // Parse and set prices in the smaller text boxes
        std::string cleanedPrice = cryptoList[i].price;
        cleanedPrice.erase(std::remove_if(cleanedPrice.begin(), cleanedPrice.end(),
                                          [](char c) { return !(std::isdigit(c) || c == '.'); }), cleanedPrice.end());
        if (i < smallerTextEdits.size()) {
            try {
                double price = std::stod(cleanedPrice);
                smallerTextEdits[i]->setText(QString::number(price, 'f', 2));
            } catch (const std::exception&) {
                smallerTextEdits[i]->setText("N/A");
            }
        }

        // Calculate and set progress bar values based on market cap
        std::string cleanedMarketCap = cryptoList[i].marketCap;
        cleanedMarketCap.erase(std::remove_if(cleanedMarketCap.begin(), cleanedMarketCap.end(),
                                              [](char c) { return !(std::isdigit(c) || c == '.'); }), cleanedMarketCap.end());
        try {
            double marketCap = std::stod(cleanedMarketCap);
            int progress = static_cast<int>((marketCap / baselineMarketCap) * 100);
            if (i < progressBars.size()) {
                progressBars[i]->setValue(std::min(progress, 100));

                // Display the market cap value as text on the progress bar
                QString marketCapText = QString::fromStdString(cryptoList[i].marketCap);
                progressBars[i]->setFormat(marketCapText);
                progressBars[i]->setTextVisible(true);
            }
        } catch (const std::exception&) {
            if (i < progressBars.size()) {
                progressBars[i]->setValue(0);
                progressBars[i]->setFormat("N/A");
                progressBars[i]->setTextVisible(true);
            }
        }
    }
}

// Slot to display error messages in a message box
void MainWindow::showError(const QString &errorMsg) {
    QMessageBox::critical(this, "Error", errorMsg);
}
