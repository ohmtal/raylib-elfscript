//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Copyright (c) 2026 Thomas Hühn (XXTH)
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// 2026-06-22 XXTH added:
//      - cursor left / right for edit line
//      - shift tab for backward complete
//      - ctrl-a for beginning and ctrl-e for end
//-----------------------------------------------------------------------------
#include "platform/platform.h"
#include "core/util/rawData.h"
#include "core/strings/stringFunctions.h"
#include "core/util/journal/process.h"

#include <signal.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

#include "console/engineAPI.h"
#include "POSIXStdConsole.h"

StdConsole *stdConsole = NULL;

DefineEngineFunction(enableWinConsole, void, (bool _enable),, "enableWinConsole(bool);")
{
   if (stdConsole)
   {
       stdConsole->enable(_enable);
       stdConsole->enableInput(_enable);
   }
}

void StdConsole::create()
{
   if (stdConsole == NULL)
      stdConsole = new StdConsole();
}

void StdConsole::destroy()
{
   if (stdConsole && stdConsole->isEnabled())
      stdConsole->enable(false);

   delete stdConsole;
   stdConsole = NULL;
}

static void signalHandler(int sigtype)
{
   if (sigtype == SIGCONT && stdConsole != NULL)
      stdConsole->resetTerminal();
}

void StdConsole::resetTerminal()
{
   if (stdConsoleEnabled)
   {
      /* setup the proper terminal modes */
      struct termios termModes;
      tcgetattr(stdIn, &termModes);
      termModes.c_lflag &= ~ICANON; // enable non-canonical mode
      termModes.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHOKE);
      termModes.c_cc[VMIN] = 0;
      termModes.c_cc[VTIME] = 5;
      tcsetattr(stdIn, TCSAFLUSH, &termModes);
   }
}

void StdConsole::enable(bool enabled)
{
   if (enabled && !stdConsoleEnabled)
   {
      stdConsoleEnabled = true;

      // install signal handler for sigcont
      signal(SIGCONT, &signalHandler);
      
      // save the terminal state
      if (originalTermState == NULL)
         originalTermState = new termios;

      tcgetattr(stdIn, originalTermState);
      
      // put the terminal into our preferred mode
      resetTerminal();
      
      printf("%s", Con::getVariable("Con::Prompt"));
     
   }
   else if (!enabled && stdConsoleEnabled)
   {
      stdConsoleEnabled = false;

      // uninstall signal handler
      signal(SIGCONT, SIG_DFL);

      // reset the original terminal state
      if (originalTermState != NULL)
         tcsetattr(stdIn, TCSANOW, originalTermState);
   }
}

void StdConsole::enableInput( bool enabled )
{
    stdConsoleInputEnabled = enabled;
}

bool StdConsole::isEnabled()
{
   if ( stdConsole )
      return stdConsole->stdConsoleEnabled;

   return false;
}

static void stdConsoleConsumer(/*ConsoleLogEntry::Level*/ U32, const char *line)
{
   stdConsole->processConsoleLine(line);
}

StdConsole::StdConsole()
{
   for (S32 iIndex = 0; iIndex < MAX_CMDS; iIndex ++)
      rgCmds[iIndex][0] = '\0';

   stdOut = dup(1);
   stdIn  = dup(0);
   stdErr = dup(2);

   // Ensure in buffer is null terminated after allocation
   inbuf[0] = 0x00;

   iCmdIndex = 0;
   stdConsoleEnabled = false;
   stdConsoleInputEnabled = false;
   Con::addConsumer(stdConsoleConsumer);
   inpos = 0;
   lineOutput = false;
   inBackground = false;
   originalTermState = NULL;
   
   Process::notify(this, &StdConsole::process, PROCESS_LAST_ORDER);
}

StdConsole::~StdConsole()
{
   Con::removeConsumer(stdConsoleConsumer);

   if (stdConsoleEnabled)
      enable(false);

   if (originalTermState != NULL)
   {
      delete originalTermState;
      originalTermState = NULL;
   }
}

void StdConsole::printf(const char *s, ...)
{
   // Get the line into a buffer.
   static const int BufSize = 4096;
   static char buffer[BufSize];
   va_list args;
   va_start(args, s);
   vsnprintf(buffer, BufSize, s, args);
   va_end(args);
   // Replace tabs with carats, like the "real" console does.
   char *pos = buffer;
   while (*pos) {
      if (*pos == '\t') {
         *pos = '^';
      }
      pos++;
   }
   // Axe the color characters.
   Con::stripColorChars(buffer);
   // Print it.
   write(stdOut, buffer, strlen(buffer));
   fflush(stdout);
}

void StdConsole::processConsoleLine(const char *consoleLine)
{

   if(stdConsoleEnabled)
   {
      if(lineOutput)
         printf("%s\n", consoleLine);
      else
      {
          // Clear current line before outputting the console line. This prevents prompt text from overflowing onto normal output.
          printf("%c[2K", 27);
          printf("%c%s\n%s%s", '\r', consoleLine, Con::getVariable("Con::Prompt"), inbuf);
      }
   }
}

void StdConsole::process()
{
   if(stdConsoleEnabled)
   {
      //U16 key;
      char typedData[64];  // damn, if you can type this fast... :-D

      //XXTH FIXME ?!
      /*
      if (UUtils->inBackground())
         // we don't have the terminal
         inBackground = true;
      else
       <<< XXTH */
      {
         // if we were in the background, reset the terminal
         if (inBackground)
            resetTerminal();
         inBackground = false;
      }   

      // see if stdIn has any input waiting
      // mojo for select call
      fd_set rfds;
      struct timeval tv;

      FD_ZERO(&rfds);
      FD_SET(stdIn, &rfds);
      // don't wait at all in select
      tv.tv_sec = 0;
      tv.tv_usec = 0;

      int numEvents = select(stdIn+1, &rfds, NULL, NULL, &tv);
      if (numEvents <= 0)
         // no data available
         return;

      numEvents = read(stdIn, typedData, 64);     
      if (numEvents == -1) 
         return;

      // TODO LINUX, when debug in qtCreator some times we get false console inputs.
      if( !stdConsoleInputEnabled )
         return;

//-------------------------------------------------------------

      typedData[numEvents] = '\0';
      if (numEvents > 0)
      {
        char outbuf[1024]; // Large buffer to handle escape sequences and redraws safely
        S32 outpos = 0;

        // REMOVED: Do NOT null-terminate at 'inpos' here! It truncates the buffer when using Left Arrow.

        for (int i = 0; i < numEvents; i++)
        {
         switch(typedData[i])
         {
            case 8:
            case 127:
            /* backspace */
               if (inpos > 0)
               {
                  S32 len = (S32)strlen(inbuf);
                  // Shift characters to the left to delete the character in memory
                  for (S32 j = inpos - 1; j < len; j++)
                     inbuf[j] = inbuf[j + 1];

                  inpos--;
                  len--;

                  // Redraw terminal line
                  outbuf[outpos++] = '\b';
                  for (S32 j = inpos; j < len; j++)
                     outbuf[outpos++] = inbuf[j];
                  outbuf[outpos++] = ' ';

                  for (S32 j = len + 1; j > inpos; j--)
                     outbuf[outpos++] = '\b';
               }
               break;
            case 1:
                /* Ctrl+A - Move cursor to the beginning of the line */
                {
                    // Move the terminal cursor back to the very start of the prompt
                    for (S32 j = 0; j < inpos; j++)
                        outbuf[outpos++] = '\b';

                    // Set logical position to the start
                    inpos = 0;
                }
                break;

            case 5:
                /* Ctrl+E - Move cursor to the end of the line */
                {
                    S32 len = (S32)strlen(inbuf);

                    // Move the terminal cursor forward until it reaches the end of the string
                    for (S32 j = inpos; j < len; j++)
                    {
                        outbuf[outpos++] = '\033';
                        outbuf[outpos++] = '[';
                        outbuf[outpos++] = 'C';
                    }

                    // Set logical position to the very end
                    inpos = len;
                }
                break;


            case '\t':
                        {
                           // Erase the current line visually
                           U32 j;
                           for (j = 0; j < (U32)inpos; j++) {
                              outbuf[outpos++] = '\b';
                              outbuf[outpos++] = ' ';
                              outbuf[outpos++] = '\b';
                           }
                           U32 maxlen = 512 - (inpos * 3);
                           inpos = Con::tabComplete(inbuf, inpos, maxlen, true);
                           for (j = 0; j < (U32)inpos; j++) {
                              outbuf[outpos++] = inbuf[j];
                           }
                           inbuf[inpos] = '\0';
                        }
                        break;

            case '\n':
            case '\r':
            /* new line */
                  outbuf[outpos++] = '\n';

                  {
                     S32 len = (S32)strlen(inbuf);
                     // Submit the WHOLE line, do not cut off at cursor position
                     inbuf[len] = '\0';
                     inpos = len;
                  }

                  outbuf[outpos] = 0;
                  printf("%s", outbuf);

                  {
                     RawData rd;
                     rd.size = inpos + 1;
                     rd.data = (S8*) inbuf;
                     Con::smConsoleInput.trigger(rd);
                  }

                  if (iCmdIndex >= MAX_CMDS)
                      iCmdIndex %= MAX_CMDS;

                  strcpy(rgCmds[iCmdIndex ++], inbuf);

                  printf("%s", Con::getVariable("Con::Prompt"));
                  inpos = outpos = 0;
                  inbuf[0] = 0x00;
                  break;

            case 27:
               if (i + 1 < numEvents && (typedData[i+1] == 91 || typedData[i+1] == 79))
               {
                  i += 2;
                  switch(typedData[i])
                  {
                      case 'Z':
                          /* Shift+TAB - Backward Tab Completion */
                          {
                              // 1. Erase the current line visually
                              U32 j;
                              for (j = 0; j < (U32)inpos; j++) {
                                  outbuf[outpos++] = '\b';
                                  outbuf[outpos++] = ' ';
                                  outbuf[outpos++] = '\b';
                              }

                              // 2. Call tabComplete with forwardTab set to FALSE
                              U32 maxlen = 512 - (inpos * 3);
                              inpos = Con::tabComplete(inbuf, inpos, maxlen, false); // <-- FALSE here

                              // 3. Redraw the line with the backward completion result
                              for (j = 0; j < (U32)inpos; j++) {
                                  outbuf[outpos++] = inbuf[j];
                              }
                              inbuf[inpos] = '\0';
                          }
                          break;

                     case 'A':
                        /* up arrow */
                        if ((-- iCmdIndex) < 0)
                           iCmdIndex = MAX_CMDS - 1;

                        if (rgCmds[iCmdIndex][0] != '\0')
                        {
                           S32 len = (S32)strlen(inbuf);
                           for (S32 j = 0; j < inpos; j++) outbuf[outpos++] = '\b';
                           for (S32 j = 0; j < len; j++) outbuf[outpos++] = ' ';
                           for (S32 j = 0; j < len; j++) outbuf[outpos++] = '\b';

                           for (inpos = 0; inpos < (S32)strlen(rgCmds[iCmdIndex]); inpos++, outpos++)
                           {
                              outbuf[outpos] = rgCmds[iCmdIndex][inpos];
                              inbuf [inpos ] = rgCmds[iCmdIndex][inpos];
                           }
                           inbuf[inpos] = '\0';
                        }
                        else if ((++ iCmdIndex) >= MAX_CMDS)
                        {
                           iCmdIndex = 0;
                        }
                        break;

                     case 'B':
                        /* down arrow */
                        if (rgCmds[iCmdIndex][0] != '\0' && (++ iCmdIndex) >= MAX_CMDS)
                           iCmdIndex = 0;

                        {
                           S32 len = (S32)strlen(inbuf);
                           for (S32 j = 0; j < inpos; j++) outbuf[outpos++] = '\b';
                           for (S32 j = 0; j < len; j++) outbuf[outpos++] = ' ';
                           for (S32 j = 0; j < len; j++) outbuf[outpos++] = '\b';
                        }

                        for (inpos = 0; inpos < (S32)strlen(rgCmds[iCmdIndex]); inpos++, outpos++)
                        {
                           outbuf[outpos] = rgCmds[iCmdIndex][inpos];
                           inbuf [inpos ] = rgCmds[iCmdIndex][inpos];
                        }
                        inbuf[inpos] = '\0';
                        break;

                     case 'C':
                         /* right arrow */
                         // Works perfectly now because strlen(inbuf) is no longer truncated
                         if (inpos < (S32)strlen(inbuf))
                         {
                             outbuf[outpos++] = '\033';
                             outbuf[outpos++] = '[';
                             outbuf[outpos++] = 'C';
                             inpos++;
                         }
                         break;

                     case 'D':
                         /* left arrow */
                         if (inpos > 0)
                         {
                             outbuf[outpos++] = '\033';
                             outbuf[outpos++] = '[';
                             outbuf[outpos++] = 'D';
                             inpos--;
                         }
                         break;
                  }
                  break;
               } else {
                  goto default_handling;
               }
               break;

            default:
            default_handling:
               {
                  S32 len = (S32)strlen(inbuf);
                  if (len < 510)
                  {
                     // Shift characters to the right to make space for insertion
                     for (S32 j = len; j >= inpos; j--)
                        inbuf[j + 1] = inbuf[j];

                     // Insert the character
                     inbuf[inpos] = typedData[i];
                     len++;
                     inbuf[len] = '\0'; // Strictly maintain string end at the true dynamic length

                     // Redraw the line from the insertion point onwards
                     for (S32 j = inpos; j < len; j++)
                        outbuf[outpos++] = inbuf[j];

                     inpos++;

                     // Move terminal cursor back to the correct position
                     for (S32 j = len; j > inpos; j--)
                        outbuf[outpos++] = '\b';
                  }
               }
               break;
         }
        }
        if (outpos)
        {
           outbuf[outpos] = 0;
           printf("%s", outbuf);
        }
      }

//-------------------------------------------------------------
//       typedData[numEvents] = '\0';
//       if (numEvents > 0)
//       {
//         char outbuf[512];
//         S32 outpos = 0;
//
//         for (int i = 0; i < numEvents; i++)
//         {
//          switch(typedData[i])
//          {
//             case 8:
//             case 127:
//             /* backspace */
//                if (inpos > 0)
//                {
//                   outbuf[outpos++] = '\b';
//                   outbuf[outpos++] = ' ';
//                   outbuf[outpos++] = '\b';
//                   inpos--;
//                }
//                break;
//
//             // XXX Don't know if we can detect shift-TAB.  So, only handling
//             // TAB for now.
//
//             case '\t':
//                         // In the output buffer, we're going to have to erase the current line (in case
//                         // we're cycling through various completions) and write out the whole input
//                         // buffer, so (inpos * 3) + complen <= 512.  Should be OK.  The input buffer is
//                         // also 512 chars long so that constraint will also be fine for the input buffer.
//                         {
//                            // Erase the current line.
//                            U32 i;
//                            for (i = 0; i < inpos; i++) {
//                               outbuf[outpos++] = '\b';
//                               outbuf[outpos++] = ' ';
//                               outbuf[outpos++] = '\b';
//                            }
//                            // Modify the input buffer with the completion.
//                            U32 maxlen = 512 - (inpos * 3);
//                            inpos = Con::tabComplete(inbuf, inpos, maxlen, true);
//                            // Copy the input buffer to the output.
//                            for (i = 0; i < inpos; i++) {
//                               outbuf[outpos++] = inbuf[i];
//                            }
//                         }
//                         break;
//
//             case '\n':
//             case '\r':
//             /* new line */
//                   outbuf[outpos++] = '\n';
//
//                   inbuf[inpos] = 0;
//                   outbuf[outpos] = 0;
//                   printf("%s", outbuf);
//
//                   S32 eventSize;
//                   eventSize = 1;
//
//                   {
//                      RawData rd;
//                      rd.size = inpos + 1;
//                      rd.data = (S8*) inbuf;
//
//                      Con::smConsoleInput.trigger(rd);
//                   }
//
//                   // If we've gone off the end of our array, wrap
//                   // back to the beginning
//                   if (iCmdIndex >= MAX_CMDS)
//                       iCmdIndex %= MAX_CMDS;
//
//                   // Put the new command into the array
//                   strcpy(rgCmds[iCmdIndex ++], inbuf);
//
//                   printf("%s", Con::getVariable("Con::Prompt"));
//                   inpos = outpos = 0;
//                   inbuf[0] = 0x00; // Ensure inbuf is NULL terminated after sending out command
//                   break;
//             case 27:
//                // JMQTODO: are these magic numbers keyboard map specific?
//                if (typedData[i+1] == 91 || typedData[i+1] == 79)
//                {
//                   i += 2;
//                   // an arrow key was pressed.
//                   switch(typedData[i])
//                   {
//                      case 'A':
//                         /* up arrow */
//                         // Go to the previous command in the cyclic array
//                         if ((-- iCmdIndex) < 0)
//                            iCmdIndex = MAX_CMDS - 1;
//
//                         // If this command isn't empty ...
//                         if (rgCmds[iCmdIndex][0] != '\0')
//                         {
//                            // Obliterate current displayed text
//                            for (S32 i = outpos = 0; i < inpos; i ++)
//                            {
//                               outbuf[outpos++] = '\b';
//                               outbuf[outpos++] = ' ';
//                               outbuf[outpos++] = '\b';
//                            }
//
//                            // Copy command into command and display buffers
//                            for (inpos = 0; inpos < (S32)strlen(rgCmds[iCmdIndex]); inpos++, outpos++)
//                            {
//                               outbuf[outpos] = rgCmds[iCmdIndex][inpos];
//                               inbuf [inpos ] = rgCmds[iCmdIndex][inpos];
//                            }
//                         }
//                         // If previous is empty, stay on current command
//                         else if ((++ iCmdIndex) >= MAX_CMDS)
//                         {
//                            iCmdIndex = 0;
//                         }
//                         break;
//                      case 'B':
//                         /* down arrow */
//                         // Go to the next command in the command array, if
//                         // it isn't empty
//                         if (rgCmds[iCmdIndex][0] != '\0' && (++ iCmdIndex) >= MAX_CMDS)
//                            iCmdIndex = 0;
//
//                         // Obliterate current displayed text
//                         for (S32 i = outpos = 0; i < inpos; i ++)
//                         {
//                            outbuf[outpos++] = '\b';
//                            outbuf[outpos++] = ' ';
//                            outbuf[outpos++] = '\b';
//                         }
//
//                         // Copy command into command and display buffers
//                         for (inpos = 0; inpos < (S32)strlen(rgCmds[iCmdIndex]); inpos++, outpos++)
//                         {
//                            outbuf[outpos] = rgCmds[iCmdIndex][inpos];
//                            inbuf [inpos ] = rgCmds[iCmdIndex][inpos];
//                         }
//                         break;
//
//                     //XXTH added arrow keys
//                      case 'C':
//                          /* right arrow */
//                          // Wir dürfen nur nach rechts, wenn inpos kleiner als die Textlänge in inbuf ist
//                          if (inpos < (S32)strlen(inbuf))
//                          {
//                              outbuf[outpos++] = '\033'; // Escape-Zeichen
//                              outbuf[outpos++] = '[';
//                              outbuf[outpos++] = 'C';    // Sende "Cursor rechts" ans Terminal
//                              inpos++;                   // Erhöhe die logische Position im Text
//                          }
//                          break;
//
//                      case 'D':
//                          /* left arrow */
//                          // Wir dürfen nur nach links, wenn wir nicht ganz am Anfang (0) stehen
//                          if (inpos > 0)
//                          {
//                              outbuf[outpos++] = '\033'; // Escape-Zeichen
//                              outbuf[outpos++] = '[';
//                              outbuf[outpos++] = 'D';    // Sende "Cursor links" ans Terminal
//                              inpos--;                   // Verringere die logische Position im Text
//                          }
//                          break;
//
//                   }
//                   // read again to get rid of a bad char.
//                   //read(stdIn, &key, sizeof(char));
//                   break;
//                } else {
//                   inbuf[inpos++] = typedData[i];
//                   outbuf[outpos++] = typedData[i];
//                   break;
//                }
//                break;
//             default:
//                inbuf[inpos++] = typedData[i];
//                outbuf[outpos++] = typedData[i];
//                break;
//          }
//         }
//         if (outpos)
//         {
//            outbuf[outpos] = 0;
//            printf("%s", outbuf);
//         }
//       }
   }
}
