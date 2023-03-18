

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

    Page {
        id: page
        anchors.fill: parent
        font.letterSpacing: 0
        focusPolicy: Qt.NoFocus
        enabled: true
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        rightPadding: 0
        background: Rectangle {
            color: "#2b2d30"
        }
        StackLayout {
            x: 26
            y: 123
            width: 440
            height: 134
            anchors.top: bar.bottom
            anchors.left: input_field.left
            currentIndex: bar.currentIndex
            Rectangle {
                id: pow_tab
                color: "white"
                radius: 5
                GridView {
                    id: pow_grid
                    anchors.fill: parent
                    anchors.margins: 10
                    clip: true
                    ScrollBar.vertical: ScrollBar {policy: ScrollBar.AlwaysOn}
                    delegate: Button {
                        width: 50
                        height: 50
                        icon.height: 50
                        icon.width: 50
                        icon.source: png
                        Image {
                            anchors.fill: parent
                            anchors.margins: pix
                            source: png_for_img
                        }
                        // @disable-check M222
                        onClicked: input_field.insert(input_field.cursorPosition, func)
                    }
                    model: ListModel {
                        ListElement {
                            png: "Images/div.png"
                            pix: 7
                            func: "()/()"
                        }
                        ListElement {
                            png: "Images/pow.png"
                            pix: 7
                            func: "pow(,)"
                        }
                        ListElement {
                            png: "Images/pow2.png"
                            pix: 7
                            func: "sqr()"
                        }
                        ListElement {
                            png: "Images/exp.png"
                            pix: 7
                            func: "exp()"
                        }
                        ListElement {
                            png: "Images/sqrt.png"
                            pix: 7
                            func: "sqrt()"
                        }
                        ListElement {
                            png: "Images/surd.png"
                            pix: 7
                            func: "surd(,)"
                        }
                        ListElement {
                            png: "Images/inf.png"
                            pix: 7
                            func: "inf"
                        }
                        ListElement {
                            png_for_img: "Images/infm.png"
                            pix: 7
                            func: "infm"
                        }
                        ListElement {
                            png_for_img: "Images/ln.png"
                            pix: 7
                            func: "ln()"
                        }
                        ListElement {
                            png_for_img: "Images/lg.png"
                            pix: 7
                            func: "lg()"
                        }
                        ListElement {
                            png_for_img: "Images/log.png"
                            pix: 5
                            func: "log(,)"
                        }
                        ListElement {
                            png_for_img: "Images/abs.png"
                            pix: 7
                            func: "abs()"
                        }
                        ListElement {
                            png_for_img: "Images/factorial.png"
                            pix: 7
                            func: "factorial()"
                        }
                        ListElement {
                            png_for_img: "Images/max.png"
                            pix: 1
                            func: "max(,)"
                        }
                        ListElement {
                            png_for_img: "Images/min.png"
                            pix: 1
                            func: "min(,)"
                        }
                        ListElement {
                            png_for_img: "Images/floor.png"
                            pix: 1
                            func: "floor()"
                        }
                        ListElement {
                            png_for_img: "Images/ceil.png"
                            pix: 1
                            func: "ceil()"
                        }
                    }
                    cellWidth: 60
                    cellHeight: 60
                }
            }
            Rectangle {
                id: periodic_tab
                color: "white"
                radius: 5
                GridView {
                    id: periodic_grid
                    anchors.fill: parent
                    anchors.margins: 10
                    clip: true
                    ScrollBar.vertical: ScrollBar {policy: ScrollBar.AlwaysOn}
                    delegate: Button {
                        width: 50
                        height: 50
                        icon.height: 50
                        icon.width: 50
                        Image {
                            anchors.fill: parent
                            anchors.margins: pix
                            source: png_for_img
                        }
                        // @disable-check M222
                        onClicked: input_field.insert(input_field.cursorPosition, func)
                    }
                    model: ListModel {
                        ListElement {
                            png_for_img: "Images/sin.png"
                            pix: 7
                            func: "sin()"
                        }
                        ListElement {
                            png_for_img: "Images/cos.png"
                            pix: 7
                            func: "cos()"
                        }
                        ListElement {
                            png_for_img: "Images/tan.png"
                            pix: 7
                            func: "tan()"
                        }
                        ListElement {
                            png_for_img: "Images/cot.png"
                            pix: 7
                            func: "cot()"
                        }
                        ListElement {
                            png_for_img: "Images/sec.png"
                            pix: 7
                            func: "sec()"
                        }
                        ListElement {
                            png_for_img: "Images/csc.png"
                            pix: 7
                            func: "csc()"
                        }
                        ListElement {
                            png_for_img: "Images/sinh.png"
                            pix: 4
                            func: "sinh()"
                        }
                        ListElement {
                            png_for_img: "Images/cosh.png"
                            pix: 4
                            func: "cosh()"
                        }
                        ListElement {
                            png_for_img: "Images/tanh.png"
                            pix: 4
                            func: "tanh()"
                        }
                        ListElement {
                            png_for_img: "Images/coth.png"
                            pix: 4
                            func: "coth()"
                        }
                        ListElement {
                            png_for_img: "Images/sech.png"
                            pix: 4
                            func: "sech()"
                        }
                        ListElement {
                            png_for_img: "Images/csch.png"
                            pix: 4
                            func: "csch()"
                        }
                        ListElement {
                            png_for_img: "Images/asin.png"
                            pix: 4
                            func: "asin()"
                        }
                        ListElement {
                            png_for_img: "Images/acos.png"
                            pix: 4
                            func: "acos()"
                        }
                        ListElement {
                            png_for_img: "Images/atan.png"
                            pix: 4
                            func: "atan()"
                        }
                        ListElement {
                            png_for_img: "Images/acot.png"
                            pix: 4
                            func: "acot()"
                        }
                    }
                    cellWidth: 60
                    cellHeight: 60
                }
            }
            Rectangle {
                id: const_tab
                color: "white"
                radius: 5
            }
        }

        TextField {
            id: input_field
            placeholderText: qsTr("Введи выражение")
            height: 50
            anchors.top: parent.top
            rightPadding: 120
            font.pointSize: 11
            placeholderTextColor: "#80332b2b"
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            cursorDelegate: Rectangle {
                visible: input_field.cursorVisible
                color: "blue"
                width: input_field.cursorRectangle.width
            }
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
                onClicked: input_field.text = ""
                text: qsTr("✕")
            }

            Button {
                id: backspace
                anchors.right: clear.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 12
                width: 25
                height: 25
                // @disable-check M222
                onClicked: input_field.remove(input_field.cursorPosition - 1,input_field.cursorPosition)
                text: qsTr("⌫")
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
                text: qsTr("Арифметические")
                font.pointSize: 10
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Тригонометрические")
                font.pointSize: 10
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Константы")
                font.pointSize: 10
                width: implicitWidth
            }
        }
    }

    Rectangle {
        id: backgr
        opacity: 0.8
        visible: false
        anchors.fill: parent
        clip: false
        activeFocusOnTab: false
        focus: false
        color: "#090909"
    }

    MyBS {
        id: busyIndicator
        x: 278
        y: 216
        width: 84
        height: 48
        visible: true
        anchors.centerIn: parent
        running: false
        wheelEnabled: false
        z: 1
        focusPolicy: Qt.NoFocus
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:60;invisible:true}
}
##^##*/

