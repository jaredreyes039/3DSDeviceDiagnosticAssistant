#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include "scene0.c"

// Scene 0
// C2D_TextBuf C2D_TextBufNew(size)
// struct {C2D_TextBuf buf; size_t begin; size_t end; float width; u32 lines; u32 words; C2D_Font font;} = C2D_Text 
C2D_TextBuf g_staticBuf, g_dynamicBuf;
C2D_Text g_staticText[6];

// Scene 1
C2D_TextBuf g_staticBuf1, g_dynamicBuf1;
C2D_Text g_staticText1[6];

static void initScene1(void){
	g_staticBuf1 = C2D_TextBufNew(4096);
	g_dynamicBuf1 = C2D_TextBufNew(4096);

	C2D_TextParse(&g_staticText1[0], g_staticBuf1, "Device Health Check");
	C2D_TextParse(&g_staticText1[1], g_staticBuf1, "v1.0.0");
 	C2D_TextParse(&g_staticText1[2], g_staticBuf1, "Hack the planet!");
 	C2D_TextParse(&g_staticText1[3], g_staticBuf1, "Battery Health");
 	C2D_TextParse(&g_staticText1[4], g_staticBuf1, "Network Health");
	C2D_TextParse(&g_staticText1[5], g_staticBuf1, "Visit https://jaydevdesign.com for more source code!");


	C2D_TextOptimize(&g_staticText1[0]);
}

static void renderScene1(size){
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
	// Initialize graphics
	gfxInitDefault();
	// 3D Init necessary for 2D function
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	// Prep init 2D
	C2D_Prepare();

	// Scene state
	int renderedScene = 0;
	int *currentScene = &renderedScene;
	
	// Create screen 
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	// Initialize the scene (not included in loop)
	initScene0(g_staticBuf, g_dynamicBuf, g_staticText);
	initScene1();
	float size = 0.5f;
		
	// BEGIN ANIMATION LOOP
	while (aptMainLoop())
	{
		// User input event scanner
		hidScanInput();
		u32 kDown = hidKeysDown();
		if(*currentScene == 0){
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW); // Move out of if?
			C2D_TargetClear(top, C2D_Color32(0x02, 0x02, 0x02, 0xFF));
			C2D_SceneBegin(top);
			buildScene0(size, g_dynamicBuf, g_staticText); 
			C3D_FrameEnd(0);
		}
		else{
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top, C2D_Color32(0x02, 0x02, 0x02, 0xFF));
			C2D_SceneBegin(top);
			renderScene1(size);
			C3D_FrameEnd(0);
		} 
		if(kDown & KEY_A){
			if(*currentScene == 0){
				renderedScene = 1;
			} else {
				renderedScene = 0;
			}
			
		}
		if(kDown & KEY_START)break;
	}
	// END ANIMATION LOOP

	// Deinitialize the scene
	exitScene0(g_staticBuf, g_dynamicBuf);
	
	// Deinitialize the libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
