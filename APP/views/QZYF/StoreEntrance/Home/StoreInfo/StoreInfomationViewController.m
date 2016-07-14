//
//  StoreInfomationViewController.m
//  wenYao-store
//
//  Created by Yang Yuexia on 16/5/6.
//  Copyright © 2016年 carret. All rights reserved.
//


/*
    本店信息
    api/branch/info          查询机构详细信息
    h5/rpt/ref/getRefCode    获取REF分享code
    api/branch/info/check    药店段信息完善性检测
 */

#import "StoreInfomationViewController.h"
#import "RatingView.h"
#import "StoreInfomationCell.h"
#import "SJAvatarBrowser.h"
#import "Store.h"
#import "InstitutionInfoViewController.h"
#import "WebDirectViewController.h"
#import "ShowBranchCodeViewController.h"
#import "JGPharmacistViewController.h"
#import "JGinfoAndQuickViewController.h"
#import "EmployInfoViewController.h"
#import "RefCode.h"
#import "NSString+WPAttributedMarkup.h"
#import "RefCodeModelR.h"
#import "BranchAppraiseViewController.h"
#import "EvaluationViewController.h"
#import "OrderPhoneViewController.h"
#import "ShippingMethodViewController.h"
#import "PharmacistInfoViewController.h"
#import "StoreInfomationCoverView.h"
#import "StoreDetailViewController.h"
#import "PayMentViewController.h"

@interface StoreInfomationViewController ()<UITableViewDataSource,UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (strong, nonatomic) IBOutlet UIView *tableHeaderView;

@property (weak, nonatomic) IBOutlet UIImageView *headImageView;    //头像
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;           //标题
@property (weak, nonatomic) IBOutlet RatingView *starView;          //星级展示
@property (weak, nonatomic) IBOutlet UILabel *starLabel;            //星级文字
@property (weak, nonatomic) IBOutlet UILabel *shareLbel;            //分享按钮
@property (weak, nonatomic) IBOutlet UIButton *shareButton;         //分享文案


@property (weak, nonatomic) IBOutlet NSLayoutConstraint *title_layout_height;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *title_layout_top;

@property (strong, nonatomic) NSMutableArray *titleArray;
@property (strong, nonatomic) NSMutableArray *imageArray;

@property (nonatomic ,strong) StoreGroupDetail  *groupModel;

//门店分享
- (IBAction)storeShareAction:(id)sender;

@end

@implementation StoreInfomationViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = @"本店信息";
    
    self.titleArray = [NSMutableArray array];
    self.imageArray = [NSMutableArray array];
    
    // 设置不同情况下的 显示的list
    [self configureArray];
    
    self.tableView.tableHeaderView = self.tableHeaderView;
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    
    //查询本店的信息
    [self getJGInfo];
    
    //开通微商时显示分享的提示蒙层
    ShowStoreInfomationCover();
}

#pragma mark ---- 设置不同情况下的 显示的list ----

- (void)configureArray
{
    if (AUTHORITY_ROOT) {
        
        // 主账号
        
        //开通微商
        self.titleArray = [[NSMutableArray alloc]initWithObjects:@[@"本店二维码",@"订单评价",@"接单电话",@"配送方式"],@[@"药师信息",@"我的机构",@"店员信息",@"商家品牌宣传"],nil];
        self.imageArray = [[NSMutableArray alloc]initWithObjects:@[@"ic_common_three",@"ic_common_two",@"ic_common_one",@"ic_common_four"],@[@"icon_medicineInformation_one",@"icon_medicineInformation_three",@"icon_medicineInformation_four",@"icon_medicineInformation_two"],nil];
        
        
        //            self.titleArray = [[NSMutableArray alloc]initWithObjects:@[@"门店信息",@"接单电话",@"配送方式",@"支付方式",@"订单评价",@"本店二维码"],@[@"药师信息",@"我的机构",@"店员信息",@"商家品牌宣传"],nil];
        //            self.imageArray = [[NSMutableArray alloc]initWithObjects:@[@"门店信息",@"ic_common_one",@"ic_common_four",@"支付方式",@"ic_common_two",@"ic_common_three"],@[@"icon_medicineInformation_one",@"icon_medicineInformation_three",@"icon_medicineInformation_four",@"icon_medicineInformation_two"],nil];
        
        
    }else
    {
        // 子账号
        
        self.titleArray = [[NSMutableArray alloc]initWithObjects:@[@"本店二维码",@"订单评价",@"接单电话",@"配送方式",@"商家品牌宣传"],nil];
        self.imageArray = [[NSMutableArray alloc]initWithObjects:@[@"ic_common_three",@"ic_common_two",@"ic_common_one",@"ic_common_four",@"icon_medicineInformation_two"],nil];
    }
}

#pragma mark ---- 查询本店信息 ----

- (void)getJGInfo
{
    if(!QWGLOBALMANAGER.loginStatus)
        return;
    if (QWGLOBALMANAGER.currentNetWork == kNotReachable)
    {
        //取缓存数据
        self.groupModel =[QWUserDefault getObjectBy:[NSString stringWithFormat:@"storeInfo%@",QWGLOBALMANAGER.configure.groupId]];
        [self setUpTopHeaderUI];
        [self.tableView reloadData];
    }
    else
    {
        //网络请求数据
        HttpClientMgr.progressEnabled = NO;
        [Store GetBranhGroupDetailWithGroupId:QWGLOBALMANAGER.configure.groupId success:^(id DFModel) {
            self.groupModel =  [StoreGroupDetail parse:DFModel];
            if ([self.groupModel.apiStatus integerValue] == 0) {
                [self setUpTopHeaderUI];
                [self.tableView reloadData];
                [QWUserDefault setObject:self.groupModel key:[NSString stringWithFormat:@"storeInfo%@",QWGLOBALMANAGER.configure.groupId]];
            }
        } failure:^(HttpException *e) {
        }];
    }
}

#pragma mark ---- 设置 headerView ----

- (void)setUpTopHeaderUI
{
    NSString *tempStr = self.groupModel.name;

    //简称
    CGSize size = [QWGLOBALMANAGER sizeText:tempStr font:fontSystem(kFontS1) limitWidth:self.titleLabel.frame.size.width];
    self.titleLabel.text = tempStr;
    if (size.height > 39) {
        self.title_layout_height.constant = 39;
        self.title_layout_top.constant = 13;
    }else{
        self.title_layout_height.constant = size.height;
        self.title_layout_top.constant = 20;
    }
    
    //头像
    self.headImageView.layer.masksToBounds = YES;
    self.headImageView.layer.cornerRadius = 6.0f;
    [self.headImageView setImageWithURL:[NSURL URLWithString:self.groupModel.url] placeholderImage:[UIImage imageNamed:@"img_pharmacy"] completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType) {
    }];
    
    //分享
    self.shareLbel.layer.cornerRadius = 4.0;
    self.shareLbel.layer.masksToBounds = YES;

    
    //设置星级显示
    [self.starView setImagesDeselected:@"2_15" partlySelected:@"2_19" fullSelected:@"2_17" andDelegate:nil];
    NSUInteger starValue = [self.groupModel.mshopStar integerValue];
    if(starValue < [self.groupModel.mshopStar integerValue])
    {
        starValue = [self.groupModel.mshopStar integerValue];
    }
    float value = starValue;
    
    [self.starView displayRating:(value/2)];
    self.starView.userInteractionEnabled = NO;
    
    //开通微商时显示分享按钮和星级文案
    if (QWGLOBALMANAGER.configure.storeType == 3) {
        self.starLabel.hidden = NO;
        self.starLabel.text = [NSString stringWithFormat:@"%.1f",value/2];
        self.shareButton.hidden = NO;
        self.shareLbel.hidden = NO;
        self.shareButton.enabled = YES;
    }else{
        self.starLabel.hidden = YES;
        self.shareLbel.hidden = YES;
        self.shareLbel.hidden = YES;
        self.shareButton.enabled = NO;
    }
    
    self.tableView.tableHeaderView = self.tableHeaderView;
    [self.tableView reloadData];
}

#pragma mark ---- UITableViewDelegate ----
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    return  47;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    
    return self.titleArray.count;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    return ((NSArray *)self.titleArray[section]).count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    if (section==0) {
        return 0;
    }
    return 7.0f;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    
    UIView *view = [[UIView alloc]initWithFrame:CGRectMake(0, 0, APP_W, 7)];
    view.backgroundColor = RGBHex(0xecf0f1);
    return view;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.1;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    StoreInfomationCell *cell = [tableView dequeueReusableCellWithIdentifier:@"StoreInfomationCell"];
    
    cell.titleLabel.text = self.titleArray[indexPath.section][indexPath.row];
    cell.iconImage.image = [UIImage imageNamed:self.imageArray[indexPath.section][indexPath.row]];
    cell.redPoint.hidden = YES;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (AUTHORITY_ROOT) { // 主账号
        
        if (indexPath.section == 0 && indexPath.row == 0)
        {
            //本店二维码
            [self showBranchCode];
            
        }else if (indexPath.section == 0 && indexPath.row == 1)
        {
            //订单评价
            [self orderEvaluate];
            
        }else if (indexPath.section == 0 && indexPath.row == 2)
        {
            //接单电话
            [self orderPhone];
            
        }else if (indexPath.section == 0 && indexPath.row == 3)
        {
            //配送方式
            [self shippingMethods];
            
        }else if (indexPath.section == 1 && indexPath.row == 0)
        {
            //药师信息
            PharmacistInfoViewController *vc = [[UIStoryboard storyboardWithName:@"StoreInfo" bundle:nil] instantiateViewControllerWithIdentifier:@"PharmacistInfoViewController"];
            vc.hidesBottomBarWhenPushed = YES;
            [self.navigationController pushViewController:vc animated:YES];
            
        }else if (indexPath.section == 1 && indexPath.row == 1)
        {
            //我的机构
            JGinfoAndQuickViewController * baseInfo = [[JGinfoAndQuickViewController alloc]init];
            baseInfo.title = @"我的机构";
            baseInfo.hidesBottomBarWhenPushed = YES;
            [self.navigationController pushViewController:baseInfo animated:YES];
            
        }else if (indexPath.section == 1 && indexPath.row == 2)
        {
            //店员信息
            EmployInfoViewController *employ = [[EmployInfoViewController alloc] init];
            employ.hidesBottomBarWhenPushed = YES;
            [self.navigationController pushViewController:employ animated:YES];
            
        }else if (indexPath.section == 1 && indexPath.row == 3)
        {
            //商家品牌宣传
            [self previewTheBranchOfLogo];
        }
        
    }else
    {
        //子账号
        
        if (indexPath.row == 0)
        {
            //本店二维码
            [self showBranchCode];
            
        }else if (indexPath.row == 1)
        {
            //订单评价
            [self orderEvaluate];
            
        }else if (indexPath.row == 2)
        {
            if (QWGLOBALMANAGER.configure.storeType == 3)
            {
                //接单电话
                [self orderPhone];
            }else
            {
                //商家品牌宣传
                [self previewTheBranchOfLogo];
            }
            
        }else if (indexPath.row == 3)
        {
            //配送方式
            [self shippingMethods];
            
        }else if (indexPath.row == 4)
        {
            //商家品牌宣传
            [self previewTheBranchOfLogo];
        }
    }
}

#pragma mark ---- 门店分享 ----
- (IBAction)storeShareAction:(id)sender
{
    if (QWGLOBALMANAGER.currentNetWork == kNotReachable)
    {
        [self showError:@"系统异常，请稍后再试"];
        return;
    } else
    {
        [QWGLOBALMANAGER statisticsEventId:@"s_bdxx_fx" withLable:@"本店信息分享" withParams:nil];
        [self getRefURLWithBlock:^(NSString *strRefURL) {
            ShareContentModel *modelShare = [ShareContentModel new];
            modelShare.title = self.groupModel.shortName.length == 0 ? self.groupModel.name : self.groupModel.shortName;
            modelShare.content = @"多种优惠商品等着你来选择";
            modelShare.shareLink = strRefURL;
            modelShare.typeShare = ShareTypeMerchant;
            modelShare.imgURL = self.groupModel.url;
            
            ShareSaveLogModel *modelR = [ShareSaveLogModel new];
            modelR.shareObj = @"19"; // 门店分享统计
            modelR.shareObjId = QWGLOBALMANAGER.configure.groupId;
            modelR.city = @"";
            modelShare.modelSavelog = modelR;
            
            [self popUpShareView:modelShare];
        }];
    }
}

#pragma mark ---- 本店二维码 ----
- (void)showBranchCode
{
    StoreDetailViewController *vc = [[UIStoryboard storyboardWithName:@"StoreDetail" bundle:nil] instantiateViewControllerWithIdentifier:@"StoreDetailViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
    
//    ShowBranchCodeViewController *branchCodeViewController = [[ShowBranchCodeViewController alloc] initWithNibName:@"ShowBranchCodeViewController" bundle:nil];
//    branchCodeViewController.hidesBottomBarWhenPushed = YES;
//    [self.navigationController pushViewController:branchCodeViewController animated:YES];
}

#pragma mark ---- 订单评价 ----
- (void)orderEvaluate
{
    
    PayMentViewController *vc = [[UIStoryboard storyboardWithName:@"PayMent" bundle:nil] instantiateViewControllerWithIdentifier:@"PayMentViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
    
    
//    // 本店评价  判断是否开通微商
//    if (QWGLOBALMANAGER.configure.storeType == 3) {
//        //开通微商药房
//        BranchAppraiseViewController *vc = [[UIStoryboard storyboardWithName:@"BranchAppraise" bundle:nil] instantiateViewControllerWithIdentifier:@"BranchAppraiseViewController"];
//        vc.hidesBottomBarWhenPushed = YES;
//        [self.navigationController pushViewController:vc animated:YES];
//        
//    }else{
//        //不开通微商药房
//        EvaluationViewController *viewcontroller=[[EvaluationViewController alloc] init];
//        viewcontroller.hidesBottomBarWhenPushed = YES;
//        [self.navigationController pushViewController:viewcontroller animated:YES];
//    }
}

#pragma mark ---- 接单电话 ----
- (void)orderPhone
{
    OrderPhoneViewController *vc = [[UIStoryboard storyboardWithName:@"StoreInfo" bundle:nil] instantiateViewControllerWithIdentifier:@"OrderPhoneViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark ---- 配送方式 ----
- (void)shippingMethods
{
    ShippingMethodViewController *vc = [[UIStoryboard storyboardWithName:@"StoreInfo" bundle:nil] instantiateViewControllerWithIdentifier:@"ShippingMethodViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark ---- 商家品牌宣传预览 ----
- (void)previewTheBranchOfLogo
{
    // 本地跳转H5页面
    WebDirectViewController *vcWebDirect = [[UIStoryboard storyboardWithName:@"WebDirect" bundle:nil] instantiateViewControllerWithIdentifier:@"WebDirectViewController"];
    
    // 本地跳转H5model的参数
    WebDirectLocalModel *modelLocal = [[WebDirectLocalModel alloc] init];
    modelLocal.typeLocalWeb = WebLocalTypeBranchLogoPreview;
    modelLocal.title = @"品牌宣传";
    [vcWebDirect setWVWithLocalModel:modelLocal];
    
    vcWebDirect.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vcWebDirect animated:YES];
}

#pragma mark ---- 获取refURL ----
- (void)getRefURLWithBlock:(void (^)(NSString *strRefURL))getRefIDBlock
{
    RefCodeModelR *modelR = [RefCodeModelR new];
    modelR.token = QWGLOBALMANAGER.configure.userToken;
    modelR.objId = QWGLOBALMANAGER.configure.groupId;
    modelR.objType = @"3";
    modelR.channel = @"1";
    [RefCode queryRefCode:modelR success:^(RefCodeModel *responseModel) {
        if (getRefIDBlock) {
            getRefIDBlock(responseModel.url);
        }
    } failure:^(HttpException *e) {
        [self showError:@"网络异常，请稍后重试"];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end