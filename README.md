#Outpost 2 Mission SDK version 2.1

Welcome to the Outpost 2 Mission Software Development Kit (SDK), version 2.1! This SDK will get you started making new missions for Outpost 2.

##Changes

See the CHANGELOG.md file for all changes.

##Requirements

To use this SDK you must have the following:

- Current version of Outpost 2. At the time of this writing, v1.3.5.
- Microsoft Visual Studio 2015 with C++ language support installed. The Community Edition is free and can be downloaded from here: https://www.microsoft.com/en-us/download/details.aspx?id=48145
- Patience. Outpost 2 mission development can be a tedious process, especially if you're new to programming.

You don't necessarily have to know C++, but it's STRONGLY recommended. However prior programming/scripting experience is almost required. (You need to be able to understand basic computer logic like if then statements, for loops, etc)

##IRC

We highly recommend downloading an IRC client and joining us on channel #Outpost2 on the Quakenet IRC network.

##Getting Started

Have a look at the Multiplayer Hooville\ project and compile it. In Multiplayer Hooville\ReleaseMinSize\ there will be an OP2Script.dll. This is the compiled mission. To test it in OP2, place it in your OP2 folder. (You'll have to rename missions for them to show up in the pick lists, by prefixing the DLL name with a code.

### Mission Prefix Codes

Mission DLL's are prefixed with one of the following codes:

a - AutoDemo
c - Colony Game
e - Eden Campaign
mfx - Multiplayer Space Race (where x is the number of players)
mlx - Multiplayer Last One
mmx - Multiplayer Midas
mrx - Multiplayer Resource Race
mux - Multiplayer Land Rush

Your DLL name (including the prefix, but not including .dll on the end) needs to be 7 characters or less. If it's any longer OP2 will display multiple entries for that DLL name. (Bug =P)

##Using Maps and Techtrees

To make new terrain maps for your level, you need the OP2Mapper. This is available at our website. To make your new mission use your own map, edit the MapName string to match the name of your map. The map name has a maximum of 8.3 characters long. This map file must be present in the OP2 folder alongside the mission, otherwise mission initialization will fail.

You can use any text editor to make tech trees, since they are in a text format. The format is pretty easy to understand from looking at default techtrees like MULTITEK.TXT. (inside the sheets.vol) To change the techtree used, edit the TechtreeName string. Also, it has a maximum of 8.3 characters, and must be present alongside the mission DLL for the mission load to succeed. Note on Tech Levels: The tech level is the first two digits of the tech topic ID. (Example: for ID 11999, which is Tiger Speed Modification, the tech level is 11).

##Releasing Missions

Outpost 2 does not have an automatic map transfer feature like other games. (The game creators never intended for the end-user to create missions).
So, the only reliable way to make sure someone has your map is through major updates, released by us.
If you have made a mission which you feel is good enough to be released, send it, and all supporting files (maps/techtrees that are not part of the game) to us on IRC (read Getting Help below to learn where to go).
When we receive your mission, we will review it doing checks like in the checklist below:
- Is the mission complete and playable, and been tested on? (Bug-free)
- Has the programmer followed proper coding standards? (mission named properly, proper file names and formats used?)
- Is the DLL free of any malicious or harmful code? (Virus free)
- If it uses it's own map or techtree, is the map/techtree presentable? (In other words, the map isn't sloppy, and looks nice)
- (Multiplayer) Is gameplay fair and balanced? (In other words, one player doesn't have an advantage over the others, unless the nature of the mission dictates that)
- And most importantly, is the mission FUN?

###A few other notes on Submissions

- Mission DLL's should not use any external libraries such as MFC or .NET. (C# or another language that relies on the .NET Framework is not acceptable).
- Also, a DLL should not rely on any OS features that may be present in one version of the OS but not another (e.g. do not use libraries like uxtheme.dll unless the DLL is able to be backwards compatible with other versions of windows)
- You shouldn't use any GUI that obstructs the game either, except in very special circumstances. (e.g. if the UI is used to make a choice, say in a single player game. You'd probably want it to look OP2-ish)
- DLL's should not make any direct memory patches to the game unless we have approved it. (For the sake of compatibility)
Also: If you are caught distributing a mission to people (e.g. for beta) that contains malicious code or anything else that could cause intentional harm, you will be immediately banned.

If your mission meets these requirements, then we might include it in the update. (All users will be required to get the update, so your mission is guaranteed to be distributed either as part of the main update, or part of an option package).

##Proposing Additions to the SDK

If you have written code or done other things like filling in or changing enums, structs, or parameters, please submit it to us FIRST so we can put it in the SDK.
Please do NOT give it to others for them to add to their header files. If people do that, after a while one person's SDK copy might be outdated or incompatible with any changes.
Consider the fresh copy of the SDK you have here the "gold standard" - it is the most up-to-date and accurate.

If you have written useful code for missions (like the functions in the OP2Helper\ folder) submit the source code for them to us. We may choose to leave them as source, or may compile them into a static library.
Same goes for mission templates. It would be great if we had some good multiplayer templates (besides Last One Standing) as well as single player templates.

##Getting Help

If you get stuck or have problems regarding the SDK or other things involved in making missions, come to #Outpost2.coding on Quakenet.
Please note we'll probably only answer SDK/mission/OP2 related questions. (In other words, we are not here to teach you the basics of C++ programming. You can learn C++ from books and tutorials online).
Also, you can converse with fellow coders who make missions like you are learning to. They will have a good bit of expertise or other helpful knowledge (on some subjects, they know more than the "officials" do! =)

Above all, good luck, and have fun writing new missions. =P

##Disclaimer

We offer this SDK as-is, with no guarantee of fitness for a particular task with this SDK. By extracting the contents of the SDK and using them, you agree to not hold us responsible for any incidental or consequential damages to persons or property when using this SDK. We cannot be held responsible for any bugs or problems with this SDK that may cause your computer to crash or lose data.

If you do not agree with this policy, you must destroy all parts to the SDK and any files created with it at once.
