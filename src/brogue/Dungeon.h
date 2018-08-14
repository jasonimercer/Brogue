/*
 *  Dungeon.h
 *  Brogue++
 *
 *  Written by Jason I Mercer
 *
 *  Based on code and ideas by Brian Walker
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DUNGEON_H
#define DUNGEON_H

enum dungeonLayers
{
  NO_LAYER = -1,
  DUNGEON = 0,  // dungeon-level tile	(e.g. walls)
  LIQUID,       // liquid-level tile	(e.g. lava)
  GAS,          // gas-level tile		(e.g. fire, smoke, swamp gas)
  SURFACE,      // surface-level tile	(e.g. grass)
  NUMBER_TERRAIN_LAYERS
};

enum DungeonFeatureTypes
{
  DF_GRANITE_COLUMN = 1,
  DF_CRYSTAL_WALL,
  DF_LUMINESCENT_FUNGUS,
  DF_GRASS,
  DF_DEAD_GRASS,
  DF_BONES,
  DF_RUBBLE,
  DF_FOLIAGE,
  DF_FUNGUS_FOREST,
  DF_DEAD_FOLIAGE,

  DF_SUNLIGHT,
  DF_DARKNESS,

  DF_SHOW_DOOR,
  DF_SHOW_POISON_GAS_TRAP,
  DF_SHOW_PARALYSIS_GAS_TRAP,
  DF_SHOW_TRAPDOOR_HALO,
  DF_SHOW_TRAPDOOR,
  DF_SHOW_CONFUSION_GAS_TRAP,
  DF_SHOW_FLAMETHROWER_TRAP,
  DF_SHOW_FLOOD_TRAP,
  DF_SHOW_NET_TRAP,
  DF_SHOW_ALARM_TRAP,

  DF_RED_BLOOD,
  DF_GREEN_BLOOD,
  DF_PURPLE_BLOOD,
  DF_WORM_BLOOD,
  DF_ACID_BLOOD,
  DF_ASH_BLOOD,
  DF_EMBER_BLOOD,
  DF_ECTOPLASM_BLOOD,
  DF_RUBBLE_BLOOD,
  DF_ROT_GAS_BLOOD,

  DF_VOMIT,
  DF_BLOAT_DEATH,
  DF_BLOAT_EXPLOSION,
  DF_BLOOD_EXPLOSION,
  DF_FLAMEDANCER_CORONA,

  DF_MUTATION_EXPLOSION,
  DF_MUTATION_LICHEN,

  DF_REPEL_CREATURES,
  DF_ROT_GAS_PUFF,
  DF_STEAM_PUFF,
  DF_STEAM_ACCUMULATION,
  DF_METHANE_GAS_PUFF,
  DF_SALAMANDER_FLAME,
  DF_URINE,
  DF_UNICORN_POOP,
  DF_PUDDLE,
  DF_ASH,
  DF_ECTOPLASM_DROPLET,
  DF_FORCEFIELD,
  DF_FORCEFIELD_MELT,
  DF_SACRED_GLYPHS,
  DF_LICHEN_GROW,
  DF_TUNNELIZE,
  DF_SHATTERING_SPELL,

  // spiderwebs
  DF_WEB_SMALL,
  DF_WEB_LARGE,

  // ancient spirit
  DF_ANCIENT_SPIRIT_VINES,
  DF_ANCIENT_SPIRIT_GRASS,

  // foliage
  DF_TRAMPLED_FOLIAGE,
  DF_SMALL_DEAD_GRASS,
  DF_FOLIAGE_REGROW,
  DF_TRAMPLED_FUNGUS_FOREST,
  DF_FUNGUS_FOREST_REGROW,

  // brimstone
  DF_ACTIVE_BRIMSTONE,
  DF_INERT_BRIMSTONE,

  // bloodwort
  DF_BLOODFLOWER_PODS_GROW_INITIAL,
  DF_BLOODFLOWER_PODS_GROW,
  DF_BLOODFLOWER_POD_BURST,

  // dewars
  DF_DEWAR_CAUSTIC,
  DF_DEWAR_CONFUSION,
  DF_DEWAR_PARALYSIS,
  DF_DEWAR_METHANE,
  DF_DEWAR_GLASS,
  DF_CARPET_AREA,

  // algae
  DF_BUILD_ALGAE_WELL,
  DF_ALGAE_1,
  DF_ALGAE_2,
  DF_ALGAE_REVERT,

  DF_OPEN_DOOR,
  DF_CLOSED_DOOR,
  DF_OPEN_IRON_DOOR_INERT,
  DF_ITEM_CAGE_OPEN,
  DF_ITEM_CAGE_CLOSE,
  DF_ALTAR_INERT,
  DF_ALTAR_RETRACT,
  DF_PORTAL_ACTIVATE,
  DF_INACTIVE_GLYPH,
  DF_ACTIVE_GLYPH,
  DF_SILENT_GLYPH_GLOW,
  DF_GUARDIAN_STEP,
  DF_MIRROR_TOTEM_STEP,
  DF_GLYPH_CIRCLE,
  DF_REVEAL_LEVER,
  DF_PULL_LEVER,
  DF_CREATE_LEVER,

  DF_BRIDGE_FALL_PREP,
  DF_BRIDGE_FALL,

  DF_PLAIN_FIRE,
  DF_GAS_FIRE,
  DF_EXPLOSION_FIRE,
  DF_DART_EXPLOSION,
  DF_BRIMSTONE_FIRE,
  DF_BRIDGE_FIRE,
  DF_FLAMETHROWER,
  DF_EMBERS,
  DF_EMBERS_PATCH,
  DF_OBSIDIAN,
  DF_ITEM_FIRE,
  DF_CREATURE_FIRE,

  DF_FLOOD,
  DF_FLOOD_2,
  DF_FLOOD_DRAIN,
  DF_HOLE_2,
  DF_HOLE_DRAIN,

  DF_POISON_GAS_CLOUD,
  DF_CONFUSION_GAS_TRAP_CLOUD,
  DF_NET,
  DF_AGGRAVATE_TRAP,
  DF_METHANE_GAS_ARMAGEDDON,

  // potions
  DF_POISON_GAS_CLOUD_POTION,
  DF_PARALYSIS_GAS_CLOUD_POTION,
  DF_CONFUSION_GAS_CLOUD_POTION,
  DF_INCINERATION_POTION,
  DF_DARKNESS_POTION,
  DF_HOLE_POTION,
  DF_LICHEN_PLANTED,

  // other items
  DF_ARMOR_IMMOLATION,
  DF_STAFF_HOLE,
  DF_STAFF_HOLE_EDGE,

  // commutation altar
  DF_ALTAR_COMMUTE,
  DF_MAGIC_PIPING,
  DF_INERT_PIPE,

  // resurrection altar
  DF_ALTAR_RESURRECT,
  DF_MACHINE_FLOOR_TRIGGER_REPEATING,

  // vampire in coffin
  DF_COFFIN_BURSTS,
  DF_COFFIN_BURNS,
  DF_TRIGGER_AREA,

  // throwing tutorial -- button in chasm
  DF_CAGE_DISAPPEARS,
  DF_MEDIUM_HOLE,
  DF_MEDIUM_LAVA_POND,
  DF_MACHINE_PRESSURE_PLATE_USED,

  // rat trap
  DF_WALL_CRACK,

  // wooden barricade at entrance
  DF_WOODEN_BARRICADE_BURN,

  // wooden barricade around altar, dead grass all around
  DF_SURROUND_WOODEN_BARRICADE,

  // pools of water that, when triggered, slowly expand to fill the room
  DF_SPREADABLE_WATER,
  DF_SHALLOW_WATER,
  DF_WATER_SPREADS,
  DF_SPREADABLE_WATER_POOL,
  DF_SPREADABLE_DEEP_WATER_POOL,

  // when triggered, the ground gradually turns into chasm:
  DF_SPREADABLE_COLLAPSE,
  DF_COLLAPSE,
  DF_COLLAPSE_SPREADS,
  DF_ADD_MACHINE_COLLAPSE_EDGE_DORMANT,

  // when triggered, a bridge appears:
  DF_BRIDGE_ACTIVATE,
  DF_BRIDGE_ACTIVATE_ANNOUNCE,
  DF_BRIDGE_APPEARS,
  DF_ADD_DORMANT_CHASM_HALO,

  // when triggered, the lava retracts:
  DF_LAVA_RETRACTABLE,
  DF_RETRACTING_LAVA,
  DF_OBSIDIAN_WITH_STEAM,

  // when triggered, the door seals and caustic gas fills the room
  DF_SHOW_POISON_GAS_VENT,
  DF_POISON_GAS_VENT_OPEN,
  DF_ACTIVATE_PORTCULLIS,
  DF_OPEN_PORTCULLIS,
  DF_VENT_SPEW_POISON_GAS,

  // when triggered, pilot light ignites and explosive gas fills the room
  DF_SHOW_METHANE_VENT,
  DF_METHANE_VENT_OPEN,
  DF_VENT_SPEW_METHANE,
  DF_PILOT_LIGHT,

  // paralysis trap: trigger plate with gas vents nearby
  DF_DISCOVER_PARALYSIS_VENT,
  DF_PARALYSIS_VENT_SPEW,
  DF_REVEAL_PARALYSIS_VENT_SILENTLY,

  // thematic dungeon
  DF_AMBIENT_BLOOD,

  // statues crack for a few turns and then shatter, revealing the monster inside
  DF_CRACKING_STATUE,
  DF_STATUE_SHATTER,

  // a turret appears:
  DF_TURRET_EMERGE,

  // an elaborate worm catacomb opens up
  DF_WORM_TUNNEL_MARKER_DORMANT,
  DF_WORM_TUNNEL_MARKER_ACTIVE,
  DF_GRANITE_CRUMBLES,
  DF_WALL_OPEN,

  // the room gradually darkens
  DF_DARKENING_FLOOR,
  DF_DARK_FLOOR,
  DF_HAUNTED_TORCH_TRANSITION,
  DF_HAUNTED_TORCH,

  // bubbles rise from the mud and bog monsters spawn
  DF_MUD_DORMANT,
  DF_MUD_ACTIVATE,

  // crystals charge when hit by lightning
  DF_ELECTRIC_CRYSTAL_ON,
  DF_TURRET_LEVER,

  // idyll:
  DF_SHALLOW_WATER_POOL,
  DF_DEEP_WATER_POOL,

  // swamp:
  DF_SWAMP_WATER,
  DF_SWAMP,
  DF_SWAMP_MUD,

  // camp:
  DF_HAY,
  DF_JUNK,

  // remnants:
  DF_REMNANT,
  DF_REMNANT_ASH,

  // chasm catwalk:
  DF_CHASM_HOLE,
  DF_CATWALK_BRIDGE,

  // lake catwalk:
  DF_LAKE_CELL,
  DF_LAKE_HALO,

  // worm den:
  DF_WALL_SHATTER,

  // monster cages open:
  DF_MONSTER_CAGE_OPENS,

  // goblin warren:
  DF_STENCH_BURN,
  DF_STENCH_SMOLDER,

  NUMBER_DUNGEON_FEATURES,
};


#endif  // DUNGEON_H
