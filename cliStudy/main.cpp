//
//  main.cpp
//  cliStudy
//
//  Created by John on 2019/3/13.
//  Copyright © 2019 John. All rights reserved.
//

#include "header.h"

int main(int argc, const char * argv[]) {

    const char * addr = "127.0.0.1";
    
    if (argc == 2) {
        addr = argv[1];
    }
    
//    daytimetcpcli(addr);
//    tcpcli01(addr);
//    tcpcli04(addr);
    tcpcli09(addr);
    
    return 0;
}
