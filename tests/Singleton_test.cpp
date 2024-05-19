#include <gtest/gtest.h>
#include "../ConceptualExample01.cpp"
#include "../ConceptualExample02.cpp"
#include "../Program.cpp"
#include "../Singleton_vs_Dependency_Injection.cpp"

// Test 1: Check Singleton instance for ConceptualExample01
TEST(SingletonTest, ConceptualExample01) {
    auto& instance1 = Singleton::getInstance();
    auto& instance2 = Singleton::getInstance();
    ASSERT_EQ(&instance1, &instance2) << "Instances are not the same in ConceptualExample01!";
}

// Test 2: Check Singleton instance for ConceptualExample02
TEST(SingletonTest, ConceptualExample02) {
    auto& instance1 = Singleton::getInstance();
    auto& instance2 = Singleton::getInstance();
    ASSERT_EQ(&instance1, &instance2) << "Instances are not the same in ConceptualExample02!";
}

// Test 3: Check Singleton instance for Singleton_vs_Dependency_Injection
TEST(SingletonTest, SingletonVsDI) {
    auto& instance1 = Singleton::getInstance();
    auto& instance2 = Singleton::getInstance();
    ASSERT_EQ(&instance1, &instance2) << "Instances are not the same in Singleton_vs_Dependency_Injection!";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
