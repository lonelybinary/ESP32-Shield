/*

    Lonely Binary Vibrating Motor ESP32 Shield
    Morse Demo Code

*/

#include <Arduino.h>

// Active High
#define MOTOR_PIN 13

/*
    In the international standard, a "dash" is three times longer than a "dot." On paper, "-" is the symbol for a dash while every "." represents a dot. "E" is a simple letter and shortest code; it consists of just one "." Other characters are a bit more intricate. For example, "-.-." means "C."
*/
static const uint32_t dot_delay = 200;
static const uint32_t dash_delay = dot_delay * 3;

/*
    If you're dealing with a letter that features multiple dots and/or dashes, there should be a pause equivalent to the length of one dot in between those components.

    The pauses that separate entire letters are longer, equal to three dots.

    You should divide individual words by even longer pauses measuring seven dots long.
*/
static const uint32_t pause_symbol = dot_delay;
static const uint32_t pause_letter = dot_delay * 3;
static const uint32_t pause_word = dot_delay * 2 + dot_delay;


// Function to active the vibrating motor
void motorOn(uint32_t delay_ms)
{
    digitalWrite(MOTOR_PIN, HIGH);
    delay(delay_ms);
}

// Function to turn off the vibrating motor
void motorOff(uint32_t delay_ms)
{
    digitalWrite(MOTOR_PIN, LOW);
    delay(delay_ms);
}

// Define Morse code as a two-dimensional array
String morseCode[36][2] = {
    {"A", ".-"}, {"B", "-..."}, {"C", "-.-."}, {"D", "-.."}, {"E", "."}, {"F", "..-."}, {"G", "--."}, {"H", "...."}, {"I", ".."}, {"J", ".---"}, {"K", "-.-"}, {"L", ".-.."}, {"M", "--"}, {"N", "-."}, {"O", "---"}, {"P", ".--."}, {"Q", "--.-"}, {"R", ".-."}, {"S", "..."}, {"T", "-"}, {"U", "..-"}, {"V", "...-"}, {"W", ".--"}, {"X", "-..-"}, {"Y", "-.--"}, {"Z", "--.."}, {"0", "-----"}, {"1", ".----"}, {"2", "..---"}, {"3", "...--"}, {"4", "....-"}, {"5", "....."}, {"6", "-...."}, {"7", "--..."}, {"8", "---.."}, {"9", "----."}};

// Function to convert a character to Morse code using the two-dimensional array
String charToMorse(char c)
{
    c = toupper(c); // Convert character to uppercase to simplify matching
    for (int i = 0; i < 36; i++)
    {
        if (morseCode[i][0][0] == c)
        {                           // Compare with the first character of the Morse code entry
            return morseCode[i][1]; // Return the Morse code string
        }
    }
    return ""; // Return empty string for unsupported characters
}

// Function to convert a string to Morse code
String stringToMorse(String text)
{
    String morse = "";
    for (int i = 0; i < text.length(); i++)
    {
        morse += charToMorse(text[i]);
        // Add a space between Morse code letters, except for last word
        if (i < text.length() - 1)
            morse += " ";
    }
    return morse;
}

// Function to convert the morse code to motor
void morseToMotor(String morse)
{
    for (int i = 0; i < morse.length(); i++)
    {

        switch (morse[i])
        {
        case '.':
            motorOn(dot_delay);
            motorOff(pause_symbol);
            break;
        case '-':
            motorOn(dash_delay);
            motorOff(pause_symbol);
            break;
        case ' ':
            // Ensure index is valid before accessing the array
            if ((i - 1) >= 0)
            {
                // Apply word pause if previous character is a space as well, otherwise apply letter pause
                motorOff(morse[i - 1] == ' ' ? pause_word - pause_letter : pause_letter);
            }
            break;
        }
    }
}

// Function to convert string to motor
void stringToMotor(String text) {
    Serial.print(text + " : ");
    String morse = stringToMorse(text);
    Serial.println(morse);
    morseToMotor(morse);
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    pinMode(MOTOR_PIN, OUTPUT);

    Serial.println("Lonely Binary Vibrating Motor Demo Code");
}

void loop()
{
    stringToMotor("SOS");

    delay(1000);
}