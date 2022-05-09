#include "scenebasic_uniform.h"
#include <sstream> // step 2 
#include "helper/texture.h";
#include <string>
using namespace std;
#include <iostream>
using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::mat4;
using glm::vec4;
using glm::mat3;
float angle, tPrev;
std::string Testmodel;
SceneBasic_Uniform::SceneBasic_Uniform() : plane(50.0f,50.0f,1,1), teapot(14,glm::mat4(1.0f)), torus(1.75f*0.75f,0.75f*0.75,50,50)  {
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
}

void SceneBasic_Uniform::initScene()
{
    compile();
    glEnable(GL_DEPTH_TEST);
    //texture
    view = glm::lookAt(vec3(1.0f, 1.25f, 1.25f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);
    //spotlight from lab
    //view = glm::lookAt(vec3(5.0f, 5.0f, 7.5f), vec3(0.0f, 0.75, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    //projection = mat4(1.0f);
    //prog.setUniform("Spot.L", vec3(0.9f));
    //prog.setUniform("Spot.La", vec3(0.5f));
    //prog.setUniform("Spot.Exponent", 50.0f);
    //prog.setUniform("Spot.Cutoff", glm::radians(15.0f));
    //// phong from lab 
    ////view = glm::lookAt(vec3(0.5f, 0.75f, 0.75f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    //projection = mat4(1.0f);
    float x, z;
    for (int i = 0; i < 3; i++)
    {
        std::stringstream name;
        name << "lights[" << i << "].Position";
        x = 2.0f * cosf((glm::two_pi<float>() / 3) * i);
        z = 2.0f * sinf((glm::two_pi<float>() / 3) * i);
        prog.setUniform(name.str().c_str(), view * glm::vec4(x, 1.2f, z + 1.0f, 1.0f));
    }
    prog.setUniform("lights[0].L", vec3(0.0f, 0.0f, 0.8f));
    prog.setUniform("lights[1].L", vec3(0.0f, 0.8f, 0.0f));
    prog.setUniform("lights[2].L", vec3(0.8f, 0.0f, 0.0f));
    GLuint texID = Texture::loadTexture("../Project_Template/media/texture/brick1.jpg");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);


}

void SceneBasic_Uniform::compile()
{

	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
	//update your angle here
    float deltaT = t - tPrev;
    if (tPrev = t - tPrev)
        deltaT = 0.0f;
    tPrev = t;
    angle += 0.25 * deltaT;
    if (angle > glm::two_pi<float>())
        angle -= glm::two_pi<float>();

  
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //phong from the lab
    prog.setUniform("Material.Kd", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.5f, 0.5f, 0.5f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
     mesh->render();
    prog.setUniform("Material.Kd", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.1f, 0.1f, 0.1f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -0.45f, 0.0f));
    vec4 lightpos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
    prog.setUniform("light.Position", view * lightpos);
    setMatrices();
  //  cube.render();
   
  //
   plane.render();
   //sport light from the lab
 /*   vec4 lightPos = vec4(0.0f, 10.0f, 0.0f, 1.0f);
    prog.setUniform("Spot.Position", vec3(view * lightPos));
    mat3 normalMatrix = mat3(vec3(view[0]), vec3(view[1]), vec3(view[2]));
    prog.setUniform("Spot.Direction", normalMatrix * vec3(-lightPos));
    prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
    prog.setUniform("Material.Shininess", 100.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, 0.0f, -2.0f));
    model = glm::rotate(model, glm::radians(45.0f), vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    setMatrices();
    teapot.render();
    prog.setUniform("Material.Kd", 0.2f, 0.55f, 0.9f);
    prog.setUniform("Material.Ks", 0.95f, 0.95f, 0.95f);
    prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
    prog.setUniform("Material.Shininess", 100.0f);
    model = mat4(1.0f);
    model = glm::translate(model, vec3(-1.0f, 0.75f, 3.0f));
    model = glm::rotate(model, glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
    setMatrices();
    torus.render();
    prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
    prog.setUniform("Material.Ks", 0.9f, 0.9f, 0.9f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Shininess", 180.0f);
    model = mat4(1.0f);
    setMatrices();
    plane.render();*/
   
}
void SceneBasic_Uniform::setMatrices() {
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]))); //we set the uniform for normal matrix

    prog.setUniform("MVP", projection * mv); //we set the model view matrix by multiplying the mv with the projection matrix
}
void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);
}
