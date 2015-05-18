//
//  KKLeaderboardAPI.cpp
//  BrainFootball
//
//  Created by tomwey on 6/18/14.
//
//

#include "KKLeaderboardAPI.h"
#include "KKShare.h"
#define kGetLeaderboardsTag "Get Leaderboards"
#define kGetScoresTag       "Get Scores"
#define kPostScoreTag       "Post Score"

/*
 * 获取该游戏下面的所有排行榜
 * @param appKey 游戏惟一标示符
 */
void KKLeaderboardAPI::requestLeaderboards(const char* appKey)
{
    HttpRequest* request = new HttpRequest();
    __String* url = __String::createWithFormat("%s/games/%s/leaderboards",
                                               m_pAPIHostName,
                                               appKey);
    log("获取排行榜: %s", url->getCString());
    
    request->setUrl(url->getCString());
    request->setRequestType(HttpRequest::Type::GET);
    request->setTag(kGetLeaderboardsTag);
    request->setResponseCallback(this,
                                 httpresponse_selector(KKLeaderboardAPI::onHttpRequestCompleted));
    HttpClient::getInstance()->send(request);
    request->release();
}

/*
 * 获取某个排行榜下的所有分数
 * @param leaderboardId 排行榜ID
 */
void KKLeaderboardAPI::requestScoresForLeaderboard(int leaderboardId)
{
    HttpRequest* request = new HttpRequest();
    __String* url = __String::createWithFormat("%s/leaderboards/%d/users?uid=%s",
                                               m_pAPIHostName,
                                               leaderboardId,KKShare::getUDID());
    
    log("获取排行榜下面的分数: %s", url->getCString());
    
    request->setUrl(url->getCString());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this,
        httpresponse_selector(KKLeaderboardAPI::onHttpRequestCompleted));
    request->setTag(kGetScoresTag);
    HttpClient::getInstance()->send(request);
    request->release();
}

/*
 * 上传分数到某个排行榜
 * @param leaderboardId 排行榜ID
 * @param player 当前玩家
 * @param score 分数
 */
void KKLeaderboardAPI::uploadScoreToLeaderboard(int leaderboardId,
                              KKPlayer* player,
                              KKScore* score)
{
    HttpRequest* request = new HttpRequest();
    __String* url = __String::createWithFormat("%s/leaderboards/%d/users",
                                               m_pAPIHostName,
                                               leaderboardId);
    log("上传分数: %s", url->getCString());
    
    request->setUrl(url->getCString());
    request->setRequestType(HttpRequest::Type::POST);
    request->setTag(kPostScoreTag);
    
    __String* postString = __String::createWithFormat("score=%d&uid=%s&uname=%s",
                                                      score->getScore(),
                                                      player->getUDID(),
                                                      player->getName());
    log("上传内容：%s", postString->getCString());
    const char* buffer = postString->getCString();
    request->setRequestData(buffer, strlen(buffer));
    request->setResponseCallback(this,
                                 httpresponse_selector(KKLeaderboardAPI::onHttpRequestCompleted));
    HttpClient::getInstance()->send(request);
    request->release();
}

void KKLeaderboardAPI::onHttpRequestCompleted(HttpClient *client,
                                              HttpResponse *response)
{
    HttpRequest* request = response->getHttpRequest();
    if ( request->getRequestType() == HttpRequest::Type::POST ) {
        if ( strcmp(request->getTag(),kPostScoreTag) == 0 &&
            response->getResponseCode() == 201 ) {
            // 上传分数
            this->onLoadedSuccessfully(NULL, kRequestResourceTypeUploadScore);
        } else {
            this->onLoadedFailure(kRequestPostScoreErrorCode);
        }
    } else {
        // Get请求
        if ( !response->isSucceed() ) {
            if ( strcmp(request->getTag(), kGetLeaderboardsTag) == 0 ) {
                this->onLoadedFailure(kRequestGetLeaderboardsErrorCode);
            } else if ( strcmp(request->getTag(), kGetScoresTag) == 0 ) {
                this->onLoadedFailure(kRequestGetScoresErrorCode);
            }
        } else {
            std::vector<char> *data = response->getResponseData();
            
            char* json = new char[data->size() + 1];
            for (unsigned int i=0; i<data->size(); i++) {
                json[i] = (*data)[i];
            }
            
            json[data->size()] = '\0';
            
            this->parseJsonForTag(request->getTag(), json);
        }
    }
}

void KKLeaderboardAPI::parseJsonForTag(const char *tag, const char *json)
{
    Ref* result = NULL;
    kRequestResourceType type;
    if ( strcmp(tag, kGetLeaderboardsTag) == 0 ) {
        result = KKLeaderboardJsonParser::parseLeaderboards(json);
        type = kRequestResourceTypeLeaderboards;
    } else if ( strcmp(tag, kGetScoresTag ) == 0 ) {
        result = KKLeaderboardJsonParser::parseScores(json, this->getTag());
        type = kRequestResourceTypeScores;
    }
    
    this->onLoadedSuccessfully(result, type);
}

void KKLeaderboardAPI::onLoadedSuccessfully(cocos2d::Ref *result,
                                            kRequestResourceType type)
{
    if ( m_pDelegate ) {
        m_pDelegate->onLoadedSuccessfully(result, type);
    }
}

void KKLeaderboardAPI::onLoadedFailure(int errorCode)
{
    std::cout<<"onLoadedFailure--"<<m_pDelegate<<std::endl;
    if ( m_pDelegate ) {
        m_pDelegate->onLoadedFailure(errorCode);
    }
}