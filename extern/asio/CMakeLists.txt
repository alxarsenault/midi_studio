 

# set(ASIO_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE ASIO_SOURCE_FILES
"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${APP_SOURCE_FILES})

# target_sources(${APP_NAME} PRIVATE ${APP_SOURCE_FILES})
 

add_library(asio INTERFACE ${ASIO_SOURCE_FILES})
target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)