message (STATUS "TimingMatch...")

add_executable(TimingMatch TimingMatch.cpp)

# ヘッダファイルのインクルードディレクトリを追加
# lib ディレクトリが含まれるようにする
target_include_directories(TimingMatch PRIVATE
    ${PROJECT_SOURCE_DIR}/lib  # ここにヘッダファイルが存在する場合
    ${PROJECT_SOURCE_DIR}/lib/src  # ここにライブラリが存在する場合
    ${ROOT_INCLUDE_DIRS}       # ROOTのインクルードディレクトリも含める
)

# ヘッダファイルのインクルードディレクトリを追加
# lib ディレクトリが含まれるようにする
target_include_directories(TimingMatch PRIVATE
    ${PROJECT_SOURCE_DIR}/lib  # ここにヘッダファイルが存在する場合
    ${PROJECT_SOURCE_DIR}/lib/src  # ここにライブラリが存在する場合
    ${ROOT_INCLUDE_DIRS}       # ROOTのインクルードディレクトリも含める
)

# 必要なライブラリをリンク
target_link_libraries(TimingMatch PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/library/libBMBasicRecon.so
    ${PROJECT_SOURCE_DIR}/lib/library/libBMBeaminfo.so
    ${PROJECT_SOURCE_DIR}/lib/library/libBMBSD.so
    ${ROOT_LIBRARIES}
    BMHitSearchLib
    STHitSearchLib
)

#install the executable in the bin folder
install(TARGETS TimingMatch DESTINATION "${CMAKE_INSTALL_BINDIR}")