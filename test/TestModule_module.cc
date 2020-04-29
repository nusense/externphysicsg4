/**
 * @file   TestModule_module.cc
 * @brief  placeholder
 * @author Robert Hatcher (rhatcher@fnal.gov)
 * @date   2020-04-29
 *
 */

// framework libraries
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "canvas/Persistency/Provenance/Timestamp.h"
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
namespace fhicl { class ParameterSet; }

class TestModule: public art::EDAnalyzer {
    public:
  explicit TestModule(fhicl::ParameterSet const& pset);

private:
  void analyze(art::Event const & e) override;
}; // class TestModule


//------------------------------------------------------------------------------
TestModule::TestModule
  (fhicl::ParameterSet const& pset)
  : EDAnalyzer(pset)
{}

//------------------------------------------------------------------------------
void TestModule::analyze(art::Event const& event)
{
  mf::LogInfo("TestModule") << " ... nothing special";
}


DEFINE_ART_MODULE(TestModule)
