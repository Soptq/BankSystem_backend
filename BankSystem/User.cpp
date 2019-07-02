//
//  User.cpp
//  BankSystem
//
//  Created by Soptq on 2019/6/28.
//  Copyright © 2019 Soptq. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <sstream>


#include "User.h"
//#include "Database.h"


using namespace std;

User::User(){
    id_account = "";
    password = "";
    name = "";
    gender = "";
    cid = "";
    phone_number = "";
    email_address = "";
    home_address = "";
    zip_code = "";
    creditLevel = 0;
    depositeAmount = 0;
    reviewed = 1;
}

User::User(std::string userid, std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string address, std::string zip, std::string deposite, std::string credit, std::string ureviewed){
    id_account = userid;
    password = upassword;
    name = uname;
    gender = ugender;
    cid = ucid;
    phone_number = phone;
    email_address = email;
    home_address = address;
    zip_code = zip;
    creditLevel = atoi(credit.c_str());
    istringstream iss(deposite);
    iss >> depositeAmount;
    istringstream isd(ureviewed);
    isd >> reviewed;
}

User::User(std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string address, std::string zip){
    password = upassword;
    name = uname;
    gender = ugender;
    cid = ucid;
    phone_number = phone;
    email_address = email;
    home_address = address;
    zip_code = zip;
}

User::~User(){
}


Manager::Manager(){
    id_account = "";
    password = "";
    name = "";
    gender = "";
    cid = "";
    phone_number = "";
    email_address = "";
    permission = 0;
}

Manager::Manager(std::string userid, std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string upermission){
    id_account = userid;
    password = upassword;
    name = uname;
    gender = ugender;
    cid = ucid;
    phone_number = phone;
    email_address = email;
    istringstream iss(upermission);
    iss >> permission;
}

Manager::Manager(std::string upassword, std::string uname, std::string ugender, std::string ucid, std::string phone, std::string email, std::string upermission){
    password = upassword;
    name = uname;
    gender = ugender;
    cid = ucid;
    phone_number = phone;
    email_address = email;
    istringstream iss(upermission);
    iss >> permission;
}

Manager::~Manager(){
}
