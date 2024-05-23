file(GLOB SCENES "scenes/*")
file(GLOB ENTITIES "entities/*")
file(GLOB SYSTEMS "systems/*")
add_executable(kamkikong main_kamkikong.cpp ${SCENES} ${ENTITIES} ${SYSTEMS})
