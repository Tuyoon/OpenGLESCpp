//
//  ViewController.m
//  OpenGLESCpp
//
//  Created by Admin on 20.11.2024.
//

#import "ViewController.h"
#import "ViewRenderer.h"

@interface ViewController ()

@property(nonatomic, strong) ViewRenderer* viewRenderer;
@property(nonatomic, strong) EAGLContext* context;

@property(nonatomic, weak) IBOutlet UISlider* rotationSlider;
@property(nonatomic, weak) IBOutlet UILabel* angleDegreeLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self configure];
    [self updateUI];
}

// MARK: - Overrides

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
    [self.viewRenderer drawInRect:rect];
}

// MARK: - Actions

- (IBAction)rotationSliderChanged:(UISlider*)slider {
    CGFloat angle = slider.value * 360.0;
    [self.viewRenderer rotate:angle];
    [self updateUI];
}

// MARK: - Private Methods

- (void)configure {
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    GLKView* glkView = (GLKView*)self.view;
    glkView.context = self.context;
    glkView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    [EAGLContext setCurrentContext:self.context];
    
    self.viewRenderer = [ViewRenderer new];
    [self.viewRenderer setup];
}

- (void)updateUI {
    self.angleDegreeLabel.text = [NSString stringWithFormat:@"Angle: %.0f degree", (self.rotationSlider.value * 360.0)];
}

@end
