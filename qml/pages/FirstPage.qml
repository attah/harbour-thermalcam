import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.KeepAlive 1.2
import thermalcam.thermalimage 1.0

Page {
    id: page

    allowedOrientations: Orientation.Landscape

    backgroundColor: "black"

    DisplayBlanking {
        id: displayBlanking
        preventBlanking: parent.visible
    }

    ThermalImage {
        id: thermal
        anchors.fill: parent
    }

    IconButton
    {
        icon.source: "image://theme/icon-m-dot"
        icon.width: Theme.iconSizeLarge
        icon.height: Theme.iconSizeLarge
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        onClicked: thermal.save();
        anchors.rightMargin: Theme.iconSizeLarge
    }

}
