//
//  DataBase64.h
//  skylantern
//
//  Created by studio on 13-12-25.
//
//

#ifndef __skylantern__DataBase64__
#define __skylantern__DataBase64__

#include <iostream>

using namespace std;

enum DataType {
    eTypeInt = 0,
    eTypeFloat,
    eTypeBool,
    eTypeDouble,
    eTypeString,
};

static const std::string dataChars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

string SaveData(unsigned char const* , unsigned int len);
string ParseData(std::string const& s);
static void setValueForKey(const char* pKey,string data,int dataType);

static int getIntegerForKey(const char* pKey);

static void setIntegerForKey(const char* pKey, int value);

static float getFloatForKey(const char* pKey);

static void setFloatForKey(const char* pKey, float value);
static double getDoubleForKey(const char* pKey);

static void setDoubleForKey(const char* pKey, float value);
static bool getBoolForKey(const char* pKey);

static void setBoolForKey(const char* pKey, bool value);

static string getStringForKey(const char* pKey);

static void setStringForKey(const char* pKey, string value);


static inline bool baseData(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string SaveData(unsigned char const* bytes_to_encode, unsigned int in_len) {
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; (i <4) ; i++)
                ret += dataChars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        
        for (j = 0; (j < i + 1); j++)
            ret += dataChars[char_array_4[j]];
        
        while((i++ < 3))
            ret += '=';
        
    }
    
    return ret;
    
}
std::string ParseData(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;
    
    while (in_len-- && ( encoded_string[in_] != '=') && baseData(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = dataChars.find(char_array_4[i]);
            
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            
            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;
        
        for (j = 0; j <4; j++)
            char_array_4[j] = dataChars.find(char_array_4[j]);
        
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        
        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }
    
    return ret;
}
static int getIntegerForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = UserDefault::getInstance()->getStringForKey(key.c_str());
    //std::string data = UserDefault::getInstance()->getStringForKey(pKey);//注释后，使用键值加密，开启，注释上句使用值加密
    data = ParseData(data);
    __String *str = __String::create(data);
    return str->intValue();
}

static void setIntegerForKey(const char* pKey, int value)
{
    char buffer[50];
    sprintf(buffer,"%d",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    setValueForKey(key.c_str(), data, eTypeInt);
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
    //    //UserDefault::getInstance()->setStringForKey(pKey, data);//注释后，使用键值加密，开启，注释上句使用值加密
    //    UserDefault::getInstance()->flush();
}

static float getFloatForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = UserDefault::getInstance()->getStringForKey(key.c_str());
    data = ParseData(data);
    __String *str = __String::create(data);
    return str->floatValue();
}

static void setFloatForKey(const char* pKey, float value)
{
    char buffer[50];
    sprintf(buffer,"%f",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    setValueForKey(key.c_str(), data, eTypeFloat);
    
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
}

static double getDoubleForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = UserDefault::getInstance()->getStringForKey(key.c_str());
    data = ParseData(data);
    __String *str = __String::create(data);
    return str->doubleValue();
}

static void setDoubleForKey(const char* pKey, float value)
{
    char buffer[50];
    sprintf(buffer,"%f",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    setValueForKey(key.c_str(), data, eTypeFloat);
    
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
}

static bool getBoolForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = UserDefault::getInstance()->getStringForKey(key.c_str());
    data = ParseData(data);
    __String *str = __String::create(data);
    return str->boolValue();
}

static void setBoolForKey(const char* pKey, bool value)
{
    char buffer[50];
    sprintf(buffer,"%d",value);
    std::string data = buffer;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    setValueForKey(key.c_str(), data, eTypeFloat);
    
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
}


static string getStringForKey(const char* pKey)
{
    std::string key = pKey;
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()), key.length());
    std::string data = UserDefault::getInstance()->getStringForKey(key.c_str());
    data = ParseData(data);
    return data;
}

static void setStringForKey(const char* pKey, string value)
{
    std::string data = value;
    std::string key = pKey;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    key = SaveData(reinterpret_cast<const unsigned char*>(key.c_str()),key.length());
//    setValueForKey(key.c_str(), data, eTypeFloat);
    
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
    UserDefault::getInstance()->flush();
}


static void setValueForKey(const char* pKey,string data,int dataType)
{
    switch (dataType) {
        case eTypeBool:{
            bool boolValue = atoi(data.c_str());
            UserDefault::getInstance()->setBoolForKey(pKey, boolValue);
            break;
        }
        case eTypeDouble:{
            double doubleValue = strtod(data.c_str(),NULL);
            UserDefault::getInstance()->setDoubleForKey(pKey, doubleValue);
            break;
        }
        case eTypeFloat:{
            double doubleValue = strtof(data.c_str(),NULL);
            UserDefault::getInstance()->setFloatForKey(pKey, doubleValue);
            break;
        }
        case eTypeInt:{
            double doubleValue = atoi(data.c_str());
            UserDefault::getInstance()->setFloatForKey(pKey, doubleValue);
            break;
        }
        case eTypeString:{
            UserDefault::getInstance()->setStringForKey(pKey, data);
            break;
        }
            
            
            
        default:
            break;
    }
    
    UserDefault::getInstance()->flush();
}

#endif /* defined(__skylantern__DataBase64__) */
