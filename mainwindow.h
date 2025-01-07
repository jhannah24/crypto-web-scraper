/** mainwindow.h
 *  Header file for the MainWindow class, which manages the application's main window and UI interactions
 *  @author by Josh Hannah
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMessageBox>
#include <iostream>
#include "worker.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

// Class to manage the main application window
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr); // Constructor to initialize the main window with optional parent widget
    ~MainWindow();                                  // Destructor for cleanup

private slots:
    // Slot to display cryptocurrency data in the UI
    void displayData(const std::vector<CryptoData>& cryptoList);

    // Slot to show error messages in the UI
    void showError(const QString &errorMsg);

private:
    Ui::MainWindow *ui;     // Pointer to UI components
    Worker *worker;         // Worker instance for data fetching
    QThread *workerThread;  // Thread for running worker
    QTimer *fetchTimer;     // Timer for scheduling periodic fetching
};

#endif // MAINWINDOW_H
