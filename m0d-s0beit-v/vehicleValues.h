#pragma once

enum SeatPositions
{
	SEAT_DRIVER = -1,
	SEAT_PASSENGER = 0,
	SEAT_BACKDRIVER = 1,
	SEAT_BACKPASSENGER = 2
};

enum WheelTypes
{
	WHEEL_TYPE_STOCK = -1,
	WHEEL_TYPE_SPORT,
	WHEEL_TYPE_MUSCLE,
	WHEEL_TYPE_LOWRIDER,
	WHEEL_TYPE_SUV,
	WHEEL_TYPE_OFFROAD,
	WHEEL_TYPE_TUNER,
	WHEEL_TYPE_BIKEWHEELS,
	WHEEL_TYPE_HIGHEND
};

enum TunerTypes
{
	WHEEL_TUNER_STOCK = -1,
	WHEEL_TUNER_COSMO,
	WHEEL_TUNER_SUPERMESH,
	WHEEL_TUNER_OUTSIDER,
	WHEEL_TUNER_ROLLAS,
	WHEEL_TUNER_DRIFFMEISTER,
	WHEEL_TUNER_SLICER,
	WHEEL_TUNER_ELQUATRO,
	WHEEL_TUNER_DUBBED,
	WHEEL_TUNER_FIVESTAR,
	WHEEL_TUNER_SLIDEWAYS,
	WHEEL_TUNER_APEX,
	WHEEL_TUNER_STANCEDEG,
	WHEEL_TUNER_COUNTERSTEER,
	WHEEL_TUNER_ENDOV1,
	WHEEL_TUNER_ENDOV2DISH,
	WHEEL_TUNER_GUPPEZ,
	WHEEL_TUNER_CHOKADORI,
	WHEEL_TUNER_CHICANE,
	WHEEL_TUNER_SAISOKU,
	WHEEL_TUNER_DISHEDEIGHT,
	WHEEL_TUNER_FUJIWARA,
	WHEEL_TUNER_ZOKUSHA,
	WHEEL_TUNER_BATTLEVLLL,
	WHEEL_TUNER_RALLYMASTER
};

enum HighEndWheels
{
	WHEEL_HIGHEND_STOCK = -1,
	WHEEL_HIGHEND_SHADOW,
	WHEEL_HIGHEND_HYPHER,
	WHEEL_HIGHEND_BLADE,
	WHEEL_HIGHEND_DIAMOND,
	WHEEL_HIGHEND_SUPAGEE,
	WHEEL_HIGHEND_CHROMATICZ,
	WHEEL_HIGHEND_MERCIECHLIP,
	WHEEL_HIGHEND_OBEYRS,
	WHEEL_HIGHEND_GTCHROME,
	WHEEL_HIGHEND_CHEETAHR,
	WHEEL_HIGHEND_SOLAR,
	WHEEL_HIGHEND_SPLITTEN,
	WHEEL_HIGHEND_DASHVIP,
	WHEEL_HIGHEND_LOZSPEEDTEN,
	WHEEL_HIGHEND_CARBONINFERNO,
	WHEEL_HIGHEND_CARBONSHADOW,
	WHEEL_HIGHEND_CARBONZ,
	WHEEL_HIGHEND_CARBONSOLAR,
	WHEEL_HIGHEND_CARBONCHEETAHR,
	WHEEL_HIGHEND_CARBONSRACER
};

enum LowriderWheels
{
	WHEEL_LOWRIDER_STOCK = -1,
	WHEEL_LOWRIDER_FLARE,
	WHEEL_LOWRIDER_WIRED,
	WHEEL_LOWRIDER_TRIPLEGOLDS,
	WHEEL_LOWRIDER_BIGWORM,
	WHEEL_LOWRIDER_SEVENFIVES,
	WHEEL_LOWRIDER_SPLITSIX,
	WHEEL_LOWRIDER_FRESHMESH,
	WHEEL_LOWRIDER_LEADSLED,
	WHEEL_LOWRIDER_TURBINE,
	WHEEL_LOWRIDER_SUPERFIN,
	WHEEL_LOWRIDER_CLASSICROD,
	WHEEL_LOWRIDER_DOLLAR,
	WHEEL_LOWRIDER_DUKES,
	WHEEL_LOWRIDER_LOWFIVE,
	WHEEL_LOWRIDER_GOOCH,
};

enum MuscleWheels
{
	WHEEL_MUSCLE_STOCK = -1,
	WHEEL_MUSCLE_CLASSICFIVE,
	WHEEL_MUSCLE_DUKES,
	WHEEL_MUSCLE_MUSCLEFREAK,
	WHEEL_MUSCLE_KRACKA,
	WHEEL_MUSCLE_AZREA,
	WHEEL_MUSCLE_MECHA,
	WHEEL_MUSCLE_BLACKTOP,
	WHEEL_MUSCLE_DRAGSPL,
	WHEEL_MUSCLE_REVOLVER,
	WHEEL_MUSCLE_CLASSICROD,
	WHEEL_MUSCLE_FAIRLRE,
	WHEEL_MUSCLE_SPOONER,
	WHEEL_MUSCLE_FIVESTAR,
	WHEEL_MUSCLE_OLDSCHOOL,
	WHEEL_MUSCLE_ELJEFE,
	WHEEL_MUSCLE_DODMAN,
	WHEEL_MUSCLE_SIXGUN,
	WHEEL_MUSCLE_MERCENARY
};

enum OffroadWheels
{
	WHEEL_OFFROAD_STOCK = -1,
	WHEEL_OFFROAD_RAIDER,
	WHEEL_OFFROAD_MUDSLINGER,
	WHEEL_OFFROAD_NEVIS,
	WHEEL_OFFROAD_CAIRNGORM,
	WHEEL_OFFROAD_AMAZON,
	WHEEL_OFFROAD_CHALLENGER,
	WHEEL_OFFROAD_DUNEBASHER,
	WHEEL_OFFROAD_FIVESTAR,
	WHEEL_OFFROAD_ROCKCRAWLER,
	WHEEL_OFFROAD_MILSPECSTEELIE
};

enum SportWheels
{
	WHEEL_SPORT_STOCK = -1,
	WHEEL_SPORT_INFERNO,
	WHEEL_SPORT_DEEPFIVE,
	WHEEL_SPORT_LOZSPEED,
	WHEEL_SPORT_DIAMONDCUT,
	WHEEL_SPORT_CHRONO,
	WHEEL_SPORT_FEROCCIRR,
	WHEEL_SPORT_FIFTYNINE,
	WHEEL_SPORT_MERCIE,
	WHEEL_SPORT_SYNTHETICZ,
	WHEEL_SPORT_ORGANICTYPED,
	WHEEL_SPORT_ENDOV1,
	WHEEL_SPORT_DUPER7,
	WHEEL_SPORT_UZER,
	WHEEL_SPORT_GROUNDRIDE,
	WHEEL_SPORT_SRACER,
	WHEEL_SPORT_VENUM,
	WHEEL_SPORT_COSMO,
	WHEEL_SPORT_DASHVIP,
	WHEEL_SPORT_ICEKID,
	WHEEL_SPORT_RUFFWELD,
	WHEEL_SPORT_WANGENMASTER,
	WHEEL_SPORT_SUPERFIVE,
	WHEEL_SPORT_ENDOV2,
	WHEEL_SPORT_SLITSIX
};

enum SUVWheels
{
	WHEEL_SUV_STOCK = -1,
	WHEEL_SUV_VIP,
	WHEEL_SUV_BENEFACTOR,
	WHEEL_SUV_COSMO,
	WHEEL_SUV_BIPPU,
	WHEEL_SUV_ROYALSIX,
	WHEEL_SUV_FAGORME,
	WHEEL_SUV_DELUXE,
	WHEEL_SUV_ICEDOUT,
	WHEEL_SUV_COGNSCENTI,
	WHEEL_SUV_LOZSPEEDTEN,
	WHEEL_SUV_SUPERNOVA,
	WHEEL_SUV_OBEYRS,
	WHEEL_SUV_LOZSPEEDBALLER,
	WHEEL_SUV_EXTRAVAGANZO,
	WHEEL_SUV_SPLITSIX,
	WHEEL_SUV_EMPOWERED,
	WHEEL_SUV_SUNRISE,
	WHEEL_SUV_DASHVIP,
	WHEEL_SUV_CUTTER
};

enum BikeWheels
{
	WHEEL_BIKE_STOCK = -1,
	WHEEL_BIKE_SPEEDWAY,
	WHEEL_BIKE_STREETSPECIAL,
	WHEEL_BIKE_RACER,
	WHEEL_BIKE_TRACKSTAR,
	WHEEL_BIKE_OVERLORD,
	WHEEL_BIKE_TRIDENT,
	WHEEL_BIKE_TRIPLETHREAT,
	WHEEL_BIKE_STILLETO,
	WHEEL_BIKE_WIRES,
	WHEEL_BIKE_BOBBER,
	WHEEL_BIKE_SOLIDUS,
	WHEEL_BIKE_ICESHIELD,
	WHEEL_BIKE_LOOPS
};

enum VehicleModTypes
{
	MOD_SPOILER,
	MOD_FRONTBUMPER,
	MOD_REARBUMPER,
	MOD_SIDESKIRT,
	MOD_EXHAUST,
	MOD_CHASSIS, //Or roll cage
	MOD_GRILLE,
	MOD_HOOD,
	MOD_FENDER,
	MOD_RIGHTFENDER,
	MOD_ROOF,
	MOD_ENGINE,
	MOD_BRAKES,
	MOD_TRANSMISSION,
	MOD_HORNS,
	MOD_SUSPENSION,
	MOD_ARMOR,
	MOD_TURBO = 18,
	MOD_TIRESMOKE = 20,
	MOD_XENONLIGHTS = 22,
	MOD_FRONTWHEELS,
	MOD_BACKWHEELS //Bikes only
};

enum VehicleModHorns
{
	HORN_STOCK = -1,
	HORN_TRUCK,
	HORN_POLICE,
	HORN_CLOWN,
	HORN_MUSICAL1,
	HORN_MUSICAL2,
	HORN_MUSICAL3,
	HORN_MUSICAL4,
	HORN_MUSICAL5,
	HORN_SADTROMBONE,
	HORN_CALSSICAL1,
	HORN_CALSSICAL2,
	HORN_CALSSICAL3,
	HORN_CALSSICAL4,
	HORN_CALSSICAL5,
	HORN_CALSSICAL6,
	HORN_CALSSICAL7,
	HORN_SCALEDO,
	HORN_SCALERE,
	HORN_SCALEMI,
	HORN_SCALEFA,
	HORN_SCALESOL,
	HORN_SCALELA,
	HORN_SCALETI,
	HORN_SCALEDO_HIGH,
	HORN_JAZZ1,
	HORN_JAZZ2,
	HORN_JAZZ3,
	HORN_JAZZLOOP,
	HORN_STARSPANGBAN1,
	HORN_STARSPANGBAN2,
	HORN_STARSPANGBAN3,
	HORN_STARSPANGBAN4
};

enum VehicleAddonLevel
{
	MOD_INDEX_OFF = -1,
	MOD_INDEX_ONE, //To determine mod index, look at the mod menu in LSC, the first item is MOD_INDEX_ONE. Count down to the item you want. Stock counts as OFF.
	MOD_INDEX_TWO,
	MOD_INDEX_THREE,
	MOD_INDEX_FOUR,
	MOD_INDEX_FIVE,
	MOD_INDEX_SIX,
	MOD_INDEX_SEVEN,
	MOD_INDEX_EIGHT,
	MOD_INDEX_NINE
};

enum NeonLightLocations
{
	NEON_LEFT,
	NEON_RIGHT,
	NEON_FRONT,
	NEON_BACK
};

enum VehicleColorsChrome
{
	COLOR_CHROME = 120
};

enum VehicleColorsClassic
{
	COLOR_CLASSIC_BLACK = 0,
	COLOR_CLASSIC_CARBON_BLACK = 147,
	COLOR_CLASSIC_GRAPHITE = 1,
	COLOR_CLASSIC_ANHRACITE_BLACK = 11,
	COLOR_CLASSIC_BLACK_STEEL = 2,
	COLOR_CLASSIC_DARK_STEEL = 3,
	COLOR_CLASSIC_SILVER = 4,
	COLOR_CLASSIC_BLUISH_SILVER = 5,
	COLOR_CLASSIC_ROLLED_STEEL = 6,
	COLOR_CLASSIC_SHADOW_SILVER = 7,
	COLOR_CLASSIC_STONE_SILVER = 8,
	COLOR_CLASSIC_MIDNIGHT_SILVER = 9,
	COLOR_CLASSIC_CAST_IRON_SILVER = 10,
	COLOR_CLASSIC_RED = 27,
	COLOR_CLASSIC_TORINO_RED = 28,
	COLOR_CLASSIC_FORMULA_RED = 29,
	COLOR_CLASSIC_LAVA_RED = 150,
	COLOR_CLASSIC_BLAZE_RED = 30,
	COLOR_CLASSIC_GRACE_RED = 31,
	COLOR_CLASSIC_GARNET_RED = 32,
	COLOR_CLASSIC_SUNSET_RED = 33,
	COLOR_CLASSIC_CABERNET_RED = 34,
	COLOR_CLASSIC_WINE_RED = 143,
	COLOR_CLASSIC_CANDY_RED = 35,
	COLOR_CLASSIC_HOT_PINK = 135,
	COLOR_CLASSIC_PFSITER_PINK = 137,
	COLOR_CLASSIC_SALMON_PINK = 136,
	COLOR_CLASSIC_SUNRISE_ORANGE = 36,
	COLOR_CLASSIC_ORANGE = 38,
	COLOR_CLASSIC_BRIGHT_ORANGE = 138,
	COLOR_CLASSIC_GOLD = 99,
	COLOR_CLASSIC_BRONZE = 90,
	COLOR_CLASSIC_YELLOW = 88,
	COLOR_CLASSIC_RACE_YELLOW = 89,
	COLOR_CLASSIC_DEW_YELLOW = 91,
	COLOR_CLASSIC_DARK_GREEN = 49,
	COLOR_CLASSIC_RACING_GREEN = 50,
	COLOR_CLASSIC_SEA_GREEN = 51,
	COLOR_CLASSIC_OLIVE_GREEN = 52,
	COLOR_CLASSIC_BRIGHT_GREEN = 53,
	COLOR_CLASSIC_GASOLINE_GREEN = 54,
	COLOR_CLASSIC_LIME_GREEN = 92,
	COLOR_CLASSIC_MIDNIGHT_BLUE = 141,
	COLOR_CLASSIC_GALAXY_BLUE = 61,
	COLOR_CLASSIC_DARK_BLUE = 62,
	COLOR_CLASSIC_SAXON_BLUE = 63,
	COLOR_CLASSIC_BLUE = 64,
	COLOR_CLASSIC_MARINER_BLUE = 65,
	COLOR_CLASSIC_HARBOR_BLUE = 66,
	COLOR_CLASSIC_DIAMOND_BLUE = 67,
	COLOR_CLASSIC_SURF_BLUE = 68,
	COLOR_CLASSIC_NAUTICAL_BLUE = 69,
	COLOR_CLASSIC_RACING_BLUE = 73,
	COLOR_CLASSIC_ULTRA_BLUE = 70,
	COLOR_CLASSIC_LIGHT_BLUE = 74,
	COLOR_CLASSIC_CHOCOLATE_BROWN = 96,
	COLOR_CLASSIC_BISON_BROWN = 101,
	COLOR_CLASSIC_CREEEN_BROWN = 95,
	COLOR_CLASSIC_FELTZER_BROWN = 94,
	COLOR_CLASSIC_MAPLE_BROWN = 97,
	COLOR_CLASSIC_BEECHWOOD_BROWN = 103,
	COLOR_CLASSIC_SIENNA_BROWN = 104,
	COLOR_CLASSIC_SADDLE_BROWN = 98,
	COLOR_CLASSIC_MOSS_BROWN = 100,
	COLOR_CLASSIC_WOODBEECH_BROWN = 102,
	COLOR_CLASSIC_STRAW_BROWN = 99,
	COLOR_CLASSIC_SANDY_BROWN = 105,
	COLOR_CLASSIC_BLEACHED_BROWN = 106,
	COLOR_CLASSIC_SCHAFTER_PURPLE = 71,
	COLOR_CLASSIC_SPINNAKER_PURPLE = 72,
	COLOR_CLASSIC_MIDNIGHT_PURPLE = 142,
	COLOR_CLASSIC_BRIGHT_PURPLE = 145,
	COLOR_CLASSIC_CREAM = 107,
	COLOR_CLASSIC_ICE_WHITE = 111,
	COLOR_CLASSIC_FROST_WHITE = 112
};

enum VehicleColorsMatte
{
	COLOR_MATTE_BLACK = 12,
	COLOR_MATTE_GRAY = 13,
	COLOR_MATTE_LIGHT_GRAY = 14,
	COLOR_MATTE_ICE_WHITE = 131,
	COLOR_MATTE_BLUE = 83,
	COLOR_MATTE_DARK_BLUE = 82,
	COLOR_MATTE_MIDNIGHT_BLUE = 84,
	COLOR_MATTE_MIDNIGHT_PURPLE = 149,
	COLOR_MATTE_SCHAFTER_PURPLE = 148,
	COLOR_MATTE_RED = 39,
	COLOR_MATTE_DARK_RED = 40,
	COLOR_MATTE_ORANGE = 41,
	COLOR_MATTE_YELLOW = 42,
	COLOR_MATTE_LIME_GREEN = 55,
	COLOR_MATTE_GREEN = 128,
	COLOR_MATTE_FOREST_GREEN = 151,
	COLOR_MATTE_FOLIAGE_GREEN = 155,
	COLOR_MATTE_OLIVE_DARB = 152,
	COLOR_MATTE_DARK_EARTH = 153,
	COLOR_MATTE_DESERT_TAN = 154
};

enum VehicleColorsMetals
{
	COLOR_METALS_PEARLESCENT_STEEL = 18,
	COLOR_METALS_BRUSHED_STEEL = 117,
	COLOR_METALS_BRUSHED_BLACK_STEEL = 118,
	COLOR_METALS_BRUSHED_ALUMINUM = 119,
	COLOR_METALS_PURE_GOLD = 158,
	COLOR_METALS_BRUSHED_GOLD = 159,
	COLOR_METALS_PEARLESCENT_GOLD = 160
};

enum PlateTextIndexs
{
	PLATE_BLUEONWHITE1,
	PLATE_YELLOWONBLACK,
	PLATE_YELLOWONBLUE,
	PLATE_BLUEONWHITE2,
	PLATE_BLUEONWHITE3,
	PLATE_YANKTON
};

enum WindowTints //m8 do you even int tint?
{
	WINDOWTINT_NONE,
	WINDOWTINT_BLACK,
	WINDOWTINT_DARKSMOKE,
	WINDOWTINT_LIGHTSMOKE,
	WINDOWTINT_STOCK,
	WINDOWTINT_LIMO,
	WINDOWTINT_GREEN
};

#define NEON_COLOR_WHITE 222, 222, 255
#define NEON_COLOR_BLUE 2, 21, 255
#define NEON_COLOR_ELECTRICBLUE 3, 83, 255
#define NEON_COLOR_MINTGREEN 0, 255, 140
#define NEON_COLOR_LIMEGREEN 94, 255, 1
#define NEON_COLOR_YELLOW 255, 255, 0
#define NEON_COLOR_GOLDENSHOWER 255, 150, 5
#define NEON_COLOR_ORANGE 255, 62, 0
#define NEON_COLOR_RED 255, 1, 1
#define NEON_COLOR_PONYPINK 255, 50, 100 //Fag
#define NEON_COLOR_HOTPINK 255, 5, 190
#define NEON_COLOR_PURPLE 35, 1, 255
#define NEON_COLOR_BACKLIGHT 15, 3, 255

#define TIRESMOKE_COLOR_WHITE 255, 255, 255
#define TIRESMOKE_COLOR_BLACK 20, 20, 20
#define TIRESMOKE_COLOR_BLUE 0, 174, 239
#define TIRESMOKE_COLOR_YELLOW 252, 238, 0
#define TIRESMOKE_COLOR_PURPLE 100, 79, 142
#define TIRESMOKE_COLOR_ORANGE 255, 127, 0
#define TIRESMOKE_COLOR_GREEN 114, 204, 114
#define TIRESMOKE_COLOR_RED 226, 6, 6
#define TIRESMOKE_COLOR_PINK 203, 54, 148
#define TIRESMOKE_COLOR_BROWN 180, 130, 97
#define TIRESMOKE_COLOR_PATRIOT 0, 0, 0

inline bool GetVehicleInfoForClanLogo(Hash vehicleModel, vector3_t& x, vector3_t& y, vector3_t& z, float& scale)
{
	switch (vehicleModel)
	{
	case VEHICLE_DOMINATOR:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FELTZER2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ADDER:
		x = { 0.0f, 1.54f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_AKUMA:
		x = { 0.0f, 0.06f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_ASEA:
		x = { 0.0f, 1.5f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ASTEROPE:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BAGGER:
		x = { 0.0f, 0.053f, 1.23f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BALLER:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER2:
		x = { 0.0f, 1.55f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BANSHEE:
		x = { 0.0f, 0.94f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_BATI:
		x = { 0.0f, 0.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BATI2:
		x = { 0.0f, 0.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BFINJECTION:
		x = { -1.0f, 0.08f, 0.19f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BISON:
		x = { 0.0f, 1.99f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BJXL:
		x = { 0.0f, 1.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_BLISTA:
		x = { 0.0f, 1.49f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.29f;
		return true;
	case VEHICLE_BOBCATXL:
		x = { 0.0f, 1.68f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.65f;
		return true;
	case VEHICLE_BODHI2:
		x = { 0.0f, 1.95f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BUCCANEER:
		x = { 0.0f, 2.01f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_BUFFALO:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BUFFALO2:
		x = { 0.0f, 2.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_BULLET:
		x = { -1.57f, 0.07f, 0.16f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_CARBONRS:
		x = { 0.0f, 0.09f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_CARBONIZZARE:
		x = { 0.0f, 1.45f, 1.0f };
		y = { 0.0f, 0.11f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_CAVALCADE:
		x = { 0.0f, 1.51f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.55f;
		return true;
	case VEHICLE_CAVALCADE2:
		x = { 0.0f, 1.59f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_CHEETAH:
		x = { -1.61f, 0.26f, 0.17f };
		y = { 0.9f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_COGCABRIO:
		x = { 0.0f, 1.42f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COMET2:
		x = { 0.0f, 1.35f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE:
		x = { 0.0f, 0.96f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.22f;
		return true;
	case VEHICLE_DAEMON:
		x = { 0.0f, 0.06f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_DILETTANTE:
		x = { 0.0f, 1.59f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DLOADER:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DOUBLE:
		x = { 0.0f, 0.08f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_DUBSTA:
		x = { -1.71f, 0.31f, 0.27f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.75f;
		return true;
	case VEHICLE_ELEGY2:
		x = { 0.0f, 1.14f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_EMPEROR:
		x = { 0.0f, 1.31f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_EMPEROR2:
		x = { 0.0f, 1.31f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ENTITYXF:
		x = { 1.52f, 0.41f, 0.15f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_EXEMPLAR:
		x = { 0.0f, 1.32f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_F620:
		x = { 0.0f, 1.28f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_FAGGIO2:
		x = { -1.0f, 0.48f, 0.11f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_FELON:
		x = { 0.0f, 1.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_FELON2:
		x = { 0.0f, 1.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_FQ2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FUGITIVE:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FUSILADE:
		x = { 0.0f, 0.98f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_FUTO:
		x = { 0.0f, 1.28f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_GAUNTLET:
		x = { 0.0f, 1.735f, 1.05f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_GRANGER:
		x = { 0.0f, 2.07f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_GRESLEY:
		x = { 0.0f, 1.75f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HABANERO:
		x = { 0.0f, 1.69f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HEXER:
		x = { 0.0f, -0.46f, 1.0f };
		y = { 0.0f, 1.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.14f;
		return true;
	case VEHICLE_HOTKNIFE:
		x = { 1.43f, -0.14f, 0.18f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_INFERNUS:
		x = { -1.0f, 0.33f, 0.08f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.06f };
		scale = 0.25f;
		return true;
	case VEHICLE_INGOT:
		x = { 0.0f, 1.58f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_INTRUDER:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ISSI2:
		x = { 0.0f, 1.21f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_JACKAL:
		x = { 0.0f, 1.36f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_JB700:
		x = { 0.0f, 1.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_KHAMELION:
		x = { 0.0f, 1.46f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.475f;
		return true;
	case VEHICLE_LANDSTALKER:
		x = { 0.0f, 1.83f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MANANA:
		x = { 0.0f, 0.86f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_MESA:
		x = { 0.0f, 1.47f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MESA3:
		x = { 0.0f, 1.47f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MINIVAN:
		x = { 0.0f, 1.95f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MONROE:
		x = { 0.0f, 1.23f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.43f;
		return true;
	case VEHICLE_NEMESIS:
		x = { 0.0f, 0.14f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.1f;
		return true;
	case VEHICLE_NINEF:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_NINEF2:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE2:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PATRIOT:
		x = { 0.0f, 1.75f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PCJ:
		x = { 0.0f, 0.02f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_PENUMBRA:
		x = { 0.0f, 1.46f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PEYOTE:
		x = { -1.0f, -0.36f, 0.2125f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PHOENIX:
		x = { 0.0f, 1.833f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.44f;
		return true;
	case VEHICLE_PICADOR:
		x = { 0.0f, 1.43f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.515f;
		return true;
	case VEHICLE_PRAIRIE:
		x = { 0.0f, 1.41f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.31f;
		return true;
	case VEHICLE_PREMIER:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PRIMO:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RADI:
		x = { 0.0f, 1.74f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RANCHERXL:
		x = { 0.0f, 1.54f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT:
		x = { 0.0f, 1.263f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT2:
		x = { 0.0f, 1.263f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RATLOADER:
		x = { 1.78f, 0.52f, 0.52f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_REBEL:
		x = { -1.22f, 0.6f, 0.44f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_REBEL2:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_REGINA:
		x = { 0.0f, 1.473f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ROCOTO:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ROMERO:
		x = { 0.0f, 1.83f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RUFFIAN:
		x = { 0.0f, 0.02f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.19f;
		return true;
	case VEHICLE_RUINER:
		x = { 0.0f, 1.34f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SABREGT:
		x = { -1.0f, 0.0f, 0.14f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.015f };
		scale = 0.35f;
		return true;
	case VEHICLE_SADLER:
		x = { 0.0f, 2.26f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING:
		x = { 0.0f, 2.496f, 1.55f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING2:
		x = { 0.0f, 2.286f, 1.55f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SCHAFTER2:
		x = { 0.0f, 1.56f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.28f;
		return true;
	case VEHICLE_SCHWARZER:
		x = { 0.0f, 1.43f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.28f;
		return true;
	case VEHICLE_SEMINOLE:
		x = { 0.0f, 1.45f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL2:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SERRANO:
		x = { 0.0f, 1.68f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.49f;
		return true;
	case VEHICLE_STANIER:
		x = { 0.0f, 1.55f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_STINGER:
		x = { 0.0f, 1.3f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_STINGERGT:
		x = { -1.0f, -0.17f, 0.12f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_STRATUM:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SULTAN:
		x = { 0.0f, 1.77f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_SUPERD:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SURANO:
		x = { 0.0f, 1.38f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SURFER:
		x = { 0.0f, 2.48f, 0.26f };
		y = { 0.0f, -1.0f, 0.212f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.32f;
		return true;
	case VEHICLE_SURFER2:
		x = { 0.0f, 2.48f, 0.26f };
		y = { 0.0f, -1.0f, 0.212f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.32f;
		return true;
	case VEHICLE_SURGE:
		x = { 0.0f, 1.69f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_TAILGATER:
		x = { 0.0f, 1.783f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO:
		x = { -1.23f, 0.11f, 0.21f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO2:
		x = { 0.0f, 1.44f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_TORNADO3:
		x = { 0.0f, 1.44f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_VACCA:
		x = { 0.0f, 1.76f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_VADER:
		x = { 0.0f, 0.08f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_VIGERO:
		x = { -1.0f, 0.11f, -0.15f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_VOLTIC:
		x = { 0.0f, 1.763f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.29f;
		return true;
	case VEHICLE_VOODOO2:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_WASHINGTON:
		x = { 0.0f, 1.61f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_YOUGA:
		x = { 0.0f, 2.02f, 1.0f };
		y = { 0.0f, -0.108f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_ZION:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_ZION2:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_ZTYPE:
		x = { 0.96f, 0.69f, 0.35f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_KALAHARI:
		x = { -1.0f, 0.18f, 0.1f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PARADISE:
		x = { 0.0f, 2.23f, 1.0f };
		y = { 0.0f, 0.22f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ALPHA:
		x = { -1.0f, 0.18f, -0.05f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HUNTLEY:
		x = { 0.0f, 1.52f, 0.99f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_ZENTORNO:
		x = { -1.24f, 0.42f, -0.14f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.035f };
		scale = 0.3f;
		return true;
	case VEHICLE_JESTER:
		x = { -1.0f, 0.17f, 0.22f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.05f };
		scale = 0.33f;
		return true;
	case VEHICLE_MASSACRO:
		x = { 0.0f, 1.37f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_TURISMOR:
		x = { -1.0f, 0.3f, 0.27f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_THRUST:
		x = { -1.0f, 0.405f, 0.4625f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.1625f;
		return true;
	case VEHICLE_BTYPE:
		x = { 0.0f, 1.143f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.7125f;
		return true;
	case VEHICLE_RHAPSODY:
		x = { -1.0f, 0.47f, -0.25f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2625f;
		return true;
	case VEHICLE_GLENDALE:
		x = { 0.0f, 1.683f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.775f;
		return true;
	case VEHICLE_WARRENER:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.775f;
		return true;
	case VEHICLE_BLADE:
		x = { -1.0f, 0.445f, 0.2075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.325f;
		return true;
	case VEHICLE_PANTO:
		x = { -1.0f, 0.0f, 0.335f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA3:
		x = { -1.0f, 0.34f, 0.2975f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PIGALLE:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE2:
		x = { -1.0f, 0.1775f, 0.195f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_INNOVATION:
		x = { 0.0f, 0.15f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_HAKUCHOU:
		x = { 0.0f, 0.27f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.16f;
		return true;
	case VEHICLE_FUROREGT:
		x = { -1.0f, 0.0f, 0.2075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_RATLOADER2:
		x = { 1.78f, 0.52f, 0.52f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_SLAMVAN:
		x = { -1.0f, 0.275f, 0.195f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUKES2:
		x = { -1.0f, 0.0f, 0.0f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.375f;
		return true;
	case VEHICLE_DUKES:
		x = { -1.0f, 0.0f, 0.0375f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3875f;
		return true;
	case VEHICLE_STALION:
		x = { -1.0f, 0.0f, 0.0925f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4375f;
		return true;
	case VEHICLE_BLISTA2:
		x = { -1.0f, 0.5325f, 0.245f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2875f;
		return true;
	case VEHICLE_CASCO:
		x = { 0.0f, 0.94f, 1.03f };
		y = { 0.0f, 0.03f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_ENDURO:
		x = { 0.0f, -0.17f, 1.0f };
		y = { 0.0f, 0.34f, -0.786f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_GBURRITO2:
		x = { 0.0f, 2.32f, 0.94f };
		y = { 0.0f, 0.182f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_GUARDIAN:
		x = { -1.94f, 1.07f, 0.38f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_KURUMA:
	case VEHICLE_KURUMA2:
		x = { -1.0f, 0.2475f, 0.175f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.435f;
		return true;
	case VEHICLE_LECTRO:
		x = { 0.0f, 0.3f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.09f;
		return true;
	case VEHICLE_FELTZER3:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_OSIRIS:
		x = { -1.0f, 0.27f, -0.033f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_VIRGO:
		x = { 1.05f, 0.0f, 0.075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_WINDSOR:
		x = { -1.2f, 0.39f, 0.12f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.55f;
		return true;
	default:
		return false;
	}
}