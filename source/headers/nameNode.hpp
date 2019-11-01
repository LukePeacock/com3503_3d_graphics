//
//  nameNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef nameNode_hpp
#define nameNode_hpp

#include <stdio.h>
#include <sgNode.hpp>

class NameNode: public SGNode {
    
public:
    NameNode(char const * name);
};
#endif /* nameNode_hpp */
