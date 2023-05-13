#pragma once

#define MAX_INPUT_LENGTH 1001
#define MAX_MORSE_LENGTH 7
#define MAX_SYMBOLS 50
#define WITH_PAUSE "pause"
#define WITHOUT_PAUSE "without_pause"

enum error_type
{
	NoError = -1,
	InputFileError,
	OutputFileError,
	InputFileEmpty,
	InvalidCharacters,
	StringSizeOutOfRange,
	IncorrectDecryptionMode,
	NoDecryptionMode
};

char morse_alphabet[MAX_SYMBOLS][MAX_MORSE_LENGTH] = {
	".-", "-...", ".--", "--.", "-..", ".", "...-", "--..",
	"..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
	".-.", "...", "-", "..-", "..-.", "....", "-.-.",
	"---.", "----", "--.-", "--.--", "-.--", "-..-",
	"..-..", "..--", ".-.-", "-.-.--", "..--..", "-.--.",
	"-.--.-", "---...", "-.-.-.", "-..-.", ".--.-.",
	"-----", ".----", "..---", "...--", "....-", ".....",
	"-....", "--...", "---..", "----"
};

char russian_alphabet[MAX_SYMBOLS] = {
    'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë',
    'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×',
    'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'Þ', 'ß', '!', '?', '(', ')',
    ':', ';', '/', '@', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 
};


int validate_data(char input[MAX_INPUT_LENGTH], char mode[14]);

void convert_with_pause(char input[MAX_INPUT_LENGTH], char output[MAX_INPUT_LENGTH][MAX_INPUT_LENGTH]);

void convert_without_pause(char input[MAX_INPUT_LENGTH], int inputLength, int curPos, char output[MAX_INPUT_LENGTH]);

int convert_symbol(char symbol[MAX_MORSE_LENGTH], char alphabet[MAX_SYMBOLS][MAX_MORSE_LENGTH]);

void print_result(char output[MAX_INPUT_LENGTH][MAX_INPUT_LENGTH]);
