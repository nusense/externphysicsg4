include(CetTest)

cet_enable_asserts()

#
# Test XYZZY plug-in
#
simple_plugin( TestModule "module"
  ${ART_FRAMEWORK_CORE}
  ${ART_FRAMEWORK_PRINCIPAL}
  ${ART_FRAMEWORK_SERVICES_REGISTRY}
  ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
  art_Persistency_Provenance
  canvas
  ${MF_MESSAGELOGGER}

  ${FHICLCPP}
  cetlib cetlib_except
  ${CLHEP}
  NO_INSTALL
)


#
# XYZZY tests
# ------------------------------
#
#
cet_test(TestModule_test1 HANDBUILT
  TEST_EXEC lar
  TEST_ARGS --rethrow-all --config TestModule.fcl -n 10
  DATAFILES
    TestModule.fcl
)
