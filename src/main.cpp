#include <Arduino.h>
#include <LiquidCrystal.h>
#include <calculate_core.h>
#include <Keypad.h>


LiquidCrystal lcd(49, 48, 47, 43, 42, 41);

const int ROW_SIZE = 4;
const int COL_SIZE = 4;
const int TONE_PIN = A9;

char KEYS[ROW_SIZE][COL_SIZE] = {
	{'+', '-', '*', '/'},
	{'=', '3', '6', '9'},
	{'C', '2', '5', '8'},
	{'0', '1', '4', '7'}
};

byte ROW_PINS[ROW_SIZE] = { 25, 24, 23, 22 };
byte COL_PINS[COL_SIZE] = { 29, 28, 27, 26 };
Keypad keypad = Keypad( makeKeymap(KEYS), ROW_PINS, COL_PINS, ROW_SIZE, COL_SIZE );

void setup() 
{	
	Serial.begin(9600);
	pinMode(TONE_PIN, OUTPUT);
	lcd.begin(16, 2);
	lcd.clear();
}
char last_char = 0;

void loop() 
{
	const int lcd_row_size = 16;	const int lcd_col_size = 2;
	char lcd_text[lcd_col_size][lcd_row_size] = {0};

	int cursor_index = 0;

	/* print the lcd from lcd text array */
	auto lcd_refresh = [&] () {
		lcd.clear();
		for (int col_index = 0; col_index < lcd_col_size; col_index++)
		{
			lcd.setCursor(0, col_index);
			lcd.print(lcd_text[col_index]);
		}
	};

	/* clear the lcd and the cursor index and lcd text arra */
	auto lcd_clear = [&] () {
		lcd.clear();
		lcd.setCursor(0, 0);
		
		for (int col_index = 0; col_index < lcd_col_size; col_index++)
		for (int row_index = 0; row_index < lcd_row_size; row_index++)
			lcd_text[col_index][row_index] = '\0';
		cursor_index = 0;
	};

	while (true)
	{
		char input_key = keypad.getKey();

		if (input_key)
		{
			/* tone */
			tone(TONE_PIN, 523, 50);
			delay(50);
			noTone(TONE_PIN);

			/* if the input is more than lcd one line clear the all to re input */
			if (cursor_index == 16)
			{
				lcd_clear();
				continue;
			}

			switch (input_key)
			{
				/* when the input key is '=' calculate the ans from input word*/
				case '=':
					/* set the calculate key word */
					lcd_text[0][cursor_index++] = '=';

					/* print the ans to lcd */
					lcd.setCursor(0, 1);
					lcd.print("= ");
					lcd.print(get_calculate(lcd_text[0]));

					/* wait the press 'C' to next calculate */
					while ( keypad.getKey() != 'C');
					lcd_clear();
					break;

				/* clear the lcd and the cursor index and lcd text array */
				case 'C':
					lcd_clear();
					break;

				/* display press key to lcd */
				default:
					lcd_text[0][cursor_index] = input_key;
					lcd_refresh();
					cursor_index++;
					break;
			}
		}
	}
}