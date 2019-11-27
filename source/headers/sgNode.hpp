//
//  sgNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#ifndef sgNode_hpp
#define sgNode_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>

class SGNode{
protected:
    char const * name;
    std::vector<SGNode*> children;
    glm::mat4 worldTransform;
    std::string getIndentString(int indent);
  
public:
    SGNode(char const * name);
    void addChild(SGNode &child);
    virtual void update();
    void print(int indent, bool inFull);
    virtual void draw();
    virtual void update(glm::mat4 t);
    
    

};
#endif /* sgNode_hpp */
