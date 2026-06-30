#include "console/engineAPI.h"
#include "console/script.h"
#include "interface/elfResource.h"
#include "raylib.h"
#include "raymath.h"

#define DK_CONSOLE_IMPLEMENTATION
#include "dk/dk_console.h"
namespace ConsoleGui {

    //XXTH globals hackfest
    // static ImUI gImui;


    Console* gConsolePtr = nullptr;
    Vector<String> gHistory;
    S32 gHistoryNeedle;



    static void ConsoleConsumer(/*ConsoleLogEntry::Level*/ U32 level, const char *line)
    {
        if (!gConsolePtr || !gConsolePtr->logs
            || !line || line[0] == 0
        ) return;
        //FIXME level matching imgui/elfscript
        char* finalBuffer = (char*)dMalloc(256);
        dMemset(finalBuffer, 0, 256);
        dSprintf(finalBuffer, 256, "%s",  line);

        S32 finalLevel = LOG_INFO;
        switch (level)
        {
            case ConsoleLogEntry::Normal: finalLevel = LOG_INFO; break;
            case ConsoleLogEntry::Warning: finalLevel = LOG_WARNING; break;
            case ConsoleLogEntry::Error: finalLevel = LOG_ERROR; break;
            default: finalLevel = LOG_INFO; break;
        }

        gConsolePtr->logs[gConsolePtr->log_index++] =
        (Log){
            .text = finalBuffer
            , .type = finalLevel
        };
    }

    void  ConsoleHandler(const char* command)
    {
        if (command && command[0] != 0){
            gHistory.push_back(command);
            gHistoryNeedle = gHistory.size(); // - 1;
            Con::evaluate(command);
        }
    }

    class ConsoleGuiObject : public SimObject
    {
        typedef SimObject Parent;
    public:
        DECLARE_CONOBJECT(ConsoleGuiObject);

         Console mConsole = { .toggle_key = KEY_GRAVE };
         ImUI mImUI;


        bool onAdd() override;
        void onRemove() override;

        static void initPersistFields();

        void pushCommand() {
            if (!gConsolePtr || gHistory.size() == 0) return;
            if ( gHistoryNeedle >= 0 && gHistoryNeedle < gHistory.size()) {
                // Con::printf("COMMAND SHOULD BE %s", gHistory[gHistoryNeedle].c_str());
                dSprintf(gConsolePtr->ConsoleInputText, 1024, "%s",  gHistory[gHistoryNeedle].c_str());
                gConsolePtr->setCursorPos = gHistory[gHistoryNeedle].length();
            } else {
                dStrcpy(gConsolePtr->ConsoleInputText, "", 1024);
                gConsolePtr->setCursorPos = 0;
            }

        }

    };
    IMPLEMENT_CONOBJECT(ConsoleGuiObject);

    void ConsoleGuiObject::initPersistFields() {
        Parent::initPersistFields();
        addField("key", TypeS32, Offset(mConsole.toggle_key, ConsoleGuiObject), "Shortcut to open console");
        addField("fontSize", TypeF32, Offset(mConsole.fontSize, ConsoleGuiObject), "font size");
    }

    bool ConsoleGuiObject::onAdd() {
        if (!Parent::onAdd()) return false;
        if (gConsolePtr) return false;
        gConsolePtr = &mConsole;

        mImUI.theme = &DK_ImUIDefaultTheme;
        mImUI.style = &DK_ImUIDefaultStyle;

        static Font font = GetFontDefault();
        mImUI.font = &font;

        DK_ConsoleInit(gConsolePtr, LOG_SIZE);
        Con::addConsumer(ConsoleConsumer);
        return true;
    }

    void ConsoleGuiObject::onRemove() {
        DK_ConsoleShutdown(gConsolePtr, LOG_SIZE);
        gConsolePtr = nullptr;
        Parent::onRemove();
    }

    DefineEngineMethod(ConsoleGuiObject, setFont, bool, (S32 fontId), , "set the console font") {
        if (!gConsolePtr) return false;
        Font* font = ElfResource::FontMap.get(fontId);
        if (font) {
            object->mImUI.font = font;
            return true;
        }
        return false;
    }

    DefineEngineMethod(ConsoleGuiObject, Update, void, (), , "update the console") {
        if (!gConsolePtr) return ;
        DK_ConsoleUpdate(gConsolePtr, &object->mImUI,ConsoleHandler);
        if (gConsolePtr->is_open) {
            if (IsKeyPressed(KEY_UP)) {
                if (gHistoryNeedle > 0) gHistoryNeedle--;
                object->pushCommand();
            } else if (IsKeyPressed(KEY_DOWN)) {
                if (gHistoryNeedle < gHistory.size()) gHistoryNeedle++;
                object->pushCommand();
            }
        }

    }

} //namespace

