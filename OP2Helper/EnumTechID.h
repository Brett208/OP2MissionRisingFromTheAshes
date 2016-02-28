#pragma once

// Note: This file contains an enum for all the research techIDs
//		 found in multitek.txt.


// Research techIDs
enum TechID
{
	// Group I (No predecessors)
	techCyberneticTeleoperation				= 3401,
	techEmergencyResponseSystems			= 3301,
	techEnvironmentalPsychology				= 3406,
	techFocusedMicrowaveProjection			= 3408,
	techHealthMaintenance					= 3303,
	techHighTemperatureSuperconductivity	= 3402,
	techHydroponicGrowingMedia				= 3403,
	techLargeScaleOpticalResonators			= 3407,
	techMetallogeny							= 3405,
	techMetalsReclamation					= 3302,
	techOffspringEnhancement				= 3304,
	techResearchTrainingPrograms			= 3305,
	techSeismology							= 3201,

	// Group II (All predecessors in Group I)
	techAdvancedVehiclePowerPlant			= 3901,
	techAutomatedDiagnosticExaminations		= 5307,
	techConsumerism							= 5101,
	techDIRTProceduralReview				= 5305,
	techDisasterResistantHousing			= 8105,
	techExpandedHousing						= 8104,
	techHeatDissipationSystemsPlymouth		= 5601,
	techHypnopaediaEden						= 5309,
	techHypnopaediaPlymouth					= 5310,
	techLeisureStudies						= 3306,
	techMobileWeaponsPlatform				= 3851,
	techPublicPerformance					= 5108,
	techRareOreProcessing					= 5110,
	techRecyclerPostprocessing				= 5306,
	techRobotAssistMechanicEden				= 5051,
	techRobotAssistMechanicPlymouth			= 5052,
	techRoboticImageProcessing				= 5318,
	techVulcanology							= 3202,

	// Group III (All predecessors in Group II or earlier)
	techAdvancedCombatChassis				= 5201,
	techAdvancedRoboticManipulatorArmEden	= 7213,
	techAdvancedRoboticManipulatorArmPlymouth = 7214,
	techDissipatingAdhesives				= 5202,
	techEnhancedDefensizeFortifications		= 8306,
	techExplosiveCharges					= 7102,
	techForumReconfiguration				= 5408,
	techGeothermalPower						= 5115,
	techHotCrackingColumnEfficiency			= 7202,
	techIndependentTurretPowerSystems		= 5111,
	techLavaDefenses						= 5701,
	techMagnetohydrodynamics				= 5107,
	techMeteorology							= 5302,
	techMultitainmentConsoleUpgrade			= 8307,
	techRareOreExtraction					= 7201,
	techReinforcedVehicleConstruction		= 5317,
	techScoutClassDriveTrainRefit			= 7206,
	techSmelterPostprocessing				= 7203,

	// Group IV (All predecessors in Group III or earlier)
	techAcidWeaponry						= 8503,
	techAdvancedArmoringSystems				= 10303,
	techArachnidWeaponry					= 7104,
	techExtendedRangeProjectileLauncherPlymouth	= 7212,
	techHighPoweredExplosives				= 8203,
	techIncreasedCapacitanceCircuitry		= 7403,
	techMagmaPurityControl					= 10301,
	techSpaceProgram						= 5405,
	techSpiderMaintenanceSoftwareRevision	= 8319,

	// Group V (All predecessors in Group IV or earlier)
	techDualTurretWeaponsSystems			= 8201,
	techDirectionalMagneticFields			= 5506,
	techElectromagneticPulsing				= 5508,
	techHeatMining							= 8304,
	techLeggedRobots						= 5116,
	techMagmaRefining						= 8103,
	techMultipleMineProjectileSystem		= 7103,
	techReducedFoamEvaporation				= 8320,
	techReinforcedPantherConstruction		= 8309,
	techRocketPropulsion					= 5599,
	techSevereAtmosphericDisturbances		= 5303,

	// Group VI (All predecessors in Group V or earlier)
	techArachnidDurability					= 8321,
	techArtificialLightning					= 10102,
	techEfficiencyEngineeringEden			= 8301,
	techEfficiencyEngineeringPlymouth		= 8302,
	techExtendedRangeProjectileLauncherEden	= 7211,
	techGrenadeLoadingMechanismPlymouth		= 10306,
	techImprovedLaunchVehicle				= 10101,
	techMeteorWatchObservatory				= 8049,
	techPrecisionTrajectoryProjectionSoftware = 10309,
	techRocketAtmosphericReEntrySystem		= 12201,
	techScorpionPowerSystems				= 7405,
	techSkydock								= 8601,
	techSolarPower							= 10204,
	techStasisSystems						= 10208,

	// Group VII (All predecessors in Group VI or earlier)
	techHabitatRing							= 10205,
	techGrenadeLoadingMechanismEden			= 10305,
	techHeatDissipationSystemsEden			= 12101,
	techHighEnergyRayCompositeProjector		= 8106,
	techIonDriveModule						= 8801,
	techCommandModule						= 10202,
	techMeteorDetection						= 8316,
	techOrbitalPackage						= 10209,
	techSensorPackage						= 10206,

	// Group VIII (All predecessors in Group VII or earlier)
	techFuelingSystems						= 8951,
	techFusionDriveModule					= 8901,

	// Group IX (All predecessors in Group VIII or earlier)
	techPhoenixModule						= 10401,

	// Special Technologies
	techTigerSpeedModification				= 11999,

	// Free Technologies
	techSpider								= 2099,
	techAgridome							= 2101,
	techCommandCenter						= 2103,
	techStructureFactory					= 2104,
	techLightTower							= 2107,
	techCommonOreMine						= 2108,
	techResidence							= 2109,
	techCommonOreSmelter					= 2110,
	techCommonMetalsStorageTanks			= 2111,
	techTokamak								= 2112,
	techTube								= 2114,
	techTradeCenter							= 2115,
	techStandardLab							= 3101,
	techConcreteWalls						= 5106,
	techAdvancedLab							= 5104,
	techRobotCommandCenter					= 3501,
	techVehicleFactory						= 3502,
	techScout								= 3601,
	techLaserTurret							= 3602,
	techMicrowaveTurret						= 3603,
	techCargoTruck							= 3604,
	techConstructionVehicle					= 3605,
	techEarthworksConstructor				= 3606,
	techRoboDozer							= 3608,
	techRoboMiner							= 3609,
	techRoboSurveyor						= 3610,
	techGuardPost							= 3801,
	techGarage								= 5102,
	techRepairvehicle						= 5401,
	techRareOreConstructionSmelter 			= 5501,
	techRareMetalsStorageTanks				= 5502,
	techRocketLauncher						= 5602,
	techObservatory							= 8051,
	techSULV								= 5503,
	techEDWARDSatellite						= 5504,
	techMeteorDetectionConstruction			= 8317,
	techEvacuationModule					= 12599,

	// Unavailable Technologies
	techBasicLaboratory						= 2106,
	techEvacuationTransport					= 3607,
	techMicrobeWall							= 8401,
	techChildrensModule						= 12499,
};

