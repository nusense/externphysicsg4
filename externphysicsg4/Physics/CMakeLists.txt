# this library should have _no_ art dependence, just Geant4 + pythia8 etc

#find_package(Geant4 REQUIRED)
#include(${Geant4_USE_FILE})
#
#include_directories(${PROJECT_SOURCE_DIR}/include
#                    ${Geant4_INCLUDE_DIR}
#                    $ENV{PYTHIA8_INCLUDE_DIR})

include_directories($ENV{GEANT4_FQ_DIR}/include/Geant4)
include_directories($ENV{PYTHIA8_INC})

find_library( PYTHIA8_LIBRARIES NAMES pythia8 PATHS $ENV{PYTHIA8_LIB} NO_DEFAULT_PATH )

art_make(LIB_LIBRARIES
        # not all of these are necessary ... cut this down later
        ${G4GLOBAL}
        ${G4PARTICLE}
        ${G4EVENT}
        ${G4INTERCOMS}
        ${G4INTERFACES}
        ${G4RUN}
        ${G4TRACKING}
        ${G4PHYSICSLISTS}
        ${G4PROCESSES}
        ${G4PARTICLES}
        # some G4 pulls in CLHEP
        ${CLHEP}
        # external physics libraries
        ${PYTHIA8_LIBRARIES}
        )

install_headers()
install_fhicl()
install_source()
