#### one of these causes _fhicl_ headers to get confused
#find_package(Geant4 REQUIRED)
#include(${Geant4_USE_FILE})

include_directories($ENV{GEANT4_FQ_DIR}/include/Geant4)
include_directories($ENV{PYTHIA8_INC})

find_library( PYTHIA8_LIBRARIES NAMES pythia8 PATHS $ENV{PYTHIA8_LIB} NO_DEFAULT_PATH )

# list of G4 pre-found library names can be seen
#    cetbuildtools/v7_15_01/Modules/FindUpsGeant4.cmake

art_make(LIBRARY_NAME     externphysicsg4_art
         LIB_LIBRARIES    externphysicsg4_Physics
         # trim this list ...
        ${G4GLOBAL}
        ${G4PARTICLE}
        ${G4EVENT}
        ${G4INTERCOMS}
        ${G4INTERFACES}
        ${G4TRACKING}
        ${G4PHYSICSLISTS} ## this isn't the name used ...
        ${G4PROCESSES}
        ${G4PARTICLES}
        # some G4 pulls in CLHEP
        ${CLHEP}
        # external physics libraries
        ${PYTHIA8_LIBRARIES}

         MODULE_LIBRARIES
        externphysicsg4_Physics
        ${G4PHYSICSLISTS}
        ${G4RUN}  # G4Exception
        ${G4GLOBAL}
        )

install_headers()
install_fhicl()
install_source()
