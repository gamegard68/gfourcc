# gfourcc
GUI Tool written in gtkmm3 for the purpose of changing the FOURCC Code and Description of an AVI file

![GFourCC Utility](/screenshots/gfourcc_scrn.png?raw=true "GFourCC Utility")

USAGE
-----
Three ways to open an AVI file:
1. Click the FileChooserButton to open the FileChooserDialog.
2. Start gfourcc via command prompt and pass the Avi File as an argument.
3. Drag and Drop the Avi File onto the GUI Tool.

INSTALL
-------
a. Building from Source

    Briefly, prepare, build and install GFourCC into the default location of
    /usr/local using:
    
    Preparation and Build
    ---------------------
    *** Method 1 ***
    ./autogen.sh
    make
       
    *** Method 2 ***
    autoreconf --install
    ./configure
    make
      
    *** Method 3 ***
    gnome-autogen.sh --prefix=<aprefix>
    make
    
    Installation
    ------------
    sudo make install // With Debug Information
      or
    sudo make install-strip // Stripped without Debug Info
          
   The following dependencies are required to build GFourCC from source:
      g++,
      make,
      gnome-common,
      gtkmm3


    
