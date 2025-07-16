# Treasure Venture

*Treasure Venture* is a text adventure game, which means it's interacted with 
through written commands, and only displays written text. There is no graphical 
element. *Treasure Venture* also contains a mini-game entitled 
"[Twenty Squares](https://github.com/LycorisDev/c_game_twenty-squares)", that I 
leave you to discover as well as the game itself.  

Written in C, it's available in two versions: CLI and GUI. "CLI" stands for 
"Command-Line Interface", and is the version which runs in the terminal, 
whereas "GUI" stands for "Graphics User Interface" and this version opens a 
window. The GUI is made with GTK4, a C library.  

Linux can run both versions, Windows can run the CLI, and I don't know for 
Mac.  

**Makefile Rules for Compilation**
- `make`: GUI for Linux.
- `make cli`: CLI for Linux.
- `make win64` or `make win32`: CLI for Windows.
