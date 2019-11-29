/* Free Used
 * ConsoleApplication导入Json文件夹可直接使用
 * MFC工程等需要设置json_reader.cpp/json_value.cpp/json_writer.cpp不包含头文件，否则不通过编译
 * 封装的Json读写函数为了防崩溃
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "json/json.h"


using namespace std;

/*******封装Json读写函数********/
int Json_ReadInt(Json::Value JV, int ori_value = 0);
double Json_ReadDouble(Json::Value JV, double ori_value = 0.0);
string Json_ReadString(Json::Value JV, string ori_value = "");
bool Json_ReadBool(Json::Value JV, bool ori_value = true);
// string UnicodeToANSI(CString strUnicode);
// CString ANSIToUnicode(string strANSI);
/******************************/

void ReadJsonFile()
{
	ifstream fin;
	fin.open("jsonfile.json");
	if (!fin)
	{
		//TCHAR("error");
		return;
	}
	ostringstream ostring;
	ostring << fin.rdbuf();
	fin.close();
	string strContext = ostring.str();
	// CharReaderBuilder
	Json::CharReaderBuilder builder;
	Json::CharReader* JsonReader(builder.newCharReader());
	Json::Value JsonRoot, ObjectTmp;
	JSONCPP_STRING errs;
	const char* pstr = strContext.c_str();
	if (!JsonReader->parse(pstr, pstr + strlen(pstr), &JsonRoot, &errs))
	{
		//TCHAR("error");
		return;
	}
	//..//
	string stringTmp; // 打印字符串
	int intTmp; // 打印整型
	double doubleTmp; // 打印浮点型
	bool boolTmp; // 打印布尔型
	// 读取字符串
	stringTmp = Json_ReadString(JsonRoot["name"]);
	cout << "name = " << stringTmp << endl;
	// 读取整型
	intTmp = Json_ReadInt(JsonRoot["age"]);
	cout << "age = " << intTmp << endl;
	// 读取浮点型数字
	doubleTmp = Json_ReadDouble(JsonRoot["height"]);
	cout << "height = " << doubleTmp << endl;
	// 读取布尔型
	boolTmp = Json_ReadBool(JsonRoot["play_football"]);
	cout << "play_football = " << boolTmp << endl;
	// 读取Json对象
	Json::Value JsonObj = JsonRoot["object"];
	intTmp = Json_ReadInt(JsonObj["sonetime"]);
	stringTmp = Json_ReadString(JsonObj["someone"]);
	stringTmp = Json_ReadString(JsonObj["somewhere"]);
	// 读取数字数组，先读取数组对象，然后在对象内遍历
	Json::Value ArrInt = JsonRoot["number_array"];
	for (size_t i = 0; i < ArrInt.size(); i++)
	{
		intTmp = Json_ReadInt(ArrInt[i]);
	}
	// 读取字符串数组
	Json::Value ArrString = JsonRoot["string_array"];
	for (size_t j = 0; j < ArrString.size(); j++)
	{
		stringTmp = Json_ReadString(ArrString[j]);
	}
	// 读取Json对象数组
	Json::Value ObjectArray;
	ObjectArray = JsonRoot["object_array"];
	for (size_t k = 0; k < ObjectArray.size(); k++)
	{
		stringTmp = Json_ReadString(ObjectArray[k]["string1"]);
		stringTmp = Json_ReadString(ObjectArray[k]["string2"]);
	}
}

void WriteJsonFile()
{
	// 声明Json变量，这个作为根
	Json::Value JsonRoot;
	// 写入字符串
	JsonRoot["name"] = Json::Value("Denny");
	// 写入整型
	JsonRoot["age"] = Json::Value(22);
	// 写入浮点型数字
	JsonRoot["height"] = Json::Value(1.78);
	// 写入布尔型
	JsonRoot["play_football"] = Json::Value(true);
	// 写入Json对象
	Json::Value JsonObj;
	JsonObj["sometime"] = Json::Value(2018);
	JsonObj["someone"] = Json::Value("Kelly");
	JsonObj["somewhere"] = Json::Value("city");
	JsonRoot["object"] = JsonObj;
	// 单个键写入数字数组
	JsonRoot["number_array"].append(1);
	JsonRoot["number_array"].append(2);
	JsonRoot["number_array"].append(3);
	JsonRoot["number_array"].append(4);
	// 单个键写入字符串数组
	JsonRoot["string_array"].append("string01");
	JsonRoot["string_array"].append("string02");
	JsonRoot["string_array"].append("string03");
	// 写入Json对象数组，即数组由对象构成
	Json::Value JsonArr1, JsonArr2, JsonArr3;
	JsonArr1["string1"] = Json::Value("1-1");
	JsonArr1["string2"] = Json::Value("1-2");
	JsonArr2["string1"] = Json::Value("2-1");
	JsonArr2["string2"] = Json::Value("2-2");
	JsonArr3["string1"] = Json::Value("3-1");
	JsonArr3["string2"] = Json::Value("3-2");
	JsonRoot["object_array"].append(JsonArr1);
	JsonRoot["object_array"].append(JsonArr2);
	JsonRoot["object_array"].append(JsonArr3);
	// 生成Json文件储存
	ofstream fout("jsonfile.json");
	if (fout)
	{
		string strContext;
		strContext = JsonRoot.toStyledString();
		fout << strContext;
		fout.close();
	}
}

int main()
{
	WriteJsonFile();
	ReadJsonFile();
	return 0;
}

///////////////////////////////////////////////////
int Json_ReadInt(Json::Value JV, int ori_value)
{
	int result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::intValue)
		result = JV.asInt();
	return result;
}
double Json_ReadDouble(Json::Value JV, double ori_value)
{
	double result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::realValue)
		result = JV.asDouble();
	return result;
}
string Json_ReadString(Json::Value JV, string ori_value)
{
	string result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::stringValue)
		result = JV.asCString();
	return result;
}
bool Json_ReadBool(Json::Value JV, bool ori_value)
{
	bool result = ori_value;
	Json::ValueType VT = JV.type();
	if (VT == Json::ValueType::booleanValue)
		result = JV.asBool();
	return result;
}

/* VS2015
string UnicodeToANSI(CString strUnicode)
{
	USES_CONVERSION;
	std::string strANSI;
	strANSI = W2A(strUnicode.GetString());
	return strANSI;
}

CString ANSIToUnicode(string strANSI)
{
	CString strUnicode;
	strUnicode = strANSI.c_str();
	return strUnicode;
}
*/
