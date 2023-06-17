#include "pch.h"
#include "CppUnitTest.h"
#include <locale.h>
#include "../MorzeDecode/Header.h"
#pragma warning(disable : 4996)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void get_result(char output[][MAX_INPUT_LENGTH], int count)
{
	FILE* stream;
	stream = fopen("output.txt", "r");

	for (int i = 0; i < count; i++) {
		fgets(output[i], MAX_INPUT_LENGTH - 1, stream);
	}

	fclose(stream);
}

namespace ConvertWithoutPauseTest
{
	TEST_CLASS(ConvertWithoutPauseTest)
	{
	public:
		
		TEST_METHOD(OneDash)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 1;
			char expected_result[count][MAX_INPUT_LENGTH] = { "Т\n" };
			char result[count][MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = "-";

			convert_without_pause(input, strlen(input), 0, output);
			get_result(result, count);

			for (int i = 0; i < count; i++)
			{
				Assert::AreEqual(0, strcmp(result[i], expected_result[i]));
			}
		}

		TEST_METHOD(OnePoint)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 1;
			char expected_result[count][MAX_INPUT_LENGTH] = { "Е\n" };
			char result[count][MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = ".";

			convert_without_pause(input, strlen(input), 0, output);
			get_result(result, count);

			for (int i = 0; i < count; i++)
			{
				Assert::AreEqual(0, strcmp(result[i], expected_result[i]));
			}
		}

		TEST_METHOD(ManySymbols)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 212;
			char expected_result[count][MAX_INPUT_LENGTH] = { "ЦПЕ\n", "ЦВИ\n", "ЦВЕЕ\n", "ЦАД\n", "ЦАНЕ\n", "ЦАТИ\n", "ЦАТЕЕ\n", "ЦЕЗ\n", "ЦЕГЕ\n", "ЦЕМИ\n", "ЦЕМЕЕ\n", "ЦЕТД\n", "ЦЕТНЕ\n", "ЦЕТТИ\n", "ЦЕТТЕЕ\n", "К?\n", "КЮИ\n", "КЮЕЕ\n", "КУД\n", "КУНЕ\n", "КУТИ\n", "КУТЕЕ\n", "КИЗ\n", "КИГЕ\n", "КИМИ\n", "КИМЕЕ\n", "КИТД\n", "КИТНЕ\n", "КИТТИ\n", "КИТТЕЕ\n", "КЕПЕ\n", "КЕВИ\n", "КЕВЕЕ\n", "КЕАД\n", "КЕАНЕ\n", "КЕАТИ\n", "КЕАТЕЕ\n", "КЕЕЗ\n", "КЕЕГЕ\n", "КЕЕМИ\n", "КЕЕМЕЕ\n", "КЕЕТД\n", "КЕЕТНЕ\n", "КЕЕТТИ\n", "КЕЕТТЕЕ\n", "НЬД\n", "НЬНЕ\n", "НЬТИ\n", "НЬТЕЕ\n", "НДЗ\n", "НДГЕ\n", "НДМИ\n", "НДМЕЕ\n", "НДТД\n", "НДТНЕ\n", "НДТТИ\n", "НДТТЕЕ\n", "ННПЕ\n", "ННВИ\n", "ННВЕЕ\n", "ННАД\n", "ННАНЕ\n", "ННАТИ\n", "ННАТЕЕ\n", "ННЕЗ\n", "ННЕГЕ\n", "ННЕМИ\n", "ННЕМЕЕ\n", "ННЕТД\n", "ННЕТНЕ\n", "ННЕТТИ\n", "ННЕТТЕЕ\n", "НТ?\n", "НТЮИ\n", "НТЮЕЕ\n", "НТУД\n", "НТУНЕ\n", "НТУТИ\n", "НТУТЕЕ\n", "НТИЗ\n", "НТИГЕ\n", "НТИМИ\n", "НТИМЕЕ\n", "НТИТД\n", "НТИТНЕ\n", "НТИТТИ\n", "НТИТТЕЕ\n", "НТЕПЕ\n", "НТЕВИ\n", "НТЕВЕЕ\n", "НТЕАД\n", "НТЕАНЕ\n", "НТЕАТИ\n", "НТЕАТЕЕ\n", "НТЕЕЗ\n", "НТЕЕГЕ\n", "НТЕЕМИ\n", "НТЕЕМЕЕ\n", "НТЕЕТД\n", "НТЕЕТНЕ\n", "НТЕЕТТИ\n", "НТЕЕТТЕЕ\n", "ТЛЗ\n", "ТЛГЕ\n", "ТЛМИ\n", "ТЛМЕЕ\n", "ТЛТД\n", "ТЛТНЕ\n", "ТЛТТИ\n", "ТЛТТЕЕ\n", "ТРПЕ\n", "ТРВИ\n", "ТРВЕЕ\n", "ТРАД\n", "ТРАНЕ\n", "ТРАТИ\n", "ТРАТЕЕ\n", "ТРЕЗ\n", "ТРЕГЕ\n", "ТРЕМИ\n", "ТРЕМЕЕ\n", "ТРЕТД\n", "ТРЕТНЕ\n", "ТРЕТТИ\n", "ТРЕТТЕЕ\n", "ТА?\n", "ТАЮИ\n", "ТАЮЕЕ\n", "ТАУД\n", "ТАУНЕ\n", "ТАУТИ\n", "ТАУТЕЕ\n", "ТАИЗ\n", "ТАИГЕ\n", "ТАИМИ\n", "ТАИМЕЕ\n", "ТАИТД\n", "ТАИТНЕ\n", "ТАИТТИ\n", "ТАИТТЕЕ\n", "ТАЕПЕ\n", "ТАЕВИ\n", "ТАЕВЕЕ\n", "ТАЕАД\n", "ТАЕАНЕ\n", "ТАЕАТИ\n", "ТАЕАТЕЕ\n", "ТАЕЕЗ\n", "ТАЕЕГЕ\n", "ТАЕЕМИ\n", "ТАЕЕМЕЕ\n", "ТАЕЕТД\n", "ТАЕЕТНЕ\n", "ТАЕЕТТИ\n", "ТАЕЕТТЕЕ\n", "ТЕЬД\n", "ТЕЬНЕ\n", "ТЕЬТИ\n", "ТЕЬТЕЕ\n", "ТЕДЗ\n", "ТЕДГЕ\n", "ТЕДМИ\n", "ТЕДМЕЕ\n", "ТЕДТД\n", "ТЕДТНЕ\n", "ТЕДТТИ\n", "ТЕДТТЕЕ\n", "ТЕНПЕ\n", "ТЕНВИ\n", "ТЕНВЕЕ\n", "ТЕНАД\n", "ТЕНАНЕ\n", "ТЕНАТИ\n", "ТЕНАТЕЕ\n", "ТЕНЕЗ\n", "ТЕНЕГЕ\n", "ТЕНЕМИ\n", "ТЕНЕМЕЕ\n", "ТЕНЕТД\n", "ТЕНЕТНЕ\n", "ТЕНЕТТИ\n", "ТЕНЕТТЕЕ\n", "ТЕТ?\n", "ТЕТЮИ\n", "ТЕТЮЕЕ\n", "ТЕТУД\n", "ТЕТУНЕ\n", "ТЕТУТИ\n", "ТЕТУТЕЕ\n", "ТЕТИЗ\n", "ТЕТИГЕ\n", "ТЕТИМИ\n", "ТЕТИМЕЕ\n", "ТЕТИТД\n", "ТЕТИТНЕ\n", "ТЕТИТТИ\n", "ТЕТИТТЕЕ\n", "ТЕТЕПЕ\n", "ТЕТЕВИ\n", "ТЕТЕВЕЕ\n", "ТЕТЕАД\n", "ТЕТЕАНЕ\n", "ТЕТЕАТИ\n", "ТЕТЕАТЕЕ\n", "ТЕТЕЕЗ\n", "ТЕТЕЕГЕ\n", "ТЕТЕЕМИ\n", "ТЕТЕЕМЕЕ\n", "ТЕТЕЕТД\n", "ТЕТЕЕТНЕ\n", "ТЕТЕЕТТИ\n", "ТЕТЕЕТТЕЕ\n" };
			char result[count][MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = "-.-..--..";

			convert_without_pause(input, strlen(input), 0, output);
			get_result(result, count);
			for (int i = 0; i < count; i++)
			{
				Assert::AreEqual(0, strcmp(result[i], expected_result[i]));
			}
		}

		TEST_METHOD(OnlyDashs)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 61;
			char expected_result[count][MAX_INPUT_LENGTH] = { "0М\n", "0ТТ\n", "ШО\n", "ШМТ\n", "ШТМ\n", "ШТТТ\n", "ОШ\n", "ООТ\n", "ОММ\n", "ОМТТ\n", "ОТО\n", "ОТМТ\n", "ОТТМ\n", "ОТТТТ\n", "М0\n", "МШТ\n", "МОМ\n", "МОТТ\n", "ММО\n", "МММТ\n", "ММТМ\n", "ММТТТ\n", "МТШ\n", "МТОТ\n", "МТММ\n", "МТМТТ\n", "МТТО\n", "МТТМТ\n", "МТТТМ\n", "МТТТТТ\n", "Т0Т\n", "ТШМ\n", "ТШТТ\n", "ТОО\n", "ТОМТ\n", "ТОТМ\n", "ТОТТТ\n", "ТМШ\n", "ТМОТ\n", "ТМММ\n", "ТММТТ\n", "ТМТО\n", "ТМТМТ\n", "ТМТТМ\n", "ТМТТТТ\n", "ТТ0\n", "ТТШТ\n", "ТТОМ\n", "ТТОТТ\n", "ТТМО\n", "ТТММТ\n", "ТТМТМ\n", "ТТМТТТ\n", "ТТТШ\n", "ТТТОТ\n", "ТТТММ\n", "ТТТМТТ\n", "ТТТТО\n", "ТТТТМТ\n", "ТТТТТМ\n", "ТТТТТТТ\n" };
			char result[count][MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = "-------";

			convert_without_pause(input, strlen(input), 0, output);
			get_result(result, count);
			for (int i = 0; i < count; i++)
			{
				Assert::AreEqual(0, strcmp(result[i], expected_result[i]));
			}
		}

		TEST_METHOD(OblyPoints)
		{
			setlocale(LC_ALL, "Rus");

			FILE* stream;
			stream = fopen("output.txt", "w");
			fclose(stream);

			const int count = 236;
			char expected_result[count][MAX_INPUT_LENGTH] = { "5Х\n", "5СЕ\n", "5ИИ\n", "5ИЕЕ\n", "5ЕС\n", "5ЕИЕ\n", "5ЕЕИ\n", "5ЕЕЕЕ\n", "Х5\n", "ХХЕ\n", "ХСИ\n", "ХСЕЕ\n", "ХИС\n", "ХИИЕ\n", "ХИЕИ\n", "ХИЕЕЕ\n", "ХЕХ\n", "ХЕСЕ\n", "ХЕИИ\n", "ХЕИЕЕ\n", "ХЕЕС\n", "ХЕЕИЕ\n", "ХЕЕЕИ\n", "ХЕЕЕЕЕ\n", "С5Е\n", "СХИ\n", "СХЕЕ\n", "ССС\n", "ССИЕ\n", "ССЕИ\n", "ССЕЕЕ\n", "СИХ\n", "СИСЕ\n", "СИИИ\n", "СИИЕЕ\n", "СИЕС\n", "СИЕИЕ\n", "СИЕЕИ\n", "СИЕЕЕЕ\n", "СЕ5\n", "СЕХЕ\n", "СЕСИ\n", "СЕСЕЕ\n", "СЕИС\n", "СЕИИЕ\n", "СЕИЕИ\n", "СЕИЕЕЕ\n", "СЕЕХ\n", "СЕЕСЕ\n", "СЕЕИИ\n", "СЕЕИЕЕ\n", "СЕЕЕС\n", "СЕЕЕИЕ\n", "СЕЕЕЕИ\n", "СЕЕЕЕЕЕ\n", "И5И\n", "И5ЕЕ\n", "ИХС\n", "ИХИЕ\n", "ИХЕИ\n", "ИХЕЕЕ\n", "ИСХ\n", "ИССЕ\n", "ИСИИ\n", "ИСИЕЕ\n", "ИСЕС\n", "ИСЕИЕ\n", "ИСЕЕИ\n", "ИСЕЕЕЕ\n", "ИИ5\n", "ИИХЕ\n", "ИИСИ\n", "ИИСЕЕ\n", "ИИИС\n", "ИИИИЕ\n", "ИИИЕИ\n", "ИИИЕЕЕ\n", "ИИЕХ\n", "ИИЕСЕ\n", "ИИЕИИ\n", "ИИЕИЕЕ\n", "ИИЕЕС\n", "ИИЕЕИЕ\n", "ИИЕЕЕИ\n", "ИИЕЕЕЕЕ\n", "ИЕ5Е\n", "ИЕХИ\n", "ИЕХЕЕ\n", "ИЕСС\n", "ИЕСИЕ\n", "ИЕСЕИ\n", "ИЕСЕЕЕ\n", "ИЕИХ\n", "ИЕИСЕ\n", "ИЕИИИ\n", "ИЕИИЕЕ\n", "ИЕИЕС\n", "ИЕИЕИЕ\n", "ИЕИЕЕИ\n", "ИЕИЕЕЕЕ\n", "ИЕЕ5\n", "ИЕЕХЕ\n", "ИЕЕСИ\n", "ИЕЕСЕЕ\n", "ИЕЕИС\n", "ИЕЕИИЕ\n", "ИЕЕИЕИ\n", "ИЕЕИЕЕЕ\n", "ИЕЕЕХ\n", "ИЕЕЕСЕ\n", "ИЕЕЕИИ\n", "ИЕЕЕИЕЕ\n", "ИЕЕЕЕС\n", "ИЕЕЕЕИЕ\n", "ИЕЕЕЕЕИ\n", "ИЕЕЕЕЕЕЕ\n", "Е5С\n", "Е5ИЕ\n", "Е5ЕИ\n", "Е5ЕЕЕ\n", "ЕХХ\n", "ЕХСЕ\n", "ЕХИИ\n", "ЕХИЕЕ\n", "ЕХЕС\n", "ЕХЕИЕ\n", "ЕХЕЕИ\n", "ЕХЕЕЕЕ\n", "ЕС5\n", "ЕСХЕ\n", "ЕССИ\n", "ЕССЕЕ\n", "ЕСИС\n", "ЕСИИЕ\n", "ЕСИЕИ\n", "ЕСИЕЕЕ\n", "ЕСЕХ\n", "ЕСЕСЕ\n", "ЕСЕИИ\n", "ЕСЕИЕЕ\n", "ЕСЕЕС\n", "ЕСЕЕИЕ\n", "ЕСЕЕЕИ\n", "ЕСЕЕЕЕЕ\n", "ЕИ5Е\n", "ЕИХИ\n", "ЕИХЕЕ\n", "ЕИСС\n", "ЕИСИЕ\n", "ЕИСЕИ\n", "ЕИСЕЕЕ\n", "ЕИИХ\n", "ЕИИСЕ\n", "ЕИИИИ\n", "ЕИИИЕЕ\n", "ЕИИЕС\n", "ЕИИЕИЕ\n", "ЕИИЕЕИ\n", "ЕИИЕЕЕЕ\n", "ЕИЕ5\n", "ЕИЕХЕ\n", "ЕИЕСИ\n", "ЕИЕСЕЕ\n", "ЕИЕИС\n", "ЕИЕИИЕ\n", "ЕИЕИЕИ\n", "ЕИЕИЕЕЕ\n", "ЕИЕЕХ\n", "ЕИЕЕСЕ\n", "ЕИЕЕИИ\n", "ЕИЕЕИЕЕ\n", "ЕИЕЕЕС\n", "ЕИЕЕЕИЕ\n", "ЕИЕЕЕЕИ\n", "ЕИЕЕЕЕЕЕ\n", "ЕЕ5И\n", "ЕЕ5ЕЕ\n", "ЕЕХС\n", "ЕЕХИЕ\n", "ЕЕХЕИ\n", "ЕЕХЕЕЕ\n", "ЕЕСХ\n", "ЕЕССЕ\n", "ЕЕСИИ\n", "ЕЕСИЕЕ\n", "ЕЕСЕС\n", "ЕЕСЕИЕ\n", "ЕЕСЕЕИ\n", "ЕЕСЕЕЕЕ\n", "ЕЕИ5\n", "ЕЕИХЕ\n", "ЕЕИСИ\n", "ЕЕИСЕЕ\n", "ЕЕИИС\n", "ЕЕИИИЕ\n", "ЕЕИИЕИ\n", "ЕЕИИЕЕЕ\n", "ЕЕИЕХ\n", "ЕЕИЕСЕ\n", "ЕЕИЕИИ\n", "ЕЕИЕИЕЕ\n", "ЕЕИЕЕС\n", "ЕЕИЕЕИЕ\n", "ЕЕИЕЕЕИ\n", "ЕЕИЕЕЕЕЕ\n", "ЕЕЕ5Е\n", "ЕЕЕХИ\n", "ЕЕЕХЕЕ\n", "ЕЕЕСС\n", "ЕЕЕСИЕ\n", "ЕЕЕСЕИ\n", "ЕЕЕСЕЕЕ\n", "ЕЕЕИХ\n", "ЕЕЕИСЕ\n", "ЕЕЕИИИ\n", "ЕЕЕИИЕЕ\n", "ЕЕЕИЕС\n", "ЕЕЕИЕИЕ\n", "ЕЕЕИЕЕИ\n", "ЕЕЕИЕЕЕЕ\n", "ЕЕЕЕ5\n", "ЕЕЕЕХЕ\n", "ЕЕЕЕСИ\n", "ЕЕЕЕСЕЕ\n", "ЕЕЕЕИС\n", "ЕЕЕЕИИЕ\n", "ЕЕЕЕИЕИ\n", "ЕЕЕЕИЕЕЕ\n", "ЕЕЕЕЕХ\n", "ЕЕЕЕЕСЕ\n", "ЕЕЕЕЕИИ\n", "ЕЕЕЕЕИЕЕ\n", "ЕЕЕЕЕЕС\n", "ЕЕЕЕЕЕИЕ\n", "ЕЕЕЕЕЕЕИ\n", "ЕЕЕЕЕЕЕЕЕ\n" };
			char result[count][MAX_INPUT_LENGTH];
			char output[MAX_INPUT_LENGTH] = "";
			char input[MAX_INPUT_LENGTH] = ".........";

			convert_without_pause(input, strlen(input), 0, output);
			get_result(result, count);
			for (int i = 0; i < count; i++)
			{
				Assert::AreEqual(0, strcmp(result[i], expected_result[i]));
			}
		}
	};
}
