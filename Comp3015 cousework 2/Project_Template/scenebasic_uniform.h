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

    float tPrev, lightAngle, lightRotationSpeed; 
    glm::vec4 lightPos;
   
    void setMatrices();
    void compile();
    void drawScene();
    void drawFloor();
    void DrawSport(const glm::vec3& pos, float rough, int metal, const glm::vec3& color);
     
public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
};

#endif // SCENEBASIC_UNIFORM_H
