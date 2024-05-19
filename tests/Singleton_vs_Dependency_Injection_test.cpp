
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string_view>
#include <iostream>
#include <sstream>

// Определения классов из SingletonLogger и DependencyInjectionLogger
namespace SingletonLogger {

    class Logger final
    {
    private:
        Logger() = default;

        Logger(const Logger&) = delete;
        Logger(Logger&&) noexcept = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger&&) noexcept = delete;

    public:
        static Logger& getInstance()
        {
            static Logger theLogger{};
            return theLogger;
        }

        void writeInfoEntry(std::string_view entry) {
            std::cout << "[INFO] " << entry << std::endl;
        }

        void writeWarnEntry(std::string_view entry) {
            std::cout << "[WARNING] " << entry << std::endl;
        }

        void writeErrorEntry(std::string_view entry) {
            std::cout << "[ERROR] " << entry << std::endl;
        }
    };

    class Customer {};

    class Identifier {};

    class CustomerRepository {
    public:
        Customer findCustomerById(const Identifier& customerId)
        {
            Logger::getInstance().writeInfoEntry("findCustomerById called ... ");
            return {};
        }
    };
}

namespace DependencyInjectionLogger {

    class ILoggingFacility
    {
    public:
        virtual ~ILoggingFacility() = default;
        virtual void writeInfoEntry(std::string_view entry) = 0;
        virtual void writeWarnEntry(std::string_view entry) = 0;
        virtual void writeErrorEntry(std::string_view entry) = 0;
    };

    class StandardOutputLogger : public ILoggingFacility
    {
    public:
        void writeInfoEntry(std::string_view entry) override {
            std::cout << "[INFO] " << entry << std::endl;
        }

        void writeWarnEntry(std::string_view entry) override {
            std::cout << "[WARNING] " << entry << std::endl;
        }

        void writeErrorEntry(std::string_view entry) override {
            std::cout << "[ERROR] " << entry << std::endl;
        }
    };

    class Customer {};

    class Identifier {};

    class CustomerRepository
    {
    public:
        CustomerRepository() = delete;

        explicit CustomerRepository(const std::shared_ptr<ILoggingFacility>& logger)
            : m_logger{ logger }
        { }
        
        Customer findCustomerById(const Identifier& customerId)
        {
            m_logger->writeInfoEntry("findCustomerById called ... ");
            return {};
        }

    private:
        std::shared_ptr<ILoggingFacility> m_logger;
    };

    class MockLogger : public ILoggingFacility
    {
    public:
        MOCK_METHOD(void, writeInfoEntry, (std::string_view), (override));
        MOCK_METHOD(void, writeWarnEntry, (std::string_view), (override));
        MOCK_METHOD(void, writeErrorEntry, (std::string_view), (override));
    };
}

// Тесты
TEST(SingletonLoggerTest, TestSingletonLoggerOutput) {
    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    SingletonLogger::CustomerRepository customerRepository;
    SingletonLogger::Identifier id;
    customerRepository.findCustomerById(id);

Дима, [19.05.2024 17:32]
std::cout.rdbuf(oldCoutStreamBuf);
    std::string output = oss.str();
    EXPECT_NE(output.find("[INFO] findCustomerById called ... "), std::string::npos);
}

TEST(DependencyInjectionLoggerTest, TestDIStandardLoggerOutput) {
    std::ostringstream oss;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    auto logger = std::make_shared<DependencyInjectionLogger::StandardOutputLogger>();
    DependencyInjectionLogger::CustomerRepository customerRepository{ logger };
    DependencyInjectionLogger::Identifier id;
    customerRepository.findCustomerById(id);

    std::cout.rdbuf(oldCoutStreamBuf);
    std::string output = oss.str();
    EXPECT_NE(output.find("[INFO] findCustomerById called ... "), std::string::npos);
}

TEST(DependencyInjectionLoggerTest, TestDIMockLogger) {
    auto mockLogger = std::make_shared<testing::StrictMock<DependencyInjectionLogger::MockLogger>>();
    DependencyInjectionLogger::CustomerRepository customerRepository{ mockLogger };

    EXPECT_CALL(*mockLogger, writeInfoEntry("findCustomerById called ... "));

    DependencyInjectionLogger::Identifier id;
    customerRepository.findCustomerById(id);
}

// main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
