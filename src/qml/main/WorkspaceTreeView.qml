import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import GreenSilage 1.0
import "../../js/utils.js" as Utils

TreeView {
    id: root
    property string currentPath: projectFileSystemModel.path(selection.currentIndex)
    frameVisible: false
    model: projectFileSystemModel
    rootIndex: projectFileSystemModel.rootIndex
    selection: itemSelectionModel

    onDoubleClicked: Utils.openSprout(projectFileSystemModel.path(index))

    function selectByPath(path) {
        var index = projectFileSystemModel.pathIndex(path)
        selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
    }

    ProjectFileSystemModel {
        id: projectFileSystemModel
        rootDir: Settings.value("Path", "workspace", Core.homePath + "/greensilage")
    }

    ItemSelectionModel {
        id: itemSelectionModel
        model: projectFileSystemModel
    }

    MouseArea {
        z: -1
        anchors.fill: parent
        acceptedButtons: Qt.RightButton
        onPressed:  {
            var index = indexAt(mouseX, mouseY)
            selection.setCurrentIndex(index, ItemSelectionModel.ClearAndSelect)
            if (currentPath) {
                fileMenu.popup()
            }
        }
    }

    Menu {
        id: fileMenu

        MenuItem {
            text: qsTr("Open")
            onTriggered: Utils.openSprout(currentPath)
        }

        MenuItem {
            text: qsTr("Remove")
            onTriggered: {
                var treeIndex = selection.currentIndex
                if (projectFileSystemModel.removeFile(treeIndex)) {
                    var tabIndex = tabView.findTab(projectFileSystemModel.path(treeIndex))
                    if (tabIndex !== -1) {
                        tabView.removeTab(tabIndex)
                    }
                }
            }
        }

        MenuItem {
            text: qsTr("Rename")
        }
    }

    TableViewColumn {
        title: qsTr("Workspace")
        role: "fileName"
        resizable: true
    }
}
