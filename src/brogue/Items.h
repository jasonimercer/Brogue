/*
 *  Items.h
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

#ifndef ITEMS_H
#define ITEMS_H

#include "Monsters.h"

struct Item
{
  ItemCategory category;
  int kind;
  unsigned long flags;
  RandomRange damage;
  int armor;
  int charges;
  int enchant1;
  int enchant2;
  int timesEnchanted;
  enum MonsterTypes vorpalEnemy;
  int strengthRequired;
  unsigned int quiverNumber;
  uchar displayChar;
  Color* foreColor;
  Color* inventoryColor;
  int quantity;
  char inventoryLetter;
  char inscription[DCOLS];
  int xLoc;
  int yLoc;
  KeyLocationProfile keyLoc[KEY_ID_MAXIMUM];
  int originDepth;
  struct Item* nextItem;
};


#endif  // ITEMS_H
