# gfourcc
GUI Tool for changing the FOURCC Codec and Description of an AVI file.

![GFourCC Utility](/screenshots/gfourcc_scrn.png?raw=true "GFourCC Utility")

INSTALL
-------
a. Building from Source

Preparation and Build

    ./autogen.sh --prefix=/usr
    make
      
Installation

    sudo make install // With Debug Information
         or
    sudo make install-strip // Stripped without Debug Info
          
    The following dependencies are required to build GFourCC from source:
        g++,
        make,
        gnome-common,
        gtkmm3

b. Installing from the Arch User Repository (AUR)

    yay -S gfourcc 

USAGE
-----
Three ways to open an AVI file:
1. Open the GUI tool and click the FileChooser Button to open the FileChooser Dialog.
2. Start gfourcc via command prompt and pass the Avi File as an argument.
3. Drag and Drop the Avi File onto the GUI Tool.


