#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Model.hpp>
#include <glimac/FreeflyCamera.hpp>
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

    Model hangar{"/home/fd/Desktop/3D-connecting-rod/assets/Shelter.obj"};

    glEnable(GL_DEPTH_TEST);

    FreeflyCamera camera{};

    Rod rod{15, 5, 1};

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    /*****************o***************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Application loop:
    glm::ivec2 mousePosition;
    float speed = 0.1;
    bool done = false;
    while (!done)
    {
        // Event loop:
        SDL_Event e;
        while (windowManager.pollEvent(e))
        {
            if (e.type == SDL_QUIT)
            {
                done = true; // Leave the loop after this iteration
            }
            if(e.type == SDL_KEYDOWN)
            {
                if (windowManager.isKeyPressed(SDLKey::SDLK_e))
                {
                    rod.runStopUpdate();
                }
                if (windowManager.isKeyPressed(SDLKey::SDLK_r))
                {
                    rod.speedUp();
                }
                if (windowManager.isKeyPressed(SDLKey::SDLK_f))
                {
                    rod.speedDown();
                }
                if (windowManager.isKeyPressed(SDLKey::SDLK_ESCAPE))
                {
                    done = true;
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_F1))
                {
                    program.onOffCameraLight();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_F2))
                {
                    program.onOffRodLight();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_F3))
                {
                    program.onOffRoomLight();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_t))
                {
                    rod.thicknessUp();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_g))
                {
                    rod.thicknessDown();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_y))
                {
                    rod.armLengthUp();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_h))
                {
                    rod.armLengthDown();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_u))
                {
                    rod.treeLengthUp();
                }
                if(windowManager.isKeyPressed(SDLKey::SDLK_j))
                {
                    rod.treeLengthDown();
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT))
                {
                    mousePosition = windowManager.getMousePosition();
                }
            }
        }
        if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT))
        {
            glm::ivec2 newMousePos;
            newMousePos = windowManager.getMousePosition();
            camera.rotateLeft(speed * -(newMousePos.x - mousePosition.x));
            mousePosition = newMousePos;
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_z))
        {
            camera.moveFront(speed);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_s))
        {
            camera.moveFront(-speed);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_d))
        {
            camera.moveLeft(-speed);
        }
        if (windowManager.isKeyPressed(SDLKey::SDLK_q))
        {
            camera.moveLeft(speed);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.updateLights(camera,rod.getTreeMatrix(),rod.midAB());
        hangar.Draw(program,camera);
        rod.draw(program, camera);
        
        

        windowManager.swapBuffers();
    }
    return EXIT_SUCCESS;
}
