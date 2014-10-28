import QtQuick 2.3
import QtQuick.Controls 1.2

Rectangle {
    width: 283
    height: 87
    color: "lightgray"

    Row {
        Column {
            Row {
                Label {
                    id: label
                    text: qsTr("Find &what:")
                }
                TextField {
                    id: lineEdit
                    placeholderText: qsTr("QtQuick")
                }
            }
            CheckBox {
                id: caseCheckBox
                text: qsTr("Match &case")
            }
            CheckBox {
                id: backwardCheckBox
                text: qsTr("Search &backward")
            }
        }
        Column {
            Button {
                id: findButton
                text: qsTr("&Find")
            }
            Button {
                id: closeButton
                text: qsTr("E&xit")
                onClicked: Qt.quit()
            }
        }
    }
}
