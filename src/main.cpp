#include <cstdint>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/assetLoaders/TextureLoader.hpp"
#include "src/common/Texture.hpp"
#include "src/mesh/Mesh.hpp"
#include "src/shader/Shader.hpp"
#include "src/tools/Debug.hpp"
#include "src/tools/Logger.hpp"
#include "Window.hpp"

using namespace gui;
using namespace shader;
using namespace mesh;
using namespace assetloaders;

// #define WINDOW_H 480
// #define WINDOW_W 640
#define WINDOW_H 640
#define WINDOW_W 640


int main()
{
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

   debug::Debug::get();
   // debug::Debug::get().enableWireframe();

   tools::Logger mainLog("Main");

   win.setEventBits(EventBit::MOUSE_MOVE | EventBit::MOUSE_CLICK);
   win.onMouseClick([](){
      printf("click\n");
   });

   std::vector<float> vertices = {
        // positions   // texture coords    // rgb
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, // top right
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, // bottom left
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, // top left 
   };

   std::vector<uint32_t> indices = {  
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
    };

   Mesh mesh;
   mesh.setDataBuffer(std::move(vertices), Mesh::STATIC);
   mesh.setElementBuffer(std::move(indices), Mesh::STATIC);
   mesh.addVertexLayer(0, 3, "Position");
   mesh.addVertexLayer(1, 2, "TextureUV");
   mesh.addVertexLayer(2, 3, "ColorRGB");
   mesh.buildLayers();

   TextureLoader& texLoader = TextureLoader::get();
   uint32_t texId = texLoader.loadTexture("assets/textures/wall.jpg").id;
   uint32_t texId2 = texLoader.loadTexture("assets/textures/container.jpg").id;
   uint32_t texId3 = texLoader.loadTexture("assets/textures/awesomeface.png").id;

   Shader shader("assets/shader/basic.glsl");
   shader.bind();
   mesh.bind();

   shader.setTexture2D("inTexture", TextureUnit::_1, texId);
   shader.setTexture2D("inTexture2", TextureUnit::_2, texId3);
   shader.setInt("ceva", 2);

   // glm::mat4 modelMat = glm::mat4(1.0f);
   // modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0, 0, 1));
   // modelMat = glm::scale(modelMat, glm::vec3(0.5f));

   // mainLog.info("size %ld", sizeof(mesh));

   /* Loop until the user closes the window */
   while (!win.shouldClose())
   {
      /* Render here */
      Window::clear(GL_COLOR_BUFFER_BIT);
      glClearColor(0.3f, 0.3f, 0.3f, 1.f);

      glm::mat4 modelMat{1.0f};
      modelMat = glm::rotate(modelMat, glm::radians((float)Window::getTime()*2.0f), glm::vec3(0, 0, 1));
      shader.setMat4f("uModelMat", modelMat);

      // glDrawArrays(GL_TRIANGLES, 0, 3);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      /* Swap front and back buffers */
      win.swap();

      /* Poll for and process events */
      Window::pollEvents();
   }

   Window::terminate();
   return 0;
}