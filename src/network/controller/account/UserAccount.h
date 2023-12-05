#pragma once
#include "Account.h"

class HttpNetwork;

namespace Controller {

class UserAccount : public Account {
public:
    UserAccount(HttpNetwork* httpNetwork);

    static constexpr auto NAME = "account";

    Async::Task<QString> create(const CreateAccount& account) override;
    Async::Task<void> update(const UpdateAccount& account) override;
    Async::Task<GetAccount> get() override;
    Async::Task<QString> login(const LoginAccount& account) override;
    Async::Task<void> remove() override;
    Async::Task<void> changePassword(const Password& password) override;

private:
    HttpNetwork* m_httpNetwork = nullptr;
};

}
