#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load the base image
    QPixmap baseImage("../images/molebg.png"); //TODO revise directory

    // Create a QLabel widget to display the base image
    QLabel baseLabel;
    baseLabel.setPixmap(baseImage);

    // Load the sliding image
    QPixmap slidingImage("../images/mole.png");

    // Create a QLabel widget to display the sliding image
    //TODO make multiple moles

    // 55, 150, 250, 350 x 60
    // same x 160


    QLabel slidingLabel;
    slidingLabel.setPixmap(slidingImage);
    slidingLabel.setMask(slidingImage.createHeuristicMask()); // Make the sliding image transparent

    // Set the initial position of the sliding image
    int startX = 55;
    int startY = 60;
    initialY = startY;
    slidingLabel.move(startX, startY);

    int travel = 5

    // Create a QTimer to animate the sliding image
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]{
        // Update the position of the sliding image
        startY += travel;
        slidingLabel.move(startX, startY);

        // Reset the position of the sliding image if it goes out of bounds
        if (startY >= initialY + 30) {
            startY = initialY + 30;
            travel = travel * -1;
        }
        if (startY <= initialY ){
            startY = initialY;
            travel = travel * -1;
        }
    });

    timer.start(50); // Set the interval of the timer to 50 ms

    // Create a QWidget to contain the base and sliding labels
    QWidget widget;
    widget.resize(baseImage.width(), baseImage.height());
    baseLabel.setParent(&widget);
    slidingLabel.setParent(&widget);

    // Show the widget and start the application event loop
    widget.show();
    return app.exec();
}
