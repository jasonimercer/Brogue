/*
 *  Grid
 *  Brogue
 *
 *  Created by Brian Walker on 12/7/12.
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

#include "IncludeGlobals.h"
#include "Rogue.h"

// mallocing two-dimensional arrays! dun dun DUN!
int** allocGrid()
{
  int i;
  int** array = malloc(DCOLS * sizeof(int*));

  array[0] = malloc(DROWS * DCOLS * sizeof(short));
  for (i = 1; i < DCOLS; i++)
  {
    array[i] = array[0] + i * DROWS;
  }
  return array;
}

void freeGrid(int** array)
{
  free(array[0]);
  free(array);
}

void copyGrid(int** to, int** from)
{
  int i, j;

  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      to[i][j] = from[i][j];
    }
  }
}

void fillGrid(int** grid, int fillValue)
{
  int i, j;

  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      grid[i][j] = fillValue;
    }
  }
}

// Highlight the portion indicated by hiliteCharGrid with the hiliteColor at the hiliteStrength -- both latter arguments
// are optional.
void hiliteGrid(int** grid, Color* hiliteColor, int hiliteStrength)
{
  int i, j, x, y;
  Color hCol;

  assureCosmeticRNG;

  if (hiliteColor)
  {
    hCol = *hiliteColor;
  }
  else
  {
    hCol = yellow;
  }

  bakeColor(&hCol);

  if (!hiliteStrength)
  {
    hiliteStrength = 75;
  }

  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j])
      {
        x = mapToWindowX(i);
        y = mapToWindowY(j);

        displayBuffer[x][y].needsUpdate = true;
        displayBuffer[x][y].backColorComponents[0] =
            clamp(displayBuffer[x][y].backColorComponents[0] + hCol.red * hiliteStrength / 100, 0, 100);
        displayBuffer[x][y].backColorComponents[1] =
            clamp(displayBuffer[x][y].backColorComponents[1] + hCol.green * hiliteStrength / 100, 0, 100);
        displayBuffer[x][y].backColorComponents[2] =
            clamp(displayBuffer[x][y].backColorComponents[2] + hCol.blue * hiliteStrength / 100, 0, 100);
        displayBuffer[x][y].foreColorComponents[0] =
            clamp(displayBuffer[x][y].foreColorComponents[0] + hCol.red * hiliteStrength / 100, 0, 100);
        displayBuffer[x][y].foreColorComponents[1] =
            clamp(displayBuffer[x][y].foreColorComponents[1] + hCol.green * hiliteStrength / 100, 0, 100);
        displayBuffer[x][y].foreColorComponents[2] =
            clamp(displayBuffer[x][y].foreColorComponents[2] + hCol.blue * hiliteStrength / 100, 0, 100);
      }
    }
  }
  restoreRNG;
}

void findReplaceGrid(int** grid, int findValueMin, int findValueMax, int fillValue)
{
  int i, j;

  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] >= findValueMin && grid[i][j] <= findValueMax)
      {
        grid[i][j] = fillValue;
      }
    }
  }
}

// Flood-fills the grid from (x, y) along cells that are within the eligible range.
// Returns the total count of filled cells.
int floodFillGrid(int** grid, int x, int y, int eligibleValueMin, int eligibleValueMax, int fillValue)
{
  enum Directions dir;
  int newX, newY, fillCount = 1;

  brogueAssert(fillValue < eligibleValueMin || fillValue > eligibleValueMax);

  grid[x][y] = fillValue;
  for (dir = 0; dir < 4; dir++)
  {
    newX = x + nbDirs[dir][0];
    newY = y + nbDirs[dir][1];
    if (coordinatesAreInMap(newX, newY) && grid[newX][newY] >= eligibleValueMin && grid[newX][newY] <= eligibleValueMax)
    {
      fillCount += floodFillGrid(grid, newX, newY, eligibleValueMin, eligibleValueMax, fillValue);
    }
  }
  return fillCount;
}

void drawRectangleOnGrid(int** grid, int x, int y, int width, int height, int value)
{
  int i, j;

  for (i = x; i < x + width; i++)
  {
    for (j = y; j < y + height; j++)
    {
      grid[i][j] = value;
    }
  }
}

void drawCircleOnGrid(int** grid, int x, int y, int radius, int value)
{
  int i, j;

  for (i = max(0, x - radius - 1); i < max(DCOLS, x + radius); i++)
  {
    for (j = max(0, y - radius - 1); j < max(DROWS, y + radius); j++)
    {
      if ((i - x) * (i - x) + (j - y) * (j - y) < radius * radius + radius)
      {
        grid[i][j] = value;
      }
    }
  }
}

void intersectGrids(int** onto, int** from)
{
  int i, j;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (onto[i][j] && from[i][j])
      {
        onto[i][j] = true;
      }
      else
      {
        onto[i][j] = false;
      }
    }
  }
}

void uniteGrids(int** onto, int** from)
{
  int i, j;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (!onto[i][j] && from[i][j])
      {
        onto[i][j] = from[i][j];
      }
    }
  }
}

void invertGrid(int** grid)
{
  int i, j;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      grid[i][j] = !grid[i][j];
    }
  }
}

// Fills grid locations with the given value if they match any terrain flags or map flags.
// Otherwise does not change the grid location.
void getTerrainGrid(int** grid, int value, unsigned long terrainFlags, unsigned long mapFlags)
{
  int i, j;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] != value && cellHasTerrainFlag(i, j, terrainFlags) || (pmap[i][j].flags & mapFlags))
      {
        grid[i][j] = value;
      }
    }
  }
}

void getTMGrid(int** grid, int value, unsigned long TMflags)
{
  int i, j;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] != value && cellHasTMFlag(i, j, TMflags))
      {
        grid[i][j] = value;
      }
    }
  }
}

void getPassableArcGrid(int** grid, int minPassableArc, int maxPassableArc, int value)
{
  int i, j, count;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] != value)
      {
        count = passableArcCount(i, j);
        if (count >= minPassableArc && count <= maxPassableArc)
        {
          grid[i][j] = value;
        }
      }
    }
  }
}

int validLocationCount(int** grid, int validValue)
{
  int i, j, count;
  count = 0;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] == validValue)
      {
        count++;
      }
    }
  }
  return count;
}

int leastPositiveValueInGrid(int** grid)
{
  int i, j, leastPositiveValue = 0;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] > 0 && (leastPositiveValue == 0 || grid[i][j] < leastPositiveValue))
      {
        leastPositiveValue = grid[i][j];
      }
    }
  }
  return leastPositiveValue;
}

// Takes a grid as a mask of valid locations, chooses one randomly and returns it as (x, y).
// If there are no valid locations, returns (-1, -1).
void randomLocationInGrid(int** grid, int* x, int* y, int validValue)
{
  const int locationCount = validLocationCount(grid, validValue);
  int i, j;

  if (locationCount <= 0)
  {
    *x = *y = -1;
    return;
  }
  int index = rand_range(0, locationCount - 1);
  for (i = 0; i < DCOLS && index >= 0; i++)
  {
    for (j = 0; j < DROWS && index >= 0; j++)
    {
      if (grid[i][j] == validValue)
      {
        if (index == 0)
        {
          *x = i;
          *y = j;
        }
        index--;
      }
    }
  }
  return;
}

// Finds the lowest positive number in a grid, chooses one location with that number randomly and returns it as (x, y).
// If there are no valid locations, returns (-1, -1).
void randomLeastPositiveLocationInGrid(int** grid, int* x, int* y, bool deterministic)
{
  const int targetValue = leastPositiveValueInGrid(grid);
  int locationCount;
  int i, j, index;

  if (targetValue == 0)
  {
    *x = *y = -1;
    return;
  }

  locationCount = 0;
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] == targetValue)
      {
        locationCount++;
      }
    }
  }

  if (deterministic)
  {
    index = locationCount / 2;
  }
  else
  {
    index = rand_range(0, locationCount - 1);
  }

  for (i = 0; i < DCOLS && index >= 0; i++)
  {
    for (j = 0; j < DROWS && index >= 0; j++)
    {
      if (grid[i][j] == targetValue)
      {
        if (index == 0)
        {
          *x = i;
          *y = j;
        }
        index--;
      }
    }
  }
  return;
}

bool getQualifyingPathLocNear(int* retValX, int* retValY, int x, int y, bool hallwaysAllowed,
                                 unsigned long blockingTerrainFlags, unsigned long blockingMapFlags,
                                 unsigned long forbiddenTerrainFlags, unsigned long forbiddenMapFlags,
                                 bool deterministic)
{
  int **grid, **costMap;
  int loc[2];

  // First check the given location to see if it works, as an optimization.
  if (!cellHasTerrainFlag(x, y, blockingTerrainFlags | forbiddenTerrainFlags) &&
      !(pmap[x][y].flags & (blockingMapFlags | forbiddenMapFlags)) && (hallwaysAllowed || passableArcCount(x, y) <= 1))
  {
    *retValX = x;
    *retValY = y;
    return true;
  }

  // Allocate the grids.
  grid = allocGrid();
  costMap = allocGrid();

  // Start with a base of a high number everywhere.
  fillGrid(grid, 30000);
  fillGrid(costMap, 1);

  // Block off the pathing blockers.
  getTerrainGrid(costMap, PDS_FORBIDDEN, blockingTerrainFlags, blockingMapFlags);
  if (blockingTerrainFlags & (T_OBSTRUCTS_DIAGONAL_MOVEMENT | T_OBSTRUCTS_PASSABILITY))
  {
    getTerrainGrid(costMap, PDS_OBSTRUCTION, T_OBSTRUCTS_DIAGONAL_MOVEMENT, 0);
  }

  // Run the distance scan.
  grid[x][y] = 1;
  costMap[x][y] = 1;
  dijkstraScan(grid, costMap, true);
  findReplaceGrid(grid, 30000, 30000, 0);

  // Block off invalid targets that aren't pathing blockers.
  getTerrainGrid(grid, 0, forbiddenTerrainFlags, forbiddenMapFlags);
  if (!hallwaysAllowed)
  {
    getPassableArcGrid(grid, 2, 10, 0);
  }

  // Get the solution.
  randomLeastPositiveLocationInGrid(grid, retValX, retValY, deterministic);

  //    dumpLevelToScreen();
  //    displayGrid(grid);
  //    if (coordinatesAreInMap(*retValX, *retValY)) {
  //        hiliteCell(*retValX, *retValY, &yellow, 100, true);
  //    }
  //    temporaryMessage("Qualifying path selected:", true);

  freeGrid(grid);
  freeGrid(costMap);

  // Fall back to a pathing-agnostic alternative if there are no solutions.
  if (*retValX == -1 && *retValY == -1)
  {
    if (getQualifyingLocNear(loc, x, y, hallwaysAllowed, nullptr, (blockingTerrainFlags | forbiddenTerrainFlags),
                             (blockingMapFlags | forbiddenMapFlags), false, deterministic))
    {
      *retValX = loc[0];
      *retValY = loc[1];
      return true;  // Found a fallback solution.
    }
    else
    {
      return false;  // No solutions.
    }
  }
  else
  {
    return true;  // Found a primary solution.
  }
}

void cellularAutomataRound(int** grid, char birthParameters[9], char survivalParameters[9])
{
  int i, j, nbCount, newX, newY;
  enum Directions dir;
  int** buffer2;

  buffer2 = allocGrid();
  copyGrid(buffer2, grid);  // Make a backup of grid in buffer2, so that each generation is isolated.

  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      nbCount = 0;
      for (dir = 0; dir < DIRECTION_COUNT; dir++)
      {
        newX = i + nbDirs[dir][0];
        newY = j + nbDirs[dir][1];
        if (coordinatesAreInMap(newX, newY) && buffer2[newX][newY])
        {
          nbCount++;
        }
      }
      if (!buffer2[i][j] && birthParameters[nbCount] == 't')
      {
        grid[i][j] = 1;  // birth
      }
      else if (buffer2[i][j] && survivalParameters[nbCount] == 't')
      {
        // survival
      }
      else
      {
        grid[i][j] = 0;  // death
      }
    }
  }

  freeGrid(buffer2);
}

// Marks a cell as being a member of blobNumber, then recursively iterates through the rest of the blob
int fillContiguousRegion(int** grid, int x, int y, int fillValue)
{
  enum Directions dir;
  int newX, newY, numberOfCells = 1;

  grid[x][y] = fillValue;

  // Iterate through the four cardinal neighbors.
  for (dir = 0; dir < 4; dir++)
  {
    newX = x + nbDirs[dir][0];
    newY = y + nbDirs[dir][1];
    if (!coordinatesAreInMap(newX, newY))
    {
      break;
    }
    if (grid[newX][newY] == 1)
    {  // If the neighbor is an unmarked region cell,
      numberOfCells += fillContiguousRegion(grid, newX, newY, fillValue);  // then recurse.
    }
  }
  return numberOfCells;
}

// Loads up **grid with the results of a cellular automata simulation.
void createBlobOnGrid(int** grid, int* retMinX, int* retMinY, int* retWidth, int* retHeight, int roundCount,
                      int minBlobWidth, int minBlobHeight, int maxBlobWidth, int maxBlobHeight,
                      int percentSeeded, char birthParameters[9], char survivalParameters[9])
{
  int i, j, k;
  int blobNumber, blobSize, topBlobNumber, topBlobSize;

  int topBlobMinX, topBlobMinY, topBlobMaxX, topBlobMaxY, blobWidth, blobHeight;
  // int buffer2[maxBlobWidth][maxBlobHeight]; // buffer[][] is already a global int array
  bool foundACellThisLine;

  // Generate blobs until they satisfy the minBlobWidth and minBlobHeight restraints
  do
  {
    // Clear buffer.
    fillGrid(grid, 0);

    // Fill relevant portion with noise based on the percentSeeded argument.
    for (i = 0; i < maxBlobWidth; i++)
    {
      for (j = 0; j < maxBlobHeight; j++)
      {
        grid[i][j] = (rand_percent(percentSeeded) ? 1 : 0);
      }
    }

    //        colorOverDungeon(&darkGray);
    //        hiliteGrid(grid, &white, 100);
    //        temporaryMessage("Random starting noise:", true);

    // Some iterations of cellular automata
    for (k = 0; k < roundCount; k++)
    {
      cellularAutomataRound(grid, birthParameters, survivalParameters);

      //            colorOverDungeon(&darkGray);
      //            hiliteGrid(grid, &white, 100);
      //            temporaryMessage("Cellular automata progress:", true);
    }

    //        colorOverDungeon(&darkGray);
    //        hiliteGrid(grid, &white, 100);
    //        temporaryMessage("Cellular automata result:", true);

    // Now to measure the result. These are best-of variables; start them out at worst-case values.
    topBlobSize = 0;
    topBlobNumber = 0;
    topBlobMinX = maxBlobWidth;
    topBlobMaxX = 0;
    topBlobMinY = maxBlobHeight;
    topBlobMaxY = 0;

    // Fill each blob with its own number, starting with 2 (since 1 means floor), and keeping track of the biggest:
    blobNumber = 2;

    for (i = 0; i < DCOLS; i++)
    {
      for (j = 0; j < DROWS; j++)
      {
        if (grid[i][j] == 1)
        {  // an unmarked blob
          // Mark all the cells and returns the total size:
          blobSize = fillContiguousRegion(grid, i, j, blobNumber);
          if (blobSize > topBlobSize)
          {  // if this blob is a new record
            topBlobSize = blobSize;
            topBlobNumber = blobNumber;
          }
          blobNumber++;
        }
      }
    }

    // Figure out the top blob's height and width:
    // First find the max & min x:
    for (i = 0; i < DCOLS; i++)
    {
      foundACellThisLine = false;
      for (j = 0; j < DROWS; j++)
      {
        if (grid[i][j] == topBlobNumber)
        {
          foundACellThisLine = true;
          break;
        }
      }
      if (foundACellThisLine)
      {
        if (i < topBlobMinX)
        {
          topBlobMinX = i;
        }
        if (i > topBlobMaxX)
        {
          topBlobMaxX = i;
        }
      }
    }

    // Then the max & min y:
    for (j = 0; j < DROWS; j++)
    {
      foundACellThisLine = false;
      for (i = 0; i < DCOLS; i++)
      {
        if (grid[i][j] == topBlobNumber)
        {
          foundACellThisLine = true;
          break;
        }
      }
      if (foundACellThisLine)
      {
        if (j < topBlobMinY)
        {
          topBlobMinY = j;
        }
        if (j > topBlobMaxY)
        {
          topBlobMaxY = j;
        }
      }
    }

    blobWidth = (topBlobMaxX - topBlobMinX) + 1;
    blobHeight = (topBlobMaxY - topBlobMinY) + 1;

  } while (blobWidth < minBlobWidth || blobHeight < minBlobHeight || topBlobNumber == 0);

  // Replace the winning blob with 1's, and everything else with 0's:
  for (i = 0; i < DCOLS; i++)
  {
    for (j = 0; j < DROWS; j++)
    {
      if (grid[i][j] == topBlobNumber)
      {
        grid[i][j] = 1;
      }
      else
      {
        grid[i][j] = 0;
      }
    }
  }

  // Populate the returned variables.
  *retMinX = topBlobMinX;
  *retMinY = topBlobMinY;
  *retWidth = blobWidth;
  *retHeight = blobHeight;
}
