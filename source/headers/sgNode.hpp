//
//  sgNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
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
    virtual const char* classname();
  
public:
    SGNode(char const * name);
    void addChild(SGNode &child);
    virtual void update();
    void print(int indent, bool inFull);
    virtual void draw();
    virtual void update(glm::mat4 t);
    
    

};
#endif /* sgNode_hpp */
