# CMakeの最低バージョンを指定（最初に置く必要があります）
cmake_minimum_required(VERSION 3.10.2)

# CMP0048ポリシーを新しいバージョンに設定
cmake_policy(SET CMP0048 NEW)

# Be verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

# インソースビルドを禁止
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif ()

# プロジェクトの定義（VERSIONオプションを使用）
project(TimingMatch
        DESCRIPTION "E71b analysis"
        VERSION "0.1"
        LANGUAGES CXX)

# ビルドタイプの設定
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

# プロジェクトバージョンの定義
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
add_compile_definitions(VERSION=${PROJECT_VERSION})

# UNIX以外のOSではビルドを中断
if (NOT UNIX)
    message(FATAL_ERROR "Non UNIX OSes are not supported")
endif ()

# macOS特有の設定
if (APPLE)
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif ()

# デフォルトのインストールディレクトリの設定
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE PATH "default install path" FORCE)
endif ()

# インストールディレクトリの設定
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib/ninja/recon)
set(CMAKE_INSTALL_INCDIR ${CMAKE_INSTALL_PREFIX}/include/ninja/recon)

# モジュールパスの設定
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# ROOTライブラリの検索とインクルード
find_package(ROOT 6.18 CONFIG REQUIRED)
include(${ROOT_USE_FILE})

# ライブラリの設定
set(E71b_LIBRARIES "")
list(APPEND E71b_LIBRARIES
    ${ROOT_LIBRARIES}
)

# C++11を標準として指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# コンパイラフラグの設定
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wno-overloaded-virtual -Wno-shadow")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif ()

# サブディレクトリの追加
add_subdirectory(src)