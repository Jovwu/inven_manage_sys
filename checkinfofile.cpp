#include "checkinfofile.h"
CheckInfoFile::CheckInfoFile(const string Path):File(CHECK_INFO_RECORD+Path)
{

}

CheckInfoFile::CheckInfoFile():File(CHECK_INFO_RECORD_TEMP)
{

}

bool CheckInfoFile::AppendCheckInfo(CheckInfo* CheckInfo) const
{
	string Content;
	Content.append(CheckInfo->GetUser());
	Content.append(" ");
	Content.append(CheckInfo->GetGoods());
	Content.append(" ");
	Content.append(to_string(CheckInfo->GetOrgCount()));
	Content.append(" ");
	Content.append(to_string(CheckInfo->GetCheckCount()));
	Content.append(" ");
	Content.append(to_string(CheckInfo->GetDifference()));
	Content.append(" ");
	Content.append(CheckInfo->GetAnalyse());
	Content.append(" ");
	if (Append(Content))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CheckInfo* CheckInfoFile::GetCheckInfo(const string CheckInfoString) const
{
	//ÏÈ·Ö¸î×Ö·û´®
	vector<string> Res = Split(CheckInfoString);
	vector<string>::iterator It = Res.begin();
	CheckInfo* checkinfo = new CheckInfo(*It, *(It + 1), stoi(*(It + 2)), stoi(*(It + 3)));
	checkinfo->SetDifference(stoi(*(It + 4)));
	checkinfo->SetAnalyse(*(It + 5));
	return checkinfo;
}
