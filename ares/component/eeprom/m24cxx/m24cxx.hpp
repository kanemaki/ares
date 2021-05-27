#pragma once

namespace ares {

struct M24Cxx {
  enum class Type : u32 {
    M24C01,  // 1024 cells => 128 x 8-bit x 1-block
    M24C02,  // 2048 cells => 256 x 8-bit x 1-block
    M24C04,  // 4096 cells => 256 x 8-bit x 2-blocks
    M24C08,  // 8192 cells => 256 x 8-bit x 4-blocks
    M24C16,  //16384 cells => 256 x 8-bit x 8-blocks
  };

  auto size() const -> u32 {
    switch(type) { default:
    case Type::M24C01: return  128;
    case Type::M24C02: return  256;
    case Type::M24C04: return  512;
    case Type::M24C08: return 1024;
    case Type::M24C16: return 2048;
    }
  }

  auto writeProtected() const -> bool {
    return !writable;
  }

  auto setWriteProtected(bool protect) -> void {
    writable = !protect;
  }

  //m24cxx.cpp
  auto power(Type, n3 enableID = 0) -> void;
  auto read() -> n1;
  auto write(maybe<n1> clock, maybe<n1> data) -> void;
  auto erase(n8 fill = 0xff) -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  n8 memory[2048];

private:
  //m24cxx.cpp
  auto select() -> bool;
  auto load() -> bool;
  auto store() -> bool;

  static constexpr bool Acknowledge = 0;

  enum class Mode : u32 {
    Standby,
    Device,
    Address,
    Read,
    Write,
  };

  struct Line {
    //m24cxx.cpp
    auto write(n1 data) -> void;

    n1 lo;
    n1 hi;
    n1 fall;
    n1 rise;
    n1 line;
  };

  Type type;
  Mode mode;
  Line clock;
  Line data;
  n3   enable;
  n8   counter;
  n8   device;
  n8   address;
  n8   input;
  n8   output;
  n1   response;
  n1   writable;
};

}
