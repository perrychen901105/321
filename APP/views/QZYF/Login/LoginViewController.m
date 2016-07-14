//
//  LoginViewController.m
//  APP
//
//  Created by qwfy0006 on 15/3/17.
//  Copyright (c) 2015年 carret. All rights reserved.
//

#import "LoginViewController.h"
#import "quickRegisterViewController.h"
#import "RegisterFailViewController.h"
#import "SearchInstitutionViewController.h"
#import "AddInfoViewController.h"
#import "ServiceSpecificationViewController.h"
#import "FinishViewController.h"
#import "Store.h"
#import "AppDelegate.h"
#import "Constant.h"
#import "SVProgressHUD.h"
#import "StoreModel.h"
#import "StoreModelR.h"
#import "UserInfoModel.h"
#import "FindAccOrPwdOneViewController.h"
#import "ComRegCheckCodeViewController.h"
#import "ContactServiceView.h"
#import "LaunchViewController.h"
#import "Circle.h"
#import "ExpertRegisterViewController.h"

@interface LoginViewController ()<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UIView *userBgView;

@property (weak, nonatomic) IBOutlet UIView *passwordBgView;

// 账号框
@property (strong, nonatomic) IBOutlet  UITextField     *text_username;

// 密码框
@property (strong, nonatomic) IBOutlet  UITextField     *text_userpwd;

// 登陆按钮
@property (strong, nonatomic) IBOutlet  UIButton        *btn_login;

// 快捷注册按钮
@property (weak, nonatomic) IBOutlet UIButton *quickRegisterButton;


// 快捷注册 Action
- (IBAction)quickRegisterAction:(id)sender;

// 登陆 Action
- (IBAction)LoginAction:(id)sender;

// 联系客服
- (IBAction)contactServiceAction:(id)sender;

// 忘记账号/密码
- (IBAction)forgetAccountOrPwdAction:(id)sender;


@end

@implementation LoginViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.title = @"问药－商家";
    self.view.backgroundColor = RGBHex(qwColor11);
    
    self.btn_login.layer.cornerRadius = 3.0f;
    self.btn_login.layer.masksToBounds = YES;
    
    self.userBgView.layer.cornerRadius = 4.0;
    self.userBgView.layer.masksToBounds = YES;
    self.userBgView.layer.borderWidth = 0.5;
    self.userBgView.layer.borderColor = RGBHex(qwColor10).CGColor;
    
    self.passwordBgView.layer.cornerRadius = 4.0;
    self.passwordBgView.layer.masksToBounds = YES;
    self.passwordBgView.layer.borderWidth = 0.5;
    self.passwordBgView.layer.borderColor = RGBHex(qwColor10).CGColor;
    
    self.quickRegisterButton.layer.borderWidth = 1.0;
    self.quickRegisterButton.layer.borderColor = RGBHex(qwColor2).CGColor;
    self.quickRegisterButton.layer.cornerRadius = 3.0f;
    self.quickRegisterButton.layer.masksToBounds = YES;
    
    self.text_username.delegate = self;
    self.text_userpwd.delegate = self;
    
    [self.text_username setValue:RGBHex(0xaaaaaa) forKeyPath:@"_placeholderLabel.textColor"];
    [self.text_userpwd setValue:RGBHex(0xaaaaaa) forKeyPath:@"_placeholderLabel.textColor"];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"注册" style:UIBarButtonItemStylePlain target:self action:@selector(commonRegister)];
    
}

#pragma mark ====
#pragma mark ==== 断网通知

- (void)getNotifType:(Enum_Notification_Type)type data:(id)data target:(id)obj{
    if (NotifNetworkDisconnect == type || NotifNetworkReconnect == type) {
        [self networkDisenable];
    }else if (type == NotifClearLoginPassword){
        self.text_userpwd.text = @"";
    }
}

- (void)networkDisenable
{
    [self.btn_login setTitle:@"登录" forState:UIControlStateNormal];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:NO animated:NO];
    
    [self setUpForDismissKeyboard];
    NSString *userName = QWGLOBALMANAGER.configure.userName;
    
    if(userName)
        self.text_username.text = userName;
    NSString *password = QWGLOBALMANAGER.configure.passWord;
    if(password)
        self.text_userpwd.text = password;
    
    if([QWUserDefault getBoolBy:APP_LOGIN_STATUS])
    {
//        [self performSelector:@selector(LoginAction:) withObject:nil afterDelay:2.5f];
        [[UIApplication sharedApplication].keyWindow addSubview:QWGLOBALMANAGER.fadeCover];
    }
}

//- (void)viewWillDisappear:(BOOL)animated
//{
//    [super viewWillDisappear:animated];
//    
//    [self.navigationController setNavigationBarHidden:YES animated:NO];
//}

#pragma mark ---- UITextFieldDelegate ----

- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    NSLog(@"===");
}

#pragma mark ---- 点击空白 收起键盘 ----

- (void)setUpForDismissKeyboard
{
    UITapGestureRecognizer *singleTapGR =
    [[UITapGestureRecognizer alloc] initWithTarget:self
                                            action:@selector(tapAnywhereToDismissKeyboard:)];
    [self.view addGestureRecognizer:singleTapGR];
}

- (void)tapAnywhereToDismissKeyboard:(UIGestureRecognizer *)gestureRecognize{
    //此method会将self.view里所有的subview的first responder都resign掉
    [UIView animateWithDuration:1 animations:^{
        
    } completion:^(BOOL finished) {
    }];
    [self.view endEditing:YES];
    
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField{
    if (textField == self.text_username) {
        [self.text_userpwd becomeFirstResponder];
        
    }else{
        [self.text_userpwd resignFirstResponder];
    }
    return YES;
}

#pragma mark ---- 登录Action ----

//登录返回状态0:新增 1:待审核 2:审核不通过 3:审核通过 4:拉黑-禁言 5:冻结 6:快捷注册
- (IBAction)LoginAction:(id)sender
{
    [QWGLOBALMANAGER statisticsEventId:@"s_dlan" withLable:@"登陆" withParams:nil];
    
    [self.view endEditing:YES];
    
    if(QWGLOBALMANAGER.currentNetWork == kNotReachable){
        [SVProgressHUD showErrorWithStatus:@"网络异常，请稍后重试" duration:DURATION_SHORT];
        return;
    }
    
    if ([[self.text_username.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]]length ]== 0 ||[[self.text_username.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]]length ]>20) {
        [SVProgressHUD showErrorWithStatus:@"请输入账号，少于20字！" duration:DURATION_SHORT];
        return;
    }
    if (self.text_userpwd.text.length == 0) {
        [SVProgressHUD showErrorWithStatus:@"请输入密码" duration:DURATION_SHORT];
        return;
    }
    
    LoginModelR *modelR = [LoginModelR new];
    modelR.account = [self.text_username.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
    modelR.password = self.text_userpwd.text;
    modelR.deviceCode = DEVICE_IDD;
    modelR.pushDeviceCode = QWGLOBALMANAGER.deviceToken;
    modelR.deviceType = @"2";
    modelR.credentials=[AESUtil encryptAESData:self.text_userpwd.text app_key:AES_KEY];
    [self.btn_login setTitle:@"正在登录" forState:UIControlStateNormal];
    self.btn_login.enabled = NO;
    
    [Store loginWithParam:modelR success:^(id obj) {
        
        [QWUserDefault setObject:@"1" key:@"ENTRANCETYPE"];
        StoreUserInfoModel *model = (StoreUserInfoModel *)obj;
        self.btn_login.enabled = YES;
        [QWGLOBALMANAGER.fadeCover fadeOut];
        if ([model.apiStatus intValue] == 0){
            
            [self.btn_login setTitle:@"登录" forState:UIControlStateNormal];
            NSMutableDictionary *setting = [NSMutableDictionary dictionary];
            setting[@"token"] = StrFromObj(model.token);
            [Circle InitByBranchWithParams:setting success:^(id obj) {
                CheckStoreStatuModel *mod = [CheckStoreStatuModel parse:obj];
                if ([mod.apiStatus integerValue] == 0) {
                    if (mod.type) {
                        QWGLOBALMANAGER.configure.storeType = mod.type;
                        QWGLOBALMANAGER.configure.storeCity = mod.city;
                        QWGLOBALMANAGER.configure.shortName = mod.branchName;
                        [QWGLOBALMANAGER saveAppConfigure];
                    }
                }else{
                    QWGLOBALMANAGER.configure.storeType = 1;
                    [QWGLOBALMANAGER saveAppConfigure];
                }
                [self saveLoginUserInfo:model];
            } failure:^(HttpException *e) {
                QWGLOBALMANAGER.configure.storeType = 1;
                [QWGLOBALMANAGER saveAppConfigure];
                [self saveLoginUserInfo:model];
            }];
            
        }else{
            
            [SVProgressHUD showErrorWithStatus:model.apiMessage duration:0.8f];
            [self.btn_login setTitle:@"登录" forState:UIControlStateNormal];
        }

    } failure:^(HttpException *e) {
        [QWGLOBALMANAGER.fadeCover fadeOut];
        self.btn_login.enabled = YES;
        [self.btn_login setTitle:@"登录" forState:UIControlStateNormal];
    }];
}


#pragma mark ---- 联系客服 ----

- (IBAction)contactServiceAction:(id)sender
{    
    [self.view endEditing:YES];
    [[ContactServiceView sharedManager] show];
}

#pragma mark ---- 忘记账号/密码 ----

- (IBAction)forgetAccountOrPwdAction:(id)sender
{
    FindAccOrPwdOneViewController *vc = [[UIStoryboard storyboardWithName:@"FindAccOrPwd" bundle:nil] instantiateViewControllerWithIdentifier:@"FindAccOrPwdOneViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark ---- 快捷注册 ----

- (IBAction)quickRegisterAction:(id)sender
{
    quickRegisterViewController *quickRV= [[quickRegisterViewController alloc]initWithNibName:@"quickRegisterViewController" bundle:nil];
    [self.navigationController pushViewController:quickRV animated:YES];
}

#pragma mark ---- 普通注册 ----

- (void)commonRegister
{
    ExpertRegisterViewController *vc = [[UIStoryboard storyboardWithName:@"ExpertLogin" bundle:nil] instantiateViewControllerWithIdentifier:@"ExpertRegisterViewController"];
    vc.hidesBottomBarWhenPushed = YES;
    vc.jumpType = 1;
    vc.navigationController = self.navigationController;
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)saveLoginUserInfo:(StoreUserInfoModel *)model
{
    NSString * str = model.token;
    if (str) {
        
        QWGLOBALMANAGER.configure.userToken = model.token;
        QWGLOBALMANAGER.configure.passportId = model.passport;
        QWGLOBALMANAGER.configure.groupId = model.branchId;
        QWGLOBALMANAGER.configure.userName = self.text_username.text;
        QWGLOBALMANAGER.configure.passWord = self.text_userpwd.text;
        QWGLOBALMANAGER.configure.type = [NSString stringWithFormat:@"%@",model.type];
        QWGLOBALMANAGER.configure.showName = model.name;
        QWGLOBALMANAGER.configure.mobile = model.mobile;
        
        /*
         1, 待审核  资料已提交页面
         2, 审核不通过  带入老数据的认证流程
         3, 审核通过    功能正常
         4, 未提交审核  认证流程
         */
        QWGLOBALMANAGER.configure.approveStatus = [NSString stringWithFormat:@"%@",model.approveStatus];
        
        if ([QWGLOBALMANAGER.configure.approveStatus integerValue] == 3) {
            // 认证通过后，清除缓存
            [QWUserDefault removeObjectBy:[NSString stringWithFormat:@"uploadLicense+%@",QWGLOBALMANAGER.configure.passportId]];
            [QWUserDefault removeObjectBy:[NSString stringWithFormat:@"OrganInfo+%@",QWGLOBALMANAGER.configure.passportId]];
        }
        
        NSString *nickName = model.branchName;
        if(nickName && ![nickName isEqual:[NSNull null]]){
            QWGLOBALMANAGER.configure.nickName = nickName;
        }else{
            QWGLOBALMANAGER.configure.nickName = @"";
        }
        NSString *avatarUrl = model.branchImgUrl;
        if(avatarUrl && ![avatarUrl isEqual:[NSNull null]]){
            QWGLOBALMANAGER.configure.avatarUrl = avatarUrl;
        }else{
            QWGLOBALMANAGER.configure.avatarUrl = @"";
        }
    
        QWGLOBALMANAGER.loginStatus = YES;
        [QWGLOBALMANAGER saveAppConfigure];
        [QWUserDefault setBool:YES key:APP_LOGIN_STATUS];
        
        [QWGLOBALMANAGER saveOperateLog:@"2"];
        
        if(QWGLOBALMANAGER.tabBar){
            [self dismissViewControllerAnimated:NO completion:nil];
        }else{
            AppDelegate *apppp = (AppDelegate *)[UIApplication sharedApplication].delegate;
            [apppp initTabBar];
        }
        //通知登录成功
        [QWGLOBALMANAGER postNotif:NotifLoginSuccess data:model object:self];
        [QWGLOBALMANAGER loginSucess];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
    
}

@end