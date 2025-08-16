//
// Created by SF on 03.07.25.
//
module;
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <functional>
#include <optional>

export module SharedState:ResourceManager;

import Logger;
import Utils;

export template<typename DERIVED, typename T>
class ResourceManager {
    public:
    ResourceManager(const std::string& l_filename) {
        std::string filePath = Utils::get_project_path() + "/resources/config/" + l_filename;
        filePath = Utils::formatPath(filePath);
        load_resource_path_pairs(filePath);

    }
    virtual ~ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    T* get(const std::string& l_id) {
        Logger::getInstance().log("ResourceManager::get: requested  id " + l_id);
        auto found_resource = m_resources.find(l_id);
        if(found_resource != m_resources.end()){
            //something found
            found_resource->second.second++;
            Logger::getInstance().log("ResourceManager::get: Returning object " + l_id +
                                      "; called in total: " +std::to_string(found_resource->second.second));
            return found_resource->second.first.get();
        }
        Logger::getInstance().log("ResourceManager::get: could not find " + l_id);
        return nullptr;
    }
    void loadResource(const std::string& l_id) {
        // is provided id known at all?
        if (auto resourcePath = get_resource_path(l_id)) {
            Logger::getInstance().log("ResourceManager::loadResource: received resourcePath " + *resourcePath);
            // if so, check if already loaded
            auto found_resource = m_resources.find(l_id);
            if(found_resource != m_resources.end()) {
                found_resource->second.second++;
                Logger::getInstance().log("ResourceManager::get: Resource id " + l_id +
                " is known, increased count to " + std::to_string(found_resource->second.second));
                return;
            }
            // if not loaded, load it to resources
            std::string filePath = Utils::formatPath(Utils::get_project_path() + "\\" + *resourcePath);

            Logger::getInstance().log("ResourceManager::loadResource: Resource id " + l_id +
            " not loaded yet, loading from path " + filePath);
            std::unique_ptr<T> resource = load(filePath);
            m_resources.emplace(l_id, std::make_pair(std::move(resource), 1));
        }else{
            // resource is not available, just log it
            Logger::getInstance().log("Error in ResourceManager::loadResource: could not load " + l_id);
        }
    }
protected:
    std::unique_ptr<T> load(const std::string& l_path) {
        Logger::getInstance().log("ResourceManager::load: loading path"  + l_path);
        auto resource = dynamic_cast<DERIVED*>(this)->load(l_path);
        return resource;
    }


private:
    std::optional<std::string> get_resource_path(const std::string& l_id) {
        auto found = m_resource_paths.find(l_id);
        if (found == m_resource_paths.end()) {
            return std::nullopt;
        }
        return found->second;
    }
    void load_resource_path_pairs(const std::string& l_id) {
        std::ifstream ff;
        ff.open(l_id);
        if (!ff.is_open()) {
            Logger::getInstance().log("Error in ResourceManager::load_resource_path_pairs: "
                                     "could not open " + std::string(l_id));
            throw std::runtime_error("Error in ResourceManager::load_resource_path_pairs: "
                                     "could not open " + std::string(l_id));
        }
        std::string line;
        while (std::getline(ff, line)) {
            std::stringstream ss{line};
            std::string first{};
            std::string second{};
            ss >> first >> second;
            Logger::getInstance().log("ResourceManager::load_resource_path_pairs: id: "
                + first + " path: " + second);
            m_resource_paths.emplace(first, second);
        }
        ff.close();
    }
    std::unordered_map<std::string, std::pair<std::unique_ptr<T>, int>> m_resources;
    std::unordered_map<std::string, std::string> m_resource_paths;
};