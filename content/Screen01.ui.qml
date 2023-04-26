

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

    Calc_page {
        id: calc_page
        // @disable-check M223
        onAnsClicked: {
            backgr.visible = true
            busyIndicator.running = true
            stackView.enabled = false
            busyIndicator.visible = true
            // @disable-check M222
            Core.solve_expr(calc_page.text)
        }
        // @disable-check M222
        onChangeMode: stackView.push(matrix_page)
    }

    Matrix_page {
        id: matrix_page
        Connections {
            target: matrix_page
            onChangeMode: stackView.pop()
            onWait: {
                backgr.visible = true
                busyIndicator.running = true
                stackView.enabled = false
                busyIndicator.visible = true
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: calc_page
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
        visible: false
        anchors.centerIn: parent
        running: false
        wheelEnabled: false
        z: 1
        focusPolicy: Qt.NoFocus
    }

    Connections {
        target: Core
        onSend_ans: msg => {
                        backgr.visible = false
                        busyIndicator.running = false
                        stackView.enabled = true
                        var new_ans = {}
                        new_ans.hist_text = msg
                        busyIndicator.visible = false
                        calc_page.add_ans(new_ans)
                    }
        onSend_error: err => {
                          backgr.visible = false
                          busyIndicator.running = false
                          stackView.enabled = true
                          busyIndicator.visible = false
                          mess_dial.message = err
                          mess_dial.open()
                      }
        onSend_matrix: (m, size_x, size_y, index) => {
                           busyIndicator.visible = false
                           backgr.visible = false
                           busyIndicator.running = false
                           stackView.enabled = true
                           if (index === 2){
                                matrix_page.changeItems_C(m, size_x, size_y)
                           }else if (index === 1){
                               matrix_page.changeItems_B(m, size_x, size_y)
                           }else{
                               matrix_page.changeItems_A(m, size_x, size_y)
                           }
                       }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

