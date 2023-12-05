#pragma once
#include "ui/dialog/StandardDialog.h"
#include "core/async/Task.h"

namespace Controller {
    class Account;
}

class QLineEdit;

class RegisterAccountDialog : public StandardDialog {
public:
    RegisterAccountDialog(Controller::Account* account);
    QString token() const;

public slots:
    void accept() override;

private:
    QLineEdit* m_loginLineEdit = nullptr;
    QLineEdit* m_fullNameLineEdit = nullptr;
    QLineEdit* m_emailLineEdit = nullptr;
    QLineEdit* m_passwordLineEdit = nullptr;
    QLineEdit* m_confirmPasswordLineEdit = nullptr;

private slots:
    void enableOkButton();
    Async::Task<void> getToken();

private:
    Controller::Account* m_account = nullptr;
    QString m_token;
};
