// "boNES" a NES emulator developed by BojanglesTheJangle on GitHub!
// Made bone by bone.


// Libraries
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <fstream>
#include <string>
#include <array>

// Header Files
#include "main.h"

// Graphics
const int WINDOW_WIDTH = 256;
const int WINDOW_HEIGHT = 224;
SDL_Window* g_main_window;
SDL_Renderer* g_main_renderer;

// Colors
namespace Colors {
    const SDL_Color BLACK = { 0, 0, 0, SDL_ALPHA_OPAQUE };
}

static bool InitSDL() { // Starts SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL2 failed to initialize with error: " << SDL_GetError();
        return false;
    }

    g_main_window = SDL_CreateWindow(
        "boNES",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (g_main_window == nullptr) {
        std::cout << "Failed to create window with SDL2. Error Code:" << SDL_GetError();
        SDL_Quit();
        return false;
    }

    g_main_renderer = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_PRESENTVSYNC);


    return true;
}

void OSDL() { // Shuts down SDL2

    if (g_main_renderer != nullptr) {
        SDL_DestroyRenderer(g_main_renderer);
        g_main_renderer = nullptr;
    }

    if (g_main_window != nullptr) {
        SDL_DestroyWindow(g_main_window);
        g_main_window = nullptr;
    }

    SDL_Quit();
}

static void clear(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, Colors::BLACK.r, Colors::BLACK.g, Colors::BLACK.b, Colors::BLACK.a);
    SDL_RenderClear(renderer);
}

int main(int argc, char* argv[]) {  // argc = number of arguments argv = path of argument 

    std::cout << "                                                                                                                        _|                  _|      _|  _|_|_|_|    _|_|_|                                                                      _|_|_|      _|_|    _|_|    _|  _|        _|                                                                            _|    _|  _|    _|  _|  _|  _|  _|_|_|      _|_|                                                                        _|    _|  _|    _|  _|    _|_|  _|              _|                                                                      _|_|_|      _|_|    _|      _|  _|_|_|_|  _|_|_|                                                                                                                                                                                                ";

    std::cout << "Welcome to the boNES emulator! \n";


    if (argc < 2)
    {
        std::cout << "Please drag a .nes file onto boNES.exe in the file explorer!\n";
        return -1;
    }



    std::string ROM = argv[1];
    std::cout << "NES file recieved!";

    if (InitSDL() == false) { OSDL(); }

    // Draw Loop for SDL2
    SDL_Event event;
    bool running = true;

    while (running) {
        clear(g_main_renderer);

        // Checking for input and proccesing.
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: { running = event.key.keysym.scancode != SDL_SCANCODE_ESCAPE; break; }
                case SDL_QUIT: {
                    running = false;
                    break;
                }
                default:
                    break;
            }
        }

        // Update the screen with rendered content
        SDL_RenderPresent(g_main_renderer);
    }

    OSDL();
    return EXIT_SUCCESS;

}

