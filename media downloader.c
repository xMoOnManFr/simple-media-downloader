#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(void){
    printf("Welcome to the Media Downloader!\n\n");
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

    //Vars needed for downloading and encoding magic
    char yt_dlp[192];
    char ffmpeg[256];
    char *temp_name = "temp_vid";

    //Logic to get different file names, also serves as a timestamp to sort files
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[80];

    //TODO: Write the file to the selected folder (If not bored create the folder/Verify it exist but will need extra imports)
    //Change this path to save to another folder/If anyone uses this
    char *folder_path = "C:\\Users\\moonman\\Documents\\cat gifs";
    
    // %d = day, %m = month, %y = 2-digit year, %S = seconds, %M = minutes, %H = hours
    strftime(buffer, sizeof(buffer), "%d_%m_%y_%S_%M_%H",t);
    
    //Logic to download as an MP4 
    if(format == 1){
        printf("You selected to download in .MP4\n");
        printf("The download will now start\n");

        //Download the video
        snprintf(yt_dlp, sizeof(yt_dlp), "yt-dlp \"%s\" -o \"%s\\video_%s.mp4\"", url, folder_path, buffer);
        system(yt_dlp);
    
    //Logic to download as an mp4 and reencode in GIF with ffmpeg
    }else if(format == 2){
    printf("You selected to download in .GIF\n");
    printf("The download will now start\n");

    snprintf(yt_dlp, sizeof(yt_dlp), "yt-dlp \"%s\" -o \"%s\\%s.mp4\"", url, folder_path, temp_name);
    system(yt_dlp);

    // Reencode to GIF, reading from and writing to folder_path
    snprintf(ffmpeg, sizeof(ffmpeg),
        "ffmpeg -i \"%s\\%s.mp4\" -vf \"fps=20,scale=480:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse\" \"%s\\gif_%s.gif\"",
        folder_path, temp_name, folder_path, buffer);
    system(ffmpeg);


    printf("Download complete\n");
    printf("Deleting temporary file\n");

    //Deleting the temp file needed for the reencoding
    char del_cmd[256];
    snprintf(del_cmd, sizeof(del_cmd), "del \"%s\\%s.mp4\"", folder_path, temp_name);
    system(del_cmd);

    printf("Temporary file deleted, Exiting program\n");
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
