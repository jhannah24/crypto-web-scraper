/** main.cpp
 *  Initializes the application, creates the main window, and starts the event loop.
 *  @author by Josh Hannah
 */

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);   // Initialize Qt application
    MainWindow mainWindow;          // Create main application window
    mainWindow.show();
    return app.exec();              //Start application's event loop
}
