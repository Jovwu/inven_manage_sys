#ifndef _GOODS_FILE_H_
#define _GOODS_FILE_H_
#include "file.h"
#include "goods.h"
#include "config.h"
#include "stringtool.h"
class GoodsFile :public File
{
public:

	GoodsFile();
	bool AppendGoods(Goods* goods) const;
	Goods* GetGoods(const string GoodsString) const;

private:
	
};



#endif // !_GOODS_FILE_H_