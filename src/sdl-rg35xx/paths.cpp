
// Paths module
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "burner.h"

char szAppHomePath[MAX_PATH] = "./.fba";			// ~/.fba
char szAppSavePath[MAX_PATH] = "./.fba/saves";		// ~/.fba/saves
char szAppConfigPath[MAX_PATH] = "./.fba/configs";	// ~/.fba/configs
char szAppHiscorePath[MAX_PATH] = "./.fba/hiscore";	// ~/.fba/highscore // for burn/hiscore.cpp
char szAppSamplesPath[MAX_PATH] = "./.fba/samples";	// ~/.fba/samples // for burn/snd/samples.cpp
char szAppPreviewPath[MAX_PATH] = "./.fba/previews";	// ~/.fba/previews
char szAppRomPaths[DIRS_MAX][MAX_PATH] = {{"./"}, {"/usr/local/share/roms/"}, {"roms/"}, {"/media/sdcard/ROMS/FBA/"}, };
char szAppBlendPath[MAX_PATH] = "./.fba/blend"; 	// for cps_obj.cpp, neo_sprite.cpp, pgm_draw.cpp
char szAppHDDPath[MAX_PATH] = "./.fba/hdd/";
char szAppEEPROMPath[MAX_PATH] = "./.fba/games/";

void BurnPathsInit()
{
	printf("BurnPathsInit: begin\n");
#ifndef WIN32
	char *home = getenv("HOME");
	if(home) sprintf(szAppHomePath, "%s/.fba", home);
	printf("set szAppHomePath:%s\n",szAppHomePath);
	if(access(szAppHomePath,0) == 0) {//exists
		printf("dir exists!\n");
	}
	else {
		printf("dir not exists,will create!\n");
		int status = mkdir(szAppHomePath, 0700);
		if(status == -1) {
			printf("error when mkdir:%d\n",errno);
			getcwd(szAppHomePath, MAX_PATH);
			strcat(szAppHomePath, "/.fba");
			mkdir(szAppHomePath, 0700);
			printf("set szAppHomePath:%s\n",szAppHomePath);
		}
	}

	sprintf(szAppSavePath, "%s/saves", szAppHomePath);
	mkdir(szAppSavePath, 0700);

	sprintf(szAppConfigPath, "%s/configs", szAppHomePath);
	mkdir(szAppConfigPath, 0700);

	sprintf(szAppPreviewPath, "%s/previews", szAppHomePath);
	mkdir(szAppPreviewPath, 0700);

	sprintf(szAppSamplesPath, "%s/samples", szAppHomePath);
	mkdir(szAppSamplesPath, 0700);
#else
	getcwd(szAppHomePath, MAX_PATH);
	strcat(szAppHomePath, "/.fba");
	mkdir(szAppHomePath);

	sprintf(szAppSavePath, "%s/saves", szAppHomePath);
	mkdir(szAppSavePath);

	sprintf(szAppConfigPath, "%s/configs", szAppHomePath);
	mkdir(szAppConfigPath);

	sprintf(szAppPreviewPath, "%s/previews", szAppHomePath);
	mkdir(szAppPreviewPath);

	sprintf(szAppSamplesPath, "%s/samples", szAppHomePath);
	mkdir(szAppSamplesPath);

	sprintf(szAppHDDPath, "%s/hdd/", szAppHomePath);
	mkdir(szAppHDDPath, 0700);

	sprintf(szAppEEPROMPath, "%s/games/", szAppHomePath);
	mkdir(szAppEEPROMPath, 0700);
#endif
	printf("BurnPathsInit: end\n");
}
