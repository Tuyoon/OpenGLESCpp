//
//  ViewRenderer.h
//  OpenGLESCpp
//
//  Created by Admin on 20.11.2024.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Cpp adapter for shape renderer. Translates messages to ShapeRenderer
@interface ViewRenderer : NSObject

- (void)setup;
- (void)drawInRect:(CGRect)rect;
- (void)rotate:(CGFloat)angle;

@end

NS_ASSUME_NONNULL_END
