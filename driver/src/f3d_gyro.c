#include <f3d_gyro.h>
#include <f3d_delay.h>
#include <stm32f30x.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define WORD_Y 145
#define HTOFF 18
uint8_t barXs[3] = {20, 60, 100}; // x positions for bars

void f3d_gyro_interface_init() {
  /**********************************************************************/
  /************** CODE HERE *********************************************/
  //You must configure and initialize the following 4 pins
 
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  //SCK PA5
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA,5,GPIO_AF_5);

  //MOSI PA6 
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA,6,GPIO_AF_5);
  
  //MISO PA7
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOA,7,GPIO_AF_5);
 
  //CS PE3
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE,&GPIO_InitStructure);
 
  //set the CS high
  GPIO_SetBits(GPIOE, GPIO_Pin_3);
  /**********************************************************************/
   
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  //SPI Initialization and configuration
  SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI1, &SPI_InitStructure);
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  SPI_Cmd(SPI1, ENABLE);
}

//the init function to be called in your main.c
void f3d_gyro_init(void) {
  //
  //SETTING THE CONTROL REGISTERS 
  f3d_gyro_interface_init();
  // CTRL1 Register 
  // Bit 7:6 Data Rate: Datarate 0
  // Bit 5:4 Bandwidth: Bandwidth 3
  // Bit 3: Power Mode: Active
  // Bit 2:0 Axes Enable: X,Y,Z enabled
  uint8_t ctrl1;
  uint8_t ctrl4;
	
  ctrl1 |= (uint8_t) (((uint8_t)0x00)|		
		      ((uint8_t)0x30)|		
		      ((uint8_t)0x08)|		
		      ((uint8_t)0x07));
  // CTRL4 Register 
  // Bit 7 Block Update: Continuous */
  // Bit 6 Endianess: LSB first  */
  // Bit 5:4 Full Scale: 500 dps */
  ctrl4 |= (uint8_t) (((uint8_t)0x00)|			
		      ((uint8_t)0x00)|				     
		      ((uint8_t)0x10));

  f3d_gyro_write(&ctrl1, 0x20, 1);
  f3d_gyro_write(&ctrl4, 0x23, 1);

}
//to read from it
void f3d_gyro_read(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead) {
  //are we reading one byte or more than one byte???
  if (NumByteToRead > 1) {
    ReadAddr |= (uint8_t)(0x80 | 0x40); // sets to multibyte mode
  }
  else {
    ReadAddr |= (uint8_t) (0x80); // sets to read mode (first bit 1)
  }
  //setting chip select to low (LETS TALK!)
  GYRO_CS_LOW();
  //sending address byte
  f3d_gyro_sendbyte(ReadAddr);  
  while(NumByteToRead > 0x00) {
    //WE are now sending dummy data so we can read the valuable!
    //remember we must write to read!
    //putting the information in the buffer
    *pBuffer = f3d_gyro_sendbyte(((uint8_t)0x00));
    NumByteToRead--;
    pBuffer++;
  }
  //setting chip select to high (DONE TALKING)
  GYRO_CS_HIGH();//setting chip select to high (DONE TALKING)
}

/*writing function*/
void f3d_gyro_write(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite) {
  //are we reading one byte or more than one byte???
  if (NumByteToWrite > 1) {
    WriteAddr |= (uint8_t)(0x80 | 0x40); // sets to multibyte mode
  } else {
    WriteAddr |= (uint8_t)(0x40); 
  }
  //setting chip select to low (LETS TALK!)
  GYRO_CS_LOW();
  //sending address byte
  f3d_gyro_sendbyte(WriteAddr);  
  while(NumByteToWrite > 0x00) {
    //WE are now sending dummy data so we can read the valuable!
    //remember we must write to read!
    //putting the information in the buffer
    f3d_gyro_sendbyte(*pBuffer);
    NumByteToWrite--;
    pBuffer++;
  }
  GYRO_CS_HIGH();
}

/*sends the bytes*/
static uint8_t f3d_gyro_sendbyte(uint8_t byte) {
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  SPI_SendData8(SPI1, byte); 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
  return (uint8_t)SPI_ReceiveData8(SPI1);
}

/*gets the data*/
void f3d_gyro_getdata(float *pfData) {
  //
  //
  int16_t RawData[3];
  uint8_t tmpbuffer[6];
  int i;
  //We are going to write some data to the gyro
  f3d_gyro_write(tmpbuffer,0x28,6);
  //Then we are going to read it
  f3d_gyro_read(tmpbuffer,0x28,6);
  //casting the data retreiving from tmpbuffer to raw data
  for(i=0; i<3; i++) {
    RawData[i]=(int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
  }
  //adjusting the data with the sensitivity
  for(i=0; i<3; i++) {
    pfData[i]=(float)RawData[i]/L3G_Sensitivity_500dps;
  }
}

void f3d_gyro_draw(int drawFrame) {
  printf("gyro mode\n"); // debug line
  float gyroVals[3] = {};
  char str[30];

  // draw frame if drawFrame equals 1
  if (drawFrame) {f3d_gyro_drawFrame();}

  // draw gyro values
  f3d_gyro_getdata(gyroVals);
  f3d_gyro_drawVals(gyroVals[0], gyroVals[1], gyroVals[2]);
}

void f3d_gyro_drawVals(float x, float y, float z) {
  char str[30]; // use to format values to strings
  //draw x,y,z values
  sprintf(str, "%.2f", x);
  f3d_lcd_drawString(barXs[0]-15, WORD_Y, "     ", WORD_COL, BACKGROUND); // clear prev val
  f3d_lcd_drawString(barXs[0]-15, WORD_Y, str, WORD_COL, BACKGROUND);

  sprintf(str, "%.2f", y);
  f3d_lcd_drawString(barXs[1]-10, WORD_Y, "     ", WORD_COL, BACKGROUND); // clear prev val
  f3d_lcd_drawString(barXs[1]-10, WORD_Y, str, WORD_COL, BACKGROUND);

  sprintf(str, "%.2f", z);
  f3d_lcd_drawString(barXs[2]-5, WORD_Y, "     ", WORD_COL, BACKGROUND); // clear prev val
  f3d_lcd_drawString(barXs[2]-5, WORD_Y, str, WORD_COL, BACKGROUND);

  // draw bars for x, y, z values
  delay(15);
  f3d_lcd_drawDynamicHBar(x, barXs[0], WORD_Y-15, 10, HTOFF, MAGENTA);
  delay(15);
  f3d_lcd_drawDynamicHBar(y, barXs[1], WORD_Y-15, 10, HTOFF, MAGENTA);
  delay(15);
  f3d_lcd_drawDynamicHBar(z, barXs[2], WORD_Y-15, 10, HTOFF, MAGENTA);
  delay(15);  
}

// draw frame for gyro screen
void f3d_gyro_drawFrame() {  
  f3d_lcd_drawString(7, 10, "mode: gyro", WORD_COL, BACKGROUND);
  f3d_lcd_drawChar(barXs[0], WORD_Y-10, 'X', YELLOW, BACKGROUND);
  f3d_lcd_drawChar(barXs[1], WORD_Y-10, 'Y', YELLOW, BACKGROUND);
  f3d_lcd_drawChar(barXs[2], WORD_Y-10, 'Z', YELLOW, BACKGROUND);
}
