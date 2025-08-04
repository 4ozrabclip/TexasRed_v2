# TexasRed.v2

TexasRed.v2 is a multi-tool application built with Qt to showcase my practical skills in C++ and GUI development.  This new Qt version is focused on lightweight practical tools for working with regex pattern matching, with an emphasis on aesthetic design and usability.

## Tools

#### Regex Sandbox
A live regex playground with real-time syntax highlighting.  Useful for  crafting and testing regular expressions safely.

#### Ema to Obj Converter
Eplans proprietary electrical CAD format .ema, to standard mesh obj format.  Currently not working, incomplete due to time restraint.  \
`This parser was originally written in Python in collaboration with Ross Leitch (Balbatross) during my contract with UltraViolet Ltd. Written permission has been granted by UltraViolet Ltd and Ross Leitch to be converted into Qt C++ and featured on TexasRed.v2.`


## Highlights

- Main window manages app flow
    - Back button with navigation history stack
    - Typing title animation on construction \
    ![Title Type Animation](/images/TitleType2.gif) 
    - Dark/Light mode toggle updates global settings\
    ![Theme Switch](/images/ThemeSwitch.gif)

- Individual pages encapsulate specific tools.
    - Custom regex highlighter extended from QSyntaxHighlighter \
    ![Regex Highlighter](/images/regexHighighter.gif)


## Notes
- There may be some irregular styling.  I attempted to use camel case and common c++ conventions (e.g. m_), however I am used to Unreal Engine styling convention. \
Due to time restraint may have made mistakes.
- ema to obj parser currently not working in this version (converted from python to c++), however the core logic is there to read.


## Contact
- Email: rabclip@4ozstudio.com