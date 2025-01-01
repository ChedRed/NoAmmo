#include "TextHelp.h"
#include "player.h"
#include "registry.h"
#ifdef _WIN32
#include <Windows.h>
#endif


#ifdef _WIN32
#define SDL_MODKEY SDL_SCANCODE_LCTRL
#elifdef __APPLE__
#define SDL_MODKEY SDL_SCANCODE_LGUI
#endif


int TX, TY;


bool run = true;
Vector2 MousePos;
Vector2 MouseVel;
std::string rpath = "./Resources/";


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
int Cursor = 1;


int main(int argc, char* argv[]) {


    #ifdef __APPLE__
    rpath = "."+rpath;
    #endif
    std::string path = SDL_GetBasePath() + rpath;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
    SDL_CreateWindowAndRenderer("No Ammo", WindowSize.x, WindowSize.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &Window, &Render);
    SDL_SetWindowMinimumSize(Window, WindowSize.x, WindowSize.y);
    SDL_StartTextInput(Window);
    SDL_HideCursor();
    frequency = SDL_GetPerformanceFrequency();


    // Setup textures
    SDL_Surface * LoadS = SDL_LoadBMP((path+"cursor.bmp").c_str());
    SDL_Texture * LoadedMouse = SDL_CreateTextureFromSurface(Render, LoadS);
    float fw, fh;
    SDL_GetTextureSize(LoadedMouse, &fw, &fh);
    int tw = fw;
    int th = fh;
    SDL_Texture * Mouse = SDL_CreateTexture(Render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, th, th);
    SDL_FRect Copy = {(Cursor-1) * th, 0, th, th};
    SDL_FRect Result = {0, 0, th, th};
    if (tw % th == 0 && Cursor > 0){
        SDL_SetRenderTarget(Render, Mouse);
        SDL_RenderTexture(Render, LoadedMouse, &Copy, &Result);
        SDL_SetRenderTarget(Render, NULL);
    }


    // Setup font
    TTF_Init();
    TTF_Font * Font = TTF_OpenFont((path+"Font.ttf").c_str(), 20);
    TextCharacters CharInit = TextCharacters(Render, Font);
    TextCharacters * Characters = &CharInit;
    // TextObject Intro = TextObject("Please enter your username below:", Characters, A_Center, A_Bottom, WindowSize/2, {255, 255, 255, 255}, false);
    // TextObject Nameput = TextObject("", Characters, A_Center, A_Top, WindowSize/2, {255, 255, 255, 255}, true);


    Registry * ItemRegistry = CreateRegistry();
    Registry * EntityRegistry = CreateRegistry();


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
                    if (KeyStates[SDL_MODKEY]) {
                        if (e.key.key == SDLK_A){
                            // Nameput.Edit("a", KeyStates[SDL_MODKEY]);
                        }
                        elif (e.key.key == SDLK_C){
                            // Nameput.Edit("c", KeyStates[SDL_MODKEY]);
                        }
                        elif (e.key.key == SDLK_X){
                            // Nameput.Edit("x", KeyStates[SDL_MODKEY]);
                        }
                        elif (e.key.key == SDLK_V){
                            // Nameput.Edit("v", KeyStates[SDL_MODKEY]);
                        }
                    }
                    if (e.key.key == SDLK_DELETE || e.key.key == SDLK_BACKSPACE){
                        // Nameput.Delete(e.key.key == SDLK_DELETE);
                    }
                    if (e.key.key == SDLK_LEFT){
                        // Nameput.MoveCursor(KeyStates[SDL_SCANCODE_LSHIFT] || KeyStates[SDL_SCANCODE_RSHIFT], KeyStates[SDL_SCANCODE_LCTRL] || KeyStates[SDL_SCANCODE_RCTRL], true);
                    }
                    elif (e.key.key == SDLK_RIGHT){
                        // Nameput.MoveCursor(KeyStates[SDL_SCANCODE_LSHIFT] || KeyStates[SDL_SCANCODE_RSHIFT], KeyStates[SDL_SCANCODE_LCTRL] || KeyStates[SDL_SCANCODE_RCTRL], false);
                    }
                    break;


                case SDL_EVENT_MOUSE_MOTION:
                    MouseVel = {e.motion.xrel, e.motion.yrel};
                    break;


                case SDL_EVENT_WINDOW_RESIZED:
                    SDL_GetWindowSize(Window, &TX, &TY);
                    WindowSize = {(float)TX, (float)TY};
                    break;


                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    // Nameput.TrySelect(MousePos, KeyStates[SDL_SCANCODE_LSHIFT]);
                    break;


                case SDL_EVENT_TEXT_INPUT:
                    // Nameput.Edit(e.text.text, false);
                    break;
            }
        }
        if (MouseStates & SDL_BUTTON_LMASK){
            // Nameput.ConTrySelect(MousePos);
        }
        MouseStates = SDL_GetMouseState(&MousePos.x, &MousePos.y);
        Result.x = MousePos.x - (Result.w/2);
        Result.y = MousePos.y - (Result.h/2);





        SDL_RenderTexture(Render, Mouse, NULL, &Result);
        SDL_RenderPresent(Render);
    }


    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Render);
    SDL_Quit();
    return 0;
}


#ifdef _WIN32
/* Windows window subsystem :( */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    return main(__argc, __argv);
}
#endif
