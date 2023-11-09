#include "ActionBuilder.h"
#include "MainWindow.h"
#include "project/Project.h"
#include "core/Constants.h"
#include "widget/Menu.h"
#include "widget/Action.h"
#include "dialog/PreferencesDialog.h"
#include "dialog/account/RegisterAccountDialog.h"
#include "dialog/account/LoginDialog.h"
#include "manager/settings/FileSettingsStorage.h"
#include "manager/network/HttpNetworkManager.h"
#include <QtWidgets>

ActionBuilder::ActionBuilder(const Parameters& parameters) :
        QObject(parameters.mainWindow),
        m_mainWindow(parameters.mainWindow),
        m_project(parameters.project),
        m_httpNetworkManager(parameters.httpNetworkManager),
        m_fileSettingsStorage(parameters.fileSettingsStorage) {
    QMenuBar* menuBar = m_mainWindow->menuBar();

    auto fileMenu = new Menu(tr("File"), menuBar);
    menuBar->addMenu(fileMenu);

    fileMenu->addBindableAction(tr("Close"), Qt::CTRL | Qt::Key_W, m_project, &Project::close)->enabled().setBinding([this] { return m_project->opened().value(); });
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Exit"), Qt::CTRL | Qt::Key_Q, m_mainWindow, &MainWindow::close);

    auto editMenu = new Menu(tr("Edit"), menuBar);
    menuBar->addMenu(editMenu);

    editMenu->addAction(tr("Preferences..."), this, &ActionBuilder::openPreferencesDialog);

    auto accountMenu = menuBar->addMenu(tr("Account"));
    accountMenu->addAction(tr("Register"), this, &ActionBuilder::openRegisterAccountDialog);
    accountMenu->addAction(tr("Login"), this, &ActionBuilder::openLoginDialog);
    accountMenu->addAction(tr("Logout"), this, &ActionBuilder::logout);

    auto helpMenu = menuBar->addMenu(tr("Help"));
    helpMenu->addAction(tr("About %1...").arg(Const::App::Name), this, &ActionBuilder::about);
}

void ActionBuilder::openPreferencesDialog() {
    PreferencesDialog preferencesDialog(m_fileSettingsStorage);
    preferencesDialog.exec();
}

void ActionBuilder::openLoginDialog() {
    LoginDialog loginDialog(m_httpNetworkManager);

    if (loginDialog.exec() == QDialog::Accepted) {
        m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(loginDialog.token()));
    }
}

void ActionBuilder::openRegisterAccountDialog() {
    RegisterAccountDialog registerAccountDialog(m_httpNetworkManager);

    if (registerAccountDialog.exec() == QDialog::Accepted) {
        m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(registerAccountDialog.token()));
    }
}

void ActionBuilder::logout() {
    m_fileSettingsStorage->setAccount(FileSettingsStorage::Account(""));

    QStringList arguments = QCoreApplication::arguments();
    arguments.removeAt(0); // Remove application name
    QProcess::startDetached(QCoreApplication::applicationFilePath(), arguments);
    qApp->quit();
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
