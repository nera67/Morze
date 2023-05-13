#include <stdio.h>
#include <string.h>
#include "Header.h"
#include <locale.h>
#include <math.h>


#pragma warning(disable : 4996)

int main()
{
    setlocale(LC_ALL, "Rus");

    // -.-----..-..--...-.-..-...-.
    char input[MAX_INPUT_LENGTH] = ".--.. - ....--. - ";
    char output[MAX_INPUT_LENGTH] = "";
    char mode[14];
    int result;

    convert_without_pause(input, strlen(input), 0, output);

    return 0;

    /*
    // Ввод сообщения и режима расшифровки
    printf("Введите сообщение на языке Морзе: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = 0; // удаляем лишний перенос строки
    printf("Введите режим расшифровки (pause/without_pause): ");
    scanf_s("%s", mode);
    // Проверка корректности входных данных
    result = validate_data(input, mode);
    if (result != 0)
    {
        printf("Ошибка: некорректные входные данные (код %d)\n", result);
        return 1;
    }
    // Расшифровка сообщения
    if (strcmp(mode, WITH_PAUSE) == 0)
    {
        convert_with_pause(input, output);
    }
    else if (strcmp(mode, WITHOUT_PAUSE) == 0)
    {
        convert_without_pause(input, output);
    }
    // Вывод результата
    print_result(output);
    return 0;
    */
}
int validate_data(char input[MAX_INPUT_LENGTH], char mode[14])
{
    int input_length = strlen(input);
    // Проверка на длину сообщения
    if (input_length == 0 || input_length > MAX_INPUT_LENGTH - 1)
    {
        return 1;
    }
    // Проверка на режим расшифровки
    if (strcmp(mode, WITH_PAUSE) != 0 && strcmp(mode, WITHOUT_PAUSE) != 0)
    {
        return 2;
    }
    // Проверка на корректность символов сообщения
    for (int i = 0; i < input_length; i++)
    {
        if (input[i] != '.' && input[i] != '-' && input[i] != ' ')
        {
            return 3;
        }
    }
    return 0;
}

void convert_with_pause(char input[MAX_INPUT_LENGTH], char output[MAX_INPUT_LENGTH][MAX_INPUT_LENGTH])
{
    int output_index = 0;
    char symbol[MAX_MORSE_LENGTH];
    int symbol_length = 0;
    char* prev_char = input;
    char* cur_char = input;
    
    while (strcmp(cur_char, " ") != 0)
    {
        cur_char = strstr(cur_char + 1, " ");
        strncpy(symbol, prev_char + 1, cur_char - prev_char - 1);
        *(symbol + (cur_char - prev_char - 1)) = '\0';
        int index = convert_symbol(symbol, morse_alphabet);
        strncpy(output[0] + output_index, russian_alphabet + index, 1);

        prev_char = cur_char;
        output_index++;
        strcpy(symbol, "\0");
    }

    *(output[0] + output_index) = '\0';
}

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
            int symbol_index = convert_symbol(symbol, morse_alphabet);
            
            if (symbol_index >= 0)
            {
                char newOutput[MAX_INPUT_LENGTH];
                strcpy(newOutput, output);

                char russian_symbol[2];
                strncpy(russian_symbol, russian_alphabet + symbol_index, 1);
                russian_symbol[1] = '\0';
                strcat(newOutput, russian_symbol);
                convert_without_pause(input, inputLength, curPos + n, newOutput);
            }

            n--;
        }
    }

    else
    {
        printf("%s\n", output);
    }
}

int convert_symbol(char symbol[MAX_MORSE_LENGTH], char alphabet[MAX_SYMBOLS][MAX_MORSE_LENGTH])
{
    int index = - 1;

    for (int i = 0; i < MAX_SYMBOLS && index == - 1; i++)
    {
        if (strcmp(symbol, alphabet[i]) == 0)
        {
            index = i;
        }
    }

    return index;
}
