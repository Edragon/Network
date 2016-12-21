//
//  DeviceViewController.m
//  BLKApp
//
//  Created by try on 13-11-27.
//  Copyright (c) 2013年 TRY. All rights reserved.
//

#import "DeviceViewController.h"
#import <AudioToolbox/AudioToolbox.h>
#import "QuartzCore/QuartzCore.h"

@interface DeviceViewController ()

@end

@implementation DeviceViewController
@synthesize MsgToBTMode;
@synthesize BLKAppUUID;
@synthesize tvRecv;
@synthesize lbDevice;

@synthesize rssi_container;

//@synthesize timer;

@synthesize peripheral;
@synthesize sensor;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    if ([self respondsToSelector:@selector(edgesForExtendedLayout)]){
        self.edgesForExtendedLayout = UIRectEdgeNone;
    }
    self.title = self.sensor.activePeripheral.name;
    self.sensor.delegate = self;
    
    tvRecv.layer.borderWidth = 1;
    tvRecv.layer.borderColor = [[UIColor grayColor] CGColor];
    tvRecv.layer.cornerRadius = 8;
    tvRecv.layer.masksToBounds = YES;
    
    BLKAppUUID.layer.borderWidth = 1;
    BLKAppUUID.layer.borderColor = [[UIColor grayColor] CGColor];
    BLKAppUUID.layer.cornerRadius = 8;
    BLKAppUUID.layer.masksToBounds = YES;
    
    lbDevice.layer.borderWidth = 1;
    lbDevice.layer.borderColor = [[UIColor grayColor] CGColor];
    lbDevice.layer.cornerRadius = 8;
    lbDevice.layer.masksToBounds = YES;
}

- (void)viewDidUnload
{
    [self setBLKAppUUID:nil];
    [self setMsgToBTMode:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

//recv data
-(void) serialGATTCharValueUpdated:(NSString *)UUID value:(NSData *)data
{
    NSString *value = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    tvRecv.text= [tvRecv.text stringByAppendingString:value];
}

//send data
- (IBAction)sendMsgToBTMode:(id)sender {
    NSData *data = [MsgToBTMode.text dataUsingEncoding:[NSString defaultCStringEncoding]];
    [sensor write:sensor.activePeripheral data:data];
}

-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    CGRect frame = textField.frame;
    int offset = frame.origin.y + 32 - (self.view.frame.size.height - 216.0);
    NSTimeInterval anm = 0.30f;
    [UIView beginAnimations:@"ResizeForKeyboard" context:nil];
    [UIView setAnimationDuration:anm];
    if(offset > 0)
    {
        self.view.frame = CGRectMake(0.0f, -offset, self.view.frame.size.width, self.view.frame.size.height);
    }
    [UIView commitAnimations];
}

-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

-(void)textFieldDidEndEditing:(UITextField *)textField
{
    if([[[UIDevice currentDevice] systemVersion]floatValue] >= 7)
    {
        self.view.frame = CGRectMake(0, 64, self.view.frame.size.width, self.view.frame.size.height);
    }else
        self.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
}

-(void)setConnect
{
    CFStringRef s = CFUUIDCreateString(kCFAllocatorDefault, (__bridge CFUUIDRef )sensor.activePeripheral.identifier);
    BLKAppUUID.text = (__bridge NSString*)s;
    tvRecv.text = @"OK+CONN";
}

-(void)setDisconnect
{
    tvRecv.text= [tvRecv.text stringByAppendingString:@"OK+LOST"];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
