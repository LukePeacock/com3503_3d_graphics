//
//  transformNode.cpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#include "transformNode.hpp"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


//Default Constructor
TransformNode::TransformNode() : SGNode("Default Transform Node"){
    transform = glm::mat4(1.0f);
}

TransformNode::TransformNode(char const * name, glm::mat4 t) : SGNode(name)
{
    transform = t;
}

void TransformNode::setTransform(glm::mat4 t)
{
    transform = t;
}

void TransformNode::update(glm::mat4 t)
{
    worldTransform = t;
    t = worldTransform * transform;
    for(int i = 0; i < children.size(); i ++)
    {
        children.at(i)->update(t);
    }
}

void TransformNode::print(int indent, bool inFull)
{
    std::cout << getIndentString(indent) << "Name: " <<name;
    if (inFull) {
      std::cout << "\nworldTransform";
      std::cout << "\n" << glm::to_string(worldTransform);
      std::cout << "\ntransform node:";
      std::cout << "\n" << glm::to_string(transform);
    }
    for (int i=0; i<children.size(); i++) {
      children.at(i)->print(indent+1, inFull);
    }
}


glm::mat4 TransformNode::getTransform(){
    return transform;
}
