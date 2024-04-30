file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp) 
target_sources(kamkanoid PRIVATE ${HEADERS} ${SOURCES}) 
