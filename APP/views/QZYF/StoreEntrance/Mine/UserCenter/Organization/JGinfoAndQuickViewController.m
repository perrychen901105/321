//
//  JGinfoAndQuick.m
//  wenyao-store
//
//  Created by chenpeng on 15/1/19.
//  Copyright (c) 2015年 xiezhenghong. All rights reserved.
//

#import "JGinfoAndQuickViewController.h"
#import "LegalPersonViewController.h"
#import "BusinessLicenseViewController.h"
#import "JGCell.h"
#import "AppDelegate.h"
#import "ZhPMethod.h"
#import "SVProgressHUD.h"
#import "JGInfomationViewController.h"
#import "JGUserViewController.h"
#import "Constant.h"
#import "OtherLicenseViewController.h"
#import "Store.h"
#import "StoreModel.h"
#import "StoreModelR.h"
#import "BranchModel.h"
#import "CheckModel.h"
#import "CertifiArrayModel.h"
#import "SoftwareUserInfoViewController.h"

#define kJGinfoAndQuickViewControllerInfoModel  @"kJGinfoAndQuickViewControllerInfoModel"

@interface JGinfoAndQuickViewController ()<UITableViewDataSource,UITableViewDelegate>

@property (nonatomic ,strong) NSMutableDictionary *infoDict;
@property (nonatomic ,strong) BranchInfoModel *infoModel;
@property (nonatomic ,strong) NSMutableArray *certificateArray;
@property (nonatomic ,strong) NSMutableArray *checkBranchInfoArr;
@property (nonatomic ,strong) NSMutableDictionary *queryBranchInfoDict;
@end
@implementation JGinfoAndQuickViewController
- (id)init{
    if (self = [super init]) {
        
        [self initPrivateObject];
    }
    return self;
}
//初始化变量
- (void)initPrivateObject
{
    self.checkBranchInfoArr = [NSMutableArray array];
    self.queryBranchInfoDict = [NSMutableDictionary dictionary];
    self.infoDict = [NSMutableDictionary dictionary];
    self.certificateArray = [NSMutableArray array];    
}

#pragma mark
#pragma mark viewWillAppear
- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    if (QWGLOBALMANAGER.currentNetWork != kNotReachable) {
        [self loadBaseInfomation];
        [self loadCertifi];
    }else{
        [self loadCacheBranchInfo];
        [self loadCacheCertifi];
    }
}
- (void)loadBaseInfomation
{
    if (!QWGLOBALMANAGER.configure.groupId) {
        return;
    }
    [Store GetBranhBranchInfoWithGroupId:QWGLOBALMANAGER.configure.groupId success:^(id responseObj) {
        self.infoModel = (BranchInfoModel *)responseObj;
        [QWUserDefault setObject:self.infoModel key:kJGinfoAndQuickViewControllerInfoModel];
        [self managerJGInfo];
    } failure:^(HttpException *e) {
    }];
}

//处理机构信息数据
- (void)managerJGInfo
{
    [self.tableMain reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setUpTableView];
    //注册退出通知
    [self getNotifType:NotifQuitOut data:nil target:self];
}

- (void)setUpTableView
{
    self.tableMain.rowHeight = 46;
    self.tableMain.scrollEnabled = NO;
    self.tableMain.delegate = self;
    self.tableMain.dataSource = self;
    self.tableMain.backgroundColor = [UIColor clearColor];
    [self.tableMain setFrame:CGRectMake(0, 0, self.tableMain.frame.size.width, APP_H-NAV_H)];
    [self.view addSubview:self.tableMain];
}

- (void)getNotifType:(Enum_Notification_Type)type data:(id)data target:(id)obj
{
    if (type == NotifQuitOut) {
        [self.certificateArray removeAllObjects];
        [self.queryBranchInfoDict removeAllObjects];
        [self.tableMain reloadData];
    }
}

- (void)loadCacheBranchInfo
{
    self.infoModel = (BranchInfoModel *)[QWUserDefault getObjectBy:kJGinfoAndQuickViewControllerInfoModel];
    [self managerJGInfo];
}

- (void)loadCacheCertifi
{
    [self.certificateArray removeAllObjects];
    [self.certificateArray addObjectsFromArray:[QWUserDefault getObjectBy:@"JGCacheCertifiInfoDataSource"]];
    [self.tableMain reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
}



#pragma mark
#pragma mark 请求证书

- (void)loadCertifi
{
    [Store QueryCertifiWithGroupId:QWGLOBALMANAGER.configure.groupId success:^(id responseObj) {
        CertifiArrayModel *arrModel = (CertifiArrayModel *)responseObj;
        [self.certificateArray removeAllObjects];
        [self.certificateArray addObjectsFromArray:arrModel.certifis];
        [self.tableMain reloadSections:[NSIndexSet indexSetWithIndex:0] withRowAnimation:UITableViewRowAnimationFade];
        [QWUserDefault setObject:self.certificateArray key:@"JGCacheCertifiInfoDataSource"];
    } failure:^(HttpException *e) {
        
    }];
}


-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.certificateArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    static NSString * cellIdentifier = @"cellIdentifier";
    JGCell * cell = (JGCell *)[tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil) {
        cell = [[NSBundle mainBundle]loadNibNamed:@"JGCell" owner:self options:nil][0];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    CertificateModel *certifiModel = self.certificateArray[indexPath.row];
    cell.titleLabel.text = certifiModel.name;
    NSString *statusStr = [NSString stringWithFormat:@"%@",certifiModel.status];
    NSInteger status = [statusStr integerValue];
    switch (status) {
        case 0: //正常
        {
            
        }
            break;
        case 1: //未完善
        {
            cell.notPerfectLabel.hidden = NO;
        }
            break;
        case 2: //过期
        {
            cell.timeOverStatus.hidden = NO;
        }
            break;
        case 3: //审核中
        {
            cell.waitStatus.hidden = NO;
        }
            break;
            
        default:
            break;
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    
    /*
     3）	type：证件类型，字符类型，必填项
     1-	营业执照
     2-	组织机构代码证
     3-	药品经营许可证
     4-	医疗器械许可证
     5-	食品流通许可证
     6-	GSP证书
     7-	税务登记证
     8-	法人/企业负责人身份证
     9-	其它
     10- 医疗机构许可证
     */
    CertificateModel *certifiModel = self.certificateArray[indexPath.row];
    
    //如果数据为空，就不用再跳转到下个界面
    if (QWGLOBALMANAGER.currentNetWork == kNotReachable && certifiModel == nil) {
        [SVProgressHUD showErrorWithStatus:kWaring33 duration:DURATION_SHORT];
        return;
    }
    NSString *typeStr = [NSString stringWithFormat:@"%@",certifiModel.type];
    
    NSInteger type = [typeStr integerValue];
    switch (type) {
        case 1: //营业执照
        {
            BusinessLicenseViewController *license = [[BusinessLicenseViewController alloc] initWithNibName:@"BusinessLicenseViewController" bundle:nil];
            license.licenseType = LicenseTypeBusiness;
            license.title = certifiModel.name;
            license.certificateModel = certifiModel;
            [self.navigationController pushViewController:license animated:YES];
        }
            break;
        case 2: //组织机构代码证
        {
            
        }
            break;
        case 3: //药品经营许可证
        {
            BusinessLicenseViewController *license = [[BusinessLicenseViewController alloc] initWithNibName:@"BusinessLicenseViewController" bundle:nil];
            license.licenseType = LicenseTypeDrug;
            license.title = certifiModel.name;
            license.certificateModel = certifiModel;
            [self.navigationController pushViewController:license animated:YES];
        }
            break;
        case 4: //医疗器械许可证
        {
            
        }
            break;
        case 5: //食品流通许可证
        {
            
        }
            break;
            //            case 6: //GSP证书  //注释掉，默认跳转到default
            //            {
            //
            //            }
            //                break;
        case 7: //税务登记证
        {
            
        }
            break;
        case 8: //法人/企业负责人身份证
        {
            LegalPersonViewController *legalVC = [[LegalPersonViewController alloc] initWithNibName:@"LegalPersonViewController" bundle:nil];
            legalVC.certificateModel = certifiModel;
            legalVC.title = certifiModel.name;
            [self.navigationController pushViewController:legalVC animated:YES];
        }
            break;
            //            case 9: //其它
            //            {
            //
            //            }
            //                break;
            //            case 10: //医疗机构许可证
            //            {
            //
            //            }
            //                break;
        default:
        {
            OtherLicenseViewController *otherLicense = [[OtherLicenseViewController alloc] initWithNibName:@"OtherLicenseViewController" bundle:nil];
            otherLicense.hidesBottomBarWhenPushed = YES;
            otherLicense.certificateModel = certifiModel;
            otherLicense.title = certifiModel.name;
            [self.navigationController pushViewController:otherLicense animated:YES];
        }
            break;
    }
}

@end