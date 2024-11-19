#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\HP\source\repos\Lab 10.1 b\Lab 10.1 b\source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            Student students[3] = {
                {"1", 2, COMPUTER_SCIENCE, {4}, {5, 4}},  
                {"J", 3, INFORMATICS, {3}, {5, 4}},     
                {"B", 1, ECONOMICS, {5}, {4, 4}}           
            };

            
            int expectedCount = 2;  
            int actualCount = countExcellentAndGoodStudents(students, 3);
            Assert::AreEqual(expectedCount, actualCount);
        };

    };
	
}
