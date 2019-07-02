//
//  Database.h
//  BankSystem
//
//  Created by Soptq on 2019/6/28.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <mysql.h>
#include "User.h"
#include "Loss.h"
#include "Appeal.h"
#include "Loan.h"

class Database{
private:
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL *connection, mysql;
    int state;
    std::string command;
public:
    Database();
    ~Database();
    std::string generateID(int n);
    std::string encrypt(std::string password);
    
    bool initConnection(std::string username, std::string password, std::string host, unsigned int port);
    bool query(std::string command);
    // add
    std::string addUser(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string address, std::string zip);
    std::string addManager(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string permission);
    bool addToAppealTable(std::string userid, std::string content);
    bool addToLoanAppeal(std::string userid, std::string amount);
    bool addToLoan(std::string loanid, std::string interest);
    bool addCard(std::string userid, std::string card_num);
    
    // delete
    bool deleteUserByString(std::string condition, std::string value);
    bool deleteUserByInt(std::string condition, std::string value);
    bool deleteUserByid(std::string userid);
    bool deleteManagerByString(std::string condition, std::string value);
    bool deleteManagerByInt(std::string condition, std::string value);
    bool deleteManagerByid(std::string userid);
    bool deleteByid(std::string userid);
    bool deleteInfoByid(std::string userid, std::string condition);
    bool deleteFromAppealTable(std::string thingid);
    bool deleteCard(std::string userid, std::string cardnum);
    bool deleteAppeal(std::string appealid);
    bool deleteLoanAppeal(std::string loanid);
    bool deleteLoan(std::string loanid);
    
    // search
    bool isManager(std::string userid);
    User* getUserByPassword(std::string userid, std::string password);
    Manager* getManagerByPassword(std::string userid, std::string password);
    std::string getPassword(std::string userid);
    std::vector<User*> searchUserByString(std::string condition, std::string value);
    std::vector<User*> searchUserByInt(std::string condition, std::string value);
    std::vector<User*> searchUserByName(std::string uname);
    std::vector<User*> searchUserByCid(std::string ucid);
    std::vector<User*> searchUserByPhone(std::string uphone);
    std::vector<User*> searchUserByEmail(std::string uemail);
    User* searchUserById(std::string userid);
    std::vector<std::string> searchCardByUserid(std::string userid);
    Manager* searchManagerById(std::string userid);
    std::vector<User*> searchReviewUsers();
    std::vector<Loss*> searchLoss();
    std::vector<Appeal*> searchAppeal();
    std::vector<LoanAppeal*> searchLoanAppeal();
    std::vector<LoanAppeal*> searchLoanAppealById(std::string userid);
    LoanAppeal* searchLoanAppealByLoanId(std::string loanid);
    std::vector<Loan*> searchLoan();
    std::vector<Loan*> searchLoanByID(std::string userid);
    Loan* searchLoanByLoanId(std::string loanid);
    
    // update
    bool updateDeposite(std::string userid, std::string amount, bool isDeposite);
    bool depositeByUser(std::string userid, std::string amount);
    bool withdrawByUser(std::string userid, std::string amount);
    bool updateInfoByString(std::string userid, std::string condition, std::string value);
    bool updateInfoByInt(std::string userid, std::string condition, std::string value);
    bool cardReportLoss(std::string cardnum);
    bool revertCardReportLoss(std::string cardnum);
    bool checkedUserProfile(std::string userid);
    bool uncheckedUserProfile(std::string userid);
    bool changePasswordbyId(std::string userid, std::string password);
    bool updateLossCardNum(std::string userid, std::string old_cardnum, std::string new_card_num);
};

#endif /* Database_h */
