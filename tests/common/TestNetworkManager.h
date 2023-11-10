#include "manager/network/NetworkManager.h"

constexpr auto Token = "1234567890";

class TestNetworkManager : public NetworkManager {
public:
    Async::Task<QString> createUser(const User& user) override;;
    Async::Task<User> getUser() override;
    Async::Task<QString> login(const User& user) override;;

    User m_user;
};
