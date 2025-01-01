#pragma once
#include <vector>

class Registry{
public:
Registry();
std::vector <std::string> IDs;
std::vector <std::string> Names;
Registry(const Registry&) = delete;
Registry& operator=(const Registry&) = delete;
};


Registry::Registry(){

}



Registry * CreateRegistry(){
    return new Registry();
}


bool Register(Registry * registry, std::string id, std::string name){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            return false;
        }
    }
    registry->IDs.push_back(id);
    registry->Names.push_back(name);
    return true;
}


bool Unregister(Registry * registry, std::string id){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            registry->IDs.erase(registry->IDs.begin() + i);
            registry->Names.erase(registry->Names.begin() + i);
            return true;
        }
    }
    return false;
}


bool GetValueFromRegistry(Registry * registry, std::string id, std::string * name){
    std::vector<std::string> IDs = registry->IDs;
    for (int i = 0; i < IDs.size(); i++){
        if (IDs[i] == id){
            *name = registry->Names[i];
            return true;
        }
    }
    return false;
}
