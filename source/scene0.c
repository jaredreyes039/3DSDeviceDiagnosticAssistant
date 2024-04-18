#include "scene0.h"

static void initScene0(C2D_TextBuf g_staticBuf, C2D_TextBuf g_dynamicBuf, C2D_Text *g_staticText)
{
 g_staticBuf = C2D_TextBufNew(1024); 
 g_dynamicBuf = C2D_TextBufNew(1024);
 
 C2D_TextParse(&g_staticText[0], g_staticBuf, "Device Health Check");
 C2D_TextParse(&g_staticText[1], g_staticBuf, "v1.0.0");
 C2D_TextParse(&g_staticText[2], g_staticBuf, "Hack the planet!");
 C2D_TextParse(&g_staticText[3], g_staticBuf, "Hardware Calibration");
 C2D_TextParse(&g_staticText[4], g_staticBuf, "System Versions");
 C2D_TextParse(&g_staticText[5], g_staticBuf, "Author: Jay Reyes (c) 2024");
 
 C2D_TextOptimize(&g_staticText[0]);
}

static void renderHeader0(C2D_Text *g_staticText){
	C2D_DrawText(&g_staticText[0], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 12.0f, 24.0f, 0.5f, 0.75f, 0.5f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText[1], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft,  220.0f, 24.0f, 0.5f, 0.65f, 0.45f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText[3], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 64.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText[4], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 166.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText[5], C2D_AtBaseline | C2D_WithColor | C2D_AlignRight , 376.0f, 240.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
}

static void renderTimeInterface(C2D_TextBuf g_dynamicBuf){
	u64 time;
	time = osGetTime();

	char timeTextBuf[64];
	C2D_Text timeText;
	snprintf(timeTextBuf, sizeof(timeTextBuf), "System Time: %llu", time);
	C2D_TextParse(&timeText, g_dynamicBuf, timeTextBuf);
	C2D_TextOptimize(&timeText);
	C2D_DrawText(&timeText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 12.0f, 44.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void renderTouchInterface(C2D_TextBuf g_dynamicBuf){
	// Init touch access
	touchPosition touch;
	hidTouchRead(&touch);
	// print text
	char touchTextBuf[64];
	C2D_Text touchText;
	snprintf(touchTextBuf, sizeof(touchTextBuf), "Touch Calibration: x: %d, y: %d", touch.px, touch.py);
	C2D_TextParse(&touchText, g_dynamicBuf, touchTextBuf);
	C2D_TextOptimize(&touchText);
	C2D_DrawText(&touchText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 76.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void renderGyroInterface(C2D_TextBuf g_dynamicBuf){
	angularRate gyroscope;
	hidGyroRead(&gyroscope);

	HIDUSER_EnableGyroscope();
	char gyroTextBuf[64];
	C2D_Text gyroText;
	snprintf(gyroTextBuf, sizeof(gyroTextBuf), "Gyro Calibration: roll: %d, yaw: %d, pitch: %d", gyroscope.x, gyroscope.y, gyroscope.z);
	C2D_TextParse(&gyroText, g_dynamicBuf, gyroTextBuf);
	C2D_TextOptimize(&gyroText);
	C2D_DrawText(&gyroText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 98.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void renderJoystickInterface(C2D_TextBuf g_dynamicBuf){
	circlePosition circlePad;
	hidCircleRead(&circlePad);

	char circleTextBuf[64];
	C2D_Text circleText;
	snprintf(circleTextBuf, sizeof(circleTextBuf), "Circle Pad Calibration: x: %d, y: %d", circlePad.dx, circlePad.dy);
	C2D_TextParse(&circleText, g_dynamicBuf, circleTextBuf);
	C2D_TextOptimize(&circleText);
	C2D_DrawText(&circleText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void renderSliderInterface(C2D_TextBuf g_dynamicBuf){
	float sliderPosition = osGet3DSliderState();

	char sliderTextBuf[64];
	C2D_Text sliderText;
	snprintf(sliderTextBuf, sizeof(sliderTextBuf), "Slider Calibration: position: %f", sliderPosition);
	C2D_TextParse(&sliderText, g_dynamicBuf, sliderTextBuf);
	C2D_TextOptimize(&sliderText);
	C2D_DrawText(&sliderText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 142.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void renderFirmwareInterface(C2D_TextBuf g_dynamicBuf){
	u32 firmVer = osGetFirmVersion();
	u32 coreVer = osGetSystemCoreVersion();
	u32 kernelVer = osGetKernelVersion();

	char firmTextBuf[64];
	C2D_Text firmText;
	snprintf(firmTextBuf, sizeof(firmTextBuf), "Firmware Version: %d", firmVer);
	C2D_TextParse(&firmText, g_dynamicBuf, firmTextBuf);
	C2D_TextOptimize(&firmText);
	C2D_DrawText(&firmText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 178.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
	char coreTextBuf[64];
	C2D_Text coreText;
	snprintf(coreTextBuf, sizeof(coreTextBuf), "SysCore Version: %d", coreVer);
	C2D_TextParse(&coreText, g_dynamicBuf, coreTextBuf);
	C2D_TextOptimize(&coreText);
	C2D_DrawText(&coreText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 200.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));	
	char kernelTextBuf[64];
	C2D_Text kernelText;
	snprintf(kernelTextBuf, sizeof(kernelTextBuf), "Kernel Version: %d", kernelVer);
	C2D_TextParse(&kernelText, g_dynamicBuf, kernelTextBuf);
	C2D_TextOptimize(&kernelText);
	C2D_DrawText(&kernelText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 222.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void compileInterfaces(C2D_TextBuf g_dynamicBuf){
	renderTimeInterface(g_dynamicBuf);
	renderTouchInterface(g_dynamicBuf);
	renderGyroInterface(g_dynamicBuf);
	renderJoystickInterface(g_dynamicBuf);
	renderSliderInterface(g_dynamicBuf);
	renderFirmwareInterface(g_dynamicBuf);	
}

// Runs in anim loop
static void buildScene0(float size, C2D_TextBuf g_dynamicBuf, C2D_Text *g_staticText){
	C2D_TextBufClear(g_dynamicBuf);
	renderHeader0(&g_staticText);
	compileInterfaces(g_dynamicBuf);
}


static void exitScene0(C2D_TextBuf g_staticBuf, C2D_TextBuf g_dynamicBuf){
	C2D_TextBufDelete(g_dynamicBuf);
	C2D_TextBufDelete(g_staticBuf);
}

