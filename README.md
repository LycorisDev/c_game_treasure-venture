# Treasure Venture

*Treasure Venture* is a text adventure game, which means it's interacted with through written commands, and only displays written text. There is no graphical element.

*Treasure Venture* understands several commands, can save the ongoing game, and has events. An example of event is to have the doors lock up behind the player when they cross the mansion's threshold for the first time. It also contains a mini-game entitled "[Twenty Squares](https://github.com/TheLycorisRadiata/c_game_twentysquares)", that I leave you to discover as well as the game itself.  

---

Written in C, it's available in two versions: CLI and GUI. "CLI" stands for "Command-Line Interface", and is the version which runs in the terminal, whereas "GUI" stands for "Graphics User Interface" and this version opens a window. The GUI is made with GTK4, a C library.  

Both versions work on Linux, and they may or may not work on Mac, but only the CLI version works on Windows. GTK may be a cross-platform library, I couldn't compile the GUI version for Windows, and it's not my priority at this time to figure this out.  

