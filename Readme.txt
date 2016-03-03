*** Rising from the Ashes

A new Eden Starship Colony Game for Outpost 2 programmed by Vagabond in Jan/Feb of 2016.

Install Directions:
 * Place the Ashes.map and c_ashes.dll file in your root Outpost 2 install directory. 
 * Open Outpost 2 and search for the new scenario with the other colony games.
 * Good luck, and have fun!

*** Source Code

Rising from the Ashes was built using C++ in Visual Studio 2015. C++11 and the C++ Standard Library are both used. 
If you want to load the scenario into a different IDE, a C++11 compliant IDE is required. 
Your IDE will also need support for the windows API and the Outpost 2 SDK ver 2.1.

Post Build Events: 3 post build events are remarked out (rem) to prevent them from copying 
files on another person's computer without their knowledge. Remove the rem from the 3 lines to
enable them.

If you need help troubleshooting the compiled scenario or the source code, use the OutpostUniverse forums.

** Bugs

 * If you load a saved version of the game and check the mission objectives, the game will crash.

 * If you launch the evacuation module you actually lose the scenario instead of winning.

 * If you destory the AI's Vehicle Factor and the AI's ConVec that builds new structures, 
   the Repair ConVec will not switch roles and rebuild the vehicle factory.

** Credits

  * SirBomber - For making great tutorials that without I probably wouldn't have been able to learn the SDK.
  * Hooman - For providing technical help, especially for re-creating the Plymouth Starship II colony game. 
    This provided a lot of insight on using the SDK.