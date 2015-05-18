//
//  IOSIAPWrapper.m
//  Brain
//
//  Created by tangwei1 on 14-5-27.
//
//

#import "IOSIAPWrapper.h"
#import "IAPurchase.h"

@implementation IOSIAPManager
{
    KKIAPDelegate* _delegate;
    
    BOOL isPurchasing;
}

static IOSIAPManager* instance = nil;
+ (IOSIAPManager *)sharedIOSIAPManager
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if ( !instance ) {
            instance = [[IOSIAPManager alloc] init];
        }
    });
    return instance;
}

+ (void)purgeIOSIAPManager
{
    if ( instance ) {
        [instance release];
        instance = nil;
    }
}

- (void)setIAPDelegate:(KKIAPDelegate *)delegate
{
    isPurchasing = NO;
    _delegate = delegate;
}

- (void)purchase:(NSString*)pid
{
    if ( !isPurchasing ) {
        isPurchasing = YES;
        
        [[IAPurchase sharedPurchase] setDelegate:(id)self];
        [[IAPurchase sharedPurchase] startRequestWithProductIdentifier:pid];
    }
}

- (void)restore
{
    if ( !isPurchasing ) {
        
        isPurchasing = YES;
        
        [[IAPurchase sharedPurchase] setDelegate:(id)self];
        [[IAPurchase sharedPurchase] restorePurchase];
        
    }
}

- (void)purchaseSuccess:(IAPurchase *)purchase
{
    // alert dialog
    [self alertMessage:NSLocalizedString(@"Thank you for your purchase!", nil)];
    
    //通知公共
    if (_delegate)
    {
        _delegate->purchaseSuccess([purchase.curProductID UTF8String]);
    }
}

- (void)purchaseFailed:(IAPurchase *)purchase
{
    // alert dialog
    [self alertMessage:NSLocalizedString(@"Sorry, Purchase Failed!", nil)];
    
    if (_delegate) {
        _delegate->purchaseFailure([purchase.curProductID UTF8String], 0);
    }
}

- (void)restoreCompletedWithProductIdentifiers:(NSArray*)transitions
{
    if (transitions.count == 0) {
        [self alertMessage:NSLocalizedString(@"Sorry, you have no transaction!", nil)];
    }else{
        
        [self alertMessage:NSLocalizedString(@"Restore successfully!", nil)];
        
        //  NSLog(@"[purchase.curProductID UTF8String] %s", [purchase.curProductID UTF8String]);
        if (_delegate)
        {
            for(int i=0;i<[transitions count];i++)
            {
                _delegate->restoreSuccess([[transitions objectAtIndex:i] UTF8String]);
            }
        }
        
    }
    
    
    
}

- (void)restoreFailed:(IAPurchase *)purchase
{
    // alert dialog
    [self alertMessage:NSLocalizedString(@"Restore failed!", nil)];
    
    if (_delegate)
    {
        _delegate->restoreFailure([purchase.curProductID UTF8String], 0);
    }
}

- (void)purchaseCanceled:(IAPurchase *)purchase
{
    // alert dialog
//    [self alertMessage:@"对不起，您的购买失败！"];
    if (_delegate)
    {
        _delegate->purchaseFailure([purchase.curProductID UTF8String], 0);
    }
}

- (void)productRequestBegin:(IAPurchase *)purchase
{
    UIWindow *curWindow=[[[UIApplication sharedApplication] windows] objectAtIndex:0];
    CGRect screenRect=[UIScreen mainScreen].applicationFrame;
    UIView *bgView=[[UIView alloc] initWithFrame:CGRectMake(0, 0,  screenRect.size.width,  screenRect.size.height)];
    [bgView setBackgroundColor:[UIColor colorWithRed:0 green:0 blue:0 alpha:0.5]];
    [bgView setTag:100000];
    
    UIActivityIndicatorViewStyle type = UIActivityIndicatorViewStyleWhite;
    if ( UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad ) {
        type = UIActivityIndicatorViewStyleWhiteLarge;
    }
    
    UIActivityIndicatorView *acView=[[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:type];
    acView.center=CGPointMake(screenRect.size.width/2.0f, screenRect.size.height/2.0f);
    [acView setTag:200000];
    [bgView addSubview:acView];
    [acView release];
    [curWindow addSubview:bgView];
    [curWindow bringSubviewToFront:bgView];
    [bgView release];
    [acView startAnimating];
}

- (void)productRequestEnd:(IAPurchase *)purchase
{
    UIWindow *curWindow=[[[UIApplication sharedApplication] windows] objectAtIndex:0];
    UIView *bgView=[curWindow viewWithTag:100000];
    UIActivityIndicatorView *acView=(UIActivityIndicatorView*)[bgView viewWithTag:200000];
    if (acView) {
        [acView stopAnimating];
        [acView removeFromSuperview];
    }
    if (bgView) {
        [bgView removeFromSuperview];
    }
    
    isPurchasing = NO;
}

- (void)productsNotReady:(IAPurchase *)purchase
{
    // alert dialog
    [self alertMessage:@"Purchase not ready."];
}

- (void)alertMessage:(NSString *)message
{
    
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:nil message:message delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alert show];
    [alert release];
}

@end
