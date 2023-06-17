#pragma once

#define MAX_INPUT_LENGTH 1001
#define MAX_MORSE_LENGTH 7
#define MAX_SYMBOLS 50
#define PAUSE "pause"
#define WITHOUT_PAUSE "without_pause"

int parse_input_file(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2]);

int validate_data(char input[MAX_INPUT_LENGTH], char mode[14], char temp[2]);

void convert_with_pause(char input[MAX_INPUT_LENGTH]);

void convert_without_pause(char input[MAX_INPUT_LENGTH], int inputLength, int curPos, char output[MAX_INPUT_LENGTH]);

void print_result(char output[MAX_INPUT_LENGTH]);
