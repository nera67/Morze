#pragma once

#define MAX_INPUT_LENGTH 1001
#define MAX_MORSE_LENGTH 7
#define MAX_SYMBOLS 50
#define PAUSE "pause"
#define WITHOUT_PAUSE "without_pause"

/*!
* Проверка и считывание сообщения из файла
*\param [in,out] input - Сообщение из файла input.txt
*\param [in,out] mode - Режим расшифровки
*\param [in,out] temp - Если что-то после режима расшифровки было написано, оно попадёт в эту переменную
*\return возвращает NoError, если ошибок нет, иначе - OutputFileError
*/
int parse_input_file(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2], char* argv[], const int argc);

/*!
* Проверка входных данных
*\param [in,out] input - Сообщение из файла input.txt
*\param [in] mode - Режим расшифровки
*\param [in] temp - Если что-то после режима расшифровки было написано, оно попадёт в эту переменную
*\return возвращает NoError, если ошибок нет, иначе - один из вариантов error_type
*/
int validate_data(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2], char* argv[], const int argc);

/*!
* Расшифровка с паузой
*\param [in] input - Сообщение из файла input.txt
*/
void convert_with_pause(char input[MAX_INPUT_LENGTH], char* argv[]);

/*!
* Расшифровка без паузы
*\param [in] input - Сообщение из файла input.txt
*\param [in] inputLength - Длина сообщение из файла input.txt
*\param [in] curPos - Текущая позиция в input
*\param [in] output - Результат функции
*/
void convert_without_pause(char input[MAX_INPUT_LENGTH], int inputLength, int curPos, char output[MAX_INPUT_LENGTH], char* argv[]);

/*!
* Вывода результата в файл
*\param [in] output - Результат, который будет записан в файл output.txt
*/
void print_result(char output[MAX_INPUT_LENGTH], char* argv[]);