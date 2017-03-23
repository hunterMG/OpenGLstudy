# OpenGLstudy
Code and note for OpenGL study.
0. Steps of project creation:
  0. Create a empty Visual C++ win32 Console Application:
    Open VS2015,File -> New -> Project -> Visual C++ -> win32 Console Application -> OK.
  0. Add Nupengl support:
    Right click on the name of the project -> Manage Nuget Packages -> Browse -> type "Nupengl" -> intsall the 2 packages below.
  0. Add new source file(.cpp) in the "Source files" directory ,usually the same as the project name.Then you can write your code with it.
0. Hide the annoying console window:
	  Right click on the name of the project -> properties -> Linker -> Advanced -> modify the value of "Entry point" to "mainCRTStartup";
	  choose "System" from the left,modify "Subsystem" to "windows(/SUBSYSTEM:WINDOWS)".
	  Apply.
