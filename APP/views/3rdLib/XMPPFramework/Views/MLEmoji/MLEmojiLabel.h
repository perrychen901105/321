//
//  MLEmojiLabel.h
//  MLEmojiLabel
//
//  Created by molon on 5/19/14.
//  Copyright (c) 2014 molon. All rights reserved.
//

#import "TTTAttributedLabel.h"


typedef NS_OPTIONS(NSUInteger, MLEmojiLabelLinkType) {
    MLEmojiLabelLinkTypeURL = 0,
    MLEmojiLabelLinkTypePhoneNumber,
    MLEmojiLabelLinkTypeEmail,
    MLEmojiLabelLinkTypeAt,
    MLEmojiLabelLinkTypePoundSign,
    MLEmojiLabelLinkTypeDrugGuide,
    MLEmojiLabelLinkTypeMedicineDetail,
    MLEmojiLabelLinkTypeOuterLink,
    MLEmojiLabelLinkTypePostDetail
};


@class MLEmojiLabel;
@protocol MLEmojiLabelDelegate <NSObject>

@optional
- (void)mlEmojiLabel:(MLEmojiLabel*)emojiLabel didSelectLink:(NSString*)link withType:(MLEmojiLabelLinkType)type;


@end

@interface MLEmojiLabel : TTTAttributedLabel

@property (nonatomic, assign) BOOL disableEmoji; //禁用表情
@property (nonatomic, assign) BOOL disableThreeCommon; //禁用电话，邮箱，连接三者

@property (nonatomic, assign) BOOL isNeedAtAndPoundSign; //是否需要话题和@功能，默认为不需要

@property (nonatomic, copy) NSString *customEmojiRegex; //自定义表情正则
@property (nonatomic, copy) NSString *customEmojiPlistName; //xxxxx.plist 格式

@property (nonatomic, weak) id<MLEmojiLabelDelegate> emojiDelegate; //点击连接的代理方法

@property (nonatomic, copy) NSString *emojiText; //设置处理文字

- (NSArray *)getTagList;
- (void)addLinkTags:(NSArray *)tagList;
+ (CGSize)needSizeWithText:(NSString *)emojiText WithConstrainSize:(CGSize)size;
+ (CGSize)needSizeWithText:(NSString *)emojiText
         WithConstrainSize:(CGSize)size
                  WithFont:(UIFont *)font;
+ (CGSize)expertInfoCommentNeedSizeWithText:(NSString *)emojiText WithConstrainSize:(CGSize)size;

@end