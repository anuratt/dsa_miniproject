#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    
    QFont appFont("Arial", 10);
    app.setFont(appFont);

    
    app.setApplicationName("Hospital Management System");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Computer Engineering DSA Project");

    
    MainWindow window;
    window.show();

    return app.exec();
}
