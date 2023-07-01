#include "ActionBuilder.h"
#include "MainWindow.h"
#include "core/Constants.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(MainWindow* mainWindow) : QObject(mainWindow), m_mainWindow(mainWindow) {
    QMenuBar* menuBar = mainWindow->menuBar();

    auto fileMenu = menuBar->addMenu(tr("File"));
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, mainWindow, &MainWindow::close);

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);
}

void ActionBuilder::about() {
    using namespace Const::App;

    QMessageBox::about(m_mainWindow, tr("About %1").arg(Name),
        tr("<h3>%1 %2</h3>"
          "IDE for Norm programming language<br><br>"
          "Based on Qt %3<br>"
          "Build on %4 %5<br><br>"
          "<a href=%6>%6</a><br><br>Copyright © %7, Vladimir Zarypov")
              .arg(Name, Version, QT_VERSION_STR, BuildDate, BuildTime, URL, CopyrightYear));
}
