# BISMILLAAHIRRAHMAANIRRAHEEM - In The Name of ALLAAH, The Most Beneficent, The Most Merciful

## WindowQuotePro

A Windows OS based CPQ application for generating quotes for window panes. [More information](https://www.MuhammadBilalKhan.com/work/WindowQuotePro)

Password for the demonstration videos `zip` file is: *cpq*

`Note:` Quite exhausted at this stage to add *doxygen* comments.

### Source release

This directory is a `git` repository.

### Build source

#### Requirements and dependencies

Tested with:

* OS: *Windows 7, Windows 10*
* CMake 3.28.3
* Microsoft Visual Studio 2022 Community Edition (*Desktop Software Development* enabled)
* wxWidgets 3.2.4
* SQLite 3

#### Build instructions

* Install the `wxWidgets` *headers* and *development files* from wxWidgets website. Set the path to the directory in root CMakeLists.txt:

```
set(wxWidgets_path_base "C:/wxWidgets")
```

The directory structure on development system looks like:

```
C:\
|- wxWidgets
   |- build
      |- msw
         |- ...
   |- include
      |- msvc
         |- ...
      |- wx
         |- ...
   |- lib
      |- vc14x_x64_dll
         |- ...
   |- lib
   |- wxwidgets.props
```

A copy of the said directory is available [here] (https://www.MuhammadBilalKhan.com/work/WindowQuotePro).
* Open the project in Microsoft Visual Studio 2022 Community Edition. Make sure the build is set to *Release*. Build.
* The application executable `WindowQuotePro` is built in subdirectory `out`.

InShaaALLAAH, the application would run as expected.

### Source files

* *WindowQuoteProApp*: Application (wxWidgets)
* *WindowQuoteProMain*: Main window frame (wxWidgets)
* *DataStore*: Central class to store application data etc
* *Page*: UI layout template helper class
* *QuotesPage*: Quotes UI based on `Page`
* *DialogAbout*: About dialog
* *DialogHelp*: Help dialog

### Additional

Source code is provided for the purpose of evaluation as per the shared document.
