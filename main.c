/* 640-LEDs clock project
 * Author: Benoît Brummer
 */

#include <stdio.h>
#include <string.h>
//#include <math.h>

void initFrameBuffer();
void updateFrameBuffer();
void draw();
void drawInConsole();	// testing
void getTime();


// 1-8,8-10, digit# 	verticalLine
unsigned char timeBitmaps[2][10][8] = {{
{127, 255, 243, 225, 225, 243, 255, 127}, {0, 192, 255, 255, 255, 255, 0, 0}, {56, 113, 227, 199, 206, 252, 120, 48}, {192, 204, 204, 204, 204, 237, 255, 126}, {15, 31, 59, 115, 227, 255, 255, 3}, {249, 249, 248, 216, 221, 223, 207, 199}, {127, 255, 255, 204, 204, 207, 239, 103}, {224, 225, 227, 231, 239, 254, 252, 248}, {119, 255, 255, 204, 204, 255, 255, 119}, {121, 253, 252, 204, 204, 253, 255, 127}
},{
{2, 3, 3, 3, 3, 3, 3, 2}, {0, 3, 3, 3, 3, 3, 3, 0}, {3, 3, 3, 3, 3, 3, 3, 3}, {3, 3, 3, 3, 3, 3, 3, 2}, {0,0,0,0,0,3,3,0}, {2, 3, 3, 3, 3, 3, 3, 2}, {2, 3, 3, 3, 3, 3, 3, 2}, {3, 3, 3, 2, 0, 0, 0, 0}, {2, 3, 3, 3, 3, 3, 3, 2}, {2, 3, 3, 3, 3, 3, 3, 2}
}};

// 1-8,8-10, weekday, verticalLine
unsigned char dayBitmaps[2][7][10] = {{
{255, 255, 224, 115, 58, 58, 115, 224, 255, 255}, {199, 197, 247, 247, 192, 199, 7, 245, 21, 245}, {255, 255, 1, 7, 30, 31, 7, 1, 255, 255}, {224, 224, 224, 255, 255, 255, 224, 239, 226, 227}, {255, 255, 216, 217, 192, 196, 192, 196, 192, 193}, {232, 169, 184, 2, 184, 170, 248, 1, 248, 72}, {240, 246, 242, 210, 214, 208, 223, 223, 223, 223}
},{
{3,3,0,3,1,1,3,0,3,3}, {3, 3, 1, 1, 0, 1, 1, 1, 3, 3}, {3, 3, 3, 2, 0, 0, 2, 3, 3, 3}, {0, 0, 0, 3, 3, 3, 0, 3, 0, 3}, {3,3,0,0,2,1,1,1,2,0}, {0,2,2,2,2,3,3,2,0,0}, {3,3,3,3,3,3,3,3,3,3}
}};

// digit#, verticalLine
unsigned char dateBitmaps[10][3] = {{31, 17, 31}, {9, 31, 1}, {23, 21, 29}, {21, 21, 31}, {28, 4, 15}, {29, 21, 23}, {31, 21, 23}, {16, 20, 31}, {31, 21, 31}, {29, 21, 31}};

// verticalLine, shift register
unsigned char frameBuffer[16][5];

unsigned char day, month, hour, minute, second, weekday;

int main()
{
  getTime();
  initFrameBuffer();
  drawInConsole();
  
  /*
   * getTime()
   * fillFrameBuffer
   * forever:
   * 	draw()
   * 
   * interrupts:
   * 	every second:
   * 		updateFrameBuffer()
   * 	when butA pressed:	(use variable to save state)
   * 		blinkHour (listen to butB to increment)
   * 		blinkMin
   * 		blinkMonth
   * 		Blinkday
   * 		exit
   * 
   */
  
}

void initFrameBuffer()
{
  hour = 18, minute = 59, second = 32, day = 25, month =9, weekday=3;	// TESTING values
  
  memset(frameBuffer, 0, sizeof(char)*80);
  
  unsigned char i;
  // time
  for(i=0; i<8; i++)
  {
    // SR1: hour1
    frameBuffer[i][0] = timeBitmaps[0][hour/10][i];
    frameBuffer[i+8][0] = timeBitmaps[0][hour%10][i];
    // SR2: hour2+min1
    frameBuffer[i][1] = (timeBitmaps[1][hour/10][i] << 6) | (timeBitmaps[0][minute/10][i] >> 2);
    frameBuffer[i+8][1] = (timeBitmaps[1][hour%10][i] << 6) | (timeBitmaps[0][minute % 10][i] >> 2);
    // SR3: min12+sec1
    frameBuffer[i][2] = (timeBitmaps[0][minute/10][i] << 6 ) | (timeBitmaps[1][minute/10][i] << 4) | (timeBitmaps[0][second/10][i] >> 4);
    frameBuffer[i+8][2] = (timeBitmaps[0][minute%10][i] << 6) | (timeBitmaps[1][minute % 10][i] << 4) | (timeBitmaps[0][second % 10][i] >> 4);
    //SR4: sec12+month(2/5)+weekd1
    frameBuffer[i][3] = (timeBitmaps[0][second / 10][i] << 4) | (timeBitmaps[1][second/10][i] << 2);
    frameBuffer[i+8][3] = (timeBitmaps[0][second % 10][i] << 4) | (timeBitmaps[1][second % 10][i] << 2);
  }
  // weekdays
  for(i=0; i<10; i++)
  {
    frameBuffer[i][3] |= (dayBitmaps[0][weekday][i] >> 6);	// SR4
    frameBuffer[i][4] = (dayBitmaps[0][weekday][i] << 2) | (dayBitmaps[1][weekday][i]); // SR5
  }
  // days, months
  for(i=0; i<3; i++)
  {
    frameBuffer[i+10][3] |= (dateBitmaps[month/10][i] >> 3);	// month top left-digit
    frameBuffer[i+13][3] |= (dateBitmaps[month % 10][i] >> 3);	// month top right-digit
    frameBuffer[i+10][4] |= (dateBitmaps[month/10][i] << 5);	// month bottom left-digit
    frameBuffer[i+13][4] |= (dateBitmaps[month % 10][i] << 5);	// month bottom right-digit
    frameBuffer[i+10][4] |= dateBitmaps[day / 10][i]; 	// day left-digit
    frameBuffer[i+13][4] |= dateBitmaps[day % 10][i];	// day right-digit
  }
  
}

void draw()
{
}

void drawInConsole()
{
  unsigned char curVLine,curSR,curBit, singleBit;
  // print first char of 1st line,
  // print first char of 2nd line,
  //...
  // print 2nd char of 1st line
  // print 2nd char of 2nd line
  for(curSR=0;curSR<5;curSR++)
  {
    for(curBit=0;curBit<8;curBit++)
    {
      for(curVLine=0;curVLine<16; curVLine++)
      {
	singleBit = 128>>curBit;
	//printf("SB: %u\tCB: %u\n", singleBit, curBit);
	if((singleBit & frameBuffer[curVLine][curSR]) >= 1)	printf("%u", 1);
	else				printf(" ");
      }
      printf("\n");
    }
  }
}

void getTime()
{
}

void updateFrameBuffer()
{
  // update secondR
  if((second % 10) == 0)
  {
    // update secondL
    if((second/10) == 0)
    {
      // update minuteR
      if((minute % 10) == 0)
      {
	// update minuteL
	if((minute/10) == 0)
	{
	  // update hourR
	  if((hour % 10) == 0)
	  {
	    // update hourL
	    if((hour / 10) == 0)
	    {
	      // update dayR, weekday
	      if((day % 10) == 0)
	      {
		// update dayL
		if((day/10) == 0)
		{
		  // update monthR
		  if((month%10) == 0)
		  {
		    // update monthL
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
}

void updateHourL()
{
  for(i=0; i<8; i++)
  {
    frameBuffer[i][0] = timeBitmaps[0][hour/10][i];
    frameBuffer[i][1] &= 63;
    frameBuffer[i][1] |= (timeBitmaps[1][hour/10][i] << 6);
  }
}

void updateHourR()
{
  // TODO update hour var
  for(i=0; i<8; i++)
  {
    frameBuffer[i+8][0] = timeBitmaps[0][hour/10][i];
    frameBuffer[i+8][1] &= 63;
    frameBuffer[i+8][1] |= (timeBitmaps[1][hour/10][i] << 6);
  }
}

void updateMinuteL()
{
  frameBuffer[i][1] &= 192;
  frameBuffer[i][1] |= (timeBitmaps[0][minute/10][i] >> 2);
  frameBuffer[i][2] &= 63;
  frameBuffer[i+8][1] |= (timeBitmaps[0][minute % 10][i] >> 2);
  frameBuffer[i][2] = (timeBitmaps[0][minute/10][i] << 6 ) | (timeBitmaps[1][minute/10][i] << 4);
  frameBuffer[i+8][2] = (timeBitmaps[0][minute%10][i] << 6) | (timeBitmaps[1][minute % 10][i] << 4);
}

void updateMinuteR()
{
  // TODO update hour var
  for(i=0; i<8; i++)
  {
    frameBuffer[i+8][0] = timeBitmaps[0][hour/10][i];
    frameBuffer[i+8][1] &= 63;
    frameBuffer[i+8][1] = (timeBitmaps[1][hour/10][i] << 6);
  }
}


