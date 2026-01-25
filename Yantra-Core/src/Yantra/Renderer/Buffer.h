#pragma once

#include <Yantra/Core.h>
#include <Yantra/Log.h>
#include <initializer_list>
#include <string>
#include <vector>

namespace Yantra {

enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  Float4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};

static uint32 ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {

  case ShaderDataType::None:
    return 0;
  case ShaderDataType::Float:
    return 4;
  case ShaderDataType::Float2:
    return 4 * 2;
  case ShaderDataType::Float3:
    return 4 * 3;
  case ShaderDataType::Float4:
    return 4 * 4;

  case ShaderDataType::Mat3:
    return 4 * 3 * 3;
  case ShaderDataType::Mat4:
    return 4 * 4 * 4;

  case ShaderDataType::Int:
    return 4;
  case ShaderDataType::Int2:
    return 4 * 2;
  case ShaderDataType::Int3:
    return 4 * 3;
  case ShaderDataType::Int4:
    return 4 * 4;

  case ShaderDataType::Bool:
    return 1;
  }
  YANTRA_CORE_ASSERT(false, "Unknow ShaderDataType");
  return 0;
}

struct BufferElement {
  std::string Name;
  ShaderDataType Type;
  uint32 Size;
  uint32 Offset;
  bool Normalized;

  BufferElement() {}
  BufferElement(ShaderDataType type, const std::string &name, bool normalized)
      : Type(type), Name(name), Normalized(normalized),
        Size(ShaderDataTypeSize(type)), Offset(0) {}

  uint32 GetComponentCount() const {
    switch (Type) {

    case ShaderDataType::None:
      return 0;
    case ShaderDataType::Float:
      return 1;
    case ShaderDataType::Float2:
      return 2;
    case ShaderDataType::Float3:
      return 3;
    case ShaderDataType::Float4:
      return 4;

    case ShaderDataType::Mat3:
      return 12;
    case ShaderDataType::Mat4:
      return 16;

    case ShaderDataType::Int:
      return 1;
    case ShaderDataType::Int2:
      return 2;
    case ShaderDataType::Int3:
      return 3;
    case ShaderDataType::Int4:
      return 4;

    case ShaderDataType::Bool:
      return 1;
    }

    YANTRA_CORE_ASSERT(false, "Unknow ShaderDataType");
    return 0;
  }
};

class YANTRA_API BufferLayout {
public:
  BufferLayout() {}

  BufferLayout(const std::initializer_list<BufferElement> elements)
      : m_Elements(elements) {
    CalcualteOffsetAndStride();
  }

  inline uint32 GetStride() const { return m_Stride; }
  inline const std::vector<BufferElement> &GetElements() const {
    return m_Elements;
  }

  std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
  std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
  std::vector<BufferElement>::const_iterator begin() const {
    return m_Elements.begin();
  }
  std::vector<BufferElement>::const_iterator end() const {
    return m_Elements.end();
  }

private:
  void CalcualteOffsetAndStride() {
    uint32 offset = 0;
    m_Stride = 0;
    for (auto &element : m_Elements) {
      element.Offset = offset;
      offset += element.Size;
      m_Stride += element.Size;
    }
  }

private:
  std::vector<BufferElement> m_Elements;
  uint32 m_Stride = 0;
};

class YANTRA_API VertexBuffer {
public:
  virtual ~VertexBuffer() {}

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual const BufferLayout &GetLayout() const = 0;
  virtual void SetLayout(BufferLayout &layout) = 0;

  static VertexBuffer *Create(float *vertices, uint32 size);
};

class YANTRA_API IndexBuffer {
public:
  virtual ~IndexBuffer() {}

  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual uint32 GetCount() const = 0;

  static IndexBuffer *Create(uint32 *indices, uint32 count);
};
} // namespace Yantra
