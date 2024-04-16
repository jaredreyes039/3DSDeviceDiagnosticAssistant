#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>

// Scene 0
C2D_TextBuf g_staticBuf, g_dynamicBuf;
C2D_Text g_staticText[6];

// Scene 1
C2D_TextBuf g_staticBuf1, g_dynamicBuf1;
C2D_Text g_staticText1[6];

// SCENE 0
static void sceneInit(void)
{
//  Text needs memory buffers for drawing
//  4096 just use case, might adjust
 g_staticBuf = C2D_TextBufNew(4096); 
 g_dynamicBuf = C2D_TextBufNew(4096);
 
//  Can I abstract this?
 C2D_TextParse(&g_staticText[0], g_staticBuf, "Device Health Check");
 C2D_TextParse(&g_staticText[1], g_staticBuf, "v1.0.0");
 C2D_TextParse(&g_staticText[2], g_staticBuf, "Hack the planet!");
 C2D_TextParse(&g_staticText[3], g_staticBuf, "Hardware Calibration");
 C2D_TextParse(&g_staticText[4], g_staticBuf, "System Versions");
 C2D_TextParse(&g_staticText[5], g_staticBuf, "Author: Jay Reyes (c) 2024");
 
//  Honestly, not sure HOW they do it, but it's necessary for perf.
 // Optimize the static text strings
 C2D_TextOptimize(&g_staticText[0]);
}

// Runs in anim loop
static void sceneRender(float size){
	// Since Jan 19XX, needs to be converted eventually to be useful
	u64 time;
	time = osGetTime();
	
	// Clear the dynamic text buffer
	C2D_TextBufClear(g_dynamicBuf);

	// Draw static text strings
	C2D_DrawText(&g_staticText[0], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 12.0f, 24.0f, 0.5f, 0.75f, 0.5f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText[1], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft,  220.0f, 24.0f, 0.5f, 0.65f, 0.45f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText[3], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 64.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText[4], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 166.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText[5], C2D_AtBaseline | C2D_WithColor | C2D_AlignRight , 376.0f, 240.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));

	// Hardware Calibration Vars
	touchPosition touch;
	hidTouchRead(&touch);
	angularRate gyroscope;
	hidGyroRead(&gyroscope);
	circlePosition circlePad;
	hidCircleRead(&circlePad);
	float sliderPosition = osGet3DSliderState();

	// Versions
	u32 firmVer = osGetFirmVersion();
	u32 coreVer = osGetSystemCoreVersion();
	u32 kernelVer = osGetKernelVersion();

	// System Time
	char timeTextBuf[64];
	C2D_Text timeText;
	snprintf(timeTextBuf, sizeof(timeTextBuf), "System Time: %llu", time);
	C2D_TextParse(&timeText, g_dynamicBuf, timeTextBuf);
	C2D_TextOptimize(&timeText);
	C2D_DrawText(&timeText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 12.0f, 44.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Display touch positions
	char touchTextBuf[64];
	C2D_Text touchText;
	snprintf(touchTextBuf, sizeof(touchTextBuf), "Touch Calibration: x: %d, y: %d", touch.px, touch.py);
	C2D_TextParse(&touchText, g_dynamicBuf, touchTextBuf);
	C2D_TextOptimize(&touchText);
	C2D_DrawText(&touchText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 76.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
	
	// Helped me diagnose gyro issues w/ my 3DS lmao 
	HIDUSER_EnableGyroscope();
	char gyroTextBuf[64];
	C2D_Text gyroText;
	snprintf(gyroTextBuf, sizeof(gyroTextBuf), "Gyro Calibration: roll: %d, yaw: %d, pitch: %d", gyroscope.x, gyroscope.y, gyroscope.z);
	C2D_TextParse(&gyroText, g_dynamicBuf, gyroTextBuf);
	C2D_TextOptimize(&gyroText);
	C2D_DrawText(&gyroText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 98.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Helped me realize my joy stick is not calib.
	// Build simple graphical UI (o)
	char circleTextBuf[64];
	C2D_Text circleText;
	snprintf(circleTextBuf, sizeof(circleTextBuf), "Circle Pad Calibration: x: %d, y: %d", circlePad.dx, circlePad.dy);
	C2D_TextParse(&circleText, g_dynamicBuf, circleTextBuf);
	C2D_TextOptimize(&circleText);
	C2D_DrawText(&circleText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
  
	// 0-1 Floats
	char sliderTextBuf[64];
	C2D_Text sliderText;
	snprintf(sliderTextBuf, sizeof(sliderTextBuf), "Slider Calibration: position: %f", sliderPosition);
	C2D_TextParse(&sliderText, g_dynamicBuf, sliderTextBuf);
	C2D_TextOptimize(&sliderText);
	C2D_DrawText(&sliderText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 142.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Versioning for lookups
	// Move to classes?
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


static void sceneExit(void){
 // Delete the text buffers
 C2D_TextBufDelete(g_dynamicBuf);
 C2D_TextBufDelete(g_staticBuf);
}

// SCENE 1
static void sceneInit1(void){
    g_staticBuf1 = C2D_TextBufNew(4096);
    g_dynamicBuf1 = C2D_TextBufNew(4096);
	
	// Abstract it?
    C2D_TextParse(&g_staticText1[0], g_staticBuf1, "Device Health Check");
	C2D_TextParse(&g_staticText1[1], g_staticBuf1, "v1.0.0");
 	C2D_TextParse(&g_staticText1[2], g_staticBuf1, "Hack the planet!");
 	C2D_TextParse(&g_staticText1[3], g_staticBuf1, "Battery Health");
 	C2D_TextParse(&g_staticText1[4], g_staticBuf1, "Network Health");
	C2D_TextParse(&g_staticText1[5], g_staticBuf1, "Visit https://jaydevdesign.com for more source code!");


    C2D_TextOptimize(&g_staticText1[0]);
}

static void sceneRender1(size){
	C2D_TextBufClear(g_dynamicBuf1);

	// Abstract it?
	C2D_DrawText(&g_staticText1[0], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 12.0f, 24.0f, 0.5f, 0.75f, 0.5f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText1[1], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft,  220.0f, 24.0f, 0.5f, 0.65f, 0.45f, C2D_Color32f(0.0f,1.0f,0.0f,0.625f));
	C2D_DrawText(&g_staticText1[2], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 44.0f, 0.0f, 0.75f, 0.5f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText1[3], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 64.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText1[4], C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft , 12.0f, 142.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));
	C2D_DrawText(&g_staticText1[5], C2D_AtBaseline | C2D_WithColor | C2D_AlignRight , 376.0f, 240.0f, 0.0f, 0.5f, 0.4f, C2D_Color32f(0.0f,0.7f,1.0f,0.625f));

	// Battery Level
	// DOES NOT INIT ON PHYS SOFTWARE, NEED TO GET PTMU INIT LIKE ACU
	u8 batteryLevel;
	u8 batteryChargeState;
	bool adapterState;

	// Wifi Statuses
	u32 wifiStatus;
	u8 securityMode;
	bool proxyEnabled;

	// Check DOCS for init
	PTMU_GetBatteryLevel(&batteryLevel);
	PTMU_GetBatteryChargeState(&batteryChargeState);
	PTMU_GetAdapterState(&adapterState);
	
	ACU_GetWifiStatus(&wifiStatus);
	ACU_GetProxyEnable(&proxyEnabled);
	ACU_GetSecurityMode(&securityMode);

	char batLevBuf[64];
	C2D_Text batLevText;
	snprintf(batLevBuf, sizeof(batLevBuf), "Current Battery Level: %d/5", batteryLevel );
	C2D_TextParse(&batLevText, g_dynamicBuf1, batLevBuf);
	C2D_TextOptimize(&batLevText);
	C2D_DrawText(&batLevText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 76.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Battery Charge State
	char batChgBuf[64];
	C2D_Text batChgText;
	snprintf(batChgBuf, sizeof(batChgBuf), "Battery Charge State: %d", batteryChargeState );
	C2D_TextParse(&batChgText, g_dynamicBuf1, batChgBuf);
	C2D_TextOptimize(&batChgText);
	C2D_DrawText(&batChgText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 98.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Adapter State
	char adpStBuf[64];
	C2D_Text adpStText;
	if(adapterState){
		snprintf(adpStBuf, sizeof(adpStBuf), "Adapter State: Connected" );
	}else{
		snprintf(adpStBuf, sizeof(adpStBuf), "Adapter State: Disconnected" );
	}
	C2D_TextParse(&adpStText, g_dynamicBuf1, adpStBuf);
	C2D_TextOptimize(&adpStText);
	C2D_DrawText(&adpStText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 120.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Wifi Status
	char wifiStBuf[64];
	C2D_Text wifiStText;
	if(wifiStatus == 0){
		snprintf(wifiStBuf, sizeof(wifiStBuf), "Wifi Status: Disconnected" );
	}else{
		snprintf(wifiStBuf, sizeof(wifiStBuf), "Wifi Status: Connected" );
	}
	C2D_TextParse(&wifiStText, g_dynamicBuf1, wifiStBuf);
	C2D_TextOptimize(&wifiStText);
	C2D_DrawText(&wifiStText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 154.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	u8 osGetWifiStrength(void)
	{
	return OS_SharedConfig->wifi_strength;
	}
	int wifiStrength = osGetWifiStrength();
	char *wifiMsg = NULL;
	// CONVERT TO LOOKUP TBL
	switch(wifiStrength)
	{
		case 1: wifiMsg = "Low"; break;
		case 2: wifiMsg = "Okay"; break;
		case 3: wifiMsg = "Amazing"; break;
	}
	char wifiTextBuf[64];
	C2D_Text wifiText;
	snprintf(wifiTextBuf, sizeof(wifiTextBuf), "Wifi Strength : %s", wifiMsg);
	C2D_TextParse(&wifiText, g_dynamicBuf1, wifiTextBuf);
	C2D_TextOptimize(&wifiText);
	C2D_DrawText(&wifiText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 176.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Proxy Status
	char proxyStBuf[64];
	C2D_Text proxyStText;
	if(proxyEnabled){
		snprintf(proxyStBuf, sizeof(proxyStBuf), "Proxy Status: Enabled" );
	}else{
		snprintf(proxyStBuf, sizeof(proxyStBuf), "Proxy Status: Disabled" );
	}
	C2D_TextParse(&proxyStText, g_dynamicBuf1, proxyStBuf);
	C2D_TextOptimize(&proxyStText);
	C2D_DrawText(&proxyStText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 198.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));

	// Security Mode
	char secModeBuf[64];
	C2D_Text secModeText;
	// CONVERT TO LOOKUP TBL
	switch(securityMode){
		case 0:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: Open Auth" );
			break;
		case 1:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WEP-40" );
			break;
		case 2:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WPA-104" );
			break;
		case 3:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WEP-128" );
			break;
		case 4:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WPA TKIP" );
			break;
		case 5:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WPA2 TKIP" );
			break;
		case 6:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WPA AES" );
			break;
		case 7:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: WPA2 AES" );
			break;
		default:
			snprintf(secModeBuf, sizeof(secModeBuf), "Security Mode: Unknown" );
			break;
	}
	C2D_TextParse(&secModeText, g_dynamicBuf1, secModeBuf);
	C2D_TextOptimize(&secModeText);
	C2D_DrawText(&secModeText, C2D_AtBaseline | C2D_WithColor | C2D_AlignLeft, 24.0f, 220.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1.0f,1.0f,1.0f,1.0f));
}

static void sceneExit1(){
	// Lets not memory leak my 3DS :)
    C2D_TextBufDelete(g_dynamicBuf1);
    C2D_TextBufDelete(g_staticBuf1);
}

// MAIN
int main()
{
	// IGNORE THIS COMMENT - FOR DOCS PROJECT
	// ######################################################
	// 3DS GRAPHICS PIPELINE:
	// GFX gives card access w/ Init (gfxInitDefault())
	// INIT 3D and 2D Respectively
	// In this case, I focus only on 2D for now (C2D_Prepare())
	// IN LOOP:
	//  1. SYNCDRAW FRAME IN FRAMEBEGIN (3D)
	//  2. CLEAR FRAME
	//  3. BEGIN SCENE RENDER
	//  4. DRAWING, SHADERS, ETC. IN RENDER FUNC
	//  5. END FRAME
	// #######################################################

	// Initialize graphics
	gfxInitDefault();
	// 3D Init necessary for 2D function
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	// Scene state
	int renderedScene = 0;
	int *currentScene = &renderedScene;

	// Create screen 
	// Can be used for bottom as well
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	
	// Initialize the scene (not included in loop)
	sceneInit();
	sceneInit1();

	float size = 0.5f;
		
		// BEGIN ANIMATION LOOP
		// Can be optimized further
	while (aptMainLoop())
	{
		// User input event scanner
		hidScanInput();
		
		// User input event output (citro2D u32)
		u32 kDown = hidKeysDown();

		if(*currentScene == 0){
			// Start C3D Frame (Move outside?)
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW); // Move out of if?
			// I like black screen terminals Im sorry <3
			// Clear screen
			// Move these out of if?
			C2D_TargetClear(top, C2D_Color32(0x02, 0x02, 0x02, 0xFF));
			C2D_SceneBegin(top);
			// isolate to if
			sceneRender(size); 
			C3D_FrameEnd(0);
		}
		if(kDown & KEY_A){
			if(*currentScene == 0){
				renderedScene = 1;
			} else {
				renderedScene = 0;
			}
			if(*currentScene == 1){
				// remove 
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				// Both dark screens :3
				// remove
				C2D_TargetClear(top, C2D_Color32(0x02, 0x02, 0x02, 0xFF));
				C2D_SceneBegin(top);
				// isolate
				sceneRender1(size);
				// move out of else
				C3D_FrameEnd(0);
			} 
		}
	

		if(kDown & KEY_START)break;
	}
	// END ANIMATION LOOP

	// Deinitialize the scene
	sceneExit();
	
	// Deinitialize the libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
