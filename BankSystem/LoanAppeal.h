//
//  Loan.h
//  BankSystem
//
//  Created by Soptq on 2019/6/30.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef Loan_h
#define Loan_h

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
