import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Normalizer

Dialog {
    title: qsTr("Sign In")
    anchors.centerIn: parent
    standardButtons: Dialog.Ok | Dialog.Cancel
    modal: true
    closePolicy: Popup.CloseOnEscape

    onVisibleChanged: if (!visible) destroy()

    Account {
        id: account
    }

    ColumnLayout {
        anchors.fill: parent

        TextField {
            id: email
            Layout.fillWidth: true
            placeholderText: qsTr("Email")
            focus: true
        }

        TextField {
            id: password
            Layout.fillWidth: true
            placeholderText: qsTr("Password")
        }
    }
}
