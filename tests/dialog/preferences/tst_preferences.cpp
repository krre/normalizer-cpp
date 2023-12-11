#include "ui/dialog/PreferencesDialog.h"
#include "manager/settings/Settings.h"
#include <QTest>
#include <QLineEdit>

static const QHostAddress Host = QHostAddress(QHostAddress::LocalHost);
constexpr auto Port = 3128;

class TestSettings : public Settings {
public:
    void setMainWindow(const MainWindow& mainWindow [[maybe_unused]]) override {}

    Settings::MainWindow mainWindow() const override {
        return MainWindow();
    }

    bool containsGeometry() const override {
        return true;
    }

    void setServerAddress(const ServerAddress& serverAddress) override {
        m_serverAddress = serverAddress;
    }

    ServerAddress serverAddress() const override {
        return m_serverAddress;
    }

    void setAccount(const Account& account) override {
        m_account = account;
    }

    Account account() const override {
        return m_account;
    }

    ServerAddress m_serverAddress;
    Account m_account;
};

class TestPreferences : public QObject {
    Q_OBJECT
private slots:
    void readSettings();
    void setSettings();
};

void TestPreferences::readSettings() {
    TestSettings settings;
    settings.m_serverAddress = TestSettings::ServerAddress(Host.toString(), Port);

    PreferencesDialog preferencesDialog(&settings);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(hostLineEdit->text(), Host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    QCOMPARE(portLineEdit->text().toInt(), Port);
}

void TestPreferences::setSettings() {
    TestSettings settings;

    PreferencesDialog preferencesDialog(&settings);

    auto hostLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    hostLineEdit->setText(Host.toString());

    QTest::keyClick(&preferencesDialog, Qt::Key_Tab);
    auto portLineEdit = static_cast<QLineEdit*>(preferencesDialog.focusWidget());
    portLineEdit->setText(QString::number(Port));

    preferencesDialog.accept();

    QCOMPARE(settings.m_serverAddress.host, Host.toString());
    QCOMPARE(settings.m_serverAddress.port, Port);
}

QTEST_MAIN(TestPreferences)

#include "tst_preferences.moc"
