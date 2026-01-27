#pragma once

#include "Yantra/Layer.h"
#include "Yantra/Timestep.h"

namespace Yantra {

class YANTRA_API ImGuiLayer : public Layer {
public:
  ImGuiLayer();
  ~ImGuiLayer();

  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnImGuiRender() override;
  virtual void OnUpdate(TimeStep ts) override;

  void Begin();
  void End();

private:
  float m_Time = 0.0f;
};

} // namespace Yantra
