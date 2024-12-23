#include "TextHelp.h"
#ifdef _WIN32
#include <Windows.h>
#endif


bool run = true;
Vector2 MousePos;
Vector2 MouseVel;
std::string rpath = "/Resources/";


float deltime;
float lastime;
Uint64 frequency;


SDL_Event e;
SDL_Window * Window;
SDL_Renderer * Render;
SDL_MouseButtonFlags MouseStates;
const bool * KeyStates = SDL_GetKeyboardState(NULL);


Vector2 WindowSize = {960, 540};
bool FullscreenMode = true;


int main(int argc, char* argv[]) {


    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
    SDL_CreateWindowAndRenderer("No Ammo", WindowSize.x, WindowSize.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY, &Window, &Render);
    SDL_SetWindowMinimumSize(Window, 960, 540);
    frequency = SDL_GetPerformanceFrequency();


    TTF_Init();
    TTF_Font * Font = TTF_OpenFont((SDL_GetBasePath()+rpath+"Font.ttf").c_str(), 26);
    TextCharacters CharInit = TextCharacters(Render, Font);
    TextCharacters * Characters = &CharInit;



    TextObject Intro = TextObject("Please enter your username below:", Characters, A_Center, A_Bottom, WindowSize/2, {255, 255, 255, 255}, false);
    TextObject Nameput = TextObject("", Characters, A_Center, A_Top, WindowSize/2, SDL_Color(255, 255, 255, 255), true);


    while (run){
        deltime = (SDL_GetPerformanceCounter() - lastime)/frequency;
        lastime = SDL_GetPerformanceCounter();


        SDL_SetRenderDrawColorFloat(Render, 0, 0, 0, 1);
        SDL_RenderClear(Render);


        while (SDL_PollEvent(&e)){
            switch (e.type){
                case SDL_EVENT_QUIT:
                    run = false;
                    break;


                case SDL_EVENT_KEY_DOWN:
                    if (e.key.scancode == SDL_SCANCODE_F11) {
                        FullscreenMode = !FullscreenMode;
                        SDL_SetWindowFullscreen(Window, FullscreenMode);
                    }
                    break;


                case SDL_EVENT_MOUSE_MOTION:
                    MouseVel = {e.motion.xrel, e.motion.yrel};
                    break;


                case SDL_EVENT_WINDOW_RESIZED:
                    int TX, TY;
                    SDL_GetWindowSize(Window, &TX, &TY);
                    WindowSize = {(float)TX, (float)TY};
            }
        }
        MouseStates = SDL_GetMouseState(&MousePos.x, &MousePos.y);








        SDL_RenderPresent(Render);
    }




    return 0;
}


#ifdef _WIN32
/* Windows window subsystem :( */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    rpath = "/";
    return main(__argc, __argv);
}
#endif
