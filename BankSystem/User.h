//
//  BaseUser.h
//  BankSystem
//
//  Created by Soptq on 2019/6/28.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef User_h
#define User_h

#include <iostream>

class BaseUser{
public:
    std::string id_account;
    std::string password;
    std::string name;
    std::string gender;
    std::string cid;
    std::string phone_number;
    std::string email_address;
};

class User : public BaseUser{
public:
    double depositeAmount;//存款金额
    int creditLevel;//信用等级
    int reviewed;
    std::string home_address;
    std::string zip_code;
    
    User();
    User(std::string userid, std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string address, std::string zip, std::string deposite, std::string credit, std::string ureviewed);
    User(std::string upassword, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string address, std::string zip);
    ~User();
};

class Manager : public BaseUser{
public:
    int permission;//权限
    Manager();
    Manager(std::string userid, std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string upermission);
    Manager(std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string upermission);
    ~Manager();
};

#endif /* User_h */
