// Burner Config file module
#include "SDL/SDL.h"

#include "burner.h"

#include <dirent.h>

int nIniVersion = 0;

CFG_OPTIONS options;
CFG_KEYMAP keymap;
CFG_AUTOFIRE autofire;

// ---------------------------------------------------------------------------
// config file parsing

TCHAR* LabelCheck(TCHAR* s, TCHAR* pszLabel)
{
	INT32 nLen;
	if (s == NULL) {
		return NULL;
	}
	if (pszLabel == NULL) {
		return NULL;
	}
	nLen = _tcslen(pszLabel);

	SKIP_WS(s);													// Skip whitespace

	if (_tcsncmp(s, pszLabel, nLen)){							// Doesn't match
		return NULL;
	}
	return s + nLen;
}

// Read in the config file for the whole application
int ConfigAppLoad()
{
	char szConfig[MAX_PATH];
	char szLine[256];
	FILE *h;

	sprintf((char*)szConfig, "%s/%s", szAppHomePath, "fbasdl.ini");

	if ((h = fopen(szConfig,"rt")) == NULL) {
		return 1;
	}

	// Go through each line of the config file
	while (fgets(szLine, sizeof(szLine), h)) {
		int nLen;

		nLen = strlen(szLine);

		// Get rid of the linefeed at the end
		if (szLine[nLen - 1] == 10) {
			szLine[nLen - 1] = 0;
			nLen--;
		}

#define VAR(x) { char *szValue = LabelCheck(szLine,#x);		\
  if (szValue) x = strtol(szValue, NULL, 0); }
#define FLT(x) { char *szValue = LabelCheck(szLine,#x);		\
  if (szValue) x = atof(szValue); }
#define STR(x) { char *szValue = LabelCheck(szLine,#x " ");	\
  if (szValue) strcpy(x,szValue); }

		VAR(nIniVersion);

		// Other
		STR(szAppRomPaths[0]);
		STR(szAppRomPaths[1]);
		STR(szAppRomPaths[2]);
		STR(szAppRomPaths[3]);
		STR(szAppRomPaths[4]);
		STR(szAppRomPaths[5]);
		STR(szAppRomPaths[6]);
		STR(szAppRomPaths[7]);
		STR(szAppRomPaths[8]);
		STR(szAppRomPaths[9]);
		STR(szAppRomPaths[10]);
		STR(szAppRomPaths[11]);
		STR(szAppRomPaths[12]);
		STR(szAppRomPaths[13]);
		STR(szAppRomPaths[14]);
		STR(szAppRomPaths[15]);
		STR(szAppRomPaths[16]);
		STR(szAppRomPaths[17]);
		STR(szAppRomPaths[18]);
		STR(szAppRomPaths[19]);
#undef STR
#undef FLT
#undef VAR
	}

	fclose(h);
	return 0;
}

// Write out the config file for the whole application
int ConfigAppSave()
{
	char szConfig[MAX_PATH];
	FILE *h;

	sprintf((char*)szConfig, "%s/%s", szAppHomePath, "fbasdl.ini");

	if ((h = fopen(szConfig, "wt")) == NULL) {
		return 1;
	}


#define VAR(x) fprintf(h, #x " %d\n", x)
#define FLT(x) fprintf(h, #x " %f\n", x)
#define STR(x) fprintf(h, #x " %s\n", x)

	fprintf(h,"\n// The application version this file was saved from\n");
	// We can't use the macros for this!
	fprintf(h, "nIniVersion 0x%06X", nBurnVer);

	fprintf(h,"\n\n// The paths to search for rom zips. (include trailing backslash)\n");
	STR(szAppRomPaths[0]);
	STR(szAppRomPaths[1]);
	STR(szAppRomPaths[2]);
	STR(szAppRomPaths[3]);
	STR(szAppRomPaths[4]);
	STR(szAppRomPaths[5]);
	STR(szAppRomPaths[6]);
	STR(szAppRomPaths[7]);
	STR(szAppRomPaths[8]);
	STR(szAppRomPaths[9]);
	STR(szAppRomPaths[10]);
	STR(szAppRomPaths[11]);
	STR(szAppRomPaths[12]);
	STR(szAppRomPaths[13]);
	STR(szAppRomPaths[14]);
	STR(szAppRomPaths[15]);
	STR(szAppRomPaths[16]);
	STR(szAppRomPaths[17]);
	STR(szAppRomPaths[18]);
	STR(szAppRomPaths[19]);

	fprintf(h,"\n\n\n");

#undef STR
#undef FLT
#undef VAR

	fclose(h);
	return 0;
}

void setGameDefault(bool vertical)
{
	printf("Initialize default configuration options\n");
	// Initialize configuration options
	options.sound = 2;
	options.samplerate = 2;		// 0 - 11025, 1 - 16000, 2 - 22050, 3 - 32000
	options.vsync = 0;
	options.rescale = 0;		// no scaling by default
	if(vertical)
		options.rotate = 2;
	else
		options.rotate = 0;
	options.hwscaling = 2;		// HW scaling full screen by default
	options.showfps = 0;
	options.frameskip = -1;		// auto frameskip by default
	options.create_lists = 0;
	options.m68kcore = 0;		// 0 - c68k, 1 - m68k, 2 - a68k
	options.z80core = 0;
	options.sense = 100;

	keymap.up = 0x77;
	keymap.down = 0x73;
	keymap.left = 0x71;
	keymap.right = 0x64;
	if(vertical) {
		keymap.fire1 = 0x5F;	// B
		keymap.fire2 = 0x5E;	// A
		keymap.fire3 = 0x61;	// Y
		keymap.fire4 = 0x60;	// X
	} else {
		keymap.fire1 = 0x79;	// Y
		keymap.fire2 = 0x62;	// B
		keymap.fire3 = 0x78;	// X
		keymap.fire4 = 0x61;	// A
	}
	keymap.fire5 = 0x64;	// L
	keymap.fire6 = 0x65;	// R
	keymap.coin1 = 0x6E;	// SELECT
	keymap.start1 = 0x6D;	// START
	keymap.pause = SDLK_p;
	keymap.quit = 0x75;
	keymap.qsave = 0x66;		// quick save
	keymap.qload = 0x67;		// quick load

	autofire.fire1.key = keymap.fire3;
	autofire.fire2.key = keymap.fire4;
	autofire.fire3.key = keymap.fire5;
	autofire.fire4.key = keymap.fire6;
	autofire.fire5.key = keymap.fire1;
	autofire.fire6.key = keymap.fire2;
	if(vertical) {
		autofire.fire1.fps = 6;
		autofire.fire2.fps = 6;
	} else {
		autofire.fire1.fps = 0;
		autofire.fire2.fps = 0;
	}
	autofire.fire3.fps = 0;
	autofire.fire4.fps = 0;
	autofire.fire5.fps = 0;
	autofire.fire6.fps = 0;
}

void ConfigGameAllDefault()
{
	ConfigGameLoadVDefault();
	ConfigGameLoadDefault();
}

void ConfigGameDefault()
{
	if (nBurnDrvActive == ~0U)
		return;
	// bool bVertical = BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL;
	bool bVertical = false;
	if(bVertical) {
		if (ConfigGameLoadVDefault()) {
			printf("ConfigGameLoadVDefault true\n");
			return;
		}
	} else {
		if (ConfigGameLoadDefault()) {
			printf("ConfigGameLoadDefault true\n");
			return;
		}
	}
	setGameDefault(bVertical);
}

int ConfigGameLoad(FILE * f)
{
	char arg1[1024];
	signed long argd;
	char line[1024];

	while(fgets(line,sizeof(line),f) != NULL) {
		sscanf(line, "%s %d", &arg1, &argd);

		if(strcmp(arg1, "#") != 0) {
			if(strcmp(arg1, "FBA_SOUND") == 0) options.sound = argd;
			if(strcmp(arg1, "FBA_SAMPLERATE") == 0) options.samplerate = argd;
			if(strcmp(arg1, "FBA_VSYNC") == 0) options.vsync = argd;
			if(strcmp(arg1, "FBA_RESCALE") == 0) options.rescale = argd;
			if(strcmp(arg1, "FBA_ROTATE") == 0) options.rotate = argd;
			if(strcmp(arg1, "FBA_HWSCALING") == 0) options.hwscaling = argd;
			if(strcmp(arg1, "FBA_SHOWFPS") == 0) options.showfps = argd;
			if(strcmp(arg1, "FBA_FRAMESKIP") == 0) options.frameskip = argd;
			if(strcmp(arg1, "FBA_M68KCORE") == 0) options.m68kcore = argd;
			if(strcmp(arg1, "FBA_Z80CORE") == 0) options.z80core = argd;
			if(strcmp(arg1, "FBA_SENSE") == 0) options.sense = argd;

			if(strcmp(arg1, "KEY_UP") == 0) keymap.up = argd;
			if(strcmp(arg1, "KEY_DOWN") == 0) keymap.down = argd;
			if(strcmp(arg1, "KEY_LEFT") == 0) keymap.left = argd;
			if(strcmp(arg1, "KEY_COIN1") == 0) keymap.coin1 = argd;
			if(strcmp(arg1, "KEY_START1") == 0) keymap.start1 = argd;
			if(strcmp(arg1, "KEY_RIGHT") == 0) keymap.right = argd;
			if(strcmp(arg1, "KEY_FIRE1") == 0) keymap.fire1 = argd;
			if(strcmp(arg1, "KEY_FIRE2") == 0) keymap.fire2 = argd;
			if(strcmp(arg1, "KEY_FIRE3") == 0) keymap.fire3 = argd;
			if(strcmp(arg1, "KEY_FIRE4") == 0) keymap.fire4 = argd;
			if(strcmp(arg1, "KEY_FIRE5") == 0) keymap.fire5 = argd;
			if(strcmp(arg1, "KEY_FIRE6") == 0) keymap.fire6 = argd;
			if(strcmp(arg1, "KEY_QUIT") == 0) keymap.quit = argd;
			if(strcmp(arg1, "KEY_PAUSE") == 0) keymap.pause = argd;

			if(strcmp(arg1, "AUTO_FIRE1_FPS") == 0) autofire.fire1.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE1_KEY") == 0) autofire.fire1.key = argd;
			if(strcmp(arg1, "AUTO_FIRE2_FPS") == 0) autofire.fire2.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE2_KEY") == 0) autofire.fire2.key = argd;
			if(strcmp(arg1, "AUTO_FIRE3_FPS") == 0) autofire.fire3.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE3_KEY") == 0) autofire.fire3.key = argd;
			if(strcmp(arg1, "AUTO_FIRE4_FPS") == 0) autofire.fire4.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE4_KEY") == 0) autofire.fire4.key = argd;
			if(strcmp(arg1, "AUTO_FIRE5_FPS") == 0) autofire.fire5.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE5_KEY") == 0) autofire.fire5.key = argd;
			if(strcmp(arg1, "AUTO_FIRE6_FPS") == 0) autofire.fire6.fps = argd;
			if(strcmp(arg1, "AUTO_FIRE6_KEY") == 0) autofire.fire6.key = argd;
		}
	}
	return 1;
}

int ConfigGameLoad()
{
	FILE *f;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/%s.cfg", szAppConfigPath, BurnDrvGetTextA(DRV_NAME));
	if(!(f = fopen(cfgname,"r"))) {
		// set default values and exit
		printf("no found config file:%s set default\n", cfgname);
		ConfigGameDefault();
		return 0;
	}
	int ret = ConfigGameLoad(f);
	fclose(f);
	return ret;
}

int ConfigGameLoadDefault()
{
	FILE *f;
	char cfgname[MAX_PATH];
	sprintf((char*)cfgname, "%s/default.cfg", szAppHomePath);
	if(!(f = fopen(cfgname,"r"))) {
		printf("no found config file:%s\n", cfgname);
		setGameDefault(false);
		return 0;
	}

	int ret = ConfigGameLoad(f);

	fclose(f);

	return ret;
}

int ConfigGameLoadVDefault()
{
	FILE *f;
	char cfgname[MAX_PATH];
	sprintf((char*)cfgname, "%s/vdefault.cfg", szAppHomePath);
	if(!(f = fopen(cfgname,"r"))) {
		printf("no found config file:%s\n", cfgname);
		setGameDefault(true);
		return 0;
	}

	int ret = ConfigGameLoad(f);

	fclose(f);

	return ret;
}

int ConfigGameSave(FILE * fp)
{
	fprintf(fp, "# FBA config file\n");
	fprintf(fp, "# %s\n\n", BurnDrvGetTextA(DRV_NAME));

	fprintf(fp, "FBA_SOUND %d\n", options.sound);
	fprintf(fp, "FBA_SAMPLERATE %d\n", options.samplerate);
	fprintf(fp, "FBA_VSYNC %d\n", options.vsync);
	fprintf(fp, "FBA_RESCALE %d\n", options.rescale);
	fprintf(fp, "FBA_ROTATE %d\n", options.rotate);
	fprintf(fp, "FBA_HWSCALING %d\n", options.hwscaling);
	fprintf(fp, "FBA_SHOWFPS %d\n", options.showfps);
	fprintf(fp, "FBA_FRAMESKIP %d\n", options.frameskip);
	fprintf(fp, "FBA_M68KCORE %d\n", options.m68kcore);
	fprintf(fp, "FBA_Z80CORE %d\n", options.z80core);
	fprintf(fp, "FBA_SENSE %d\n", options.sense);

	fprintf(fp, "\n# Keys layout\n\n");
	fprintf(fp, "KEY_UP %d\n", keymap.up);
	fprintf(fp, "KEY_DOWN %d\n", keymap.down);
	fprintf(fp, "KEY_LEFT %d\n", keymap.left);
	fprintf(fp, "KEY_RIGHT %d\n", keymap.right);
	fprintf(fp, "KEY_COIN1 %d\n", keymap.coin1); 
	fprintf(fp, "KEY_START1 %d\n", keymap.start1);
	fprintf(fp, "KEY_FIRE1 %d\n", keymap.fire1);
	fprintf(fp, "KEY_FIRE2 %d\n", keymap.fire2);
	fprintf(fp, "KEY_FIRE3 %d\n", keymap.fire3);
	fprintf(fp, "KEY_FIRE4 %d\n", keymap.fire4);
	fprintf(fp, "KEY_FIRE5 %d\n", keymap.fire5);
	fprintf(fp, "KEY_FIRE6 %d\n", keymap.fire6);
	fprintf(fp, "KEY_QUIT %d\n", keymap.quit);
	fprintf(fp, "KEY_PAUSE %d\n", keymap.pause);

	fprintf(fp, "AUTO_FIRE1_FPS %d\n", autofire.fire1.fps);
	fprintf(fp, "AUTO_FIRE1_KEY %d\n", autofire.fire1.key);
	fprintf(fp, "AUTO_FIRE2_FPS %d\n", autofire.fire2.fps);
	fprintf(fp, "AUTO_FIRE2_KEY %d\n", autofire.fire2.key);
	fprintf(fp, "AUTO_FIRE3_FPS %d\n", autofire.fire3.fps);
	fprintf(fp, "AUTO_FIRE3_KEY %d\n", autofire.fire3.key);
	fprintf(fp, "AUTO_FIRE4_FPS %d\n", autofire.fire4.fps);
	fprintf(fp, "AUTO_FIRE4_KEY %d\n", autofire.fire4.key);
	fprintf(fp, "AUTO_FIRE5_FPS %d\n", autofire.fire5.fps);
	fprintf(fp, "AUTO_FIRE5_KEY %d\n", autofire.fire5.key);
	fprintf(fp, "AUTO_FIRE6_FPS %d\n", autofire.fire6.fps);
	fprintf(fp, "AUTO_FIRE6_KEY %d\n", autofire.fire6.key);

	return 1;
}

int ConfigGameSave()
{
	FILE *fp;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/%s.cfg", szAppConfigPath, BurnDrvGetTextA(DRV_NAME));
	fp = fopen(cfgname, "w");
	printf("ConfigGameSave:%s\n",cfgname);
	int ret = ConfigGameSave(fp);

	fclose(fp);
	return ret;
}

int ConfigGameSaveDefault()
{
	FILE *fp;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/default.cfg", szAppHomePath);
	fp = fopen(cfgname, "w");
	printf("ConfigGameSaveDefault:%s\n",cfgname);
	int ret = ConfigGameSave(fp);

	fclose(fp);
	return ret;
}

int ConfigGameSaveVDefault()
{
	FILE *fp;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/vdefault.cfg", szAppHomePath);
	fp = fopen(cfgname, "w");
	printf("ConfigGameSaveVDefault:%s\n",cfgname);
	int ret = ConfigGameSave(fp);

	fclose(fp);
	return ret;
}

void ConfigGameDelete()
{
	dirent *file;
	DIR *dir;
	char cfgname[MAX_PATH];

	sprintf((char*)cfgname, "%s/", szAppConfigPath);

	dir = opendir(cfgname);
	while (file = readdir(dir)) {
		if (strlen(file->d_name) > 4 && strncmp(".cfg", file->d_name + strlen(file->d_name) - 4, 4) == 0) {
			sprintf((char*)cfgname, "%s/%s", szAppConfigPath, file->d_name);
			remove(cfgname);
			printf("ConfigGameDelete:%s\n",cfgname);
		}
	}

}

void ConfigGameDefaultDelete() {
	char cfgname[MAX_PATH];
	sprintf((char*)cfgname, "%s/default.cfg", szAppHomePath);

	remove(cfgname);
	printf("ConfigGameDefaultDelete:%s\n",cfgname);
	sprintf((char*)cfgname, "%s/vdefault.cfg", szAppHomePath);
	remove(cfgname);
	printf("ConfigGameVDefaultDelete:%s\n",cfgname);
}
