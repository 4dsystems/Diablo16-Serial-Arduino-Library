/*
   Diablo_Serial_4DLib.cpp - Library for 4D Systems Serial Environment.
 */

#include "Diablo_Serial_4DLib.h"

#if (ARDUINO >= 100)
	#include "Arduino.h" // for Arduino 1.0
#else
	#include "WProgram.h" // for Arduino 23
#endif

Diablo_Serial_4DLib::Diablo_Serial_4DLib(Stream * virtualPort, void (*setBaudRateHndl)(unsigned long)) { 
  _virtualPort = virtualPort; 
  setBaudRateExternal = setBaudRateHndl;
  setBaudRateInternal = &Diablo_Serial_4DLib::exSetBaudRateHndl;
  unknownSerial = true;
}

Diablo_Serial_4DLib::Diablo_Serial_4DLib(HardwareSerial * serial) { 
  _virtualPort = (Stream *)serial; 
  setBaudRateInternal = &Diablo_Serial_4DLib::hwSetBaudRateHndl;
}

#ifdef SoftwareSerial_h		
Diablo_Serial_4DLib::Diablo_Serial_4DLib(SoftwareSerial * serial) { 
  _virtualPort = (Stream *)serial; 
  setBaudRateInternal = &Diablo_Serial_4DLib::swSetBaudRateHndl;
}
#endif

#ifdef AltSoftSerial_h
Diablo_Serial_4DLib::Diablo_Serial_4DLib(AltSoftSerial * serial) { 
  _virtualPort = (Stream *)serial; 
  setBaudRateInternal = &Diablo_Serial_4DLib::alSetBaudRateHndl;
}
#endif

//*********************************************************************************************//
//**********************************Intrinsic 4D Routines**************************************//
//*********************************************************************************************//

void Diablo_Serial_4DLib::WriteChars(char * charsout)
{
  unsigned char wk ;
  do
  {
    wk = *charsout++ ;
    _virtualPort->write(wk) ;
  } while (wk) ;
}

void Diablo_Serial_4DLib::WriteBytes(char * Source, int Size)
{
 	unsigned char wk ;
	int i ;
	for (i = 0; i < Size; i++)
	{
		wk = *Source++ ;
                _virtualPort->write(wk) ;
	}
}

void Diablo_Serial_4DLib::WriteWords(word * Source, int Size)
{
  word wk ;
  int i ;
  for (i = 0; i < Size; i++)
  {
    wk = *Source++ ;
    _virtualPort->write(wk >> 8) ;
    _virtualPort->write(wk) ;
  }
}

void Diablo_Serial_4DLib::getbytes(char * data, int size)
{
  int read ;
  unsigned long sttime ;
  int readc ;
  readc  = 0 ;
  sttime = millis() ;
  while ((readc != size) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      data[readc++] = _virtualPort->read() ;
    }
  }
  if (readc != size)
  {
    Error4D = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
}

void Diablo_Serial_4DLib::GetAck(void)
{
  int read ;
  unsigned char readx ;
  unsigned long sttime ;
  Error4D = Err4D_OK ;
  sttime  = millis();
  read    = 0 ;
  while ((read != 1) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available() != 0) 
    {
      readx = _virtualPort->read() ;
      read = 1 ;
    }
  }
  if (read == 0)
  {
    Error4D = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
  else if (readx != 6)
  {
    Error4D     = Err4D_NAK ;
    Error4D_Inv = readx ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
}

word Diablo_Serial_4DLib::GetWord(void)
{
  unsigned char readx[2] ;
  int readc ;
  unsigned long sttime ;
  
  if (Error4D != Err4D_OK)
    return 0 ;
  sttime   = millis();
  readc    = 0 ;
  while ((readc != 2) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      readx[readc++] = _virtualPort->read() ;
    }
  }
  
  if (readc != 2)
  {
    Error4D  = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  return 0 ;
  }
  else
    return readx[0] << 8 | readx[1] ;
}

void Diablo_Serial_4DLib::getString(char * outStr, int strLen)
{
  unsigned char readx[2] ;
  int readc ;
  unsigned long sttime ;
  
  if (Error4D != Err4D_OK)
  {
    outStr[0] = 0 ;
    return ;
  }
  sttime   = millis();
  readc    = 0 ;
  while ((readc != strLen) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      outStr[readc++] = _virtualPort->read() ;
    }
  }
  
  if (readc != strLen)
  {
    Error4D  = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
  outStr[readc] = 0 ;
}

word Diablo_Serial_4DLib::GetAckResp(void)
{
	GetAck() ;
	return GetWord() ;
}

word Diablo_Serial_4DLib::GetAckRes2Words(word * word1, word * word2)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	*word1 = GetWord() ;
	*word2 = GetWord() ;
	return Result ;
}

void Diablo_Serial_4DLib::GetAck2Words(word * word1, word * word2)
{
	GetAck() ;
	*word1 = GetWord() ;
	*word2 = GetWord() ;
}

word Diablo_Serial_4DLib::GetAckResSector(t4DSector Sector)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getbytes(Sector, 512) ;
	return Result ;
}

word Diablo_Serial_4DLib::GetAckResStr(char * OutStr)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getString(OutStr, Result) ;
	return Result ;
}

word Diablo_Serial_4DLib::GetAckResData(t4DByteArray OutData, word size)
{
	int Result ;
	GetAck() ;
	Result = GetWord() ;
	getbytes(OutData, size) ;
	return Result ;
}

//*********************************************************************************************//
//**********************************Compound 4D Routines***************************************//
//*********************************************************************************************//

word Diablo_Serial_4DLib::bus_Read8()
{
  _virtualPort->write(F_bus_Read8 >> 8) ;
  _virtualPort->write(F_bus_Read8) ;
  return GetAckResp() ;
}

void Diablo_Serial_4DLib::bus_Write8(word Bits)
{
  _virtualPort->write(F_bus_Write8 >> 8) ;
  _virtualPort->write(F_bus_Write8) ;
  _virtualPort->write(Bits >> 8) ;
  _virtualPort->write(Bits) ;
  GetAck() ;
}

word Diablo_Serial_4DLib::charheight(char  TestChar)
{
  _virtualPort->print((char)(F_charheight >> 8));
  _virtualPort->print((char)(F_charheight));
  _virtualPort->print((char)(TestChar));
  return GetAckResp();
}

word Diablo_Serial_4DLib::charwidth(char  TestChar)
{
  _virtualPort->print((char)(F_charwidth >> 8));
  _virtualPort->print((char)(F_charwidth));
  _virtualPort->print((char)(TestChar));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Close(word  Handle)
{
  _virtualPort->print((char)(F_file_Close >> 8));
  _virtualPort->print((char)(F_file_Close));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Count(char *  Filename)
{
  _virtualPort->print((char)(F_file_Count >> 8));
  _virtualPort->print((char)(F_file_Count));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Dir(char *  Filename)
{
  _virtualPort->print((char)(F_file_Dir >> 8));
  _virtualPort->print((char)(F_file_Dir));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Erase(char *  Filename)
{
  _virtualPort->print((char)(F_file_Erase >> 8));
  _virtualPort->print((char)(F_file_Erase));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Error()
{
  _virtualPort->print((char)(F_file_Error >> 8));
  _virtualPort->print((char)(F_file_Error));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Exec(char *  Filename, word  ArgCount, t4DWordArray  Args)
{
  _virtualPort->print((char)(F_file_Exec >> 8));
  _virtualPort->print((char)(F_file_Exec));
  WriteChars(Filename);
  _virtualPort->print((char)(ArgCount >> 8));
  _virtualPort->print((char)(ArgCount));
  WriteWords(Args, ArgCount);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Exists(char *  Filename)
{
  _virtualPort->print((char)(F_file_Exists >> 8));
  _virtualPort->print((char)(F_file_Exists));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_FindFirst(char *  Filename)
{
  _virtualPort->print((char)(F_file_FindFirst >> 8));
  _virtualPort->print((char)(F_file_FindFirst));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_FindNext()
{
  _virtualPort->print((char)(F_file_FindNext >> 8));
  _virtualPort->print((char)(F_file_FindNext));
  return GetAckResp();
}

char Diablo_Serial_4DLib::file_GetC(word  Handle)
{
  _virtualPort->print((char)(F_file_GetC >> 8));
  _virtualPort->print((char)(F_file_GetC));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_GetS(char *  StringIn, word  Size, word  Handle)
{
  _virtualPort->print((char)(F_file_GetS >> 8));
  _virtualPort->print((char)(F_file_GetS));
  _virtualPort->print((char)(Size >> 8));
  _virtualPort->print((char)(Size));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResStr(StringIn);
}

word Diablo_Serial_4DLib::file_GetW(word  Handle)
{
  _virtualPort->print((char)(F_file_GetW >> 8));
  _virtualPort->print((char)(F_file_GetW));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Image(word  X, word  Y, word  Handle)
{
  _virtualPort->print((char)(F_file_Image >> 8));
  _virtualPort->print((char)(F_file_Image));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Index(word  Handle, word  HiSize, word  LoSize, word  Recordnum)
{
  _virtualPort->print((char)(F_file_Index >> 8));
  _virtualPort->print((char)(F_file_Index));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(HiSize >> 8));
  _virtualPort->print((char)(HiSize));
  _virtualPort->print((char)(LoSize >> 8));
  _virtualPort->print((char)(LoSize));
  _virtualPort->print((char)(Recordnum >> 8));
  _virtualPort->print((char)(Recordnum));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_LoadFunction(char *  Filename)
{
  _virtualPort->print((char)(F_file_LoadFunction >> 8));
  _virtualPort->print((char)(F_file_LoadFunction));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_LoadImageControl(char *  Datname, char *  GCIName, word  Mode)
{
  _virtualPort->print((char)(F_file_LoadImageControl >> 8));
  _virtualPort->print((char)(F_file_LoadImageControl));
  WriteChars(Datname);
  WriteChars(GCIName);
  _virtualPort->print((char)(Mode >> 8));
  _virtualPort->print((char)(Mode));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Mount()
{
  _virtualPort->print((char)(F_file_Mount >> 8));
  _virtualPort->print((char)(F_file_Mount));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Open(char *  Filename, char  Mode)
{
  _virtualPort->print((char)(F_file_Open >> 8));
  _virtualPort->print((char)(F_file_Open));
  WriteChars(Filename);
  _virtualPort->print((char)(Mode));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_PlayWAV(char *  Filename)
{
  _virtualPort->print((char)(F_file_PlayWAV >> 8));
  _virtualPort->print((char)(F_file_PlayWAV));
  WriteChars(Filename);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_PutC(char  Character, word  Handle)
{
  _virtualPort->print((char)(F_file_PutC >> 8));
  _virtualPort->print((char)(F_file_PutC));
  _virtualPort->print((char)(Character));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_PutS(char *  StringOut, word  Handle)
{
  _virtualPort->print((char)(F_file_PutS >> 8));
  _virtualPort->print((char)(F_file_PutS));
  WriteChars(StringOut);
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_PutW(word  Word, word  Handle)
{
  _virtualPort->print((char)(F_file_PutW >> 8));
  _virtualPort->print((char)(F_file_PutW));
  _virtualPort->print((char)(Word >> 8));
  _virtualPort->print((char)(Word));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Read(t4DByteArray  Data, word  Size, word  Handle)
{
  _virtualPort->print((char)(F_file_Read >> 8));
  _virtualPort->print((char)(F_file_Read));
  _virtualPort->print((char)(Size >> 8));
  _virtualPort->print((char)(Size));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResData(Data,Size);
}

word Diablo_Serial_4DLib::file_Rewind(word  Handle)
{
  _virtualPort->print((char)(F_file_Rewind >> 8));
  _virtualPort->print((char)(F_file_Rewind));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Run(char *  Filename, word  ArgCount, t4DWordArray  Args)
{
  _virtualPort->print((char)(F_file_Run >> 8));
  _virtualPort->print((char)(F_file_Run));
  WriteChars(Filename);
  _virtualPort->print((char)(ArgCount >> 8));
  _virtualPort->print((char)(ArgCount));
  WriteWords(Args, ArgCount);
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_ScreenCapture(word  X, word  Y, word  Width, word  Height, word  Handle)
{
  _virtualPort->print((char)(F_file_ScreenCapture >> 8));
  _virtualPort->print((char)(F_file_ScreenCapture));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Width >> 8));
  _virtualPort->print((char)(Width));
  _virtualPort->print((char)(Height >> 8));
  _virtualPort->print((char)(Height));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Seek(word  Handle, word  HiWord, word  LoWord)
{
  _virtualPort->print((char)(F_file_Seek >> 8));
  _virtualPort->print((char)(F_file_Seek));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(HiWord >> 8));
  _virtualPort->print((char)(HiWord));
  _virtualPort->print((char)(LoWord >> 8));
  _virtualPort->print((char)(LoWord));
  return GetAckResp();
}

word Diablo_Serial_4DLib::file_Size(word  Handle, word *  HiWord, word *  LoWord)
{
  _virtualPort->print((char)(F_file_Size >> 8));
  _virtualPort->print((char)(F_file_Size));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckRes2Words(HiWord,LoWord);
}

word Diablo_Serial_4DLib::file_Tell(word  Handle, word *  HiWord, word *  LoWord)
{
  _virtualPort->print((char)(F_file_Tell >> 8));
  _virtualPort->print((char)(F_file_Tell));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckRes2Words(HiWord,LoWord);
}

void Diablo_Serial_4DLib::file_Unmount()
{
  _virtualPort->print((char)(F_file_Unmount >> 8));
  _virtualPort->print((char)(F_file_Unmount));
  GetAck();
}

word Diablo_Serial_4DLib::file_Write(word  Size, t4DByteArray  Source, word  Handle)
{
  _virtualPort->print((char)(F_file_Write >> 8));
  _virtualPort->print((char)(F_file_Write));
  _virtualPort->print((char)(Size >> 8));
  _virtualPort->print((char)(Size));
  WriteBytes(Source, Size);
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_BevelShadow(word  Value)
{
  _virtualPort->print((char)(F_gfx_BevelShadow >> 8));
  _virtualPort->print((char)(F_gfx_BevelShadow));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_BevelWidth(word  Value)
{
  _virtualPort->print((char)(F_gfx_BevelWidth >> 8));
  _virtualPort->print((char)(F_gfx_BevelWidth));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_BGcolour(word  Color)
{
  _virtualPort->print((char)(F_gfx_BGcolour >> 8));
  _virtualPort->print((char)(F_gfx_BGcolour));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Button(word  Up, word  x, word  y, word  buttonColour, word  txtColour, word  font, word  txtWidth, word  txtHeight, char *   text)
{
  _virtualPort->print((char)(F_gfx_Button >> 8));
  _virtualPort->print((char)(F_gfx_Button));
  _virtualPort->print((char)(Up >> 8));
  _virtualPort->print((char)(Up));
  _virtualPort->print((char)(x >> 8));
  _virtualPort->print((char)(x));
  _virtualPort->print((char)(y >> 8));
  _virtualPort->print((char)(y));
  _virtualPort->print((char)(buttonColour >> 8));
  _virtualPort->print((char)(buttonColour));
  _virtualPort->print((char)(txtColour >> 8));
  _virtualPort->print((char)(txtColour));
  _virtualPort->print((char)(font >> 8));
  _virtualPort->print((char)(font));
  _virtualPort->print((char)(txtWidth >> 8));
  _virtualPort->print((char)(txtWidth));
  _virtualPort->print((char)(txtHeight >> 8));
  _virtualPort->print((char)(txtHeight));
  WriteChars(text);
  GetAck();
}

void Diablo_Serial_4DLib::gfx_ChangeColour(word  OldColor, word  NewColor)
{
  _virtualPort->print((char)(F_gfx_ChangeColour >> 8));
  _virtualPort->print((char)(F_gfx_ChangeColour));
  _virtualPort->print((char)(OldColor >> 8));
  _virtualPort->print((char)(OldColor));
  _virtualPort->print((char)(NewColor >> 8));
  _virtualPort->print((char)(NewColor));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Circle(word  X, word  Y, word  Radius, word  Color)
{
  _virtualPort->print((char)(F_gfx_Circle >> 8));
  _virtualPort->print((char)(F_gfx_Circle));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Radius >> 8));
  _virtualPort->print((char)(Radius));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_CircleFilled(word  X, word  Y, word  Radius, word  Color)
{
  _virtualPort->print((char)(F_gfx_CircleFilled >> 8));
  _virtualPort->print((char)(F_gfx_CircleFilled));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Radius >> 8));
  _virtualPort->print((char)(Radius));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Clipping(word  OnOff)
{
  _virtualPort->print((char)(F_gfx_Clipping >> 8));
  _virtualPort->print((char)(F_gfx_Clipping));
  _virtualPort->print((char)(OnOff >> 8));
  _virtualPort->print((char)(OnOff));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_ClipWindow(word  X1, word  Y1, word  X2, word  Y2)
{
  _virtualPort->print((char)(F_gfx_ClipWindow >> 8));
  _virtualPort->print((char)(F_gfx_ClipWindow));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Cls()
{
  _virtualPort->print((char)(F_gfx_Cls >> 8));
  _virtualPort->print((char)(F_gfx_Cls));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_Contrast(word  Contrast)
{
  _virtualPort->print((char)(F_gfx_Contrast >> 8));
  _virtualPort->print((char)(F_gfx_Contrast));
  _virtualPort->print((char)(Contrast >> 8));
  _virtualPort->print((char)(Contrast));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Ellipse(word  X, word  Y, word  Xrad, word  Yrad, word  Color)
{
  _virtualPort->print((char)(F_gfx_Ellipse >> 8));
  _virtualPort->print((char)(F_gfx_Ellipse));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Xrad >> 8));
  _virtualPort->print((char)(Xrad));
  _virtualPort->print((char)(Yrad >> 8));
  _virtualPort->print((char)(Yrad));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_EllipseFilled(word  X, word  Y, word  Xrad, word  Yrad, word  Color)
{
  _virtualPort->print((char)(F_gfx_EllipseFilled >> 8));
  _virtualPort->print((char)(F_gfx_EllipseFilled));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Xrad >> 8));
  _virtualPort->print((char)(Xrad));
  _virtualPort->print((char)(Yrad >> 8));
  _virtualPort->print((char)(Yrad));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_FrameDelay(word  Msec)
{
  _virtualPort->print((char)(F_gfx_FrameDelay >> 8));
  _virtualPort->print((char)(F_gfx_FrameDelay));
  _virtualPort->print((char)(Msec >> 8));
  _virtualPort->print((char)(Msec));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_Get(word  Mode)
{
  _virtualPort->print((char)(F_gfx_Get >> 8));
  _virtualPort->print((char)(F_gfx_Get));
  _virtualPort->print((char)(Mode >> 8));
  _virtualPort->print((char)(Mode));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_GetPixel(word  X, word  Y)
{
  _virtualPort->print((char)(F_gfx_GetPixel >> 8));
  _virtualPort->print((char)(F_gfx_GetPixel));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Line(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
  _virtualPort->print((char)(F_gfx_Line >> 8));
  _virtualPort->print((char)(F_gfx_Line));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_LinePattern(word  Pattern)
{
  _virtualPort->print((char)(F_gfx_LinePattern >> 8));
  _virtualPort->print((char)(F_gfx_LinePattern));
  _virtualPort->print((char)(Pattern >> 8));
  _virtualPort->print((char)(Pattern));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_LineTo(word  X, word  Y)
{
  _virtualPort->print((char)(F_gfx_LineTo >> 8));
  _virtualPort->print((char)(F_gfx_LineTo));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_MoveTo(word  X, word  Y)
{
  _virtualPort->print((char)(F_gfx_MoveTo >> 8));
  _virtualPort->print((char)(F_gfx_MoveTo));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_Orbit(word  Angle, word  Distance, word *  Xdest, word *  Ydest)
{
  _virtualPort->print((char)(F_gfx_Orbit >> 8));
  _virtualPort->print((char)(F_gfx_Orbit));
  _virtualPort->print((char)(Angle >> 8));
  _virtualPort->print((char)(Angle));
  _virtualPort->print((char)(Distance >> 8));
  _virtualPort->print((char)(Distance));
  GetAck2Words(Xdest,Ydest);
  return 0 ;
}

word Diablo_Serial_4DLib::gfx_OutlineColour(word  Color)
{
  _virtualPort->print((char)(F_gfx_OutlineColour >> 8));
  _virtualPort->print((char)(F_gfx_OutlineColour));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Panel(word  Raised, word  X, word  Y, word  Width, word  Height, word  Color)
{
  _virtualPort->print((char)(F_gfx_Panel >> 8));
  _virtualPort->print((char)(F_gfx_Panel));
  _virtualPort->print((char)(Raised >> 8));
  _virtualPort->print((char)(Raised));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Width >> 8));
  _virtualPort->print((char)(Width));
  _virtualPort->print((char)(Height >> 8));
  _virtualPort->print((char)(Height));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Polygon(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
  _virtualPort->print((char)(F_gfx_Polygon >> 8));
  _virtualPort->print((char)(F_gfx_Polygon));
  _virtualPort->print((char)(n >> 8));
  _virtualPort->print((char)(n));
  WriteWords(Xvalues, n);
  WriteWords(Yvalues, n);
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_PolygonFilled(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
  _virtualPort->print((char)(F_gfx_PolygonFilled >> 8));
  _virtualPort->print((char)(F_gfx_PolygonFilled));
  _virtualPort->print((char)(n >> 8));
  _virtualPort->print((char)(n));
  WriteWords(Xvalues, n);
  WriteWords(Yvalues, n);
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Polyline(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
  _virtualPort->print((char)(F_gfx_Polyline >> 8));
  _virtualPort->print((char)(F_gfx_Polyline));
  _virtualPort->print((char)(n >> 8));
  _virtualPort->print((char)(n));
  WriteWords(Xvalues, n);
  WriteWords(Yvalues, n);
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_PutPixel(word  X, word  Y, word  Color)
{
  _virtualPort->print((char)(F_gfx_PutPixel >> 8));
  _virtualPort->print((char)(F_gfx_PutPixel));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_Rectangle(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
  _virtualPort->print((char)(F_gfx_Rectangle >> 8));
  _virtualPort->print((char)(F_gfx_Rectangle));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_RectangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
  _virtualPort->print((char)(F_gfx_RectangleFilled >> 8));
  _virtualPort->print((char)(F_gfx_RectangleFilled));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_ScreenCopyPaste(word  Xs, word  Ys, word  Xd, word  Yd, word  Width, word  Height)
{
  _virtualPort->print((char)(F_gfx_ScreenCopyPaste >> 8));
  _virtualPort->print((char)(F_gfx_ScreenCopyPaste));
  _virtualPort->print((char)(Xs >> 8));
  _virtualPort->print((char)(Xs));
  _virtualPort->print((char)(Ys >> 8));
  _virtualPort->print((char)(Ys));
  _virtualPort->print((char)(Xd >> 8));
  _virtualPort->print((char)(Xd));
  _virtualPort->print((char)(Yd >> 8));
  _virtualPort->print((char)(Yd));
  _virtualPort->print((char)(Width >> 8));
  _virtualPort->print((char)(Width));
  _virtualPort->print((char)(Height >> 8));
  _virtualPort->print((char)(Height));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_ScreenMode(word  ScreenMode)
{
  _virtualPort->print((char)(F_gfx_ScreenMode >> 8));
  _virtualPort->print((char)(F_gfx_ScreenMode));
  _virtualPort->print((char)(ScreenMode >> 8));
  _virtualPort->print((char)(ScreenMode));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Set(word  Func, word  Value)
{
  _virtualPort->print((char)(F_gfx_Set >> 8));
  _virtualPort->print((char)(F_gfx_Set));
  _virtualPort->print((char)(Func >> 8));
  _virtualPort->print((char)(Func));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_SetClipRegion()
{
  _virtualPort->print((char)(F_gfx_SetClipRegion >> 8));
  _virtualPort->print((char)(F_gfx_SetClipRegion));
  GetAck();
}

word Diablo_Serial_4DLib::gfx_Slider(word  Mode, word  X1, word  Y1, word  X2, word  Y2, word  Color, word  Scale, word  Value)
{
  _virtualPort->print((char)(F_gfx_Slider >> 8));
  _virtualPort->print((char)(F_gfx_Slider));
  _virtualPort->print((char)(Mode >> 8));
  _virtualPort->print((char)(Mode));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  _virtualPort->print((char)(Scale >> 8));
  _virtualPort->print((char)(Scale));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_Transparency(word  OnOff)
{
  _virtualPort->print((char)(F_gfx_Transparency >> 8));
  _virtualPort->print((char)(F_gfx_Transparency));
  _virtualPort->print((char)(OnOff >> 8));
  _virtualPort->print((char)(OnOff));
  return GetAckResp();
}

word Diablo_Serial_4DLib::gfx_TransparentColour(word  Color)
{
  _virtualPort->print((char)(F_gfx_TransparentColour >> 8));
  _virtualPort->print((char)(F_gfx_TransparentColour));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  return GetAckResp();
}

void Diablo_Serial_4DLib::gfx_Triangle(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color)
{
  _virtualPort->print((char)(F_gfx_Triangle >> 8));
  _virtualPort->print((char)(F_gfx_Triangle));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(X3 >> 8));
  _virtualPort->print((char)(X3));
  _virtualPort->print((char)(Y3 >> 8));
  _virtualPort->print((char)(Y3));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

void Diablo_Serial_4DLib::gfx_TriangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color)
{
  _virtualPort->print((char)(F_gfx_TriangleFilled >> 8));
  _virtualPort->print((char)(F_gfx_TriangleFilled));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  _virtualPort->print((char)(X3 >> 8));
  _virtualPort->print((char)(X3));
  _virtualPort->print((char)(Y3 >> 8));
  _virtualPort->print((char)(Y3));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  GetAck();
}

word Diablo_Serial_4DLib::img_ClearAttributes(word  Handle, word  Index, word  Value)
{
  _virtualPort->print((char)(F_img_ClearAttributes >> 8));
  _virtualPort->print((char)(F_img_ClearAttributes));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Darken(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Darken >> 8));
  _virtualPort->print((char)(F_img_Darken));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Disable(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Disable >> 8));
  _virtualPort->print((char)(F_img_Disable));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Enable(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Enable >> 8));
  _virtualPort->print((char)(F_img_Enable));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_GetWord(word  Handle, word  Index, word  Offset )
{
  _virtualPort->print((char)(F_img_GetWord >> 8));
  _virtualPort->print((char)(F_img_GetWord));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  _virtualPort->print((char)(Offset  >> 8));
  _virtualPort->print((char)(Offset ));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Lighten(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Lighten >> 8));
  _virtualPort->print((char)(F_img_Lighten));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_SetAttributes(word  Handle, word  Index, word  Value)
{
  _virtualPort->print((char)(F_img_SetAttributes >> 8));
  _virtualPort->print((char)(F_img_SetAttributes));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_SetPosition(word  Handle, word  Index, word  Xpos, word  Ypos)
{
  _virtualPort->print((char)(F_img_SetPosition >> 8));
  _virtualPort->print((char)(F_img_SetPosition));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  _virtualPort->print((char)(Xpos >> 8));
  _virtualPort->print((char)(Xpos));
  _virtualPort->print((char)(Ypos >> 8));
  _virtualPort->print((char)(Ypos));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_SetWord(word  Handle, word  Index, word  Offset , word  Word)
{
  _virtualPort->print((char)(F_img_SetWord >> 8));
  _virtualPort->print((char)(F_img_SetWord));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  _virtualPort->print((char)(Offset  >> 8));
  _virtualPort->print((char)(Offset ));
  _virtualPort->print((char)(Word >> 8));
  _virtualPort->print((char)(Word));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Show(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Show >> 8));
  _virtualPort->print((char)(F_img_Show));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::img_Touched(word  Handle, word  Index)
{
  _virtualPort->print((char)(F_img_Touched >> 8));
  _virtualPort->print((char)(F_img_Touched));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(Index >> 8));
  _virtualPort->print((char)(Index));
  return GetAckResp();
}

word Diablo_Serial_4DLib::media_Flush()
{
  _virtualPort->print((char)(F_media_Flush >> 8));
  _virtualPort->print((char)(F_media_Flush));
  return GetAckResp();
}

void Diablo_Serial_4DLib::media_Image(word  X, word  Y)
{
  _virtualPort->print((char)(F_media_Image >> 8));
  _virtualPort->print((char)(F_media_Image));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  GetAck();
}

word Diablo_Serial_4DLib::media_Init()
{
  _virtualPort->print((char)(F_media_Init >> 8));
  _virtualPort->print((char)(F_media_Init));
  return GetAckResp();
}

word Diablo_Serial_4DLib::media_RdSector(t4DSector  SectorIn)
{
  _virtualPort->print((char)(F_media_RdSector >> 8));
  _virtualPort->print((char)(F_media_RdSector));
  return GetAckResSector(SectorIn);
}

word Diablo_Serial_4DLib::media_ReadByte()
{
  _virtualPort->print((char)(F_media_ReadByte >> 8));
  _virtualPort->print((char)(F_media_ReadByte));
  return GetAckResp();
}

word Diablo_Serial_4DLib::media_ReadWord()
{
  _virtualPort->print((char)(F_media_ReadWord >> 8));
  _virtualPort->print((char)(F_media_ReadWord));
  return GetAckResp();
}

void Diablo_Serial_4DLib::media_SetAdd(word  HiWord, word  LoWord)
{
  _virtualPort->print((char)(F_media_SetAdd >> 8));
  _virtualPort->print((char)(F_media_SetAdd));
  _virtualPort->print((char)(HiWord >> 8));
  _virtualPort->print((char)(HiWord));
  _virtualPort->print((char)(LoWord >> 8));
  _virtualPort->print((char)(LoWord));
  GetAck();
}

void Diablo_Serial_4DLib::media_SetSector(word  HiWord, word  LoWord)
{
  _virtualPort->print((char)(F_media_SetSector >> 8));
  _virtualPort->print((char)(F_media_SetSector));
  _virtualPort->print((char)(HiWord >> 8));
  _virtualPort->print((char)(HiWord));
  _virtualPort->print((char)(LoWord >> 8));
  _virtualPort->print((char)(LoWord));
  GetAck();
}

void Diablo_Serial_4DLib::media_Video(word  X, word  Y)
{
  _virtualPort->print((char)(F_media_Video >> 8));
  _virtualPort->print((char)(F_media_Video));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  GetAck();
}

void Diablo_Serial_4DLib::media_VideoFrame(word  X, word  Y, word  Framenumber)
{
  _virtualPort->print((char)(F_media_VideoFrame >> 8));
  _virtualPort->print((char)(F_media_VideoFrame));
  _virtualPort->print((char)(X >> 8));
  _virtualPort->print((char)(X));
  _virtualPort->print((char)(Y >> 8));
  _virtualPort->print((char)(Y));
  _virtualPort->print((char)(Framenumber >> 8));
  _virtualPort->print((char)(Framenumber));
  GetAck();
}

word Diablo_Serial_4DLib::media_WriteByte(word  Byte)
{
  _virtualPort->print((char)(F_media_WriteByte >> 8));
  _virtualPort->print((char)(F_media_WriteByte));
  _virtualPort->print((char)(Byte >> 8));
  _virtualPort->print((char)(Byte));
  return GetAckResp();
}

word Diablo_Serial_4DLib::media_WriteWord(word  Word)
{
  _virtualPort->print((char)(F_media_WriteWord >> 8));
  _virtualPort->print((char)(F_media_WriteWord));
  _virtualPort->print((char)(Word >> 8));
  _virtualPort->print((char)(Word));
  return GetAckResp();
}

word Diablo_Serial_4DLib::media_WrSector(t4DSector  SectorOut)
{
  _virtualPort->print((char)(F_media_WrSector >> 8));
  _virtualPort->print((char)(F_media_WrSector));
  WriteBytes(SectorOut, 512);
  return GetAckResp();
}

word Diablo_Serial_4DLib::mem_Free(word  Handle)
{
  _virtualPort->print((char)(F_mem_Free >> 8));
  _virtualPort->print((char)(F_mem_Free));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  return GetAckResp();
}

word Diablo_Serial_4DLib::mem_Heap()
{
  _virtualPort->print((char)(F_mem_Heap >> 8));
  _virtualPort->print((char)(F_mem_Heap));
  return GetAckResp();
}

word Diablo_Serial_4DLib::peekM(word  Address)
{
  _virtualPort->print((char)(F_peekM >> 8)) ;
  _virtualPort->print((char)(F_peekM)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::pin_HI(word Pin)
{
  _virtualPort->write((char)(F_pin_HI >> 8)) ;
  _virtualPort->write((char)(F_pin_HI)) ;
  _virtualPort->write((char)(Pin >> 8)) ;
  _virtualPort->write((char)(Pin)) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::pin_LO(word Pin)
{
  _virtualPort->write((char)(F_pin_LO >> 8)) ;
  _virtualPort->write((char)(F_pin_LO)) ;
  _virtualPort->write((char)(Pin >> 8)) ;
  _virtualPort->write((char)(Pin)) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::pin_Read(word Pin)
{
  _virtualPort->write((char)(F_pin_Read >> 8)) ;
  _virtualPort->write((char)(F_pin_Read)) ;
  _virtualPort->write((char)(Pin >> 8)) ;
  _virtualPort->write((char)(Pin)) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::pin_Set(word Mode, word Pin)
{
  _virtualPort->write((char)(F_pin_Set >> 8)) ;
  _virtualPort->write((char)(F_pin_Set)) ;
  _virtualPort->write((char)(Mode >> 8)) ;
  _virtualPort->write((char)(Mode)) ;
  _virtualPort->write((char)(Pin >> 8)) ;
  _virtualPort->write((char)(Pin)) ;
  return GetAckResp() ;
}

void Diablo_Serial_4DLib::pokeM(word  Address, word  WordValue)
{
  _virtualPort->print((char)(F_pokeM >> 8)) ;
  _virtualPort->print((char)(F_pokeM)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  _virtualPort->print((char)(WordValue >> 8)) ;
  _virtualPort->print((char)(WordValue)) ;
  GetAck() ;
}

void Diablo_Serial_4DLib::putCH(word  WordChar)
{
  _virtualPort->print((char)(F_putCH >> 8)) ;
  _virtualPort->print((char)(F_putCH)) ;
  _virtualPort->print((char)(WordChar >> 8)) ;
  _virtualPort->print((char)(WordChar)) ;
  GetAck() ;
}

word Diablo_Serial_4DLib::putstr(char *  InString)
{
  _virtualPort->print((char)(F_putstr >> 8));
  _virtualPort->print((char)(F_putstr));
  WriteChars(InString);
  return GetAckResp();
}

//-----------------print----------------------------------

#ifdef AVR
void Diablo_Serial_4DLib::print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    putCH(c);
  }
}
#endif

void Diablo_Serial_4DLib::print(const String &s)
{
	int len = s.length();
	char arr[len + 1];
	s.toCharArray(arr,len + 1);
	//putstr(arr);
	for(int x=0; x<len; x++)
	{
		putCH(arr[x]);
	}
}

void Diablo_Serial_4DLib::print(const char str[])
{
  int len = strlen(str);
  for(int x = 0; x<len; x++)
  {
	putCH(str[x]);
  }
}

void Diablo_Serial_4DLib::print(char c)
{
  putCH(c);
}

void Diablo_Serial_4DLib::print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void Diablo_Serial_4DLib::print(int n, int base)
{
  print((long) n, base);
}

void Diablo_Serial_4DLib::print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

void Diablo_Serial_4DLib::print(long n, int base)
{

  if (base == 10) 
  {
    if (n < 0) 
	{
      //int t = print('-');
	  putCH('-');
      n = -n;
      printNumber(n, 10);
    }
	else
	{
	printNumber(n, 10);
	}
  } 
  else 
  {
    printNumber(n, base);
  }

}

void Diablo_Serial_4DLib::print(unsigned long n, int base)
{
  printNumber(n, base);
}

void Diablo_Serial_4DLib::print(double n, int digits)
{
  printFloat(n, digits);
}


//println

void Diablo_Serial_4DLib::println(const __FlashStringHelper *ifsh)
{
  print(ifsh);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(const String &s)
{
  print(s);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(const char c[])
{
  print(c);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(char c)
{
  print((char)c);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(unsigned char b, int base)
{
  print((unsigned char)b, base);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(int num, int base)
{
  print((int)num, base);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(unsigned int num, int base)
{
  print((unsigned int)num, base);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(long num, int base)
{
  print((long)num, base);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(unsigned long num, int base)
{
  print((unsigned long)num, base);
  putCH('\n');
  putCH('\r');
}

void Diablo_Serial_4DLib::println(double num, int digits)
{
  print((double)num, digits);
  putCH('\n');
  putCH('\r');
}


//-Private:

void Diablo_Serial_4DLib::printNumber(unsigned long n, uint8_t base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  int count = 0;
  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    buf[count] = c < 10 ? c + '0' : c + 'A' - 10;
    count++;
  } while(n);
  
  for(int x = count - 1; x>=0; x--)
  {
	putCH(buf[x]);
  }
}

void Diablo_Serial_4DLib::printFloat(double number, uint8_t digits) 
{ 
  size_t n = 0;
  if (isnan(number)) print("nan"); 
  else if (isinf(number)) print("inf"); 
  else if (number > 4294967040.0) print ("ovf");  // constant determined empirically
  else if (number <-4294967040.0) print ("ovf");  // constant determined empirically
  else{
  // Handle negative numbers
  if (number < 0.0)
  {
     putCH('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  //print((unsigned long)int_part);
  printNumber(int_part, 10);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    putCH('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    printNumber((unsigned long)toPrint, 10);
    remainder -= toPrint; 
  } 
  }
}


//--------------------------------------------------------

void Diablo_Serial_4DLib::snd_BufSize(word  Bufsize)
{
  _virtualPort->print((char)(F_snd_BufSize >> 8));
  _virtualPort->print((char)(F_snd_BufSize));
  _virtualPort->print((char)(Bufsize >> 8));
  _virtualPort->print((char)(Bufsize));
  GetAck();
}

void Diablo_Serial_4DLib::snd_Continue()
{
  _virtualPort->print((char)(F_snd_Continue >> 8));
  _virtualPort->print((char)(F_snd_Continue));
  GetAck();
}

void Diablo_Serial_4DLib::snd_Pause()
{
  _virtualPort->print((char)(F_snd_Pause >> 8));
  _virtualPort->print((char)(F_snd_Pause));
  GetAck();
}

word Diablo_Serial_4DLib::snd_Pitch(word  Pitch)
{
  _virtualPort->print((char)(F_snd_Pitch >> 8));
  _virtualPort->print((char)(F_snd_Pitch));
  _virtualPort->print((char)(Pitch >> 8));
  _virtualPort->print((char)(Pitch));
  return GetAckResp();
}

word Diablo_Serial_4DLib::snd_Playing()
{
  _virtualPort->print((char)(F_snd_Playing >> 8));
  _virtualPort->print((char)(F_snd_Playing));
  return GetAckResp();
}

void Diablo_Serial_4DLib::snd_Stop()
{
  _virtualPort->print((char)(F_snd_Stop >> 8));
  _virtualPort->print((char)(F_snd_Stop));
  GetAck();
}

void Diablo_Serial_4DLib::snd_Volume(word  Volume)
{
  _virtualPort->print((char)(F_snd_Volume >> 8));
  _virtualPort->print((char)(F_snd_Volume));
  _virtualPort->print((char)(Volume >> 8));
  _virtualPort->print((char)(Volume));
  GetAck();
}

word Diablo_Serial_4DLib::sys_Sleep(word  Units)
{
  _virtualPort->print((char)(F_sys_Sleep >> 8));
  _virtualPort->print((char)(F_sys_Sleep));
  _virtualPort->print((char)(Units >> 8));
  _virtualPort->print((char)(Units));
  return GetAckResp();
}

void Diablo_Serial_4DLib::touch_DetectRegion(word  X1, word  Y1, word  X2, word  Y2)
{
  _virtualPort->print((char)(F_touch_DetectRegion >> 8));
  _virtualPort->print((char)(F_touch_DetectRegion));
  _virtualPort->print((char)(X1 >> 8));
  _virtualPort->print((char)(X1));
  _virtualPort->print((char)(Y1 >> 8));
  _virtualPort->print((char)(Y1));
  _virtualPort->print((char)(X2 >> 8));
  _virtualPort->print((char)(X2));
  _virtualPort->print((char)(Y2 >> 8));
  _virtualPort->print((char)(Y2));
  GetAck();
}

word Diablo_Serial_4DLib::touch_Get(word  Mode)
{
  _virtualPort->print((char)(F_touch_Get >> 8));
  _virtualPort->print((char)(F_touch_Get));
  _virtualPort->print((char)(Mode >> 8));
  _virtualPort->print((char)(Mode));
  return GetAckResp();
}

void Diablo_Serial_4DLib::touch_Set(word  Mode)
{
  _virtualPort->print((char)(F_touch_Set >> 8));
  _virtualPort->print((char)(F_touch_Set));
  _virtualPort->print((char)(Mode >> 8));
  _virtualPort->print((char)(Mode));
  GetAck();
}

word Diablo_Serial_4DLib::txt_Attributes(word  Attribs)
{
  _virtualPort->print((char)(F_txt_Attributes >> 8));
  _virtualPort->print((char)(F_txt_Attributes));
  _virtualPort->print((char)(Attribs >> 8));
  _virtualPort->print((char)(Attribs));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_BGcolour(word  Color)
{
  _virtualPort->print((char)(F_txt_BGcolour >> 8));
  _virtualPort->print((char)(F_txt_BGcolour));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Bold(word  Bold)
{
  _virtualPort->print((char)(F_txt_Bold >> 8));
  _virtualPort->print((char)(F_txt_Bold));
  _virtualPort->print((char)(Bold >> 8));
  _virtualPort->print((char)(Bold));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_FGcolour(word  Color)
{
  _virtualPort->print((char)(F_txt_FGcolour >> 8));
  _virtualPort->print((char)(F_txt_FGcolour));
  _virtualPort->print((char)(Color >> 8));
  _virtualPort->print((char)(Color));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_FontID(word  FontNumber)
{
  _virtualPort->print((char)(F_txt_FontID >> 8));
  _virtualPort->print((char)(F_txt_FontID));
  _virtualPort->print((char)(FontNumber >> 8));
  _virtualPort->print((char)(FontNumber));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Height(word  Multiplier)
{
  _virtualPort->print((char)(F_txt_Height >> 8));
  _virtualPort->print((char)(F_txt_Height));
  _virtualPort->print((char)(Multiplier >> 8));
  _virtualPort->print((char)(Multiplier));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Inverse(word  Inverse)
{
  _virtualPort->print((char)(F_txt_Inverse >> 8));
  _virtualPort->print((char)(F_txt_Inverse));
  _virtualPort->print((char)(Inverse >> 8));
  _virtualPort->print((char)(Inverse));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Italic(word  Italic)
{
  _virtualPort->print((char)(F_txt_Italic >> 8));
  _virtualPort->print((char)(F_txt_Italic));
  _virtualPort->print((char)(Italic >> 8));
  _virtualPort->print((char)(Italic));
  return GetAckResp();
}

void Diablo_Serial_4DLib::txt_MoveCursor(word  Line, word  Column)
{
  _virtualPort->print((char)(F_txt_MoveCursor >> 8));
  _virtualPort->print((char)(F_txt_MoveCursor));
  _virtualPort->print((char)(Line >> 8));
  _virtualPort->print((char)(Line));
  _virtualPort->print((char)(Column >> 8));
  _virtualPort->print((char)(Column));
  GetAck();
}

word Diablo_Serial_4DLib::txt_Opacity(word  TransparentOpaque)
{
  _virtualPort->print((char)(F_txt_Opacity >> 8));
  _virtualPort->print((char)(F_txt_Opacity));
  _virtualPort->print((char)(TransparentOpaque >> 8));
  _virtualPort->print((char)(TransparentOpaque));
  return GetAckResp();
}

void Diablo_Serial_4DLib::txt_Set(word  Func, word  Value)
{
  _virtualPort->print((char)(F_txt_Set >> 8));
  _virtualPort->print((char)(F_txt_Set));
  _virtualPort->print((char)(Func >> 8));
  _virtualPort->print((char)(Func));
  _virtualPort->print((char)(Value >> 8));
  _virtualPort->print((char)(Value));
  GetAck();
}

word Diablo_Serial_4DLib::txt_Underline(word  Underline)
{
  _virtualPort->print((char)(F_txt_Underline >> 8));
  _virtualPort->print((char)(F_txt_Underline));
  _virtualPort->print((char)(Underline >> 8));
  _virtualPort->print((char)(Underline));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Width(word  Multiplier)
{
  _virtualPort->print((char)(F_txt_Width >> 8));
  _virtualPort->print((char)(F_txt_Width));
  _virtualPort->print((char)(Multiplier >> 8));
  _virtualPort->print((char)(Multiplier));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Wrap(word  Position)
{
  _virtualPort->print((char)(F_txt_Wrap >> 8));
  _virtualPort->print((char)(F_txt_Wrap));
  _virtualPort->print((char)(Position >> 8));
  _virtualPort->print((char)(Position));
  return GetAckResp();
}

word Diablo_Serial_4DLib::txt_Xgap(word  Pixels)
{
  _virtualPort->print((char)(F_txt_Xgap >> 8));
  _virtualPort->print((char)(F_txt_Xgap));
  _virtualPort->print((char)(Pixels >> 8));
  _virtualPort->print((char)(Pixels));
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::txt_Ygap(word  Pixels)
{
  _virtualPort->print((char)(F_txt_Ygap >> 8));
  _virtualPort->print((char)(F_txt_Ygap));
  _virtualPort->print((char)(Pixels >> 8));
  _virtualPort->print((char)(Pixels));
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::file_CallFunction(word  Handle, word  ArgCount, t4DWordArray  Args)
{
  _virtualPort->print((char)(F_file_CallFunction >> 8));
  _virtualPort->print((char)(F_file_CallFunction));
  _virtualPort->print((char)(Handle >> 8));
  _virtualPort->print((char)(Handle));
  _virtualPort->print((char)(ArgCount >> 8));
  _virtualPort->print((char)(ArgCount));
  WriteWords(Args, ArgCount);
  return GetAckResp();
}

word Diablo_Serial_4DLib::sys_GetModel(char *  ModelStr)
{
  _virtualPort->print((char)(F_sys_GetModel >> 8));
  _virtualPort->print((char)(F_sys_GetModel));
  return GetAckResStr(ModelStr);
}

word Diablo_Serial_4DLib::sys_GetVersion()
{
  _virtualPort->print((char)(F_sys_GetVersion >> 8));
  _virtualPort->print((char)(F_sys_GetVersion));
  return GetAckResp();
}

word Diablo_Serial_4DLib::sys_GetPmmC()
{
  _virtualPort->print((char)(F_sys_GetPmmC >> 8)) ;
  _virtualPort->print((char)(F_sys_GetPmmC)) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::writeString(word  Handle, char *  StringOut)
{
  _virtualPort->print((char)(F_writeString >> 8)) ;
  _virtualPort->print((char)(F_writeString)) ;
  _virtualPort->print((char)(Handle >> 8)) ;
  _virtualPort->print((char)(Handle)) ;
  WriteChars(StringOut) ;
  return GetAckResp() ;
}

word Diablo_Serial_4DLib::readString(word  Handle, char *  StringIn)
{
  _virtualPort->print((char)(F_readString >> 8)) ;
  _virtualPort->print((char)(F_readString)) ;
  _virtualPort->print((char)(Handle >> 8)) ;
  _virtualPort->print((char)(Handle)) ;
  return GetAckResStr(StringIn) ;
}

void Diablo_Serial_4DLib::blitComtoDisplay(word  X, word  Y, word  Width, word  Height, t4DByteArray  Pixels)
{
  _virtualPort->print((char)(F_blitComtoDisplay >> 8)) ;
  _virtualPort->print((char)(F_blitComtoDisplay)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  _virtualPort->print((char)(Width >> 8)) ;
  _virtualPort->print((char)(Width)) ;
  _virtualPort->print((char)(Height >> 8)) ;
  _virtualPort->print((char)(Height)) ;
  WriteBytes(Pixels, Width*Height*2) ;
  GetAck() ;
}

word Diablo_Serial_4DLib::file_FindFirstRet(char *  Filename, char *  StringIn)
{
  _virtualPort->print((char)(F_file_FindFirstRet >> 8)) ;
  _virtualPort->print((char)(F_file_FindFirstRet)) ;
  WriteChars(Filename) ;
  return GetAckResStr(StringIn) ;
}

word Diablo_Serial_4DLib::file_FindNextRet(char *  StringIn)
{
  _virtualPort->print((char)(F_file_FindNextRet >> 8)) ;
  _virtualPort->print((char)(F_file_FindNextRet)) ;
  return GetAckResStr(StringIn) ;
}

unsigned long Diablo_Serial_4DLib::GetBaudRate(word Newrate)
{
  unsigned long br ;
  switch(Newrate)
  {
    case BAUD_110:
      br = 110l ;
      break ;
    case BAUD_300:
      br = 300l ;
      break ;
    case BAUD_600:
      br = 600l ;
      break ;
    case BAUD_1200:
      br = 1200l ;
      break ;
    case BAUD_2400:
      br = 2400l ;
      break ;
    case BAUD_4800:
      br = 4800l ;
      break ;
    case BAUD_9600:
      br = 9600l ;
      break ;
    case BAUD_14400:
      br = 14400l ;
     break ;
    case BAUD_19200:
      br = 19200l ;
      break ;
    case BAUD_31250:
      br = 31250l ;
      break ;
    case BAUD_38400:
      br = 38400l ;
      break ;
    case BAUD_56000:
      br = 56000l ;
      break ;
    case BAUD_57600:
      br = 57600l ;
      break ;
    case BAUD_115200:
      br = 115200l ;
      break ;
    case BAUD_128000:
      br = 133928l ; // actual rate is not 128000 ;
      break ;
    case BAUD_256000:
      br = 281250l ; // actual rate is not  256000 ;
      break ;
    case BAUD_300000:
      br = 312500l ; // actual rate is not  300000 ;
      break ;
    case BAUD_375000:
      br = 401785l ; // actual rate is not  375000 ;
      break ;
    case BAUD_500000:
      br = 562500l ; // actual rate is not  500000 ;
      break ;
    case BAUD_600000:
      br = 703125l ; // actual rate is not  600000 ;
      break ;
    default:
      br = 0;
      break;
  }
  return br;
}

bool Diablo_Serial_4DLib::setbaudWait(word Newrate)
{
  if (unknownSerial && (setBaudRateExternal == NULL)) return false;
  unsigned long baudrate = GetBaudRate(Newrate);
  if (baudrate == 0) return false;
  _virtualPort->print((char)(F_setbaudWait >> 8));
  _virtualPort->print((char)(F_setbaudWait));
  _virtualPort->print((char)(Newrate >> 8));
  _virtualPort->print((char)(Newrate));
  (this->*setBaudRateInternal)(baudrate); // change this systems baud rate to match new display rate, ACK is 100ms away
  GetAck() ;
  return true;
}

void Diablo_Serial_4DLib::exSetBaudRateHndl(unsigned long newRate) {
  setBaudRateExternal(newRate);
}

void Diablo_Serial_4DLib::hwSetBaudRateHndl(unsigned long newRate) {
  ((HardwareSerial *)_virtualPort)->flush();
  ((HardwareSerial *)_virtualPort)->end();
  ((HardwareSerial *)_virtualPort)->begin(newRate);
  delay(50) ; // Display sleeps for 100
  ((HardwareSerial *)_virtualPort)->flush();
}

#ifdef SoftwareSerial_h
void Diablo_Serial_4DLib::swSetBaudRateHndl(unsigned long newRate) {
  ((SoftwareSerial *)_virtualPort)->flush();
  ((SoftwareSerial *)_virtualPort)->end();
  ((SoftwareSerial *)_virtualPort)->begin(newRate);
  delay(50) ; // Display sleeps for 100
  ((SoftwareSerial *)_virtualPort)->flush();  
}
#endif

#ifdef AltSoftSerial_h
void Diablo_Serial_4DLib::alSetBaudRateHndl(unsigned long newRate) {
  ((AltSoftSerial *)_virtualPort)->flush();
  ((AltSoftSerial *)_virtualPort)->end();
  ((AltSoftSerial *)_virtualPort)->begin(newRate);
  delay(50) ; // Display sleeps for 100
  ((AltSoftSerial *)_virtualPort)->flush();  
}
#endif		
