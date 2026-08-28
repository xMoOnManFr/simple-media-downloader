#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    //Startup text
    printf("Welcome to the Media Downloader!\n");

    char url[256];

    //URL checking logic
    do {
        printf("Enter a URL: ");
        scanf("%64s", url);
        
        // Check condition: if INVALID, loop repeats
        if (strstr(url, "https://") != url) {
            printf("Invalid format. Try again.\n");
        }
    } while (strstr(url, "https://") != url);

    printf("URL successfully registered\n");

    printf("In which format do you wish to save your file ?\n");
    printf("1. mp4\n");
    printf("2. GIF\n");

    int format; 
    scanf("%d", &format);

    char *rm = "del temp_vid.mp4";
    char yt_dlp[128];
    char ffmpeg[256];
    char *temp_name = "temp_vid";

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[80];
    
    // %d = day, %m = month, %y = 2-digit year
    strftime(buffer, sizeof(buffer), "%d_%m_%y", t);


    if(format == 1){
        printf("You selected to download in .MP4\n");
        printf("The download will now start\n");

        //Download the video
        snprintf(yt_dlp,sizeof(yt_dlp), "yt-dlp \"%s\" -o \"video_%s\"", url,buffer);
        system(yt_dlp);

        //TODO: Open yt-dlp and download file, then write the file to the selected folder
    
    }else if(format == 2){
        printf("You selected to download in .GIF\n");
        printf("The download will now start\n");

        //Download the video
        snprintf(yt_dlp,sizeof(yt_dlp), "yt-dlp \"%s\" -o temp_vid.mp4", url);
        system(yt_dlp);

        snprintf(ffmpeg, sizeof(ffmpeg), "ffmpeg -i \"%s.mp4\" -vf \"fps=20,scale=480:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse\" \"gif_%s.gif\"", temp_name, buffer);
        system(ffmpeg);
        printf("Download complete\n");
        printf("Deleting temporary file\n");
        system(rm);
        printf("Temporary file deleted, Exiting program");
    
    }else{
        do{
            printf("Invalid format. Try again.\n");
            printf("1. mp4\n");
            printf("2. GIF\n");
            scanf("%d", &format);
    
        } while (format != 1 && format != 2);

    }
    return 0;
}