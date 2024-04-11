#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab11.1/lab11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestProcessData) {
            const char* test_input_file = "t1.txt";
            const char* test_output_file = "t2.txt";
            ofstream testInput(test_input_file);
            testInput << "1 2 3 4 5";
            testInput.close();

            ProcessData(test_input_file, test_output_file);

            ifstream testOutput(test_output_file);
            stringstream buffer;
            buffer << testOutput.rdbuf();
            string outputContent = buffer.str();

            string expectedOutput = "Average of max and min components: 3\nAverage of all components: 3\n";
            Assert::AreEqual(expectedOutput, outputContent);
        }

        TEST_METHOD(TestPrintFileContents) {
            const char* test_input_file = "t.txt";
            ofstream testInput(test_input_file);
            string fileData = "Line 1\nLine 2\nLine 3";
            testInput << fileData;
            testInput.close();

            streambuf* origCoutStreamBuf = std::cout.rdbuf();
            ostringstream strCout;
            cout.rdbuf(strCout.rdbuf());
            PrintFileContents(test_input_file);
            cout.rdbuf(origCoutStreamBuf);
            string expectedOutput = "Contents of t.txt:\nLine 1\nLine 2\nLine 3\n";

            Assert::AreEqual(expectedOutput, strCout.str());
        }
	};
}