#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char url[192];
char *folder_path = "\%userprofile%\\Downloads";
char yt_dlp_container[192];
char ffmpeg[256];
char *buffer;
char video_name[128];

int generate_time(void){
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    buffer = malloc(32);
    if (!buffer) return -1;
    strftime(buffer, 32, "%d_%m_%y_%H_%M_%S", t);

    snprintf(video_name, sizeof(video_name),"vid_\%s\"",buffer);
   return 0;
}

int yt_dlp(void){
    //calls the function to actually write in memory
    generate_time();

    //builds the command
    snprintf(yt_dlp_container, sizeof(yt_dlp_container), "yt-dlp \"%s\" -o \"%s\\%s.mp4\"", url, folder_path, video_name);

    //executes the command
    system(yt_dlp_container);
}

int main(void){

    printf("Welcome to the Media Downloader!\n\n");
    //int occurations = 0;

    //URL checking logic
    do {
        memset(url,0,sizeof(url)); // Clear the url buffer
        printf("Enter a URL: ");
        scanf("%s", url);
    
        //TODO: check for number of occurations of "https://" in the url, if more than 1, print error and ask for input again
        // Check condition: if INVALID, loop repeats
        if (strstr(url, "https://") != url) {
            printf("Invalid url format. Try again.\n");
        }
    } while (strstr(url, "https://") != url);

    printf("URL successfully registered\n");

    int result;
    int format; 

    do {
    printf("1. MP4\n");
    printf("2. GIF\n");
    result = scanf("%d", &format);

    //Checks to catch a char in the buffer
    if (result != 1) {
        printf("Invalid entry, the input must not be a number .\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        format = 0;
    }
} while (format != 1 && format != 2);

    //TODO: Write the file to the selected folder (If not bored create the folder/Verify it exist but will need extra imports)
    char *folder_path = "\%userprofile%\\Downloads";

    
    //Logic to download as an MP4 
    if(format == 1){
        printf("You selected to download in .mp4\n");
        printf("The download will now start\n");

        //Download the video
        yt_dlp();
    
    //Logic to download as an mp4 and reencode in GIF with ffmpeg
    }else if(format == 2){
    printf("You selected to download in .gif\n");
    printf("The download will now start\n");

    yt_dlp();
    
    // Reencode to GIF, reading from and writing to folder_path
    snprintf(ffmpeg, sizeof(ffmpeg),
    "ffmpeg -i \"%s\\%s.mp4\" ""-vf \"fps=20,scale=480:-1:flags=lanczos,split[s0][s1];""[s0]palettegen[p];[s1][p]paletteuse\" ""\"%s\\gif_%s.gif\""
    ,folder_path,video_name,folder_path,video_name);
    system(ffmpeg);

    printf("Download complete\n");
    printf("Deleting temporary file\n");

    //Deleting the temp file needed for the reencoding
    //TODO: Add a check to verify the file is actually deleted before proceeding
    //FILE *file = fopen(video_name, "r");
    char del_cmd[64];
    snprintf(del_cmd, sizeof(del_cmd), "del \"%s\\%s.mp4\"", folder_path, video_name);
    system(del_cmd);

    printf("Temporary file deleted, Exiting program\n");

}
    return 0;
}
