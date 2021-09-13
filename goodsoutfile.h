#ifndef _GOODS_OUT_FILE_H_
#define _GOODS_OUT_FILE_H_
#include "file.h"
#include "goodsout.h"
#include "config.h"
class GoodsOutFile :public File
{
public:

	GoodsOutFile();
	bool AppendGoodsOut(GoodsOut* goodsout) const;
	GoodsOut* GetGoodsOut(const string GoodsOutString) const;

private:

};



#endif // !_GOODS_OUT_FILE_H_