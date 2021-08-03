void testMode()
{
	while (1)
	{
		Serial.println("SSR ON");
		digitalWrite(ssrPin, HIGH);
		delay(1000);
		Serial.println("Relay ON");
		digitalWrite(relayPin, HIGH);
		delay(1000);
		Serial.println("SSR OFF");
		digitalWrite(ssrPin, LOW);
		delay(1000);
		Serial.println("Relay OFF");
		//digitalWrite(relayPin, LOW);
		delay(1000);
		Serial.println("LED1 ON");
		pwmWrite(pwmPin1, 65535);
		delay(1000);
		Serial.println("LED2 ON");
		pwmWrite(pwmPin2, 65535);
		delay(1000);
		Serial.println("LED1 OFF");
		pwmWrite(pwmPin1, 0);
		delay(1000);
		Serial.println("LED2 OFF");
		pwmWrite(pwmPin2, 0);
		delay(1000);

	}
	
}
