#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <map>
#include <iostream>
#include "Header.h"

#pragma warning(disable : 4996)

using namespace std;

// Ошибки
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

// Алфавит
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


int main(const int argc, char* argv[])
{
    // Поддержка русского языка
    setlocale(LC_ALL, "Rus");

    char input[MAX_INPUT_LENGTH] = "";      // Сообщение из файла input.txt
    char output[MAX_INPUT_LENGTH] = "";     // Расшифрованное сообщение, которое будет записано в output.txt
    char mode[14] = "";                     // Режим расшифровки
    char temp[2] = "";                      // Если что-то после режима расшифровки было написано, оно попадёт в эту переменную
    int result;                             // Результат проверок

    // Проверка и считывание сообщения из файла
    result = parse_input_file(input, mode, temp, argv, argc);

    // Если удалось считать сообщение
    if (result == NoError) 
    {
        // Проверка считанного файла
        result = validate_data(input, mode, temp, argv, argc);

        // Если сообщение не имеет ошибок
        if (result == NoError)
        {
            // Если режим расшифровки - без паузы
            if (strcmp(mode, WITHOUT_PAUSE) == 0)
            {
                // Использовать функцию - расшифровка без паузы
                convert_without_pause(input, strlen(input), 0, output, argv);
            }
            // Иначе
            else
            {
                // Использовать функцию - расшифровка c паузой
                convert_with_pause(input, argv);
            }
        }
        else
        {
            // Вывод ошибки
            printf("%d", result);
        }
    }
    else
    {
        // Вывод ошибки
        printf("%d", result);
    }
    return 0;
}

// Проверка и считывание сообщения из файла
int parse_input_file(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2], char* argv[], const int argc)
{
    FILE* stream;

    // Проверка на наличие входного файла и доступа к нему
    if (argc == 1)
    {
        return InputFileError;
    }
    else if (fopen_s(&stream, argv[1], "r") == 0)
    {
        fgets(input, MAX_INPUT_LENGTH - 1, stream); // Считывание сообщения
        fgets(mode, 14, stream);    // Считывание режима расшифровки

        // Если сообщение содержит 1000 символов, то
        if (strcmp(mode, "\n") == 0)
        {
            fgets(mode, 14, stream);    // Считываем режим расшифровки ещё раз
        }

        fgets(temp, 2, stream); // Считываем оставшиеся символы
        fclose(stream);
    }
    else
    {
        // Вывод ошибки
        return InputFileError;
    }

    // Вывод ошибки
    return NoError;
}

// Проверка входных данных
int validate_data(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2], char* argv[], const int argc)
{
    // Проверка возможности создания выходного файла
    FILE* stream;
    int i = 0;

    // Проверка на наличие выходного файла и доступа к нему
    if (argc == 2)
    {
        return OutputFileError;
    }
    else if (fopen_s(&stream, argv[2], "w") == 0)
    {
        fclose(stream);
    }


    if (strcmp(input, "") == 0) {
        return InputFileEmpty;
        printf("%c", "Входной файл пуст");
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

// Расшифровка с паузой
void convert_with_pause(char input[MAX_INPUT_LENGTH], char* argv[])
{
    char output[MAX_INPUT_LENGTH] = ""; // Результат работы функции
    char symbol[MAX_MORSE_LENGTH];      // Текущая комбинация символов Морзе между пробелами
    int output_index = 0;               // Номер последнего записанного символа в output
    int left_index = 0;                 // Начало комбинации символов Морзе
    bool looping = true;                // Дошли ли да конца сообщения
    bool error_occurred = false;        // Произошла ли ошибка во время расшифровки

    // Пока не дошли до конца сообщения и не встретили недопустимый символ
    for (int i = 0; looping && error_occurred == false; i++)
    {
        // Если длина символа превышает максимальную длину символа в Морзе
        if (i - left_index >= MAX_MORSE_LENGTH)
        {
            // То ошибка найдена
            error_occurred = true;
        }

        // Если дошли до конца слова в сообщении
        else if (input[i] == ' ' || input[i] == '\0')
        {
            looping = input[i] != '\0';                             // Дошли ли до конца сообщения
            strncpy(symbol, input + left_index, i - left_index);    // Запоминаем букву на Морзе
            *(symbol + i - left_index) = '\0';                      // Ставим нуль-символ

            // Если в Морзе существует такая последовательность символов
            if (alphabet.count(symbol) != 0)
            {
                *(output + output_index) = alphabet[symbol];    // Добавляем новую букву к результату работы функции (output)
                left_index = i + 1;                             // Переходим в начало следующей комбинации символов Морзе
                output_index++;                                 // Увеличиваем номер символа на 1
            }

            // Иначе
            else
            {
                // Ошибка найдена
                error_occurred = true;
            }
        }
    }
    // Если ошибка найдена
    if (error_occurred)
    {
        // Печатаем ошибку
        printf("%d", InvalidCharacters);
    }
    // Иначе
    else
    {
        // Сохраняем результат
        print_result(output, argv);
    }
}

// Расшифровка без паузы
void convert_without_pause(char input[MAX_INPUT_LENGTH], int inputLength, int curPos, char output[MAX_INPUT_LENGTH], char* argv[])
{
    // Если не дошли до конца сообщения
    if (curPos < inputLength)
    {
        
        int n = inputLength - curPos >= MAX_MORSE_LENGTH ? MAX_MORSE_LENGTH - 1 : inputLength - curPos;
        
        //int n = inputLength - curPos;   // Максимальная длина комбинации символов Морзе

        //// Если максимальная длина комбинации символов Морзе больше или равна MAX_MORSE_LENGTH, то
        //if (n >= MAX_MORSE_LENGTH)
        //{
        //    // Уменьшаем до MAX_MORSE_LENGTH - 1
        //    n = MAX_MORSE_LENGTH - 1;
        //}
        // Для всех длин символов в Морзе
        for (int length = n; length > 0; length--)
        {
            char symbol[MAX_MORSE_LENGTH];              // Текущий символ
            strncpy(symbol, input + curPos, length);    // Запоминаем букву на Морзе
            symbol[length] = '\0';                      // Ставим нуль-символ

            // Если такой символ есть в Морзе
            if (alphabet.count(symbol) != 0)
            {
                char newOutput[MAX_INPUT_LENGTH];   // Новый результат функции в данной итерации рекурсии
                strcpy(newOutput, output);          // Копируем уже найденный результат

                char russian_symbol[2];                 // Переведённый символ
                russian_symbol[0] = alphabet[symbol];   // Запоминаем переведённый символ
                russian_symbol[1] = '\0';               // Ставим нуль-символ
                strcat(newOutput, russian_symbol);      // Добавляем новый символ к текущему результату функции

                // Рекурсивно вызываем функцию
                convert_without_pause(input, inputLength, curPos + length, newOutput, argv);
            }
        }
    }
    // Иначе
    else
    {
        // Сохраняем результат
        print_result(output, argv);
    }
}

// Вывода результата в файл
void print_result(char output[MAX_INPUT_LENGTH], char* argv[])
{
     FILE* mf = fopen(argv[2], "a");
     fprintf(mf, "%s\n", output);
     fclose(mf);
}