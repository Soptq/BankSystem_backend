//
//  Loan.h
//  BankSystem
//
//  Created by Soptq on 2019/6/30.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef Loan_h
#define Loan_h


class Loan{
public:
    std::string loanid;
    std::string userid;
    std::string amount;
    std::string date;
    std::string interest;
    
    
    Loan(std::string mloanid, std::string muserid, std::string mamount, std::string mdate, std::string minterest){
        loanid = mloanid;
        userid = muserid;
        amount = mamount;
        date = mdate;
        interest = minterest;
    }
};

class LoanAppeal{
public:
    std::string loanid;
    std::string userid;
    std::string amount;
    
    
    LoanAppeal(std::string mloanid, std::string muserid, std::string mamount){
        loanid = mloanid;
        userid = muserid;
        amount = mamount;
    }
};

#endif /* Loan_h */
