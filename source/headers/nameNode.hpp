//
//  nameNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#ifndef nameNode_hpp
#define nameNode_hpp

#include <sgNode.hpp>

class NameNode: public SGNode {
    
public:
    NameNode(char const * name): SGNode(name) {};
    NameNode() : SGNode("default") {};
};
#endif /* nameNode_hpp */
