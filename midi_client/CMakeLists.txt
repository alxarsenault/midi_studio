
set(CLIENT_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE CLIENT_SOURCE_FILES
  "${CLIENT_SOURCE_DIRECTORY}/*.cpp"
  "${CLIENT_SOURCE_DIRECTORY}/*.h"
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CLIENT_SOURCE_FILES})



add_executable(midi_client ${CLIENT_SOURCE_FILES})
target_include_directories(midi_client PUBLIC ${CLIENT_SOURCE_DIRECTORY})
target_link_libraries(midi_client PUBLIC rtmidi asio uv_a)