void comRead(void)
{
	ssRead();
	if (mark == true)
	{
		ssAnalysis();
		if (comdataSub[0].equals("ok"))
		{
			/*if (DEBUG_mode)
				Serial.println("OK");*/
		}
		else if (comdataSub[0].equals("down"))
		{
			if (comdataSub[1].equals("none"))
			{
				//if (DEBUG_mode)
				//	Serial.println("none");
			}
			else if (comdataSub[1].equals("set_properties"))
			{
				setProp();
			}

			else if (comdataSub[1].equals("get_properties"))
			{
				getProp();
			}

			else if (comdataSub[1].equals("MIIO_net_change"))
			{
				if (comdataSub[2].equals("cloud"))
					onCloud = 2;
				else if (comdataSub[2].equals("local"))
					onCloud = 1;
				else if (comdataSub[2].equals("offline"))
					onCloud = 0;
				/*if (DEBUG_mode)
				{
					Serial.print(comdataSub[2]);
					Serial.println(onCloud);
				}*/
			}
		}
		else if (comdataSub[0].equals("2") && comdataSub[4].equals("-") && comdataSub[7].equals("-")
			&& comdataSub[10].equals(" ") && comdataSub[13].equals(":") && comdataSub[16].equals(":"))
		{
			Serial.println("Time Get");
		}

		mark = false;
		comdata = "";
	}
}
void setProp()
{
	siid = comdataSub[2].toInt();
	piid = comdataSub[3].toInt();
	if (DEBUG_mode)
	{
		Serial.println("set_prop");
		Serial.print(comdataSub[2]);
		Serial.print(" ");
		Serial.print(comdataSub[3]);
		Serial.print(" ");
		Serial.println(comdataSub[4]);
	}

	if (siid == 2)
	{
		if (piid == 1)
		{
			if (comdataSub[4].equals("true"))
			{
				valu = 2;
				siid2.brightMin = 20;
				siid2.brightMax = 20;
				BGLight = 20;
				siid2.mode = 1;
				ssrRelay(false);
				mainRelay(true);
			}
			else
			{
				valu = 0;
				siid2.brightMin = 0;
				siid2.brightMax = 0;
				BGLight = 0;
				ssrRelay(false);
				mainRelay(false);
			}

			siid2.on = valu;
			
		}
		else if (piid == 2)
		{
			valu = comdataSub[4].toInt();
			siid2.brightMin = valu;
		}
		else if (piid == 3)
		{
			valu = comdataSub[4].toInt();
			siid2.brightMax = valu;
		}
		else if (piid == 4)
		{
			valu = comdataSub[4].toInt();
			siid2.mode = valu;
			switch (siid2.mode) {
			case 0://Auto
				siid2.brightMin = 80;
				siid2.brightMax = 255;
				BGLight = 255;
				ssrRelay(true);
				mainRelay(true);
				break;
			case 1://day
				siid2.brightMin = 80;
				siid2.brightMax = 80;
				BGLight = 255;
				ssrRelay(true);
				mainRelay(true);
				break;
			case 2://night
				siid2.brightMin = 20;
				siid2.brightMax = 20;
				BGLight = 20;
				ssrRelay(false);
				mainRelay(true);
				break;
			case 3://read
				siid2.brightMin = 255;
				siid2.brightMax = 255;
				BGLight = 255;
				ssrRelay(true);
				mainRelay(true);
				break;
			case 4://sleep
				siid2.brightMin = 16;
				siid2.brightMax = 16;
				BGLight = 0;
				ssrRelay(false);
				mainRelay(false);
				break;
			}

		}
		//delay(200);
		resultUp(siid, piid, 0);
	}
	
	/*
	if (siid == 2)
	{
		if (piid == 1)
		{
			propChangeBool(siid, piid, siid2.on);
		}
		else if (piid == 2)
		{
			propChange(siid, piid, siid2.brightMin);
		}
		else if (piid == 3)
		{
			propChange(siid, piid, siid2.brightMax);
		}
		else if (piid == 4)
		{
			propChange(siid, piid, siid2.mode);
		}
	}
	*/
	
}
void getProp()
{
	siid = comdataSub[2].toInt();
	piid = comdataSub[3].toInt();
	if (DEBUG_mode)
	{
		Serial.println("get_prop");
		Serial.print(comdataSub[2]);
		Serial.print(" ");
		Serial.println(comdataSub[3]);
	}
	if (siid == 3)
	{
		if (piid == 1)
		{
			valuF = siid3.temperature;
			propChangeFloat(siid, piid, valuF);
		}
		else if (piid == 2)
		{
			valu = siid3.humidy;
			propChange(siid, piid, valu);
		}
		else if (piid == 3)
		{
			valu = siid3.light;
			propChange(siid, piid, valu);
		}
		else if (piid == 4)
		{
			valu = siid3.detection;
			propChange(siid, piid, valu);
		}
	}

	else if (siid == 4)
	{
		if (piid == 1)
			valu = siid4.sw1;
		else if (piid == 2)
			valu = siid4.sw2;
		else if (piid == 3)
			valu = siid4.sw3;
		else if (piid == 4)
			valu = siid4.sw4;
		propChangeBool(siid, piid, valu);
	}
	
}



void propChange(int s, int p, int v)
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(s);
	tmpData += " ";
	tmpData += String(p);
	tmpData += " ";
	tmpData += String(v);
	Serial1.print(tmpData);
	Serial1.print("\r");
}
void propChangeBool(int s, int p, int v)
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(s);
	tmpData += " ";
	tmpData += String(p);
	tmpData += " ";
	if (v == 1)
		tmpData += "true";
	else
		tmpData += "false";
	Serial1.print(tmpData);
	Serial1.print("\r");
}
void propChangeFloat(int s, int p, float v)
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(s);
	tmpData += " ";
	tmpData += String(p);
	tmpData += " ";
	char tmp[5];
	dtostrf(v, 4, 1, tmp);
	tmpData += tmp;
	Serial1.print(tmpData);
	Serial1.print("\r");
}
void resultUp(int s, int p, int v)
{
	String tmpData = "";
	tmpData += "result";
	tmpData += " ";
	tmpData += String(s);
	tmpData += " ";
	tmpData += String(p);
	tmpData += " ";
	tmpData += String(v);
	Serial1.print(tmpData);
	Serial1.print("\r");

	if (DEBUG_mode)
	{
		Serial.println(tmpData);
	}
}


void askTime()
{
	String tmpData = "";
	tmpData += "time";
	Serial1.print(tmpData);
	Serial1.print("\r");
}


void getdown()
{
	Serial1.print("get_down\r");
}

void restore()
{
	Serial1.print("restore\r");
}

void propUp2()
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(1);
	tmpData += " ";
	if(siid2.on)
		tmpData += "true";
	else
		tmpData += "false";
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(siid2.brightMin);
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(siid2.brightMax);
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(siid2.mode);
	Serial1.print(tmpData);
	Serial1.print("\r");
	if (DEBUG_mode)
		Serial.println(tmpData);
}

void propUp3()
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(1);
	tmpData += " ";
	char tmp[5];
	dtostrf(siid3.temperature, 2, 1, tmp);
	tmpData += tmp;
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(siid3.humidy);
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(siid3.light);
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(siid3.detection);
	Serial1.print(tmpData);
	Serial1.print("\r");
	if (DEBUG_mode)
		Serial.println(tmpData);
}

void propUp4()
{
	String tmpData = "";
	tmpData += "properties_changed";
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(1);
	tmpData += " ";
	tmpData += String(siid4.sw1);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(2);
	tmpData += " ";
	tmpData += String(siid4.sw2);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(3);
	tmpData += " ";
	tmpData += String(siid4.sw3);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(4);
	tmpData += " ";
	tmpData += String(siid4.sw4);
	Serial1.print(tmpData);
	Serial1.print("\r");
	if (DEBUG_mode)
		Serial.println(tmpData);
}