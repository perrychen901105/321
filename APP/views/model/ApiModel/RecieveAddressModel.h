//
//  RecieveAddressModel.h
//  wenYao-store
//
//  Created by qw_imac on 16/5/16.
//  Copyright © 2016年 carret. All rights reserved.
//

#import "BaseAPIModel.h"

@interface RecieveAddressModel : BaseAPIModel

@end

@interface EmpAddressListVo : BaseAPIModel
@property (nonatomic,strong) NSArray *address;      //收货地址列表
@end

@interface EmpAddressVo : BaseAPIModel
@property (nonatomic,strong) NSString *id;//收货地址ID,
@property (nonatomic,strong) NSString *receiverLng;//收货人经度,
@property (nonatomic,strong) NSString *receiverLat;//收货人纬度,
@property (nonatomic,strong) NSString *receiver;//收货人,
@property (nonatomic,strong) NSString *receiverGender;//收货人性别（M:男，F:女）,
@property (nonatomic,strong) NSString *receiverTel;//收货人电话,
@property (nonatomic,strong) NSString *receiverProvince;// 收货人省份,
@property (nonatomic,strong) NSString *receiverCity;// 收货人城市,
@property (nonatomic,strong) NSString *receiverDist;//  收货人区县,
@property (nonatomic,strong) NSString *receiverProvinceName;//收货人省份名称,
@property (nonatomic,strong) NSString *receiverCityName;//  收货人城市名称,
@property (nonatomic,strong) NSString *receiverDistName;//  收货人区县名称,
@property (nonatomic,strong) NSString *receiverVillage ;// 收货人小区,
@property (nonatomic,strong) NSString *receiverAddr ;//收货人地址,
@property (nonatomic,assign) BOOL falgDefault ;// 是否默认地址
@end

@interface RemoveAddressVo : BaseAPIModel

@end