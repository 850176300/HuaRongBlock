/*
 * KKDialogManagerandroid.cpp
 *
 *  Created on: 2014-10-19
 *      Author: studio
 */

#include "KKDialogManager_android.h"

static KKDialogDelegate* sg_pDialogDelegate = 0;

KKDialogManager_android::KKDialogManager_android() {
	// TODO Auto-generated constructor stub

}

KKDialogManager_android::~KKDialogManager_android() {
	// TODO Auto-generated destructor stub
}

void KKDialogManager_android::setDialogDelegate(KKDialogDelegate* delegate)
{
	sg_pDialogDelegate = delegate;
}

void KKDialogManager_android::DialogNegativeCLicked(int tag)
{

	if(sg_pDialogDelegate){
		sg_pDialogDelegate->DialogNegativeCLicked(tag);
	}
}

void KKDialogManager_android::DialogPositiveCLicked(int tag)
{

	if(sg_pDialogDelegate){
		sg_pDialogDelegate->DialogPositiveCLicked(tag);
	}
}

