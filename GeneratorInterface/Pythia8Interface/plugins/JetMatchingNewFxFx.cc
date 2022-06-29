#include "JetMatchingNewFxFx.h"

JetMatchingNewFxFx::JetMatchingNewFxFx(const edm::ParameterSet& iConfig) 
  : setMad_(iConfig.getParameter<bool>("setMad")),
    scheme_(iConfig.getParameter<int>("scheme")),
    merge_(iConfig.getParameter<bool>("merge")),
    jetAlgorithm_(iConfig.getParameter<int>("jetAlgorithm")),
    etaJetMax_(iConfig.getParameter<double>("etaJetMax")),
    coneRadius_(iConfig.getParameter<double>("coneRadius")),
    slowJetPower_(iConfig.getParameter<int>("slowJetPower")),
    qCut_(iConfig.getParameter<double>("qCut")),
    doFxFx_(iConfig.getParameter<bool>("doFxFx")),
    qCutME_(iConfig.getParameter<double>("qCutME")),
    nQmatch_(iConfig.getParameter<int>("nQmatch")),
    nJetMax_(iConfig.getParameter<int>("nJetMax")) {}

bool JetMatchingNewFxFx::initAfterBeams() {return true;}

bool JetMatchingNewFxFx::doVetoProcessLevel(Pythia8::Event& event) {return true;}
