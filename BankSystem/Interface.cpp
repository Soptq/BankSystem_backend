//
//  Interface.cpp
//  BankSystem
//
//  Created by Soptq on 2019/6/29.
//  Copyright © 2019 Soptq. All rights reserved.
//


#include <iostream>
#include <vector>
#include <sstream>
#include "Interface.hpp"
#include "User.h"

using namespace std;

Interface::Interface(){
    db.initConnection("root", "jplpFDetz3KF8Vy", "127.0.0.1", 3306);
}

string Interface::signUpNewUser(string password, string name, string gender, string cid, string phone, string email, string address, string zip){
    cout << phone << endl;
    return db.addUser(password, name, gender, cid, phone, email, address, zip);
}

bool Interface::isManager(std::string userid){
    return db.isManager(userid);
}

UserInterface::UserInterface(){
}

UserInterface::UserInterface(User muser){
    if (db.isManager(muser.id_account)) {
        cout << "The userid you input is not vaild" << endl;
    } else {
        user = muser;
    }
}


UserInterface::~UserInterface(){
//    db.~Database();
}

void UserInterface::changeUser(User muser){
    if (db.isManager(muser.id_account)) {
        cout << "The userid you input is not vaild" << endl;
    } else {
        user = muser;
    }
}



void UserInterface::showUser(){
    cout << user.id_account << " " << user.name << endl;
}

bool UserInterface::login(std::string userid, std::string password){
    User tempUser = *db.getUserByPassword(userid, password);
    if (tempUser.id_account == "") {
        return false;
    }else {
        user = tempUser;
        return true;
    }
}

bool UserInterface::depositeMoney(string amount){
    if (user.id_account != "") {
        if (db.depositeByUser(user.id_account, amount)){
            user.depositeAmount += std::atof(amount.c_str());
            return true;
        } else return false;
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::withdrawMoney(string amount){
    if (user.id_account != "") {
        if (db.withdrawByUser(user.id_account, amount)) {
            user.depositeAmount -= std::atof(amount.c_str());
            return true;
        } else return false;
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::updatePhoneInfo(std::string value){
    if (user.id_account != "") {
        if (db.updateInfoByString(user.id_account, "phone", value)) {
            user.phone_number = value;
            return true;
        } else return false;
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::updateEmailInfo(std::string value){
    if (user.id_account != "") {
        if (db.updateInfoByString(user.id_account, "email", value)) {
            user.email_address = value;
            return true;
        } else return false;
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}


bool UserInterface::updateAddressInfo(std::string value){
    if (user.id_account != "") {
        if (db.updateInfoByString(user.id_account, "address", value)) {
            user.home_address = value;
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}


bool UserInterface::updateZipInfo(std::string value){
    if (user.id_account != "") {
        if (db.updateInfoByString(user.id_account, "zip", value)) {
            user.zip_code = value;
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::deletePhoneInfo() {
    if (user.id_account != "") {
        if (db.deleteInfoByid(user.id_account, "phone")) {
            user.phone_number = "";
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::deleteEmailInfo(){
    if (user.id_account != "") {
        if (db.deleteInfoByid(user.id_account, "email")) {
            user.email_address = "";
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::deleteAddressInfo(){
    if (user.id_account != "") {
        if (db.deleteInfoByid(user.id_account, "address")) {
            user.home_address = "";
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::needReview(){
    if (user.id_account != "") {
        return db.uncheckedUserProfile(user.id_account);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::addCard(std::string card_num){
    if (user.id_account != "") {
        return db.addCard(user.id_account, card_num);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

std::vector<std::string> UserInterface::getAllCards() {
    if (user.id_account != "") {
        return db.searchCardByUserid(user.id_account);
    } else {
        cout << "No User Selected" << endl;
        return *new vector<string>;
    }
}

bool UserInterface::removeCard(std::string card_num){
    if (user.id_account != "") {
        return db.deleteCard(user.id_account, card_num);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::deleteZipInfo(){
    if (user.id_account != "") {
        if (db.deleteInfoByid(user.id_account, "zip")) {
            user.zip_code = "";
            return false;
        } else {
            return true;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::appeal(std::string content){
    if (user.id_account != ""){
        return db.addToAppealTable(user.id_account, content);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::reportLoss(std::string cardnum){
    if (user.id_account != "") {
        return db.cardReportLoss(cardnum);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::revertReportLoss(std::string cardnum){
    if (user.id_account != ""){
        return db.revertCardReportLoss(cardnum);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::changePassword(std::string new_password){
    if (user.id_account != "") {
        return db.changePasswordbyId(user.id_account, new_password);
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}


bool UserInterface::deleteUser(){
    if (user.id_account != "") {
        if (user.depositeAmount < 5 &&  db.deleteUserByid(user.id_account)) {
            user.id_account = "";
            user.password = "";
            user.name = "";
            user.gender = "";
            user.cid = "";
            user.phone_number = "";
            user.email_address = "";
            user.home_address = "";
            user.zip_code = "";
            user.creditLevel = 0;
            user.depositeAmount = 0;
            user.reviewed = 1;
            return true;
        } else {
            return false;
        }
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}

bool UserInterface::applyLoan(std::string amount){
    if (user.id_account == "") {
        cout << "NO User Selected" << endl;
        return new User;
    } else {
        return db.addToLoanAppeal(user.id_account, amount);
    }
}

std::vector<LoanAppeal*> UserInterface::checkLoanAppeal(){
    if (user.id_account == "") {
        cout << "NO User Selected" << endl;
        return *new vector<LoanAppeal*>;
    } else {
        return db.searchLoanAppealById(user.id_account);
    }
}

std::vector<Loan*> UserInterface::checkLoan(){
    if (user.id_account == "") {
        cout << "NO User Selected" << endl;
        return *new vector<Loan*>;
    } else {
        return db.searchLoanByID(user.id_account);
    }
}

bool UserInterface::payLoan(std::string loanid){
    if (user.id_account == "") {
        cout << "No User Selected" << endl;
        return false;
    } else {
        if (stof(db.searchLoanByLoanId(loanid)->amount) <= user.depositeAmount) {
            db.withdrawByUser(user.id_account, db.searchLoanByLoanId(loanid)->amount);
            db.deleteLoan(loanid);
            user.depositeAmount -= stof(db.searchLoanByLoanId(loanid)->amount);
            return true;
        } else return false;
    }
}

bool UserInterface::transferMoney(std::string userid, std::string amount) {
    if (user.id_account != "") {
        if (db.withdrawByUser(user.id_account, amount) && db.depositeByUser(userid, amount)) {
            user.depositeAmount -= std::atof(amount.c_str());
            return true;
        } else return false;
    } else {
        cout << "No User Selected" << endl;
        return false;
    }
}



User* UserInterface::getUser(){
    if (user.id_account == "") {
        cout << "NO User Selected" << endl;
        return new User;
    } else {
        return &user;
    }
}

ManagerInterface::ManagerInterface(){
}

ManagerInterface::ManagerInterface(Manager muser){
    if (db.isManager(muser.id_account)) {
        manager = muser;
    } else {
        cout << "The user you input is not vaild" << endl;
    }
}


ManagerInterface::~ManagerInterface(){
    
}


void ManagerInterface::changeManager(Manager muser){
    if (db.isManager(muser.id_account)) {
        manager = muser;
    } else {
        cout << "The user you input is not vaild" << endl;
    }
}

string ManagerInterface::signupNewManager(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, int permission) {
    string perm;
    stringstream ss;
    ss << permission;
    ss >> perm;
    return db.addManager(password, name, gender, cid, phone, email, perm);
}



void ManagerInterface::showManager(){
    cout << manager.id_account << " " << manager.name << endl;
}

bool ManagerInterface::login(std::string userid, std::string password){
    Manager tempManager = *db.getManagerByPassword(userid, password);
    if (tempManager.id_account == "") {
        return false;
    }else {
        manager = tempManager;
        return true;
    }
}


vector<User*> ManagerInterface::getNewAccount(){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return *new vector<User*>;
    } else {
        return db.searchReviewUsers();
    }
}

bool ManagerInterface::verifyNewAccount(std::string userid){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return false;
    } else {
        return db.checkedUserProfile(userid);
    }
}

std::vector<Loss*> ManagerInterface::getLoss(){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return *new vector<Loss*>;
    } else {
        return db.searchLoss();
    }
}


bool ManagerInterface::processReport_Loss(std::string userid, std::string old_card_num, std::string new_card_num) {
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return false;
    } else {
        return db.updateLossCardNum(userid, old_card_num, new_card_num);
    }
}

std::vector<Appeal*> ManagerInterface::getAppeal(){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return *new vector<Appeal*>;
    } else {
        return db.searchAppeal();
    }
}

bool ManagerInterface::processAppeal(std::string appealid) {
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return false;
    } else {
        return db.deleteAppeal(appealid);
    }
}

Manager* ManagerInterface::getManager(){
    if (manager.id_account == "") {
        cout << "NO Manager Selected" << endl;
        return new Manager;
    } else {
        return &manager;
    }
}

std::vector<LoanAppeal*> ManagerInterface::getLoanAppeals(){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return *new vector<LoanAppeal*>;
    } else {
        return db.searchLoanAppeal();
    }
}

bool ManagerInterface::approveLoanAppeals(std::string loanid, std::string interest){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return false;
    } else {
        if (db.addToLoan(loanid, interest)) {
            db.deleteLoanAppeal(loanid);
            return true;
        } else return false;
    }
}

bool ManagerInterface::deleteUser(std::string userid){
    if (manager.id_account == "") {
        cout << "No Manager Selected" << endl;
        return false;
    } else {
        return db.deleteUserByid(userid);
    }
}
