otb_add_test(NAME leTuNormalBayesMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbNormalBayesMachineLearningModelNew)

otb_add_test(NAME leTuRandomForestsMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbRandomForestsMachineLearningModelNew)

otb_add_test(NAME leTvANNMachineLearningModel COMMAND otbSupervisedTestDriver
  otbANNMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/ann_model.txt
  )

# ------------------ Regression tests --------------------
otb_add_test(NAME leTvANNMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbNeuralNetworkRegressionTests
  )

otb_add_test(NAME leTvSVMMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbSVMRegressionTests
  )

otb_add_test(NAME leTvDecisionTreeMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbDecisionTreeRegressionTests
  )

otb_add_test(NAME leTvGradientBoostedTreeMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbGradientBoostedTreeRegressionTests
  )

otb_add_test(NAME leTvKNearestNeighborsMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbKNearestNeighborsRegressionTests
  )

otb_add_test(NAME leTvRandomForestsMachineLearningModelReg COMMAND otbSupervisedTestDriver
  otbRandomForestsRegressionTests
  )
# --------------------------------------------------------------

otb_add_test(NAME leTuSVMMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbSVMMachineLearningModelNew)

otb_add_test(NAME leTuDecisionTreeMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbDecisionTreeMachineLearningModelNew)

otb_add_test(NAME leTuKNearestNeighborsMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbKNearestNeighborsMachineLearningModelNew)

otb_add_test(NAME leTvSVMMachineLearningRegressionModel COMMAND otbSupervisedTestDriver
  otbSVMMachineLearningRegressionModel
  ${INPUTDATA}/abalone.scale
  ${TEMP}/svm_model_regression.txt
  )

otb_add_test(NAME leTvSVMMachineLearningModel COMMAND otbSupervisedTestDriver
  otbSVMMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/svm_model.txt
  )

otb_add_test(NAME leTuBoostMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbBoostMachineLearningModelNew)

otb_add_test(NAME leTvNormalBayesMachineLearningModel COMMAND otbSupervisedTestDriver
  otbNormalBayesMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/normalbayes_model.txt
  )

otb_add_test(NAME leTvGradientBoostedTreeMachineLearningModel COMMAND otbSupervisedTestDriver
  otbGradientBoostedTreeMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/gbt_model.txt
  )

otb_add_test(NAME leTvRandomForestsMachineLearningModel COMMAND otbSupervisedTestDriver
  otbRandomForestsMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/rf_model.txt
  )

otb_add_test(NAME leTuGradientBoostedTreeMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbGradientBoostedTreeMachineLearningModelNew)

otb_add_test(NAME leTuANNMachineLearningModelNew COMMAND otbSupervisedTestDriver
  otbANNMachineLearningModelNew)

otb_add_test(NAME leTvKNearestNeighborsMachineLearningModel COMMAND otbSupervisedTestDriver
  otbKNearestNeighborsMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/knn_model.txt
  )

otb_add_test(NAME leTvDecisionTreeMachineLearningModel COMMAND otbSupervisedTestDriver
  otbDecisionTreeMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/decisiontree_model.txt
  )

otb_add_test(NAME leTvBoostMachineLearningModel COMMAND otbSupervisedTestDriver
  otbBoostMachineLearningModel
  ${INPUTDATA}/letter.scale
  ${TEMP}/boost_model.txt
  )

otb_add_test(NAME leTuImageClassificationFilterNew COMMAND otbSupervisedTestDriver
  otbImageClassificationFilterNew)

otb_add_test(NAME leTvImageClassificationFilterSVM COMMAND otbSupervisedTestDriver
  --compare-image ${NOTOL}
  ${BASELINE}/leImageClassificationFilterSVMOutput.tif
  ${TEMP}/leImageClassificationFilterSVMOutput.tif
  otbImageClassificationFilter
  ${INPUTDATA}/ROI_QB_MUL_4.tif
  ${INPUTDATA}/ROI_QB_MUL_4_svmModel.txt
  ${TEMP}/leImageClassificationFilterSVMOutput.tif
  )

otb_add_test(NAME leTvDecisionTreeMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbDecisionTreeMachineLearningModelCanRead
  ${TEMP}/decisiontree_model.txt
  )
set_property(TEST leTvDecisionTreeMachineLearningModelCanRead APPEND PROPERTY DEPENDS leTvDecisionTreeMachineLearningModel)

otb_add_test(NAME leTvGradientBoostedTreeMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbGradientBoostedTreeMachineLearningModelCanRead
  ${TEMP}/gbt_model.txt
  )
set_property(TEST leTvGradientBoostedTreeMachineLearningModelCanRead PROPERTY DEPENDS leTvGradientBoostedTreeMachineLearningModel)

otb_add_test(NAME leTvNormalBayesMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbNormalBayesMachineLearningModelCanRead
  ${TEMP}/normalbayes_model.txt
  )
set_property(TEST leTvNormalBayesMachineLearningModelCanRead PROPERTY DEPENDS leTvNormalBayesMachineLearningModel)

otb_add_test(NAME leTvANNMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbNeuralNetworkMachineLearningModelCanRead
  ${TEMP}/ann_model.txt
  )
set_property(TEST leTvANNMachineLearningModelCanRead PROPERTY DEPENDS leTvANNMachineLearningModel)

otb_add_test(NAME leTvSVMMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbSVMMachineLearningModelCanRead
  ${TEMP}/svm_model.txt
  )
set_property(TEST leTvSVMMachineLearningModelCanRead PROPERTY DEPENDS leTvSVMMachineLearningModel)

otb_add_test(NAME leTvBoostMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbBoostMachineLearningModelCanRead
  ${TEMP}/boost_model.txt
  )
set_property(TEST leTvBoostMachineLearningModelCanRead PROPERTY DEPENDS leTvBoostMachineLearningModel)

otb_add_test(NAME leTvRandomForestsMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbRandomForestsMachineLearningModelCanRead
  ${TEMP}/rf_model.txt
  )
set_property(TEST leTvRandomForestsMachineLearningModelCanRead PROPERTY DEPENDS leTvRandomForestsMachineLearningModel)

otb_add_test(NAME leTvKNNMachineLearningModelCanRead COMMAND otbSupervisedTestDriver
  otbKNNMachineLearningModelCanRead
  ${TEMP}/knn_model.txt
  )
set_property(TEST leTvKNNMachineLearningModelCanRead PROPERTY DEPENDS leTvKNearestNeighborsMachineLearningModel)
