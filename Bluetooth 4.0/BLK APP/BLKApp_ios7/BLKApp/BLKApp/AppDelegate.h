//
//  AppDelegate.h
//  BLKApp
//
//  Created by try on 13-11-26.
//  Copyright (c) 2013年 TRY. All rights reserved.
//

#import <UIKit/UIKit.h>

@class MainViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) MainViewController *mainViewController;
@property (strong, nonatomic) UINavigationController *navController;

@end
