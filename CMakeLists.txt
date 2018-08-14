cmake_minimum_required(VERSION 3.1)
project(Brogue)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src/brogue src/platform)

add_executable (brogue
	src/brogue/Architect.cpp
	src/brogue/Buttons.cpp
	src/brogue/Combat.cpp
	src/brogue/Dijkstra.cpp
	src/brogue/Globals.cpp
	src/brogue/Grid.cpp
	src/brogue/IncludeGlobals.h
	src/brogue/IO.cpp
	src/brogue/Items.cpp
	src/brogue/Light.cpp
	src/brogue/MainMenu.cpp
	src/brogue/Monsters.cpp
	src/brogue/Movement.cpp
	src/brogue/Random.cpp
	src/brogue/Recordings.cpp
	src/brogue/Rogue.h
	src/brogue/RogueMain.cpp
	src/brogue/Time.cpp

  src/brogue/Color.h
  src/brogue/Dungeon.h
  src/brogue/Flag.h
  src/brogue/IncludeGlobals.h
  src/brogue/Items.h
  src/brogue/Monsters.h
  src/brogue/Movement.h
  src/brogue/RandomRange.h
  src/brogue/Rogue.h
  src/brogue/Types.h
)

target_link_libraries(brogue m)

#demo.cppxx demo_b.cppxx)

# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
#target_link_libraries (helloDemo LINK_PUBLIC Hello)
