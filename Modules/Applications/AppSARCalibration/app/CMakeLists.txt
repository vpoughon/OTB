set(OTBAppSARCalibration_LINK_LIBS
  ${OTBSARCalibration_LIBRARIES}
  ${OTBApplicationEngine_LIBRARIES}
)

otb_create_application(
  NAME           SarRadiometricCalibration
  SOURCES        otbSarRadiometricCalibration.cxx
  LINK_LIBRARIES ${${otb-module}_LIBRARIES})

otb_create_application(
  NAME           SARCalibration
  SOURCES        otbSARCalibration.cxx
  LINK_LIBRARIES ${${otb-module}_LIBRARIES})

otb_create_application(
  NAME           SARDeburst
  SOURCES        otbSARDeburst.cxx
  LINK_LIBRARIES ${${otb-module}_LIBRARIES})
