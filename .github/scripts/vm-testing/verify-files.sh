 #!/bin/bash


if [[ -f "$HOME/Documents/document.doc" ]]; then
    echo "Document Verification Complete"
else
    echo "Document Verification Failed"
    exit 1
fi

if [[ -f "$HOME/Pictures/blackhole.jpg" ]]; then
    echo "Picture Verification Complete"
else
    echo "Picture Verification Failed"
    exit 1
fi

if [[ -f "$HOME/Videos/horse.mp4" ]]; then
    echo "Video Verification Complete"
else
    echo "Video Verification Failed"
    exit 1
fi

if [[ ! -f "$HOME/add.py" ]]; then
    echo "General Files Verification Complete"
else
    echo "General Files Verification Failed"
    exit 1
fi