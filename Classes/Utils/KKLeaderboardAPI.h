//
//  KKLeaderboardAPI.h
//  BrainFootball
//
//  Created by tomwey on 6/18/14.
//
//

#ifndef __BrainFootball__KKLeaderboardAPI__
#define __BrainFootball__KKLeaderboardAPI__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "libjson/libjson.h"
#include "libjson/_internal/Source/JSONNode.h"
#include "network/HttpClient.h"
USING_NS_CC;
using namespace cocos2d::network;
USING_NS_CC_EXT;

#define kDefaultHostName "http://api.kekestudio.com"

typedef enum {
    kRequestResourceTypeLeaderboards, // 获取排行榜
    kRequestResourceTypeScores,       // 获取某个排行榜下的分数排名
    kRequestResourceTypeUploadScore,  // 上传分数到指定排行榜
} kRequestResourceType ; // 请求类型

enum {
    kRequestGetLeaderboardsErrorCode = 100,
    kRequestGetScoresErrorCode = 101,
    kRequestPostScoreErrorCode = 102,
};

class KKLeaderboardAPIDelegate
{
public:
    virtual void onLoadedSuccessfully(Ref* result, kRequestResourceType type) {};
    virtual void onLoadedFailure(int errorCode) {};
};

class KKLeaderboard;
class KKScore;
class KKPlayer;

class KKLeaderboardAPI : public Ref
{
public:
    KKLeaderboardAPI():m_pDelegate(NULL),m_pAPIHostName(kDefaultHostName),mTag(0) {}
    void setDelegate(KKLeaderboardAPIDelegate* callback)
    {
        m_pDelegate = callback;
    }
    
    void setTag(int tag)
    {
        mTag = tag;
    }
    
    int getTag()
    {
        return mTag;
    }
    
public:
    /*
     * 获取该游戏下面的所有排行榜
     * @param appKey 游戏惟一标示符
     */
    void requestLeaderboards(const char* appKey);
    
    /*
     * 获取某个排行榜下的所有分数
     * @param leaderboardId 排行榜ID
     */
    void requestScoresForLeaderboard(int leaderboardId);
    
    /*
     * 上传分数到某个排行榜
     * @param leaderboardId 排行榜ID
     * @param player 当前玩家
     * @param score 分数
     */
    void uploadScoreToLeaderboard(int leaderboardId,
                                  KKPlayer* player,
                                  KKScore* score);
    
    /*
     * 设置接口主机域名
     * @param hostName 主机域名
     * @brify 如果传入的参数为空，那么默认为：api.kekestudio.com
     */
    void setAPIHostName(const char* hostName)
    {
        m_pAPIHostName = hostName;
    }
    
    
private:
    void onHttpRequestCompleted(HttpClient* client, HttpResponse* response);
    void onLoadedSuccessfully(Ref* result, kRequestResourceType type);
    void onLoadedFailure(int errorCode);
    void parseJsonForTag(const char* tag, const char* json);
    
private:
    KKLeaderboardAPIDelegate* m_pDelegate;
    const char* m_pAPIHostName;
    int mTag;
};

// 排行榜类
class KKLeaderboard : public Ref
{
public:
    KKLeaderboard():m_pName(0),m_iID(0)
    {}
public:
    void setName(const char* name)
    {
        m_pName = name;
    }
    
    const char* getName()
    {
        return m_pName;
    }
    
    void setId(unsigned int idd)
    {
        m_iID = idd;
    }
    
    unsigned int getId()
    {
        return m_iID;
    }
private:
    const char* m_pName;
    unsigned int m_iID;
};

// 分数类
class KKScore : public Ref
{
public:
    KKScore():m_iScore(0), m_pUserName(0), m_pUserUDID(0) {}
    ~KKScore() { CC_SAFE_RELEASE(m_pUserName); }
    
public:
    void setScore(unsigned int score)
    {
        m_iScore = score;
    }
    
    unsigned int getScore()
    {
        return m_iScore;
    }
    
    void setUserName(const char* uname)
    {
        CC_SAFE_RELEASE(m_pUserName);
        m_pUserName = __String::create(uname);
        m_pUserName->retain();
    }
    
    const char* getUserName() const
    {
        return m_pUserName->getCString();
    }
    
    void setUserUDID(const char* udid)
    {
        CC_SAFE_RELEASE(m_pUserUDID);
        m_pUserUDID = __String::create(udid);
        m_pUserUDID->retain();
    }
    
    const char* getUserUDID() const
    {
        return m_pUserUDID->getCString();
    }
    
private:
    unsigned int m_iScore;
    __String* m_pUserName;
    __String* m_pUserUDID;
};

// 玩家类
class KKPlayer : public Ref
{
public:
    KKPlayer():m_pName(NULL),m_pUDID(NULL),m_pEmail(NULL)
    {}
    ~KKPlayer()
    {
        CC_SAFE_RELEASE(m_pEmail);
        CC_SAFE_RELEASE(m_pName);
        CC_SAFE_RELEASE(m_pUDID);
    }
public:
    void setEmail(const char* email)
    {
        CC_SAFE_RELEASE(m_pEmail);
        m_pEmail = __String::create(email);
        m_pEmail->retain();
    }
    
    const char* getEmail() const
    {
        return m_pEmail->getCString();
    }
    
    void setName(const char* name)
    {
        CC_SAFE_RELEASE(m_pName);
        m_pName = __String::create(name);
        m_pName->retain();
    }
    
    const char* getName() const
    {
        if ( m_pName == NULL ) return "";
        return m_pName->getCString();
    }
    
    void setUDID(const char* udid)
    {
        CC_SAFE_RELEASE(m_pUDID);
        m_pUDID = __String::create(udid);
        m_pUDID->retain();
    }
    
    const char* getUDID() const
    {
        if ( m_pUDID == NULL ) return "";
        return m_pUDID->getCString();
    }
    
private:
    __String* m_pEmail;
    __String* m_pName;
    __String* m_pUDID;
};

// json解析类
class KKLeaderboardJsonParser
{
public:
    // 解析排行榜
    static inline __Array* parseLeaderboards(const char* configJson)
    {
        // judge whether jsonData is valid
        if(!json_is_valid(configJson)) return __Array::create();
        
        JSONNode* mainNode = (JSONNode*)json_parse(configJson);
        if(!mainNode) return __Array::create();
        
        JSONNode::json_iterator itor = mainNode->begin();
        __Array* array = __Array::create();
        while(itor != mainNode->end())
        {
            if ( (*itor)->name() == "data" ) {
                JSONNode::json_iterator itorArray = (*itor)->begin();
                while ( itorArray != (*itor)->end() ) {
                    JSONNode::json_iterator itorEle = (*itorArray)->begin();
                    KKLeaderboard* lb = new KKLeaderboard();
                    while ( itorEle != (*itorArray)->end() ) {
                        if ( (*itorEle)->name() == "id" ) {
                            lb->setId((*itorEle)->as_int());
                        } else if ( (*itorEle)->name() == "name" ) {
                            lb->setName((*itorEle)->as_string().c_str());
                        }
                        ++itorEle;
                    }
                    array->addObject(lb);
                    lb->release();
                    
                    ++itorArray;
                }
                
            }
            ++itor;
        }
        JSONNode::deleteJSONNode(mainNode);
        return array;
    }
    
    // 解析分数排名
    static inline __Dictionary* parseScores(const char* configJson, int tag)
    {
        if(!json_is_valid(configJson)) return __Dictionary::create();
        
        JSONNode* mainNode = (JSONNode*)json_parse(configJson);
        if(!mainNode) return __Dictionary::create();
        
        __Dictionary* dict = __Dictionary::create();
        JSONNode::json_iterator itor = mainNode->begin();
        while(itor != mainNode->end())
        {
            if ( (*itor)->name() == "data" ) {
                JSONNode::json_iterator itorDict = ( *itor )->begin();
                while ( itorDict != (*itor)->end() ) {
                    
                    if ( (*itorDict)->name() == "total" ) {
                        dict->setObject(CCInteger::create((*itorDict)->as_int()), "total");
                    } else if ( (*itorDict)->name() == "me" ) {
                        // 解析字典
                        JSONNode::json_iterator itorMe = (*itorDict)->begin();
                        while ( itorMe !=  (*itorDict)->end() ) {
                            if ( (*itorMe)->name() == "score" ) {
                                dict->setObject(CCInteger::create((*itorMe)->as_int()), __String::createWithFormat("me.score%d", tag)->getCString());
                            } else if ( (*itorMe)->name() == "rank" ) {
                                dict->setObject(CCInteger::create((*itorMe)->as_int()), "me.rank");
                            }
                            ++itorMe;
                        }
                    } else if ( (*itorDict)->name() == "scores" ) {
                        __Array* array = __Array::create();
                        JSONNode::json_iterator itorArray = (*itorDict)->begin();
                        while ( itorArray != (*itorDict)->end() ) {
                            JSONNode::json_iterator itorEle = (*itorArray)->begin();
                            KKScore* score = new KKScore();
                            while ( itorEle != (*itorArray)->end() ) {
                                if ( (*itorEle)->name() == "score" ) {
                                    score->setScore((*itorEle)->as_int());
                                }
                                
                                if ( (*itorEle)->name() == "uname" ) {
                                    CCLog("uname: %s", (*itorEle)->as_string().c_str());
                                    score->setUserName( (*itorEle)->as_string().c_str() );
                                }
                                
                                if ( (*itorEle)->name() == "udid" ) {
                                    score->setUserUDID( (*itorEle)->as_string().c_str() );
                                }
                                
                                ++itorEle;
                            }
                            
                            array->addObject(score);
                            score->release();
                            
                            ++itorArray;
                        }
                        
                        dict->setObject(array, "scores");

                    }
                    
                    ++itorDict;
                }
            }
            ++itor;
        }
        JSONNode::deleteJSONNode(mainNode);
        return dict;
    }
};

#endif /* defined(__BrainFootball__KKLeaderboardAPI__) */
