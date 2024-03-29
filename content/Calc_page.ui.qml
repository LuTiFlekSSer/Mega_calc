import QtQuick 6.4
import QtQuick.Controls 6.4
import Mega_calc
import QtQuick.Dialogs 6.4
import QtQuick.Layouts 6.4
import QtMultimedia 6.3

Page {
    id: calc_page
    font.letterSpacing: 0
    focusPolicy: Qt.NoFocus
    enabled: true
    background: Rectangle {
        color: "#2b2d30"
    }

    property string text
    signal ansClicked
    signal changeMode
    // @disable-check M222
    function add_ans(ans) {
        // @disable-check M222
        list_model.insert(0, ans)
    }

    StackLayout {
        id: stackl
        width: 560
        anchors.bottom: num9.top
        anchors.bottomMargin: 20
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
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
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
                        png_for_img: "Images/add.png"
                        pix: 6
                        func: "()+()"
                    }
                    ListElement {
                        png_for_img: "Images/sub.png"
                        pix: 6
                        func: "()-()"
                    }
                    ListElement {
                        png_for_img: "Images/mult.png"
                        pix: 6
                        func: "()*()"
                    }
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
                        png_for_img: "Images/phase.png"
                        pix: 7
                        func: "phase()"
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
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
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
                    onClicked: input_field.insert(input_field.cursorPosition,
                                                  func)
                }
                model: ListModel {
                    ListElement {
                        png_for_img: "Images/dtr.png"
                        pix: 5
                        func: "dtr()"
                    }
                    ListElement {
                        png_for_img: "Images/rtg.png"
                        pix: 5
                        func: "rtd()"
                    }
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
                    ListElement {
                        png_for_img: "Images/asec.png"
                        pix: 4
                        func: "asec()"
                    }
                    ListElement {
                        png_for_img: "Images/acsc.png"
                        pix: 4
                        func: "acsc()"
                    }
                    ListElement {
                        png_for_img: "Images/asinh.png"
                        pix: 4
                        func: "asinh()"
                    }
                    ListElement {
                        png_for_img: "Images/acosh.png"
                        pix: 4
                        func: "acosh()"
                    }
                    ListElement {
                        png_for_img: "Images/atanh.png"
                        pix: 4
                        func: "atanh()"
                    }
                    ListElement {
                        png_for_img: "Images/acoth.png"
                        pix: 4
                        func: "acoth()"
                    }
                    ListElement {
                        png_for_img: "Images/asech.png"
                        pix: 4
                        func: "asech()"
                    }
                    ListElement {
                        png_for_img: "Images/acsch.png"
                        pix: 4
                        func: "acsch()"
                    }
                }
                cellWidth: 60
                cellHeight: 60
            }
        }
        Rectangle {
            id: many_value_tab
            color: "white"
            radius: 5
            GridView {
                id: many_value_grid
                anchors.fill: parent
                anchors.margins: 10
                clip: true
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
                delegate: Button {
                    width: 50
                    height: 50
                    Image {
                        anchors.fill: parent
                        anchors.margins: pix
                        source: png_for_img
                    }
                    // @disable-check M222
                    onClicked: input_field.insert(input_field.cursorPosition,
                                                  func)
                }
                model: ListModel {
                    ListElement {
                        png_for_img: "Images/Mphase.png"
                        pix: 5
                        func: "Mphase(,)"
                    }
                    ListElement {
                        png_for_img: "Images/Mln.png"
                        pix: 5
                        func: "Mln(,)"
                    }
                    ListElement {
                        png_for_img: "Images/Mlog.png"
                        pix: 5
                        func: "Mlog(,,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Mpow.png"
                        pix: 5
                        func: "Mpow(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Msqrt.png"
                        pix: 5
                        func: "Msqrt(,)"
                    }
                    ListElement {
                        png_for_img: "Images/Msurd.png"
                        pix: 5
                        func: "Msurd(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Masin.png"
                        pix: 5
                        func: "Masin(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macos.png"
                        pix: 5
                        func: "Macos(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Matan.png"
                        pix: 5
                        func: "Matan(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macot.png"
                        pix: 5
                        func: "Macot(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Masec.png"
                        pix: 5
                        func: "Masec(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macsc.png"
                        pix: 5
                        func: "Macsc(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Masinh.png"
                        pix: 5
                        func: "Masinh(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macosh.png"
                        pix: 5
                        func: "Macosh(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Matanh.png"
                        pix: 5
                        func: "Matanh(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macoth.png"
                        pix: 5
                        func: "Macoth(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Masech.png"
                        pix: 5
                        func: "Masech(,,)"
                    }
                    ListElement {
                        png_for_img: "Images/Macsch.png"
                        pix: 5
                        func: "Macsch(,,)"
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
            GridView {
                id: const_grid
                anchors.fill: parent
                anchors.margins: 10
                clip: true
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
                delegate: Button {
                    width: 50
                    height: 50
                    Image {
                        anchors.fill: parent
                        anchors.margins: pix
                        source: png_for_img
                    }
                    // @disable-check M222
                    onClicked: input_field.insert(input_field.cursorPosition,
                                                  func)
                }
                model: ListModel {
                    ListElement {
                        png_for_img: "Images/Pi.png"
                        pix: 7
                        func: "Pi"
                    }
                    ListElement {
                        png_for_img: "Images/e.png"
                        pix: 7
                        func: "e"
                    }
                    ListElement {
                        png_for_img: "Images/i.png"
                        pix: 7
                        func: "i"
                    }
                }
                cellWidth: 60
                cellHeight: 60
            }
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
        anchors.topMargin: 20
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
            // @disable-check M223
            onClicked: {
                calc_page.text = input_field.text
                // @disable-check M222
                calc_page.ansClicked()
            }
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
            onClicked: input_field.remove(input_field.cursorPosition - 1,
                                          input_field.cursorPosition)
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
            text: qsTr("Многозначные")
            font.pointSize: 10
            width: implicitWidth
        }
        TabButton {
            text: qsTr("Константы")
            font.pointSize: 10
            width: implicitWidth
        }
    }

    Button {
        id: num1
        anchors.bottom: num0.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("1")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num0
        y: 423
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 110
        height: 40
        font.pointSize: 11
        text: qsTr("0")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: numdot
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: num0.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        text: qsTr(".")
        bottomPadding: 20
        font.pointSize: 30
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num2
        anchors.left: num1.right
        anchors.leftMargin: 10
        anchors.bottom: num0.top
        anchors.bottomMargin: 10
        width: 50
        height: 40
        text: qsTr("2")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num4
        anchors.bottom: num1.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("4")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num5
        anchors.bottom: num2.top
        anchors.bottomMargin: 10
        anchors.left: num4.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("5")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num7
        anchors.bottom: num4.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("7")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num8
        anchors.bottom: num4.top
        anchors.bottomMargin: 10
        anchors.left: num7.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("8")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num9
        anchors.bottom: num6.top
        anchors.bottomMargin: 10
        anchors.left: num8.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("9")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num6
        anchors.bottom: num3.top
        anchors.bottomMargin: 10
        anchors.left: num5.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("6")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num3
        anchors.bottom: numdot.top
        anchors.bottomMargin: 10
        anchors.left: num2.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        font.pointSize: 11
        text: qsTr("3")
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_br_l
        anchors.bottom: num_add.top
        anchors.bottomMargin: 10
        anchors.left: num9.right
        anchors.leftMargin: 20
        width: 50
        height: 40
        text: qsTr("(")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_br_r
        anchors.bottom: num_sub.top
        anchors.bottomMargin: 10
        anchors.left: num_br_l.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        text: qsTr(")")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_add
        anchors.bottom: num_mult.top
        anchors.bottomMargin: 10
        anchors.left: num6.right
        anchors.leftMargin: 20
        width: 50
        height: 40
        text: qsTr("+")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_sub
        anchors.bottom: num_div.top
        anchors.bottomMargin: 10
        anchors.left: num_add.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        text: qsTr("-")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_mult
        anchors.bottom: numAns.top
        anchors.bottomMargin: 10
        anchors.left: num3.right
        anchors.leftMargin: 20
        width: 50
        height: 40
        text: qsTr("*")
        topPadding: 15
        font.pointSize: 15
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: num_div
        anchors.bottom: num_per.top
        anchors.bottomMargin: 10
        anchors.left: num_mult.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        text: qsTr("/")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Button {
        id: numAns
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: numdot.right
        anchors.leftMargin: 20
        width: 50
        height: 40
        text: qsTr("Ans")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, "Ans")
    }

    Button {
        id: num_per
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: numAns.right
        anchors.leftMargin: 10
        width: 50
        height: 40
        text: qsTr("%")
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, text)
    }

    Rectangle {
        id: ans_rect
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: stackl.right
        anchors.leftMargin: 20
        anchors.top: stackl.top
        color: "#ffffff"
        radius: 5
        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 10
            anchors.bottomMargin: hist_clear.height + 20
            clip: true
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }

            model: ListModel {
                id: list_model
            }
            delegate: TextField {
                height: implicitHeight + 10
                width: ListView.view.width - 10
                readOnly: true
                text: hist_text
                rightPadding: 40
                wrapMode: TextInput.WrapAnywhere
                Button {
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    width: 25
                    height: width
                    font.pointSize: 11
                    text: qsTr("")
                    // @disable-check M222
                    onClicked: input_field.insert(input_field.cursorPosition,
                                                  parent.text)
                    Image {
                        anchors.fill: parent
                        anchors.margins: 2
                        source: "Images/save.png"
                    }
                }
            }
        }

        Button {
            id: hist_clear
            width: implicitWidth
            height: 40
            text: qsTr("Очистить")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            font.pointSize: 11
            // @disable-check M222
            onClicked: list_model.clear()
        }
    }

    Button {
        id: ms
        property string buf: ""
        width: 50
        height: 40
        text: qsTr("MS")
        anchors.left: num_sub.right
        anchors.top: mr.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 10
        font.pointSize: 11
        // @disable-check M223
        onClicked: {
            buf = input_field.text
            memory_indicator.visible = true
        }
    }

    Button {
        id: mc
        width: 50
        height: 40
        text: qsTr("MC")
        anchors.left: mr.right
        anchors.top: ms.bottom
        anchors.leftMargin: -50
        anchors.topMargin: 10
        font.pointSize: 11
        // @disable-check M223
        onClicked: {
            ms.buf = ""
            memory_indicator.visible = false
        }
    }

    Button {
        id: mr
        width: 50
        height: 40
        text: qsTr("MR")
        anchors.left: num_br_r.right
        anchors.top: stackl.bottom
        anchors.leftMargin: 20
        anchors.topMargin: 20
        font.pointSize: 11
        // @disable-check M222
        onClicked: input_field.insert(input_field.cursorPosition, ms.buf)
    }

    Text {
        id: memory_indicator
        visible: false
        color: "#ffffff"
        anchors.bottom: input_field.top
        anchors.left: input_field.left
        anchors.bottomMargin: 2
        anchors.leftMargin: 2
        text: qsTr("M")
        font.pixelSize: 12
    }

    Button {
        id: change
        width: implicitWidth
        height: 40
        text: qsTr("Матрицы")
        anchors.right: ans_rect.left
        anchors.top: mc.bottom
        anchors.rightMargin: 10
        font.pointSize: 11
        anchors.topMargin: 10
        // @disable-check M222
        onClicked: calc_page.changeMode()
    }

    Connections {
        target: Core
        onEvent: {
            dead_inside_player.stop()
            dead_inside_player.play()
        }
    }

    SoundEffect {
        id: dead_inside_player
        source: "Music/123.wav"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:136}
}
##^##*/

