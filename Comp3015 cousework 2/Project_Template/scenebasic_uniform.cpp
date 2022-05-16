#include "scenebasic_uniform.h"
#include <sstream> // step 2 
#include "helper/texture.h";
#include <string>
using namespace std;
#include <iostream>
using std::cerr;
using std::endl;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;
using glm::vec4;
using glm::mat3;
float angle, tPrev;
int shadermode = 1;
std::string Testmodel;
SceneBasic_Uniform::SceneBasic_Uniform() : plane(50.0f,50.0f,1,1), teapot(14,glm::mat4(1.0f)), torus(1.75f*0.75f,0.75f*0.75,50,50), tPrev(0.0f), lightPos(5.0f,5.0f,5.0f,1.0f)  {
    cout << "there is two model you can choose the dount and the pig.\n";
    cout << "to choose the dount please type one in all lower case or leave it for the pig\n";
   
     std::getline(std::cin, Testmodel);
    if (Testmodel == "one") {
        cout << "warning the dount will take a while to load a min";
       mesh = ObjMesh::load("../Project_Template/media/donut.obj", true); // this will slow the computer this will take 56 second on my computer so yeah.
        cout << "this is now done please press enter to load it ";
        std::getline(std::cin, Testmodel);
    }
    else {
        mesh = ObjMesh::load("../Project_Template/media/pig_triangulated.obj", true);
    }
    cout << "welcome to the random number of object\n";
}

void SceneBasic_Uniform::initScene()
{
    
    compile();
    //if (shadermode == 0) {
    //    //uniform
    //    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //    glEnable(GL_DEPTH_TEST);
    //    float c = 1.5f;
    //    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f * c, 0.3f * c, 0.1f, 100.0f);

    //    prog.setUniform("Line.Width", 0.75f);
    //    prog.setUniform("Line.Color", vec4(0.05f, 0.0f, 0.05f, 1.0f));
    //    prog.setUniform("Material.kd", 0.7f, 0.7f, 0.7f);
    //    prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //    prog.setUniform("Material.ka", 0.2f, 0.2f, 0.2f);
    //    prog.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);
    //    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    //    prog.setUniform("Material.Shininess", 100.0f);
    //}
    
    
        // pbr
    GLuint TexID =
        Texture::loadTexture("../Project_Template/media/texture/bluewater.jpg");
    glGenTextures(1, &TexID);
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexID);
        view = glm::lookAt(
            glm::vec3(0.0f, 9.0f, 7.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0, 1.0f, 0.0f)
        );
        projection = glm::perspective(glm::radians(50.0f), (float)width / height, 0.5f, 100.0f);
        lightAngle = 0.0f;
        lightRotationSpeed = 1.5f;

        prog.setUniform("Light[0].L", glm::vec3(45.0f));
        prog.setUniform("Light[0].Position", view * lightPos);
        prog.setUniform("Light[1].L", glm::vec3(0.3f));
        prog.setUniform("Light[1].Position", glm::vec4(0, 0.15f, -1.0f, 0));
        prog.setUniform("Light[2].L", glm::vec3(45.0f));
        prog.setUniform("Light[2].Position", view * glm::vec4(-7, 3, 7, 1));
    

    //geom
  //  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  //  glEnable(GL_DEPTH_TEST);

  //  numSprites = 50;
  //  location = new float[numSprites * 3];
  //  srand((unsigned int)time(0));

  //  for (int i = 0; i < numSprites; i++)
  //  {
  //      vec3 p(((float)rand() / RAND_MAX * 2.0f) - 1.0f,
  //          ((float)rand() / RAND_MAX * 2.0f) - 1.0f,
  //          ((float)rand() / RAND_MAX * 2.0f) - 1.0f);
  //      location[i * 3] = p.x;
  //      location[i * 3 + 1] = p.y;
  //      location[i * 3 + 2] = p.z;

  //  }
  //  GLuint handle;
  ////  glGenBuffers(1,)

}

void SceneBasic_Uniform::compile()
{

        try { //pbr
            prog.compileShader("shader/basic_uniform.vert");
            prog.compileShader("shader/basic_uniform.frag");
            prog.link();
            prog.use();
        }
        catch (GLSLProgramException& e) {
            cerr << e.what() << endl;
            exit(EXIT_FAILURE);
        }
    
}

void SceneBasic_Uniform::update( float t )
{
	//update your angle here
    float deltaT = t - tPrev;
    if (tPrev == 0.0f)
        deltaT = 0.0f;

    tPrev = t;

    if (animating()) {
        lightAngle = glm::mod(lightAngle + deltaT * lightRotationSpeed, glm::two_pi<float>());
        lightPos.x = glm::cos(lightAngle) * 7.0f;
        lightPos.y = 3.0f;
        lightPos.z = glm::sin(lightAngle) * 7.0f;

    }

  
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    prog.setUniform("Light[0].Position", view * lightPos);
    drawScene();


    //phong from the lab
 //   prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
 //   prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
 //   prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
 //   prog.setUniform("Material.Shininess", 180.0f);
 //   model = mat4(1.0f);
 //   model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
 //   setMatrices();
 //    mesh->render();
 //   prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
 //   prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
 //   prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
 //   prog.setUniform("Material.Shininess", 180.0f);
 //   model = mat4(1.0f);
 //   model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
 //   vec4 lightpos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
 //   prog.setUniform("light.Position", view * lightpos);
 //   setMatrices();
 // //  cube.render();
 //  
 // //
 //  plane.render();
 //  //sport light from the lab
 ///*   vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
 //   prog.setUniform("Spot.Position", vec3(view * lightPos));
 //   mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
 //   prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));
 //   prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
 //   prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
 //   prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
 //   prog.setUniform("Material.Shininess", 100.0f);
 //   model = mat4(1.0f);
 //   model = glm::translate(model, vec3(0.0f, 0.0f, -2.0f));
 //   model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
 //   model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
 //   setMatrices();
 //   teapot.render();
 //   prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
 //   prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
 //   prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
 //   prog.setUniform("Material.Shininess", 100.0f);
 //   model = mat4(1.0f);
 //   model = glm::translate(model, vec3(-1.0f, 0.75f, 3.0f));
 //   model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
 //   setMatrices();
 //   torus.render();
 //   prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
 //   prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
 //   prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
 //   prog.setUniform("Material.Shininess", 180.0f);
 //   model = mat4(1.0f);
 //   setMatrices();
 //   plane.render();*/
   
}
void SceneBasic_Uniform::setMatrices() {
    glm::mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(mv));
    prog.setUniform("MVP", projection * mv);
}
void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(60.0f), (float) width / height, 0.3f, 100.0f);
}

void SceneBasic_Uniform::drawScene() {
    drawFloor();
    srand(time(NULL));
    int num;
    std::string numberRandomOn;
    
   // std::getline(std::cin, numberRandomOn);
    
        num = rand() % 10 + 1;
    
   
    
    
    glm::vec3 cowBasecolor(0.0f, 0.33f, 0.96f);
    for (int i = 0; i < num; i++) {
        float numobject = i * (10.f / (num - 1)) - 5.0f;
        float rough = (i + 1) * (1.0f / numobject);
        DrawSport(glm::vec3(numobject, 0, 0), rough, 0, cowBasecolor);
    }
    float metalRough = 0.43f;

    DrawSport(glm::vec3(-3.0f, 0.0f, 3.0f), metalRough, 1, glm::vec3(1.0f, 0.71f, 0.29f));
    DrawSport(glm::vec3(-1.5f, 0.0f, 3.0f), metalRough, 1, glm::vec3(0.95f, 0.64f, 0.54f));
    DrawSport(glm::vec3(-3.0f, 0.0f, 3.0f), metalRough, 1, glm::vec3(0.91f, 0.92f, 0.92f));
    DrawSport(glm::vec3(-3.0f, 0.0f, 3.0f), metalRough, 1, glm::vec3( 0.542f, 0.497f, 0.449f));
    DrawSport(glm::vec3(-3.0f, 0.0f, 3.0f), metalRough, 1, glm::vec3(0.95f, 0.93f, 0.88f));

}
void SceneBasic_Uniform::drawFloor() {
    model = glm::mat4(1.0f);
    prog.setUniform("Material,Rough", 0.9f);
    prog.setUniform("Material.Metal", 0);
    prog.setUniform("Material.Color", glm::vec3(0.2f));
    model = glm::translate(model, glm::vec3(0.0f, -0.75, 0.0f));
    setMatrices();
    plane.render();
}

void SceneBasic_Uniform::DrawSport(const glm::vec3& pos, float rough, int metal, const glm::vec3& color) {
    model = glm::mat4(1.0f);
    prog.setUniform("Material,Rough", rough);
    prog.setUniform("Material.Metal", metal);
    prog.setUniform("Material.Color",  color);
    model = glm::translate(model,pos);
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
    mesh->render();
}