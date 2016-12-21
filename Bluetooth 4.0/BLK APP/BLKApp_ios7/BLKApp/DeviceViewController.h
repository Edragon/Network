//
//  DeviceViewController.h
//  BLKApp
//
//  Created by try on 13-11-27.
//  Copyright (c) 2013年 TRY. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SerialGATT.h"

#define RSSI_THRESHOLD -60
#define WARNING_MESSAGE @"z"

@class CBPeripheral;
@class SerialGATT;

@interface DeviceViewController : UIViewController<BTSmartSensorDelegate>

@property (strong, nonatomic) CBPeripheral *peripheral;
@property (strong, nonatomic) SerialGATT *sensor;

//@property (strong, nonatomic) NSTimer *timer;

@property (strong, nonatomic) NSMutableArray *rssi_container; // used for contain the indexers of the lower rssi value

@property (weak, nonatomic) IBOutlet UILabel *BLKAppUUID;

- (IBAction)sendMsgToBTMode:(id)sender;
@property (weak, nonatomic) IBOutlet UITextField *MsgToBTMode;
@property (weak, nonatomic) IBOutlet UITextView *tvRecv;
@property (weak, nonatomic) IBOutlet UILabel *lbDevice;

@end
