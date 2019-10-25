//
//  cube.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef cube_hpp
#define cube_hpp

#include <stdio.h>

class Cube {

public:
    float vertices[192] = {
        //Coords                Normals     Tex
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,  0.0f, 0.0f,  // 0      //left bottom back
        -0.5f, -0.5f,  0.5f,  -1, 0, 0,  1.0f, 0.0f,  // 1      //left bottom front
        -0.5f,  0.5f, -0.5f,  -1, 0, 0,  0.0f, 1.0f,  // 2      //left top back
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,  1.0f, 1.0f,  // 3      //left top front
         0.5f, -0.5f, -0.5f,   1, 0, 0,  1.0f, 0.0f,  // 4      //right bottom back
         0.5f, -0.5f,  0.5f,   1, 0, 0,  0.0f, 0.0f,  // 5      //right bottom front
         0.5f,  0.5f, -0.5f,   1, 0, 0,  1.0f, 1.0f,  // 6      //right top back
         0.5f,  0.5f,  0.5f,   1, 0, 0,  0.0f, 1.0f,  // 7      //right top front

        -0.5f, -0.5f, -0.5f,  0,0,-1,  1.0f, 0.0f,  // 8        //left bottom back
        -0.5f, -0.5f,  0.5f,  0,0,1,   0.0f, 0.0f,  // 9        //left bottom front
        -0.5f,  0.5f, -0.5f,  0,0,-1,  1.0f, 1.0f,  // 10       //left top back
        -0.5f,  0.5f,  0.5f,  0,0,1,   0.0f, 1.0f,  // 11       //left top front
         0.5f, -0.5f, -0.5f,  0,0,-1,  0.0f, 0.0f,  // 12       //right bottom back
         0.5f, -0.5f,  0.5f,  0,0,1,   1.0f, 0.0f,  // 13       //right bottom front
         0.5f,  0.5f, -0.5f,  0,0,-1,  0.0f, 1.0f,  // 14       //right top back
         0.5f,  0.5f,  0.5f,  0,0,1,   1.0f, 1.0f,  // 15       //right top front

        -0.5f, -0.5f, -0.5f,  0,-1,0,  0.0f, 0.0f,  // 16       //left bottom back
        -0.5f, -0.5f,  0.5f,  0,-1,0,  0.0f, 1.0f,  // 17       //left bottom front
        -0.5f,  0.5f, -0.5f,  0,1,0,   0.0f, 1.0f,  // 18       //left top back
        -0.5f,  0.5f,  0.5f,  0,1,0,   0.0f, 0.0f,  // 19       //left top front
         0.5f, -0.5f, -0.5f,  0,-1,0,  1.0f, 0.0f,  // 20       //right bottom back
         0.5f, -0.5f,  0.5f,  0,-1,0,  1.0f, 1.0f,  // 21       //right bottom front
         0.5f,  0.5f, -0.5f,  0,1,0,   1.0f, 1.0f,  // 22       //right top back
         0.5f,  0.5f,  0.5f,  0,1,0,   1.0f, 0.0f   // 23       //right top front
    };
    
    unsigned int indices[36] = {  // note that we start from 0!
        0,1,3, // x -ve
        3,2,0, // x -ve
        4,6,7, // x +ve
        7,5,4, // x +ve
        9,13,15, // z +ve
        15,11,9, // z +ve
        8,10,14, // z -ve
        14,12,8, // z -ve
        16,20,21, // y -ve
        21,17,16, // y -ve
        23,22,18, // y +ve
        18,19,23  // y +ve
    };
    
    float * GetVertices();
    unsigned int * GetIndices();
    int GetVertexSize();
    int GetIndicesSize();
    int GetIndicesCount();
};


#endif /* cube_hpp */
