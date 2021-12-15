#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Model.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Cylinder.hpp>
#include <experimental/filesystem>
#include <glimac/SceneStructure.hpp>
#include <glimac/Rod.hpp>

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

    Rod rod{4,5,1};

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
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
        
        //hangar.Draw(program,camera);
        rod.draw(program,camera);
        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}
