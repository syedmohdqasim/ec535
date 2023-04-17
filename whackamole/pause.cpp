#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create the pop-up dialog
    QMessageBox::information(nullptr, "Game Paused", "Message");

    // Start the application event loop
    return app.exec();
}
