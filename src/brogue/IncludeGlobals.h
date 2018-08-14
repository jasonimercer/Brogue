/*
 *  Include Globals.h
 *  Brogue
 *
 *  Created by Brian Walker on 2/8/09.
 *  Copyright 2012. All rights reserved.
 *
 *  This file is part of Brogue.
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

#include "Rogue.h"

extern TCell tmap[DCOLS][DROWS];  // grids with info about the map
extern pcell pmap[DCOLS][DROWS];  // grids with info about the map
extern int** scentMap;
extern cellDisplayBuffer displayBuffer[COLS][ROWS];
extern int terrainRandomValues[DCOLS][DROWS][8];
extern int** safetyMap;  // used to help monsters flee
extern int** allySafetyMap;
extern int** chokeMap;

// extern const int nbDirs[8][2];
extern const int cDirs[8][2];
extern LevelData* levels;
extern Creature player;
extern PlayerCharacter rogue;
extern Creature* monsters;
extern Creature* dormantMonsters;
extern Creature* graveyard;
extern Creature* purgatory;
extern Item* floorItems;
extern Item* packItems;
extern Item* monsterItemsHopper;
extern int numberOfWaypoints;

extern char displayedMessage[MESSAGE_LINES][COLS];
extern bool messageConfirmed[3];
extern char combatText[COLS];
int messageArchivePosition;
char messageArchive[MESSAGE_ARCHIVE_LINES][COLS * 2];

extern char currentFilePath[BROGUE_FILENAME_MAX];
extern unsigned long randomNumbersGenerated;

extern char displayDetail[DCOLS][DROWS];

#ifdef AUDIT_RNG
extern FILE* RNGLogFile;
#endif

extern unsigned char inputRecordBuffer[INPUT_RECORD_BUFFER + 100];
extern unsigned int locationInRecordingBuffer;

extern unsigned long positionInPlaybackFile;
extern unsigned long lengthOfPlaybackFile;
extern unsigned long recordingLocation;
extern unsigned long maxLevelChanges;
extern char annotationPathname[BROGUE_FILENAME_MAX];  // pathname of annotation file
extern unsigned long previousGameSeed;

// basic colors
extern Color white;
extern Color red;
extern Color blue;
extern Color darkRed;
extern Color gray;
extern Color darkGray;
extern Color veryDarkGray;
extern Color black;
extern Color yellow;
extern Color darkYellow;
extern Color teal;
extern Color purple;
extern Color darkPurple;
extern Color brown;
extern Color green;
extern Color darkGreen;
extern Color orange;
extern Color darkOrange;
extern Color darkBlue;
extern Color lightBlue;
extern Color pink;
extern Color tanColor;
extern Color sunlight;
extern Color rainbow;

// tile colors
extern Color undiscoveredColor;

extern Color wallForeColor;
extern Color wallBackColorStart;
extern Color wallBackColorEnd;
extern Color wallBackColor;
extern Color graniteBackColor;
extern Color floorForeColor;
extern Color floorBackColor;
extern Color doorForeColor;
extern Color doorBackColor;

extern Color deepWaterForeColor;
extern Color deepWaterBackColor;
extern Color shallowWaterForeColor;
extern Color shallowWaterBackColor;
extern Color mudForeColor;
extern Color mudBackColor;
extern Color chasmForeColor;
extern Color chasmEdgeBackColor;
extern Color fireForeColor;

// light colors
extern Color minersLightColor;
extern Color minersLightStartColor;
extern Color minersLightEndColor;
extern Color torchLightColor;
extern Color deepWaterLightColor;
extern Color redFlashColor;

extern Color discordColor;
extern Color memoryColor;
extern Color memoryOverlay;
extern Color magicMapColor;
extern Color clairvoyanceColor;
extern Color telepathyMultiplier;
extern Color omniscienceColor;
extern Color basicLightColor;

extern Color colorDim25;
extern Color colorMultiplier100;

extern Color magicMapFlashColor;

extern Color itemColor;
extern Color blueBar;
extern Color redBar;
extern Color hiliteColor;
extern Color interfaceBoxColor;
extern Color interfaceButtonColor;

extern Color playerInvisibleColor;
extern Color playerInShadowColor;
extern Color playerInLightColor;
extern Color playerInDarknessColor;

extern const Color inLightMultiplierColor;
extern const Color inDarknessMultiplierColor;

extern const Color buttonHoverColor;
extern Color titleButtonColor;

// other colors
extern Color centipedeColor;
extern Color confusionGasColor;
extern Color lightningColor;
extern Color spectralImageColor;

extern Color goodMessageColor;
extern Color badMessageColor;
extern Color advancementMessageColor;
extern Color itemMessageColor;
extern Color backgroundMessageColor;

extern Color flavorTextColor;

extern const Color flameSourceColor;
extern const Color flameSourceColorSecondary;
extern const Color flameTitleColor;

extern const Color superVictoryColor;

extern Color* dynamicColors[NUMBER_DYNAMIC_COLORS][3];

extern const AutoGenerator autoGeneratorCatalog[NUMBER_AUTOGENERATORS];

extern FloorTileType tileCatalog[NUMBER_TILETYPES];

extern DungeonFeature dungeonFeatureCatalog[NUMBER_DUNGEON_FEATURES];
extern DungeonProfile dungeonProfileCatalog[NUMBER_DUNGEON_PROFILES];

extern LightSource lightCatalog[NUMBER_LIGHT_KINDS];

extern const blueprint blueprintCatalog[NUMBER_BLUEPRINTS];

extern CreatureType monsterCatalog[NUMBER_MONSTER_KINDS];
extern MonsterWords monsterText[NUMBER_MONSTER_KINDS];
extern HordeType hordeCatalog[NUMBER_HORDES];
extern const Mutation mutationCatalog[NUMBER_MUTATORS];
extern const MonsterClass MonsterClassCatalog[MONSTER_CLASS_COUNT];

extern const Feature featTable[FEAT_COUNT];

// ITEMS
extern char itemTitles[NUMBER_SCROLL_KINDS][30];
extern char titlePhonemes[NUMBER_TITLE_PHONEMES][30];
extern char itemColors[NUMBER_ITEM_COLORS][30];
extern char itemWoods[NUMBER_ITEM_WOODS][30];
extern char itemMetals[NUMBER_ITEM_METALS][30];
extern char itemGems[NUMBER_ITEM_GEMS][30];

extern char itemColorsRef[NUMBER_ITEM_COLORS][30];
extern char itemWoodsRef[NUMBER_ITEM_WOODS][30];
extern char itemMetalsRef[NUMBER_ITEM_METALS][30];
extern char itemGemsRef[NUMBER_ITEM_GEMS][30];

extern ItemTable keyTable[NUMBER_KEY_TYPES];
extern ItemTable foodTable[NUMBER_FOOD_KINDS];
extern ItemTable weaponTable[NUMBER_WEAPON_KINDS];
extern ItemTable armorTable[NUMBER_ARMOR_KINDS];
extern ItemTable scrollTable[NUMBER_SCROLL_KINDS];
extern ItemTable potionTable[NUMBER_POTION_KINDS];
extern ItemTable wandTable[NUMBER_WAND_KINDS];
extern ItemTable staffTable[NUMBER_STAFF_KINDS];
extern ItemTable ringTable[NUMBER_RING_KINDS];
extern ItemTable charmTable[NUMBER_CHARM_KINDS];

extern const Bolt boltCatalog[NUMBER_BOLT_KINDS];

extern const char weaponRunicNames[NUMBER_WEAPON_RUNIC_KINDS][30];

extern const char armorRunicNames[NUMBER_ARMOR_ENCHANT_KINDS][30];

extern const char monsterBehaviorFlagDescriptions[32][COLS];
extern const char monsterAbilityFlagDescriptions[32][COLS];
extern const char monsterBookkeepingFlagDescriptions[32][COLS];
