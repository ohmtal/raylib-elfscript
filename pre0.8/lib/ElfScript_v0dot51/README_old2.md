# ElfScript

While the source in TorqueScript folder also works, this is where i 
put in my latest changes and fixes. It's uses in Ohmflux/ElfTest and
raylib-elfscript.

- [X] FIX: assigment to a  defined FIELD is very slow!
    example in test.cs mode==3 
    
    OP_SAVEFIELD_STR
    => void SimObject::setDataField(StringTableEntry slotName, const char *array, const char *value) 
      =>  if(mFlags.test(ModStaticFields)) ....
    
    Added FastPath when array is 0;
      
      
## 2026-06-18 Attempt II
Copy from TorqueScript and start cleanup.

### [done] Milestone I: cleanup : check which sources are unused 

- [X] SimDataBlock
- [X] NetString/tagged strings 
- [X] sim is unused
- [X] ./util used stuff moved to core/util then removed 
- [X] core/util/zip

There is some stuff left in platform and maybe in core but it's ok for now. 


### Milestone II [open]: replace MountSystem / Virtual 

While it's basicly a good idea to have a mountsystem 
and virtual filesystem it's overpowered for loading a 
script or export doc/variables/objects. So I only need
to set a base directory, implement loading a test file
and replace the ugly expand filename ~/ ./ ^ logic. 
I guess dso is also loaded saved as text ... maybe i dont 
need dso anyway. 

NOTE: Not sure i want to remove this but i need to check why getMainDotCsDir is used and not getCurrentDir as BasePath 

- [X] removed log to file and buffer (only use consumers)
- [ ] FIXME: 
    - [ ] file platformFileIO.cpp
    - [ ] Platform::makeFullPathName
    - [ ] StringTableEntry getModNameFromPath(const char *path)
    - [ ] expandOldScriptFilename, expandToolScriptFilename in expandScriptFilename
    - [ ] Platform::getMainDotCsDir


- [ ] core/util/path
- [ ] core/volume
- [ ] core/virtualMountSystem
- [ ] core/resourceManager 
- [ ] core/resource
- [ ] platform/win|posix volume stuff

 modifing:
- [ ] console/console
- [ ] core/fileObject 
- [ ] console/scriptFilename << no longer needed then ??


