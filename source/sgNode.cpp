//
//  sgNode.cpp
//  Com3503
//
//  Created by Luke on 01/11/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#include "sgNode.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <iostream>
#include <typeinfo>

SGNode::SGNode(char const * name)
{
    //children implicity initialised in header
    this->name = name;
    worldTransform = glm::mat4(1.0f);
}

void SGNode::addChild(SGNode &child)
{
    
   // std::cout << "adding child " << child.name << " to " << name << std::endl;    //debug output
    this->children.push_back(&child);  //add child to children vector
    
}

void SGNode::update()
{
    update(worldTransform);
}

void SGNode::update(glm::mat4 t)
{
    worldTransform = t;
    for (int i = 0; i < children.size(); i++)
    {
        children.at(i)->update(t);
    }
}

std::string SGNode::getIndentString(int indent)
{
    std::string s = "";
    s.append(std::to_string(indent));
    s.append(" ");
    for(int i = 0; i < indent; i++)
    {
        s += "  ";
    }
    return s;
}

void SGNode::print(int indent, bool inFull)
{
    std::cout << getIndentString(indent) << "Name: " << name << std::endl;;
    if (inFull) {
        std::cout << "worldTransform" << "\n";
        std::cout << glm::to_string(worldTransform) + "\n";
    }
    for (int i=0; i<children.size(); i++) {
      children.at(i)->print(indent+1, inFull);
    }
}

void SGNode::draw()
{
    for (int i = 0; i < children.size(); i ++)
    {
        children.at(i)->draw();
    }
}

