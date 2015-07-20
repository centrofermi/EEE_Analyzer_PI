#include "stdafx.h"
#include "E3RawData.h"

E3RawData::E3RawData(UInt_32b word) :
  _word(word)
{
}


E3RawData::E3RawData(void):_word(0)
{
}


E3RawData::~E3RawData(void)
{
}

UInt_16b E3RawData::getChannel(void)
{

	UInt_16b channel = (_word>>19) & 0x1f;  //get raw channel number

	//SWAP dei canali a gruppi di 3 
	if (channel<8) channel=7-channel;
	else if (channel<16) channel=23-channel;
	else if (channel<24) channel=39-channel;
	return channel;

}


std::ostream& E3RawData::fillStream(std::ostream& os)
{

	os << "digi word " << std::hex << std::showbase << _word
    << std::noshowbase << std::dec;
	return os;
}