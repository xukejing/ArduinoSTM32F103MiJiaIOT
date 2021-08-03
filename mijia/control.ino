//UART1 A9 TX A10 RX    
//ESP32 17 TX   16 RX
//PWM B6 B7
//ADC A0-7
//SSR PB0
//Relay PB9
bool Door4 =false;
int wifiLedPin = PC13;
int ledState = HIGH;
int restorePin = PB1;
int detecPin = PB8;
uint8_t restoreCount = 0;
int doorPin0 = PA0;
int doorPin1 = PA1;
int doorPin2 = PA2;
int doorPin3 = PA3;
double doorV0 = 0;
double doorV1 = 0;
double doorV2 = 0;
double doorV3 = 0;
int pwmPin1 = PB6;
int pwmPin2 = PB7;
int ssrPin = PB0;
int relayPin = PB9;
int doorValue[4] = {0};
int doorOpen = 0;
int dutyCycle = 0;
int BGLight = 80;
void init_control()
{
	pinMode(wifiLedPin, OUTPUT);
	pinMode(ssrPin, OUTPUT);
	pinMode(relayPin, OUTPUT);

	pinMode(restorePin, INPUT_PULLUP);
	pinMode(detecPin, INPUT);

	pinMode(doorPin0, INPUT_ANALOG);
	pinMode(doorPin1, INPUT_ANALOG);
	pinMode(doorPin2, INPUT_ANALOG);
	pinMode(doorPin3, INPUT_ANALOG);

	pinMode(pwmPin1, PWM);
	pinMode(pwmPin2, PWM);

	pwmWrite(pwmPin1, 400);
	pwmWrite(pwmPin2, 400);

	digitalWrite(wifiLedPin, ledState);
	digitalWrite(ssrPin, LOW);
	digitalWrite(relayPin, HIGH);
}
void wifiLedBlink(uint32_t c)
{
	if (restoreCount > 0)
		restoreCount--;

	if (digitalRead(restorePin) == LOW)
	{
		if (restoreCount == 0)
		{
			restore();
			restoreCount = 100;
		}
	}

	if (onCloud == 2)
	{
		if (ledState == HIGH)
		{
			ledState = LOW;
			digitalWrite(wifiLedPin, ledState);
		}
	}
	else if (onCloud == 1)
	{
		if (c % 20 == 0)
		{
			if (ledState == LOW) {
				ledState = HIGH;
			}
			else {
				ledState = LOW;
			}
			digitalWrite(wifiLedPin, ledState);
		}
	}
	else if (onCloud == 0)
	{
		if (c % 100 == 0)
		{
			if (ledState == LOW) {
				ledState = HIGH;
			}
			else {
				ledState = LOW;
			}
			digitalWrite(wifiLedPin, ledState);
		}
	}
}
void ssrRelay(bool ssr)
{
	if (ssr)
		digitalWrite(ssrPin, HIGH);
	else
		digitalWrite(ssrPin, LOW);
}
void mainRelay(bool r)
{
	if (r)
		digitalWrite(relayPin, HIGH);
	else
		digitalWrite(relayPin, LOW);
}
void doorDetec()
{
	doorValue[0]= analogRead(doorPin0) - 2127;
	doorV0 = doorV0*0.9 + (double)doorValue[0] * 0.1;
	doorValue[0] = (int)doorV0;
	if (doorValue[0] < 0)
		doorValue[0] *= -1;
	doorValue[1] = analogRead(doorPin1) - 2127;
	doorV1 = doorV1*0.9 + (double)doorValue[1] * 0.1;
	doorValue[1] = (int)doorV1;
	if (doorValue[1] < 0)
		doorValue[1] *= -1;
	doorValue[2] = analogRead(doorPin2) - 2127;
	doorV2 = doorV2*0.9 + (double)doorValue[2] * 0.1;
	doorValue[2] = (int)doorV2;
	if (doorValue[2] < 0)
		doorValue[2] *= -1;
	doorValue[3] = analogRead(doorPin3) - 2127;
	doorV3 = doorV3*0.9 + (double)doorValue[3] * 0.1;
	doorValue[3] = (int)doorV3;
	if (doorValue[3] < 0)
		doorValue[3] *= -1;


	doorOpen = 0;
	if (doorValue[0] < 20)
	{
		doorOpen++;
		siid4.sw1 = 1;
	}
	else siid4.sw1 = 0;

	if (doorValue[1] < 20)
	{
		doorOpen++;
		siid4.sw2 = 1;
	}
	else siid4.sw2 = 0;

	if (Door4)
	{
		if (doorValue[2] < 20)
		{
			doorOpen++;
			siid4.sw3 = 1;
		}
		else siid4.sw3 = 0;

		if (doorValue[3] < 20)
		{
			doorOpen++;
			siid4.sw4 = 1;
		}
		else siid4.sw4 = 0;
	}
	else
	{
		if (doorValue[2] < 20)
		{
			//doorOpen++;
			siid4.sw3 = 1;
		}
		else siid4.sw3 = 0;

		if (doorValue[3] < 20)
		{
			//doorOpen++;
			siid4.sw4 = 1;
		}
		else siid4.sw4 = 0;
	}
	
		
	
	if (doorOpen == 0)
	{
		bright = siid2.brightMin;
		
	}
	else
	{
		bright = siid2.brightMax;
		
	}
	
}
void ledLineControl()
{
	if (bright == siid2.brightMin)
	{
		
		if (dutyCycle > bright)
			{dutyCycle--;
			
			}
		else if (dutyCycle < bright)
			{
			  dutyCycle++;
			}
	
	}
	else if (bright == siid2.brightMax)
	{
		if (dutyCycle < bright)
		{
		  dutyCycle++;
		}
		else if (dutyCycle > bright)
			{dutyCycle--;
			}
	}
	pwmWrite(pwmPin1, dutyCycle*dutyCycle);
}
void BGlightControl()
{
	if (Bbright < BGLight)
		Bbright++;
	else if (Bbright>BGLight)
		Bbright--;
	pwmWrite(pwmPin2, Bbright*Bbright);
}
void catDetec()
{
	if (digitalRead(detecPin) == HIGH)
	{
		siid3.detection = 1;
	}
	else siid3.detection = 0;

}