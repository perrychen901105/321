/*!
 @header API.h
 @abstract 所有接口地址及相关常量
 @author .
 @version 1.00 2015/01/01  (1.00)
 */

//测试账号  手机号18675535684，密码：123456  9a960552303f3306800aa95ee6bf0a19
//uta环境测试账号13861318715   840319
//sit环境下           13915531876  111111
//jira

// hj   123456
// yff  111111

#ifndef APP_API_h
#define APP_API_h

/*
 SIT内网 IM地址 im.qw.com   端口5222
 SIT内网 WEBAPI地址  http://m.api.qw.com
 SIT外网 IM地址 im.sit.qwysfw.cn 端口5222
 SIT外网 WEBA
 P·I地址    http://m.api.sit.qwysfw.cn
 UAT内网 IM地址 im.qwysfw.cn 端口5222
 UAT内网 WEBAPI地址 http://api-m.qwysfw.cn
 UAT外网 IM地址 im.qwysfw.cn 端口6222
 UAT外网 WEBAPI地址 http://api-m.qwysfw.cn
 */



/**************************************************************************************
 *                                打包前注意切换环境                                     *
 *************************************************************************************/

//动态的生产环境
//#define DE_BASE_URL                     @"http://api-m.myquanwei.com"
//#define DE_H5_DOMAIN_URL                @"http://h5-api.myquanwei.com"
//#define DE_ONCE_URL                     @"http://222.92.113.236:9300"
//#define DE_TWICE_URL                    @"http://112.80.47.67:9300"
//#define DE_SHARE_URL                    @"http://m.myquanwei.com"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//动态的UAT环境
//#define DE_BASE_URL                     @"http://api-m.qwysfw.cn"
//#define DE_H5_DOMAIN_URL                @"http://h5-api.qwysfw.cn"
//#define DE_ONCE_URL                     @"http://58.210.18.35:9300"
//#define DE_TWICE_URL                    @"http://58.210.18.35:9300"
//#define DE_SHARE_URL                    @"http://m.qwysfw.cn"

//动态的SIT内网环境
//#define DE_BASE_URL                     @"http://m.api.qw.com"
//#define DE_H5_DOMAIN_URL                @"http://h5-api.qw.com"
//#define DE_ONCE_URL                     @"http://58.210.18.35:9400"
//#define DE_TWICE_URL                    @"http://58.210.18.35:9400"
//#define DE_SHARE_URL                    @"http://m.sit.qwysfw.cn"

//动态的sit外网环境
#define DE_BASE_URL                     @"http://m.api.sit.qwysfw.cn"
#define DE_H5_DOMAIN_URL                @"http://h5-api.sit.qwysfw.cn"
#define DE_ONCE_URL                     @"http://58.210.18.35:9400"
#define DE_TWICE_URL                    @"http://58.210.18.35:9400"
#define DE_SHARE_URL                    @"http://m.sit.qwysfw.cn"

//动态的PRE环境
//#define DE_BASE_URL                       @"http://api-m.pre.qw.com"
//#define DE_H5_DOMAIN_URL                  @"http://h5-api.pre.qw.com"
//#define DE_ONCE_URL                       @"http://192.168.0.44:9300"
//#define DE_TWICE_URL                      @"http://192.168.0.44:9300"
//#define DE_SHARE_URL                      @"http://m.pre.qw.com"
//#define DEBUG                             1

#define BASE_URL_V2           (StrIsEmpty([[NSUserDefaults standardUserDefaults] objectForKey:@"APIDOMAIN"])?[NSString stringWithFormat:@"%@/",DE_BASE_URL]:[[NSUserDefaults standardUserDefaults] objectForKey:@"APIDOMAIN"])
#define H5_DOMAIN_URL         (StrIsEmpty([[NSUserDefaults standardUserDefaults] objectForKey:@"H5DOMAIN"])?[NSString stringWithFormat:@"%@/",DE_H5_DOMAIN_URL]:[[NSUserDefaults standardUserDefaults] objectForKey:@"H5DOMAIN"])



/**************************************************************************************
 *                                打包前注意切换环境                                    *
 *************************************************************************************/

#define   APPEND                             [NSString stringWithFormat:@"%@%@",BASE_URL_V2,APPEND]
#define   API_APPEND_V2(APPEND)              [NSString stringWithFormat:@"%@%@",BASE_URL_V2,APPEND]

#define HTML5_DIRECT_ROOT_URL                BASE_URL_V2 //[NSString stringWithFormat:@"http://192.168.5.250:8183"]   //BASE_URL_V2 //
#define HTML5_DIRECT_URL                    [NSString stringWithFormat:@"%@app/html",HTML5_DIRECT_ROOT_URL]
#define HTML5_DIRECT_URL_WITH_VERSION                    [NSString stringWithFormat:@"%@/v2.2.0",HTML5_DIRECT_URL]

// MARK: 分享  每次版本更改
#define H5_SHARE_URL                    [NSString stringWithFormat:@"%@QWWEB/v401/",H5_DOMAIN_URL]
#define H5_BASE_URL                     [NSString stringWithFormat:@"%@QWAPP/v401/",H5_DOMAIN_URL]
#define H5_WAP_URL                      [NSString stringWithFormat:@"%@/QWWAP/",DE_SHARE_URL]

#define SHARE_URL                           BASE_URL_V2

// 促销活动分享
#define SHARE_URL_SYMPTOM(APPEND,APPEND2,APPEND3,APPEND4,APPEND5)               [NSString stringWithFormat:@"%@html5/v2.2.0/activities.html?id=%@&packPromotionId=%@&type=5&device=%@&account=%@&accountType=%@",SHARE_URL,APPEND,APPEND2,APPEND3,APPEND4,APPEND5]

// 优惠券使用成功的分享 
#define SHARE_URL_COUPON_SUCCESS_WITHVERSION(APPEND,APPEND2,APPEND3,APPEND4,APPEND5)           [NSString stringWithFormat:@"%@discount/html/couponSub.html?type=1&device=%@&id=%@&branchId=%@&account=%@&accountType=%@",H5_WAP_URL,APPEND,APPEND2,APPEND3,APPEND4,APPEND5]

// 慢病券使用成功的分享
#define SHARE_URL_SLOWDISEASE_SUCCESS_WITHVERSION(APPEND)           [NSString stringWithFormat:@"%@html5/v2.2.0/coupon.html?type=3&device=%@",SHARE_URL,APPEND]

// 商家门店宣传预览
#define SHARE_URL_WITHSTOREPOSTER(APPEND,APPEND2,APPEND3)   [NSString stringWithFormat:@"%@html5/v2.2.0/activity.html?id=%@&account=%@&accountType=%@",SHARE_URL,APPEND,APPEND2,APPEND3]//没有用了，调用H5传的

// 分享帖子详情
#define SHARE_URL_POST_DETAIL(APPEND,APPEND2)        [NSString stringWithFormat:@"%@web/post_detail/html/postDetail.html?postId=%@&deviceCode=%@",H5_SHARE_URL,APPEND,APPEND2]


#define WELCOME_MESSAGE                    @"欢迎注册问药App！关注家人健康，关注用药安全，吃药先“问药”，很有必要！"
#define GREENTCOLOR                     UICOLOR(58, 185, 0)
//#define GREENTCOLOR                     UICOLOR(9, 173, 0)
#define APP_VERSION                [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]
#define DEVICE_IDD   [[[UIDevice currentDevice] identifierForVendor] UUIDString]

//#define iOS_V               [[[UIDevice currentDevice] systemVersion] floatValue]
//#define iOSv7               (iOS_V >= 7)
#define UMENG_KEY                   @"5472f8adfd98c5eb22000bd4"
#define ALERT_MESSAGE               @"当前身份已失效,请重新登录"
#define APP_EMPTY_STRING            @""
#define APP_MESSAGE_MUSIC           @"appmessagemusic"
#define APP_AVATAR_KEY              @"appavatarkey"
#define APP_NICKNAME_KEY            @"appnicknamekey"
#define VERSION_CHECK_DATE          @"versionNoticeDate"
#define APP_DOMAIN_KEY              @"appdomainkey"
#define APP_DOWNLOAD                @"https://itunes.apple.com/cn/app/wen-yao/id901262090?mt=8"
#define APP_GESTURE_ENABLE          @"kgestureenable"
#define UPDATE_GUIDE_Notification   @"update_guide_notification"
#define CHANGED_GUIDE_Notification  @"CHANGED_GUIDE_Notification"
#define NEED_UPDATE_AVATAR          @"NEED_UPDATE_AVATAR"
#define PHARMACY_NEED_UPDATE        @"PHARMACY_NEED_UPDATE"
#define OFFICIAL_MESSAGE            @"OFFICIAL_MESSAGE"
#define APP_UPDATE_AFTER_THREE_DAYS @"App_update_three_days"
#define APP_LAST_TIMESTAMP          @"App_last_timestamp"
#define APP_LAST_SYSTEM_VERSION     @"App_last_systemVersion"
#define APP_LAST_SYSTEM_VERSION_V2  @"App_last_systemVersion_v2"


//商家版
//---------cp-------------
//优惠订单模块

#define NW_queryDiseaseFormulaProductList @"api/drug/queryDiseaseFormulaProductList"      //疾病组方配方用药查询(OK)app/drug/queryDiseaseFormulaProductList

#define PromotionComplete                 @"api/215/promotion/completeOrder"//@"api/promotion/complete"  //app/promotion/complete/v3


//---------cp------------


//------------------------meng----------------------

#define Branch_queryBranchApprove       @"api/branch/info/queryBranchApprove"//3.5.39	查询机构所有待审信息
#define Branch_queryCertifi             @"api/branch/certifi/queryCertifi"//@brief 3.5.20	查询机构执照
#define Branch_queryAllCertifi          @"api/branch/certifi/queryAll" //查询机构执照统一接口
#define Branch_queryCertifiApprove      @"api/branch/certifi/queryCertifiApprove"//@brief 3.5.21	查询待审核机构执照
#define Branch_updateBranchInfo         @"api/branch/info"//更新商家机构信息

#define Branch_employeeQuery                @"api/employee"//查询店员信息
#define Branch_employeeCreate               @"api/employee"//新增店员
#define Branch_employeeEdit                 @"api/employee/valid"//编辑已存在店员
#define Branch_employeeRemove               @"api/employee"//删除店员
#define Branch_saveCertifi                  @"api/branch/certifi/save"//3.5.23	修改机构执照(OK)

#define Branch_updateCertifi                @"api/branch/certifi/update"//3.5.23	修改机构执照(OK)
#define Branch_queryPharmacist              @"api/branch/pharmacist/query/all"//查询药店药师信息
#define Branch_queryPharmacistNew           @"api/branch/pharmacist/query" //获取所有药师信息列表 -> 药店端2.1.8
#define Branch_queryPharmacistApprove       @"api/branch/pharmacist/query/approving"//查询药店审核信息

#define Branch_queryAreaList            @"api/branch/info/queryArea"//3.5.43	获取省市区列表
#define Branch_getAreaCode              @"api/branch/info/getAreaCode"//3.8.2	获取省市区的编码

#define Branch_savePharmacist                @"api/branch/pharmacist/savePharmacist"//3.5.28	修改药师信息(OK)
#define Branch_updatePharmacist          @"api/branch/pharmacist/updatePharmacist"//更新药师信息(OK)

#define updateBranchLat                 @"api/branch/info/updateBranchLat"

//------------------------meng----------------------



//-------------cj-----------------------------------------------------------
//赠送记录
#define GetRecord                                   @"api/coupon/queryPresentLog"
#define GetCouponCondition                          @"h5/promotion/condition"         // 优惠细则
#define GetNotice                                   @"h5/bmmall/queryNotice" 
#define ConfigInfoQueryBanner                       @"h5/configInfo/queryBanner"
//搜索
#define GetSearchKeywords                           @"api/drug/getSearchKeywords"   //app/drug/getSearchKeywords
#define GetDiseaseBykwid                            @"api/disease/byKwId"
#define GetSpmByKwId                                @"api/spm/byKwId"   //根据关键字ID获取症状列表
#define GetProductByKwId                            @"api/drug/queryProductByKwId"

#define NW_spmInfoDetail                            @"api/spm/detailInfo"
#define QueryAssociationDisease                     @"api/spm/associationDisease" //症状关联的疾病
#define QW_queryDiseaseDetailIos                    @"api/disease/detail4Ios"//疾病详情

#define QueryProductDetail                          @"api/drug/queryProductDetail"   //app/drug/queryProductDetail
#define NW_queryDiseaseFormulaProductList           @"api/drug/queryDiseaseFormulaProductList"    //疾病组方配方用药
#define NW_queryDiseaseProductList                  @"api/drug/queryDiseaseProductList"

#define GetQueryStoreCode                           @"api/passport/branch/queryStoreCode" //根据序列号获取商家详情
#define GetBranchGroup                              @"api/branch/info" //获取药店端的商家的信息
#define PostBranchGroup                             @"api/branch/info" //更新药店端的商家的信息
#define PostSendVerifyCode                          @"api/mbr/code/sendVerifyCode"//发送验证码
#define PostRegister                                @"api/store/register"                //快捷注册的一系列的验证
#define GetActivities                               @"api/activity/activities" //根据门店获取营销活动列表
#define GetActivitiesCoupn                          @"api/activity/queryMultiActivity" //根据门店获取营销活动和优惠列表

#define GetActivityInfo                             @"api/activity/getActivity"// 营销活动详情
#define PutDeleteActivities                         @"api/activity/delete"// 删除营销活动
#define PostSaveOrUpdate                            @"api/activity/saveOrUpdate"//发布更新营销活动
#define GetAppraise                                 @"api/appraise/list"    //药店评价列表
#define PostValidVerifyCode                         @"api/passport/code/validVerifyCode"   //校验手机验证码

#define GetPromotionDetail                          @"api/promotion/query"//优惠活动的详细内容

#define StoreBranchPromotion                        @"api/branch/info/branchPromotion" //查询药店详情时，查询该药店的优惠活动

//2.2的新接口
//验证码
#define GetVerifyCode                               @"api/order/base/scan" //根据输入的验证码验证
#define PostVerifyCode                              @"api/coupon/order/complete" //优惠券确认订单
#define PostVerifyProduct                           @"api/order/activity/branchConfirm" //优惠商品确认订单
//我的用药
#define QueryProductByKeyword                       @"api/drug/queryProductByKeyword"       //app/drug/queryProductByKeyword(555)

//统计
#define GetQueryCoupnSell                           @"api/rpt/coupon/query"//优惠券消费统计
#define GetQueryProductSell                         @"api/rpt/promotion/queryProducts"//优惠商品销量统计
#define GetQueryProductSecond                       @"api/rpt/promotion/queryPromotions"//优惠商品二级页面的统计
#define GetQueryProductByName                       @"api/rpt/promotion/queryProductsByName"//优惠商品搜素
//本店活动
#define GetQueryCoupnActivity                       @"api/package/activity/list"//优惠活动（促销活动）的列表
#define GetCoupnActivityDetail                      @"api/package/activity/detail"//优惠活动的详情
#define GetProductActivityDetail                    @"api/package/activity/products"//优惠活动的商品的列表
//上传小票
#define GetAllTips                                  @"api/order/base/orderList"//上传小票模块的订单列表
#define GetTipDeatil                                @"api/order/base/orderDetail"//上传小票的详细内容
#define PostUpTipDeatil                             @"api/order/base/uploadReceipt"//上传小票
#define PostSaveTipDeatil                           @"h5/maicromall/order/uploadInvoice"//新的保存上传小票

//本店优惠

#define GetTag                                      @"api/activity/promotion/drug/tagByBranch"//优惠商品的标签
#define GetAllCoupn                                 @"api/coupon/queryAllByBranch"//本店优惠券
#define GetAllSuitable                              @"api/coupon/product/suitable"//慢病优惠券的适用商品
#define GetAllCoupnProduct                          @"api/activity/promotion/drug/branchDrug"//本店优惠商品
#define GetSearchProduct                            @"api/search/promotion/branch/product"//优惠商品搜索
#define GetScanProduct                              @"api/search/promotion/branch/product/barCode"//条形码搜索
//IM
#define GetonLineCoupn                              @"api/coupon/getOnlineCouponByBranch"//优惠券详情
#define CheckIOSAudit               @"h5/system/checkIOSAudit"


//发现搜索：
#define FinderAssociate     @"api/discovery/searchAssociate"//搜索联想词
#define SearchDiscovery     @"api/discovery/searchDiscovery"//主列表

#define SearchDisease       @"api/discovery/searchDisease"  //疾病列表
#define SearchSymptom       @"api/discovery/searchSpm"      //症状列表
#define SearchProduct       @"api/discovery/searchProduct"  //商品列表
#define SearchProblem       @"api/discovery/searchProblem"  //问答列表

//域名解析
#define GetDomianIs                              @"api/system/checkDomainBlocked"//检查域名是否被封
#define GetNewDomain                             @"api/system/getReserveDomains"//获取新的域名

#define AppLogFlag                 @"api/system/appLogFlag"
#define AppUploadLog               @"api/system/appUploadLog"

//-------------cj-------------------------------------------------------------

//----------------------------------yyx---------------------------------
#define StoreLogin                       @"api/passport/branch/login/byAll"                 //商家账号登录  
#define JG_getBranhBranchInfoWithApprove @"api/branch/info/withApprove"                     //获取药店详细信息,包含审核信息
#define JG_getBranhGroupDetail           @"api/branch/info"                                 //查询机构详细信息
#define JG_infoCheck                     @"api/branch/info/check"                           //药店段信息完善性检测
#define UpdatePassword                   @"api/store/updatePassword"                        //商家修改密码
#define NW_logout                        @"api/store/logout"                                //商家用户登出
#define NW_submitFeedback                @"api/system/submitFeedback"                       //添加反馈
#define MobileValid                      @"api/store/existsMobile"                          //检测手机号是否已经被注册
#define FetchLoginNameByPhone            @"api/store/loginNameByPhone"                      //获取商家账号昵称
#define ResetPassword                    @"api/store/resetPassword"                         //商家重置密码
#define SearchShop                       @"api/branch/info/queryStore"                      //条件查询药店
#define LoginAreaList                    @"api/branch/info/queryArea"                       //获取省市区列表
#define ShopTagquery                     @"api/branch/search/tag"                           //药店标签
#define SaveInstitutionInfo              @"api/branch/info/saveBranch"                      //商家注册保存机构信息
#define UpdateBranch                     @"api/store/updateRegister"                        //商家注册信息修改
#define SearchCerfiti                    @"api/branch/certifi/queryCertifi"                 //查询机构执照
#define UpdateBranchGroupType            @"api/branch/info/updateBranchGroupType"           //修改机构类型
#define NW_uploadFile                    @"api/system/uploadFile"                           //上传图片
#define UpdateBranchStatus               @"api/branch/info/updateBranchStatus"              //更新商家状态待审核
#define SavePharmacist                   @"api/branch/pharmacist/savePharmacist"            //保存药师信息
#define Savecerfiti                      @"api/branch/certifi/save"                         //保存机构执照

#define CustomerInfoCount                @"api/215/customer/countList"                      //客户详情页面的count
#define EmployeeGetInfo                  @"api/215/employee/getInfo"                        //获取店员信息
#define BranchInfoGetSymbol              @"api/branch/info/getSymbol"
#define UpdateEmployeeInfo               @"api/215/employee/updateEmployee"                 //更新店员信息
#define ConsultStatistics                @"api/consult/statistics"                          //互动统计
#define CustomerQueryConsultList         @"api/215/customer/queryConsultList"               //咨询历史
#define SystemPushSet                    @"api/system/pushSet"                              //设置推送状态
#define StatisticsByRecent               @"api/consult/statisticsByRecent"                  //最近统计信息
#define StatisticsByDate                 @"api/consult/statisticsByDate"                    //按日期统计信息

#define CustomerGroupCreate              @"api/customer/group"                              //新建客户分组
#define CustomerGroupList                @"api/customer/group"                              //获取客户分组列表
#define CustomerGroupUpdate              @"api/customer/group"                              //修改客户分组
#define CustomerGroupRemove              @"api/customer/group/remove"                       //删除客户分组
#define CustomerCustAdd                  @"api/customer/group/cust/batchadd"                //批量添加客户
#define CustomerCustRemove               @"api/customer/group/cust/batchremove"             //批量删除客户
#define CustomerCustList                 @"api/customer/group/members"                      //查询分组内客户列表
#define GetChangeAliPayPhoneNumber       @"api/branch/info/mobileForUpdateAlipay"           //获取修改支付宝账号的手机号
#define GetSoftwareUserPhoneNumber       @"api/branch/info/getAccountInfo"                  //获取软件使用人的基本信息
#define UpdateSoftwareUserInfo           @"api/branch/info/updateAccountInfo"               //更新软件使用人的信息


#define FunctionIntroduceUrl_temp        @"api/helpClass/sjgnjs"                            //功能介绍
//#define ServiceInformationUrl_temp       @"app/helpClass/sjfwzn"                            //服务指南
#define Im_Help_Url_temp                 @"api/helpClass/im_help"                           //login 的 帮助
#define ServiceSpeciticationUrl_temp     @"api/helpClass/sjfwtk"                            //login 的服务规范
#define FunctionJiamentUrl_temp          @"api/helpClass/sjqwys"                            //全维药师介绍

#define PassportBranchRegisterComplete   @"api/passport/branch/register"                    //普通注册
#define PassportBranchPasswordRenew      @"api/passport/branch/password/renew"              //重置密码
#define PassportBranchGetAccountByMobile @"api/passport/branch/getAccountByMobile"          //通过手机号获得账号
#define BranchInfoQueryArea              @"api/branch/info/queryArea"                       //获取省市区列表
#define PassportBranchLinkageReserve     @"api/passport/branch/linkage/reserve"             //连锁 认证 预留联系信息
#define BranchApproveLicenseSubmit       @"api/branch/approve/license/submit"               //认证批量上传证照
#define BranchApproveInfoSubmit          @"api/branch/approve/info/submit"                  //提交基本审核信息
#define BranchApprove                    @"api/branch/approve"                              //获取提交的最新审核信息

#define OrderQueryCustomerOrdersByBranch @"api/order/queryCustomerOrdersByBranch"           //客户的历史订单列表
#define OrderGetOrderDetail              @"api/order/getOrderDetail"                        //客户历史订单详情
#define CouponPresentPromotion           @"api/coupon/presentPromotion"                     //送券
#define SystemShort                      @"api/system/short"                                //转换短链接

#define AppLogFlag                      @"api/system/appLogFlag"
#define AppUploadLog                    @"api/system/appUploadLog"

#define MallOrderByBranch                @"api/mall/order/byBranch"                         //兑换商品列表
#define RptMktgByGroup                   @"api/rpt/mktg/byGroup"                            //商家营销方案统计列表
#define RptMktgById                      @"api/rpt/mktg/byId"                               //商家营销方案统计详情
#define MallOrderComplete                @"api/mall/order/complete"                         //输入验证码积分完成订单

#define TeamGetTeamHotInfo               @"api/team/getTeamHotInfo"                         //圈子热议
#define TeamGetMbrInfoListByTeamId       @"api/team/getMbrInfoListByTeamId"                 //查看圈主列表
#define MbrUserExpertLogin               @"api/mbr/user/expertLogin"                        //专家登录
#define TeamGetTeamDetailsInfo           @"api/team/getTeamDetailsInfo"                     //圈子详细信息
#define TeamGetPostListInfoByTeamId      @"api/team/getPostListInfoByTeamId"                //圈子详细信息 帖子列表
#define TeamApplyMasterInfo              @"api/team/applyMasterInfo"                        //申请做圈主
#define TeamAttentionTeam                @"api/team/attentionTeam"                          //关注圈子/取消关注圈子
#define TeamAttentionMbr                 @"api/team/attentionMbr"                           //关注用户／取消关注用户
#define TeamAllTeamList                  @"api/team/allTeamList"                            //圈子全部接口
#define TeamMyFansList                   @"api/team/myFansList"                             //我的粉丝
#define TeamMyAttnExpertList             @"api/team/myAttnExpertList"                       //我关注的专家
#define TeamMyAttnTeamList               @"api/team/myAttnTeamList"                         //我关注的圈子
#define TeamMyPostList                   @"api/team/myPostList"                             //我的发帖列表
#define TeamMyReplyList                  @"api/team/myReplyList"                            //我的回帖列表
#define TeamExpertInfo                   @"api/team/expertInfo"                             //专家 专栏信息
#define TeamHisPostList                  @"api/team/hisPostList"                            //Ta的发文列表
#define TeamHisReplyList                 @"api/team/hisReplyList"                           //Ta的回帖列表
#define ExpertTokenValid                 @"api/mbr/user/tokenValid"                         //专家token校验
#define TeamUploadCertInfo               @"api/team/uploadCertInfo"                         //上传药师认证信息
#define TeamExpertiseList                @"api/team/expertiseList"                          //擅长领域列表
#define TeamHisAttnTeamList              @"api/team/hisAttnTeamList"                        //Ta关注的圈子列表
#define TeamHisAttnExpertList            @"api/team/hisAttnExpertList"                      //Ta关注的专家列表
#define TeamUpdateMbrInfo                @"api/team/updateMbrInfo"                          //更新个人信息
#define TeamMyInfo                       @"api/team/myInfo"                                 //个人信息
#define TeamGetCollectionPost            @"api/team/getCollectionPost"                      //我收藏的帖子
#define H5CollectionCancelCollection     @"h5/collection/cancelCollection"                  //取消收藏帖子
#define BranchAppraiseMmall              @"h5/branch/appraise/mmall"                       //新的评价
#define BranchAppraiseNormal             @"h5/branch/appraise/normal"                      //老的评价
#define Expert_logout                    @"api/mbr/user/logout"                             //用户登出
#define TeamMessage                      @"api/team/message"                                //圈子消息列表
#define TeamQueryUnReadMessage           @"api/team/queryUnReadMessage"                     //轮询获取圈子消息
#define TeamDelPostInfo                  @"api/team/delPostInfo"                            //删除帖子
#define TeamDelReply                     @"api/team/delReply"                               //删除评论
#define TeamChangeMessageShowFlag        @"api/team/changeMessageShowFlag"                  //删除单条消息
#define TeamQueryZanListByObjId          @"api/team/queryZanListByObjId"                    //查看点赞列表
#define TeamChangeAllMessageReadFlag     @"api/team/changeAllMessageReadFlag"               //全部标记为已读
#define TeamPostReply                    @"api/team/postReply"                              //回复评论
#define TeamChangeMsgReadFlagByMsgClass  @"api/team/changeMsgReadFlagByMsgClass"            //分类标记已读
#define InitByBranch                     @"api/init/byBranch"                               //商户端获取基本信息
#define UserRegisterValid                @"api/mbr/user/registerValid"                      //专家注册校验手机号是否注册过
#define BmmallQueryShareOrder            @"h5/bmmall/queryShareOrder"                       //员工分享转化订单统计


#define TeamChatSessionGetAll            @"h5/team/chat/session/getAll"                     //专家私聊会话列表
#define TeamChatSessionGetChatList       @"h5/team/chat/session/getChatList"                //专家私聊会话列表轮询
#define TeamChatDetailGetAll             @"h5/team/chat/detail/getAll"                      //私聊聊天详情
#define TeamChatDetailGetChatDetailList  @"h5/team/chat/detail/getChatDetailList"           //私聊聊天详情轮询
#define TeamChatDetailAddChatDetail      @"h5/team/chat/detail/addChatDetail"               //私聊发消息

#define ImConsultQueryQAList             @"h5/imConsult/queryQAList"                        //查询问答列表
#define ImConsultQueryQADetail           @"h5/imConsult/queryQADetail"                      //问答详情
#define ImConsultLoopNews                @"h5/imConsult/loopNews"                           //问答详情轮询
#define ImConsultReply                   @"h5/imConsult/reply"                              //问答回复发消息
#define ImConsultCheckCanRace            @"h5/imConsult/checkCanRace"                       //商户检查是否可以抢答
#define ImConsultIgnore                  @"h5/imConsult/ignore"                             //专家忽略
#define ImConsultRace                    @"h5/imConsult/race"                               //专家抢答
#define MbrImageCode                     @"h5/mbr/imageCode"                                //获取图片验证码
#define MbrCodeSendCodeByImageVerify     @"h5/mbr/code/sendCodeByImageVerify"               //验证图片验证码并发送短信验证码
#define MbrCodeValidVerifyCodeOnly4check @"h5/mbr/code/validVerifyCodeOnly4check"           //检验4位验证码，不消耗验证码

#define MbrExpertLogin                   @"h5/mbr/expert/login"                             //专家用户名密码登录
#define MbrExpertRegister                @"h5/mbr/expert/register"                          //专家注册
#define MbrExpertResetPassword           @"h5/mbr/expert/resetPassword"                     //专家重置密码
#define MbrExpertUpdatePassword          @"h5/mbr/expert/updatePassword"                    //专家设置新密码／修改密码
#define MbrExpertRegisterValid           @"h5/mbr/expert/registerValid"                     //检测专家是否已注册

//320
#define MbrExpertQueryExpertByBranchId   @"h5/mbr/expert/queryExpertByBranchId"             //本店信息的药师列表
#define MbrExpertUpdateOnlineFlag        @"h5/mbr/expert/updateOnlineFlag"                  //设置专家上下线
#define BranchGetBranchPostTips          @"h5/branch/getBranchPostTips"                     //获取配送方式
#define BranchQueryOrderLinks            @"h5/branch/queryOrderLinks"                       //获取接单电话
#define BranchUpdateOrderLinks           @"h5/branch/updateOrderLinks"                      //更新接单电话
#define BranchScoreRank                  @"h5/branch/score/rank"                            //积分排行列表
#define BranchScoreEmpRank               @"h5/branch/score/emp/rank"                        //积分排行详情
#define RptOperateSaveLog                @"api/rpt/operate/saveLog"                         //用户行为统计
#define TeamMyTeam                       @"h5/team/myTeam"                                  //我的圈 帖子列表
#define TeamQueryTeamList                @"h5/team/queryTeamList"                           //全部圈子 4.0.0以后
#define TeamQueryAttnTeamExpert          @"h5/team/queryAttnTeamExpert"                     //入驻专家列表
#define MmallByName                      @"h5/mmall/byName"                                 //本店咨询 药品搜索
#define MmallByBarcode                   @"h5/mmall/byBarcode"                              //本店咨询 扫码搜索
#define ProductQueryProductByKwName      @"h5/product/queryProductByKwName"                 //专家咨询 药品搜索
#define ProductQueryProductByBarCode     @"h5/product/queryProductByBarCode"                //专家咨询 扫码搜索
#define TeamChatDetailGetAllByChatId     @"h5/team/chat/detail/getAllByChatId"

//401
#define BmmallDeliveryMode               @"h5/bmmall/deliveryMode"                          //获取门店配送方式
#define BmmallDeliveryCancel             @"h5/bmmall/deliveryCancel"                        //门店取消配送方式
#define BmmallDeliveryOnsite             @"h5/bmmall/deliveryOnsite"                        //编辑配送方式 到店取货
#define BmmallDeliveryHome               @"h5/bmmall/deliveryHome"                          //编辑配送方式 送货上门
#define BmmallDeliveryExpress            @"h5/bmmall/deliveryExpress"                       //编辑配送方式 同城快递
#define BmmallPayMode                    @"h5/bmmall/payMode"                               //获取门店支付方式

//----------------------------------yyx---------------------------------


//----------------------------------zpx---------------------------------
#define QueryOrdersList                 @"h5/maicromall/order/queryShopOrders"      //请求订单列表
#define OperateOrders                   @"h5/maicromall/order/operateShopOrder"     //订单操作
#define QueryPostList                   @"h5/maicromall/order/queryLCInfo"          //查询物流列表
#define FillPostDetail                  @"h5/maicromall/order/fillLogistics"        //填写物流
#define QueryShopOrderDetailInfo        @"h5/maicromall/order/queryShopOrderDetail" //查询订单详情
#define QueryRefuseReasonInfo           @"h5/maicromall/order/queryReasons4Cancel"  //拒绝订单理由列表
#define QueryMMallActivity              @"h5/bmmall/queryMMallActivity"             //请求微商活动列表
#define QueryActivityCombo              @"h5/bmmall/queryActivityCombo"             //套餐详情
#define QueryActivityPromotion          @"h5/bmmall/queryActivityPromotin"          //优惠活动详情
#define QueryActivityRepd               @"h5/bmmall/queryActivityRepd"              //换购详情
#define QueryActivityRush               @"h5/bmmall/queryActivityRush"              //抢购详情
#define WechatUpdateActivity            @"h5/bmmall/updateActivity"                 //下架活动
#define QueryPerformanceList            @"h5/maicromall/order/myPerformanceOrders" //业绩订单列表
#define QueryEmpLvlInfo                 @"h5/mbr/branch/queryEmpLvlInfo"            //我的等级
#define GetRecieveAddressList           @"h5/emp/address/addresses"                 //收货地址列表
#define EditRecieveAddress              @"h5/emp/address/edit"                      //地址编辑
#define RemoveRecieveAddress            @"h5/emp/address/remove"                    //删除地址
//----------------------------------zpx---------------------------------

//------------czp---------

#define QueryCustomer                   @"api/im/customer/query"//  // 查询我的客户列表
#define QueryCustomerInfo               @"api/im/customer" //         //获取客户详情
#define  CustomerTags                   @"api/im/customer"
#define  QueryCustomerTags                   @"api/im/customer/tag"
#define RemoveCustomerTags              @"api/im/customer/tag/remove"
#define deleteCustomerLabel             @"api/im/customer/remove" //
#define QueryCustomerDrug               @"api/im/customer/drug"    //查询用户购药历史
#define QueryRecommendProductByClass    @"api/drug/queryRecommendProductByClass"//健康方案商品列表

#define Fixreceipt                        @"api/promotion/receipt"//绑定小票
//#define Delreceipt                        @"api/promotion/receipt/remove" ////删除小票

#define HealthyCountQuestions       @"api/search/knowledge/questionClassify"   //@"api/healthy/count/questions"
#define HealthyQueryTagQuestion     @"api/search/knowledge/question"     //@"api/healthy/query/tag/question"
#define HealthyDetail               @"api/healthy/detail"

#define ConsultItemReaded           @"api/consult/detail/read"                  //收到一个消息回执一个
#define ConsultSetUnreadNum         @"api/consult/setUnreadNum"
#define NW_checkNewVersion           @"api/system/version"//@"api/system/getLastVersion"//读取服务器上最新版本数据

// 订单通知
#define MsgBoxListOrderNotiList     @"api/message/order/queryStore"
#define OrderNotiMsgRead            @"api/message/order/read"
#define MsgBoxListOrderNewList      @"api/message/order/queryUnRead"
#define OrderNotiRemoveItem         @"api/message/order/removeByCustomer"
#define OrderGetNew                 @"h5/maicromall/order/getNewOrderCount"      // 获取未处理的订单数量

#define RptShareSaveLog                  @"api/rpt/share/saveLog"   //3.13.9	App是否后台状态设置

#define QueryInternalProductList         @"h5/bmmall/queryClassifyProduct"       // 本店商品列表
#define QueryInternalProductPackage      @"h5/mmall/queryDiscountPackage"        // 本店商品列表
#define QueryInternalProductCateList     @"h5/bmmall/queryClassifys"             // 本店商品类别列表
#define QueryInternalCatesWithPro        @"h5/bmmall/branchProductCategories"    // 根据商品获取类别列表
#define QueryInternalCatesWithCount      @"h5/bmmall/productCountOfCategories"   // 获取本店商品类别列表含个数
#define UpdateInternalProductStock       @"h5/bmmall/updateStock"                // 维护商品库存
#define UpdateInternalProductStatus      @"h5/bmmall/updateStatus"               // 商品上架下架
#define SearchInternalProductList        @"h5/bmmall/searchProduct"              // 查找商品
#define QueryInternalProductDetail       @"h5/bmmall/queryProductDetail"         // 获取商品详情
#define GetRefCode                       @"h5/rpt/ref/getRefCode"                // 获取REF分享code

#define MktgQueryCoupons                 @"h5/mmall/mktg/queryCoupons"           // 选择列表：券
#define MktgQueryActs                    @"h5/mmall/mktg/queryActs"              // 选择列表：活动
#define MktgQueryDms                     @"h5/mmall/mktg/queryDms"               // 选择列表：海报
#define MktgQueryNcds                    @"h5/mmall/mktg/queryNcds"              // 慢病标签分组
#define CustomerQueryNcds                @"h5/customer/queryNcds"                // 首页慢病标签分组
#define MktgCheck                        @"h5/mmall/mktg/check"                  // 提交前校验
#define MktgSubmitAct                    @"h5/mmall/mktg/submit/act"             // 提交活动
#define MktgSubmitDm                     @"h5/mmall/mktg/submit/dm"              // 提交海报
#define MktgSubmitCoupon                 @"h5/mmall/mktg/submit/coupon"          // 提交优惠券
#define TrainList                        @"h5/train/trainList"                   // 获取培训列表
#define TrainDetail                      @"h5/train/trainDetails"                // 获取培训详情
#define CustomerQueryByNcd               @"h5/customer/queryByNcd"               // 获取门店会员
#define CustomerQueryOrderList           @"h5/maicromall/order/queryMemberOrders"// 查询会员微商订单列表
#define TaskReminder                     @"h5/branch/emp/taskReminder"           // 积分任务接口
#define VerifyRecords                    @"h5/mall/order/byBranch"         // 验证记录列表
#define QueryQwProduct                   @"h5/bmmall/queryQwProduct"             // 发布商品の根据条形码查询全维商品
#define ReleaseGood                      @"h5/bmmall/releaseGoods"               // 发布商品
#define RecoProducts                     @"h5/bmmall/recommendProduct"           // 推荐商品
#define CancelRecoProducts               @"h5/bmmall/cancelRecommendProduct"     // 取消推荐商品
#define MergeCates                       @"h5/bmmall/mergeProductCategories"     // 合并商品分类

//------------czp----------


//-------xzh--------
#define DeleteIM                     @"api/im/remove"                           //删除聊天记录
#define SelectIM                     @"api/im"                           //查询IM聊天记录数目
#define AddQWIM                      @"api/im/qw"                           //添加会话记录 官方
#define SelectQWIM                   @"api/im/qw"
#define CheckCert                    @"api/branch/certifi/check"
#define IMSetReceived                @"api/im/setReceived"
#define QuickReply                   @"api/consult/qReply"

#define AlternativeIMSelect          @"api/im/unreceived"
#define DeleteI                      @"app/im/delete/i"
#define DelAllMessage                @"api/im/chatview/remove"
#define GetChatView                  @"api/im/chatview"
#define QueryInfoByIds               @"api/mbr/member/queryInfoByIds" //  //根据用户账号获取用户信息
#define DelQwRecord                  @"app/im/delQwRecord"       //清空全维药事会话记录
#define TopChatView                  @"api/im/chatview/top"      //设置IM聊天条目是否置顶
#define CheckTimeout                 @"api/p2p/24check"
#define PTPRemoveByPhar              @"api/p2p/removeByPhar"
#define PTPTopByPhar                 @"api/p2p/topByPhar"
#define HeartBeat                    @"api/system/heartbeat"
#define SystemBackSet                @"api/system/backSet"

#define UpdateDeviceByToken          @"api/system/updateDeviceByToken"

#define ConsultClosed                @"api/consult/closed?v=2.1"
#define ConsultConsulting            @"api/consult/consulting"          //全量获取解答列表
#define ConsultGiveUpByPhar          @"api/consult/giveUpByPhar"          //抢答未答放弃
#define ConsultConsultingnewDetail   @"api/consult/phar/newDetail"     //增量获取解答列表

#define ConsultCreate                @"api/consult/create"
#define ConsultCustomer              @"api/consult/customer"

#define ConsultDetailCreate          @"api/consult/217/reply"           //和用户进行聊天
#define ConsultConsultingFirst       @"api/consult/217/reply"      //第一次答复用户
#define CheckStatusByPharWhenGettingDetailFromRacing        @"api/consult/checkStatusByPharWhenGettingDetailFromRacing"

#define ConsultIgnore                @"api/consult/ignore"
#define ConsultDetailCustomer        @"api/consult/detail/customer"         //
#define ConsultDetailPhar            @"api/consult/detail/phar"             //全量详情
#define ConsultDetailPharPoll        @"api/consult/detail/phar/poll"        //增量详情
#define ConsultDetailReceive         @"api/consult/detail/receive"
#define ConsultDetailRemove          @"api/consult/detail/remove"
#define ConsultIdRaced               @"api/consult/id/raced"
#define ConsultRacing                @"api/consult/racing"
#define ConsultReplyFirst            @"api/consult/reply/first"
#define ConsultSpCreate              @"api/consult/sp/create"
#define ConsultCustomerItemRead      @"api/consult/detail/read"                 //消息回执

#define NW_uploadSpe                    @"api/system/upload/audio"//文件上传 fixed by xiezhenghong

//----------xzh----------



//----------lj----------
//#define PromotionScan                   @"api/promotion/scan"//@"api/promotion/scan/s"//an/s" 二维码扫描 fixed by lijian
#define QueryProductByBarCode           @"api/drug/queryProductByBarCode" //@"app/drug/queryProductByBarCode" 扫码获取商品信息 fixed by lijian

#define TokenValid                      @"api/token/check"//聊天时Token有效性验证 fixed by lijian
#define NW_fetchSellWellProducts        @"api/branch/info/sellWellProducts"//商家畅销商品 fixed by lijian
#define NW_spmList             @"api/spm/list"//获取所有症状列表 fixed by lijian
#define NW_querySpmInfoListByBody       @"api/spm/byBody"//部位下关联症状查询 fixed by lijian
#define NW_queryFactoryProductList      @"api/factory/queryFactoryProductList"//获取生产厂家产品列表 fixed by lijian
#define FetchProFactoryByClass          @"api/drug/fetchProFactoryByClass"//根据商品分类ID，查找相应生产厂家
#define QueryProductByClass             @"api/drug/queryProductByClass"//根据分类查询商品 fixed by lijian


#define UpdateDeviceToken         @"api/system/updateDeviceByToken" //更新DeviceToken
//---------------------------

/**
 *  --------------------------------sgp-------------------------------------
 */

#define GetByCustomer                       @"api/p2p/phar/detail/getByCustomer"                         //我的用药所有标签
#define PollBySessionId                 @"api/p2p/phar/detail/pollBySessionId"


#define PTPDetailCreate                 @"api/p2p/detail/create"

#define PTPDetailRead                   @"api/p2p/detail/read"

#define PTPDetailRemove                 @"api/p2p/detail/remove"
/**
 *  --------------------------------sgp-------------------------------------
 */

/**
 *  --------------------------------yqy-------------------------------------
 */

#define PTPPharGetAll                 @"api/p2p/phar/session/getAll"   //本店全量
#define PTPPharPoll                   @"api/p2p/phar/session/poll"     //本店轮询

/**
 *  --------------------------------yqy-------------------------------------
 */


/**
 *  --------------------------------ll start-------------------------------------
 */
#define API_Store_queryMyRecommends         @"api/mbr/inviter/queryMyRecommends"                    // 推荐人列表
#define API_Store_GetServiceTelLists        @"h5/system/getServiceTel"                              // 客服电话
#define API_Store_GetWenyaoActivityList     @"h5/act/list"                                          // 获取问药活动列表
#define API_Store_GetTrainList              @"h5/train/trainList"                                   // 获取列表(培训、生意经)
#define API_Store_GetTrainDetails           @"h5/train/trainDetails"                                // 培训详情
#define API_Store_GetProductMarket          @"h5/salesrpt/productMarket"                            // 商品销售统计
#define API_Store_QueryEmployees            @"h5/mbr/branch/queryEmployees"                         // 店员信息
#define API_StoreEmployee_Sign              @"h5/branch/emp/sign"                                   // 签到
// 3.2.1
#define API_Store_QueryBookProduct          @"h5/act/book/list"                                     // 查询推荐顾客预定商品
/**
 *  --------------------------------ll end-------------------------------------
 */

// ---------- cty <<<
#define MsgBoxReadAllByType @"h5/notice/branch/clear" //客户：清空未读数（消息中心，订单通知，积分消息）
#define MsgBoxGetIndex @"h5/notice/branch/index" //消息盒子首页
#define MsgBoxPollAll @"h5/notice/branch/poll" //轮询-获取所有消息
#define MsgBoxGetNoNoticeList @"h5/notice/branch/queryNoNotices" //消息中心列表
#define MsgBoxGetOrderNoticeList @"h5/notice/branch/queryOrderNotices" //订单消息列表
#define MsgBoxGetCreditNoticeList @"h5/notice/branch/queryScoreNotices" //积分消息列表
#define MsgBoxReadMsg @"api/message/read" // 逐条设置已读
#define MsgBoxDelByType @"api/message/removeByType" // 按类型全部删除
// ---------- cty >>>

#define PollByPhar  @"api/im/qw/pollByPhar"
#endif