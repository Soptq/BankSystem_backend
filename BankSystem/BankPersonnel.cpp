//
//  BankPersonnel.cpp
//  BankSystem
//
//  Created by Soptq on 2019/6/30.
//  Copyright © 2019 Soptq. All rights reserved.
//

#include <iostream>
#include <vector>

#include "BankPersonnel.hpp"

using namespace std;

BankPersonnel::BankPersonnel() {
    
}

string BankPersonnel::signUp(User user){
    return userInterface.signUpNewUser(user.password, user.name, user.gender, user.cid, user.phone_number, user.email_address, user.home_address, user.zip_code);
}

string BankPersonnel::signup(Manager manager, int permission){
    // 检查是否有管理员登陆。
    if (category == 1 && managerInterface.getManager() -> permission > -1) {
        // 检查注册管理员权限是否低于当前管理员
        if (managerInterface.getManager() -> permission >= permission){
            return managerInterface.signupNewManager(manager.password, manager.name, manager.gender, manager.cid, manager.phone_number, manager.email_address, permission);
        } else {
            cout << "You have no authority to signup a manager that has higher permission than you" << endl;
            return "";
        }
    } else {
        cout << "No Manager selected" << endl;
        return "";
    }
}



int BankPersonnel::login(std::string userid, std::string password){
    if (userInterface.isManager(userid)) {
        // 是管理员
        if(managerInterface.login(userid, password)) {
            category = 1;
            return 1;
        } else {
            return -1;
        }
    } else {
        // 是普通用户
        if (userInterface.login(userid, password)) {
            category = 0;
            return 0;
        } else {
            return -1;
        }
    }
}

bool BankPersonnel::signout(){
    category = -1;
    return true;
}

bool BankPersonnel::setUnreviewed(){
    if (category != 0) {
        cout << "No User Selected" << endl;
        return new User();
    } else {
        return userInterface.needReview();
    }
}


User* BankPersonnel::seeInfo(){
    if (category != 0) {
        cout << "No User Selected" << endl;
        return new User();
    } else {
        return userInterface.getUser();
    }
}


bool BankPersonnel::alterInfo(int ccategory, std::string value){
    if (category != 0){
        cout << "No User Selected" << endl;
        return false;
    } else {
        switch (ccategory) {
            case 1:
                // alter phone
                return userInterface.updatePhoneInfo(value);
            case 2:
                // alter email
                return userInterface.updateEmailInfo(value);
            case 3:
                // alter address
                return userInterface.updateAddressInfo(value);
            case 4:
                // alter zip
                return userInterface.updateZipInfo(value);
            default:
                cout << "please input the right categoty" << endl;
                return false;
        }
    }
}

bool BankPersonnel::depositeMoney(std::string amount){
    if (category != 0) {
        cout << "No User Selected" << endl;
        return false;
    } else {
        return userInterface.depositeMoney(amount);
    }
}

bool BankPersonnel::withdrawMoney(std::string amount){
    if (category != 0) {
        cout << "No User Selected" << endl;
        return false;
    } else {
        if (stof(amount) > userInterface.getUser()->depositeAmount){
            cout << "Not enough deposite" << endl;
            return false;
        }
        return userInterface.withdrawMoney(amount);
    }
}

bool BankPersonnel::tranferMoney(std::string userid, std::string amount){
    if (category != 0) {
        cout << "NO User Selected" << endl;
        return false;
    } else {
        return userInterface.transferMoney(userid, amount);
    }
}

bool BankPersonnel::applyLoan(std::string amount){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.applyLoan(amount);
    }
}

vector<LoanAppeal*> BankPersonnel::seeAllLoanAppeals(){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return *new vector<LoanAppeal*>;
    } else {
        return userInterface.checkLoanAppeal();
    }
}

vector<Loan*> BankPersonnel::seeAllLoans(){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return *new vector<Loan*>;
    } else {
        return userInterface.checkLoan();
    }
}

bool BankPersonnel::payLoan(std::string loanid){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.payLoan(loanid);
    }
}

bool BankPersonnel::bindCard(std::string cardNum){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.addCard(cardNum);
    }
}


bool BankPersonnel::removeCard(std::string cardNum){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.removeCard(cardNum);
    }
}

std::vector<std::string> BankPersonnel::seeAllCard(){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return *new vector<string>;
    } else {
        return userInterface.getAllCards();
    }
}

bool BankPersonnel::reportCardLoss(std::string cardNum){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.reportLoss(cardNum);
    }
}


bool BankPersonnel::revertReportCardLoss(std::string cardNum){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.revertReportLoss(cardNum);
    }
}

bool BankPersonnel::appeal(std::string content){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.appeal(content);
    }
}

bool BankPersonnel::changePassword(std::string newPassword){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.changePassword(newPassword);
    }
}

bool BankPersonnel::deleteUser(){
    if (category != 0) {
        cout << "No User Selectd" << endl;
        return false;
    } else {
        return userInterface.deleteUser();
    }
}

bool BankPersonnel::deleteUser(std::string userid){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return false;
    } else {
        return managerInterface.deleteUser(userid);
    }
}

vector<User*> BankPersonnel::getUnReviewedUser(){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return *new vector<User*>;
    } else {
        return managerInterface.getNewAccount();
    }
}

bool BankPersonnel::approveUnReviewedUser(string userid){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return false;
    } else {
        return managerInterface.verifyNewAccount(userid);
    }
}

vector<Appeal*> BankPersonnel::getAllAppeal(){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return *new vector<Appeal*>;
    } else {
        return managerInterface.getAppeal();
    }
}

bool BankPersonnel::approveAppeal(string appealid){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return false;
    } else {
        return managerInterface.processAppeal(appealid);
    }
}


vector<Loss*> BankPersonnel::getAllLoss(){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return *new vector<Loss*>;
    } else {
        return managerInterface.getLoss();
    }
}

bool BankPersonnel::approveLoss(std::string userid, std::string old_card_num, std::string new_card_num){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return false;
    } else {
        return managerInterface.processReport_Loss(userid, old_card_num, new_card_num);
    }
}

vector<LoanAppeal*> BankPersonnel::getAllLoanAppeal(){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return *new vector<LoanAppeal*>;
    } else {
        return managerInterface.getLoanAppeals();
    }
}

bool BankPersonnel::approveLoanAppeal(std::string loanid, std::string interest){
    if (category != 1) {
        cout << "No Manager Selectd" << endl;
        return false;
    } else {
        return managerInterface.approveLoanAppeals(loanid, interest);
    }
}
