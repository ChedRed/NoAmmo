#include "TextHelp.h"
#include "Registry/registry.h"
#include "Registry/entity.h"
#include "Vector2.h"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_mouse.h>
#include <iostream>
#include <filesystem>
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
iVector2 iMousePos;
Vector2 MouseVel;
std::string SourcePath;


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
float CursorScale = 1.5;


std::string SDL_GetBasePathNOS(){
    std::string data = SDL_GetBasePath();
    #ifdef _WIN32
    std::string returnv;
    for (int i = 0; i < data.length(); i++){
        if (data[i] == '\\'){
            returnv += "/";
        }
        else{
            returnv += data[i];
        }
    }
    return returnv;
    #else
    return data;
    #endif
}


int main(int argc, char* argv[]) {

    #ifdef _WIN32
    SourcePath = "Resources/Content/";
    #elifdef __APPLE__
    rpath = "Content/";
    #endif
    std::string ResourcePath = SDL_GetBasePathNOS() + SourcePath;


    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
    SDL_CreateWindowAndRenderer("No Ammo", WindowSize.x, WindowSize.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &Window, &Render);
    SDL_SetWindowMinimumSize(Window, WindowSize.x, WindowSize.y);
    SDL_StartTextInput(Window);
    SDL_HideCursor();
    frequency = SDL_GetPerformanceFrequency();


    // Setup textures
    SDL_Surface * LoadS = SDL_LoadBMP((ResourcePath+"/Textures/UI/cursor.bmp").c_str());
    SDL_Texture * LoadedMouse = SDL_CreateTextureFromSurface(Render, LoadS);
    SDL_DestroySurface(LoadS);
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
    Result.w *= CursorScale;
    Result.h *= CursorScale;
    SDL_SetTextureScaleMode(Mouse, SDL_SCALEMODE_LINEAR);


    // Setup font
    TTF_Init();
    TTF_Font * Font = TTF_OpenFont((ResourcePath+"/Fonts/Font.ttf").c_str(), 20);
    TextCharacters * Characters = CreaTextCharacters(Render, Font);
    // TextObject Intro = TextObject("Please enter your username below:", Characters, A_Center, A_Bottom, WindowSize/2, {255, 255, 255, 255}, false);
    // TextObject Nameput = TextObject("", Characters, A_Center, A_Top, WindowSize/2, {255, 255, 255, 255}, true);


    Registry<Entity> * EntityRegistry = new Registry<Entity>(Render, ResourcePath, "Entities");


    Register(EntityRegistry, Render, "::player", Entity(Vector2(), Vector2(), 0, SDL_FRect(0, 0, 16, 10), 100, 1));


    Entity Player = Create(EntityRegistry, "::player");


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


        iVector2 Offset;
        MouseStates = SDL_GetGlobalMouseState(&MousePos.x, &MousePos.y);
        SDL_GetWindowPosition(Window, &Offset.x, &Offset.y);
        Result.x = MousePos.x - (Result.w/2) - Offset.x;
        Result.y = MousePos.y - (Result.h/2) - Offset.y;

        Player.Update(deltime);
        Player.Render(Render);
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
