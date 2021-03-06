#ifndef Geometry_HGCalCommonData_HGCalTypes_h
#define Geometry_HGCalCommonData_HGCalTypes_h

#include <cmath>
#include <cstdint>
#include <vector>

class HGCalTypes {
public:
  HGCalTypes() {}

  enum class CellType {
    UndefinedType = -1,
    CentralType = 0,
    BottomLeftEdge = 1,
    LeftEdge = 2,
    TopLeftEdge = 3,
    TopRightEdge = 4,
    RightEdge = 5,
    BottomRightEdge = 6,
    BottomCorner = 11,
    BottomLeftCorner = 12,
    TopLeftCorner = 13,
    TopCorner = 14,
    TopRightCorner = 15,
    BottomRightCorner = 16
  };

  enum WaferCorner {
    WaferCorner0 = 0,
    WaferCorner1 = 1,
    WaferCorner2 = 2,
    WaferCorner3 = 3,
    WaferCorner4 = 4,
    WaferCorner5 = 5
  };

  enum WaferPosition {
    UnknownPosition = -1,
    WaferCenter = 0,
    CornerCenterYp = 1,
    CornerCenterYm = 2,
    CornerCenterXp = 3,
    CornerCenterXm = 4
  };

  enum WaferType { WaferFineThin = 0, WaferCoarseThin = 1, WaferCoarseThick = 2, WaferFineThick = 3 };

  enum WaferSizeType {
    WaferFull = 0,
    WaferFive = 1,
    WaferChopTwo = 2,
    WaferChopTwoM = 3,
    WaferHalf = 4,
    WaferSemi = 5,
    WaferSemi2 = 6,
    WaferThree = 7,
    WaferOut = 99
  };

  static constexpr int32_t WaferCornerMin = 3;

  enum TileType { TileFine = 0, TileCoarseCast = 1, TileCoarseMould = 2 };

  enum TileSiPMType { SiPMUnknown = 0, SiPMSmall = 2, SiPMLarge = 4 };

  static int32_t packTypeUV(int type, int u, int v);
  static int32_t getUnpackedType(int id);
  static int32_t getUnpackedU(int id);
  static int32_t getUnpackedV(int id);

private:
  static constexpr int32_t facu_ = 1;
  static constexpr int32_t facv_ = 100;
  static constexpr int32_t factype_ = 1000000;
  static constexpr int32_t signu_ = 10000;
  static constexpr int32_t signv_ = 100000;
  static constexpr int32_t maxuv_ = 100;
  static constexpr int32_t maxsign_ = 10;
};

#endif
