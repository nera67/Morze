#include "pch.h"
#include "CppUnitTest.h"
#include "../MorzeDecode/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const int argc = -1;

namespace ValidateDataTest
{
	TEST_CLASS(ValidateDataTest)
	{
	public:
		
		TEST_METHOD(NoError_WithoutPause)
		{
			char input[MAX_INPUT_LENGTH] = "-.---.-..-.-.--.--.-.-.-";
			char mode[14] = "without_pause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(-1, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(NoError_WithPause)
		{
			char input[MAX_INPUT_LENGTH] = "-.- --- .. .-. --";
			char mode[14] = "pause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(- 1, validate_data(input, mode, temp, argv, argc));
		}

		TEST_METHOD(InputFileEmpty)
		{
			char input[MAX_INPUT_LENGTH] = "";
			char mode[14] = "";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(2, validate_data(input, mode, temp, argv, argc));
		}

		TEST_METHOD(InvalidCharacters_WithPause_NotPointNotDash)
		{
			char input[MAX_INPUT_LENGTH] = "-.a --s 3. .4. -*";
			char mode[14] = "pause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(3, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(InvalidCharacters_WithoutPause_NotPointNotDash)
		{
			char input[MAX_INPUT_LENGTH] = "-.a--.s3.4.-*";
			char mode[14] = "without_pause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(3, validate_data(input, mode, temp, argv, argc));
		}

		TEST_METHOD(StringSizeOutOfRange_WithPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "pause";
			char temp[2] = "p";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(4, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(StringSizeOutOfRange_WithoutPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-.-.--..--.-.-";
			char mode[14] = "without_pause";
			char temp[2] = "p";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(4, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(StringSizeOutOfRange_WithoutPause_More1000Symbols)
		{
			char input[MAX_INPUT_LENGTH] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			char mode[14] = "-\nwithout_pau";
			char temp[2] = "s";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(4, validate_data(input, mode, temp, argv, argc));
		}

		TEST_METHOD(NoDecryptionMode_WithPause)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(5, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(NoDecryptionMode_WithoutPause)
		{
			char input[MAX_INPUT_LENGTH] = "-.-.--..--.-.-";
			char mode[14] = "";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(5, validate_data(input, mode, temp, argv, argc));
		}

		TEST_METHOD(IncorrectDecryptionMode_WithPause_More1000Symbols)
		{
			char input[MAX_INPUT_LENGTH] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			char mode[14] = "-\npause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(6, validate_data(input, mode, temp, argv, argc));
		}
		TEST_METHOD(IncorrectDecryptionMode_WithPause_CharacterLengthMoreAlphabetLength)
		{
			char input[MAX_INPUT_LENGTH] = ".-.--.-.----.";
			char mode[14] = "pause";
			char temp[2] = "";
			char* argv[] = { "program_name", input, "output.txt" };

			Assert::AreEqual(6, validate_data(input, mode, temp, argv, argc));
		}
	};
}
