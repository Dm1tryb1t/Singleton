#include "gtest/gtest.h"
#include "ConceptualExample01.cpp" // Включаем ваш исходный файл для тестирования

// Тест на одиночество (singleton) без потоков
TEST(SingletonTest, NonThreadedSingleton) {
    ConceptualExample01::Singleton* singleton = ConceptualExample01::Singleton::getInstance();
    ASSERT_NE(singleton, nullptr);
    
    ConceptualExample01::Singleton* another_singleton = ConceptualExample01::Singleton::getInstance();
    ASSERT_EQ(singleton, another_singleton);
}

// Тест на несколько экземпляров без обеспечения потокобезопасности
TEST(SingletonTest, MultipleInstancesWithoutThreadSafety) {
    ConceptualExample01::Singleton* singleton1 = ConceptualExample01::Singleton::getInstance();
    ConceptualExample01::Singleton* singleton2 = ConceptualExample01::Singleton::getInstance();
    ASSERT_EQ(singleton1, singleton2);
    
    ConceptualExample01::Singleton* singleton3 = ConceptualExample01::Singleton::getInstanceThreadSafe();
    ConceptualExample01::Singleton* singleton4 = ConceptualExample01::Singleton::getInstanceThreadSafe();
    ASSERT_EQ(singleton3, singleton4);
}

// Тест на потокобезопасность в С++17
TEST(SingletonTest, ThreadSafetyCpp17) {
    constexpr int num_threads = 4;
    std::vector<std::thread> threads(num_threads);
    std::vector<ConceptualExample01::Singleton*> singletons(num_threads);

    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([&singletons, i]() {
            singletons[i] = ConceptualExample01::Singleton::getInstanceThreadSafe_Cpp17();
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (int i = 1; i < num_threads; ++i) {
        ASSERT_EQ(singletons[i], singletons[0]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}