/*
 * KKDialogManagerandroid.h
 *
 *  Created on: 2014-10-19
 *      Author: studio
 */

#ifndef KKDIALOGMANAGERANDROID_H_
#define KKDIALOGMANAGERANDROID_H_

#include "KKDialogDelegate.h"

class KKDialogManager_android {
public:
	KKDialogManager_android();
	virtual ~KKDialogManager_android();
	static void setDialogDelegate(KKDialogDelegate* delegate);

    static void DialogNegativeCLicked(int tag);

    static void DialogPositiveCLicked(int tag);
};

#endif /* KKDIALOGMANAGERANDROID_H_ */
