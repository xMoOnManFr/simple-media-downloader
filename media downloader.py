import os
import subprocess
import time
import tkinter

def download():
    url = link_input.get()

    destination = os.path.join(os.path.expanduser("~"), "Downloads")

    unique_name = f"gif_{time.strftime('%d%m%Y_%H%M%S')}"

    video_temp = os.path.join(destination, f"{unique_name}.mp4")
    gif_sortie = os.path.join(destination, f"{unique_name}.gif")

    subprocess.run(["yt-dlp", "-o", video_temp, url])

    subprocess.run(["ffmpeg","-i",video_temp,"-vf","fps=10,scale=480:-1:flags=lanczos,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse","-y",gif_sortie,])

    if os.path.exists(video_temp):
        os.remove(video_temp)

    print(f"GIF enregistré : {gif_sortie}")
    os.startfile(destination)

root = tkinter.Tk()

bg_color = "#424449"

root.title("Media Downloader")
root.configure(background=bg_color)
root.minsize(600, 300)

tkinter.Label(
    root,
    bg="#424449",
    fg="white",
    text="Welcome to the media downloader !\n Please input your link below",
).pack()

link_input = tkinter.Entry(
    root, width=75, bg="#84868e", fg="White", borderwidth=0
)
link_input.pack()

tkinter.Label(root, bg=bg_color).pack()

dl_button = tkinter.Button(root, width=20, text="Download", command=download)
dl_button.pack(pady=5)

root.mainloop()
