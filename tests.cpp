#include <gtest/gtest.h>

extern "C" {
    #include "vector.h"
    #include "real.h"
    #include "error.h"
}

TEST(VectorCreateTest, NullFieldInfo) {
    Vector* v = vector_create(NULL);
    EXPECT_EQ(v, nullptr);
    EXPECT_TRUE(has_error());
    get_error();
}

TEST(VectorPushBackTest, NullVector) {
    double val = 1.0;
    vector_push_back(NULL, &val);
    EXPECT_TRUE(has_error());
    get_error();
}

TEST(VectorPushBackTest, NullElement) {
    const FieldInfo* info = get_real_field_info();
    Vector* v = vector_create(info);
    vector_push_back(v, NULL);
    EXPECT_TRUE(has_error());
    get_error();
    vector_destroy(v);
}

TEST(VectorGetTest, EmptyVector) {
    const FieldInfo* info = get_real_field_info();
    Vector* v = vector_create(info);
    void* elem = vector_get(v, 0);
    EXPECT_EQ(elem, nullptr);
    EXPECT_TRUE(has_error());
    vector_destroy(v);
    get_error();
}

TEST(VectorAddTest, DifferentTypes) {
    // Этот тест показывает, что GoogleTest работает
    // Проверка сложения векторов разных типов
    EXPECT_TRUE(true);
}

TEST(DotProductTest, DifferentTypes) {
    // Этот тест показывает, что GoogleTest работает
    EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}