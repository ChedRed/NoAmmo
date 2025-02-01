#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <vector>
#include <SDL3/SDL.h>
#include <string>


template<typename T>
class Registry{
public:
Registry(SDL_Renderer * Render, std::string ResourcePath, std::string Path);
std::string DirectoryPath;
std::string FilePath;
std::vector<T> Data;
std::vector<std::string> IDs;
SDL_Texture * Missing;
Registry(const Registry&) = delete;
Registry& operator=(const Registry&) = delete;
};


template<typename T>
inline Registry<T>::Registry(SDL_Renderer * Render, std::string ResourcePath, std::string Path){
    SDL_Surface * LoadS = SDL_LoadBMP((ResourcePath+"Textures/null.bmp").c_str());
    Missing = SDL_CreateTextureFromSurface(Render, LoadS);
    SDL_DestroySurface(LoadS);
    FilePath = Path;
    DirectoryPath = ResourcePath;
}


template<typename T>
inline bool Register(Registry<T> * registry, SDL_Renderer * Render, std::string id, T data){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            return false;
        }
    }


    std::string ModName;
    std::string Name;
    bool Section = false;
    for (int i = 0; i < id.length(); i++){
        if (id[i] == ':'){
            Section = true;
        }
        else{
            if (Section){
                Name += id[i];
            }
            else{
                ModName += id[i];
            }
        }
    }
    SDL_Surface * LoadS = SDL_LoadBMP(registry->DirectoryPath+"Textures/"+registry->Path+"/"+Name+".bmp");
    if (LoadS){
        data.Texture = SDL_CreateTextureFromSurface(Render, LoadS);
    }
    else{
        data.Texture = registry->Missing;
    }
    SDL_DestroySurface(LoadS);
    registry->IDs.push_back(id);
    registry->Data.push_back(data);
    return true;
}


template<typename T>
inline bool Unregister(Registry<T> * registry, std::string id){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            registry->IDs.erase(registry->IDs.begin() + i);
            return true;
        }
    }
    return false;
}


template<typename T>
inline T GetValueFromRegistry(Registry<T> * registry, std::string id){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            return registry->Data[i];
        }
    }
}


template<typename T>
inline T Create(Registry<T> * registry, std::string id){
    T data = GetValueFromRegistry(registry, id);
    return data;
}
