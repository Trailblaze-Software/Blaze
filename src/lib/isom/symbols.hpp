#pragma once

#include "isom/colors.hpp"

class ISOMSymbol {
  public:
  enum ISOMSymbolEnum {
    Contour,
    IndexContour,
    FormLine,

    OpenLand,
    RoughOpenLand,
    Forest,

    VegetationSlow,
    VegetationWalk,
    VegetationFight,

    Building,
  };

  private:

  ISOMSymbolEnum m_symbol;

  public:

  ISOMSymbol(ISOMSymbolEnum symbol) : m_symbol(symbol) {}

  CMYKColor color() const {
    switch (m_symbol) {
      case Contour:
        return Brown;
      case IndexContour:
        return Brown;
      case FormLine:
        return Brown;

      case OpenLand:
        return Yellow;
      case RoughOpenLand:
        return Yellow * 0.5;
      case Forest:
        return White;
      case VegetationSlow:
        return Green * 0.3;
      case VegetationWalk:
        return Green * 0.6;
      case VegetationFight:
        return Green;

      case Building:
        return Black;
    }
    __builtin_unreachable();
  }

};
