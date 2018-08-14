//
//  RogueMain.h
//  Brogue
//
//  Created by Brian Walker on 12/26/08.
//  Copyright 2012. All rights reserved.
//
//  This file is part of Brogue.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as
//  published by the Free Software Foundation, either version 3 of the
//  License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlatformDefines.h"
#include "Flag.h"
#include "Types.h"
#include "Color.h"
#include "RandomRange.h"
#include "Dungeon.h"
#include "Monsters.h"

// unicode: comment this line to revert to ASCII

#define USE_UNICODE

// version string -- no more than 16 bytes:
#define BROGUE_VERSION_STRING "1.7.4"

// debug macros -- define DEBUGGING as 1 to enable wizard mode.

#define DEBUGGING 0

#define DEBUG if (DEBUGGING)
#define MONSTERS_ENABLED (!DEBUGGING || 1)  // Quest room monsters can be generated regardless.
#define ITEMS_ENABLED (!DEBUGGING || 1)

#define D_BULLET_TIME (DEBUGGING && 0)
#define D_WORMHOLING (DEBUGGING && 1)
#define D_IMMORTAL (DEBUGGING && 1)

#define D_SAFETY_VISION (DEBUGGING && 0)
#define D_SCENT_VISION (DEBUGGING && 0)
#define D_DISABLE_BACKGROUND_COLORS (DEBUGGING && 0)

#define D_INSPECT_LEVELGEN (DEBUGGING && 0)
#define D_INSPECT_MACHINES (DEBUGGING && 0)

#define D_MESSAGE_ITEM_GENERATION (DEBUGGING && 0)
#define D_MESSAGE_MACHINE_GENERATION (DEBUGGING && 0)

// set to false to allow multiple loads from the same saved file:
#define DELETE_SAVE_FILE_AFTER_LOADING true

// set to false to disable references to keystrokes (e.g. for a tablet port)
#define KEYBOARD_LABELS true

//#define BROGUE_ASSERTS		// introduces several assert()s -- useful to find certain array overruns and other bugs
//#define AUDIT_RNG             // VERY slow, but sometimes necessary to debug out-of-sync recording errors
//#define GENERATE_FONT_FILES	// Displays font in grid upon startup, which can be screen-captured into font files for
// PC.

#ifdef BROGUE_ASSERTS
#include <assert.h>
#define brogueAssert(x) assert(x)
#else
#define brogueAssert(x)
#endif


#define PI 3.14159265
#define FLOAT_FUDGE 0.00001

// recording and save filenames
#define LAST_GAME_PATH "LastGame.broguesave"
#define LAST_GAME_NAME "LastGame"
#define LAST_RECORDING_NAME "LastRecording"
#define RECORDING_SUFFIX ".broguerec"
#define GAME_SUFFIX ".broguesave"
#define ANNOTATION_SUFFIX ".txt"
#define RNG_LOG "RNGLog.txt"

#define BROGUE_FILENAME_MAX (min(1024 * 4, FILENAME_MAX))



#define MESSAGE_LINES 3
#define MESSAGE_ARCHIVE_LINES ROWS

// Size of the entire terminal window. These need to be hard-coded here and in Viewport.h
#define COLS 100
#define ROWS (31 + MESSAGE_LINES)

// Size of the portion of the terminal window devoted to displaying the dungeon:
#define DCOLS                                                                                                          \
  (COLS - STAT_BAR_WIDTH - 1)  // n columns on the left for the sidebar;
                               // one column to separate the sidebar from the map.
#define DROWS                                                                                                          \
  (ROWS - MESSAGE_LINES - 2)  // n lines at the top for messages;
                              // one line at the bottom for flavor text;
                              // another line at the bottom for the menu bar.

#define STAT_BAR_WIDTH 20  // number of characters in the stats bar to the left of the map

#define LOS_SLOPE_GRANULARITY                                                                                          \
  32768  // how finely we divide up the squares when calculating slope;
         // higher numbers mean fewer artifacts but more memory and processing
#define INTERFACE_OPACITY 95

#define LIGHT_SMOOTHING_THRESHOLD 150  // light components higher than this magnitude will be toned down a little

#define MAX_BOLT_LENGTH DCOLS * 10

#define VISIBILITY_THRESHOLD 50  // how bright cumulative light has to be before the cell is marked visible

#define AMULET_LEVEL 26   // how deep before the amulet appears
#define DEEPEST_LEVEL 40  // how deep the universe goes

#define MACHINES_FACTOR 1.0  // use this to adjust machine frequency

#define MACHINES_BUFFER_LENGTH 200

#define DEFENSE_FACTOR                                                                                                 \
  0.987  // Each point of armor multiplies enemy attackers' accuracy by this value.
         // (displayed armor value is 10% of the real value)
#define WEAPON_ENCHANT_DAMAGE_FACTOR                                                                                   \
  1.065  // Each marginal point of weapon enchantment
         // multiplies damage by this factor.
#define WEAPON_ENCHANT_ACCURACY_FACTOR                                                                                 \
  1.065  // Each marginal point of weapon enchantment
         // multiplies accuracy by this factor.

#define WEAPON_KILLS_TO_AUTO_ID 20
#define ARMOR_DELAY_TO_AUTO_ID 1000
#define RING_DELAY_TO_AUTO_ID 1500

#define FALL_DAMAGE_MIN 8
#define FALL_DAMAGE_MAX 10

#define INPUT_RECORD_BUFFER 1000  // how many bytes of input data to keep in memory before saving it to disk
#define DEFAULT_PLAYBACK_DELAY 50

#define HIGH_SCORES_COUNT 30

// color escapes
#define COLOR_ESCAPE 25
#define COLOR_VALUE_INTERCEPT 25

// display characters:

#ifdef USE_UNICODE

#define FLOOR_CHAR 0x00b7
#define LIQUID_CHAR '~'
#define CHASM_CHAR 0x2237
#define TRAP_CHAR 0x25c7
#define FIRE_CHAR 0x22CF
#define GRASS_CHAR '"'
#define BRIDGE_CHAR '='
#define DESCEND_CHAR '>'
#define ASCEND_CHAR '<'
#define WALL_CHAR '#'
#define DOOR_CHAR '+'
#define OPEN_DOOR_CHAR '\''
#define ASH_CHAR '\''
#define BONES_CHAR ','
#define MUD_CHAR ','
#define WEB_CHAR ':'
//#define FOLIAGE_CHAR	0x03A8 // lower-case psi
#define FOLIAGE_CHAR 0x2648  // Aries symbol
#define VINE_CHAR ':'
#define ALTAR_CHAR '|'
#define LEVER_CHAR '/'
#define LEVER_PULLED_CHAR '\\'
#define STATUE_CHAR 0x00df
#define VENT_CHAR '='
#define DEWAR_CHAR '&'

#define TRAMPLED_FOLIAGE_CHAR '"'  // 0x2034 // 0x2037

#define PLAYER_CHAR '@'

#define AMULET_CHAR 0x2640
#define FOOD_CHAR ';'
#define SCROLL_CHAR 0x266A  //'?'		// 0x039E
//#define RING_CHAR		0x26AA //0xffee
#define RING_CHAR 0xffee
#define CHARM_CHAR 0x03DE
#define POTION_CHAR '!'
#define ARMOR_CHAR '['
#define WEAPON_CHAR 0x2191
#define STAFF_CHAR '\\'
#define WAND_CHAR '~'
#define GOLD_CHAR '*'
#define GEM_CHAR 0x25cf
#define TOTEM_CHAR 0x26b2
#define TURRET_CHAR 0x25cf
#define UNICORN_CHAR 0x00da
#define KEY_CHAR '-'
#define ELECTRIC_CRYSTAL_CHAR 164

#define UP_ARROW_CHAR 0x2191
#define DOWN_ARROW_CHAR 0x2193
#define LEFT_ARROW_CHAR 0x2190
#define RIGHT_ARROW_CHAR 0x2192
#define UP_TRIANGLE_CHAR 0x2206
#define DOWN_TRIANGLE_CHAR 0x2207
#define OMEGA_CHAR 0x03A9
#define THETA_CHAR 0x03B8
#define LAMDA_CHAR 0x03BB
#define KOPPA_CHAR 0x03DF  // 0x03DE
#define LOZENGE_CHAR 0x29EB
#define CROSS_PRODUCT_CHAR 0x2A2F

#define CHAIN_TOP_LEFT '\\'
#define CHAIN_BOTTOM_RIGHT '\\'
#define CHAIN_TOP_RIGHT '/'
#define CHAIN_BOTTOM_LEFT '/'
#define CHAIN_TOP '|'
#define CHAIN_BOTTOM '|'
#define CHAIN_LEFT '-'
#define CHAIN_RIGHT '-'

#define BAD_MAGIC_CHAR 0x29F2
#define GOOD_MAGIC_CHAR 0x29F3

#else

#define FLOOR_CHAR '.'
#define LIQUID_CHAR '~'
#define CHASM_CHAR ':'
#define TRAP_CHAR '%'
#define FIRE_CHAR '^'
#define GRASS_CHAR '"'
#define BRIDGE_CHAR '='
#define DESCEND_CHAR '>'
#define ASCEND_CHAR '<'
#define WALL_CHAR '#'
#define DOOR_CHAR '+'
#define OPEN_DOOR_CHAR '\''
#define ASH_CHAR '\''
#define BONES_CHAR ','
#define MUD_CHAR ','
#define WEB_CHAR ':'
#define FOLIAGE_CHAR '&'
#define VINE_CHAR ':'
#define ALTAR_CHAR '|'
#define LEVER_CHAR '/'
#define LEVER_PULLED_CHAR '\\'
#define STATUE_CHAR '&'
#define VENT_CHAR '='
#define DEWAR_CHAR '&'

#define TRAMPLED_FOLIAGE_CHAR '"'

#define PLAYER_CHAR '@'

#define AMULET_CHAR ','
#define FOOD_CHAR ';'
#define SCROLL_CHAR '?'
#define RING_CHAR '='
#define CHARM_CHAR '+'
#define POTION_CHAR '!'
#define ARMOR_CHAR '['
#define WEAPON_CHAR '('
#define STAFF_CHAR '\\'
#define WAND_CHAR '~'
#define GOLD_CHAR '*'
#define GEM_CHAR '+'
#define TOTEM_CHAR '0'
#define TURRET_CHAR '*'
#define UNICORN_CHAR 'U'
#define KEY_CHAR '-'
#define ELECTRIC_CRYSTAL_CHAR '$'

#define UP_ARROW_CHAR '^'
#define DOWN_ARROW_CHAR 'v'
#define LEFT_ARROW_CHAR '<'
#define RIGHT_ARROW_CHAR '>'
#define UP_TRIANGLE_CHAR '^'
#define DOWN_TRIANGLE_CHAR 'v'
#define OMEGA_CHAR '^'
#define THETA_CHAR '0'
#define LAMDA_CHAR '\\'
#define KOPPA_CHAR 'k'
#define LOZENGE_CHAR '+'
#define CROSS_PRODUCT_CHAR 'x'

#define CHAIN_TOP_LEFT '\\'
#define CHAIN_BOTTOM_RIGHT '\\'
#define CHAIN_TOP_RIGHT '/'
#define CHAIN_BOTTOM_LEFT '/'
#define CHAIN_TOP '|'
#define CHAIN_BOTTOM '|'
#define CHAIN_LEFT '-'
#define CHAIN_RIGHT '-'

#define BAD_MAGIC_CHAR '+'
#define GOOD_MAGIC_CHAR '$'

#endif

enum EventTypes
{
  KEYSTROKE,
  MOUSE_UP,
  MOUSE_DOWN,
  RIGHT_MOUSE_DOWN,
  RIGHT_MOUSE_UP,
  MOUSE_ENTERED_CELL,
  RNG_CHECK,
  SAVED_GAME_LOADED,
  END_OF_RECORDING,
  EVENT_ERROR,
  NUMBER_OF_EVENT_TYPES,  // unused
};

struct RogueEvent
{
  enum EventTypes eventType;
  signed long param1;
  signed long param2;
  bool controlKey;
  bool shiftKey;
};

struct RogueHighScoresEntry
{
  char date[128];
  char description[DCOLS];
  long score;
};

typedef struct fileEntry
{
  char* path;
  char date[100];
} fileEntry;

enum RNGs
{
  RNG_SUBSTANTIVE,
  RNG_COSMETIC,
  NUMBER_OF_RNGS,
};

enum DisplayDetailValues
{
  DV_UNLIT = 0,
  DV_LIT,
  DV_DARK,
};

enum TextEntryTypes
{
  TEXT_INPUT_NORMAL = 0,
  TEXT_INPUT_FILENAME,
  TEXT_INPUT_NUMBERS,
  TEXT_INPUT_TYPES,
};

#define NUMBER_DYNAMIC_COLORS 6

enum TileType
{
  NOTHING = 0,
  GRANITE,
  FLOOR,
  FLOOR_FLOODABLE,
  CARPET,
  MARBLE_FLOOR,
  WALL,
  DOOR,
  OPEN_DOOR,
  SECRET_DOOR,
  LOCKED_DOOR,
  OPEN_IRON_DOOR_INERT,
  DOWN_STAIRS,
  UP_STAIRS,
  DUNGEON_EXIT,
  DUNGEON_PORTAL,
  TORCH_WALL,  // wall lit with a torch
  CRYSTAL_WALL,
  PORTCULLIS_CLOSED,
  PORTCULLIS_DORMANT,
  WOODEN_BARRICADE,
  PILOT_LIGHT_DORMANT,
  PILOT_LIGHT,
  HAUNTED_TORCH_DORMANT,
  HAUNTED_TORCH_TRANSITIONING,
  HAUNTED_TORCH,
  WALL_LEVER_HIDDEN,
  WALL_LEVER,
  WALL_LEVER_PULLED,
  WALL_LEVER_HIDDEN_DORMANT,
  STATUE_INERT,
  STATUE_DORMANT,
  STATUE_CRACKING,
  STATUE_INSTACRACK,
  PORTAL,
  TURRET_DORMANT,
  WALL_MONSTER_DORMANT,
  DARK_FLOOR_DORMANT,
  DARK_FLOOR_DARKENING,
  DARK_FLOOR,
  MACHINE_TRIGGER_FLOOR,
  ALTAR_INERT,
  ALTAR_KEYHOLE,
  ALTAR_CAGE_OPEN,
  ALTAR_CAGE_CLOSED,
  ALTAR_SWITCH,
  ALTAR_SWITCH_RETRACTING,
  ALTAR_CAGE_RETRACTABLE,
  PEDESTAL,
  MONSTER_CAGE_OPEN,
  MONSTER_CAGE_CLOSED,
  COFFIN_CLOSED,
  COFFIN_OPEN,

  GAS_TRAP_POISON_HIDDEN,
  GAS_TRAP_POISON,
  TRAP_DOOR_HIDDEN,
  TRAP_DOOR,
  GAS_TRAP_PARALYSIS_HIDDEN,
  GAS_TRAP_PARALYSIS,
  MACHINE_PARALYSIS_VENT_HIDDEN,
  MACHINE_PARALYSIS_VENT,
  GAS_TRAP_CONFUSION_HIDDEN,
  GAS_TRAP_CONFUSION,
  FLAMETHROWER_HIDDEN,
  FLAMETHROWER,
  FLOOD_TRAP_HIDDEN,
  FLOOD_TRAP,
  NET_TRAP_HIDDEN,
  NET_TRAP,
  ALARM_TRAP_HIDDEN,
  ALARM_TRAP,
  MACHINE_POISON_GAS_VENT_HIDDEN,
  MACHINE_POISON_GAS_VENT_DORMANT,
  MACHINE_POISON_GAS_VENT,
  MACHINE_METHANE_VENT_HIDDEN,
  MACHINE_METHANE_VENT_DORMANT,
  MACHINE_METHANE_VENT,
  STEAM_VENT,
  MACHINE_PRESSURE_PLATE,
  MACHINE_PRESSURE_PLATE_USED,
  MACHINE_GLYPH,
  MACHINE_GLYPH_INACTIVE,
  DEWAR_CAUSTIC_GAS,
  DEWAR_CONFUSION_GAS,
  DEWAR_PARALYSIS_GAS,
  DEWAR_METHANE_GAS,

  DEEP_WATER,
  SHALLOW_WATER,
  MUD,
  CHASM,
  CHASM_EDGE,
  MACHINE_COLLAPSE_EDGE_DORMANT,
  MACHINE_COLLAPSE_EDGE_SPREADING,
  LAVA,
  LAVA_RETRACTABLE,
  LAVA_RETRACTING,
  SUNLIGHT_POOL,
  DARKNESS_PATCH,
  ACTIVE_BRIMSTONE,
  INERT_BRIMSTONE,
  OBSIDIAN,
  BRIDGE,
  BRIDGE_FALLING,
  BRIDGE_EDGE,
  STONE_BRIDGE,
  MACHINE_FLOOD_WATER_DORMANT,
  MACHINE_FLOOD_WATER_SPREADING,
  MACHINE_MUD_DORMANT,

  HOLE,
  HOLE_GLOW,
  HOLE_EDGE,
  FLOOD_WATER_DEEP,
  FLOOD_WATER_SHALLOW,
  GRASS,
  DEAD_GRASS,
  GRAY_FUNGUS,
  LUMINESCENT_FUNGUS,
  LICHEN,
  HAY,
  RED_BLOOD,
  GREEN_BLOOD,
  PURPLE_BLOOD,
  ACID_SPLATTER,
  VOMIT,
  URINE,
  UNICORN_POOP,
  WORM_BLOOD,
  ASH,
  BURNED_CARPET,
  PUDDLE,
  BONES,
  RUBBLE,
  JUNK,
  BROKEN_GLASS,
  ECTOPLASM,
  EMBERS,
  SPIDERWEB,
  NETTING,
  FOLIAGE,
  DEAD_FOLIAGE,
  TRAMPLED_FOLIAGE,
  FUNGUS_FOREST,
  TRAMPLED_FUNGUS_FOREST,
  FORCEFIELD,
  FORCEFIELD_MELT,
  SACRED_GLYPH,
  MANACLE_TL,
  MANACLE_BR,
  MANACLE_TR,
  MANACLE_BL,
  MANACLE_T,
  MANACLE_B,
  MANACLE_L,
  MANACLE_R,
  PORTAL_LIGHT,
  GUARDIAN_GLOW,

  PLAIN_FIRE,
  BRIMSTONE_FIRE,
  FLAMEDANCER_FIRE,
  GAS_FIRE,
  GAS_EXPLOSION,
  DART_EXPLOSION,
  ITEM_FIRE,
  CREATURE_FIRE,

  POISON_GAS,
  CONFUSION_GAS,
  ROT_GAS,
  STENCH_SMOKE_GAS,
  PARALYSIS_GAS,
  METHANE_GAS,
  STEAM,
  DARKNESS_CLOUD,
  HEALING_CLOUD,

  BLOODFLOWER_STALK,
  BLOODFLOWER_POD,

  HAVEN_BEDROLL,

  DEEP_WATER_ALGAE_WELL,
  DEEP_WATER_ALGAE_1,
  DEEP_WATER_ALGAE_2,

  ANCIENT_SPIRIT_VINES,
  ANCIENT_SPIRIT_GRASS,

  AMULET_SWITCH,

  COMMUTATION_ALTAR,
  COMMUTATION_ALTAR_INERT,
  PIPE_GLOWING,
  PIPE_INERT,

  RESURRECTION_ALTAR,
  RESURRECTION_ALTAR_INERT,
  MACHINE_TRIGGER_FLOOR_REPEATING,

  STATUE_INERT_DOORWAY,
  STATUE_DORMANT_DOORWAY,

  CHASM_WITH_HIDDEN_BRIDGE,
  CHASM_WITH_HIDDEN_BRIDGE_ACTIVE,
  MACHINE_CHASM_EDGE,

  RAT_TRAP_WALL_DORMANT,
  RAT_TRAP_WALL_CRACKING,

  ELECTRIC_CRYSTAL_OFF,
  ELECTRIC_CRYSTAL_ON,
  TURRET_LEVER,

  WORM_TUNNEL_MARKER_DORMANT,
  WORM_TUNNEL_MARKER_ACTIVE,
  WORM_TUNNEL_OUTER_WALL,

  BRAZIER,

  MUD_FLOOR,
  MUD_WALL,
  MUD_DOORWAY,

  NUMBER_TILETYPES,
};

enum LightType
{
  NO_LIGHT,
  MINERS_LIGHT,
  BURNING_CREATURE_LIGHT,
  WISP_LIGHT,
  SALAMANDER_LIGHT,
  IMP_LIGHT,
  PIXIE_LIGHT,
  LICH_LIGHT,
  FLAMEDANCER_LIGHT,
  SENTINEL_LIGHT,
  UNICORN_LIGHT,
  IFRIT_LIGHT,
  PHOENIX_LIGHT,
  PHOENIX_EGG_LIGHT,
  YENDOR_LIGHT,
  SPECTRAL_BLADE_LIGHT,
  SPECTRAL_IMAGE_LIGHT,
  SPARK_TURRET_LIGHT,
  EXPLOSIVE_BLOAT_LIGHT,
  BOLT_LIGHT_SOURCE,
  TELEPATHY_LIGHT,

  SCROLL_PROTECTION_LIGHT,
  SCROLL_ENCHANTMENT_LIGHT,
  POTION_STRENGTH_LIGHT,
  EMPOWERMENT_LIGHT,
  GENERIC_FLASH_LIGHT,
  FALLEN_TORCH_FLASH_LIGHT,
  SUMMONING_FLASH_LIGHT,
  EXPLOSION_FLARE_LIGHT,
  QUIETUS_FLARE_LIGHT,
  SLAYING_FLARE_LIGHT,
  CHARGE_FLASH_LIGHT,

  TORCH_LIGHT,
  LAVA_LIGHT,
  SUN_LIGHT,
  DARKNESS_PATCH_LIGHT,
  FUNGUS_LIGHT,
  FUNGUS_FOREST_LIGHT,
  LUMINESCENT_ALGAE_BLUE_LIGHT,
  LUMINESCENT_ALGAE_GREEN_LIGHT,
  ECTOPLASM_LIGHT,
  UNICORN_POOP_LIGHT,
  EMBER_LIGHT,
  FIRE_LIGHT,
  BRIMSTONE_FIRE_LIGHT,
  EXPLOSION_LIGHT,
  INCENDIARY_DART_LIGHT,
  PORTAL_ACTIVATE_LIGHT,
  CONFUSION_GAS_LIGHT,
  DARKNESS_CLOUD_LIGHT,
  FORCEFIELD_LIGHT,
  CRYSTAL_WALL_LIGHT,
  CANDLE_LIGHT,
  HAUNTED_TORCH_LIGHT,
  GLYPH_LIGHT_DIM,
  GLYPH_LIGHT_BRIGHT,
  SACRED_GLYPH_LIGHT,
  DESCENT_LIGHT,
  NUMBER_LIGHT_KINDS
};

// Item categories
enum ItemCategory
{
  NONE = 0,
  FOOD = Fl(0),
  WEAPON = Fl(1),
  ARMOR = Fl(2),
  POTION = Fl(3),
  SCROLL = Fl(4),
  STAFF = Fl(5),
  WAND = Fl(6),
  RING = Fl(7),
  CHARM = Fl(8),
  GOLD = Fl(9),
  AMULET = Fl(10),
  GEM = Fl(11),
  KEY = Fl(12),

  CAN_BE_DETECTED = (WEAPON | ARMOR | POTION | SCROLL | RING | CHARM | WAND | STAFF | AMULET),
  PRENAMED_CATEGORY = (FOOD | GOLD | AMULET | GEM | KEY),
  NEVER_IDENTIFIABLE = (FOOD | CHARM | GOLD | AMULET | GEM | KEY),
  COUNTS_TOWARD_SCORE = (GOLD | AMULET | GEM),
  CAN_BE_SWAPPED = (WEAPON | ARMOR | STAFF | CHARM | RING),
  ALL_ITEMS = (FOOD | POTION | WEAPON | ARMOR | STAFF | WAND | SCROLL | RING | CHARM | GOLD | AMULET | GEM | KEY),
};

enum KeyKind
{
  KEY_DOOR,
  KEY_CAGE,
  KEY_PORTAL,
  NUMBER_KEY_TYPES
};

enum FoodKind
{
  RATION,
  FRUIT,
  NUMBER_FOOD_KINDS
};

enum PotionKind
{
  POTION_LIFE,
  POTION_STRENGTH,
  POTION_TELEPATHY,
  POTION_LEVITATION,
  POTION_DETECT_MAGIC,
  POTION_HASTE_SELF,
  POTION_FIRE_IMMUNITY,
  POTION_INVISIBILITY,
  POTION_POISON,
  POTION_PARALYSIS,
  POTION_HALLUCINATION,
  POTION_CONFUSION,
  POTION_INCINERATION,
  POTION_DARKNESS,
  POTION_DESCENT,
  POTION_LICHEN,
  NUMBER_POTION_KINDS
};

enum WeaponKind
{
  DAGGER,
  SWORD,
  BROADSWORD,

  WHIP,
  RAPIER,
  FLAIL,

  MACE,
  HAMMER,

  SPEAR,
  PIKE,

  AXE,
  WAR_AXE,

  DART,
  INCENDIARY_DART,
  JAVELIN,
  NUMBER_WEAPON_KINDS
};

enum WeaponEnchants
{
  W_SPEED,
  W_QUIETUS,
  W_PARALYSIS,
  W_MULTIPLICITY,
  W_SLOWING,
  W_CONFUSION,
  W_FORCE,
  W_SLAYING,
  W_MERCY,
  NUMBER_GOOD_WEAPON_ENCHANT_KINDS = W_MERCY,
  W_PLENTY,
  NUMBER_WEAPON_RUNIC_KINDS
};

enum ArmorKind
{
  LEATHER_ARMOR,
  SCALE_MAIL,
  CHAIN_MAIL,
  BANDED_MAIL,
  SPLINT_MAIL,
  PLATE_MAIL,
  NUMBER_ARMOR_KINDS
};

enum ArmorEnchants
{
  A_MULTIPLICITY,
  A_MUTUALITY,
  A_ABSORPTION,
  A_REPRISAL,
  A_IMMUNITY,
  A_REFLECTION,
  A_RESPIRATION,
  A_DAMPENING,
  A_BURDEN,
  NUMBER_GOOD_ARMOR_ENCHANT_KINDS = A_BURDEN,
  A_VULNERABILITY,
  A_IMMOLATION,
  NUMBER_ARMOR_ENCHANT_KINDS,
};

enum WandKind
{
  WAND_TELEPORT,
  WAND_SLOW,
  WAND_POLYMORPH,
  WAND_NEGATION,
  WAND_DOMINATION,
  WAND_BECKONING,
  WAND_PLENTY,
  WAND_INVISIBILITY,
  WAND_EMPOWERMENT,
  NUMBER_WAND_KINDS
};

enum StaffKind
{
  STAFF_LIGHTNING,
  STAFF_FIRE,
  STAFF_POISON,
  STAFF_TUNNELING,
  STAFF_BLINKING,
  STAFF_ENTRANCEMENT,
  STAFF_OBSTRUCTION,
  STAFF_DISCORD,
  STAFF_CONJURATION,
  STAFF_HEALING,
  STAFF_HASTE,
  STAFF_PROTECTION,
  NUMBER_STAFF_KINDS
};

// these must be wand bolts, in order, and then staff bolts, in order:
enum BoltType
{
  BOLT_NONE = 0,
  BOLT_TELEPORT,
  BOLT_SLOW,
  BOLT_POLYMORPH,
  BOLT_NEGATION,
  BOLT_DOMINATION,
  BOLT_BECKONING,
  BOLT_PLENTY,
  BOLT_INVISIBILITY,
  BOLT_EMPOWERMENT,
  BOLT_LIGHTNING,
  BOLT_FIRE,
  BOLT_POISON,
  BOLT_TUNNELING,
  BOLT_BLINKING,
  BOLT_ENTRANCEMENT,
  BOLT_OBSTRUCTION,
  BOLT_DISCORD,
  BOLT_CONJURATION,
  BOLT_HEALING,
  BOLT_HASTE,
  BOLT_SLOW_2,
  BOLT_SHIELDING,
  BOLT_SPIDERWEB,
  BOLT_SPARK,
  BOLT_DRAGONFIRE,
  BOLT_DISTANCE_ATTACK,
  BOLT_POISON_DART,
  BOLT_ACID_TURRET_ATTACK,
  BOLT_ANCIENT_SPIRIT_VINES,
  BOLT_WHIP,
  NUMBER_BOLT_KINDS
};

enum RingKind
{
  RING_CLAIRVOYANCE,
  RING_STEALTH,
  RING_REGENERATION,
  RING_TRANSFERENCE,
  RING_LIGHT,
  RING_AWARENESS,
  RING_WISDOM,
  RING_REAPING,
  NUMBER_RING_KINDS
};

enum CharmKind
{
  CHARM_HEALTH,
  CHARM_PROTECTION,
  CHARM_HASTE,
  CHARM_FIRE_IMMUNITY,
  CHARM_INVISIBILITY,
  CHARM_TELEPATHY,
  CHARM_LEVITATION,
  CHARM_SHATTERING,
  CHARM_GUARDIAN,
  CHARM_TELEPORTATION,
  CHARM_RECHARGING,
  CHARM_NEGATION,
  NUMBER_CHARM_KINDS
};

enum ScrollKind
{
  SCROLL_ENCHANTING,
  SCROLL_IDENTIFY,
  SCROLL_TELEPORT,
  SCROLL_REMOVE_CURSE,
  SCROLL_RECHARGING,
  SCROLL_PROTECT_ARMOR,
  SCROLL_PROTECT_WEAPON,
  SCROLL_SANCTUARY,
  SCROLL_MAGIC_MAPPING,
  SCROLL_NEGATION,
  SCROLL_SHATTERING,
  SCROLL_DISCORD,
  SCROLL_AGGRAVATE_MONSTER,
  SCROLL_SUMMON_MONSTER,
  NUMBER_SCROLL_KINDS
};

#define MAX_PACK_ITEMS 26



#define NUMBER_MUTATORS 8

#define NUMBER_HORDES 168

#define MONSTER_CLASS_COUNT 13

// flavors

#define NUMBER_ITEM_COLORS 21
#define NUMBER_TITLE_PHONEMES 21
#define NUMBER_ITEM_WOODS 21
#define NUMBER_POTION_DESCRIPTIONS 18
#define NUMBER_ITEM_METALS 12
#define NUMBER_ITEM_GEMS 18

// Dungeon flags
enum tileFlags
{
  DISCOVERED = Fl(0),
  VISIBLE = Fl(1),  // cell has sufficient light and is in field of view, ready to draw.
  HAS_PLAYER = Fl(2),
  HAS_MONSTER = Fl(3),
  HAS_DORMANT_MONSTER = Fl(4),  // hidden monster on the square
  HAS_ITEM = Fl(5),
  IN_FIELD_OF_VIEW = Fl(6),  // player has unobstructed line of sight whether or not there is enough light
  WAS_VISIBLE = Fl(7),
  HAS_DOWN_STAIRS = Fl(8),
  HAS_UP_STAIRS = Fl(9),
  IS_IN_SHADOW = Fl(10),  // so that a player gains an automatic stealth bonus
  MAGIC_MAPPED = Fl(11),
  ITEM_DETECTED = Fl(12),
  CLAIRVOYANT_VISIBLE = Fl(13),
  WAS_CLAIRVOYANT_VISIBLE = Fl(14),
  CLAIRVOYANT_DARKENED = Fl(15),      // magical blindness from a cursed ring of clairvoyance
  CAUGHT_FIRE_THIS_TURN = Fl(16),     // so that fire does not spread asymmetrically
  PRESSURE_PLATE_DEPRESSED = Fl(17),  // so that traps do not trigger repeatedly while you stand on them
  STABLE_MEMORY = Fl(18),             // redraws will simply be pulled from the memory array, not recalculated
  KNOWN_TO_BE_TRAP_FREE = Fl(19),     // keep track of where the player has stepped as he knows no traps are there
  IS_IN_PATH = Fl(20),                // the yellow trail leading to the cursor
  IN_LOOP = Fl(21),                   // this cell is part of a terrain loop
  IS_CHOKEPOINT = Fl(22),             // if this cell is blocked, part of the map will be rendered inaccessible
  IS_GATE_SITE = Fl(23),              // consider placing a locked door here
  IS_IN_ROOM_MACHINE = Fl(24),
  IS_IN_AREA_MACHINE = Fl(25),
  IS_POWERED = Fl(26),   // has been activated by machine power this turn (can probably be eliminate if needed)
  IMPREGNABLE = Fl(27),  // no tunneling allowed!
  TERRAIN_COLORS_DANCING = Fl(28),  // colors here will sparkle when the game is idle
  TELEPATHIC_VISIBLE = Fl(29),      // potions of telepathy let you see through other creatures' eyes
  WAS_TELEPATHIC_VISIBLE = Fl(30),  // potions of telepathy let you see through other creatures' eyes

  HAS_STAIRS = (HAS_UP_STAIRS | HAS_DOWN_STAIRS),
  IS_IN_MACHINE = (IS_IN_ROOM_MACHINE | IS_IN_AREA_MACHINE),  // sacred ground; don't generate items here, or teleport
                                                              // randomly to it

  PERMANENT_TILE_FLAGS = (DISCOVERED | MAGIC_MAPPED | ITEM_DETECTED | HAS_ITEM | HAS_DORMANT_MONSTER | HAS_UP_STAIRS |
                          HAS_DOWN_STAIRS | PRESSURE_PLATE_DEPRESSED | STABLE_MEMORY | KNOWN_TO_BE_TRAP_FREE | IN_LOOP |
                          IS_CHOKEPOINT | IS_GATE_SITE | IS_IN_MACHINE | IMPREGNABLE),

  ANY_KIND_OF_VISIBLE = (VISIBLE | CLAIRVOYANT_VISIBLE | TELEPATHIC_VISIBLE),
};

#define TURNS_FOR_FULL_REGEN 300
#define STOMACH_SIZE 2150
#define HUNGER_THRESHOLD (STOMACH_SIZE - 1800)
#define WEAK_THRESHOLD 150
#define FAINT_THRESHOLD 50
#define MAX_EXP_LEVEL 20
#define MAX_EXP 100000000L

#define XPXP_NEEDED_FOR_TELEPATHIC_BOND 1400  // XPXP required to enable telepathic awareness with the ally

#define ROOM_MIN_WIDTH 4
#define ROOM_MAX_WIDTH 20
#define ROOM_MIN_HEIGHT 3
#define ROOM_MAX_HEIGHT 7
#define HORIZONTAL_CORRIDOR_MIN_LENGTH 5
#define HORIZONTAL_CORRIDOR_MAX_LENGTH 15
#define VERTICAL_CORRIDOR_MIN_LENGTH 2
#define VERTICAL_CORRIDOR_MAX_LENGTH 9
#define CROSS_ROOM_MIN_WIDTH 3
#define CROSS_ROOM_MAX_WIDTH 12
#define CROSS_ROOM_MIN_HEIGHT 2
#define CROSS_ROOM_MAX_HEIGHT 5
#define MIN_SCALED_ROOM_DIMENSION 2

#define ROOM_TYPE_COUNT 8

#define CORRIDOR_WIDTH 1

#define WAYPOINT_SIGHT_RADIUS 10
#define MAX_WAYPOINT_COUNT 40

#define MAX_ITEMS_IN_MONSTER_ITEMS_HOPPER 100

// Making these larger means cave generation will take more trials; set them too high and the program will hang.
#define CAVE_MIN_WIDTH 50
#define CAVE_MIN_HEIGHT 20

// Keyboard commands:
#define UP_KEY 'k'
#define DOWN_KEY 'j'
#define LEFT_KEY 'h'
#define RIGHT_KEY 'l'
#define UP_ARROW 63232
#define LEFT_ARROW 63234
#define DOWN_ARROW 63233
#define RIGHT_ARROW 63235
#define UPLEFT_KEY 'y'
#define UPRIGHT_KEY 'u'
#define DOWNLEFT_KEY 'b'
#define DOWNRIGHT_KEY 'n'
#define DESCEND_KEY '>'
#define ASCEND_KEY '<'
#define REST_KEY 'z'
#define AUTO_REST_KEY 'Z'
#define SEARCH_KEY 's'
#define INVENTORY_KEY 'i'
#define ACKNOWLEDGE_KEY ' '
#define EQUIP_KEY 'e'
#define UNEQUIP_KEY 'r'
#define APPLY_KEY 'a'
#define THROW_KEY 't'
#define RELABEL_KEY 'R'
#define TRUE_COLORS_KEY '\\'
#define AGGRO_DISPLAY_KEY ']'
#define DROP_KEY 'd'
#define CALL_KEY 'c'
#define QUIT_KEY 'Q'
#define MESSAGE_ARCHIVE_KEY 'M'
#define HELP_KEY '?'
#define DISCOVERIES_KEY 'D'
#define EXPLORE_KEY 'x'
#define AUTOPLAY_KEY 'A'
#define SEED_KEY '~'
#define EASY_MODE_KEY '&'
#define ESCAPE_KEY '\033'
#define RETURN_KEY '\015'
#define ENTER_KEY '\012'
#define DELETE_KEY '\177'
#define TAB_KEY '\t'
#define SHIFT_TAB_KEY 25  // Cocoa reports shift-tab this way for some reason.
#define PERIOD_KEY '.'
#define VIEW_RECORDING_KEY 'V'
#define LOAD_SAVED_GAME_KEY 'O'
#define SAVE_GAME_KEY 'S'
#define NEW_GAME_KEY 'N'
#define NUMPAD_0 48
#define NUMPAD_1 49
#define NUMPAD_2 50
#define NUMPAD_3 51
#define NUMPAD_4 52
#define NUMPAD_5 53
#define NUMPAD_6 54
#define NUMPAD_7 55
#define NUMPAD_8 56
#define NUMPAD_9 57
#define PAGE_UP_KEY 63276
#define PAGE_DOWN_KEY 63277

#define UNKNOWN_KEY (128 + 19)

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define clamp(x, low, hi) (min(hi, max(x, low)))  // pins x to the [y, z] interval

#define terrainFlags(x, y)                                                                                             \
  (tileCatalog[pmap[x][y].layers[DUNGEON]].flags | tileCatalog[pmap[x][y].layers[LIQUID]].flags |                      \
   tileCatalog[pmap[x][y].layers[SURFACE]].flags | tileCatalog[pmap[x][y].layers[GAS]].flags)

#define terrainMechFlags(x, y)                                                                                         \
  (tileCatalog[pmap[x][y].layers[DUNGEON]].mechFlags | tileCatalog[pmap[x][y].layers[LIQUID]].mechFlags |              \
   tileCatalog[pmap[x][y].layers[SURFACE]].mechFlags | tileCatalog[pmap[x][y].layers[GAS]].mechFlags)

#ifdef BROGUE_ASSERTS
bool cellHasTerrainFlag(int x, int y, unsigned long flagMask);
#else
#define cellHasTerrainFlag(x, y, flagMask) ((flagMask)&terrainFlags((x), (y)) ? true : false)
#endif
#define cellHasTMFlag(x, y, flagMask) ((flagMask)&terrainMechFlags((x), (y)) ? true : false)

#define cellHasTerrainType(x, y, terrain)                                                                              \
  ((pmap[x][y].layers[DUNGEON] == (terrain) || pmap[x][y].layers[LIQUID] == (terrain) ||                               \
    pmap[x][y].layers[SURFACE] == (terrain) || pmap[x][y].layers[GAS] == (terrain)) ?                                  \
       true :                                                                                                          \
       false)

#define cellHasKnownTerrainFlag(x, y, flagMask) ((flagMask)&pmap[(x)][(y)].rememberedTerrainFlags ? true : false)

#define cellIsPassableOrDoor(x, y)                                                                                     \
  (!cellHasTerrainFlag((x), (y), T_PATHING_BLOCKER) ||                                                                 \
   (cellHasTMFlag((x), (y), (TM_IS_SECRET | TM_PROMOTES_WITH_KEY | TM_CONNECTS_LEVEL)) &&                              \
    cellHasTerrainFlag((x), (y), T_OBSTRUCTS_PASSABILITY)))

#define coordinatesAreInMap(x, y) ((x) >= 0 && (x) < DCOLS && (y) >= 0 && (y) < DROWS)
#define coordinatesAreInWindow(x, y) ((x) >= 0 && (x) < COLS && (y) >= 0 && (y) < ROWS)
#define mapToWindowX(x) ((x) + STAT_BAR_WIDTH + 1)
#define mapToWindowY(y) ((y) + MESSAGE_LINES)
#define windowToMapX(x) ((x)-STAT_BAR_WIDTH - 1)
#define windowToMapY(y) ((y)-MESSAGE_LINES)

#define playerCanDirectlySee(x, y) (pmap[x][y].flags & VISIBLE)
#define playerCanSee(x, y) (pmap[x][y].flags & ANY_KIND_OF_VISIBLE)
#define playerCanSeeOrSense(x, y)                                                                                      \
  ((pmap[x][y].flags & ANY_KIND_OF_VISIBLE) ||                                                                         \
   (rogue.playbackOmniscience && (pmap[x][y].layers[DUNGEON] != GRANITE || (pmap[x][y].flags & DISCOVERED))))

#define CYCLE_MONSTERS_AND_PLAYERS(x)                                                                                  \
  for ((x) = &player; (x) != nullptr; (x) = ((x) == &player ? monsters->nextCreature : (x)->nextCreature))

#define assureCosmeticRNG                                                                                              \
  int oldRNG = rogue.RNG;                                                                                              \
  rogue.RNG = RNG_COSMETIC;
#define restoreRNG rogue.RNG = oldRNG;

#define MIN_COLOR_DIFF 600
// weighted sum of the squares of the component differences. Weights are according to color perception.
#define COLOR_DIFF(f, b)                                                                                               \
  (((f).red - (b).red) * ((f).red - (b).red) * 0.2126 + ((f).green - (b).green) * ((f).green - (b).green) * 0.7152 +   \
   ((f).blue - (b).blue) * ((f).blue - (b).blue) * 0.0722)

// game data formulae:

#define staffDamageLow(enchant) ((int)(3 * (2 + (enchant)) / 4 + FLOAT_FUDGE))
#define staffDamageHigh(enchant) ((int)(4 + 5 * (enchant) / 2 + FLOAT_FUDGE))
#define staffDamage(enchant) (randClumpedRange(staffDamageLow(enchant), staffDamageHigh(enchant), 1 + (enchant) / 3))
#define staffPoison(enchant) ((int)(5 * pow(1.3, (double)(enchant)-2) + FLOAT_FUDGE))
#define staffBlinkDistance(enchant) ((int)((enchant)*2 + 2 + FLOAT_FUDGE))
#define staffHasteDuration(enchant) ((int)(2 + (enchant)*4 + FLOAT_FUDGE))
#define staffBladeCount(enchant) ((int)((enchant)*3 / 2 + FLOAT_FUDGE))
#define staffDiscordDuration(enchant) ((int)((enchant)*4 + FLOAT_FUDGE))
#define staffProtection(enchant) ((int)(50 * pow(1.53, (double)(enchant)-2) + FLOAT_FUDGE))
#define staffEntrancementDuration(enchant) ((int)((enchant)*3 + FLOAT_FUDGE))

#define ringWisdomMultiplier(enchant) (int)(10 * pow(1.3, min(27, (enchant))) + FLOAT_FUDGE)

#define charmHealing(enchant) ((int)(clamp(20 * (enchant), 0, 100) + FLOAT_FUDGE))
#define charmProtection(enchant) ((int)(150 * pow(1.35, (double)(enchant)-1) + FLOAT_FUDGE))
#define charmShattering(enchant) ((int)(4 + (enchant) + FLOAT_FUDGE))
#define charmGuardianLifespan(enchant) ((int)(4 + (2 * (enchant)) + FLOAT_FUDGE))
#define charmNegationRadius(enchant) ((int)(1 + (3 * (enchant)) + FLOAT_FUDGE))

#define wandDominate(monst)                                                                                            \
  (((monst)->currentHP * 5 < (monst)->info.maxHP) ?                                                                    \
       100 :                                                                                                           \
       max(0, 100 * ((monst)->info.maxHP - (monst)->currentHP) / (monst)->info.maxHP))

#define weaponParalysisDuration(enchant) (max(2, (int)(2 + ((enchant) / 2) + FLOAT_FUDGE)))
#define weaponConfusionDuration(enchant) (max(3, (int)(1.5 * (enchant) + FLOAT_FUDGE)))
#define weaponForceDistance(enchant)                                                                                   \
  (max(4, (((int)(enchant + FLOAT_FUDGE)) * 2 + 2)))  // Depends on definition of staffBlinkDistance() above.
#define weaponSlowDuration(enchant) (max(3, (int)(((enchant) + 2) * ((enchant) + 2) / 3 + FLOAT_FUDGE)))
#define weaponImageCount(enchant) (clamp((int)((enchant) / 3 + FLOAT_FUDGE), 1, 7))
#define weaponImageDuration(enchant) 3  //(max((int) (1 + (enchant) / 3), 2))

#define armorReprisalPercent(enchant) (max(5, (int)((enchant)*5 + FLOAT_FUDGE)))
#define armorAbsorptionMax(enchant) (max(1, (int)((enchant) + FLOAT_FUDGE)))
#define armorImageCount(enchant) (clamp((int)((enchant) / 3 + FLOAT_FUDGE), 1, 5))
#define reflectionChance(enchant) (clamp((100 - (int)(100 * pow(0.85, (enchant)) + FLOAT_FUDGE)), 1, 100))

#define turnsForFullRegen(bonus) ((long)(1000 * TURNS_FOR_FULL_REGEN * pow(0.75, (bonus)) + 2000 + FLOAT_FUDGE))
// This will max out at full regeneration in about two turns.
// This is the Syd nerf, after Syd broke the game over his knee with a +18 ring of regeneration.

// structs



// keeps track of graphics so we only redraw if the cell has changed:
typedef struct cellDisplayBuffer
{
  uchar character;
  char foreColorComponents[3];
  char backColorComponents[3];
  char opacity;
  bool needsUpdate;
} cellDisplayBuffer;

typedef struct pcell
{                                               // permanent cell; have to remember this stuff to save levels
  enum TileType layers[NUMBER_TERRAIN_LAYERS];  // terrain
  unsigned long flags;                          // non-terrain cell flags
  unsigned int volume;                          // quantity of gas in cell
  unsigned char machineNumber;
  cellDisplayBuffer rememberedAppearance;  // how the player remembers the cell to look
  ItemCategory rememberedItemCategory;     // what category of item the player remembers lying there
  int rememberedItemKind;                  // what kind of item the player remembers lying there
  int rememberedItemQuantity;              // how many of the item the player remembers lying there
  enum TileType rememberedTerrain;  // what the player remembers as the terrain (i.e. highest priority terrain upon last
                                    // seeing)
  unsigned long rememberedCellFlags;     // map cell flags the player remembers from that spot
  unsigned long rememberedTerrainFlags;  // terrain flags the player remembers from that spot
  unsigned long rememberedTMFlags;       // TM flags the player remembers from that spot
} pcell;

struct TCell
{                   // transient cell; stuff we don't need to remember between levels
  int light[3];     // RGB components of lighting
  int oldLight[3];  // compare with subsequent lighting to determine whether to refresh cell
};




enum ItemFlags
{
  ITEM_IDENTIFIED = Fl(0),
  ITEM_EQUIPPED = Fl(1),
  ITEM_CURSED = Fl(2),
  ITEM_PROTECTED = Fl(3),
  // unused               = Fl(4),
  ITEM_RUNIC = Fl(5),
  ITEM_RUNIC_HINTED = Fl(6),
  ITEM_RUNIC_IDENTIFIED = Fl(7),
  ITEM_CAN_BE_IDENTIFIED = Fl(8),
  ITEM_PREPLACED = Fl(9),
  ITEM_FLAMMABLE = Fl(10),
  ITEM_MAGIC_DETECTED = Fl(11),
  ITEM_MAX_CHARGES_KNOWN = Fl(12),
  ITEM_IS_KEY = Fl(13),

  ITEM_ATTACKS_HIT_SLOWLY = Fl(14),    // mace, hammer
  ITEM_ATTACKS_EXTEND = Fl(15),        // whip
  ITEM_ATTACKS_QUICKLY = Fl(16),       // rapier
  ITEM_ATTACKS_PENETRATE = Fl(17),     // spear, pike
  ITEM_ATTACKS_ALL_ADJACENT = Fl(18),  // axe, war axe
  ITEM_LUNGE_ATTACKS = Fl(19),         // rapier
  ITEM_SNEAK_ATTACK_BONUS = Fl(20),    // dagger
  ITEM_PASS_ATTACKS = Fl(21),          // flail

  ITEM_KIND_AUTO_ID = Fl(22),   // the item type will become known when the item is picked up.
  ITEM_PLAYER_AVOIDS = Fl(23),  // explore and travel will try to avoid picking the item up
};

#define KEY_ID_MAXIMUM 20

struct KeyLocationProfile
{
  int x;
  int y;
  int machine;
  bool disposableHere;
};



struct ItemTable
{
  char* name;
  char* flavor;
  char callTitle[30];
  int frequency;
  int marketValue;
  int strengthRequired;
  RandomRange range;
  bool identified;
  bool called;
  char description[1500];
};


enum dungeonProfileTypes
{
  DP_BASIC,
  DP_BASIC_FIRST_ROOM,

  DP_GOBLIN_WARREN,
  DP_SENTINEL_SANCTUARY,

  NUMBER_DUNGEON_PROFILES,
};

struct LightSource
{
  const Color* lightColor;
  RandomRange lightRadius;
  int radialFadeToPercent;
  bool passThroughCreatures;  // generally no, but miner light does
};

struct Flare
{
  LightSource* light;        // Flare light
  int coeffChangeAmount;     // The constant amount by which the coefficient changes per frame, e.g. -25 means it gets
                             // 25% dimmer per frame.
  int coeffLimit;            // Flare ends if the coefficient passes this percentage (whether going up or down).
  int xLoc, yLoc;            // Current flare location.
  long coeff;                // Current flare coefficient; always starts at 100.
  unsigned long turnNumber;  // So we can eliminate those that fired one or more turns ago.
};

enum DFFlags
{
  DFF_EVACUATE_CREATURES_FIRST = Fl(0),  // Creatures in the DF area get moved outside of it
  DFF_SUBSEQ_EVERYWHERE =
      Fl(1),  // Subsequent DF spawns in every cell that this DF spawns in, instead of only the origin
  DFF_TREAT_AS_BLOCKING =
      Fl(2),  // If filling the footprint of this DF with walls would disrupt level connectivity, then abort.
  DFF_PERMIT_BLOCKING = Fl(3),  // Generate this DF without regard to level connectivity.
  DFF_ACTIVATE_DORMANT_MONSTER =
      Fl(4),  // Dormant monsters on this tile will appear -- e.g. when a statue bursts to reveal a monster.
  DFF_CLEAR_OTHER_TERRAIN = Fl(5),  // Erase other terrain in the footprint of this DF.
  DFF_BLOCKED_BY_OTHER_LAYERS =
      Fl(6),                  // Will not propagate into a cell if any layer in that cell has a superior priority.
  DFF_SUPERPRIORITY = Fl(7),  // Will overwrite terrain of a superior priority.
  DFF_AGGRAVATES_MONSTERS =
      Fl(8),  // Will act as though an aggravate monster scroll of effectRadius radius had been read at that point.
  DFF_RESURRECT_ALLY = Fl(9),  // Will bring back to life your most recently deceased ally.
};

enum BoltEffects
{
  BE_NONE,
  BE_ATTACK,
  BE_TELEPORT,
  BE_SLOW,
  BE_POLYMORPH,
  BE_NEGATION,
  BE_DOMINATION,
  BE_BECKONING,
  BE_PLENTY,
  BE_INVISIBILITY,
  BE_EMPOWERMENT,
  BE_DAMAGE,
  BE_POISON,
  BE_TUNNELING,
  BE_BLINKING,
  BE_ENTRANCEMENT,
  BE_OBSTRUCTION,
  BE_DISCORD,
  BE_CONJURATION,
  BE_HEALING,
  BE_HASTE,
  BE_SHIELDING,
};

enum BoltFlags
{
  BF_PASSES_THRU_CREATURES = Fl(0),  // Bolt continues through creatures (e.g. lightning and tunneling)
  BF_HALTS_BEFORE_OBSTRUCTION =
      Fl(1),  // Bolt takes effect the space before it terminates (e.g. conjuration, obstruction, blinking)
  BF_TARGET_ALLIES = Fl(2),   // Staffs/wands/creatures that shoot this bolt will auto-target allies.
  BF_TARGET_ENEMIES = Fl(3),  // Staffs/wands/creatures that shoot this bolt will auto-target enemies.
  BF_FIERY = Fl(4),           // Bolt will light flammable terrain on fire as it passes, and will ignite monsters hit.
  BF_NEVER_REFLECTS = Fl(5),  // Bolt will never reflect (e.g. spiderweb, arrows).
  BF_NOT_LEARNABLE = Fl(6),   // This technique cannot be absorbed by empowered allies.
  BF_NOT_NEGATABLE = Fl(7),   // Won't be erased by negation.
  BF_ELECTRIC = Fl(8),        // Activates terrain that has TM_PROMOTES_ON_ELECTRICITY
  BF_DISPLAY_CHAR_ALONG_LENGTH =
      Fl(9),  // Display the character along the entire length of the bolt instead of just at the front.
};

struct Bolt
{
  char name[DCOLS];
  char description[COLS];
  char abilityDescription[COLS * 2];
  uchar theChar;
  const Color* foreColor;
  const Color* backColor;
  int boltEffect;
  int magnitude;
  int pathDF;
  int targetDF;
  unsigned long forbiddenMonsterFlags;
  unsigned long flags;
};

// Level profiles, affecting what rooms get chosen and how they're connected:
struct DungeonProfile
{
  // Room type weights (in the natural dungeon, these are also adjusted based on depth):
  int roomFrequencies[ROOM_TYPE_COUNT];

  int corridorChance;
};

// Dungeon features, spawned from Architect.c:
struct DungeonFeature
{
  // tile info:
  enum TileType tile;
  enum dungeonLayers layer;

  // spawning pattern:
  int startProbability;
  int probabilityDecrement;
  unsigned long flags;
  char description[DCOLS];
  enum LightType lightFlare;
  const Color* flashColor;
  int effectRadius;
  enum TileType propagationTerrain;
  enum DungeonFeatureTypes subsequentDF;
  bool messageDisplayed;
};

// Terrain types:
struct FloorTileType
{
  // appearance:
  uchar displayChar;
  const Color* foreColor;
  const Color* backColor;
  int drawPriority;     // priority (lower number means higher priority); governs drawing as well as tile replacement
                        // comparisons.
  char chanceToIgnite;  // chance to burn if a flame terrain is on one of the four cardinal neighbors
  enum DungeonFeatureTypes fireType;      // spawn this DF when the terrain ignites (or, if it's T_IS_DF_TRAP, when the
                                          // pressure plate clicks)
  enum DungeonFeatureTypes discoverType;  // spawn this DF when successfully searched if T_IS_SECRET is set
  enum DungeonFeatureTypes promoteType;   // creates this dungeon spawn type when it promotes for some other reason
                                          // (random promotion or promotion through machine activation)
  int promoteChance;  // percent chance per turn to spawn the promotion type; will also vanish upon doing so if
                      // T_VANISHES_UPON_PROMOTION is set
  int glowLight;      // if it glows, this is the ID of the light type
  unsigned long flags;
  unsigned long mechFlags;
  char description[COLS];
  char flavorText[COLS];
};

enum TerrainFlagCatalog
{
  T_OBSTRUCTS_PASSABILITY = Fl(0),        // cannot be walked through
  T_OBSTRUCTS_VISION = Fl(1),             // blocks line of sight
  T_OBSTRUCTS_ITEMS = Fl(2),              // items can't be on this tile
  T_OBSTRUCTS_SURFACE_EFFECTS = Fl(3),    // grass, blood, etc. cannot exist on this tile
  T_OBSTRUCTS_GAS = Fl(4),                // blocks the permeation of gas
  T_OBSTRUCTS_DIAGONAL_MOVEMENT = Fl(5),  // can't step diagonally around this tile
  T_SPONTANEOUSLY_IGNITES = Fl(6),        // monsters avoid unless chasing player or immune to fire
  T_AUTO_DESCENT = Fl(7),                 // automatically drops creatures down a depth level and does some damage (2d6)
  T_LAVA_INSTA_DEATH = Fl(8),             // kills any non-levitating non-fire-immune creature instantly
  T_CAUSES_POISON = Fl(9),                // any non-levitating creature gets 10 poison
  T_IS_FLAMMABLE = Fl(10),                // terrain can catch fire
  T_IS_FIRE = Fl(11),                     // terrain is a type of fire; ignites neighboring flammable cells
  T_ENTANGLES = Fl(12),                   // entangles players and monsters like a spiderweb
  T_IS_DEEP_WATER = Fl(13),               // steals items 50% of the time and moves them around randomly
  T_CAUSES_DAMAGE = Fl(14),               // anything on the tile takes max(1-2, 10%) damage per turn
  T_CAUSES_NAUSEA = Fl(15),               // any creature on the tile becomes nauseous
  T_CAUSES_PARALYSIS = Fl(16),            // anything caught on this tile is paralyzed
  T_CAUSES_CONFUSION = Fl(17),            // causes creatures on this tile to become confused
  T_CAUSES_HEALING = Fl(18),              // heals 20% max HP per turn for any player or non-inanimate monsters
  T_IS_DF_TRAP = Fl(19),                  // spews gas of type specified in fireType when stepped on
  T_CAUSES_EXPLOSIVE_DAMAGE =
      Fl(20),         // is an explosion; deals higher of 15-20 or 50% damage instantly, but not again for five turns
  T_SACRED = Fl(21),  // monsters that aren't allies of the player will avoid stepping here

  T_OBSTRUCTS_SCENT = (T_OBSTRUCTS_PASSABILITY | T_OBSTRUCTS_VISION | T_AUTO_DESCENT | T_LAVA_INSTA_DEATH |
                       T_IS_DEEP_WATER | T_SPONTANEOUSLY_IGNITES),
  T_PATHING_BLOCKER = (T_OBSTRUCTS_PASSABILITY | T_AUTO_DESCENT | T_IS_DF_TRAP | T_LAVA_INSTA_DEATH | T_IS_DEEP_WATER |
                       T_IS_FIRE | T_SPONTANEOUSLY_IGNITES),
  T_DIVIDES_LEVEL = (T_OBSTRUCTS_PASSABILITY | T_AUTO_DESCENT | T_IS_DF_TRAP | T_LAVA_INSTA_DEATH | T_IS_DEEP_WATER),
  T_LAKE_PATHING_BLOCKER = (T_AUTO_DESCENT | T_LAVA_INSTA_DEATH | T_IS_DEEP_WATER | T_SPONTANEOUSLY_IGNITES),
  T_WAYPOINT_BLOCKER = (T_OBSTRUCTS_PASSABILITY | T_AUTO_DESCENT | T_IS_DF_TRAP | T_LAVA_INSTA_DEATH | T_IS_DEEP_WATER |
                        T_SPONTANEOUSLY_IGNITES),
  T_MOVES_ITEMS = (T_IS_DEEP_WATER | T_LAVA_INSTA_DEATH),
  T_CAN_BE_BRIDGED = (T_AUTO_DESCENT),
  T_OBSTRUCTS_EVERYTHING = (T_OBSTRUCTS_PASSABILITY | T_OBSTRUCTS_VISION | T_OBSTRUCTS_ITEMS | T_OBSTRUCTS_GAS |
                            T_OBSTRUCTS_SURFACE_EFFECTS | T_OBSTRUCTS_DIAGONAL_MOVEMENT),
  T_HARMFUL_TERRAIN = (T_CAUSES_POISON | T_IS_FIRE | T_CAUSES_DAMAGE | T_CAUSES_PARALYSIS | T_CAUSES_CONFUSION |
                       T_CAUSES_EXPLOSIVE_DAMAGE),
  T_RESPIRATION_IMMUNITIES = (T_CAUSES_DAMAGE | T_CAUSES_CONFUSION | T_CAUSES_PARALYSIS | T_CAUSES_NAUSEA),
};

enum TerrainMechanicalFlagCatalog
{
  TM_IS_SECRET = Fl(0),  // successful search or being stepped on while visible transforms it into discoverType
  TM_PROMOTES_WITH_KEY =
      Fl(1),  // promotes if the key is present on the tile (in your pack, carried by monster, or lying on the ground)
  TM_PROMOTES_WITHOUT_KEY = Fl(2),  // promotes if the key is NOT present on the tile (in your pack, carried by monster,
                                    // or lying on the ground)
  TM_PROMOTES_ON_STEP = Fl(3),  // promotes when a creature, player or item is on the tile (whether or not levitating)
  TM_PROMOTES_ON_ITEM_PICKUP = Fl(4),   // promotes when an item is lifted from the tile (primarily for altars)
  TM_PROMOTES_ON_PLAYER_ENTRY = Fl(5),  // promotes when the player enters the tile (whether or not levitating)
  TM_PROMOTES_ON_ELECTRICITY = Fl(6),   // promotes when hit by a lightning bolt
  TM_ALLOWS_SUBMERGING = Fl(7),         // allows submersible monsters to submerge in this terrain
  TM_IS_WIRED = Fl(8),                  // if wired, promotes when powered, and sends power when promoting
  TM_IS_CIRCUIT_BREAKER = Fl(9),        // prevents power from circulating in its machine
  TM_GAS_DISSIPATES = Fl(10),           // does not just hang in the air forever
  TM_GAS_DISSIPATES_QUICKLY = Fl(11),   // dissipates quickly
  TM_EXTINGUISHES_FIRE = Fl(12),        // extinguishes burning terrain or creatures
  TM_VANISHES_UPON_PROMOTION = Fl(13),  // vanishes when creating promotion dungeon feature, even if the replacement
                                        // terrain priority doesn't require it
  TM_REFLECTS_BOLTS = Fl(14),   // magic bolts reflect off of its surface randomly (similar to pmap flag IMPREGNABLE)
  TM_STAND_IN_TILE = Fl(15),    // earthbound creatures will be said to stand "in" the tile, not on it
  TM_LIST_IN_SIDEBAR = Fl(16),  // terrain will be listed in the sidebar with a description of the terrain type
  TM_VISUALLY_DISTINCT =
      Fl(17),  // terrain will be color-adjusted if necessary so the character stands out from the background
  TM_BRIGHT_MEMORY = Fl(18),      // no blue fade when this tile is out of sight
  TM_EXPLOSIVE_PROMOTE = Fl(19),  // when burned, will promote to promoteType instead of burningType if surrounded by
                                  // tiles with T_IS_FIRE or TM_EXPLOSIVE_PROMOTE
  TM_CONNECTS_LEVEL = Fl(20),     // will be treated as passable for purposes of calculating level connectedness,
                                  // irrespective of other aspects of this terrain layer
  TM_INTERRUPT_EXPLORATION_WHEN_SEEN =
      Fl(21),  // will generate a message when discovered during exploration to interrupt exploration
  TM_INVERT_WHEN_HIGHLIGHTED = Fl(22),   // will flip fore and back colors when highlighted with pathing
  TM_SWAP_ENCHANTS_ACTIVATION = Fl(23),  // in machine, swap item enchantments when two suitable items are on this
                                         // terrain, and activate the machine when that happens
};

enum StatusEffects
{
  STATUS_DONNING = 0,
  STATUS_WEAKENED,
  STATUS_TELEPATHIC,
  STATUS_HALLUCINATING,
  STATUS_LEVITATING,
  STATUS_SLOWED,
  STATUS_HASTED,
  STATUS_CONFUSED,
  STATUS_BURNING,
  STATUS_PARALYZED,
  STATUS_POISONED,
  STATUS_STUCK,
  STATUS_NAUSEOUS,
  STATUS_DISCORDANT,
  STATUS_IMMUNE_TO_FIRE,
  STATUS_EXPLOSION_IMMUNITY,
  STATUS_NUTRITION,
  STATUS_ENTERS_LEVEL_IN,
  STATUS_MAGICAL_FEAR,
  STATUS_ENTRANCED,
  STATUS_DARKNESS,
  STATUS_LIFESPAN_REMAINING,
  STATUS_SHIELDED,
  STATUS_INVISIBLE,
  STATUS_AGGRAVATING,
  NUMBER_OF_STATUS_EFFECTS,
};

enum CreatureModes
{
  MODE_NORMAL,
  MODE_PERM_FLEEING
};

struct Mutation
{
  char title[100];
  const Color* textColor;
  int healthFactor;
  int moveSpeedFactor;
  int attackSpeedFactor;
  int defenseFactor;
  int damageFactor;
  int DFChance;
  enum DungeonFeatureTypes DFType;
  enum LightType light;
  unsigned long monsterFlags;
  unsigned long monsterAbilityFlags;
  unsigned long forbiddenFlags;
  unsigned long forbiddenAbilityFlags;
  char description[1000];
};

struct HordeType
{
  enum MonsterTypes leaderType;

  // membership information
  int numberOfMemberTypes;
  enum MonsterTypes memberType[5];
  RandomRange memberCount[5];

  // spawning information
  int minLevel;
  int maxLevel;
  int frequency;
  enum TileType spawnsIn;
  int machine;

  enum HordeFlags flags;
};

struct MonsterClass
{
  char name[30];
  int frequency;
  int maxDepth;
  enum MonsterTypes memberList[15];
};

struct Creature
{
  CreatureType info;
  int xLoc;
  int yLoc;
  int depth;
  int currentHP;
  long turnsUntilRegen;
  int regenPerTurn;                   // number of HP to regenerate every single turn
  int weaknessAmount;                 // number of points of weakness that are inflicted by the weakness status
  int poisonAmount;                   // number of points of damage per turn from poison
  enum CreatureStates creatureState;  // current behavioral state
  enum CreatureModes creatureMode;    // current behavioral mode (higher-level than state)

  int mutationIndex;  // what mutation the monster has (or -1 for none)

  // Waypoints:
  int targetWaypointIndex;                          // the index number of the waypoint we're pathing toward
  bool waypointAlreadyVisited[MAX_WAYPOINT_COUNT];  // checklist of waypoints
  int lastSeenPlayerAt[2];                          // last location at which the monster hunted the player

  int targetCorpseLoc[2];         // location of the corpse that the monster is approaching to gain its abilities
  char targetCorpseName[30];      // name of the deceased monster that we're approaching to gain its abilities
  unsigned long absorptionFlags;  // ability/behavior flags that the monster will gain when absorption is complete
  bool absorbBehavior;            // above flag is behavior instead of ability (ignored if absorptionBolt is set)
  int absorptionBolt;             // bolt index that the monster will learn to cast when absorption is complete
  int corpseAbsorptionCounter;    // used to measure both the time until the monster stops being interested in the
                                  // corpse, and, later, the time until the monster finishes absorbing the corpse.
  int** mapToMe;                  // if a pack leader, this is a periodically updated pathing map to get to the leader
  int** safetyMap;     // fleeing monsters store their own safety map when out of player FOV to avoid omniscience
  int ticksUntilTurn;  // how long before the creature gets its next move

  // Locally cached statistics that may be temporarily modified:
  int movementSpeed;
  int attackSpeed;

  int turnsSpentStationary;  // how many (subjective) turns it's been since the creature moved between tiles
  int flashStrength;         // monster will flash soon; this indicates the percent strength of flash
  Color flashColor;          // the color that the monster will flash
  int status[NUMBER_OF_STATUS_EFFECTS];
  int maxStatus[NUMBER_OF_STATUS_EFFECTS];  // used to set the max point on the status bars
  unsigned long bookkeepingFlags;
  int spawnDepth;           // keep track of the depth of the machine to which they relate (for activation monsters)
  int machineHome;          // monsters that spawn in a machine keep track of the machine number here (for activation
                            // monsters)
  int xpxp;                 // exploration experience (used to time telepathic bonding for allies)
  int newPowerCount;        // how many more times this monster can absorb a fallen monster
  int totalPowerCount;      // how many times has the monster been empowered? Used to recover abilities when negated.
  struct Creature* leader;  // only if monster is a follower
  struct Creature* carriedMonster;  // when vampires turn into bats, one of the bats restores the vampire when it dies
  struct Creature* nextCreature;
  struct Item* carriedItem;  // only used for monsters
};

enum NGCommands
{
  NG_NOTHING = 0,
  NG_NEW_GAME,
  NG_NEW_GAME_WITH_SEED,
  NG_OPEN_GAME,
  NG_VIEW_RECORDING,
  NG_HIGH_SCORES,
  NG_SCUM,
  NG_QUIT,
};

enum FeatureTypes
{
  FEAT_PURE_MAGE = 0,
  FEAT_PURE_WARRIOR,
  FEAT_PACIFIST,
  FEAT_ARCHIVIST,
  FEAT_COMPANION,
  FEAT_SPECIALIST,
  FEAT_JELLYMANCER,
  FEAT_INDOMITABLE,
  FEAT_MYSTIC,
  FEAT_DRAGONSLAYER,
  FEAT_PALADIN,

  FEAT_COUNT,
};

// these are basically global variables pertaining to the game state and player's unique variables:
struct PlayerCharacter
{
  int depthLevel;  // which dungeon level are we on
  int deepestLevel;
  bool disturbed;                        // player should stop auto-acting
  bool gameHasEnded;                     // stop everything and go to death screen
  bool highScoreSaved;                   // so that it saves the high score only once
  bool blockCombatText;                  // busy auto-fighting
  bool autoPlayingLevel;                 // seriously, don't interrupt
  bool automationActive;                 // cut some corners during redraws to speed things up
  bool justRested;                       // previous turn was a rest -- used in stealth
  bool cautiousMode;                     // used to prevent careless deaths caused by holding down a key
  bool receivedLevitationWarning;        // only warn you once when you're hovering dangerously over liquid
  bool updatedSafetyMapThisTurn;         // so it's updated no more than once per turn
  bool updatedAllySafetyMapThisTurn;     // so it's updated no more than once per turn
  bool updatedMapToSafeTerrainThisTurn;  // so it's updated no more than once per turn
  bool updatedMapToShoreThisTurn;        // so it's updated no more than once per turn
  bool easyMode;                         // enables easy mode
  bool inWater;                          // helps with the blue water filter effect
  bool heardCombatThisTurn;              // so you get only one "you hear combat in the distance" per turn
  bool creaturesWillFlashThisTurn;       // there are creatures out there that need to flash before the turn ends
  bool staleLoopMap;                     // recalculate the loop map at the end of the turn
  bool alreadyFell;                      // so the player can fall only one depth per turn
  bool eligibleToUseStairs;              // so the player uses stairs only when he steps onto them
  bool trueColorMode;                    // whether lighting effects are disabled
  bool displayAggroRangeMode;            // whether your stealth range is displayed
  bool quit;                             // to skip the typical end-game theatrics when the player quits
  unsigned long seed;                    // the master seed for generating the entire dungeon
  int RNG;                               // which RNG are we currently using?
  unsigned long gold;                    // how much gold we have
  unsigned long goldGenerated;  // how much gold has been generated on the levels, not counting gold held by monsters
  int strength;
  unsigned int monsterSpawnFuse;  // how much longer till a random monster spawns

  Item* weapon;
  Item* armor;
  Item* ringLeft;
  Item* ringRight;

  Flare** flares;
  int flareCount;
  int flareCapacity;

  Creature* yendorWarden;

  LightSource minersLight;
  float minersLightRadius;
  int ticksTillUpdateEnvironment;    // so that some periodic things happen in objective time
  unsigned int scentTurnNumber;      // helps make scent-casting work
  unsigned long playerTurnNumber;    // number of input turns in recording. Does not increment during paralysis.
  unsigned long absoluteTurnNumber;  // number of turns since the beginning of time. Always increments.
  signed long milliseconds;          // milliseconds since launch, to decide whether to engage cautious mode
  int xpxpThisTurn;                  // how many squares the player explored this turn
  int aggroRange;                    // distance from which monsters will notice you

  int previousHealthPercent;  // remembers what your health proportion was at the start of the turn,
  int previousPoisonPercent;  // and your poison proportion, to display percentage alerts for each

  int upLoc[2];    // upstairs location this level
  int downLoc[2];  // downstairs location this level

  int cursorLoc[2];                      // used for the return key functionality
  Creature* lastTarget;                  // to keep track of the last monster the player has thrown at or zapped
  int rewardRoomsGenerated;              // to meter the number of reward machines
  int machineNumber;                     // so each machine on a level gets a unique number
  int sidebarLocationList[ROWS * 2][2];  // to keep track of which location each line of the sidebar references

  // maps
  int** mapToShore;        // how many steps to get back to shore
  int** mapToSafeTerrain;  // so monsters can get to safety

  // recording info
  bool playbackMode;                // whether we're viewing a recording instead of playing
  unsigned long currentTurnNumber;  // how many turns have elapsed
  unsigned long howManyTurns;       // how many turns are in this recording
  int howManyDepthChanges;          // how many times the player changes depths
  int playbackDelayPerTurn;         // base playback speed; modified per turn by events
  int playbackDelayThisTurn;        // playback speed as modified
  bool playbackPaused;
  bool playbackFastForward;                // for loading saved games and such -- disables drawing and prevents pauses
  bool playbackOOS;                        // playback out of sync -- no unpausing allowed
  bool playbackOmniscience;                // whether to reveal all the map during playback
  bool playbackBetweenTurns;               // i.e. waiting for a top-level input -- iff, permit playback commands
  unsigned long nextAnnotationTurn;        // the turn number during which to display the next annotation
  char nextAnnotation[5000];               // the next annotation
  unsigned long locationInAnnotationFile;  // how far we've read in the annotations file

  // metered items
  long foodSpawned;  // amount of nutrition units spawned so far this game
  int lifePotionFrequency;
  int lifePotionsSpawned;
  int strengthPotionFrequency;
  int enchantScrollFrequency;

  // ring bonuses:
  int clairvoyance;
  int stealthBonus;
  int regenerationBonus;
  int lightMultiplier;
  int awarenessBonus;
  int transference;
  int wisdomBonus;
  int reaping;

  // feats:
  bool featRecord[FEAT_COUNT];

  // waypoints:
  int** wpDistance[MAX_WAYPOINT_COUNT];
  int wpCount;
  int wpCoordinates[MAX_WAYPOINT_COUNT][2];
  int wpRefreshTicker;

  // cursor trail:
  int cursorPathIntensity;
  bool cursorMode;

  // What do you want to do, player -- play, play with seed, resume, recording, high scores or quit?
  enum NGCommands nextGame;
  char nextGamePath[BROGUE_FILENAME_MAX];
  unsigned long nextGameSeed;
};

// Stores the necessary info about a level so it can be regenerated:
struct LevelData
{
  bool visited;
  pcell mapStorage[DCOLS][DROWS];
  struct Item* items;
  struct Creature* monsters;
  struct Creature* dormantMonsters;
  int** scentMap;
  unsigned long levelSeed;
  int upStairsLoc[2];
  int downStairsLoc[2];
  int playerExitedVia[2];
  unsigned long awaySince;
};

enum MachineFeatureFlags
{
  MF_GENERATE_ITEM = Fl(0),  // feature entails generating an item (overridden if the machine is adopting an item)
  MF_OUTSOURCE_ITEM_TO_MACHINE = Fl(1),  // item must be adopted by another machine
  MF_BUILD_VESTIBULE = Fl(2),  // call this at the origin of a door room to create a new door guard machine there
  MF_ADOPT_ITEM = Fl(3),  // this feature will take the adopted item (be it from another machine or a previous feature)
  MF_NO_THROWING_WEAPONS = Fl(4),  // the generated item cannot be a throwing weapon
  MF_GENERATE_HORDE = Fl(5),       // generate a monster horde that has all of the horde flags
  MF_BUILD_AT_ORIGIN = Fl(6),      // generate this feature at the room entrance
  // unused                       = Fl(7),	//
  MF_PERMIT_BLOCKING = Fl(8),  // permit the feature to block the map's passability (e.g. to add a locked door)
  MF_TREAT_AS_BLOCKING =
      Fl(9),  // treat this terrain as though it blocks, for purposes of deciding whether it can be placed there
  MF_NEAR_ORIGIN = Fl(10),        // feature must spawn in the rough quarter of tiles closest to the origin
  MF_FAR_FROM_ORIGIN = Fl(11),    // feature must spawn in the rough quarter of tiles farthest from the origin
  MF_MONSTER_TAKE_ITEM = Fl(12),  // the item associated with this feature (including if adopted) will be in possession
                                  // of the horde leader that's generated
  MF_MONSTER_SLEEPING = Fl(13),   // the monsters should be asleep when generated
  MF_MONSTER_FLEEING = Fl(14),    // the monsters should be permanently fleeing when generated
  MF_EVERYWHERE = Fl(15),         // generate the feature on every tile of the machine (e.g. carpeting)
  MF_ALTERNATIVE = Fl(16),        // build only one feature that has this flag per machine; the rest are skipped
  MF_ALTERNATIVE_2 =
      Fl(17),  // same as MF_ALTERNATIVE, but provides for a second set of alternatives of which only one will be chosen
  MF_REQUIRE_GOOD_RUNIC = Fl(18),  // generated item must be uncursed runic
  MF_MONSTERS_DORMANT = Fl(19),    // monsters are dormant, and appear when a dungeon feature with
                                   // DFF_ACTIVATE_DORMANT_MONSTER spawns on their tile
  // unused                       = Fl(20),	//
  MF_BUILD_IN_WALLS = Fl(21),            // build in an impassable tile that is adjacent to the interior
  MF_BUILD_ANYWHERE_ON_LEVEL = Fl(22),   // build anywhere on the level that is not inside the machine
  MF_REPEAT_UNTIL_NO_PROGRESS = Fl(23),  // keep trying to build this feature set until no changes are made
  MF_IMPREGNABLE = Fl(24),               // this feature's location will be immune to tunneling
  MF_IN_VIEW_OF_ORIGIN = Fl(25),         // this feature must be in view of the origin
  MF_IN_PASSABLE_VIEW_OF_ORIGIN =
      Fl(26),  // this feature must be in view of the origin, where "view" is blocked by pathing blockers
  MF_NOT_IN_HALLWAY = Fl(27),          // the feature location must have a passableArcCount of <= 1
  MF_NOT_ON_LEVEL_PERIMETER = Fl(28),  // don't build it in the outermost walls of the level
  MF_SKELETON_KEY =
      Fl(29),  // if a key is generated or adopted by this feature, it will open all locks in this machine.
  MF_KEY_DISPOSABLE =
      Fl(30),  // if a key is generated or adopted, it will self-destruct after being used at this current location.
};

struct MachineFeature
{
  // terrain
  enum DungeonFeatureTypes featureDF;  // generate this DF at the feature location (0 for none)
  enum TileType terrain;               // generate this terrain tile at the feature location (0 for none)
  enum dungeonLayers layer;            // generate the terrain tile in this layer

  int instanceCountRange[2];  // generate this range of instances of this feature
  int minimumInstanceCount;   // abort if fewer than this

  // items: these will be ignored if the feature is adopting an item
  int itemCategory;  // generate this category of item (or -1 for random)
  int itemKind;      // generate this kind of item (or -1 for random)

  int monsterID;  // generate a monster of this kind if MF_GENERATE_MONSTER is set

  int personalSpace;         // subsequent features must be generated more than this many tiles away from this feature
  unsigned long hordeFlags;  // choose a monster horde based on this
  unsigned long itemFlags;   // assign these flags to the item
  unsigned long flags;       // feature flags
};

enum BlueprintFlags
{
  BP_ADOPT_ITEM = Fl(0),  // the machine must adopt an item (e.g. a door key)
  BP_VESTIBULE = Fl(1),   // spawns in a doorway (location must be given) and expands outward, to guard the room
  BP_PURGE_PATHING_BLOCKERS = Fl(2),  // clean out traps and other T_PATHING_BLOCKERs
  BP_PURGE_INTERIOR = Fl(3),          // clean out all of the terrain in the interior before generating the machine
  BP_PURGE_LIQUIDS = Fl(4),           // clean out all of the liquids in the interior before generating the machine
  BP_SURROUND_WITH_WALLS =
      Fl(5),  // fill in any impassable gaps in the perimeter (e.g. water, lava, brimstone, traps) with wall
  BP_IMPREGNABLE =
      Fl(6),          // impassable perimeter and interior tiles are locked; tunneling bolts will bounce off harmlessly
  BP_REWARD = Fl(7),  // metered reward machines
  BP_OPEN_INTERIOR =
      Fl(8),  // clear out walls in the interior, widen the interior until convex or bumps into surrounding areas
  BP_MAXIMIZE_INTERIOR = Fl(9),  // same as BP_OPEN_INTERIOR but expands the room as far as it can go, potentially
                                 // surrounding the whole level.
  BP_ROOM = Fl(10),  // spawns in a dead-end room that is dominated by a chokepoint of the given size (as opposed to a
                     // random place of the given size)
  BP_TREAT_AS_BLOCKING =
      Fl(11),  // abort the machine if, were it filled with wall tiles, it would disrupt the level connectivity
  BP_REQUIRE_BLOCKING =
      Fl(12),  // abort the machine unless, were it filled with wall tiles, it would disrupt the level connectivity
  BP_NO_INTERIOR_FLAG = Fl(13),  // don't flag the area as being part of a machine
  BP_REDESIGN_INTERIOR =
      Fl(14),  // nuke and pave -- delete all terrain in the interior and build entirely new rooms within the bounds
};

typedef struct blueprint
{
  int depthRange[2];           // machine must be built between these dungeon depths
  int roomSize[2];             // machine must be generated in a room of this size
  int frequency;               // frequency (number of tickets this blueprint enters in the blueprint selection raffle)
  int featureCount;            // how many different types of features follow (max of 20)
  int dungeonProfileType;      // if BP_REDESIGN_INTERIOR is set, which dungeon profile do we use?
  unsigned long flags;         // blueprint flags
  MachineFeature feature[20];  // the features themselves
} blueprint;

enum machineTypes
{
  // Reward rooms:
  MT_REWARD_MULTI_LIBRARY = 1,
  MT_REWARD_MONO_LIBRARY,
  MT_REWARD_CONSUMABLES,
  MT_REWARD_PEDESTALS_PERMANENT,
  MT_REWARD_PEDESTALS_CONSUMABLE,
  MT_REWARD_COMMUTATION_ALTARS,
  MT_REWARD_RESURRECTION_ALTAR,
  MT_REWARD_ADOPTED_ITEM,
  MT_REWARD_DUNGEON,
  MT_REWARD_KENNEL,
  MT_REWARD_VAMPIRE_LAIR,
  MT_REWARD_ASTRAL_PORTAL,
  MT_REWARD_GOBLIN_WARREN,
  MT_REWARD_SENTINEL_SANCTUARY,

  // Amulet holder:
  MT_AMULET_AREA,

  // Door guard machines:
  MT_LOCKED_DOOR_VESTIBULE,
  MT_SECRET_DOOR_VESTIBULE,
  MT_SECRET_LEVER_VESTIBULE,
  MT_FLAMMABLE_BARRICADE_VESTIBULE,
  MT_STATUE_SHATTERING_VESTIBULE,
  MT_STATUE_MONSTER_VESTIBULE,
  MT_THROWING_TUTORIAL_VESTIBULE,
  MT_PIT_TRAPS_VESTIBULE,
  MT_BECKONING_OBSTACLE_VESTIBULE,
  MT_GUARDIAN_VESTIBULE,

  // Key guard machines:
  MT_KEY_REWARD_LIBRARY,
  MT_KEY_SECRET_ROOM,
  MT_KEY_THROWING_TUTORIAL_AREA,
  MT_KEY_RAT_TRAP_ROOM,
  MT_KEY_FIRE_TRANSPORTATION_ROOM,
  MT_KEY_FLOOD_TRAP_ROOM,
  MT_KEY_FIRE_TRAP_ROOM,
  MT_KEY_THIEF_AREA,
  MT_KEY_COLLAPSING_FLOOR_AREA,
  MT_KEY_PIT_TRAP_ROOM,
  MT_KEY_LEVITATION_ROOM,
  MT_KEY_WEB_CLIMBING_ROOM,
  MT_KEY_LAVA_MOAT_ROOM,
  MT_KEY_LAVA_MOAT_AREA,
  MT_KEY_POISON_GAS_TRAP_ROOM,
  MT_KEY_EXPLOSIVE_TRAP_ROOM,
  MT_KEY_BURNING_TRAP_ROOM,
  MT_KEY_STATUARY_TRAP_AREA,
  MT_KEY_GUARDIAN_WATER_PUZZLE_ROOM,
  MT_KEY_GUARDIAN_GAUNTLET_ROOM,
  MT_KEY_GUARDIAN_CORRIDOR_ROOM,
  MT_KEY_SUMMONING_CIRCLE_ROOM,
  MT_KEY_BECKONING_OBSTACLE_ROOM,
  MT_KEY_WORM_TRAP_AREA,
  MT_KEY_MUD_TRAP_ROOM,
  MT_KEY_ELECTRIC_CRYSTALS_ROOM,
  MT_KEY_ZOMBIE_TRAP_ROOM,
  MT_KEY_PHANTOM_TRAP_ROOM,
  MT_KEY_WORM_TUNNEL_ROOM,
  MT_KEY_TURRET_TRAP_ROOM,
  MT_KEY_BOSS_ROOM,

  // Thematic machines:
  MT_BLOODFLOWER_AREA,
  MT_SHRINE_AREA,
  MT_IDYLL_AREA,
  MT_SWAMP_AREA,
  MT_CAMP_AREA,
  MT_REMNANT_AREA,
  MT_DISMAL_AREA,
  MT_BRIDGE_TURRET_AREA,
  MT_LAKE_PATH_TURRET_AREA,
  MT_PARALYSIS_TRAP_AREA,
  MT_PARALYSIS_TRAP_HIDDEN_AREA,
  MT_TRICK_STATUE_AREA,
  MT_WORM_AREA,
  MT_SENTINEL_AREA,

  NUMBER_BLUEPRINTS,
};

struct AutoGenerator
{
  // What spawns:
  enum TileType terrain;
  enum dungeonLayers layer;

  enum DungeonFeatureTypes DFType;

  enum machineTypes machine;  // Machine placement also respects BP_ placement flags in the machine blueprint

  // Parameters governing when and where it spawns:
  enum TileType requiredDungeonFoundationType;
  enum TileType requiredLiquidFoundationType;
  int minDepth;
  int maxDepth;
  int frequency;
  int minNumberIntercept;  // actually intercept * 100
  int minNumberSlope;      // actually slope * 100
  int maxNumber;
};

#define NUMBER_AUTOGENERATORS 49

struct Feature
{
  char name[100];
  char description[200];
  bool initialValue;
};

#define PDS_FORBIDDEN -1
#define PDS_OBSTRUCTION -2
#define PDS_CELL(map, x, y) ((map)->links + ((x) + DCOLS * (y)))

typedef struct pdsLink pdsLink;
typedef struct pdsMap pdsMap;

typedef struct BrogueButton
{
  char text[COLS * 3];  // button label; can include color escapes
  int x;                // button's leftmost cell will be drawn at (x, y)
  int y;
  signed long hotkey[10];  // up to 10 hotkeys to trigger the button
  Color buttonColor;       // background of the button; further gradient-ized when displayed
  int opacity;             // further reduced by 50% if not enabled
  uchar symbol[COLS];      // Automatically replace the nth asterisk in the button label text with
                           // the nth character supplied here, if one is given.
                           // (Primarily to display magic character and item symbols in the inventory display.)
  unsigned long flags;
} BrogueButton;

enum ButtonDrawStates
{
  BUTTON_NORMAL = 0,
  BUTTON_HOVER,
  BUTTON_PRESSED,
};

enum BUTTON_FLAGS
{
  B_DRAW = Fl(0),
  B_ENABLED = Fl(1),
  B_GRADIENT = Fl(2),
  B_HOVER_ENABLED = Fl(3),
  B_WIDE_CLICK_AREA = Fl(4),
  B_KEYPRESS_HIGHLIGHT = Fl(5),
};

struct ButtonState
{
  // Indices of the buttons that are doing stuff:
  int buttonFocused;
  int buttonDepressed;

  // Index of the selected button:
  int buttonChosen;

  // The buttons themselves:
  int buttonCount;
  BrogueButton buttons[50];

  // The window location, to determine whether a click is a cancelation:
  int winX;
  int winY;
  int winWidth;
  int winHeight;

  // Graphical buffers:
  cellDisplayBuffer dbuf[COLS][ROWS];  // Where buttons are drawn.
  cellDisplayBuffer rbuf[COLS][ROWS];  // Reversion screen state.
};

#if defined __cplusplus
extern "C"
{
#endif

  void rogueMain();
  void executeEvent(RogueEvent* theEvent);
  bool fileExists(const char* pathname);
  bool chooseFile(char* path, char* prompt, char* defaultName, char* suffix);
  bool openFile(const char* path);
  void initializeRogue(unsigned long seed);
  void gameOver(char* killedBy, bool useCustomPhrasing);
  void victory(bool superVictory);
  void enableEasyMode();
  int rand_range(int lowerBound, int upperBound);
  unsigned long seedRandomGenerator(unsigned long seed);
  int randClumpedRange(int lowerBound, int upperBound, int clumpFactor);
  int randClump(RandomRange theRange);
  bool rand_percent(int percent);
  void shuffleList(int* list, int listLength);
  void fillSequentialList(int* list, int listLength);
  int unflag(unsigned long flag);
  void considerCautiousMode();
  void refreshScreen();
  void displayLevel();
  void storeColorComponents(char components[3], const Color* theColor);
  bool separateColors(Color* fore, Color* back);
  void bakeColor(Color* theColor);
  void shuffleTerrainColors(int percentOfCells, bool refreshCells);
  void normColor(Color* baseColor, const int aggregateMultiplier, const int colorTranslation);
  void getCellAppearance(int x, int y, uchar* returnChar, Color* returnForeColor, Color* returnBackColor);
  void logBuffer(char array[DCOLS][DROWS]);
  // void logBuffer(int **array);
  bool search(int searchStrength);
  bool proposeOrConfirmLocation(int x, int y, char* failureMessage);
  bool useStairs(int stairDirection);
  int passableArcCount(int x, int y);
  void analyzeMap(bool calculateChokeMap);
  bool buildAMachine(enum machineTypes bp, int originX, int originY, unsigned long requiredMachineFlags,
                     Item* adoptiveItem, Item* parentSpawnedItems[50], Creature* parentSpawnedMonsters[50]);
  void attachRooms(int** grid, const DungeonProfile* theDP, int attempts, int maxRoomCount);
  void digDungeon();
  void updateMapToShore();
  int levelIsDisconnectedWithBlockingMap(char blockingMap[DCOLS][DROWS], bool countRegionSize);
  void resetDFMessageEligibility();
  bool fillSpawnMap(enum dungeonLayers layer, enum TileType surfaceTileType, char spawnMap[DCOLS][DROWS],
                    bool blockedByOtherLayers, bool refresh, bool superpriority);
  bool spawnDungeonFeature(int x, int y, DungeonFeature* Feature, bool refreshCell, bool abortIfBlocking);
  void restoreMonster(Creature* monst, int** mapToStairs, int** mapToPit);
  void restoreItem(Item* theItem);
  void refreshWaypoint(int wpIndex);
  void setUpWaypoints();
  void zeroOutGrid(char grid[DCOLS][DROWS]);
  int oppositeDirection(int theDir);

  void plotChar(uchar inputChar, int xLoc, int yLoc, int backRed, int backGreen, int backBlue, int foreRed,
                int foreGreen, int foreBlue);
  void pausingTimerStartsNow();
  bool pauseForMilliseconds(int milliseconds);
  void nextKeyOrMouseEvent(RogueEvent* returnEvent, bool textInput, bool colorsDance);
  bool controlKeyIsDown();
  bool shiftKeyIsDown();
  int getHighScoresList(RogueHighScoresEntry returnList[HIGH_SCORES_COUNT]);
  bool saveHighScore(RogueHighScoresEntry theEntry);
  void initializeBrogueSaveLocation();
  fileEntry* listFiles(int* fileCount, char** dynamicMemoryBuffer);
  void initializeLaunchArguments(enum NGCommands* command, char* path, unsigned long* seed);

  char nextKeyPress(bool textInput);
  void refreshSideBar(int focusX, int focusY, bool focusedEntityMustGoFirst);
  void printHelpScreen();
  void printDiscoveriesScreen();
  void printHighScores(bool hiliteMostRecent);
  void displayGrid(int** map);
  void printSeed();
  void printProgressBar(int x, int y, const char barLabel[COLS], long amtFilled, long amtMax, Color* fillColor,
                        bool dim);
  int printMonsterInfo(Creature* monst, int y, bool dim, bool highlight);
  void describeHallucinatedItem(char* buf);
  int printItemInfo(Item* theItem, int y, bool dim, bool highlight);
  int printTerrainInfo(int x, int y, int py, const char* description, bool dim, bool highlight);
  void rectangularShading(int x, int y, int width, int height, const Color* backColor, int opacity,
                          cellDisplayBuffer dbuf[COLS][ROWS]);
  int printTextBox(char* textBuf, int x, int y, int width, Color* foreColor, Color* backColor,
                   cellDisplayBuffer rbuf[COLS][ROWS], BrogueButton* buttons, int buttonCount);
  void printMonsterDetails(Creature* monst, cellDisplayBuffer rbuf[COLS][ROWS]);
  void printFloorItemDetails(Item* theItem, cellDisplayBuffer rbuf[COLS][ROWS]);
  unsigned long printCarriedItemDetails(Item* theItem, int x, int y, int width, bool includeButtons,
                                        cellDisplayBuffer rbuf[COLS][ROWS]);
  void funkyFade(cellDisplayBuffer displayBuf[COLS][ROWS], const Color* colorStart, const Color* colorEnd,
                 int stepCount, int x, int y, bool invert);
  void displayCenteredAlert(char* message);
  void flashMessage(char* message, int x, int y, int time, Color* fColor, Color* bColor);
  void flashTemporaryAlert(char* message, int time);
  void waitForAcknowledgment();
  void waitForKeystrokeOrMouseClick();
  bool confirm(char* prompt, bool alsoDuringPlayback);
  void refreshDungeonCell(int x, int y);
  void applyColorMultiplier(Color* baseColor, const Color* multiplierColor);
  void applyColorAverage(Color* baseColor, const Color* newColor, int averageWeight);
  void applyColorAugment(Color* baseColor, const Color* augmentingColor, int augmentWeight);
  void applyColorScalar(Color* baseColor, int scalar);
  void applyColorBounds(Color* baseColor, int lowerBound, int upperBound);
  void desaturate(Color* baseColor, int weight);
  void randomizeColor(Color* baseColor, int randomizePercent);
  void swapColors(Color* color1, Color* color2);
  void irisFadeBetweenBuffers(cellDisplayBuffer fromBuf[COLS][ROWS], cellDisplayBuffer toBuf[COLS][ROWS], int x, int y,
                              int frameCount, bool outsideIn);
  void colorBlendCell(int x, int y, Color* hiliteColor, int hiliteStrength);
  void hiliteCell(int x, int y, const Color* hiliteColor, int hiliteStrength, bool distinctColors);
  void colorMultiplierFromDungeonLight(int x, int y, Color* editColor);
  void plotCharWithColor(uchar inputChar, int xLoc, int yLoc, const Color* cellForeColor, const Color* cellBackColor);
  void plotCharToBuffer(uchar inputChar, int x, int y, Color* foreColor, Color* backColor,
                        cellDisplayBuffer dbuf[COLS][ROWS]);
  void commitDraws();
  void dumpLevelToScreen();
  void hiliteCharGrid(char hiliteCharGrid[DCOLS][DROWS], Color* hiliteColor, int hiliteStrength);
  void blackOutScreen();
  void colorOverDungeon(const Color* Color);
  void copyDisplayBuffer(cellDisplayBuffer toBuf[COLS][ROWS], cellDisplayBuffer fromBuf[COLS][ROWS]);
  void clearDisplayBuffer(cellDisplayBuffer dbuf[COLS][ROWS]);
  Color colorFromComponents(char rgb[3]);
  void overlayDisplayBuffer(cellDisplayBuffer overBuf[COLS][ROWS], cellDisplayBuffer previousBuf[COLS][ROWS]);
  void flashForeground(int* x, int* y, Color** flashColor, int* flashStrength, int count, int frames);
  void flash(Color* theColor, int frames, int x, int y);
  void colorFlash(const Color* theColor, unsigned long reqTerrainFlags, unsigned long reqTileFlags, int frames,
                  int maxRadius, int x, int y);
  void printString(const char* theString, int x, int y, Color* foreColor, Color* backColor,
                   cellDisplayBuffer dbuf[COLS][ROWS]);
  int wrapText(char* to, const char* sourceText, int width);
  int printStringWithWrapping(char* theString, int x, int y, int width, Color* foreColor, Color* backColor,
                              cellDisplayBuffer dbuf[COLS][ROWS]);
  bool getInputTextString(char* inputText, const char* prompt, int maxLength, const char* defaultEntry,
                          const char* promptSuffix, int textEntryType, bool useDialogBox);
  void displayChokeMap();
  void displayLoops();
  bool pauseBrogue(int milliseconds);
  void nextBrogueEvent(RogueEvent* returnEvent, bool textInput, bool colorsDance, bool realInputEvenInPlayback);
  void executeMouseClick(RogueEvent* theEvent);
  void executeKeystroke(signed long keystroke, bool controlKey, bool shiftKey);
  void initializeLevel();
  void startLevel(int oldLevelNumber, int stairDirection);
  void updateMinersLightRadius();
  void freeCreature(Creature* monst);
  void emptyGraveyard();
  void freeEverything();
  bool randomMatchingLocation(int* x, int* y, int dungeonType, int liquidType, int terrainType);
  enum dungeonLayers highestPriorityLayer(int x, int y, bool skipGas);
  enum dungeonLayers layerWithTMFlag(int x, int y, unsigned long flag);
  enum dungeonLayers layerWithFlag(int x, int y, unsigned long flag);
  char* tileFlavor(int x, int y);
  char* tileText(int x, int y);
  void describedItemBasedOnParameters(int theCategory, int theKind, int theQuantity, char* buf);
  void describeLocation(char buf[DCOLS], int x, int y);
  void printLocationDescription(int x, int y);
  void useKeyAt(Item* theItem, int x, int y);
  void playerRuns(int direction);
  void exposeCreatureToFire(Creature* monst);
  void updateFlavorText();
  void updatePlayerUnderwaterness();
  bool monsterShouldFall(Creature* monst);
  void applyInstantTileEffectsToCreature(Creature* monst);
  void vomit(Creature* monst);
  void becomeAllyWith(Creature* monst);
  void freeCaptive(Creature* monst);
  bool freeCaptivesEmbeddedAt(int x, int y);
  bool handleWhipAttacks(Creature* attacker, enum Directions dir, bool* aborted);
  bool diagonalBlocked(const int x1, const int y1, const int x2, const int y2, const bool limitToPlayerKnowledge);
  bool playerMoves(int direction);
  void calculateDistances(int** distanceMap, int destinationX, int destinationY, unsigned long blockingTerrainFlags,
                          Creature* traveler, bool canUseSecretDoors, bool eightWays);
  int pathingDistance(int x1, int y1, int x2, int y2, unsigned long blockingTerrainFlags);
  int nextStep(int** distanceMap, int x, int y, Creature* monst, bool reverseDirections);
  void travelRoute(int path[1000][2], int steps);
  void travel(int x, int y, bool autoConfirm);
  void populateGenericCostMap(int** costMap);
  void getLocationFlags(const int x, const int y, unsigned long* tFlags, unsigned long* TMFlags,
                        unsigned long* cellFlags, const bool limitToPlayerKnowledge);
  void populateCreatureCostMap(int** costMap, Creature* monst);
  enum Directions adjacentFightingDir();
  void getExploreMap(int** map, bool headingToStairs);
  bool explore(int frameDelay);
  int getPlayerPathOnMap(int path[1000][2], int** map, int originX, int originY);
  void reversePath(int path[1000][2], int steps);
  void hilitePath(int path[1000][2], int steps, bool unhilite);
  void clearCursorPath();
  void hideCursor();
  void showCursor();
  void mainInputLoop();
  bool isDisturbed(int x, int y);
  void discover(int x, int y);
  int randValidDirectionFrom(Creature* monst, int x, int y, bool respectAvoidancePreferences);
  bool exposeTileToElectricity(int x, int y);
  bool exposeTileToFire(int x, int y, bool alwaysIgnite);
  bool cellCanHoldGas(int x, int y);
  void monstersFall();
  void updateEnvironment();
  void updateAllySafetyMap();
  void updateSafetyMap();
  void updateSafeTerrainMap();
  int staffChargeDuration(const Item* theItem);
  void rechargeItemsIncrementally(int multiplier);
  void extinguishFireOnCreature(Creature* monst);
  void autoRest();
  bool startFighting(enum Directions dir, bool tillDeath);
  void autoFight(bool tillDeath);
  void synchronizePlayerTimeState();
  void playerRecoversFromAttacking(bool anAttackHit);
  void playerTurnEnded();
  void resetScentTurnNumber();
  void displayMonsterFlashes(bool flashingEnabled);
  void displayMessageArchive();
  void temporaryMessage(char* msg1, bool requireAcknowledgment);
  void messageWithColor(char* msg, Color* theColor, bool requireAcknowledgment);
  void flavorMessage(char* msg);
  void message(const char* msg, bool requireAcknowledgment);
  void displayMoreSignWithoutWaitingForAcknowledgment();
  void displayMoreSign();
  int encodeMessageColor(char* msg, int i, const Color* theColor);
  int decodeMessageColor(const char* msg, int i, Color* returnColor);
  Color* messageColorFromVictim(Creature* monst);
  void upperCase(char* theChar);
  void updateMessageDisplay();
  void deleteMessages();
  void confirmMessages();
  void stripShiftFromMovementKeystroke(signed long* keystroke);

  void storeMemories(const int x, const int y);
  void updateFieldOfViewDisplay(bool updateDancingTerrain, bool refreshDisplay);
  void updateFieldOfView(int xLoc, int yLoc, int radius, bool paintScent, bool passThroughCreatures,
                         bool setFieldOfView, int theColor[3], int fadeToPercent);
  void betweenOctant1andN(int* x, int* y, int x0, int y0, int n);

  void getFOVMask(char grid[DCOLS][DROWS], int xLoc, int yLoc, float maxRadius, unsigned long forbiddenTerrain,
                  unsigned long forbiddenFlags, bool cautiousOnWalls);
  void scanOctantFOV(char grid[DCOLS][DROWS], int xLoc, int yLoc, int octant, float maxRadius,
                     int columnsRightFromOrigin, long startSlope, long endSlope, unsigned long forbiddenTerrain,
                     unsigned long forbiddenFlags, bool cautiousOnWalls);

  Creature* generateMonster(int monsterID, bool itemPossible, bool mutationPossible);
  int chooseMonster(int forLevel);
  Creature* spawnHorde(int hordeID, int x, int y, unsigned long forbiddenFlags, unsigned long requiredFlags);
  void fadeInMonster(Creature* monst);
  bool removeMonsterFromChain(Creature* monst, Creature* theChain);
  bool monsterWillAttackTarget(const Creature* attacker, const Creature* defender);
  bool monstersAreTeammates(const Creature* monst1, const Creature* monst2);
  bool monstersAreEnemies(const Creature* monst1, const Creature* monst2);
  void initializeGender(Creature* monst);
  bool stringsMatch(const char* str1, const char* str2);
  void resolvePronounEscapes(char* text, Creature* monst);
  int pickHordeType(int depth, enum MonsterTypes summonerType, unsigned long forbiddenFlags,
                    unsigned long requiredFlags);
  Creature* cloneMonster(Creature* monst, bool announce, bool placeClone);
  void empowerMonster(Creature* monst);
  unsigned long forbiddenFlagsForMonster(CreatureType* monsterType);
  unsigned long avoidedFlagsForMonster(CreatureType* monsterType);
  bool monsterCanSubmergeNow(Creature* monst);
  void populateMonsters();
  void updateMonsterState(Creature* monst);
  void decrementMonsterStatus(Creature* monst);
  bool specifiedPathBetween(int x1, int y1, int x2, int y2, unsigned long blockingTerrain, unsigned long blockingFlags);
  bool traversiblePathBetween(Creature* monst, int x2, int y2);
  bool openPathBetween(int x1, int y1, int x2, int y2);
  Creature* monsterAtLoc(int x, int y);
  Creature* dormantMonsterAtLoc(int x, int y);
  void perimeterCoords(int returnCoords[2], int n);
  bool monsterBlinkToPreferenceMap(Creature* monst, int** preferenceMap, bool blinkUphill);
  bool monsterSummons(Creature* monst, bool alwaysUse);
  bool resurrectAlly(const int x, const int y);
  void unAlly(Creature* monst);
  bool monsterFleesFrom(Creature* monst, Creature* defender);
  void monstersTurn(Creature* monst);
  bool getRandomMonsterSpawnLocation(int* x, int* y);
  void spawnPeriodicHorde();
  void clearStatus(Creature* monst);
  void moralAttack(Creature* attacker, Creature* defender);
  int runicWeaponChance(Item* theItem, bool customEnchantLevel, float enchantLevel);
  void magicWeaponHit(Creature* defender, Item* theItem, bool backstabbed);
  void teleport(Creature* monst, int x, int y, bool respectTerrainAvoidancePreferences);
  void chooseNewWanderDestination(Creature* monst);
  bool canPass(Creature* mover, Creature* blocker);
  bool isPassableOrSecretDoor(int x, int y);
  bool knownToPlayerAsPassableOrSecretDoor(int x, int y);
  bool moveMonster(Creature* monst, int dx, int dy);
  unsigned long burnedTerrainFlagsAtLoc(int x, int y);
  unsigned long discoveredTerrainFlagsAtLoc(int x, int y);
  bool monsterAvoids(Creature* monst, int x, int y);
  int distanceBetween(int x1, int y1, int x2, int y2);
  void alertMonster(Creature* monst);
  void wakeUp(Creature* monst);
  bool monsterRevealed(Creature* monst);
  bool monsterHiddenBySubmersion(const Creature* monst, const Creature* observer);
  bool monsterIsHidden(const Creature* monst, const Creature* observer);
  bool canSeeMonster(Creature* monst);
  bool canDirectlySeeMonster(Creature* monst);
  void monsterName(char* buf, Creature* monst, bool includeArticle);
  bool monsterIsInClass(const Creature* monst, const int MonsterClass);
  float strengthModifier(Item* theItem);
  float netEnchant(Item* theItem);
  int hitProbability(Creature* attacker, Creature* defender);
  bool attackHit(Creature* attacker, Creature* defender);
  void applyArmorRunicEffect(char returnString[DCOLS], Creature* attacker, int* damage, bool melee);
  bool attack(Creature* attacker, Creature* defender, bool lungeAttack);
  void inflictLethalDamage(Creature* attacker, Creature* defender);
  bool inflictDamage(Creature* attacker, Creature* defender, int damage, const Color* flashColor,
                     bool ignoresProtectionShield);
  void addPoison(Creature* monst, int totalDamage, int concentrationIncrement);
  void killCreature(Creature* decedent, bool administrativeDeath);
  void buildHitList(Creature** hitList, const Creature* attacker, Creature* defender, const bool penetrate,
                    const bool sweep);
  void addScentToCell(int x, int y, int distance);
  void populateItems(int upstairsX, int upstairsY);
  Item* placeItem(Item* theItem, int x, int y);
  void removeItemFrom(int x, int y);
  void pickUpItemAt(int x, int y);
  Item* addItemToPack(Item* theItem);
  void aggravateMonsters(int distance, int x, int y, const Color* flashColor);
  int getLineCoordinates(int listOfCoordinates[][2], const int originLoc[2], const int targetLoc[2]);
  void getImpactLoc(int returnLoc[2], const int originLoc[2], const int targetLoc[2], const int maxDistance,
                    const bool returnLastEmptySpace);
  void negate(Creature* monst);
  int monsterAccuracyAdjusted(const Creature* monst);
  float monsterDamageAdjustmentAmount(const Creature* monst);
  int monsterDefenseAdjusted(const Creature* monst);
  void weaken(Creature* monst, int maxDuration);
  void slow(Creature* monst, int turns);
  void haste(Creature* monst, int turns);
  void heal(Creature* monst, int percent, bool panacea);
  bool projectileReflects(Creature* attacker, Creature* defender);
  int reflectBolt(int targetX, int targetY, int listOfCoordinates[][2], int kinkCell, bool retracePath);
  void checkForMissingKeys(int x, int y);
  enum BoltEffects boltEffectForItem(Item* theItem);
  enum BoltType boltForItem(Item* theItem);
  bool zap(int originLoc[2], int targetLoc[2], Bolt* theBolt, bool hideDetails);
  bool nextTargetAfter(int* returnX, int* returnY, int targetX, int targetY, bool targetEnemies, bool targetAllies,
                       bool targetItems, bool targetTerrain, bool requireOpenPath, bool reverseDirection);
  bool moveCursor(bool* targetConfirmed, bool* canceled, bool* tabKey, int targetLoc[2], RogueEvent* event,
                  ButtonState* state, bool colorsDance, bool keysMoveCursor, bool targetCanLeaveMap);
  void identifyItemKind(Item* theItem);
  void autoIdentify(Item* theItem);
  int numberOfItemsInPack();
  char nextAvailableInventoryCharacter();
  void checkForDisenchantment(Item* theItem);
  void updateFloorItems();
  void itemName(Item* theItem, char* root, bool includeDetails, bool includeArticle, Color* baseColor);
  char displayInventory(unsigned int categoryMask, unsigned long requiredFlags, unsigned long forbiddenFlags,
                        bool waitForAcknowledge, bool includeButtons);
  int numberOfMatchingPackItems(unsigned int categoryMask, unsigned long requiredFlags, unsigned long forbiddenFlags,
                                bool displayErrors);
  void clearInventory(char keystroke);
  Item* initializeItem();
  Item* generateItem(unsigned int theCategory, int theKind);
  int chooseKind(ItemTable* theTable, int numKinds);
  Item* makeItemInto(Item* theItem, ItemCategory ItemCategory, int itemKind);
  void updateEncumbrance();
  int displayedArmorValue();
  void strengthCheck(Item* theItem);
  void recalculateEquipmentBonuses();
  void equipItem(Item* theItem, bool force);
  void equip(Item* theItem);
  Item* keyInPackFor(int x, int y);
  Item* keyOnTileAt(int x, int y);
  void unequip(Item* theItem);
  void drop(Item* theItem);
  void findAlternativeHomeFor(Creature* monst, int* x, int* y, bool chooseRandomly);
  bool getQualifyingLocNear(int loc[2], int x, int y, bool hallwaysAllowed, char blockingMap[DCOLS][DROWS],
                            unsigned long forbiddenTerrainFlags, unsigned long forbiddenMapFlags, bool forbidLiquid,
                            bool deterministic);
  bool getQualifyingGridLocNear(int loc[2], int x, int y, bool grid[DCOLS][DROWS], bool deterministic);

  // Grid operations
  int** allocGrid();
  void freeGrid(int** array);
  void copyGrid(int** to, int** from);
  void fillGrid(int** grid, int fillValue);
  void hiliteGrid(int** grid, Color* hiliteColor, int hiliteStrength);
  void findReplaceGrid(int** grid, int findValueMin, int findValueMax, int fillValue);
  int floodFillGrid(int** grid, int x, int y, int eligibleValueMin, int eligibleValueMax, int fillValue);
  void drawRectangleOnGrid(int** grid, int x, int y, int width, int height, int value);
  void drawCircleOnGrid(int** grid, int x, int y, int radius, int value);
  void getTerrainGrid(int** grid, int value, unsigned long terrainFlags, unsigned long mapFlags);
  void getTMGrid(int** grid, int value, unsigned long TMflags);
  int validLocationCount(int** grid, int validValue);
  void randomLocationInGrid(int** grid, int* x, int* y, int validValue);
  bool getQualifyingPathLocNear(int* retValX, int* retValY, int x, int y, bool hallwaysAllowed,
                                unsigned long blockingTerrainFlags, unsigned long blockingMapFlags,
                                unsigned long forbiddenTerrainFlags, unsigned long forbiddenMapFlags,
                                bool deterministic);
  void createBlobOnGrid(int** grid, int* retMinX, int* retMinY, int* retWidth, int* retHeight, int roundCount,
                        int minBlobWidth, int minBlobHeight, int maxBlobWidth, int maxBlobHeight, int percentSeeded,
                        char birthParameters[9], char survivalParameters[9]);

  void checkForContinuedLeadership(Creature* monst);
  void demoteMonsterFromLeadership(Creature* monst);
  void toggleMonsterDormancy(Creature* monst);
  void monsterDetails(char buf[], Creature* monst);
  void makeMonsterDropItem(Creature* monst);
  void throwCommand(Item* theItem);
  void relabel(Item* theItem);
  void apply(Item* theItem, bool recordCommands);
  bool itemCanBeCalled(Item* theItem);
  void call(Item* theItem);
  int chooseVorpalEnemy();
  void describeMonsterClass(char* buf, const int classID, bool conjunctionAnd);
  void identify(Item* theItem);
  void updateIdentifiableItem(Item* theItem);
  void updateIdentifiableItems();
  void readScroll(Item* theItem);
  void updateRingBonuses();
  void updatePlayerRegenerationDelay();
  bool removeItemFromChain(Item* theItem, Item* theChain);
  void addItemToChain(Item* theItem, Item* theChain);
  void drinkPotion(Item* theItem);
  Item* promptForItemOfType(unsigned int category, unsigned long requiredFlags, unsigned long forbiddenFlags,
                            char* prompt, bool allowInventoryActions);
  Item* itemOfPackLetter(char letter);
  void unequipItem(Item* theItem, bool force);
  int magicCharDiscoverySuffix(int category, int kind);
  uchar itemMagicChar(Item* theItem);
  Item* itemAtLoc(int x, int y);
  Item* dropItem(Item* theItem);
  ItemTable* tableForItemCategory(enum ItemCategory theCat, int* kindCount);
  bool isVowelish(char* theChar);
  int charmEffectDuration(int CharmKind, int enchant);
  int charmRechargeDelay(int CharmKind, int enchant);
  bool itemIsCarried(Item* theItem);
  void itemDetails(char* buf, Item* theItem);
  void deleteItem(Item* theItem);
  void shuffleFlavors();
  unsigned long itemValue(Item* theItem);
  int strLenWithoutEscapes(const char* str);
  void combatMessage(char* theMsg, Color* theColor);
  void displayCombatText();
  void flashMonster(Creature* monst, const Color* theColor, int strength);

  bool paintLight(LightSource* theLight, int x, int y, bool isMinersLight, bool maintainShadows);
  void backUpLighting(int lights[DCOLS][DROWS][3]);
  void restoreLighting(int lights[DCOLS][DROWS][3]);
  void updateLighting();
  bool playerInDarkness();
  Flare* newFlare(LightSource* light, int x, int y, int changePerFrame, int limit);
  void createFlare(int x, int y, enum LightType lightIndex);
  void animateFlares(Flare** flares, int count);
  void deleteAllFlares();
  void demoteVisibility();
  void discoverCell(const int x, const int y);
  void updateVision(bool refreshDisplay);
  void burnItem(Item* theItem);
  void activateMachine(int machineNumber);
  bool circuitBreakersPreventActivation(int machineNumber);
  void promoteTile(int x, int y, enum dungeonLayers layer, bool useFireDF);
  void autoPlayLevel(bool fastForward);
  void updateClairvoyance();
  int scentDistance(int x1, int y1, int x2, int y2);
  int armorAggroAdjustment(Item* theArmor);
  int currentAggroValue();

  void initRecording();
  void flushBufferToFile();
  void fillBufferFromFile();
  void recordEvent(RogueEvent* event);
  void recallEvent(RogueEvent* event);
  void pausePlayback();
  void displayAnnotation();
  void loadSavedGame();
  void recordKeystroke(uchar keystroke, bool controlKey, bool shiftKey);
  void recordKeystrokeSequence(unsigned char* commandSequence);
  void recordMouseClick(int x, int y, bool controlKey, bool shiftKey);
  void OOSCheck(unsigned long x, int numberOfBytes);
  void RNGCheck();
  void executePlaybackInput(RogueEvent* recordingInput);
  void getAvailableFilePath(char* filePath, const char* defaultPath, const char* suffix);
  bool characterForbiddenInFilename(const char theChar);
  void saveGame();
  void saveRecording();
  void parseFile();
  void RNGLog(char* message);

  void checkForDungeonErrors();

  bool dialogChooseFile(char* path, const char* suffix, const char* prompt);
  void dialogAlert(char* message);
  void mainBrogueJunction();

  void initializeButton(BrogueButton* button);
  void drawButtonsInState(ButtonState* state);
  void initializeButtonState(ButtonState* state, BrogueButton* buttons, int buttonCount, int winX, int winY,
                             int winWidth, int winHeight);
  int processButtonInput(ButtonState* state, bool* canceled, RogueEvent* event);
  int smoothHiliteGradient(const int currentXValue, const int maxXValue);
  void drawButton(BrogueButton* button, enum ButtonDrawStates highlight, cellDisplayBuffer dbuf[COLS][ROWS]);
  int buttonInputLoop(BrogueButton* buttons, int buttonCount, int winX, int winY, int winWidth, int winHeight,
                      RogueEvent* returnEvent);

  void dijkstraScan(int** distanceMap, int** costMap, bool useDiagonals);
  void pdsClear(pdsMap* map, int maxDistance, bool eightWays);
  void pdsSetDistance(pdsMap* map, int x, int y, int distance);
  void pdsBatchOutput(pdsMap* map, int** distanceMap);

#if defined __cplusplus
}
#endif

#endif  // ROGUE_H
