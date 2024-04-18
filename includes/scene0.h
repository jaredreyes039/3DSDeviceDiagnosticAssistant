#include <stdio.h>
#include <3ds.h>
#include <citro2d.h>

static void initScene0(C2D_TextBuf statBuf, C2D_TextBuf dynBuf, C2D_Text *statText);
static void renderHeader0(C2D_Text *statText);
static void renderTimeInterface(C2D_TextBuf dynBuf);
static void renderTouchInterface(C2D_TextBuf dynBuf);
static void renderJoystickInterface(C2D_TextBuf dynBuf);
static void renderGyroInterface(C2D_TextBuf dynBuf);
static void renderSliderInterface(C2D_TextBuf dynBuf);
static void renderFirmwareInterface(C2D_TextBuf dynBuf);
static void compileInterfaces(C2D_TextBuf dynBuf);
static void buildScene0(float size, C2D_TextBuf dynBuf, C2D_Text *statText);
static void exitScene0(C2D_TextBuf statBuf, C2D_TextBuf dynBuf );
