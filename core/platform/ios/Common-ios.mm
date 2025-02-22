/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "platform/Common.h"

#include <stdarg.h>
#include <stdio.h>

#import <UIKit/UIAlertController.h>
#import <UIKit/UIWindow.h>
#include "base/Director.h"
#include "base/Logging.h"

NS_AX_BEGIN

// ios no MessageBox, use log instead
void messageBox(const char* msg, const char* title)
{
    // only enable it on iOS.
    // FIXME: Implement it for tvOS
#if !defined(AX_TARGET_OS_TVOS)
    NSString* tmpTitle = (title) ? [NSString stringWithUTF8String:title] : nil;
    NSString* tmpMsg   = (msg) ? [NSString stringWithUTF8String:msg] : nil;

    UIAlertController* alertController = [UIAlertController alertControllerWithTitle:tmpTitle
                                                                             message:tmpMsg
                                                                      preferredStyle:UIAlertControllerStyleAlert];

    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK"
                                                            style:UIAlertActionStyleDefault
                                                          handler:^(UIAlertAction* action){
                                                          }];

    [alertController addAction:defaultAction];
    auto rootViewController = [UIApplication sharedApplication].windows[0].rootViewController;
    [rootViewController presentViewController:alertController animated:YES completion:nil];
#endif
}

NS_AX_END
