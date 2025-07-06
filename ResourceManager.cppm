//
// Created by SF on 03.07.25.
//
module;
#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>
export module SharedState:ResourceManager;


export template<typename DERIVED, typename T>
class ResourceManager {
    public:
    ResourceManager(const std::string_view l_paths_name) {
        load_resource_path_pairs(l_paths_name);

    }
    virtual ~ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    T& get(const std::string_view l_id) {
        T t;
        return t;
    }
    void loadResource(const std::string& l_id) {
        if (auto resourcePath = get_resource_path(l_id)) {
            std::unique_ptr<T> resource = load(*resourcePath);
        }
    }
protected:
    std::unique_ptr<T> load(const std::string& l_id) {
        auto resource = dynamic_cast<DERIVED*>(this)->load(l_id);
        return resource;
    }
    std::optional<std::string> get_resource_path(const std::string& l_id) {
        auto found = m_resource_paths.find(l_id);
        if (found == m_resource_paths.end()) {
            return std::nullopt;
        }
        return found->second;
    }

private:
    void load_resource_path_pairs(const std::string_view l_id) {

    }
    std::unordered_map<std::string, std::pair<std::unique_ptr<T>, int>> m_resources;
    std::unordered_map<std::string, std::string> m_resource_paths;
};