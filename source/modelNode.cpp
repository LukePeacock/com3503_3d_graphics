//
//  modelNode.cpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#include "modelNode.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

//Default constructor
ModelNode::ModelNode() : SGNode("Default Model Node"){
}

ModelNode::ModelNode(char const * name, Model m) : SGNode(name)
{
    model = m;
}

void ModelNode::draw()
{
    //std::cout << "drawing " << name << std::endl;
   // std::cout << glm::to_string(worldTransform) << std::endl;
    model.render(worldTransform);
    for(int i =0 ; i < children.size(); i++)
    {
        children.at(i)->draw();
    }
}
