import QtQuick 2.5
import "../../../js/utils.js" as Utils

FileDialogBase {
    title: qsTr("Choose Directory")
    selectFolder: true
    nameFilters: []
}
