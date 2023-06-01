import QtQuick 6.4
import QtQuick.Controls 6.4
import Mega_calc
import QtQuick.Dialogs 6.4
import QtQuick.Layouts 6.4
import Qt.labs.qmlmodels
import QtMultimedia 6.3

Page {
    id: matrix_page
    baselineOffset: 0
    background: Rectangle {
        color: "#2b2d30"
    }

    property var matrix_A
    property var matrix_B
    property var matrix_C
    signal changeMode
    signal wait
    // @disable-check M222
    function quick_error(msg) {
        mess_dial.message = msg
        // @disable-check M222
        mess_dial.open()
    }

    // @disable-check M222
    function generateItems_A() {
        // @disable-check M222
        mat_A_Elems.clear()
        // @disable-check M222 // @disable-check M223
        if (parseInt(mat_A_X.text) > 0 && parseInt(mat_A_Y.text) > 0) {
            // @disable-check M222-
            matrix_page.matrix_A = new Array(parseInt(mat_A_X.text))
            // @disable-check M222
            mat_A.elem_x = parseInt(mat_A_X.text)
            // @disable-check M222
            mat_A.elem_y = parseInt(mat_A_Y.text)
            // @disable-check M222 // @disable-check M223
            for (var i = 0; i < parseInt(mat_A_X.text); i++) {
                // @disable-check M222
                matrix_page.matrix_A[i] = new Array(parseInt(mat_A_Y.text))
                // @disable-check M223 // @disable-check M222
                for (var j = 0; j < parseInt(mat_A_Y.text); j++) {
                    matrix_page.matrix_A[i][j] = "0"
                    var list_element = {}
                    list_element.tmp_x = i
                    list_element.tmp_y = j
                    list_element.txt = ""
                    list_element.pos = 0
                    // @disable-check M222
                    mat_A_Elems.append(list_element)
                }
            }
            // @disable-check M223
        } else {
            mat_A.elem_y = 0
            mat_A.elem_x = 0
        }
    }

    // @disable-check M222
    function generateItems_B() {
        // @disable-check M222
        mat_B_Elems.clear()
        // @disable-check M222 // @disable-check M223
        if (parseInt(mat_B_X.text) > 0 && parseInt(mat_B_Y.text) > 0) {
            // @disable-check M222
            matrix_page.matrix_B = new Array(parseInt(mat_B_X.text))
            // @disable-check M222
            mat_B.elem_x = parseInt(mat_B_X.text)
            // @disable-check M222
            mat_B.elem_y = parseInt(mat_B_Y.text)
            // @disable-check M222 // @disable-check M223
            for (var i = 0; i < parseInt(mat_B_X.text); i++) {
                // @disable-check M222
                matrix_page.matrix_B[i] = new Array(parseInt(mat_B_Y.text))
                // @disable-check M223 // @disable-check M222
                for (var j = 0; j < parseInt(mat_B_Y.text); j++) {
                    matrix_page.matrix_B[i][j] = "0"
                    var list_element = {}
                    list_element.tmp_x = i
                    list_element.tmp_y = j
                    list_element.txt = ""
                    list_element.pos = 0
                    // @disable-check M222
                    mat_B_Elems.append(list_element)
                }
            }
            // @disable-check M223
        } else {
            mat_B.elem_y = 0
            mat_B.elem_x = 0
        }
    }
    // @disable-check M222
    function changeItems_A(mat, size_x, size_y) {
        mat_A.elem_x = size_x
        mat_A.elem_y = size_y
        mat_A_X.text = "" + size_x
        mat_A_Y.text = "" + size_y
        // @disable-check M222
        mat_A_Elems.clear()
        matrix_page.matrix_A = new Array(size_x)
        // @disable-check M223
        for (var i = 0; i < size_x; i++) {
            matrix_page.matrix_A[i] = new Array(size_y)
            // @disable-check M223
            for (var j = 0; j < size_y; j++) {
                matrix_page.matrix_A[i][j] = mat[i][j]
                var list_element = {}
                list_element.tmp_x = i
                list_element.tmp_y = j
                list_element.txt = mat[i][j]
                list_element.pos = 0
                // @disable-check M222
                mat_A_Elems.append(list_element)
            }
        }
    }

    // @disable-check M222
    function changeItems_B(mat, size_x, size_y) {
        mat_B.elem_x = size_x
        mat_B.elem_y = size_y
        mat_B_X.text = "" + size_x
        mat_B_Y.text = "" + size_y
        // @disable-check M222
        mat_B_Elems.clear()
        matrix_page.matrix_B = new Array(size_x)
        // @disable-check M223
        for (var i = 0; i < size_x; i++) {
            matrix_page.matrix_B[i] = new Array(size_y)
            // @disable-check M223
            for (var j = 0; j < size_y; j++) {
                matrix_page.matrix_B[i][j] = mat[i][j]
                var list_element = {}
                list_element.tmp_x = i
                list_element.tmp_y = j
                list_element.txt = mat[i][j]
                list_element.pos = 0
                // @disable-check M222
                mat_B_Elems.append(list_element)
            }
        }
    }

    // @disable-check M222
    function changeItems_C(mat, size_x, size_y) {
        mat_C.elem_x = size_x
        mat_C.elem_y = size_y
        // @disable-check M222
        mat_C_Elems.clear()
        matrix_page.matrix_C = new Array(size_x)
        // @disable-check M223
        for (var i = 0; i < size_x; i++) {
            matrix_page.matrix_C[i] = new Array(size_y)
            // @disable-check M223
            for (var j = 0; j < size_y; j++) {
                matrix_page.matrix_C[i][j] = mat[i][j]
                var list_element = {}
                list_element.txt = mat[i][j]
                list_element.pos = 0
                // @disable-check M222
                mat_C_Elems.append(list_element)
            }
        }
    }

    Rectangle {
        id: mat_A
        visible: true
        radius: 5
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.verticalCenter
        clip: true
        anchors.bottomMargin: 10
        anchors.right: mat_A_X.left
        anchors.rightMargin: 10
        color: "#ffffff"
        property int elem_x: 0
        property int elem_y: 0
        ScrollBar.vertical: ScrollBar {
            id: mat_A_bar
            policy: ScrollBar.AlwaysOn
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
        Flickable {
            anchors.fill: parent
            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
            contentHeight: gw_A.height
            contentWidth: gw_A.width
            GridView {
                id: gw_A
                property int elem_width: 70
                property int elem_height: 50
                ScrollBar.vertical: mat_A_bar
                cacheBuffer: 5000
                clip: true
                width: elem_width * mat_A.elem_y
                height: mat_A.height
                model: ListModel {
                    id: mat_A_Elems
                }

                delegate: TextField {
                    property int x_c: tmp_x
                    property int y_c: tmp_y
                    width: gw_A.elem_width
                    height: gw_A.elem_height
                    placeholderText: '0'
                    text: txt
                    cursorPosition: pos
                    onTextEdited: matrix_page.matrix_A[x_c][y_c] = text
                }
                cellWidth: elem_width
                cellHeight: elem_height
            }
        }
    }

    Rectangle {
        id: mat_C
        radius: 5
        anchors.left: mat_A_T.right
        anchors.leftMargin: 20
        anchors.right: clear_B.left
        anchors.rightMargin: 20
        anchors.bottom: mat_C_C.top
        anchors.bottomMargin: 20
        anchors.top: parent.verticalCenter
        anchors.topMargin: 10
        color: "#ffffff"
        clip: true
        ScrollBar.vertical: ScrollBar {
                    id: mat_C_bar
                    policy: ScrollBar.AlwaysOn
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
        }
        property int elem_x: 0
        property int elem_y: 0
        Flickable {
            anchors.fill: parent
            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
            contentHeight: gw_C.height
            contentWidth: gw_C.width
            GridView {
                id: gw_C
                property int elem_width: 70
                property int elem_height: 50

                ScrollBar.vertical: mat_C_bar
                cacheBuffer: 5000
                clip: true
                width: elem_width * mat_C.elem_y
                height: mat_C.height

                model: ListModel {
                    id: mat_C_Elems
                }
                
                delegate: TextField {
                    width: gw_C.elem_width
                    height: gw_C.elem_height
                    text: txt
                    readOnly: true
                    cursorPosition: pos
                }
                cellWidth: elem_width
                cellHeight: elem_height
            }
        }

        Button {
            id: as_text
            anchors.bottom: parent.bottom
            width: 30
            height: 30
            anchors.right: parent.right
            anchors.margins: 8
            Image {
                anchors.fill: parent
                anchors.margins: 4
                source: "Images/as_txt.png"
            }
            Connections {
                target: as_text
                onClicked: {
                    textArea.clear()
                    flickable.visible = true
                    close_text.visible = true
                    for (var i = 0; i < mat_C.elem_x; ++i) {
                        var line = ""
                        for (var j = 0; j < mat_C.elem_y; ++j) {
                            line += matrix_page.matrix_C[i][j] + " "
                        }
                        textArea.append(line)
                    }
                }
            }
        }
    }

    Rectangle {
        id: mat_B
        radius: 5
        anchors.left: mat_B_X.right
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.bottom: parent.verticalCenter
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 20
        color: "#ffffff"
        clip: true
        ScrollBar.vertical: ScrollBar {
            id: mat_B_bar
            policy: ScrollBar.AlwaysOn
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }
        property int elem_x: 0
        property int elem_y: 0
        Flickable {
            anchors.fill: parent
            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
            contentHeight: gw_B.height
            contentWidth: gw_B.width
            GridView {
                id: gw_B
                property int elem_width: 70
                property int elem_height: 50

                ScrollBar.vertical: mat_B_bar
                cacheBuffer: 5000
                clip: true
                width: elem_width * mat_B.elem_y
                height: mat_B.height

                model: ListModel {
                    id: mat_B_Elems
                }

                delegate: TextField {
                    property int x_c: tmp_x
                    property int y_c: tmp_y
                    width: gw_B.elem_width
                    height: gw_B.elem_height
                    placeholderText: '0'
                    text: txt
                    cursorPosition: pos
                    onTextEdited: matrix_page.matrix_B[x_c][y_c] = text
                }
                cellWidth: elem_width
                cellHeight: elem_height
            }
        }
    }

    Button {
        id: clear_A
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.verticalCenter
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: clear_A
            onClicked: {
                mat_A.elem_x = 0
                mat_A.elem_y = 0
                mat_A_Elems.clear()
                mat_A_X.text = ""
                mat_A_Y.text = ""
            }
        }

        text: qsTr("Очистить")
    }

    Button {
        id: mat_swap
        height: 35
        width: 70
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        font.pointSize: 11
        anchors.topMargin: 20
        Connections {
            target: mat_swap
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0 && mat_B.elem_x > 0
                        && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.swap_matrix(matrix_page.matrix_A, matrix_page.matrix_B)
                } else {
                    quick_error("Can't swap empty matrixes")
                }
            }
        }

        text: qsTr("swap")
    }

    Button {
        id: mat_mult
        x: 296
        height: 35
        width: 70
        anchors.top: mat_dif.bottom
        topPadding: 12
        font.pointSize: 19
        anchors.topMargin: 10
        anchors.left: mat_dif.left
        Connections {
            target: mat_mult
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0 && mat_B.elem_x > 0
                        && mat_B.elem_y) {
                    matrix_page.wait()
                    Core.mult_matrix(matrix_page.matrix_A, matrix_page.matrix_B)
                } else {
                    quick_error("Matrix sizes cannot be 0")
                }
            }
        }

        text: qsTr("*")
    }

    Button {
        id: mat_dif
        height: 35
        width: 70
        anchors.top: mat_sum.bottom
        topPadding: 2
        font.pointSize: 16
        anchors.topMargin: 10
        anchors.left: mat_sum.left
        Connections {
            target: mat_dif
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0 && mat_B.elem_x > 0
                        && mat_B.elem_y) {
                    matrix_page.wait()
                    Core.dif_matrix(matrix_page.matrix_A, matrix_page.matrix_B)
                } else {
                    quick_error("Matrix sizes cannot be 0")
                }
            }
        }
        text: qsTr("-")
    }

    Button {
        id: mat_sum
        height: 35
        width: 70
        anchors.top: mat_swap.bottom
        font.pointSize: 14
        anchors.topMargin: 10
        anchors.left: mat_swap.left
        Connections {
            target: mat_sum
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0 && mat_B.elem_x > 0
                        && mat_B.elem_y) {
                    matrix_page.wait()
                    Core.sum_matrix(matrix_page.matrix_A, matrix_page.matrix_B)
                } else {
                    quick_error("Matrix sizes cannot be 0")
                }
            }
        }
        text: qsTr("+")
    }

    Button {
        id: mat_solve
        height: 35
        width: 70
        anchors.top: mat_mult.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.left: mat_mult.left

        Connections {
            target: mat_solve
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0 && mat_B.elem_x > 0
                        && mat_B.elem_y) {
                    matrix_page.wait()
                    Core.solve_matrix(matrix_page.matrix_A,
                                      matrix_page.matrix_B)
                } else {
                    quick_error("Matrix sizes cannot be 0")
                }
            }
        }

        text: qsTr("=")
    }

    Button {
        id: mat_A_T
        anchors.left: clear_A.right
        anchors.leftMargin: 10
        anchors.top: parent.verticalCenter
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_T
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.transpose_matrix(matrix_page.matrix_A, 0)
                } else {
                    quick_error("Can't transpose empty matrix")
                }
            }
        }

        text: qsTr("Транспонировать")
    }

    Button {
        id: mat_A_M
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: clear_A.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_M
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.mult_matrix_on_num(matrix_page.matrix_A,
                                            mat_A_M_N.text, 0)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }

        text: qsTr("Умножить на")
    }

    Button {
        id: mat_A_P
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: mat_A_M.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_P
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.pow_matrix_in_num(matrix_page.matrix_A,
                                           mat_A_P_N.text, 0)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Возвести в")
    }

    Button {
        id: mat_A_D
        anchors.left: mat_A_I.right
        anchors.leftMargin: 10
        anchors.right: mat_A_T.right
        anchors.top: mat_A_P_N.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_D
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.determinant(matrix_page.matrix_A)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Определитель")
    }

    Button {
        id: mat_A_R
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: mat_A_I.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_R
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.matrix_rang(matrix_page.matrix_A)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }

        text: qsTr("Ранг")
    }

    Button {
        id: mat_A_I
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: mat_A_P.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_A_I
            onClicked: {
                if (mat_A.elem_x > 0 && mat_A.elem_y > 0) {
                    matrix_page.wait()
                    Core.matrix_inv(matrix_page.matrix_A)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Обратная")
    }

    Button {
        id: mat_C_A
        width: implicitWidth
        height: implicitHeight
        anchors.right: mat_C_C.left
        anchors.rightMargin: 20
        anchors.top: mat_C_C.top
        font.pointSize: 11
        text: qsTr("to A")
        Connections {
            target: mat_C_A
            onClicked: {
                if (mat_C.elem_x > 0 && mat_C.elem_y > 0) {
                    changeItems_A(matrix_page.matrix_C, mat_C.elem_x,
                                  mat_C.elem_y)
                } else {
                    quick_error("Matrix C is empty")
                }
            }
        }
    }

    Button {
        id: mat_C_B
        width: implicitWidth
        height: implicitHeight
        anchors.left: mat_C_C.right
        anchors.leftMargin: 20
        anchors.bottom: mat_C_C.bottom
        font.pointSize: 11
        Connections {
            target: mat_C_B
            onClicked: {
                if (mat_C.elem_x > 0 && mat_C.elem_y > 0) {
                    changeItems_B(matrix_page.matrix_C, mat_C.elem_x,
                                  mat_C.elem_y)
                } else {
                    quick_error("Matrix C is empty")
                }
            }
        }
        text: qsTr("to B")
    }

    Button {
        id: mat_C_C
        width: implicitWidth
        height: implicitHeight
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        font.pointSize: 11
        anchors.bottomMargin: 20
        Connections {
            target: mat_C_C
            onClicked: {
                mat_C_Elems.clear()
                mat_C.elem_x = 0
                mat_C.elem_y = 0
            }
        }

        text: qsTr("Очистить")
    }

    TextField {
        id: mat_A_X
        width: 60
        height: 35
        anchors.top: parent.top
        font.pointSize: 11
        anchors.topMargin: 20
        anchors.right: mat_swap.left
        anchors.rightMargin: 15
        placeholderText: qsTr("X")
        validator: RegularExpressionValidator {
            regularExpression: /[0-9]{4}/
        }

        Connections {
            target: mat_A_X
            onTextEdited: generateItems_A()
        }
    }

    TextField {
        id: mat_A_Y
        width: 60
        height: 35
        anchors.top: mat_A_X.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.right: mat_swap.left
        anchors.rightMargin: 15
        validator: RegularExpressionValidator {
            regularExpression: /[0-9]{4}/
        }
        Connections {
            target: mat_A_Y
            onTextEdited: generateItems_A()
        }
        placeholderText: qsTr("Y")
    }

    TextField {
        id: mat_B_X
        width: 60
        height: 35
        anchors.top: parent.top
        horizontalAlignment: Text.AlignRight
        font.pointSize: 11
        anchors.topMargin: 20
        anchors.left: mat_swap.right
        anchors.leftMargin: 15
        validator: RegularExpressionValidator {
            regularExpression: /[0-9]{4}/
        }
        Connections {
            target: mat_B_X
            onTextEdited: generateItems_B()
        }
        placeholderText: qsTr("X")
    }

    TextField {
        id: mat_B_Y
        width: 60
        height: 35
        anchors.top: mat_B_X.bottom
        horizontalAlignment: Text.AlignRight
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.left: mat_swap.right
        anchors.leftMargin: 15
        Connections {
            target: mat_B_Y
            onTextEdited: generateItems_B()
        }
        placeholderText: qsTr("Y")
    }

    TextField {
        id: mat_A_M_N
        height: mat_A_M.height
        anchors.left: mat_A_M.right
        anchors.leftMargin: 10
        anchors.right: mat_A_T.right
        anchors.top: mat_A_T.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        placeholderText: qsTr("Множитель")
    }

    TextField {
        id: mat_A_P_N
        height: mat_A_P.height
        anchors.left: mat_A_P.right
        anchors.leftMargin: 10
        anchors.right: mat_A_T.right
        anchors.top: mat_A_M_N.bottom
        rightPadding: 10
        leftPadding: 10
        font.pointSize: 11
        anchors.topMargin: 10
        placeholderText: qsTr("Степень")
    }

    Button {
        id: clear_B
        height: implicitHeight
        anchors.right: mat_B_T.left
        anchors.rightMargin: 10
        anchors.top: parent.verticalCenter
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: clear_B
            onClicked: {
                mat_B_Elems.clear()
                mat_B.elem_x = 0
                mat_B.elem_y = 0
                mat_B_X.text = ""
                mat_B_Y.text = ""
            }
        }
        text: qsTr("Очистить")
    }

    Button {
        id: mat_B_T
        width: implicitWidth
        height: implicitHeight
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.verticalCenter
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_B_T
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.transpose_matrix(matrix_page.matrix_B, 1)
                } else {
                    quick_error("Can't transpose empty matrix")
                }
            }
        }

        text: qsTr("Транспонировать")
    }

    Button {
        id: mat_B_M
        height: implicitHeight
        anchors.left: clear_B.left
        anchors.top: clear_B.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_B_M
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.mult_matrix_on_num(matrix_page.matrix_B,
                                            mat_B_M_N.text, 1)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Умножить на")
    }

    Button {
        id: mat_B_P
        height: implicitHeight
        anchors.left: mat_B_M.left
        anchors.top: mat_B_M.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_B_P
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.pow_matrix_in_num(matrix_page.matrix_B,
                                           mat_B_P_N.text, 1)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Возвести в")
    }

    Button {
        id: mat_B_D
        height: implicitHeight
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: mat_B_P_N.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.left: mat_B_I.right
        anchors.leftMargin: 10
        Connections {
            target: mat_B_D
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.determinant(matrix_page.matrix_B)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Определитель")
    }

    Button {
        id: mat_B_R
        width: implicitWidth
        height: mat_B_M.height
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: mat_B_D.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_B_R
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.matrix_rang(matrix_page.matrix_B)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }
        text: qsTr("Ранг")
    }

    Button {
        id: mat_B_I
        height: implicitHeight
        anchors.left: mat_B_M.left
        anchors.top: mat_B_P.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        Connections {
            target: mat_B_I
            onClicked: {
                if (mat_B.elem_x > 0 && mat_B.elem_y > 0) {
                    matrix_page.wait()
                    Core.matrix_inv(matrix_page.matrix_B)
                } else {
                    quick_error("Matrix size cannot be 0")
                }
            }
        }

        text: qsTr("Обратная")
    }

    TextField {
        id: mat_B_M_N
        height: mat_B_M.height
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: mat_B_T.bottom
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.left: mat_B_M.right
        anchors.leftMargin: 10
        placeholderText: qsTr("Множитель")
    }

    TextField {
        id: mat_B_P_N
        height: mat_B_M.height
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: mat_B_M_N.bottom
        rightPadding: 10
        leftPadding: 10
        font.pointSize: 11
        anchors.topMargin: 10
        anchors.left: mat_B_P.right
        anchors.leftMargin: 10
        placeholderText: qsTr("Степень")
    }

    Button {
        id: change
        width: implicitWidth
        height: implicitHeight
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        font.pointSize: 11
        anchors.bottomMargin: 20
        text: qsTr("Калькулятор")
        // @disable-check M222
        onClicked: matrix_page.changeMode()
    }

    Flickable {
        id: flickable
        visible: false
        anchors.fill: parent
        anchors.margins: 19
        boundsMovement: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }
        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOn
        }
        contentHeight: textArea.height
        contentWidth: textArea.width
        clip: true

        TextArea {
            id: textArea
            clip: true
            verticalAlignment: Text.AlignTop
            font.pointSize: 11
            width: Math.max(flickable.width, textArea.implicitWidth)
            height: Math.max(flickable.height, textArea.implicitHeight)
            readOnly: true
        }
    }
    Button {
        id: close_text
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 27
        visible: false
        text: qsTr("Закрыть")
        Connections {
            target: close_text
            onClicked: {
                flickable.visible = false
                close_text.visible = false
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

