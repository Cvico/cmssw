/*
 *  See header file for a description of this class.
 *
 *  \author N. Amapane - INFN Torino
 */

#include "MagneticField/VolumeBasedEngine/interface/MagGeometry.h"
#include "MagneticField/VolumeGeometry/interface/MagVolume.h"
#include "MagneticField/VolumeGeometry/interface/MagVolume6Faces.h"
#include "MagneticField/Layers/interface/MagBLayer.h"
#include "MagneticField/Layers/interface/MagESector.h"

#include "Utilities/BinningTools/interface/PeriodicBinFinderInPhi.h"

#include "FWCore/Utilities/interface/isFinite.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <iostream>

using namespace std;
using namespace edm;

MagGeometry::MagGeometry(int geomVersion,
                         const std::vector<MagBLayer*>& tbl,
                         const std::vector<MagESector*>& tes,
                         const std::vector<MagVolume6Faces*>& tbv,
                         const std::vector<MagVolume6Faces*>& tev)
    : MagGeometry(geomVersion,
                  reinterpret_cast<std::vector<MagBLayer const*> const&>(tbl),
                  reinterpret_cast<std::vector<MagESector const*> const&>(tes),
                  reinterpret_cast<std::vector<MagVolume6Faces const*> const&>(tbv),
                  reinterpret_cast<std::vector<MagVolume6Faces const*> const&>(tev)) {}

MagGeometry::MagGeometry(int geomVersion,
                         const std::vector<MagBLayer const*>& tbl,
                         const std::vector<MagESector const*>& tes,
                         const std::vector<MagVolume6Faces const*>& tbv,
                         const std::vector<MagVolume6Faces const*>& tev)
    : lastVolume(nullptr),
      theBLayers(tbl),
      theESectors(tes),
      theBVolumes(tbv),
      theEVolumes(tev),
      cacheLastVolume(true),
      geometryVersion(geomVersion) {
  vector<double> rBorders;

  for (vector<MagBLayer const*>::const_iterator ilay = theBLayers.begin(); ilay != theBLayers.end(); ++ilay) {
    LogTrace("MagGeometry") << "  Barrel layer at " << (*ilay)->minR() << endl;
    //FIXME assume layers are already sorted in minR
    rBorders.push_back((*ilay)->minR() * (*ilay)->minR());
  }

  theBarrelBinFinder = new MagBinFinders::GeneralBinFinderInR<double>(rBorders);

#ifdef EDM_ML_DEBUG
  for (vector<MagESector const*>::const_iterator isec = theESectors.begin(); isec != theESectors.end(); ++isec) {
    LogTrace("MagGeometry") << "  Endcap sector at " << (*isec)->minPhi() << endl;
  }
#endif

  //FIXME assume sectors are already sorted in phi
  //FIXME: PeriodicBinFinderInPhi gets *center* of first bin
  int nEBins = theESectors.size();
  if (nEBins > 0)
    theEndcapBinFinder = new PeriodicBinFinderInPhi<float>(theESectors.front()->minPhi() + Geom::pi() / nEBins, nEBins);

  // Compute barrel dimensions based on geometry version
  switch (geomVersion >= 120812 ? 0 : (geomVersion >= 90812 ? 1 : 2)) {
    case 0:  // since 120812
      barrelRsq1 = 172.400f * 172.400f;
      barrelRsq2 = 308.735f * 308.735f;
      barrelZ0 = 350.000f;
      barrelZ1 = 633.290f;
      barrelZ2 = 662.010f;
      break;
    case 1:  // version 90812 (no longer in use)
      barrelRsq1 = 172.400f * 172.400f;
      barrelRsq2 = 308.755f * 308.755f;
      barrelZ0 = 350.000f;
      barrelZ1 = 633.890f;
      barrelZ2 = 662.010f;
      break;
    case 2:  // versions 71212, 90322
      barrelRsq1 = 172.400f * 172.400f;
      barrelRsq2 = 308.755f * 308.755f;
      barrelZ0 = 350.000f;
      barrelZ1 = 633.290f;
      barrelZ2 = 661.010f;
      break;
  }
}

MagGeometry::~MagGeometry() {
  if (theBarrelBinFinder != nullptr)
    delete theBarrelBinFinder;
  if (theEndcapBinFinder != nullptr)
    delete theEndcapBinFinder;

  for (vector<MagBLayer const*>::const_iterator ilay = theBLayers.begin(); ilay != theBLayers.end(); ++ilay) {
    delete (*ilay);
  }

  for (vector<MagESector const*>::const_iterator ilay = theESectors.begin(); ilay != theESectors.end(); ++ilay) {
    delete (*ilay);
  }
}

// Return field vector at the specified global point
GlobalVector MagGeometry::fieldInTesla(const GlobalPoint& gp) const {
  MagVolume const* v = nullptr;

  v = findVolume(gp);
  if (v != nullptr) {
    return v->fieldInTesla(gp);
  }

  // Fall-back case: no volume found

  if (edm::isNotFinite(gp.mag())) {
    LogWarning("InvalidInput") << "Input value invalid (not a number): " << gp << endl;

  } else {
    LogWarning("MagneticField") << "MagGeometry::fieldInTesla: failed to find volume for " << gp << endl;
  }
  return GlobalVector();
}

// Linear search implementation (just for testing)
MagVolume const* MagGeometry::findVolume1(const GlobalPoint& gp, double tolerance) const {
  MagVolume6Faces const* found = nullptr;

  int errCnt = 0;
  if (inBarrel(gp)) {  // Barrel
    for (vector<MagVolume6Faces const*>::const_iterator v = theBVolumes.begin(); v != theBVolumes.end(); ++v) {
      if ((*v) == nullptr) {  //FIXME: remove this check
        LogError("MagGeometry") << endl << "***ERROR: MagGeometry::findVolume: MagVolume for barrel not set" << endl;
        ++errCnt;
        if (errCnt < 3)
          continue;
        else
          break;
      }
      if ((*v)->inside(gp, tolerance)) {
        found = (*v);
        break;
      }
    }

  } else {  // Endcaps
    for (vector<MagVolume6Faces const*>::const_iterator v = theEVolumes.begin(); v != theEVolumes.end(); ++v) {
      if ((*v) == nullptr) {  //FIXME: remove this check
        LogError("MagGeometry") << endl << "***ERROR: MagGeometry::findVolume: MagVolume for endcap not set" << endl;
        ++errCnt;
        if (errCnt < 3)
          continue;
        else
          break;
      }
      if ((*v)->inside(gp, tolerance)) {
        found = (*v);
        break;
      }
    }
  }

  return found;
}

// Use hierarchical structure for fast lookup.
MagVolume const* MagGeometry::findVolume(const GlobalPoint& gp, double tolerance) const {
  // Check volume cache
  auto lastVolumeCheck = lastVolume.load(std::memory_order_acquire);
  if (lastVolumeCheck != nullptr && lastVolumeCheck->inside(gp)) {
    return lastVolumeCheck;
  }

  MagVolume const* result = nullptr;
  if (inBarrel(gp)) {  // Barrel
    double aRsq = gp.perp2();
    int bin = theBarrelBinFinder->binIndex(aRsq);

    // Search up to 3 layers inwards. This may happen for very thin layers.
    for (int bin1 = bin; bin1 >= max(0, bin - 3); --bin1) {
      LogTrace("MagGeometry") << "Trying layer at R " << theBLayers[bin1]->minR() << " " << sqrt(aRsq) << endl;
      result = theBLayers[bin1]->findVolume(gp, tolerance);
      LogTrace("MagGeometry") << "***In blayer " << bin1 - bin << " " << (result == nullptr ? " failed " : " OK ")
                              << endl;
      if (result != nullptr)
        break;
    }

  } else {  // Endcaps
    Geom::Phi<float> phi = gp.phi();
    if (theEndcapBinFinder != nullptr && !theESectors.empty()) {
      int bin = theEndcapBinFinder->binIndex(phi);
      LogTrace("MagGeometry") << "Trying endcap sector at phi " << theESectors[bin]->minPhi() << " " << phi << endl;
      result = theESectors[bin]->findVolume(gp, tolerance);
      LogTrace("MagGeometry") << "***In guessed esector " << (result == nullptr ? " failed " : " OK ") << endl;
    } else
      edm::LogError("MagGeometry") << "Endcap empty";
  }

  if (result == nullptr && tolerance < 0.0001) {
    // If search fails, retry with a 300 micron tolerance.
    // This is a hack for thin gaps on air-iron boundaries,
    // which will not be present anymore once surfaces are matched.
    LogTrace("MagGeometry") << "Increasing the tolerance to 0.03" << endl;
    result = findVolume(gp, 0.03);
  }

  if (cacheLastVolume)
    lastVolume.store(result, std::memory_order_release);

  return result;
}

bool MagGeometry::inBarrel(const GlobalPoint& gp) const {
  float aZ = fabs(gp.z());
  float aRsq = gp.perp2();

  return ((aZ < barrelZ0) || (aZ < barrelZ1 && aRsq > barrelRsq1) || (aZ < barrelZ2 && aRsq > barrelRsq2));
}
