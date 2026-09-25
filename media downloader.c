#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char url[192];
char *folder_path = "%USERPROFILE%\\Downloads";
char yt_dlp_container[512];
char ffmpeg_cmd[512];
char video_name[128];

int generate_time(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timebuf[32];  // FIX: local buffer instead of malloc
    strftime(timebuf, sizeof(timebuf), "%d_%m_%y_%H_%M_%S", t);

    snprintf(video_name, sizeof(video_name), "vid_%s", timebuf);
    return 0;
}

int yt_dlp(void) {
    generate_time();

    // Build base command
    int len = snprintf(yt_dlp_container, sizeof(yt_dlp_container),
                       "yt-dlp \"%s\" -o \"%s\\%s.mp4\"", url, folder_path, video_name);
    system(yt_dlp_container);
    return 0;
}

int main(void) {
    printf("Welcome to the Media Downloader!\n\n");

    do {
        memset(url, 0, sizeof(url));
        printf("Enter a URL: ");
        scanf("%191s", url);

        if (strstr(url, "https://") != url) {
            printf("Invalid url format. Try again.\n");
        }
    } while (strstr(url, "https://") != url);

    char browser[8];
    //Add a check for youtube and specify how it works (or not)
    if(strstr(url, "youtube") != url){
        printf("\nIt appears you tried to download a video from youtube.\n");
        printf("Unfortunatly youtube downloading isn't supported because it requires browser cookies \nSadly only firefox allow to use cookies\n");
        printf("If you wish to continue please ");
        printf("If you have firefox installed AND have a youtube session in your cookies.");
        scanf("%s",browser);
    }

    printf("\nURL successfully registered\n");

    int format;
    do {
        printf("1. MP4\n2. GIF\n");
        int result = scanf("%d", &format);
        if (result != 1) {
            printf("Invalid entry, input must be a number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            format = 0;
        }
    } while (format != 1 && format != 2);

    if (format == 1) {
        printf("You selected to download in .mp4\n");
        printf("The download will now start\n");
        yt_dlp();
    } else if (format == 2) {
        printf("You selected to download in .gif\n");
        printf("The download will now start\n");
        yt_dlp();

        snprintf(ffmpeg_cmd, sizeof(ffmpeg_cmd),
        "ffmpeg -i \"%s\\%s.mp4\" -vf \"fps=20,scale=480:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse\" \"%s\\gif_%s.gif\"",
        folder_path, video_name, folder_path, video_name);
        system(ffmpeg_cmd);

        printf("Download complete\n");
        printf("Deleting temporary file\n");

        char del_cmd[256];
        snprintf(del_cmd, sizeof(del_cmd), "del \"%s\\%s.mp4\"", folder_path, video_name);
        system(del_cmd);
        
        printf("Temporary file deleted, Exiting program\n");
    }
    return 0;
}