//
//  SerialGATT.h
//  BLKSoft
//
//  Created by BLKSofts on 7/13/12.
//  Copyright (c) 2012 jnhuamao.cn. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

//#define SERIAL_PERIPHERAL_SERVICE_UUID      @"FFF0"//@"FFF0" //可以看做是主服务，不干活的，就是标志
//#define SERIAL_PERIPHERAL_CHAR_RECV_UUID    @"FFF1"//@"FFF1"

//#define SERIAL_PERIPHERAL_NOTIFY_SERVICE_UUID @"FFE0"
//#define SERIAL_PERIPHERAL_CHAR_NOTIFY_UUID  @"FFE1"

/*#define mainService     0xFFA0
#define mainSub1        0xFFA1
#define mainSub2        0xFFA2
#define mainSub3        0xFFA3
#define mainSub4        0xFFA4
#define mainSub5        0xFFA5*/
#define fileService     0xFFE0
#define fileSub         0xFFE1

@protocol BTSmartSensorDelegate

@optional
- (void) peripheralFound:(CBPeripheral *)peripheral;
- (void) serialGATTCharValueUpdated: (NSString *)UUID value: (NSData *)data;
- (void) setConnect;
- (void) setDisconnect;
@end

@interface SerialGATT : NSObject<CBCentralManagerDelegate, CBPeripheralDelegate> {
    
}

@property (nonatomic, assign) id <BTSmartSensorDelegate> delegate;
@property (strong, nonatomic) NSMutableArray *peripherals;
@property (strong, nonatomic) CBCentralManager *manager;
@property (strong, nonatomic) CBPeripheral *activePeripheral;


#pragma mark - Methods for controlling the BLKSoft Sensor
-(void) setup; //controller setup

-(int) findBLKSoftPeripherals:(int)timeout;
-(void) scanTimer: (NSTimer *)timer;

-(void) connect: (CBPeripheral *)peripheral;
-(void) disconnect: (CBPeripheral *)peripheral;

-(void) write:(CBPeripheral *)peripheral data:(NSData *)data;
-(void) read:(CBPeripheral *)peripheral;
-(void) notify:(CBPeripheral *)peripheral on:(BOOL)on;


- (void) printPeripheralInfo:(CBPeripheral*)peripheral;

-(void) notification:(int)serviceUUID characteristicUUID:(int)characteristicUUID p:(CBPeripheral *)p on:(BOOL)on;
-(UInt16) swap:(UInt16)s;

-(CBService *) findServiceFromUUIDEx:(CBUUID *)UUID p:(CBPeripheral *)p;
-(CBCharacteristic *) findCharacteristicFromUUIDEx:(CBUUID *)UUID service:(CBService*)service;
-(const char *) UUIDToString:(CFUUIDRef) UUID;
-(const char *) CBUUIDToString:(CBUUID *) UUID;
-(int) compareCBUUID:(CBUUID *) UUID1 UUID2:(CBUUID *)UUID2;
-(int) compareCBUUIDToInt:(CBUUID *) UUID1 UUID2:(UInt16)UUID2;
-(UInt16) CBUUIDToInt:(CBUUID *) UUID;
-(void) writeValue:(int)serviceUUID characteristicUUID:(int)characteristicUUID p:(CBPeripheral *)p data:(NSData *)data;
-(void) readValue: (int)serviceUUID characteristicUUID:(int)characteristicUUID p:(CBPeripheral *)p;

@end
