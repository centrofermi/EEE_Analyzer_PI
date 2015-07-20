#ifndef BOSS__E3OUTFILEBASE__LIBGUARD
#define BOSS__E3OUTFILEBASE__LIBGUARD




class E3OutFileBase:public std::ofstream
{
public:
	E3OutFileBase(void);
	~E3OutFileBase(void);
	

	//open out file from string
	inline StatusCode open(std::string path)	{return open(path.c_str());};
	//open out file from const char*
	StatusCode open(const char* path);
	
	// write generic field
	template<class T> void write(T obj, UInt_16b width);
	// write floating point field
	template<class T> void write(T obj, UInt_16b width,UInt_16b precision);
	// write field
	template<class T> void write(T obj);

	//write endline
	inline void endline()  {*this<<std::endl;}; 

};




template <class T> void E3OutFileBase::write(T value, unsigned short width)
{
  *this << std::setw(width) << value;
}


template <class T> void E3OutFileBase::write(T value, unsigned short width,
                                            unsigned short precision)
{
  *this << std::setw(width) << std::setprecision(precision) << value;
}

template <class T> void E3OutFileBase::write(T value)
{
  *this << value;
}

#endif
