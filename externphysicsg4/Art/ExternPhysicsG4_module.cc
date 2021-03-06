////////////////////////////////////////////////////////////////////////
// Class:       ExternPhysicsG4
// Module Type: producer
// File:        ExternPhysicsG4_module.cc
//
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include <memory>
#include <iostream>
#include <iomanip>

#include "G4PhysListFactoryAlt.hh"

// allow ourselves to extend the short names for physics ctor addition/replace
// along the same lines as EMX, EMY, etc
#include "G4PhysListRegistry.hh"

// allow ourselves to give the user extra info about available physics ctors
#include "G4PhysicsConstructorFactory.hh"

namespace extg4 {

  class ExternPhysicsG4 : public art::EDProducer {
  public:
    explicit ExternPhysicsG4(fhicl::ParameterSet const & p);
    // The destructor generated by the compiler is fine for classes
    // without bare pointers or other resource use.

    // Plugins should not be copied or assigned.
    ExternPhysicsG4(ExternPhysicsG4 const &) = delete;
    ExternPhysicsG4(ExternPhysicsG4 &&) = delete;
    ExternPhysicsG4 & operator = (ExternPhysicsG4 const &) = delete;
    ExternPhysicsG4 & operator = (ExternPhysicsG4 &&) = delete;

  private:
    // Required functions.
    void produce(art::Event & e) override;

    // Optional functions.
    void endJob() override;

    // Internal functions
    void PrintAvailable(int verb=1);

    std::string fGenieModuleLabel;
  };

  ExternPhysicsG4::ExternPhysicsG4(fhicl::ParameterSet const & p)
    : EDProducer{p}
  {

    // set a short name for the plugin
    G4PhysListRegistry* plreg = G4PhysListRegistry::Instance();
    plreg->AddPhysicsExtension("PY8DK","Py8DecayerPhysics");

    //// start TEST -----------------------------------------------
    // pick physics list
    std::string physListName = "FTFP_BERT+PY8DK";

    g4alt::G4PhysListFactory factory;
    G4VModularPhysicsList* physicsList = nullptr;
    factory.SetDefaultReferencePhysList("NO_DEFAULT_PHYSLIST");

    physicsList = factory.GetReferencePhysList(physListName);

    if ( ! physicsList ) {
      int verbosity = 1;
      PrintAvailable(verbosity);

      // if we can't get what the user asked for...
      //    don't go on to use something else, that's confusing
      G4ExceptionDescription ED;
      ED << "The factory for the physicslist ["
         << physListName
         << "] does not exist!"
         << G4endl;
      G4Exception("extensibleFactory",
                  "extensibleFactory001", FatalException, ED);
      exit(42);
    } else {
      int verbosity = 1;
      PrintAvailable(verbosity);

      delete physicsList;
    }
    //// end TEST -----------------------------------------------

    produces<std::vector<std::string> >();
  }

  void ExternPhysicsG4::produce(art::Event & e)
  {
    // Implementation of required member function here.
    auto vec = std::make_unique<std::vector<std::string>>();

    vec->push_back("ExternPhysicsG4");

    e.put(std::move(vec));
  }

  void ExternPhysicsG4::endJob()
  {
  }

  void ExternPhysicsG4::PrintAvailable(int verbosity) {

    G4cout << G4endl;
    G4cout << "extensibleFactory: here are the available physics lists:"
           << G4endl;
    g4alt::G4PhysListFactory factory;
    factory.PrintAvailablePhysLists();

    // if user asked for extra verbosity then print physics ctors as well
    if ( verbosity > 1 ) {
      G4cout << G4endl;
      G4cout << "extensibleFactory: "
             << "here are the available physics ctors that can be added:"
             << G4endl;
      G4PhysicsConstructorRegistry* g4pctorFactory =
        G4PhysicsConstructorRegistry::Instance();
      g4pctorFactory->PrintAvailablePhysicsConstructors();
    }

  }

} // namespace

DEFINE_ART_MODULE(extg4::ExternPhysicsG4)
