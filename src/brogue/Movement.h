/*
 *  Movement.h
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

#ifndef MOVEMENT_H
#define MOVEMENT_H

enum Directions
{
  NO_DIRECTION = -1,
  // Cardinal directions; must be 0-3:
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3,
  // Secondary directions; must be 4-7:
  UPLEFT = 4,
  DOWNLEFT = 5,
  UPRIGHT = 6,
  DOWNRIGHT = 7,

  DIRECTION_COUNT = 8,
};

constexpr int xComponent(Directions direction)
{
  switch (direction)
  {
    case UPLEFT:
    case LEFT:
    case DOWNLEFT:
      return -1;

    case UP:
    case NO_DIRECTION:
    case DOWN:
    case DIRECTION_COUNT:
      return 0;

    case UPRIGHT:
    case RIGHT:
    case DOWNRIGHT:
      return 1;
  }
  return 0;
}

constexpr int yComponent(Directions direction)
{
  switch (direction)
  {
    case DOWN:
    case DOWNLEFT:
    case DOWNRIGHT:
      return -1;
    case LEFT:
    case RIGHT:
    case NO_DIRECTION:
    case DIRECTION_COUNT:
      return 0;
    case UP:
    case UPLEFT:
    case UPRIGHT:
      return 1;
  }
  return 0;
}

static constexpr int nbDirs[8][2] = {
  { xComponent(UP), yComponent(UP) },           { xComponent(DOWN), yComponent(DOWN) },
  { xComponent(LEFT), yComponent(LEFT) },       { xComponent(RIGHT), yComponent(RIGHT) },
  { xComponent(UPLEFT), yComponent(UPLEFT) },   { xComponent(DOWNLEFT), yComponent(DOWNLEFT) },
  { xComponent(UPRIGHT), yComponent(UPRIGHT) }, { xComponent(DOWNRIGHT), yComponent(DOWNRIGHT) }
};

#endif  // MOVEMENT_H
