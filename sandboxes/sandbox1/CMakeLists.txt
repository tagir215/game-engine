file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)
add_executable (sandbox1 ${SOURCES} ${HEADERS})
target_link_libraries(sandbox1 engine)


