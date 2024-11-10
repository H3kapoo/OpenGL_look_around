#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <string>

#include "src/assetLoaders/TextureLoader.hpp"
#include "src/objects/GameObject.hpp"
#include "src/common/Texture.hpp"
#include "src/common/Transform.hpp"
#include "src/mesh/Mesh.hpp"
#include "src/mesh/MeshFactory.hpp"
#include "src/renderer/Renderer.hpp"
#include "src/common/WindowCommon.hpp"
#include "src/shader/Shader.hpp"
#include "src/tools/Debug.hpp"
#include "src/tools/Logger.hpp"
#include "Window.hpp"

using namespace gui;
using namespace shader;
using namespace mesh;
using namespace assetloaders;
using namespace renderer;
using namespace objects;

#define WINDOW_H 720
#define WINDOW_W 1280
// #define WINDOW_H 640
// #define WINDOW_W 640

int main()
{
   // tools::Logger::unsetLevels(tools::Logger::Level::DEBUG);

   /* Initialize the library */
   if (!Window::initGlfwWindowing())
   {
      return -1;
   }

   /* Create a windowed mode window and its OpenGL context */
   Window win("Test", WINDOW_W, WINDOW_H, Window::HintFactory::createDebuggable());

   if (!win.getHandle())
   {
      Window::terminate();
      return -1;
   }

   win.setContextCurrent();

   if (glewInit() != GLEW_OK)
   {
      return -1;
   }

   // debug::Debug::get().enableWireframe();
   tools::Logger mainLog("Main");

   debug::Debug::get();

   win.setEventBits(WindowInputBit::MOUSE_MOVE | WindowInputBit::MOUSE_CLICK);
   win.onMouseClick([]()
   {
      printf("click\n");
   });

   Mesh cubeMesh = MeshFactory::createCubeMesh();
   Mesh cubeMesh2 = MeshFactory::createCubeMesh();

   TextureLoader& texLoader = TextureLoader::get();
   uint32_t texId = texLoader.loadTexture("assets/textures/wall.jpg").id;
   uint32_t texId2 = texLoader.loadTexture("assets/textures/container.jpg").id;
   uint32_t texId3 = texLoader.loadTexture("assets/textures/awesomeface.png").id;

   Shader shader("assets/shader/basic.glsl");
   shader.bind();

   shader.setTexture2D("inTexture", GL_TEXTURE0, texId2);
   shader.setTexture2D("inTexture2", GL_TEXTURE1, texId3);
   shader.setInt("ceva", 2);

   glm::mat4 projMat = glm::perspective(glm::radians(45.0f), (float)WINDOW_W/WINDOW_H, 0.1f, 100.0f);

   glm::mat4 viewMat{1.0f};
   viewMat = glm::translate(viewMat, glm::vec3(0, -0.1, -3));

   shader.setMat4f("uProjMat", projMat);
   shader.setMat4f("uViewMat", viewMat);

   GameObject obj(cubeMesh);
   GameObject obj2(cubeMesh);

   obj.getTransform().pos.x = 2;
   glEnable(GL_DEPTH_TEST);

   /* Loop until the user closes the window */
   while (!win.shouldClose())
   {
      win.setTitle(std::to_string(glfwGetTime()));

      if (glfwGetTime() > 3.1 && glfwGetTime() < 3.2)
      {
         // mainLog.error("New line here");
         // obj.getTransform().dirty = false;
      }

      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

      // glm::mat4 modelMat2{1.0f};
      // // modelMat = glm::translate(modelMat, glm::vec3(-0.3f, -0.3f, 0));
      // modelMat2 = glm::rotate(modelMat2, glm::radians(, glm::vec3(0, 1, 0));
      // modelMat2 = glm::scale(modelMat2, glm::vec3(((std::sin(Window::getTime())+2.0f)*0.5f)));

      obj.getTransform().rot.y = (float)Window::getTime()*14.0f;
      obj.getTransform().scale = glm::vec3((std::sin(Window::getTime())+2.0f)*0.5f);
      shader.setMat4f("uModelMat", obj.getModelMatrix());

      obj.bind();
      Renderer::renderElements(GL_TRIANGLES, 36);

      obj2.getTransform().rot.y = (float)Window::getTime()*14.0f;
      obj2.getTransform().scale = glm::vec3((std::sin(Window::getTime())+2.0f)*0.5f);
      shader.setMat4f("uModelMat", obj2.getModelMatrix());

      obj2.bind();
      Renderer::renderElements(GL_TRIANGLES, 36);

      /* Swap front and back buffers */
      win.swap();

      /* Poll for and process events */
      Window::pollEvents();
   }

   Window::terminate();
   return 0;
}