#ifndef AUTH_H
#define AUTH_H
#include<string>
class Auth{
    std::string login_url;
    std::string logout_url;
    public:
    Auth();
    void login();
    std::string get_auth_token();
    bool validate_auth_token();
    void logout();
};
#endif