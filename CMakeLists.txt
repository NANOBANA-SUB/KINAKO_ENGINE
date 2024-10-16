cmake_minimum_required(VERSION 3.10)
project(KINAKO_ENGINE)

# C++の標準バージョンを指定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 実行ファイルの出力ディレクトリを設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# インクルードディレクトリを指定
include_directories(
    ${CMAKE_SOURCE_DIR}/third_party
    ${CMAKE_SOURCE_DIR}/Main/include
    ${CMAKE_SOURCE_DIR}/include
)

# ライブラリのリンクディレクトリを指定
link_directories(
    ${CMAKE_SOURCE_DIR}/third_party/GL/lib
    ${CMAKE_SOURCE_DIR}/third_party/SDL2/lib/x64
    ${CMAKE_SOURCE_DIR}/third_party/quill/include
)

# ソースファイルを指定
set(SOURCES
    Main/src/Main.cpp
    Main/src/Engine.cpp
)

# 実行ファイルを作成（通常ビルド用）
add_executable(KINAKO_ENGINE ${SOURCES})

# 必要なライブラリをリンク
target_link_libraries(KINAKO_ENGINE
    SDL2main
    SDL2
    glew32
    opengl32
)

# テストのビルドオプションを追加
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()

    # テスト用のソースファイルを設定
    set(TEST_SOURCES
        test/EngineTest.cpp
    )

    # テスト実行ファイルを作成
    add_executable(test_engine ${TEST_SOURCES} Main/src/Engine.cpp)

    # テスト実行ファイルにライブラリをリンク
    target_link_libraries(test_engine
        SDL2main
        SDL2
        glew32
        opengl32
    )
endif()
