*** Rising from the Ashes

A new Eden Starship Colony Game for Outpost 2 programmed by Vagabond from Jan to Mar of 2016.

Install Directions:
 * Place the Ashes.map, c_ashes.dll, & multitekNoLavaWalls.txt files in your root Outpost 2 install directory. 
 * Open Outpost 2 and search for the new scenario with the other colony games.
 * Good luck, and have fun!

*** Source Code

Rising from the Ashes was built using C++ in Visual Studio 2015. C++11 and the C++ Standard Library are both used. 
If you want to load the scenario into a different IDE, a C++11 compliant IDE is required. 
Your IDE will also need support for the windows API and the Outpost 2 SDK ver 2.1.

Post Build Events: 3 post build events are remarked out (rem command) to prevent them from copying 
files on another person's computer without their knowledge. Remove the rem from the 3 lines to
enable them.

If you need help troubleshooting the compiled scenario or the source code, use the OutpostUniverse forums.

** Bugs

 * TRIVIAL - If you destory the AI's Vehicle Factor and the AI's ConVec that builds new structures, 
   the Repair ConVec will not switch roles and rebuild the vehicle factory.

** Credits

  * SirBomber - For making great tutorials that without I probably wouldn't have been able to learn the SDK.
  * Hooman - For providing technical help, especially for re-creating the Plymouth Starship II colony game. 
    This provided a lot of insight on using the SDK. Also, for solving the victory conditions/Saving bug.

** Change Log

Version 1.0.6
 - Stop player from being able to build lava walls (Tech file update)
 - Move HFL initialization into DLLMain
 - Improve header include formatting
