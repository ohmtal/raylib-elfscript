# raylib-elfscript (WiP) 
 
Raylib binding of Elf(Torque)Script.

##Setup: 

I usually have the TorqueScript Source in "/opt/TorqueScript" which is set as default in CMake. 
But you can also put it somewhere else and need to add the path to cmake like:

    git pull https://github.com/ohmtal/TorqueScript.git

and then

    cmake -S . -B build -DELFSCRIPT_PATH="/whereIHaveMySource/TorqueScript"
    cmake --build build
    ./raylib-elfscript

    
