import QtQuick
import QtQuick.Controls

ApplicationWindow {
    maximumWidth: 720
    maximumHeight: 640
    minimumWidth: 720
    minimumHeight: 640
    visible: true

    MainWindow {
        id: main_window
        anchors.fill: parent
    }
}
