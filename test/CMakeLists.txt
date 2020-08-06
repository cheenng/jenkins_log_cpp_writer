set(Target test_xml)
set(Include_Path ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE sources *.cpp)
file(GLOB_RECURSE headers *.h)
file(GLOB include ${Include_Path}/*.h) 
add_executable(${Target} ${sources} ${headers} ${include})

Target_include_directories(${Target} PUBLIC ${CMAKE_SOURCE_DIR}/xml
                                     PUBLIC ${Include_Path}) 

target_link_libraries(${Target} debug tinyxml_STL)
target_link_libraries(${Target} optimized tinyxml_STL)

