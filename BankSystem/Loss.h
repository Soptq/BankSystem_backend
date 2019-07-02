//
//  Loss.h
//  BankSystem
//
//  Created by Soptq on 2019/6/29.
//  Copyright © 2019 Soptq. All rights reserved.
//

#ifndef Loss_h
#define Loss_h

class Loss{
public:
    std::string userid;
    std::string cardnum;
    Loss(std::string muserid, std::string mcardnum){
        userid = muserid;
        cardnum = mcardnum;
    }
};

#endif /* Loss_h */
