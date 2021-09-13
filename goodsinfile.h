#ifndef _GOODS_IN_FILE_H_
#define _GOODS_IN_FILE_H_
#include "file.h"
#include "goodsin.h"
#include "config.h"
class GoodsInFile :public File
{
public:

	GoodsInFile();
	bool AppendGoodsIn(GoodsIn* goodsin) const;
	GoodsIn* GetGoodsIn(const string GoodsInString) const;

private:

};



#endif // !_GOODS_IN_FILE_H_