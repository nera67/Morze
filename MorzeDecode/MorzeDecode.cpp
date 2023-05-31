#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include "Header.h"


#pragma warning(disable : 4996)

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");

    char input[MAX_INPUT_LENGTH] = "";
    char temp[MAX_INPUT_LENGTH] = "";
    char mode[14];

    int result = validate_data(input, mode);

    if (result == NoError)
    {
        if (strcmp(mode, WITHOUT_PAUSE) == 0)
        {
            convert_without_pause(input, strlen(input), 0, temp);
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

    return 0;
}

int validate_data(char input[MAX_INPUT_LENGTH], char mode[14])
{
    // Проверка возможности создание выходного файла и его создание OutputFileError
    FILE* stream;
    char temp[2];
    int i = 0;
    if (fopen_s(&stream, "output.txt", "w") == 0) // Проверка на наличие входного файла и доступа к нему
    {
        fclose(stream);
    }
    else
    {
        return OutputFileError;
    }

    if (fopen_s(&stream, "input.txt", "r") == 0) // Проверка на наличие входного файла и доступа к нему
    {
        if (fgets(input, MAX_INPUT_LENGTH - 1, stream) == NULL) // Проверка на наличие символов сообщения
        {
            return InputFileEmpty;
        }
        if (strcmp(input, "\n") == 0) // Проверка на наличие символов сообщения
        {
            return InputFileEmpty;
        }
        if (fgets(mode, 14, stream) == NULL) // Проверка на наличия режима расшифровки
        {
            return NoDecryptionMode;
        }

        if (strcmp(mode, "\n") == 0)
        {
            if (fgets(mode, 14, stream) == NULL) // Проверка на наличия режима расшифровки
            {
                return NoDecryptionMode;
            }
        }

        if (fgets(temp, 2, stream) != NULL) // Проверка на кол-во символов
        {
            return StringSizeOutOfRange;
        }
        fclose(stream);
    }
    else
    {
        return InputFileError;
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
    else if (!(strcmp(mode, PAUSE) == 0))
    {
        return IncorrectDecryptionMode;
    }

    // Всё ок
    return NoError;
}

void convert_with_pause(char input[MAX_INPUT_LENGTH])
{
    char output[MAX_INPUT_LENGTH] = "";
    char symbol[MAX_MORSE_LENGTH];
    int output_index = 0;
    int left_index = 0;
    //int rus_index = 0;
    bool looping = true;
    bool error_occurred = false;

    //for (; input[i] != '\0' && i - left_index < MAX_MORSE_LENGTH && rus_index != - 1; i++)
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
            //rus_index = convert_symbol(symbol, morse_alphabet);
            //*(output + output_index) = russian_alphabet[rus_index];
            
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

    //if (i - left_index >= MAX_MORSE_LENGTH || rus_index == - 1)
    if (error_occurred)
    {
        printf("%d", InvalidCharacters);
    }
    else
    {
        FILE* mf = fopen("output.txt", "w");
        fprintf(mf, "%s\n", output);
        fclose(mf);
    }
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
            //int symbol_index = convert_symbol(symbol, morse_alphabet);
            
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
        FILE * mf = fopen("output.txt", "a");
        fprintf(mf, "%s\n", output);
        fclose(mf);
    }
}

//int convert_symbol(char symbol[MAX_MORSE_LENGTH], map <string, char> alphabet)
//{
//    int index = - 1;
//
//    for (int i = 0; i < MAX_SYMBOLS && index == - 1; i++)
//    {
//        if (strcmp(symbol, alphabet[i]) == 0)
//        {
//            index = i;
//        }
//    }
//
//    return index;
//}
