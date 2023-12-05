#include "ui/dialog/account/AccountDialog.h"
#include "tests/common/TestAccount.h"
#include <QTest>
#include <QLineEdit>

constexpr auto Login = "admin";
constexpr auto Email = "admin@example.com";
constexpr auto FullName = "Admin";

class TestAccountDialog : public QObject {
    Q_OBJECT
private slots:
    void getData();
    void updateData();
};

void TestAccountDialog::getData() {
    TestAccount account;
    account.m_getAccount.login = Login;
    account.m_getAccount.email = Email;
    account.m_getAccount.fullName = FullName;

    AccountDialog accountDialog(&account);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    QTest::keyClick(&accountDialog, Qt::Key_Backtab);

    QLineEdit* emailLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    QTest::keyClick(&accountDialog, Qt::Key_Backtab);

    QLineEdit* loginLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());

    accountDialog.accept();

    QCOMPARE(account.m_getAccount.fullName, fullNameLineEdit->text());
    QCOMPARE(account.m_getAccount.email, emailLineEdit->text());
    QCOMPARE(account.m_getAccount.login, loginLineEdit->text());
}

void TestAccountDialog::updateData() {
    TestAccount account;
    AccountDialog accountDialog(&account);

    QLineEdit* fullNameLineEdit = static_cast<QLineEdit*>(accountDialog.focusWidget());
    fullNameLineEdit->setText(FullName);

    QTest::keyClick(&accountDialog, Qt::Key_Tab);

    accountDialog.accept();

    QCOMPARE(account.m_updateAccount.fullName, FullName);
}

QTEST_MAIN(TestAccountDialog)

#include "tst_account.moc"
