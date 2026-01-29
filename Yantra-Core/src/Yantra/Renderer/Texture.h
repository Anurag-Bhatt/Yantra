#pragma once

#include "Yantra/Core.h"
#include <memory>
#include <string>

namespace Yantra {

class Texture {
public:
  virtual ~Texture() = default;

  virtual uint32 GetWidth() const = 0;
  virtual uint32 GetHeight() const = 0;

  virtual void Bind(uint32 slot = 0) const = 0;
};

class Texture2D : public Texture {
public:
  static std::shared_ptr<Texture2D> Create(const std::string &path);
};

} // namespace Yantra
