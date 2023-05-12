#!/bin/bash

cd ~
mkdir Documents Pictures Videos Music
echo XDG_DESKTOP_DIR="$HOME/Desktop">>$HOME/.config/user-dirs.dirs
echo XDG_DOCUMENTS_DIR="$HOME/Documents">>$HOME/.config/user-dirs.dirs
echo XDG_DOWNLOAD_DIR="$HOME/Downloads">>$HOME/.config/user-dirs.dirs
echo XDG_MUSIC_DIR="$HOME/Music">>$HOME/.config/user-dirs.dirs
echo XDG_PICTURES_DIR="$HOME/Pictures">>$HOME/.config/user-dirs.dirs
echo XDG_PUBLICSHARE_DIR="$HOME/Public">>$HOME/.config/user-dirs.dirs
echo XDG_TEMPLATES_DIR="$HOME/Templates">>$HOME/.config/user-dirs.dirs
echo XDG_VIDEOS_DIR="$HOME/Videos">>$HOME/.config/user-dirs.dirs