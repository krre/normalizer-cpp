#include "Account.h"
#include "external/network/controller/account/Account.h"

namespace Qml {

Account::Account() {
    m_account.reset(new Controller::Account(restApi()));
}

Account::~Account() {

}

void Account::create(const QString& login, const QString& email, const QString& fullName, const QString& password) {
    createImpl(login, email, fullName, password);
}

void Account::login(const QString& email, const QString& password) {
    loginImpl(email, password);
}

Async::Task<void> Account::createImpl(const QString& login, const QString& email, const QString& fullName, const QString& password) {
    Controller::Account::Request::Create params;
    params.login = login;
    params.email = email;
    params.fullName = fullName;
    params.password = password;

    try {
        Controller::Account::Response::Token response = co_await m_account->create(params);
        emit created(response.token);
    } catch (RestException& e) {
        QString message = e.status() == RestStatus::Conflict ? tr("Account already exists") : e.message();
        emit errorOccured(e.status(), message);
    }
}

Async::Task<void> Account::loginImpl(const QString& email, const QString& password) {
    Controller::Account::Request::Login params;
    params.email = email;
    params.password = password;

    try {
        Controller::Account::Response::Token response = co_await m_account->login(params);
        emit logined(response.token);
    } catch (RestException& e) {
        QString message = e.message();

        if (e.status() == RestStatus::NotFound) {
            message = tr("Email not found");
        } else if (e.status() == RestStatus::Unauthorized) {
            message = tr("Wrong password");
        }

        emit errorOccured(e.status(), message);
    }
}

}
