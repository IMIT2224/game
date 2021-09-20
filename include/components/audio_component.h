#ifndef INCLUDE_COMPONENTS_AUDIO_COMPONENT_H_
#define INCLUDE_COMPONENTS_AUDIO_COMPONENT_H_
#include <string>

#include "../include/ecs/components.h"

class AudioComponent : public IComponent {
 public:
  std::string file_name_;

  explicit AudioComponent(std::string file_name) : file_name_(file_name) {}
};
#endif  // INCLUDE_COMPONENTS_AUDIO_COMPONENT_H_
