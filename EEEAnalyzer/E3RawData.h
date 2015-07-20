#ifndef BOSS__E3RAWDATA__LIBGUARD
#define BOSS__E3RAWDATA__LIBGUARD



//enumerator to detect stream word type

enum DigiWordType {
  BOARD_BEGIN	= 0xbbbbbbbb,
  BOARD_END		= 0xbebebebe,
  TDC_BEGIN		= 0x00ebebeb,
  TDC_END		= 0x00eeee00,
  TDC_HEADER	= 0x20000000,
  TDC_TRAILER   = 0x30000000,
  RISING_EDGE   = 0x40000000,
  FALLING_EDGE  = 0x50000000
};



class E3RawData
{
private:

	UInt_32b _word;

public:
	E3RawData(UInt_32b word); //constructor from binary data
	E3RawData(void);
	~E3RawData(void);

	////////////////////////////////////////////
	//check word type
	////////////////////////////////////////////

	// brief return if it's board begin
	inline bool isBoardBegin()				{ return _word == BOARD_BEGIN; };

	// brief return if it's board end
	inline bool isBoardEnd()				{ return _word == BOARD_END; };

	// brief return if it's TDC begin (added by FPGA)
	inline bool isTdcBegin()				{ return (_word & 0x00ffffff) == TDC_BEGIN; };

	// brief Return true if the digi is a TDC end(added by FPGA).
	inline bool isTdcEnd()					{ return (_word & 0x00ffff00) == TDC_END; };

	// brief Return true if the digi is a TDC begin for a given TDC(added by FPGA).
	inline bool isTdcBegin(UInt_32b tdcIdx)	{ return(_word & 0xffffffff) == TDC_BEGIN + (tdcIdx << 24); };

	// brief Return true if the digi is a TDC end for a given TDC(added by FPGA).
	inline bool isTdcEnd(UInt_32b tdcIdx)	{ return (_word & 0xffffff00) == TDC_END + (tdcIdx << 24); };

	// brief Return true if the digi is a TDC Header.
	inline bool isTdcHeader()				{ return (_word & 0xf0000000) == TDC_HEADER; };

	// brief Return true if the digi is a TDC trailer.
	inline bool isTdcTrailer()				{ return (_word & 0xf0000000) == TDC_TRAILER; };

	// brief Return true if the digi is a rising edge.
	inline bool isRisingEdge()				{ return (_word & 0xf0000000) == RISING_EDGE; };

	// brief Return true if the digi is a falling edge.
	inline bool isFallingEdge()				{ return (_word & 0xf0000000) == FALLING_EDGE; };

	//brief Return true if the digi corresponds to an edge.
	inline bool isEdge()					{ return isRisingEdge() || isFallingEdge(); };

	/// \brief Return the plain payload.
	inline UInt_32b digiWord()			{ return _word; };

	//////////////////////////////////////////////////////////////////////////////////////////////
	// get hit info
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	UInt_16b getChannel();
	inline UInt_32b getPs()	{return (_word & 0x7ffff)*TDC_RESOLUTION;};        //hit time in ps unit (wrt trigger time)

	 /// \print out
	std::ostream& fillStream(std::ostream& os);
};

typedef std::vector<E3RawData> E3RawDataVec;
typedef std::vector<E3RawData>::iterator E3RawDataVecIter;

#endif