//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <string.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define MaxCharWidth 16
#define MaxLines 2
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

char message[] = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
char blank[MaxCharWidth];
int messageLength = strlen(message);
int lineCount = 2;
char **lines;
// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}

void setup()
{
  lcd.begin(MaxCharWidth, MaxLines);              // start the library
  Serial.begin(9600);
  lineCount = (messageLength / MaxCharWidth);
  if ( (messageLength % MaxCharWidth) > 0) {
    lineCount++;
  }

  Serial.print("Number of lines: ");
  Serial.println(lineCount);

  lines = malloc( lineCount * sizeof(char*));
  for (int curLineInMessage = 0; curLineInMessage < lineCount; curLineInMessage++) {
    lines[curLineInMessage] = malloc(MaxCharWidth * sizeof(char) + 1);
    char curLine[MaxCharWidth];
    memset( curLine, ' ', MaxCharWidth);
    Serial.print("chars left: ");
    Serial.println(&message[curLineInMessage * MaxCharWidth]);
    if ( strlen(&message[curLineInMessage * MaxCharWidth]) > MaxCharWidth) {
      memcpy( curLine, &message[curLineInMessage * MaxCharWidth], MaxCharWidth);
    } else {
      memcpy(curLine, &message[curLineInMessage * MaxCharWidth], strlen(message[curLineInMessage * MaxCharWidth]));
    }
    curLine[MaxCharWidth] = '\0';
    Serial.print("curLine: " );
    Serial.print(curLine);
    Serial.println("|");
    strcpy( lines[curLineInMessage], curLine);
    Serial.print("lines[x]: " );
    Serial.print(lines[curLineInMessage]);
    Serial.println("|");
  }
}

void printLine(char message[], int lineNumber) {
  lcd.setCursor(0, lineNumber);
  lcd.print( message);
}

void loop()
{

  for (int curLineNumber = 0; curLineNumber < lineCount; curLineNumber++) {

    printLine( lines[curLineNumber], 0);
    delay(1000);
  }

  //  lcd_key = read_LCD_buttons();  // read the buttons

  //  switch (lcd_key)               // depending on which button was pushed, we perform an action
  //  {
  //    case btnRIGHT:
  //      {
  //        Serial.println("RIGHT ");
  //        break;
  //      }
  //    case btnLEFT:
  //      {
  //        Serial.println("LEFT   ");
  //        break;
  //      }
  //    case btnUP:
  //      {
  //        Serial.println("UP    ");
  //        break;
  //      }
  //    case btnDOWN:
  //      {
  //        Serial.println("DOWN  ");
  //        break;
  //      }
  //    case btnSELECT:
  //      {
  //        Serial.println("SELECT");
  //        break;
  //      }
  //    case btnNONE:
  //      {
  //        Serial.println("NONE  ");
  //        break;
  //      }
  //  }

}
