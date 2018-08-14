/*
 *  Color.h
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

#ifndef COLOR_H
#define COLOR_H

struct Color
{
  // base RGB components:
  int red;
  int green;
  int blue;

  // random RGB components to add to base components:
  int redRand;
  int greenRand;
  int blueRand;

  // random scalar to add to all components:
  int rand;

  // Flag: this color "dances" with every refresh:
  bool colorDances;
};

#endif  // COLOR_H
