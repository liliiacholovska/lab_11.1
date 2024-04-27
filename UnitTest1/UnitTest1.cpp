#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.1/lab11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestCalculateAverages) {
            const char* test_input_file = "t1.bin";
            ofstream testInput(test_input_file, ios::binary);
            int numbers[] = { 1, 2, 3, 4, 5 };
            for (int num : numbers) {
                testInput.write(reinterpret_cast<char*>(&num), sizeof(num));
            }
            testInput.close();

            double avgMinMax, overallAvg;
            CalculateAverages(test_input_file, avgMinMax, overallAvg);

            Assert::AreEqual(3.0, avgMinMax, 0.01); 
            Assert::AreEqual(3.0, overallAvg, 0.01); 
        }

        TEST_METHOD(TestWriteAndReadAverages) {
            const char* test_output_file = "t2.bin";
            double avgMinMax = 3.0, overallAvg = 3.0;

            WriteAveragesToFile(test_output_file, avgMinMax, overallAvg);

            double readAvgMinMax, readOverallAvg;
            ReadAveragesFromFile(test_output_file, readAvgMinMax, readOverallAvg);

            Assert::AreEqual(avgMinMax, readAvgMinMax, 0.01);
            Assert::AreEqual(overallAvg, readOverallAvg, 0.01);
        }
	};
}
