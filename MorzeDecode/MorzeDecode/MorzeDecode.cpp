#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <map>
#include <iostream>
#include "Header.h"

#pragma warning(disable : 4996)

using namespace std;

enum error_type
{
    NoError = -1,
    OutputFileError,			// Невозможно создать указанный выходной файл.										0
    InputFileError,				// Указанный входной файл не существует или к нему нет доступа.						1
    InputFileEmpty,				// Входной файл пуст.																2
    InvalidCharacters,			// Входной файл содержит недопустимые символы.										3
    StringSizeOutOfRange,		// Размерность сообщения во входном файле находится вне допустимого диапазона.		4
    NoDecryptionMode,			// Отсутствует указание режима расшифровки.											5
    IncorrectDecryptionMode		// Выбран некорректный режим расшифровки.											6
};

map <string, char> alphabet = {
    {".-", 'А'}, {"-...", 'Б'}, {".--", 'В'}, {"--.", 'Г'}, {"-..", 'Д'},
    {".", 'Е'}, {"...-", 'Ж'}, {"--..", 'З'}, {"..", 'И'}, {".---", 'Й'},
    {"-.-", 'К'}, {".-..", 'Л'}, {"--", 'М'}, {"-.", 'Н'}, {"---", 'О'},
    {".--.", 'П'}, {".-.", 'Р'}, {"...", 'С'}, {"-", 'Т'}, {"..-", 'У'},
    {"..-.", 'Ф'}, {"....", 'Х'}, {"-.-.", 'Ц'}, {"---.", 'Ч'}, {"----", 'Ш'},
    {"--.-", 'Щ'}, {"--.--", 'Ъ'}, {"-.--", 'Ы'}, {"-..-", 'Ь'}, {"..-..", 'Э'},
    {"..--", 'Ю'}, {".-.-", 'Я'}, {"-.-.--", '!'}, {"..--..", '?'}, {"-.--.", '('},
    {"-.--.-", ')'}, {"---...", ':'}, {"-.-.-.", ';'}, {"-..-.", '/'}, {".--.-.", '@'},
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'},
    {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----", '9' }
};


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    char input[MAX_INPUT_LENGTH] = "";
    char output[MAX_INPUT_LENGTH] = "";
    char mode[14] = "";
    char temp[2] = "";
    int result;

    result = parse_input_file(input, mode, temp);

    if (result == NoError) {
        result = validate_data(input, mode, temp);

        if (result == NoError)
        {
            if (strcmp(mode, WITHOUT_PAUSE) == 0)
            {
                convert_without_pause(input, strlen(input), 0, output);
            }
            else
            {
                convert_with_pause(input);
            }
        }
        else
        {
            printf("%d", result);
        }
    }

    return 0;
}

int parse_input_file(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2])
{
    FILE* stream;

    if (fopen_s(&stream, "input.txt", "r") == 0) // Проверка на наличие входного файла и доступа к нему
    {
        fgets(input, MAX_INPUT_LENGTH - 1, stream);
        fgets(mode, 14, stream);
        if (strcmp(mode, "\n") == 0)
        {
            fgets(mode, 14, stream);
        }
        fgets(temp, 2, stream);
        fclose(stream);
    }
    else
    {
        return InputFileError;
    }
    return NoError;
}

//Проверка входных данных
int validate_data(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2])
{
    // Проверка возможности создания выходного файла
    FILE* stream;
    int i = 0;

    if (fopen_s(&stream, "output.txt", "w") == 0) // Проверка на наличие выходного файла и доступа к нему
    {
        fclose(stream);
    }
    else
    {
        return OutputFileError;
    }

    if (strcmp(input, "") == 0) {
        return InputFileEmpty;
    }
    if (strcmp(mode, "") == 0) {
        return NoDecryptionMode;
    }
    if (strcmp(temp, "") != 0) {
        return StringSizeOutOfRange;
    }

    // Проверка на корректность символов сообщения
    for (i = 0; input[i] != NULL && input[i] != '\n'; i++)
    {
        if (input[i] != '.' && input[i] != '-' && input[i] != ' ')
        {
            return InvalidCharacters;
        }
    }
    *(input + i) = '\0';

    // Проверка корректности режима расшифровки
    if (strcmp(mode, WITHOUT_PAUSE) == 0)
    {
        bool space_exists = false;
        for (i = 0; input[i] != '\0' && space_exists == false; i++)
        {
            space_exists = input[i] == ' ';
        }
        if (space_exists)
        {
            return IncorrectDecryptionMode;
        }
    }
    else if ((strcmp(mode, PAUSE) == 0))
    {
        int length = strlen(input);
        if (length >= MAX_MORSE_LENGTH && strstr(input, " ") == NULL)
        {
            return IncorrectDecryptionMode;
        }
    }
    else
    {
        return IncorrectDecryptionMode;
    }

    // Всё ок
    return NoError;
}

//Расшифровка с паузой
void convert_with_pause(char input[MAX_INPUT_LENGTH])
{
    char output[MAX_INPUT_LENGTH] = "";
    char symbol[MAX_MORSE_LENGTH];
    int output_index = 0;
    int left_index = 0;
    bool looping = true;
    bool error_occurred = false;

    for (int i = 0; looping && error_occurred == false; i++)
    {
        if (i - left_index >= MAX_MORSE_LENGTH)
        {
            error_occurred = true;
        }
        else if (input[i] == ' ' || input[i] == '\0')
        {
            looping = input[i] != '\0';
            strncpy(symbol, input + left_index, i - left_index);
            *(symbol + i - left_index) = '\0';
            
            if (alphabet.count(symbol) != 0)
            {
                *(output + output_index) = alphabet[symbol];
                left_index = i + 1;
                output_index++;
            }

            else 
            {
                error_occurred = true;
            }
        }
    }

    if (error_occurred)
    {
        printf("%d", InvalidCharacters);
    }
    else
    {
        print_result(output);
    }
}

//Расшифровка без паузы
void convert_without_pause(char input[MAX_INPUT_LENGTH], int inputLength, int curPos, char output[MAX_INPUT_LENGTH])
{
    if (curPos < inputLength)
    {
        int n = inputLength - curPos;
        if (n > 6)
        {
            n = 6;
        }

        while (n > 0)
        {
            char symbol[MAX_MORSE_LENGTH];

            strncpy(symbol, input + curPos, n);
            symbol[n] = '\0';
            
            if (alphabet.count(symbol) != 0)
            {
                char newOutput[MAX_INPUT_LENGTH];
                strcpy(newOutput, output);

                char russian_symbol[2];
                russian_symbol[0] = alphabet[symbol];
                russian_symbol[1] = '\0';
                strcat(newOutput, russian_symbol);
                convert_without_pause(input, inputLength, curPos + n, newOutput);
            }

            n--;
        }
    }

    else
    {
        print_result(output);
    }
}

void print_result(char output[MAX_INPUT_LENGTH])
{
    FILE* mf = fopen("output.txt", "a");
    fprintf(mf, "%s\n", output);
    fclose(mf);
}
