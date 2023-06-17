#include "pch.h"
#include "CppUnitTest.h"
#include "../MorzeDecode/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
			Assert::AreEqual(-1, validate_data(input, mode, temp));
		}
		TEST_METHOD(NoError_WithPause)
		{
			char input[MAX_INPUT_LENGTH] = "-.- --- .. .-. --";
			char mode[14] = "pause";
			char temp[2] = "";
			Assert::AreEqual(- 1, validate_data(input, mode, temp));
		}

		TEST_METHOD(InputFileEmpty)
		{
			char input[MAX_INPUT_LENGTH] = "";
			char mode[14] = "";
			char temp[2] = "";
			Assert::AreEqual(2, validate_data(input, mode, temp));
		}

		TEST_METHOD(InvalidCharacters_WithPause_NotPointNotDash)
		{
			char input[MAX_INPUT_LENGTH] = "-.a --s 3. .4. -*";
			char mode[14] = "pause";
			char temp[2] = "";
			Assert::AreEqual(3, validate_data(input, mode, temp));
		}
		TEST_METHOD(InvalidCharacters_WithoutPause_NotPointNotDash)
		{
			char input[MAX_INPUT_LENGTH] = "-.a--.s3.4.-*";
			char mode[14] = "without_pause";
			char temp[2] = "";
			Assert::AreEqual(3, validate_data(input, mode, temp));
		}

		TEST_METHOD(StringSizeOutOfRange_WithPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "pause";
			char temp[2] = "p";
			Assert::AreEqual(4, validate_data(input, mode, temp));
		}
		TEST_METHOD(StringSizeOutOfRange_WithoutPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "without_pause";
			char temp[2] = "p";
			Assert::AreEqual(4, validate_data(input, mode, temp));
		}
		TEST_METHOD(StringSizeOutOfRange_WithoutPause_More1000Symbols)
		{
			char input[MAX_INPUT_LENGTH] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			char mode[14] = "-\nwithout_pau";
			char temp[2] = "s";
			Assert::AreEqual(4, validate_data(input, mode, temp));
		}

		TEST_METHOD(NoDecryptionMode_WithPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "";
			char temp[2] = "";
			Assert::AreEqual(5, validate_data(input, mode, temp));
		}
		TEST_METHOD(NoDecryptionMode_WithoutPause_More2StringsInInputFile)
		{
			char input[MAX_INPUT_LENGTH] = "-. -.- -. .--. -.-";
			char mode[14] = "";
			char temp[2] = "";
			Assert::AreEqual(5, validate_data(input, mode, temp));
		}

		TEST_METHOD(IncorrectDecryptionMode_WithPause_More1000Symbols)
		{
			char input[MAX_INPUT_LENGTH] = "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
			char mode[14] = "-\npause";
			char temp[2] = "";
			Assert::AreEqual(6, validate_data(input, mode, temp));
		}
		TEST_METHOD(IncorrectDecryptionMode_WithPause_CharacterLengthMoreAlphabetLength)
		{
			char input[MAX_INPUT_LENGTH] = ".-.--.-.----.";
			char mode[14] = "pause";
			char temp[2] = "";
			Assert::AreEqual(6, validate_data(input, mode, temp));
		}
	};
}
