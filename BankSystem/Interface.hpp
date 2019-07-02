//
//  Interface.hpp
//  BankSystem
//
//  Created by Soptq on 2019/6/29.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

#include "Database.h"
#include "User.h"
#include "Loss.h"
#include "Loan.h"

class Interface{
public:
    Database db;
    std::string signUpNewUser(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, std::string address, std::string zip); //创建新用户, 传入 密码， 姓名， 性别， 身份证号， 手机号， 电子邮箱号， 地址， 邮编。返回值为一个string， 如果为 NULL 则表示操作数据库失败，否则返回生成的用户 id 。
    bool isManager(std::string userid); // 传入一个 userid， 返回一个 bool ，真表示这个人是 manager， 假表示这个人不是 manager。
    Interface();
    ~Interface(){};
};

class UserInterface : public Interface {
private:
    User user;
public:
    UserInterface(); //构造函数，这个构造函数只能占位，不能实现任何功能。可以调用 login 函数使用id和密码进行初始化
    UserInterface(std::string userid, std::string password);
    UserInterface(User muser); //标准构造函数，初始化当前操作对象，传入一个 User 对象
    ~UserInterface();
    void changeUser(User muser); //切换当前用户，传入一个 User 对象
    void showUser();
    bool needReview(); //调用这个函数使该用户需要再次审核。
    bool login(std::string userid, std::string password); //登陆函数。若账号密码正确，则会自动初始化 User，返回一个 bool，表示是否登陆成功。
    bool depositeMoney(std::string amount);//存款，传入一个存款数值。返回值是一个 bool， 表示数据库操作是否成功，
    bool withdrawMoney(std::string amount);//取款，传入一个取款数值。返回值是一个 bool，表示数据库操作是否成功。
    bool addCard(std::string cardnum); //为该用户绑定一张银行卡，传入银行卡号。返回值为一个 bool， 表示数据库操作是否成功。
    bool removeCard(std::string cardnum); //为该用户解绑一个银行l卡号，传入银行卡号。返回值是一个 bool， 表示数据库操作是否成功。
    std::vector<std::string> getAllCards(); //获取该用户的所有银行卡号，返回值是一个b包含了每个银行卡字符串的 vector。
    bool updatePhoneInfo(std::string value);//增加手机信息，传入一个字符串手机号。返回值是一个 bool， 表示数据库操作是否成功。
    bool updateEmailInfo(std::string value);//增加邮箱信息，传入一个字符串邮箱。返回值是一个 bool， 表示数据库操作是否成功。
    bool updateAddressInfo(std::string value);//增加地址信息，传入一个字符串地址。返回值是一个 bool， 表示数据库操作是否成功。
    bool updateZipInfo(std::string value);//增加邮编信息，传入一个字符串地址。返回值是一个 bool， 表示数据库操作是否成功。
    bool deletePhoneInfo();//删除手机信息，返回值是一个 bool， 表示数据库操作是否成功。
    bool deleteEmailInfo();//删除邮箱信息,返回值是一个 bool， 表示数据库操作是否成功。
    bool deleteAddressInfo();//删除地址信息,返回值是一个 bool， 表示数据库操作是否成功。
    bool deleteZipInfo();//删除邮编信息,返回值是一个 bool， 表示数据库操作是否成功。
    bool reportLoss(std::string cardnum);//挂失，传入需要挂失的银行卡卡号。返回值是一个 bool， 表示数据库操作是否成功。
    bool revertReportLoss(std::string cardnum); //撤销挂失，传入需要撤销挂失的银行卡号.返回值是一个 bool， 表示数据库操作是否成功。
    bool changePassword(std::string new_password);//修改密码,传入新密码。返回值是一个 bool， 表示数据库操作是否成功。
    bool appeal(std::string content);//申诉，传入申述内容，返回值是一个 bool， 表示数据库操作是否成功。
    bool deleteUser();//注销账户，从数据库彻底删除整个用户。
    bool applyLoan(std::string amount);
    std::vector<LoanAppeal*> checkLoanAppeal();
    std::vector<Loan*> checkLoan();
    bool payLoan(std::string loanid);
    bool transferMoney(std::string userid, std::string amount);
    
    User* getUser();
};

class ManagerInterface : public Interface {
private:
    Manager manager;
public:
    ManagerInterface();
    ManagerInterface(Manager muser);
    ~ManagerInterface();
    void showManager();
    void changeManager(Manager muser);
    std::string signupNewManager(std::string password, std::string name, std::string gender, std::string cid, std::string phone, std::string email, int permission);
    bool login(std::string userid, std::string password); //登陆函数。若账号密码正确，则会自动初始化 Manager，返回一个 bool，表示是否登陆成功。
    std::vector<User*> getNewAccount();//获取需要审核的新账户, 返回值是一个包含 User 指针的 vector， 里面的所有用户都是需要审核的。
    bool verifyNewAccount(std::string userid); //传入一个 id， 表示管理员通过了对于这个id的审核。
    std::vector<Loss*> getLoss(); //获取目前所有挂失的新账户,返回值是一个装有 Loss 指针的 vector。
    bool processReport_Loss(std::string userid, std::string old_card_num, std::string new_card_num);//处理挂失信息,传入用户 id， 用户挂失卡号，新卡卡号，将为用户替换。传回一个 bool， 说明数据库操作有没有成功。
    std::vector<Appeal*> getAppeal();//获取目前所有申述的信息,返回值是一个装有 Loss 指针的 vector。
    bool processAppeal(std::string appealid);//处理挂失,当申述处理完成后 传入申述id，将此申述从表中删除。传回一个 bool， 说明数据库操作有没有成功。
    std::vector<LoanAppeal*> getLoanAppeals();
    bool approveLoanAppeals(std::string loanid, std::string interest);
    Manager* getManager(); //获取当前管理员的权限等级。
    bool deleteUser(std::string userid);
};

#endif /* Interface_hpp */
