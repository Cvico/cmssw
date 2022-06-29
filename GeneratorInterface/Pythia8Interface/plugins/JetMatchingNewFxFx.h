#ifndef GeneratorInterface_Pythia8Interface_JetMatchingNewFxFx_h
#define GeneratorInterface_Pythia8Interface_JetMatchingNewFxFx_h

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PluginManager/interface/PluginFactory.h"
#include "Pythia8/Pythia.h"
#include <memory>
#include "GeneratorInterface/Pythia8Interface/interface/CustomHook.h"


// Adapted by Kevin Pedro to run on cmssw as a user hook
class JetMatchingNewFxFx : public Pythia8::UserHooks {
public:
  JetMatchingNewFxFx(const edm::ParameterSet& iConfig);
  ~JetMatchingNewFxFx() override {}

  bool initAfterBeams() override;

  bool canVetoProcessLevel() override { return true; }
  bool doVetoProcessLevel(Pythia8::Event& event) override;
protected:
  bool setMad_;
  int scheme_;
  bool merge_;
  int jetAlgorithm_;
  double etaJetMax_;
  double coneRadius_;
  int slowJetPower_;
  double qCut_;
  bool doFxFx_;
  double qCutME_;
  int nQmatch_;
  int nJetMax_;
};

REGISTER_USERHOOK(JetMatchingNewFxFx);
#endif
