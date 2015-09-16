#include "mainwindow.h"
#include "osgwidget.h"
#include "version.h"
#include "../settings.h"
#include <QtCore/QRect>
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLineEdit>

extern QSharedPointer<Settings> settings;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Greenery");
    setMinimumSize(160, 160);

    OsgWidget* osgWidget = new OsgWidget(this, Qt::Widget, osgViewer::CompositeViewer::SingleThreaded);
    setCentralWidget(osgWidget);

    createMenus();
    loadSettings();
}

void MainWindow::newFile() {
    qDebug() << "new";
}

void MainWindow::open() {
    qDebug() << "open";
}

void MainWindow::quitApp() {
    close();
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Greenery"),
            QString("<h3>Greenery %1</h3>Build date: %2<br>Copyright (c) 2015, Vladimir Zarypov").arg(Version::full()).arg(__DATE__));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(tr("New"), this, SLOT(newFile()), Qt::CTRL + Qt::Key_N);
    fileMenu->addAction(tr("Open..."), this, SLOT(open()), Qt::CTRL + Qt::Key_O);
    fileMenu->addSeparator();
    fileMenu->addAction(tr("Quit"), this, SLOT(about()), Qt::CTRL + Qt::Key_Q);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(tr("About..."), this, SLOT(about()));
    helpMenu->addAction(tr("About Qt..."), this, SLOT(aboutQt()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    saveSettings();
}

void MainWindow::saveSettings()
{
    QMap<QString, int> map;
    map["x"] = x();
    map["y"] = y();
    map["width"] = width();
    map["height"] = height();
    ::settings.data()->setGeometry(map);
}

void MainWindow::loadSettings()
{
    QMap<QString, int>map = ::settings.data()->getGeometry();
    if (map.isEmpty()) {
        // move window to center screen
        auto *screen = QGuiApplication::primaryScreen();
        auto screenSize = screen->size();
        int width = 800;
        int height = 600;
        int x = (screenSize.width() - width) / 2;
        int y = (screenSize.height() - height) / 2;
        setGeometry(x, y, width, height);
    } else {
        setGeometry(map["x"], map["y"], map["width"], map["height"]);
    }
}


