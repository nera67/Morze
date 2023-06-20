#include "pch.h"
#include "CppUnitTest.h"
#include <locale.h>
#include "../MorzeDecode/Header.h"
#pragma warning(disable : 4996)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// MorzeDecode\x64\Debug - output.txt
void get_result(char output[MAX_INPUT_LENGTH])
{
	FILE* stream;
	stream = fopen("output.txt", "r");
	fgets(output, MAX_INPUT_LENGTH - 1, stream);

	fclose(stream);
}

namespace ConvertWithPauseTest
{
	TEST_CLASS(ConvertWithPauseTest)
	{
	public:
		
		TEST_METHOD(OneDash)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			char expected_result[MAX_INPUT_LENGTH] = "Т\n";
			char result[MAX_INPUT_LENGTH];
			char input[MAX_INPUT_LENGTH] = "-";
			char* argv[] = { "program_name", input, "output.txt" };

			convert_with_pause(input, argv);
			get_result(result);

			Assert::AreEqual(0, strcmp(result, expected_result));
		}

		TEST_METHOD(OnePoint)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 1;
			char expected_result[MAX_INPUT_LENGTH] = { "Е\n" };
			char result[MAX_INPUT_LENGTH];
			char input[MAX_INPUT_LENGTH] = ".";
			char* argv[] = { "program_name", input, "output.txt" };

			convert_with_pause(input, argv);
			get_result(result);

			Assert::AreEqual(0, strcmp(result, expected_result));
		}

		TEST_METHOD(ManySymbols)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			char expected_result[MAX_INPUT_LENGTH] = "АЗБУКАМОРЗЕБЫЛАРАЗРАБОТАНАВ1830ХГОДАХАВ1840ХГОДАХУСОВЕРШЕНСТВОВАНА\n";
			char result[MAX_INPUT_LENGTH];
			char input[MAX_INPUT_LENGTH] = ".- --.. -... ..- -.- .- -- --- .-. --.. . -... -.-- .-.. .- .-. .- --.. .-. .- -... --- - .- -. .- .-- .---- ---.. ...-- ----- .... --. --- -.. .- .... .- .-- .---- ---.. ....- ----- .... --. --- -.. .- .... ..- ... --- .-- . .-. ---- . -. ... - .-- --- .-- .- -. .-";
			char* argv[] = { "program_name", input, "output.txt" };

			convert_with_pause(input, argv);
			get_result(result);
			Assert::AreEqual(0, strcmp(result, expected_result));
		}

		TEST_METHOD(OnlyDashs)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			char expected_result[MAX_INPUT_LENGTH] = "ОМТ\n";
			char result[MAX_INPUT_LENGTH];
			char input[MAX_INPUT_LENGTH] = "--- -- -";
			char* argv[] = { "program_name", input, "output.txt" };

			convert_with_pause(input, argv);
			get_result(result);
			Assert::AreEqual(0, strcmp(result, expected_result));
		}

		TEST_METHOD(OnlyPoints)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			char expected_result[MAX_INPUT_LENGTH] = "СИИЕ\n";
			char result[MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = "... .. .. .";
			char* argv[] = { "program_name", input, "output.txt" };

			convert_with_pause(input, argv);
			get_result(result);
			Assert::AreEqual(0, strcmp(result, expected_result));
		}
	};
}
