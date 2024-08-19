# ライブラリターゲットの名前を指定
add_library(BMHitSearchLib SHARED BMHitSearch.cpp)
add_library(STHitSearchLib SHARED STHitSearch.cpp)

# ライブラリのヘッダファイルを公開（他のターゲットで使えるように）
target_include_directories(BMHitSearchLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(STHitSearchLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link with ...
target_link_libraries(BMHitSearchLib PUBLIC ${ROOT_LIBRARIES})
target_link_libraries(STHitSearchLib PUBLIC ${ROOT_LIBRARIES})