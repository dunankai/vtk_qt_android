import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import qtquick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GridLayout {
        columns: 2

        MyVtkItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }

        MyConeItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }

        MyWidgetItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }

        MyGeomItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }

        MyVolumeItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }

        MyGlyphItem {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: 200
        }
    }
}
