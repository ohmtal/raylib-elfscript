//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// NOTE only parts implemented ....
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"


using namespace ElfResource;

//------------------------------------------------------------------------------------
// File system management functions
//------------------------------------------------------------------------------------

// RLAPI unsigned char *LoadFileData(const char *fileName, int *dataSize); // Load file data as byte array (read)
// RLAPI void UnloadFileData(unsigned char *data);                     // Unload file data allocated by LoadFileData()
// RLAPI bool SaveFileData(const char *fileName, const void *data, int dataSize); // Save data to file from byte array (write), returns true on success
// RLAPI bool ExportDataAsCode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
// RLAPI char *LoadFileText(const char *fileName);                     // Load text data from file (read), returns a '\0' terminated string
// RLAPI void UnloadFileText(char *text);                              // Unload file text data allocated by LoadFileText()
// RLAPI bool SaveFileText(const char *fileName, const char *text);    // Save text data to file (write), string must be '\0' terminated, returns true on success
// RLAPI char *LoadFileText(const char *fileName);                     // Load text data from file (read)
DefineEngineFunction( LoadFileText, const char*, (String fileName), , "Load text data from file and return it as a string") {
    char* fileText = LoadFileText(fileName.c_str());

    if (fileText == nullptr) {
        return "";
    }

    // Wir kopieren den Text in den flüchtigen Torque-Return-Buffer,
    // damit TorqueScript sicher damit arbeiten kann.
    U32 textLength = dStrlen(fileText) + 1;
    char* retBuffer = Con::getReturnBuffer(textLength);
    dStrcpy(retBuffer, fileText, textLength);

    // WICHTIG: Wir geben den von Raylib alloziierten Speicher SOFORT frei,
    // damit wir kein Speicherleck erzeugen!
    UnloadFileText(fileText);

    return retBuffer;
}

// RLAPI bool SaveFileText(const char *fileName, const char *text);    // Save text data to file (write)
DefineEngineFunction( SaveFileText, bool, (String fileName, String text), , "Save text data to a file, returns true on success") {
    // Da TorqueScript-Strings immer Null-terminiert sind, können wir sie direkt übergeben
    return SaveFileText(fileName.c_str(), text.c_str());
}

//------------------------------------------------------------------------------------
// // File access custom callbacks
// // WARNING: Callbacks setup is intended for advanced users
// RLAPI void SetLoadFileDataCallback(LoadFileDataCallback callback);  // Set custom file binary data loader
// RLAPI void SetSaveFileDataCallback(SaveFileDataCallback callback);  // Set custom file binary data saver
// RLAPI void SetLoadFileTextCallback(LoadFileTextCallback callback);  // Set custom file text data loader
// RLAPI void SetSaveFileTextCallback(SaveFileTextCallback callback);  // Set custom file text data saver
//------------------------------------------------------------------------------------
// RLAPI bool FileExists(const char *fileName);                        // Check if file exists
DefineEngineFunction( FileExists, bool, (String fileName), , "Check if file exists") {
    return FileExists(fileName.c_str());
}

// RLAPI bool DirectoryExists(const char *dirPath);                    // Check if a directory path exists
DefineEngineFunction( DirectoryExists, bool, (String dirPath), , "Check if a directory path exists") {
    return DirectoryExists(dirPath.c_str());
}

// RLAPI int FileTextReplace(const char *fileName, const char *search, const char *replacement);
DefineEngineFunction( FileTextReplace, int, (String fileName, String search, String replacement), , "Replace text in an existing file. Returns count of replacements.") {
    return FileTextReplace(fileName.c_str(), search.c_str(), replacement.c_str());
}

// RLAPI int FileTextFindIndex(const char *fileName, const char *search); // Find text in existing file
DefineEngineFunction( FileTextFindIndex, int, (String fileName, String search), , "Find text in existing file, returns character index or -1 if not found") {
    return FileTextFindIndex(fileName.c_str(), search.c_str());
}
// -----------------------------------------------------------------------------
// RLAPI int FileRename(const char *fileName, const char *fileRename); // Rename file
DefineEngineFunction( FileRename, bool, (String fileName, String fileRename), , "Rename a file. Returns true on success.") {
    return FileRename(fileName.c_str(), fileRename.c_str()) == 0; // 0 bedeutet bei OS-Operationen oft Erfolg
}

// RLAPI int FileRemove(const char *fileName);                         // Remove file
DefineEngineFunction( FileRemove, bool, (String fileName), , "Delete a file. Returns true on success.") {
    return FileRemove(fileName.c_str()) == 0;
}

// RLAPI int FileCopy(const char *srcPath, const char *dstPath);       // Copy file
DefineEngineFunction( FileCopy, bool, (String srcPath, String dstPath), , "Copy a file from one path to another. Returns true on success.") {
    return FileCopy(srcPath.c_str(), dstPath.c_str()) == 0;
}

// RLAPI int FileMove(const char *srcPath, const char *dstPath);       // Move file
DefineEngineFunction( FileMove, bool, (String srcPath, String dstPath), , "Move a file from one directory to another. Returns true on success.") {
    return FileMove(srcPath.c_str(), dstPath.c_str()) == 0;
}
// -----------------------------------------------------------------------------
// Helper, um statische Raylib-Strings sicher an TorqueScript zu übergeben
inline const char* CopyToTorqueBuffer(const char* staticStr) {
    if (staticStr == nullptr) return "";
    U32 len = dStrlen(staticStr) + 1;
    char* retBuffer = Con::getReturnBuffer(len);
    dStrcpy(retBuffer, staticStr, len);
    return retBuffer;
}

// RLAPI int GetFileLength(const char *fileName);                      // Get file length in bytes
DefineEngineFunction( GetFileLength, int, (String fileName), , "Get file length in bytes") {
    return GetFileLength(fileName.c_str());
}

// RLAPI const char *GetFileExtension(const char *fileName);           // Get extension (includes dot)
DefineEngineFunction( GetFileExtension, const char*, (String fileName), , "Get extension for a filename string (includes dot: '.png')") {
    return CopyToTorqueBuffer(GetFileExtension(fileName.c_str()));
}

// RLAPI const char *GetFileName(const char *filePath);                // Get filename
DefineEngineFunction( GetFileName, const char*, (String filePath), , "Get filename for a path string") {
    return CopyToTorqueBuffer(GetFileName(filePath.c_str()));
}

// RLAPI const char *GetFileNameWithoutExt(const char *filePath);      // Get filename without extension
DefineEngineFunction( GetFileNameWithoutExt, const char*, (String filePath), , "Get filename string without extension") {
    return CopyToTorqueBuffer(GetFileNameWithoutExt(filePath.c_str()));
}

// -----------------------------------------------------------------------------
// RLAPI int MakeDirectory(const char *dirPath);                       // Create directories
DefineEngineFunction( MakeDirectory, bool, (String dirPath), , "Create directories (including full path requested), returns true on success") {
    return MakeDirectory(dirPath.c_str()) == 0;
}

// RLAPI unsigned int GetDirectoryFileCount(const char *dirPath);      // Get file count
DefineEngineFunction( GetDirectoryFileCount, int, (String dirPath), , "Get the total file count in a directory") {
    return (int)GetDirectoryFileCount(dirPath.c_str());
}

// RLAPI unsigned int GetDirectoryFileCountEx(const char *basePath, const char *filter, bool scanSubdirs);
DefineEngineFunction( GetDirectoryFileCountEx, int, (String basePath, String filter, bool scanSubdirs), , "Get file count with extension filtering and recursive directory scan. Use 'DIR' in filter to include directories.") {
    return (int)GetDirectoryFileCountEx(basePath.c_str(), filter.c_str(), scanSubdirs);
}

// -----------------------------------------------------------------------------

// RLAPI int FileRename(const char *fileName, const char *fileRename); // Rename file (if exists)
// RLAPI int FileRemove(const char *fileName);                         // Remove file (if exists)
// RLAPI int FileCopy(const char *srcPath, const char *dstPath);       // Copy file from one path to another, dstPath created if it doesn't exist
// RLAPI int FileMove(const char *srcPath, const char *dstPath);       // Move file from one directory to another, dstPath created if it doesn't exist
// RLAPI int FileTextReplace(const char *fileName, const char *search, const char *replacement); // Replace text in an existing file
// RLAPI int FileTextFindIndex(const char *fileName, const char *search); // Find text in existing file
// RLAPI bool FileExists(const char *fileName);                        // Check if file exists
// RLAPI bool DirectoryExists(const char *dirPath);                    // Check if a directory path exists
// RLAPI bool IsFileExtension(const char *fileName, const char *ext);  // Check file extension (recommended include point: .png, .wav)
// RLAPI int GetFileLength(const char *fileName);                      // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
// RLAPI long GetFileModTime(const char *fileName);                    // Get file modification time (last write time)
// RLAPI const char *GetFileExtension(const char *fileName);           // Get pointer to extension for a filename string (includes dot: '.png')
// RLAPI const char *GetFileName(const char *filePath);                // Get pointer to filename for a path string
// RLAPI const char *GetFileNameWithoutExt(const char *filePath);      // Get filename string without extension (uses static string)
// RLAPI const char *GetDirectoryPath(const char *filePath);           // Get full path for a given fileName with path (uses static string)
// RLAPI const char *GetPrevDirectoryPath(const char *dirPath);        // Get previous directory path for a given path (uses static string)
// RLAPI const char *GetWorkingDirectory(void);                        // Get current working directory (uses static string)
// RLAPI const char *GetApplicationDirectory(void);                    // Get the directory of the running application (uses static string)
// RLAPI int MakeDirectory(const char *dirPath);                       // Create directories (including full path requested), returns 0 on success
// RLAPI bool ChangeDirectory(const char *dirPath);                    // Change working directory, return true on success
// RLAPI bool IsPathFile(const char *path);                            // Check if a given path is a file or a directory
// RLAPI bool IsFileNameValid(const char *fileName);                   // Check if fileName is valid for the platform/OS
// RLAPI FilePathList LoadDirectoryFiles(const char *dirPath);         // Load directory filepaths, files and directories, no subdirs scan
// RLAPI FilePathList LoadDirectoryFilesEx(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and subdir scan; some filters available: `*.*`,`FILES*`,`DIRS*`
// RLAPI void UnloadDirectoryFiles(FilePathList files);                // Unload filepaths
// RLAPI bool IsFileDropped(void);                                     // Check if a file has been dropped into window
// RLAPI FilePathList LoadDroppedFiles(void);                          // Load dropped filepaths
// RLAPI void UnloadDroppedFiles(FilePathList files);                  // Unload dropped filepaths
// RLAPI unsigned int GetDirectoryFileCount(const char *dirPath);      // Get the file count in a directory
// RLAPI unsigned int GetDirectoryFileCountEx(const char *basePath, const char *filter, bool scanSubdirs); // Get the file count in a directory with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result
//------------------------------------------------------------------------------------
// Compression/Encoding functionality
//------------------------------------------------------------------------------------
// RLAPI unsigned char *CompressData(const unsigned char *data, int dataSize, int *compDataSize);        // Compress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI unsigned char *DecompressData(const unsigned char *compData, int compDataSize, int *dataSize);  // Decompress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI char *EncodeDataBase64(const unsigned char *data, int dataSize, int *outputSize);               // Encode data to Base64 string (includes NULL terminator), memory must be MemFree()
// RLAPI unsigned char *DecodeDataBase64(const char *text, int *outputSize);                             // Decode Base64 string (expected NULL terminated), memory must be MemFree()
// RLAPI unsigned int ComputeCRC32(const unsigned char *data, int dataSize); // Compute CRC32 hash code
// RLAPI unsigned int *ComputeMD5(const unsigned char *data, int dataSize);  // Compute MD5 hash code, returns static int[4] (16 bytes)
// RLAPI unsigned int *ComputeSHA1(const unsigned char *data, int dataSize); // Compute SHA1 hash code, returns static int[5] (20 bytes)
// RLAPI unsigned int *ComputeSHA256(const unsigned char *data, int dataSize); // Compute SHA256 hash code, returns static int[8] (32 bytes)

//------------------------------------------------------------------------------------
// Automation events functionality
//------------------------------------------------------------------------------------
// RLAPI AutomationEventList LoadAutomationEventList(const char *fileName); // Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
// RLAPI void UnloadAutomationEventList(AutomationEventList list);   // Unload automation events list from file
// RLAPI bool ExportAutomationEventList(AutomationEventList list, const char *fileName); // Export automation events list as text file
// RLAPI void SetAutomationEventList(AutomationEventList *list);     // Set automation event list to record to
// RLAPI void SetAutomationEventBaseFrame(int frame);                // Set automation event internal base frame to start recording
// RLAPI void StartAutomationEventRecording(void);                   // Start recording automation events (AutomationEventList must be set)
// RLAPI void StopAutomationEventRecording(void);                    // Stop recording automation events
// RLAPI void PlayAutomationEvent(AutomationEvent event);            // Play a recorded automation event
