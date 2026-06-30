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



    static void ConsoleConsumer(/*ConsoleLogEntry::Level*/ U32 level, const char *line)
    {
        if (!gConsolePtr || !gConsolePtr->logs) return;
        //FIXME level matching imgui/elfscript
        char* finalBuffer = (char*)dMalloc(256);
        dMemset(finalBuffer, 0, 256);
        dSprintf(finalBuffer, 256, "%s",  line);

        gConsolePtr->logs[gConsolePtr->log_index++] =
        (Log){
            .text = finalBuffer
            , .type = (S32)level
        };
    }

    void  ConsoleHandler(const char* command)
    {
        if (command)  Con::evaluate(command);
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


    };
    IMPLEMENT_CONOBJECT(ConsoleGuiObject);

    void ConsoleGuiObject::initPersistFields() {
        Parent::initPersistFields();
        addField("key", TypeS32, Offset(mConsole.toggle_key, ConsoleGuiObject), "Shortcut to open console");
    }

    bool ConsoleGuiObject::onAdd() {
        if (!Parent::onAdd()) return false;
        if (gConsolePtr) return false;
        gConsolePtr = &mConsole;

        mImUI.theme = &DK_ImUISolarizedTheme;
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
    }

} //namespace

