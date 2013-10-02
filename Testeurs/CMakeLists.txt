cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests fileTesteur.cpp pileTesteur.cpp carteTesteur.cpp ../Carte.cpp colonneTesteur.cpp ../Colonne.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)