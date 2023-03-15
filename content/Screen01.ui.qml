

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.4
import QtQuick.Controls 6.4
import Mega_calc
import QtQuick.Dialogs 6.4
import QtQuick.Layouts 6.4

Rectangle {
    id: rectangle
    anchors.fill: parent
    color: Constants.backgroundColor

    MyBS {
        id: busyIndicator
        width: 84
        height: 48
        anchors.centerIn: parent
        running: true
        wheelEnabled: false
        z: 1
        focusPolicy: Qt.NoFocus
    }

    Page {
        id: page
        anchors.fill: parent
        font.letterSpacing: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        rightPadding: 0
        background: Rectangle {
            color: "#2b2d30"
        }

        TextField {
            id: input_field
            placeholderText: qsTr("Введи выражение")
            height: 50
            anchors.top: parent.top
            rightPadding: 100
            font.pointSize: 11
            placeholderTextColor: "#80332b2b"
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            Button {
                id: get_ans
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                width: 25
                height: 25
                text: qsTr("=")
            }

            Button {
                id: clear
                anchors.right: get_ans.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                width: 25
                height: 25
                text: qsTr("x")
            }
        }

        TabBar {
            id: bar
            anchors.top: input_field.bottom
            spacing: 0
            currentIndex: 0
            anchors.topMargin: 10
            anchors.left: input_field.left
            TabButton {
                text: qsTr("Степенные")
                font.pointSize: 10
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Периодичные")
                font.pointSize: 10
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Константы")
                font.pointSize: 10
                width: implicitWidth
            }
        }
        StackLayout {
            x: 26
            y: 123
            width: 440
            height: 99
            anchors.top: bar.bottom
            anchors.left: input_field.left
            currentIndex: bar.currentIndex
            Rectangle {
                id: pow_tab
                color: "white"
                radius: 5

                Button {
                    id: button
                    x: 8
                    y: 8
                    text: qsTr("pow(num,deg)")
                }

                Button {
                    id: button1
                    x: 125
                    y: 8
                    text: qsTr("exp(num)")
                }
            }
            Rectangle {
                id: periodic_tab
                color: "white"
                radius: 5
            }
            Rectangle {
                id: const_tab
                color: "white"
                radius: 5
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

