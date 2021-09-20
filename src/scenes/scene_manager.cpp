#include "../include/scenes/scene_manager.h"
#include <string>

void SceneManager::OnRender() {
    if (ctx_.scene_ != current_scene_) {
        if (scenes_.count(current_scene_) != 0) {
            scenes_.at(current_scene_)->OnExit();
        }
        current_scene_ = ctx_.scene_;
        scenes_.at(current_scene_)->OnCreate();
    }
    if (scenes_.count(current_scene_) != 0) {
        scenes_.at(current_scene_)->OnRender();
    }
}

void SceneManager::OnExit() const {
    if (scenes_.count(current_scene_) != 0) {
        scenes_.at(current_scene_)->OnExit();
    }
}
void SceneManager::Put(const std::string& name, IScene* const scene) {
    scenes_[name] = std::unique_ptr<IScene>(scene);
}
SceneManager::SceneManager(const Context& ctx) : ctx_(ctx) {}
