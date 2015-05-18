//
//  SceneManager.h
//  HuaRongStreet
//
//  Created by liuwei on 14-11-8.
//
//

#ifndef __HuaRongStreet__SceneManager__
#define __HuaRongStreet__SceneManager__

#include <iostream>
#include "SingleTon.h"
#include "SuperGlobal.h"

class SceneManager: public SingleTon<SceneManager>{
    friend class SingleTon<SceneManager>;
public:
    SceneManager();
    void gotoloading();
    void gotoHomeLayer();
    void gotoLevelLayer(LevelTitle* thetitle);
    void gotoPlayGame(LevelDescripe* descripe);
    void gotoShopLayer();
    void gotoVedioLayer();
};
#endif /* defined(__HuaRongStreet__SceneManager__) */
