//
//  BankPersonnel.hpp
//  BankSystem
//
//  Created by Soptq on 2019/6/30.
//  Copyright © 2019 Soptq. All rights reserved.
//

/**
 * @Title: BankPersonnel
 *
 * @Description: 数据库调用接口封装
 * @author Soptq sooptq@gmail.com
 * @date  2019/6/30
 * @version V1.0
 */

#ifndef BankPersonnel_hpp
#define BankPersonnel_hpp

#include <stdio.h>
#include "Interface.hpp"

class BankPersonnel {
private:
    UserInterface userInterface;
    ManagerInterface managerInterface;
    int category = -1; //-1 表示当前没有用户登陆，0 表示当前有普通用户登陆， 1 表示当前有管理员登陆
public:
    
    /**
     *  @Description: 初始化整个类
     **/
    
    BankPersonnel();
    
    /**
     * @Description: 普通用户注册函数，传入需要注册的用户对象，返回值是一个 string 是系统为该新注册用户生成的 id 号。如果该 id 号不为空 ，表示普通用户注册是否成功。该函数允许在没有用户登陆的情况下调用。
     *
     * @param user
     * @return id
     *
     **/
    
    std::string signUp(User user);
    
    /**
     * @Description: 管理员用户注册函数，传入需要注册的管理员对象，返回值是一个 string 是系统为该用户生成的 id 号。如果该 id 号不为空，表示管理员用户注册是否成功。该函数在调用的时候必须本身有一个管理员用户已经登陆，且该管理员创建的管理员用户的权限等级不能高于登陆的管理员权限等级。
     *
     * @param manager, permission
     * @return id
     *
     **/
    
    std::string signup(Manager manager, int permission);
    
    /**
     * @Description: 基本登陆模块,返回值是一个 int，为 -1 表示登陆失败，为 0 表示是普通用户， 为 1 表示是管理员用户。
     *
     * @param userid password
     * @return int
     *
     **/
    
    int login(std::string userid, std::string password);
    
    /**
     * @Description: 基本注销模块，注销当前用户。返回值是一个 bool，表示是否注销成功。
     *
     * @param
     * @return bool
     *
     **/
    
    bool signout();
    
    /**
     * @Description: 将当前用户置于需要审核。返回值是一个 bool，表示是否注销成功。只能由登陆的用户执行该函数
     *
     * @param
     * @return bool
     *
     **/
    
    bool setUnreviewed();
    
    /**
     * @Description: 查看当前登陆用户的个人信息。返回值是一个 User 指针类型，若获得信息失败，将返回一个空 User 指针，即 User 对象里没有内容。只有当前登陆用户才能调用这个函数。管理员无法调用。
     *
     * @param
     * @return User
     *
     **/
    
    User* seeInfo();
    
    
    /**
     * @Description: 修改基本内容。设计中一个用户可以修改的个人信息内容只有 phone, email, address 和 zip，传入第一个变量是一个 int 类型的类别，1 表示 phone，2 表示 email，3 表示 address，4 表示 zip， 第二个变量是一个 string 类型的变量，表示修改的内容，可以为空表示删除这项个人信息。这个函数只能由登陆后的用户调用，管理员无法调用。返回值是一个 bool，表示修改是否成功。
     *
     * @param ccategory value
     * @return bool
     *
     **/
    
    bool alterInfo(int ccategory, std::string value);
    
    
    /**
     * @Description: 普通用户的存款功能，传入一个 string 类型的数值，表示为当前普通用户存入数值大小的金额。该函数只能在普通用户登陆后才能调用。管理员无法调用。返回值是一个 bool， 表示存钱是否成功。
     *
     * @param amount
     * @return bool
     *
     **/
    
    bool depositeMoney(std::string amount);
    
    
    /**
     * @Description: 普通用户的取款功能，传入一个 string 类型的数值，表示当前用户取走了数值大小的金额，该函数只能在普通用户登陆后才能被调用。管理员无法调用。返回值是一个 bool，表示取钱是否成功。
     *
     * @param
     * @return bool
     *
     **/
    
    bool withdrawMoney(std::string amount);
    
    /**
     * @Description: 转账模块，传入要转给用户的用户id和金额。返回值是一个 bool，表示是否转账成功。该函数只能由登陆的用户执行，管理员无权执行
     *
     * @param userid, amount
     * @return bool
     *
     **/
    
    bool tranferMoney(std::string userid, std::string amount);
    
    /**
     * @Description: 贷款申请模块，传入需要申请贷款的金额。返回值是一个 bool，表示是否申请成功。
     *
     * @param
     * @return bool
     *
     **/
    
    bool applyLoan(std::string amount);
    
    /**
     * @Description: 查看当前所有正在申请的贷款。返回值是一个 vector<LoanAppeal*>。只能由用户执行，管理员无法调用这个函数。
     *
     * @param
     * @return bool
     *
     **/
    
    std::vector<LoanAppeal*> seeAllLoanAppeals();
    
    /**
     * @Description: 查看当前所有已经申请成功的贷款。返回值是一个 vector<Loan*>。只能由用户执行，管理员无法调用这个函数。
     *
     * @param
     * @return std::vector<Loan*>
     *
     **/
    
    std::vector<Loan*> seeAllLoans();
    
    /**
     * @Description: 偿还一个贷款。传入贷款单号，将自动判断用户的余额是否足够偿还，不够偿还回返回 false，返回值是一个 bool，表示是否偿还成功。函数只能由登陆的用户执行
     *
     * @param loanid
     * @return bool
     *
     **/
    
    bool payLoan(std::string loanid);
    
    
    /**
     * @Description: 绑定银行卡号，传入一个 string 表示需要与该用户绑定的银行卡号。返回值是一个 bool，表示是否绑定成功。函数只能由登陆的用户执行
     *
     * @param cardNum
     * @return bool
     *
     **/
    
    bool bindCard(std::string cardNum);
    
    /**
     * @Description: 解除银行卡绑定，传入一个 string 表示需要与该用户解除绑定绑定的银行卡号。返回值是一个 bool，表示是否解除绑定成功。函数只能由登陆的用户执行
     *
     * @param cardNum
     * @return bool
     *
     **/
    
    bool removeCard(std::string cardNum);
    
    
    /**
     * @Description: 查看该用户名下的所有银行卡。返回值是一个 vector<string>，表示所有银行卡。函数只能由登陆的用户执行
     *
     * @param
     * @return std::vector<std::string>
     *
     **/
    
    std::vector<std::string> seeAllCard();
    
    /**
     * @Description: 挂失银行卡，传入一个 string 表示需要需要挂失的银行卡。返回值是一个 bool，表示是否解除绑定成功。函数只能由登陆的用户执行
     *
     * @param cardNum
     * @return bool
     *
     **/
    
    bool reportCardLoss(std::string cardNum);
    
    
    /**
     * @Description: 解除挂失银行卡，传入一个 string 表示需要需要解除挂失的银行卡。返回值是一个 bool，表示是否解除绑定成功。函数只能由登陆的用户执行
     *
     * @param cardNum
     * @return bool
     *
     **/
    
    bool revertReportCardLoss(std::string cardNum);
    
    
    /**
     * @Description: 申述，传入一个 string 表示申述内容。返回值是一个 bool，表示是否申述成功。函数只能由登陆的用户执行
     *
     * @param content
     * @return bool
     *
     **/
    
    bool appeal(std::string content);
    
    /**
     * @Description: 修改密码，传入一个 string 表示新密码。返回值是一个 bool，表示是否修改成功。函数只能由登陆的用户执行。
     *
     * @param cardNum
     * @return bool
     *
     **/
    
    bool changePassword(std::string newPassword);
    
    
    /**
     * @Description: 注销用户，指彻底从数据库删除用户。返回值是一个 bool，表示是否删除成功。函数只能由登陆的用户执行。
     *
     * @param
     * @return bool
     *
     **/
    
    bool deleteUser();
    
    /**
     * @Description: 注销用户，指彻底从数据库删除用户。传入需要被删除的用户id，返回值是一个 bool，表示是否删除成功。函数只能由登陆的管理员执行。
     *
     * @param userid
     * @return bool
     *
     **/
    
    bool deleteUser(std::string userid);
    
    
    /**
     * @Description: 得到所有的需要审核的用户名单，返回值是一个 std::vector<User*>。函数只能由登陆的管理员执行。
     *
     * @param
     * @return std::vector<User*>
     *
     **/
    
    std::vector<User*> getUnReviewedUser();
    
    /**
     * @Description: 通过目标用户的审核，传入一个 userid，返回是否成功修改数据库。函数只能由登陆的管理员执行。
     *
     * @param userid
     * @return bool
     *
     **/
    
    bool approveUnReviewedUser(std::string userid);
    
    /**
     * @Description: 得到所有的申述，返回值是一个 std::vector<User*>。函数只能由登陆的管理员执行。
     *
     * @param
     * @return std::vector<Appeal*>
     *
     **/
    
    std::vector<Appeal*> getAllAppeal();
    
    /**
     * @Description: 通过目标用户的审核，传入一个 申述单号，返回是否成功修改数据库。函数只能由登陆的管理员执行。
     *
     * @param appealid
     * @return bool
     *
     **/
    
    bool approveAppeal(std::string appealid);
    
    /**
     * @Description: 得到所有的挂失信息，返回值是一个 std::vector<Loss*>。函数只能由登陆的管理员执行。
     *
     * @param
     * @return std::vector<Appeal*>
     *
     **/
    
    std::vector<Loss*> getAllLoss();
    
    /**
     * @Description: 手动给用户换一张新卡，传入 用户id，丢失的卡卡号，新卡卡号，返回是否成功修改数据库。函数只能由登陆的管理员执行。
     *
     * @param userid, old_car_num, new_card_num
     * @return bool
     *
     **/
    
    bool approveLoss(std::string userid, std::string old_card_num, std::string new_card_num);
    
    /**
     * @Description: 得到所有的贷款申请信息，返回值是一个 std::vector<LoanAppeal*>。函数只能由登陆的管理员执行。
     *
     * @param
     * @return std::vector<Appeal*>
     *
     **/
    
    std::vector<LoanAppeal*> getAllLoanAppeal();
    
    /**
     * @Description: 通过用户的贷款申请，传入 申请贷款用户ID，利率，返回是否成功修改数据库。函数只能由登陆的管理员执行。
     *
     * @param userid, old_car_num, new_card_num
     * @return bool
     *
     **/
    
    bool approveLoanAppeal(std::string loanid, std::string interest);
    
    
    
};

#endif /* BankPersonnel_hpp */
