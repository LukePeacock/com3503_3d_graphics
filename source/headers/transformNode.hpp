//
//  transformNode.hpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef transformNode_hpp
#define transformNode_hpp

#include <stdio.h>
#include <sgNode.hpp>
#include <glm/glm.hpp>

class TransformNode: public SGNode {

private:
    glm::mat4 transform;
    
protected:
    
    
public:
    TransformNode(char const * name, glm::mat4 t);
    void setTransform(glm::mat4 t);
    void print(int indent, bool inFull);
    virtual void update(glm::mat4 t);
    glm::mat4 getTransform();
};
#endif /* transformNode_hpp */
