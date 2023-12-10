#include <QtQuick>

#include <sailfishapp.h>
#include "thermalimage.h"

int main(int argc, char *argv[])
{
    QGuiApplication* app = SailfishApp::application(argc, argv);

    app->setOrganizationName(QStringLiteral("net.attah"));
    app->setApplicationName(QStringLiteral("thermalcam"));

    qmlRegisterType<ThermalImage>("thermalcam.thermalimage", 1, 0, "ThermalImage");

    QQuickView* view = SailfishApp::createView();

    view->engine()->addImportPath(SailfishApp::pathTo("qml/pages").toString());
    view->setSource(SailfishApp::pathToMainQml());

    view->show();
    return app->exec();

}
