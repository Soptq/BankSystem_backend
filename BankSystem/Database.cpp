//
//  Database.cpp
//  BankSystem
//
//  Created by Soptq on 2019/6/28.
//  Copyright © 2019 Soptq. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>

#include "Database.h"
#include "md5.h"

using namespace std;

Database::Database(){
    mysql_init(&mysql);
}

Database::~Database(){
    mysql_close(connection);
}

/**
 *  随机生成一个 n 位数字字符
 **/

string Database::generateID(int n = 6){
    string output;
//    cout << "time=" << (unsigned)clock() << endl;
    srand((unsigned)clock());
    for (int i = 0; i < n; ++i) {
        output += (char)(rand() % 10 + 48);
    }
    return output;
}

/**
 *  加密密码的程序，未完成
 **/

string Database::encrypt(std::string password){
//    cout << password << endl;
//    cout << MD5(password).toStr() << endl;
    return MD5(password).toStr();
}

bool Database::initConnection(std::string username, std::string password, std::string host, unsigned int port){
    connection = mysql_real_connect(&mysql, host.c_str(), username.c_str(), password.c_str(), "bank_data", port, 0, 0);
    if (connection == NULL){
        cout << mysql_error(&mysql) << endl;
        return false;
        // return tables;
    }else{
//        cout << "Successfully connected to the database" << endl;
        state = mysql_query(connection, "SHOW TABLES");
        if (state != 0){
            cout << mysql_error(connection) << endl;
            return false;
        }
        result = mysql_store_result(connection);
        bool hasBaseUserTable = false, hasUserTable = false, hasManagerTable = false, hasAppealTable = false,  hasCardTable = false, hasLoanTable = false,
            hasLoanAppealTable = false;
        while ( (row = mysql_fetch_row(result)) != NULL ){
            string temp = row[0];
            if (temp == "base_user_table") {
                hasBaseUserTable = true;
                continue;
            }
            if (temp == "user_table") {
                hasUserTable = true;
                continue;
            }
            if (temp == "manager_table") {
                hasManagerTable = true;
                continue;
            }
            if (temp == "appeal_table") {
                hasAppealTable = true;
                continue;
            }
            if (temp == "card_table") {
                hasCardTable = true;
                continue;
            }
            if (temp == "loan_table") {
                hasLoanTable = true;
                continue;
            }
            if (temp == "loan_appeal_table") {
                hasLoanAppealTable = true;
                continue;
            }
        }
        mysql_free_result(result);
        if (!hasBaseUserTable) {
            state = mysql_query(connection, "CREATE TABLE `base_user_table` (`user_id` varchar(255) DEFAULT NULL,`password` varchar(255) DEFAULT NULL,`is_user` int(255) DEFAULT NULL);");
            if (state != 0){
                cout << mysql_error(connection) << endl;
                return false;
            }else {
                command = "INSERT INTO `bank_data`.`base_user_table`(`user_id`, `password`, `is_user`) VALUES ('000001', '" + encrypt("123456") + "', 0);";
                state = mysql_query(connection, command.c_str());
                if (state != 0) {
                    cout << mysql_error(connection) << endl;
                    return false;
                }
            }
        }
        if (!hasUserTable) {
            state = mysql_query(connection, "CREATE TABLE `user_table` (`user_id` varchar(255) DEFAULT NULL,`name` varchar(255) DEFAULT NULL,`gender` varchar(255) DEFAULT NULL,`cid` varchar(255) DEFAULT NULL,`phone` varchar(255) DEFAULT NULL,`email` varchar(255) DEFAULT NULL,`address` varchar(255) DEFAULT NULL,`zip` varchar(255) DEFAULT NULL,`credit` int(255) DEFAULT NULL,`deposit` double(255,4) DEFAULT NULL,`reviewed` int(255) DEFAULT NULL);");
        }
        if (!hasManagerTable) {
            state = mysql_query(connection, "CREATE TABLE `manager_table` (`user_id` varchar(255) DEFAULT NULL,`name` varchar(255) DEFAULT NULL,`gender` varchar(255) DEFAULT NULL,`cid` varchar(255) DEFAULT NULL,`phone` varchar(255) DEFAULT NULL,`email` varchar(255) DEFAULT NULL,`permission` int(255) DEFAULT NULL);");
            if (state != 0) {
                cout << mysql_error(connection) << endl;
                return false;
            } else {
                state = mysql_query(connection, "INSERT INTO `bank_data`.`manager_table`(`user_id`, `name`, `gender`, `cid`, `phone`, `email`, `permission`) VALUES ('000001', 'Soptq', 'male', '000001', '100000', 'admin@admin.org', 5);");
                if (state != 0) {
                    cout << mysql_error(connection) << endl;
                    return false;
                }
            }
        }
        if (!hasAppealTable) {
            state = mysql_query(connection, "CREATE TABLE `appeal_table` (`id` varchar(255) DEFAULT NULL,`content` varchar(255) DEFAULT NULL,`userid` varchar(255) DEFAULT NULL);");
            if (state != 0) {
                cout << mysql_error(connection) << endl;
                return false;
            }
        }
        if (!hasCardTable) {
            state = mysql_query(connection, "CREATE TABLE `card_table` (`userid` varchar(255) DEFAULT NULL,`cardnum` varchar(255) DEFAULT NULL,`isloss` int(255) DEFAULT NULL);");
            if (state != 0) {
                cout << mysql_error(connection) << endl;
                return false;
            }
        }
        if (!hasLoanTable) {
            state = mysql_query(connection, "CREATE TABLE `loan_table` (`id` varchar(255) DEFAULT NULL,`userid` varchar(255) DEFAULT NULL,`loan_amount` varchar(255) DEFAULT NULL,`date` varchar(255) DEFAULT NULL,`interest` double(255,0) DEFAULT NULL);");
            if (state != 0) {
                cout << mysql_error(connection) << endl;
                return false;
            }
        }
        if (!hasLoanAppealTable) {
            state = mysql_query(connection, "CREATE TABLE `loan_appeal_table` (`loan_id` varchar(255) DEFAULT NULL,`userid` varchar(255) DEFAULT NULL,`amount` varchar(255) DEFAULT NULL);");
            if (state != 0) {
                cout << mysql_error(connection) << endl;
                return false;
            }
        }
        return true;
    }
}


bool Database::query(std::string command){
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    }
    return true;
}


/**
 * 为数据库添加普通用户的接口
 **/

string Database::addUser(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string address, std::string zip){
    // generate fake id
    string id = generateID();
    // check if this id is used
    do {
        string command = "SELECT * FROM base_user_table WHERE user_id = '" + id + "';";
        state = mysql_query(connection, command.c_str());
        if (state != 0) {
            cout << mysql_error(connection) << endl;
            return NULL;
        } else {
            result = mysql_store_result(connection);
            if (mysql_num_rows(result) == 0) {
                break;
            }
            mysql_free_result(result);
        }
    } while(true);
    // insert this user to base-user-table
    // cout << id << endl;
    command = "INSERT INTO `bank_data`.`base_user_table`(`user_id`, `password`, `is_user`) VALUES ('" + id + "', '" + encrypt(password) + "', 1);";
//    cout << command << endl;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return NULL;
    } else {
//        cout << "successfully insert into base_user_table" << endl;
    }
    // insert this user to user-table
    command = "INSERT INTO `bank_data`.`user_table`(`user_id`, `name`, `gender`, `cid`, `phone`, `email`, `address`, `zip`, `credit`, `deposit`, `reviewed`) VALUES ('" + id + "', '" + name + "', '" + gender + "', '" + cid + "', '" + phone + "', '" + email + "', '" + address + "', '" + zip + "', 100, 0, 0)";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return NULL;
    } else {
//        cout << "successfully insert into user_table" << endl;
    }
    return id;
}


string Database::addManager(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string permission){
    // generate fake id
    string id = generateID();
    // check if this id is used
    do {
        string command = "SELECT * FROM base_user_table WHERE user_id = '" + id + "';";
        state = mysql_query(connection, command.c_str());
        if (state != 0) {
            cout << mysql_error(connection) << endl;
            return NULL;
        } else {
            result = mysql_store_result(connection);
            if (mysql_num_rows(result) == 0) {
                break;
            }
            mysql_free_result(result);
        }
    } while(true);
    // insert this user to base-user-table
    command = "INSERT INTO `bank_data`.`base_user_table`(`user_id`, `password`, `is_user`) VALUES ('" + id + "', '" + encrypt(password) + "', 0);";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return NULL;
    } else {
//        cout << "successfully insert into base_user_table" << endl;
    }
    // insert this user to manager-table
    command = "INSERT INTO `bank_data`.`manager_table`(`user_id`, `name`, `gender`, `cid`, `phone`, `email`, `permission`) VALUES ('" + id + "', '" + name + "', '" + gender + "', '" + cid + "', '" + phone + "', '" + email + "', " + permission + ");";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return NULL;
    } else {
//        cout << "successfully insert into user_table" << endl;
    }
    return id;
}


bool Database::addToAppealTable(std::string userid, std::string content){
    // generate fake id
    string id = generateID();
    // check if this id is used
    do {
        string command = "SELECT * FROM appeal_table WHERE id = '" + id + "';";
        state = mysql_query(connection, command.c_str());
        if (state != 0) {
            cout << mysql_error(connection) << endl;
            return false;
        } else {
            result = mysql_store_result(connection);
            if (mysql_num_rows(result) == 0) {
                break;
            }
            mysql_free_result(result);
        }
    } while(true);
    command = "INSERT INTO `bank_data`.`appeal_table`(`id`, `content`, `userid`) VALUES ('" + id + "', '" + content + "', '" + userid + "');";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::addToLoanAppeal(std::string userid, std::string amount){
    // generate fake id
    string id = generateID();
    do {
        string command = "SELECT * FROM loan_table WHERE id = '" + id + "';";
        state = mysql_query(connection, command.c_str());
        if (state != 0) {
            cout << mysql_error(connection) << endl;
            return false;
        } else {
            result = mysql_store_result(connection);
            if (mysql_num_rows(result) == 0) {
                break;
            }
            mysql_free_result(result);
        }
    } while(true);
    command = "INSERT INTO `bank_data`.`loan_appeal_table`(`loan_id`, `userid`, `amount`) VALUES ('" + id + "', '" + userid + "', '" + amount + "');";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::addToLoan(std::string loanid, std::string interest){
    command = "SELECT * FROM `bank_data`.`loan_appeal_table` WHERE `loan_id` = '" + loanid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        ostringstream os;
        os << clock();
        istringstream is(os.str());
        string time;
        is >> time;
        command = "INSERT INTO `bank_data`.`loan_table`(`id`, `userid`, `loan_amount`, `date`, `interest`) VALUES ('" + loanid + "', '" + row[1] + "', '" + row[2] + "', '" + time + "', " + interest + ");";
        state = mysql_query(connection, command.c_str());
        if (state != 0) {
            cout << mysql_error(connection) << endl;
            return false;
        } else {
            return depositeByUser(row[1], row[2]);
        }
    }
}

bool Database::addCard(std::string userid, std::string card_num){
    command = "INSERT INTO `bank_data`.`card_table`(`userid`, `cardnum`, `isloss`) VALUES ('" + userid + "', '" + card_num + "', 0)";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else return true;
}


bool Database::deleteUserByString(std::string condition, std::string value){
    command = "DELETE FROM `bank_data`.`user_table` WHERE `" + condition + "` = '" + value +"'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
//        cout << "successfully delete the user" << endl;
    }
    return true;
}

bool Database::deleteUserByInt(std::string condition, std::string value){
    command = "DELETE FROM `bank_data`.`user_table` WHERE `" + condition + "` = " + value +"";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
//        cout << "successfully delete the user" << endl;
    }
    return true;
}

bool Database::deleteUserByid(std::string userid){
    return deleteUserByString("user_id", userid);
}

bool Database::deleteManagerByString(std::string condition, std::string value) {
    command = "DELETE FROM `bank_data`.`manager_table` WHERE `" + condition + "` = '" + value +"'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
//        cout << "successfully delete the manager" << endl;
    }
    return true;
}

bool Database::deleteManagerByInt(std::string condition, std::string value) {
    command = "DELETE FROM `bank_data`.`manager_table` WHERE `" + condition + "` = " + value +"";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
//        cout << "successfully delete the manager" << endl;
    }
    return true;
}

bool Database::deleteManagerByid(std::string userid){
    return deleteManagerByString("user_id", userid);
}


bool Database::deleteByid(std::string userid){
    if (isManager(userid)) {
        return deleteManagerByid(userid);
    } else {
        return deleteUserByid(userid);
    }
}



string Database::getPassword(std::string userid){
    command = "SELECT * FROM `bank_data`.`base_user_table` WHERE `user_id` = '" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return NULL;
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        return row[1];
    }
}


bool Database::deleteInfoByid(std::string userid, std::string condition){
    command = "UPDATE `bank_data`.`user_table` SET `" + condition + "` = '' WHERE `user_id` = ‘" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::deleteFromAppealTable(std::string thingid){
    command = "DELETE FROM `bank_data`.`appeal_table` WHERE `id` = '" + thingid + "'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::deleteCard(std::string userid, std::string cardnum){
    command = "DELETE FROM `bank_data`.`card_table` WHERE `userid` = '" + userid + "' AND `cardnum` = '" + cardnum + "'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::deleteAppeal(std::string appealid){
    command = "DELETE FROM `bank_data`.`appeal_table` WHERE `id` = '" + appealid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::deleteLoanAppeal(std::string loanid){
    command = "DELETE FROM `bank_data`.`loan_appeal_table` WHERE `loan_id` = '" + loanid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::deleteLoan(std::string loanid){
    command = "DELETE FROM `bank_data`.`loan_table` WHERE `id` = '" + loanid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::isManager(std::string userid){
    command = "SELECT * FROM base_user_table WHERE user_id = '" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        result = mysql_store_result(connection);
        if (mysql_num_rows(result) == 0){
            cout << "No Result" << endl;
            return false;
        }
        if (strcmp(mysql_fetch_row(result)[2], "0") == 0) {
            mysql_free_result(result);
            return true;
        } else {
            mysql_free_result(result);
            return false;
        }
    }
}


User* Database::getUserByPassword(std::string userid, std::string password){
    command = "SELECT * FROM base_user_table WHERE user_id = '" + userid + "'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new User();
    } else {
        result = mysql_store_result(connection);
        if (mysql_num_rows(result) == 0){
            cout << "No Result" << endl;
            return new User();
        }
        row = mysql_fetch_row(result);
        mysql_free_result(result);
//        cout << "encrpt= " << encrypt(password) << endl;
//        cout << row[1] << endl;
        if (strcmp(encrypt(password).c_str(), row[1]) == 0) {
            // password matched
            return searchUserById(userid);
        } else {
            return new User();
        }
    }
}

Manager* Database::getManagerByPassword(std::string userid, std::string password){
    command = "SELECT * FROM base_user_table WHERE user_id = '" + userid + "'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new Manager();
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        if (strcmp(encrypt(password).c_str(), row[1]) == 0) {
            // password matched
            return searchManagerById(userid);
        } else {
            return new Manager();
        }
    }
}


vector<User*> Database::searchUserByString(std::string condition, std::string value){
    vector<User*> output;
    command = "SELECT * FROM `bank_data`.`user_table` WHERE `" + condition + "` = '" + value +"'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new User(row[0], "", row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[9], row[8], row[11]));
        }
        mysql_free_result(result);
        return output;
    }
}


vector<User*> Database::searchUserByInt(std::string condition, std::string value){
    vector<User*> output;
    command = "SELECT * FROM `bank_data`.`user_table` WHERE `" + condition + "` = " + value;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new User(row[0], "", row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[9], row[8], row[11]));
        }
        mysql_free_result(result);
        return output;
    }
}


vector<User*> Database::searchUserByName(std::string uname){
    return searchUserByString("name", uname);
}

vector<User*> Database::searchUserByCid(std::string ucid){
    return searchUserByString("cid", ucid);
}

vector<User*> Database::searchUserByPhone(std::string uphone){
    return searchUserByString("phone", uphone);
}

vector<User*> Database::searchUserByEmail(std::string uemail){
    return searchUserByString("email", uemail);
}

User* Database::searchUserById(std::string userid){
    command = "SELECT * FROM `bank_data`.`user_table` WHERE `user_id` = " + userid;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new User();
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        User* output = new User(row[0], "", row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[9], row[8], row[11]);
        mysql_free_result(result);
        return output;
    }
}

Manager* Database::searchManagerById(std::string userid){
    command = "SELECT * FROM `bank_data`.`manager_table` WHERE `user_id` = " + userid;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new Manager();
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        Manager* output = new Manager(row[0], "", row[1], row[2], row[3], row[4], row[5], row[6]);
        mysql_free_result(result);
        return output;
    }
}

vector<string> Database::searchCardByUserid(std::string userid){
    vector<string> output;
    command = "SELECT * FROM `bank_data`.`card_table` WHERE `userid` = " + userid;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(row[1]);
        }
        mysql_free_result(result);
        return output;
    }
}


vector<User*> Database::searchReviewUsers(){
    return searchUserByInt("reviewed", "0");
}


vector<Loss*> Database::searchLoss(){
    vector<Loss*> output;
    command = "SELECT * FROM `bank_data`.`card_table` WHERE `isloss` = 1;";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new Loss(row[0], row[1]));
        }
        mysql_free_result(result);
        return output;
    }
}

vector<Appeal*> Database::searchAppeal(){
    vector<Appeal*> output;
    command = "SELECT * FROM `bank_data`.`appeal_table`;";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new Appeal(row[0], row[2], row[1]));
        }
        mysql_free_result(result);
        return output;
    }
}

vector<LoanAppeal*> Database::searchLoanAppeal(){
    vector<LoanAppeal*> output;
    command = "SELECT * FROM `bank_data`.`loan_appeal_table`;";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new LoanAppeal(row[0], row[1], row[2]));
        }
        mysql_free_result(result);
        return output;
    }
}

vector<LoanAppeal*> Database::searchLoanAppealById(std::string userid){
    vector<LoanAppeal*> output;
    command = "SELECT * FROM `bank_data`.`loan_appeal_table` WHERE `userid` = '" + userid + "';";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new LoanAppeal(row[0], row[1], row[2]));
        }
        mysql_free_result(result);
        return output;
    }
}


LoanAppeal* Database::searchLoanAppealByLoanId(std::string loanid){
    vector<LoanAppeal*> output;
    command = "SELECT * FROM `bank_data`.`loan_appeal_table` WHERE `loan_id` = '" + loanid + "';";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new LoanAppeal("","","");
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        return new LoanAppeal(row[0], row[1], row[2]);
    }
}

vector<Loan*> Database::searchLoan(){
    vector<Loan*> output;
    command = "SELECT * FROM `bank_data`.`loan_table`;";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new Loan(row[0], row[1], row[2], row[3], row[4]));
        }
        mysql_free_result(result);
        return output;
    }
}

vector<Loan*> Database::searchLoanByID(std::string userid){
    vector<Loan*> output;
    command = "SELECT * FROM `bank_data`.`loan_table` WHERE ``userid` = '" + userid + "';";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return output;
    } else {
        result = mysql_store_result(connection);
        while ((row = mysql_fetch_row(result)) != NULL) {
            output.push_back(new Loan(row[0], row[1], row[2], row[3], row[4]));
        }
        mysql_free_result(result);
        return output;
    }
}

Loan* Database::searchLoanByLoanId(std::string loanid){
    command = "SELECT * FROM `bank_data`.`loan_table` WHERE ``id` = '" + loanid + "';";
    state =  mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return new Loan("","","","","");
    } else {
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
        mysql_free_result(result);
        return new Loan(row[0], row[1], row[2], row[3], row[4]);
    }
}



bool Database::updateDeposite(std::string userid, std::string amount, bool isDeposite){
    if (isDeposite) {
        command = "UPDATE `bank_data`.`user_table` SET `deposit` = `deposit` + " + amount + " WHERE `user_id` = '" + userid + "';";
    } else {
        command = "UPDATE `bank_data`.`user_table` SET `deposit` = `deposit` - " + amount + " WHERE `user_id` = '" + userid + "';";
    }
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::depositeByUser(std::string userid, std::string amount){
    return updateDeposite(userid, amount, true);
}

bool Database::withdrawByUser(std::string userid, std::string amount){
    return updateDeposite(userid, amount, false);
}

bool Database::updateInfoByString(std::string userid, std::string condition, std::string value) {
    command = "UPDATE `bank_data`.`user_table` SET `" + condition + "` = '" + value + "' WHERE `user_id` = '" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::updateInfoByInt(std::string userid, std::string condition, std::string value) {
    command = "UPDATE `bank_data`.`user_table` SET `" + condition + "` = " + value + " WHERE `user_id` = '" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::cardReportLoss(std::string cardnum) {
    command = "UPDATE `bank_data`.`card_table` SET `isloss` = 1 WHERE `cardnum` = '" + cardnum + "'";
//    cout << command << endl;
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::revertCardReportLoss(std::string cardnum){
    command = "UPDATE `bank_data`.`card_table` SET `isloss` = 0 WHERE `cardnum` = '" + cardnum + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

bool Database::checkedUserProfile(std::string userid){
    return updateInfoByInt(userid, "reviewed", "1");
}

bool Database::uncheckedUserProfile(std::string userid){
    return updateInfoByInt(userid, "reviewed", "0");
}

bool Database::changePasswordbyId(std::string userid, std::string password){
    command = "UPDATE `bank_data`.`base_user_table` SET `password` = " + encrypt(password) + " WHERE `user_id` = '" + userid + "';";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}


bool Database::updateLossCardNum(std::string userid, std::string old_cardnum, std::string new_card_num) {
    command = "UPDATE `bank_data`.`card_table` SET `cardnum` = '" + new_card_num + "', `isloss` = 0 WHERE `userid` = '" + userid + "' AND `cardnum` = '" + old_cardnum + "'";
    state = mysql_query(connection, command.c_str());
    if (state != 0) {
        cout << mysql_error(connection) << endl;
        return false;
    } else {
        return true;
    }
}

