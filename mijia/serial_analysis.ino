void ssRead()
{
	while (Serial1.available() > 0)
	{
		comdata += char(Serial1.read());
		delay(1);
		mark = true;
		j = 0;
	}
	 //if (mark&&DEBUG_mode)
	 // Serial.println(comdata);
}

void ssAnalysis()
{
	for (i = 0; i < 32; i++)
		comdataSub[i] = "";
	for (i = 0; i < comdata.length()-1; i++)
	{
		if (comdata[i] == ' ')
			j++;
		else
		{
			comdataSub[j] += char(comdata[i]);
		}
	}
	//if (mark&&DEBUG_mode)
	//{
	//	for (i = 0; i <= j; i++)
	//	{
	//	  Serial.print(i);
	//	  Serial.print("  ");
	//	  Serial.println(comdataSub[i]);
	//	}
	//}
}


