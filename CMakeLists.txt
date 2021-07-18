cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME BoardGames)

project(${PROJECT_NAME})

set(SOURCE_FILES main.cpp source/buddhichal/buddhichal.cpp source/checkers/checkers.cpp source/chess/chess.cpp include/buddhichal/Buddhichal.hpp include/checkers/Checkers.hpp include/chess/Chess.hpp)

set(SFMLLinkers -lsfml-network -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(BoardGames include)

target_link_libraries(${PROJECT_NAME} ${SFMLLinkers})

