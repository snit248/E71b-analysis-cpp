message (STATUS "TimingMatch...")

add_executable(TimingMatch TimingMatch.cpp)

target_link_libraries(TimingMatch ${ROOT_LIBRARIES} BMHitSearchLib STHitSearchLib)

#install the executable in the bin folder
install(TARGETS TimingMatch DESTINATION "{CMAKE_INSTALL_BINDIR}/TimingMatch")