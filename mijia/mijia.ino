//UART1 A9 TX A10 RX    
//ESP32 17 TX   16 RX
//PWM B6 B7
//ADC A0-7
//SCL2 B10 SDA2 B11
//SSR PB0
//Relay PB9

bool DEBUG_mode = false;
bool DEBUG_adc = false;
int onCloud = 0;
int siid, piid,valu;
float valuF;
uint32_t st, et,timeCount,propUpCount;
String comdata = "";// data from uart
String comdataSub[32] = {""};// data from uart
bool mark = false;//if uart read
int i = 0, j = 0;//0~255

int bright = 80;//led line
int Bbright = 80;



//light
struct Siid2 {
	int on;
	int brightMin;//0~255
	int brightMax;
	int mode;//0auto 1day 2night 3read 4tv 5computer
};
Siid2 siid2;

//sensor
struct Siid3 {
	float temperature;
	int humidy;
	int light;//0~100
	int detection;//0~255
};
Siid3 siid3;

//door
struct Siid4 {
	int sw1;
	int sw2;
	int sw3;
	int sw4;
};
Siid4 siid4;

void setup()
{
	
	initialProp();
	Serial.begin(115200); 
	Serial1.begin(115200);// A9 A10
	//
	init_control();
	st = millis();
	//testMode();
}

void loop()
{
	et = millis();
	if ((et - st) >= 10)//100Hz
	{
		
		st = et;
		timeCount++;
		if (timeCount % 3 == 0)//30Hz
		{
			
			ledLineControl();
			BGlightControl();
			doorDetec();
		}
		if (timeCount % 10 == 0)//10Hz
		{
			
			wifiLedBlink(timeCount);
			
			
		}
		if (timeCount % 30 == 0)//3Hz
		{
			getdown();

		}
		
		if (timeCount % 200 == 0)//0.5Hz
		{
			if(propUpCount % 3 == 0)
			{
				propUp2();
			}
			else if (propUpCount % 3 == 1)
			{
				catDetec();
				propUp3();
				
			}
			else if (propUpCount % 3 == 2)
			{
				propUp4();
			}
			propUpCount++;
		}				
	}
	
	comRead();
	
}
