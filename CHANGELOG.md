# Change Log
This is the changelog for OutpostHD.

## [2.1.0] - 2015-10-31

First update to the OP2 SDK downloadable package in 10 years.

### Changed
- This README file has been updated to conform to Markup specifications.
- Visual Studio 2015 project file has been included.
- Directory structure has been updated it a bit with the intention that a mission developer can simply copy the entire directory, rename the project and start developing a new mission immediately.
- Some of the comments in the template files have been updated to conform to Doxygen formatting syntax.
- The comments have been cleaned up a bit to make it clear what's important to know and what is just interesting trivia about the code and Outpost 2 itself.
- Moved change information from README to CHANGELOG.

### Removed
- Removed old Visual C++ project files and workspaces.


## [2.0.0] - 2005-10-27

First release of the 2.0 versions of the OP2 SDK.

### Changed
- The Outpost2DLL.h has been split up into many different header files. To include the headers you would still use the same #include "../Outpost2DLL/Outpost2DLL.h" however.
- Most of the enum values have been updated. One major change is in the map_id's. The underscores and spelling errors have been removed, so for example: map_Nursury becomes mapNursery. You can disable this for the map_id's by using a #define CompatibleNames. This should revert to the old map_id's, but you may experience other problems. (It's best to go through and make your code compatible with the latest version).
- Many of the enum values have been prefixed, and some new enums have been added. Check the headers to see exactly what is different.
- We've tried to fill in most of the parameters for OP2 functions that we can. There are still quite a few we don't know about yet.
- Other additional updates to the Hooville project, and a new multiplayer template, which should be a lot easier to use.

