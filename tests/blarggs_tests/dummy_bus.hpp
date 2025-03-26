#pragma once

#include "simple_bus.hpp"
#include <string>

class DummyBus : public SimpleBus
{
public:
  uint8_t Read(uint16_t addr) override;
  void Write(uint16_t addr, uint8_t data) override;
  [[nodiscard]] bool IsTestPassed() const;
  [[nodiscard]] bool IsTestCompleted() const;
  [[nodiscard]] std::string GetMessage() const;

private:
  std::string m_message;
};
