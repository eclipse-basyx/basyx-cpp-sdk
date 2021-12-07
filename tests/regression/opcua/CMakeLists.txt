###############################################
###              tests_opcua                ###
###############################################

cmake_minimum_required(VERSION 3.1.0)
project(tests_opcua)

add_executable(tests_opcua)

target_sources(tests_opcua
    PRIVATE
	"OPCUATestSetup.h"
	"modelprovider/test_OPCUAModelProvider.cpp"
	"modelprovider/test_OPCUALegacyModelVABAccess.cpp"
	"modelprovider/test_OPCUAModelProviderTypeMeta.cpp"
	"modelprovider/test_AASAggregatorProvider.cpp"
	"utilities/test_OPCUAUtilities.cpp"
	"utilities/test_OPUAClientServices.cpp"
	"utilities/test_ModeProviderUtilities.cpp"
	"node/test_AssetAdministrationShellNodeManager.cpp"
	"node/test_SubmodelNodeManager.cpp"
	"node/test_PropertyNodeManager.cpp"
	"api/test_ApiAssetAdminstrationShell.cpp"
	"api/test_ApiSubmodel.cpp"
	"api/test_ApiProperty.cpp"
)

target_link_libraries(tests_opcua basyx::util basyx::shared lib::gtest basyx::vab tests::support BaSyx::AAS tests::main basyx::opcua)
gtest_discover_tests(tests_opcua)

diagnostics_print(tests_opcua)