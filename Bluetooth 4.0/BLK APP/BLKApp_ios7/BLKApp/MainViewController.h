//
//  MainViewController.h
//  BLKApp
//
//  Created by try on 13-11-27.
//  Copyright (c) 2013年 TRY. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SerialGATT.h"

@class DeviceViewController;

@interface MainViewController : UIViewController<BTSmartSensorDelegate, UITableViewDelegate, UITableViewDataSource>

@property (strong, nonatomic) SerialGATT *sensor;
@property (nonatomic, retain) NSMutableArray *peripheralViewControllerArray;

- (IBAction)scanBLKAppDevices:(id)sender;

-(void) scanTimer:(NSTimer *)timer;

@property (weak, nonatomic) IBOutlet UITableView *btBLKAppTableView;

@property (weak, nonatomic) IBOutlet UIButton *Scan;

@end
