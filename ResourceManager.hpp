//
// Created by Keen on 12/11/2021.
//

#ifndef ENEMATA_RESOURCEMANAGER_HPP
#define ENEMATA_RESOURCEMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

template<typename T, typename DERIVED>
class ResourceManager {
public:
    ResourceManager(const std::string& l_paths);
    // string is Identifier; unique_ptr holds resource, int counts how many times resources has been requested
    void loadResource(const std::string& l_resourceName);
    T* getResource(const std::string& l_resourceName);
    void removeResource(const std::string& l_resourceName);
    void clearResources();
private:
    std::unique_ptr<T> load(const std::string& l_resourceName);
    void loadPaths(const std::string l_paths);
    std::unordered_map<std::string, std::pair<std::unique_ptr<T>, int>> m_resources;
    std::unordered_map<std::string, std::string> m_resourcePaths;
    std::string m_paths;
};

template<typename T, typename DERIVED>
ResourceManager<T, DERIVED>::ResourceManager(const std::string &l_paths)
: m_resources()
, m_resourcePaths()
, m_paths(l_paths){
    loadPaths(l_paths);
}

template<typename T, typename DERIVED>
void ResourceManager<T, DERIVED>::loadResource(const std::string& l_resourceName) {
    auto foundResourcePath = m_resourcePaths.find((l_resourceName));
    if(foundResourcePath == m_resourcePaths.end()){
        std::cout << "WARNING in ResourceManager::loadResource: could not find entry \"" << l_resourceName << "\""
        << " in " << m_paths << "\n";
        return;
    }
    auto foundResourcePair = m_resources.find(l_resourceName);
    if(foundResourcePair != m_resources.end()){
        foundResourcePair->second.second++;
        return;
    }
    // requested resource not loaded yet, so load and add it to m_resources
    auto resource = load(foundResourcePath->second);
    m_resources.emplace(l_resourceName, std::make_pair(std::move(resource), 1));
}

template<typename T, typename DERIVED>
T* ResourceManager<T, DERIVED>::getResource(const std::string &l_resourceName) {
    auto foundResourcePair = m_resources.find(l_resourceName);
    if(foundResourcePair == m_resources.end()){
        throw std::runtime_error("Error in ResourceManager::getResource: could not find " + l_resourceName);
    }
    return foundResourcePair->second.first.get();
}

template<typename T, typename DERIVED>
void ResourceManager<T, DERIVED>::removeResource(const std::string &l_resourceName) {
    auto foundResource = m_resources.find(l_resourceName);
    if(foundResource == m_resources.end()){
        std::cout << "Warning in ResourceManager::removeResource: no resource " << l_resourceName << " to remove\n";
        return;
    }

    int& resourceCounter = foundResource->second.second;
    if(resourceCounter <= 0){ return; }

    resourceCounter--;
    if(resourceCounter == 0){
        m_resources.erase(foundResource);
    }
}

template<typename T, typename DERIVED>
void ResourceManager<T, DERIVED>::clearResources() {
    m_resources.clear();
}

template<typename T, typename DERIVED>
std::unique_ptr<T> ResourceManager<T, DERIVED>::load(const std::string& l_resourcePath) {
    return static_cast<DERIVED*>(this)->loadImplementation(l_resourcePath);
}

template<typename T, typename DERIVED>
void ResourceManager<T, DERIVED>::loadPaths(const std::string l_paths) {
    std::ifstream file;
    file.open(l_paths);
    if(!file.is_open()){
        throw std::runtime_error("Error in ResourceManager::loadPaths: could not open file " + l_paths);
    }
    std::string line{};
    while(std::getline(file, line)){
        if(line.empty()) continue;
        if(line[0] == '#') continue;

        std::stringstream ss{line};
        std::string left, right;
        ss >> left >> right;
        m_resourcePaths.emplace(left, right);
    }

}

#endif //ENEMATA_RESOURCEMANAGER_HPP
