//
//  modelNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#ifndef modelNode_hpp
#define modelNode_hpp

#include <stdio.h>
#include <model.hpp>
#include <sgNode.hpp>

class ModelNode : public SGNode {
protected:
    Model model;
    
public:
    ModelNode(char const * name, Model m);
    virtual void draw();
    
};

#endif /* modelNode_hpp */
