#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../third_party/doctest/doctest.h"
#include "../Main/include/Engine.h" // テスト対象の実装ファイル

TEST_CASE("Engine Initialization Test") {
    Engine engine;

    // Initializeメソッドが成功するかのテスト
    CHECK(engine.Initialize() == true);
}
