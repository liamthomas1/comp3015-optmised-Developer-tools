#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"
#include "helper/plane.h";
#include "helper/objmesh.h";
#include <glad/glad.h>
#include "helper/glslprogram.h"
//
#include "helper/torus.h"
#include "helper/teapot.h"
#include <glm/glm.hpp>
#include "helper/cube.h"

class SceneBasic_Uniform : public Scene
{
private:
    //GLuint vaoHandle;
    GLSLProgram prog;
    //float angle; for lab 2 both need to remove 
    Torus torus;
    Teapot teapot;
    Plane plane; 
    std::unique_ptr<ObjMesh> mesh;
 /*   Torus torus;*/
    Cube cube;
    void setMatrices();

    void compile();

public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
