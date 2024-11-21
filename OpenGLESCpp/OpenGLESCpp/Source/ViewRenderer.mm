//
//  ViewRenderer.m
//  OpenGLESCpp
//
//  Created by Admin on 20.11.2024.
//

#import "ViewRenderer.h"
#import "ShapeRenderer.hpp"

@interface ViewRenderer()
@property(nonatomic) ShapeRenderer *renderer;
@end

@implementation ViewRenderer

- (instancetype)init {
    self = [super init];
    if (self) {
        self.renderer = new ShapeRenderer();
    }
    return self;
}

- (void)setup {
    self.renderer->setup();
}

- (void)drawInRect:(CGRect)rect {
    self.renderer->draw(rect.size.width, rect.size.height);
}

- (void)rotate:(CGFloat)angle {
    self.renderer->rotate(angle);
}

- (void)dealloc {
    delete self.renderer;
}

@end
