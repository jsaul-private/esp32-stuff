#define pushButton_pin	35
#define LED_pin         LED_BUILTIN


// This is just a dummy that turns on/off an LED and prints the state to
// the terminal. The reason for also printing to terminal is to make sure
// to have properly debounced the button press, as a bounce is so brief
// that it would only cause invisible flicker of the LED.
void toggle(bool pressed)
{
	static bool state = false;

	if (pressed) {
		state = ! state;
		digitalWrite(LED_pin, state);
		Serial.println(state);
	}
}


void IRAM_ATTR buttonChange()
{
	static unsigned long lastChangeTime = 0;
	static unsigned long debounceDelay = 10;
	static bool state = false;

	unsigned long now = millis();
	if (now-lastChangeTime > debounceDelay) {
		// This is a relevant state change, so we read the on/off state
		// directly from the button pin.
		bool s = ! digitalRead(pushButton_pin);

		if (s == state) {
			// Noise spike not changing the state
			Serial.println("Noise spike ignored");
		}
		else {
			state = s;
			// Take action based on the current on/off state
			toggle(state);
		}
		
	}
	else {
		Serial.print("Noise spike detected, duration millis = ");
		Serial.println(now-lastChangeTime);
	}
	lastChangeTime = now;
}


void setup()
{
	// Serial monitor only used for debugging/demo, not production code!
	Serial.begin(115200);
	delay(100);
	Serial.println();

	pinMode(LED_pin, OUTPUT);
	pinMode(pushButton_pin, INPUT_PULLUP);
	attachInterrupt(pushButton_pin, buttonChange, CHANGE);
} 


void loop() {
	// empty
}
