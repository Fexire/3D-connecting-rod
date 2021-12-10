#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Model.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>
#include <experimental/filesystem>

using namespace glimac;

int main(int argc, char **argv)
{
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError)
    {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);
    Program program(loadProgram(applicationPath.dirPath() + "shaders/model.vs.glsl",
                                applicationPath.dirPath() + "shaders/model.fs.glsl"));
    program.use();

    Model hangar{"/home/fd/Desktop/3D-connecting-rod/obj/corridor.obj"};

    glEnable(GL_DEPTH_TEST);

    FreeflyCamera camera{};

    Cube cube{};
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    Mesh cubeMesh = cube.build();

    Cylinder cylinder;
    Mesh cylinderMesh = cylinder.build(100);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(70.f), 800.f / 600.f, 0.1f, 100.f);

    /*****************o***************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Application loop:
    bool done = false;
    while (!done)
    {
        if (windowManager.isKeyPressed(SDLKey::SDLK_LEFT))
        {
            camera.rotateLeft(1.0);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_RIGHT))
        {
            camera.rotateLeft(-1.0);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_UP))
        {
            camera.rotateUp(1.0);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_DOWN))
        {
            camera.rotateUp(-1.0);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_z))
        {
            camera.moveFront(0.1);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_s))
        {
            camera.moveFront(-0.1);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_d))
        {
            camera.moveLeft(-1.);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_q))
        {
            camera.moveLeft(1.);
        }
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 viewMatrix = camera.getViewMatrix();
        glUniformMatrix4fv(program.uViewMatrix, 1, GL_FALSE,
                           glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE,
                           glm::value_ptr(glm::transpose(glm::inverse(viewMatrix))));
        glUniformMatrix4fv(program.uProjectionMatrix, 1, GL_FALSE,
                           glm::value_ptr(projectionMatrix * viewMatrix));
        hangar.Draw(program);
        cylinderMesh.Draw(program);

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}
