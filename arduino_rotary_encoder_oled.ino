

#include <SSD1306AsciiWire.h>
#include <SSD1306Ascii.h>

#define OLED_I2C_ADDRESS 0x3C
SSD1306AsciiWire display;

#define CLK_PIN 6
#define DT_PIN 7
#define LED_PIN 2

#define DEBUG_SERIAL_BAUD 115200

int state_CLK;
int prevState_CLK;
int count = 0;

void setupDisplay()
{
	display.begin(&Adafruit128x32, OLED_I2C_ADDRESS);
	display.set400kHz();
	display.setFont(Adafruit5x7);
	display.clear();
	display.setCursor(0, 0);
	display.print(F("Ready"));
}

int getCLK()
{
	return digitalRead(CLK_PIN);
}

int getDT()
{
	return digitalRead(DT_PIN);
}

void setup()
{
	
	Serial.begin(DEBUG_SERIAL_BAUD);

	pinMode(CLK_PIN, INPUT);
	pinMode(DT_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);

	prevState_CLK = getCLK();

	Serial.println(count);

	setupDisplay();
	setupDisplay();
	display.clear();
	display.print(count);
}

int getPulse()
{
	int state_CLK = getCLK();

	// no change, no pulse
	if (state_CLK == prevState_CLK)
	{
		return 0;
	}

	// a pulse occured
	prevState_CLK = state_CLK;

	// find direction
	int state_DT = getDT();
	// clock wise
	if (state_DT != state_CLK)
	{
		return 1;
	}
	// counter-clock wise
	return -1;
}



void loop()
{
	int pulse = getPulse();

	if (pulse != 0)
	{
		count += pulse;
		display.clear();
		display.print(count);
		//Serial.println(count);
		digitalWrite(LED_PIN, HIGH);
		delay(1);
		digitalWrite(LED_PIN, LOW);
	}
}
