//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// ElfScript ImGui binding
//-----------------------------------------------------------------------------
// HOWTO and Requirements:
// - ImGui must be implemented and initialited..
// - using structs:
//      ImVec4 - F32 rgba
//      ImVec2 - F32 x,y
// - InitBindings_ImGui must be called on init to load constants
//-----------------------------------------------------------------------------

#include "console/engineAPI.h"
#include "console/consoleExtras.h"
#include "bindings_imgui.h"
#include "core/strings/stringUnit.h"
#include "math/mMathFn.h"

#include <string>
#include <format>

#include <imgui.h>
#include <imgui_internal.h>

//-----------------------------------------------------------------------------
// TypeImVec2
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( ImVec2,
                  ImVec2, ,
                  "" )

FIELD( x, x, 1, "X coordinate." )
FIELD( y, y, 1, "Y coordinate." )
END_IMPLEMENT_STRUCT;

ConsoleType(ImVec2, TypeImVec2, ImVec2, "")
ImplementConsoleTypeCasters( TypeImVec2, ImVec2 )

ConsoleGetType( TypeImVec2 )
{
    ImVec2 *pt = (ImVec2 *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g", pt->x, pt->y);
    return returnBuffer;
}

ConsoleSetType( TypeImVec2 )
{
    if(argc == 1)
        dSscanf(argv[0], "%g %g", &((ImVec2 *) dptr)->x, &((ImVec2 *) dptr)->y);
    else if(argc == 2)
        *((ImVec2 *) dptr) = ImVec2(dAtof(argv[0]), dAtof(argv[1]));
    else
        Con::printf("ImVec2 must be set as { x, y } or \"x y\"");
}
//-----------------------------------------------------------------------------
// TypeImVec4
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( ImVec4,
                  ImVec4, ,
                  "" )

FIELD( x, x, 1, "X coordinate." )
FIELD( y, y, 1, "Y coordinate." )
FIELD( z, z, 1, "Z coordinate." )
FIELD( w, w, 1, "W coordinate." )
END_IMPLEMENT_STRUCT;

ConsoleType(ImVec4, TypeImVec4, ImVec4, "")
ImplementConsoleTypeCasters(TypeImVec4, ImVec4)

ConsoleGetType( TypeImVec4 )
{
    ImVec4 *pt = (ImVec4 *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g %g %g", pt->x, pt->y, pt->z, pt->w);
    return returnBuffer;
}

ConsoleSetType( TypeImVec4 )
{
    if(argc == 1)
        dSscanf(argv[0], "%g %g %g %g", &((ImVec4 *) dptr)->x, &((ImVec4 *) dptr)->y, &((ImVec4 *) dptr)->z , &((ImVec4 *) dptr)->w);
    else if(argc == 4)
        *((ImVec4 *) dptr) = ImVec4(dAtof(argv[0]), dAtof(argv[1]), dAtof(argv[2]), dAtof(argv[3]));
    else
        Con::printf("ImVec4 must be set as { x, y, z, w } or \"x y z w\"");
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
static ImU32 ParseColor(F32 r, F32 g, F32 b, F32 a = 1.0f) {
    return ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a));
}

// -----------------------------------------------------------------------------
void RegisterImGuiWindowConstants() {
    // Window Flags (ImGuiWindowFlags_)
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_None);
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoTitleBar);                // Disable title-bar
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoResize);                  // Disable user resizing with the lower-right corner
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoMove);                    // Disable user moving the window
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoScrollbar);               // Disable scrollbars (window can still scroll with mouse wheel)
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoScrollWithMouse);         // Disable user vertically scrolling with mouse wheel
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoCollapse);                // Disable user collapsing window by double-clicking it
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_AlwaysAutoResize);          // Resize every frame to its content
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoBackground);              // Disable drawing background color and margins
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoSavedSettings);           // Never load/save settings in .ini file
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoMouseInputs);             // Disable catching mouse inputs
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_MenuBar);                  // Has a menu-bar (required for ImBeginMenuBar)
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_HorizontalScrollbar);       // Allow horizontal scrollbar to appear
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoFocusOnAppearing);        // Disable taking focus when transitioning from hidden to visible state
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoBringToFrontOnFocus);     // Disable bringing window to front when clicking on it
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_AlwaysVerticalScrollbar);   // Always show vertical scrollbar
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_AlwaysHorizontalScrollbar); // Always show horizontal scrollbar
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoNavFocus);                // No focusing navigation inside window
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_UnsavedDocument);           // Display a dot next to the title (indicates unsaved changes)
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoNav);                     // Combination of NoNavInputs and NoNavFocus
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoDecoration);              // Combination of NoTitleBar, NoResize, NoScrollbar, NoCollapse
    Con::REGISTER_CONST_S32(ImGuiWindowFlags_NoInputs);                  // Combination of NoMouseInputs, NoNavInputs, NoNavFocus

    // ------------ Node Flags:
    // Tree Node Flags (ImGuiTreeNodeFlags_)
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_None);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_Selected);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_Framed);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_AllowOverlap);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_NoTreePushOnOpen);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_NoAutoOpenOnLog);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_DefaultOpen);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_OpenOnDoubleClick);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_OpenOnArrow);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_Leaf);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_Bullet);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_FramePadding);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_SpanAvailWidth);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_SpanFullWidth);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_SpanLabelWidth);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_SpanAllColumns);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_LabelSpanAllColumns);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_NavLeftJumpsToParent);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_CollapsingHeader);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_DrawLinesNone);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_DrawLinesFull);
    Con::REGISTER_CONST_S32(ImGuiTreeNodeFlags_DrawLinesToNodes);

    // Popup Flags (ImGuiPopupFlags_)
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_None);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_MouseButtonLeft);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_MouseButtonRight);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_MouseButtonMiddle);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_MouseButtonMask_);
    // Con::REGISTER_CONST_S32(ImGuiPopupFlags_MouseButtonDefault_);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_NoReopen);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_NoOpenOverExistingPopup);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_NoOpenOverItems);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_AnyPopupId);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_AnyPopupLevel);
    Con::REGISTER_CONST_S32(ImGuiPopupFlags_AnyPopup);

    // Color Indices (ImGuiCol_)
    Con::REGISTER_CONST_S32(ImGuiCol_Text);
    Con::REGISTER_CONST_S32(ImGuiCol_TextDisabled);
    Con::REGISTER_CONST_S32(ImGuiCol_WindowBg);
    Con::REGISTER_CONST_S32(ImGuiCol_ChildBg);
    Con::REGISTER_CONST_S32(ImGuiCol_PopupBg);
    Con::REGISTER_CONST_S32(ImGuiCol_Border);
    Con::REGISTER_CONST_S32(ImGuiCol_BorderShadow);
    Con::REGISTER_CONST_S32(ImGuiCol_FrameBg);
    Con::REGISTER_CONST_S32(ImGuiCol_FrameBgHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_FrameBgActive);
    Con::REGISTER_CONST_S32(ImGuiCol_TitleBg);
    Con::REGISTER_CONST_S32(ImGuiCol_TitleBgActive);
    Con::REGISTER_CONST_S32(ImGuiCol_TitleBgCollapsed);
    Con::REGISTER_CONST_S32(ImGuiCol_MenuBarBg);
    Con::REGISTER_CONST_S32(ImGuiCol_ScrollbarBg);
    Con::REGISTER_CONST_S32(ImGuiCol_ScrollbarGrab);
    Con::REGISTER_CONST_S32(ImGuiCol_ScrollbarGrabHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_ScrollbarGrabActive);
    Con::REGISTER_CONST_S32(ImGuiCol_CheckMark);
    Con::REGISTER_CONST_S32(ImGuiCol_SliderGrab);
    Con::REGISTER_CONST_S32(ImGuiCol_SliderGrabActive);
    Con::REGISTER_CONST_S32(ImGuiCol_Button);
    Con::REGISTER_CONST_S32(ImGuiCol_ButtonHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_ButtonActive);
    Con::REGISTER_CONST_S32(ImGuiCol_Header);
    Con::REGISTER_CONST_S32(ImGuiCol_HeaderHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_HeaderActive);
    Con::REGISTER_CONST_S32(ImGuiCol_Separator);
    Con::REGISTER_CONST_S32(ImGuiCol_SeparatorHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_SeparatorActive);
    Con::REGISTER_CONST_S32(ImGuiCol_ResizeGrip);
    Con::REGISTER_CONST_S32(ImGuiCol_ResizeGripHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_ResizeGripActive);
    Con::REGISTER_CONST_S32(ImGuiCol_TabHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_Tab);
    Con::REGISTER_CONST_S32(ImGuiCol_TabSelected);
    Con::REGISTER_CONST_S32(ImGuiCol_TabSelectedOverline);
    Con::REGISTER_CONST_S32(ImGuiCol_TabDimmed);
    Con::REGISTER_CONST_S32(ImGuiCol_TabDimmedSelected);
    Con::REGISTER_CONST_S32(ImGuiCol_TabDimmedSelectedOverline);
    Con::REGISTER_CONST_S32(ImGuiCol_PlotLines);
    Con::REGISTER_CONST_S32(ImGuiCol_PlotLinesHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_PlotHistogram);
    Con::REGISTER_CONST_S32(ImGuiCol_PlotHistogramHovered);
    Con::REGISTER_CONST_S32(ImGuiCol_TableHeaderBg);
    Con::REGISTER_CONST_S32(ImGuiCol_TableBorderStrong);
    Con::REGISTER_CONST_S32(ImGuiCol_TableBorderLight);
    Con::REGISTER_CONST_S32(ImGuiCol_TableRowBg);
    Con::REGISTER_CONST_S32(ImGuiCol_TableRowBgAlt);
    Con::REGISTER_CONST_S32(ImGuiCol_TextLink);
    Con::REGISTER_CONST_S32(ImGuiCol_TextSelectedBg);
    Con::REGISTER_CONST_S32(ImGuiCol_DragDropTarget);
    Con::REGISTER_CONST_S32(ImGuiCol_NavHighlight);
    Con::REGISTER_CONST_S32(ImGuiCol_NavWindowingHighlight);
    Con::REGISTER_CONST_S32(ImGuiCol_NavWindowingDimBg);
    Con::REGISTER_CONST_S32(ImGuiCol_ModalWindowDimBg);
    Con::REGISTER_CONST_S32(ImGuiCol_COUNT);

    // Style Variables (ImGuiStyleVar_)
    Con::REGISTER_CONST_S32(ImGuiStyleVar_Alpha);               // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_DisabledAlpha);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_WindowPadding);       // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_WindowRounding);      // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_WindowBorderSize);    // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_WindowMinSize);       // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_WindowTitleAlign);    // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ChildRounding);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ChildBorderSize);     // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_PopupRounding);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_PopupBorderSize);     // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_FramePadding);        // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_FrameRounding);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_FrameBorderSize);     // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ItemSpacing);         // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ItemInnerSpacing);    // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_IndentSpacing);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_CellPadding);         // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ScrollbarSize);       // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ScrollbarRounding);    // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_GrabMinSize);         // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_GrabRounding);        // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_TabRounding);         // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_TabBarBorderSize);    // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_TabBarOverlineSize);  // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_TableAngledHeadersAngle); // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_TableAngledHeadersTextAlign); // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_ButtonTextAlign);     // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_SelectableTextAlign); // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_SeparatorTextPadding); // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_SeparatorTextAlign);  // ImVec2
    Con::REGISTER_CONST_S32(ImGuiStyleVar_SeparatorTextBorderSize); // float
    Con::REGISTER_CONST_S32(ImGuiStyleVar_COUNT);

    // Input Text Flags (ImGuiInputTextFlags_)
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_None);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CharsDecimal);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CharsHexadecimal);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CharsUppercase);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CharsNoBlank);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_AutoSelectAll);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_EnterReturnsTrue);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackCompletion);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackHistory);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackAlways);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackCharFilter);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_AllowTabInput);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CtrlEnterForNewLine);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_NoHorizontalScroll);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_AlwaysOverwrite);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_ReadOnly);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_Password);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_NoUndoRedo);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CharsScientific);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackResize);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_CallbackEdit);
    Con::REGISTER_CONST_S32(ImGuiInputTextFlags_EscapeClearsAll);


}

// -----------------------------------------------------------------------------
void RegisterImGuiKeyConstants() {

    // Modifiers / Chords
    Con::REGISTER_CONST_S32(ImGuiMod_None);
    Con::REGISTER_CONST_S32(ImGuiMod_Ctrl);
    Con::REGISTER_CONST_S32(ImGuiMod_Shift);
    Con::REGISTER_CONST_S32(ImGuiMod_Alt);
    Con::REGISTER_CONST_S32(ImGuiMod_Super);

    // Alphabet
    Con::REGISTER_CONST_S32(ImGuiKey_A); Con::REGISTER_CONST_S32(ImGuiKey_B);
    Con::REGISTER_CONST_S32(ImGuiKey_C); Con::REGISTER_CONST_S32(ImGuiKey_D);
    Con::REGISTER_CONST_S32(ImGuiKey_E); Con::REGISTER_CONST_S32(ImGuiKey_F);
    Con::REGISTER_CONST_S32(ImGuiKey_G); Con::REGISTER_CONST_S32(ImGuiKey_H);
    Con::REGISTER_CONST_S32(ImGuiKey_I); Con::REGISTER_CONST_S32(ImGuiKey_J);
    Con::REGISTER_CONST_S32(ImGuiKey_K); Con::REGISTER_CONST_S32(ImGuiKey_L);
    Con::REGISTER_CONST_S32(ImGuiKey_M); Con::REGISTER_CONST_S32(ImGuiKey_N);
    Con::REGISTER_CONST_S32(ImGuiKey_O); Con::REGISTER_CONST_S32(ImGuiKey_P);
    Con::REGISTER_CONST_S32(ImGuiKey_Q); Con::REGISTER_CONST_S32(ImGuiKey_R);
    Con::REGISTER_CONST_S32(ImGuiKey_S); Con::REGISTER_CONST_S32(ImGuiKey_T);
    Con::REGISTER_CONST_S32(ImGuiKey_U); Con::REGISTER_CONST_S32(ImGuiKey_V);
    Con::REGISTER_CONST_S32(ImGuiKey_W); Con::REGISTER_CONST_S32(ImGuiKey_X);
    Con::REGISTER_CONST_S32(ImGuiKey_Y); Con::REGISTER_CONST_S32(ImGuiKey_Z);

    // Numbers
    Con::REGISTER_CONST_S32(ImGuiKey_0); Con::REGISTER_CONST_S32(ImGuiKey_1);
    Con::REGISTER_CONST_S32(ImGuiKey_2); Con::REGISTER_CONST_S32(ImGuiKey_3);
    Con::REGISTER_CONST_S32(ImGuiKey_4); Con::REGISTER_CONST_S32(ImGuiKey_5);
    Con::REGISTER_CONST_S32(ImGuiKey_6); Con::REGISTER_CONST_S32(ImGuiKey_7);
    Con::REGISTER_CONST_S32(ImGuiKey_8); Con::REGISTER_CONST_S32(ImGuiKey_9);

    // Function Keys
    Con::REGISTER_CONST_S32(ImGuiKey_F1);  Con::REGISTER_CONST_S32(ImGuiKey_F2);
    Con::REGISTER_CONST_S32(ImGuiKey_F3);  Con::REGISTER_CONST_S32(ImGuiKey_F4);
    Con::REGISTER_CONST_S32(ImGuiKey_F5);  Con::REGISTER_CONST_S32(ImGuiKey_F6);
    Con::REGISTER_CONST_S32(ImGuiKey_F7);  Con::REGISTER_CONST_S32(ImGuiKey_F8);
    Con::REGISTER_CONST_S32(ImGuiKey_F9);  Con::REGISTER_CONST_S32(ImGuiKey_F10);
    Con::REGISTER_CONST_S32(ImGuiKey_F11); Con::REGISTER_CONST_S32(ImGuiKey_F12);

    // Navigation & Editing
    Con::REGISTER_CONST_S32(ImGuiKey_Tab);
    Con::REGISTER_CONST_S32(ImGuiKey_LeftArrow);
    Con::REGISTER_CONST_S32(ImGuiKey_RightArrow);
    Con::REGISTER_CONST_S32(ImGuiKey_UpArrow);
    Con::REGISTER_CONST_S32(ImGuiKey_DownArrow);
    Con::REGISTER_CONST_S32(ImGuiKey_PageUp);
    Con::REGISTER_CONST_S32(ImGuiKey_PageDown);
    Con::REGISTER_CONST_S32(ImGuiKey_Home);
    Con::REGISTER_CONST_S32(ImGuiKey_End);
    Con::REGISTER_CONST_S32(ImGuiKey_Insert);
    Con::REGISTER_CONST_S32(ImGuiKey_Delete);
    Con::REGISTER_CONST_S32(ImGuiKey_Backspace);
    Con::REGISTER_CONST_S32(ImGuiKey_Space);
    Con::REGISTER_CONST_S32(ImGuiKey_Enter);
    Con::REGISTER_CONST_S32(ImGuiKey_Escape);

    // Mouse Button Enums
    Con::REGISTER_CONST_S32(ImGuiMouseButton_Left);
    Con::REGISTER_CONST_S32(ImGuiMouseButton_Right);
    Con::REGISTER_CONST_S32(ImGuiMouseButton_Middle);

}
// -----------------------------------------------------------------------------
void RegisterImGuiTableConstants() {

    // Table Flags (ImGuiTableFlags_)
    Con::REGISTER_CONST_S32(ImGuiTableFlags_None);
    Con::REGISTER_CONST_S32(ImGuiTableFlags_Resizable);        // Make columns resizable
    Con::REGISTER_CONST_S32(ImGuiTableFlags_Reorderable);      // Allow reordering columns via drag-and-drop
    Con::REGISTER_CONST_S32(ImGuiTableFlags_Hideable);         // Allow hiding columns via right-click
    Con::REGISTER_CONST_S32(ImGuiTableFlags_Sortable);         // Enable sorting features
    Con::REGISTER_CONST_S32(ImGuiTableFlags_NoSavedSettings);  // Don't save style modifications to .ini
    Con::REGISTER_CONST_S32(ImGuiTableFlags_ContextMenuInBody);// Right-click inside table body opens options

    // Table Decorations / Styling
    Con::REGISTER_CONST_S32(ImGuiTableFlags_RowBg);            // Alternating row background colors (Zebra stripes)
    Con::REGISTER_CONST_S32(ImGuiTableFlags_BordersInnerH);    // Draw horizontal borders inside
    Con::REGISTER_CONST_S32(ImGuiTableFlags_BordersOuterH);    // Draw horizontal borders outside
    Con::REGISTER_CONST_S32(ImGuiTableFlags_BordersInnerV);    // Draw vertical borders inside
    Con::REGISTER_CONST_S32(ImGuiTableFlags_BordersOuterV);    // Draw vertical borders outside
    Con::REGISTER_CONST_S32(ImGuiTableFlags_Borders);          // Full border grid combination
    Con::REGISTER_CONST_S32(ImGuiTableFlags_ScrollX);          // Enable horizontal scrolling inside table
    Con::REGISTER_CONST_S32(ImGuiTableFlags_ScrollY);          // Enable vertical scrolling inside table

    // Column Configuration Flags (ImGuiTableColumnFlags_)
    Con::REGISTER_CONST_S32(ImGuiTableColumnFlags_None);
    Con::REGISTER_CONST_S32(ImGuiTableColumnFlags_Disabled);    // Completely hide/disable column
    Con::REGISTER_CONST_S32(ImGuiTableColumnFlags_DefaultHide); // Hidden by default, user can turn it on
    Con::REGISTER_CONST_S32(ImGuiTableColumnFlags_WidthFixed);
    Con::REGISTER_CONST_S32(ImGuiTableColumnFlags_WidthStretch);

}

// -----------------------------------------------------------------------------
// Borrowed from OhmFlux
void RegisterColorConstants() {

    #define REGISTER_COLOR_CONST(name, x, y, z, w) \
    { \
        char colBuf[128]; \
        std::snprintf(colBuf, sizeof(colBuf), "\"%f %f %f %f\"", x, y, z, w); \
        Con::setScriptConstant(#name, colBuf); \
    }

    // Standard Colors
    REGISTER_COLOR_CONST(cl_NONE,        -1.0f, -1.0f, -1.0f, -1.0f);
    REGISTER_COLOR_CONST(cl_White,        1.0f,  1.0f,  1.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Black,        0.0f,  0.0f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Red,          1.0f,  0.0f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Green,        0.0f,  1.0f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Blue,         0.0f,  0.0f,  1.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Yellow,       1.0f,  1.0f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Cyan,         0.0f,  1.0f,  1.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Magenta,      1.0f,  0.0f,  1.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Gray,         0.5f,  0.5f,  0.5f,  1.0f);
    REGISTER_COLOR_CONST(cl_LightGray,    0.75f, 0.75f, 0.75f, 1.0f);
    REGISTER_COLOR_CONST(cl_DarkGray,     0.25f, 0.25f, 0.25f, 1.0f);
    REGISTER_COLOR_CONST(cl_Orange,       1.0f,  0.5f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Purple,       0.5f,  0.0f,  0.5f,  1.0f);
    REGISTER_COLOR_CONST(cl_Brown,        0.6f,  0.3f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Lime,         0.75f, 1.0f,  0.0f,  1.0f);
    REGISTER_COLOR_CONST(cl_Pink,         1.0f,  0.4f,  0.7f,  1.0f);

    // Modern / UI UI Accents
    REGISTER_COLOR_CONST(cl_Crimson,      0.86f, 0.08f, 0.24f, 1.0f);
    REGISTER_COLOR_CONST(cl_Emerald,      0.16f, 0.71f, 0.44f, 1.0f);
    REGISTER_COLOR_CONST(cl_SkyBlue,      0.53f, 0.81f, 0.98f, 1.0f);
    REGISTER_COLOR_CONST(cl_Slate,        0.18f, 0.24f, 0.31f, 1.0f);
    REGISTER_COLOR_CONST(cl_Gold,         1.00f, 0.84f, 0.00f, 1.0f);
    REGISTER_COLOR_CONST(cl_Transparent,  0.00f, 0.00f, 0.00f, 0.00f);

    // Environment Colors
    REGISTER_COLOR_CONST(cl_Aquamarine,   0.50f, 1.00f, 0.83f, 1.0f);
    REGISTER_COLOR_CONST(cl_Coral,        1.00f, 0.50f, 0.31f, 1.0f);
    REGISTER_COLOR_CONST(cl_DeepSea,      0.00f, 0.08f, 0.20f, 1.0f);
    REGISTER_COLOR_CONST(cl_Seafoam,      0.60f, 0.85f, 0.75f, 1.0f);
    REGISTER_COLOR_CONST(cl_Sand,         0.76f, 0.70f, 0.50f, 1.0f);
    REGISTER_COLOR_CONST(cl_Kelp,         0.13f, 0.29f, 0.13f, 1.0f);

    // Debug / Visualizer Colors
    REGISTER_COLOR_CONST(cl_NeonPink,     1.00f, 0.00f, 0.50f, 1.0f);
    REGISTER_COLOR_CONST(cl_ElectricBlue, 0.00f, 1.00f, 1.00f, 1.0f);
    REGISTER_COLOR_CONST(cl_AcidGreen,    0.50f, 1.00f, 0.00f, 1.0f);

    // Special FX Colors
    REGISTER_COLOR_CONST(cl_Glass,        1.00f, 1.00f, 1.00f, 0.25f);
    REGISTER_COLOR_CONST(cl_Shadow,       0.00f, 0.00f, 0.00f, 0.40f);
    REGISTER_COLOR_CONST(cl_Ghost,        0.70f, 0.70f, 1.00f, 0.50f);

    #undef REGISTER_COLOR_CONST
}

// -----------------------------------------------------------------------------
void InitBindings_ImGui() {
    //real constant using preprocessor*
     Con::setScriptConstant("FLT_MIN", (F64)FLT_MIN);
     Con::setScriptConstant("FLT_MAX", (F64)FLT_MAX);

     RegisterImGuiWindowConstants();
     RegisterImGuiTableConstants();
     RegisterImGuiKeyConstants();
     RegisterColorConstants();

     Con::registerEnumS32<ImGuiCond_>("", false);


     // Con::registerEnumS32<ImGuiKey>("", true);
     //enum ImGuiKey : int
}
// -----------------------------------------------------------------------------
ConsoleFunctionGroupBegin( ImGui, "ImGui/BaseFlux functions");
// -----------------------------------------------------------------------------
DefineEngineFunction(ImSetNextWindowSize, void, (ImVec2 size, S32 condition ),(0),"Set the next Window Size if not saved.")
{
    ImGui::SetNextWindowSize(size, condition);
}
// -----------------------------------------------------------------------------
DefineEngineFunction(ImSetNextWindowPos, void, (ImVec2 size, S32 condition, ImVec2 pivot ),(0, ImVec2(0.f,0.f)),"Set the next Window Position if not saved.")
{
    ImGui::SetNextWindowPos(size, condition, pivot);
}

// -----------------------------------------------------------------------------
DefineEngineFunction(ImBegin, bool, (String name, String openVarName, S32 windowFlags),("", 0 ),"")
{
    // IMGUI_API bool          Begin(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0);
    if (!openVarName.isEmpty()) {
        bool value = Con::getBoolVariable(openVarName.c_str(), true);
        if (ImGui::Begin(name.c_str(), &value, windowFlags)) {
            Con::setBoolVariable(openVarName, value);
            return true;
        }
        return false;
    }
    return ImGui::Begin(name.c_str());
}

DefineEngineFunction(ImEnd, void, (),,"") { ImGui::End(); }

DefineEngineFunction(ImBeginGroup, void, (),,"") { ImGui::BeginGroup(); }
DefineEngineFunction(ImEndGroup, void, (),,"") { ImGui::EndGroup(); }

// -----------------------------------------------------------------------------
DefineEngineFunction(ImSameLine, void, (F32 offsetX, F32 spacing),(0.0f, -1.0f),"") {
    ImGui::SameLine(offsetX, spacing);
}
DefineEngineFunction(ImNewLine, void, (),,"") { ImGui::NewLine(); }
DefineEngineFunction(ImSpacing, void, (),,"") { ImGui::Spacing(); }
DefineEngineFunction(ImDummy, void, (ImVec2 size ),,"") { ImGui::Dummy(size); }
// -----------------------------------------------------------------------------
DefineEngineFunction(ImPushID, void, (const char* str_id),,"") { ImGui::PushID(str_id); }
DefineEngineFunction(ImPopID, void, (),,"") { ImGui::PopID(); }
// -----------------------------------------------------------------------------
DefineEngineFunction(ImText, void, (String text),,"") { ImGui::Text("%s", text.c_str()); }
DefineEngineFunction(ImTextColored, void, (ImVec4 color, String text),,"") {
    ImGui::TextColored(color, "%s", text.c_str());
}
DefineEngineFunction(ImTextLink, bool, (const char* label),,"") { return ImGui::TextLink(label); }
// -----------------------------------------------------------------------------
DefineEngineFunction(ImBullet, void, (),,"draw a small circle + keep the cursor on the same line") { ImGui::Bullet(); }
// -----------------------------------------------------------------------------
// ProgressBar(F32 fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0), const char* overlay = NULL);
DefineEngineFunction(ImProgressBar, void, (F32 fraction, ImVec2 size, String overlay),(ImVec2(-FLT_MIN, 0.f), "")  ,"a ProgressBar") {
    if (!overlay.isEmpty()) ImGui::ProgressBar(fraction, size, overlay.c_str());
    else ImGui::ProgressBar(fraction, size);
}
// -----------------------------------------------------------------------------
DefineEngineFunction(ImSeparator, void, (),,"") { ImGui::Separator(); }
DefineEngineFunction(ImSeparatorText, void, (const char* label),,"") { ImGui::SeparatorText(label); }
// -----------------------------------------------------------------------------
// IMGUI_API bool          Button(const char* label, const ImVec2& size = ImVec2(0, 0));   // button
DefineEngineFunction(ImButton, bool, (const char* label, ImVec2 size ),(ImVec2(0.f,0.f)),"") {
    return ImGui::Button(label, size);
}
// =============================================================================
//  ImGui Tab Bars
// =============================================================================

DefineEngineFunction(ImBeginTabBar, bool, (const char* str_id, S32 flags),(0) ,
                     "Begins a ImGui TabBar\n")
{
    return ImGui::BeginTabBar(str_id, flags);
}

DefineEngineFunction(ImBeginTabItem, bool, (const char* label, String openVarName, S32 tabItemFlags),("", 0 )
    ,"Begin a Tab Item ")
{
    //  IMGUI_API bool  BeginTabItem(const char* label, bool* p_open = NULL, ImGuiTabItemFlags flags = 0);
    if (!openVarName.isEmpty()) {
        bool value = Con::getBoolVariable(openVarName.c_str(), true);
        if (ImGui::BeginTabItem(label, &value, tabItemFlags)) {
            Con::setBoolVariable(openVarName, value);
            return true;
        }
        return false;
    }
    return ImGui::BeginTabItem(label);
}

DefineEngineFunction(ImEndTabItem, void, (), , "Ends a ImGui TabBarItem")
{
    return ImGui::EndTabItem();
}
DefineEngineFunction(ImEndTabBar, void, (), ,"Ends a ImGui TabBar")
{
    return ImGui::EndTabBar();
}

DefineEngineFunction(ImTabItemButton, bool, (const char* label, S32 flags), ,"")
{
    return ImGui::TabItemButton(label, flags);
}
// =============================================================================
//  ImGui Input
// =============================================================================
DefineEngineFunction(ImCheckbox, bool, (const char* text, const char* valueVarName),,
    "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
    "Example: Imcheckbox(\"test\", \"$myvar\"); "
    "Example: Imcheckbox(\"test\", \"MyObject.myvar\"); "
    "Example: Imcheckbox(\"test\", %obj.getId() @ \".myvar\"); "
) {
    bool value = Con::getBoolVariable(valueVarName, false);
    bool result = ImGui::Checkbox(text, &value);
    if (result) {
        Con::setBoolVariable(valueVarName, value);
    }
    return result;
}
// -----------------------------------------------------------------------------
DefineEngineFunction(ImSliderFloat, bool, (const char* text, const char* valueVarName, F32 min, F32 max, const char* format, S32 flags),
    (0.f, 1.f,"%.3f", 0),
    "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
) {
    F32 value = Con::getFloatVariable(valueVarName, 0.f);
    bool result = ImGui::SliderFloat(text, &value, min, max, format, flags);
    if (result) {
        Con::setFloatVariable(valueVarName, value);
    }
    return result;
}
// -----------------------------------------------------------------------------
DefineEngineFunction(ImSliderInt, bool, (const char* text, const char* valueVarName
    , S32 min, S32 max, const char* format, S32 flags),
    (0, 100,"%d", 0),
    "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
) {
    S32 value = Con::getIntVariable(valueVarName, 0);
    bool result = ImGui::SliderInt(text, &value, min, max, format, flags);
    if (result) {
        Con::setIntVariable(valueVarName, value);
    }
    return result;
}
// -----------------------------------------------------------------------------
// InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
DefineEngineFunction(ImInputText, bool, (const char* text, const char* valueVarName,  S32 flags),
    (0),
    "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
) {

    char buf[1024]{};
    const char* value = Con::getVariable(valueVarName, "");
    dStrcpy(buf, value, 1024);
    bool result = ImGui::InputText(text, buf,1024, flags);
    if (result) {
        Con::setVariable(valueVarName, buf);
    }
    return result;
}

// IMGUI_API bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
DefineEngineFunction(ImColorEdit, bool, (const char* label, const char* valueVarName, bool using_rgba_u8), (false),
                     "Color Edit, when set bool using_rgba_u8 we convert it from 1.f to 255.") {

    const char* currentStr = Con::getVariable(valueVarName);
    float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    if (currentStr && currentStr[0] != '\0') {
        int scanned = dSscanf(currentStr, "%f %f %f %f", &color[0], &color[1], &color[2], &color[3]);
        if (using_rgba_u8) {
            for (int i = 0; i < scanned; ++i) {
                color[i] /= 255.0f;
            }
        }
    }
    bool result = ImGui::ColorEdit4(label, color, 0);

    if (result) {
        char buffer[256];
        if (using_rgba_u8) {
            int r = (int)ElfMath::mRound(color[0] * 255.0f);
            int g = (int)ElfMath::mRound(color[1] * 255.0f);
            int b = (int)ElfMath::mRound(color[2] * 255.0f);
            int a = (int)ElfMath::mRound(color[3] * 255.0f);
            dSprintf(buffer, sizeof(buffer), "%d %d %d %d", r, g, b, a);
        } else {
            dSprintf(buffer, sizeof(buffer), "%f %f %f %f", color[0], color[1], color[2], color[3]);
        }

        Con::setVariable(valueVarName, buffer);
    }

    return result;
}

// -----------------------------------------------------------------------------
// =============================================================================
//  ImGui Boxes
// =============================================================================
DefineEngineFunction(ImCombo, bool, (
    const char* label
    , const char* currentItemIndexVarName
    , const char* ItemsTabSeparated),,
    "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
    "@var currentItemIndexVarName is the name of variable where the current item index lives\n"
    "@var ItemsTabSeparated tab separated list of items \n"
) {
    S32 index = Con::getIntVariable(currentItemIndexVarName, 0);
    bool valueChanged = false;
    const char* previewText = "";
    if (ItemsTabSeparated && ItemsTabSeparated[0] != '\0' && index >= 0) {
        const char* currentItem = StringUnit::getUnit(ItemsTabSeparated, index, "\t");
        if (currentItem) {
            previewText = currentItem;
        }
    }
    if (ImGui::BeginCombo(label, previewText, 0)) {
        if (ItemsTabSeparated && ItemsTabSeparated[0] != '\0') {
            U32 count = StringUnit::getUnitCount(ItemsTabSeparated, "\t");

            for (U32 i = 0; i < count; ++i) {
                const char* item = StringUnit::getUnit(ItemsTabSeparated, i, "\t");
                if (!item || item[0] == '\0') {
                    continue;
                }
                const bool isSelected = (index == static_cast<S32>(i));
                if (ImGui::Selectable(item, isSelected)) {
                    index = i;
                    valueChanged = true;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
        }
        ImGui::EndCombo();
    }
    if (valueChanged) {
        Con::setIntVariable(currentItemIndexVarName, index);
    }
    return valueChanged;
}


// -----------------------------------------------------------------------------
DefineEngineFunction(ImListBox, bool, (
        const char* label
        , const char* currentItemIndexVarName
        , const char* ItemsTabSeparated
        , S32 height_in_items),
        (-1),
        "return true if changed add a varname as reference. Can be a global variable or a Object field.\n"
        "@var currentItemIndexVarName is the name of variable where the current item index lives\n"
        "@var ItemsTabSeparated tab separated list of items \n"
) {

    S32 index = Con::getIntVariable(currentItemIndexVarName, 0);
    bool valueChanged = false;

    if (!ItemsTabSeparated || ItemsTabSeparated[0] == '\0') {
        return false;
    }
    U32 count = StringUnit::getUnitCount(ItemsTabSeparated, "\t");
    if (ImGui::BeginListBox(label,
            height_in_items > 0
                ? ImVec2(0, height_in_items * ImGui::GetTextLineHeightWithSpacing())
                : ImVec2(0,0)
        )) {
        for (U32 i = 0; i < count; ++i) {
            const char* item = StringUnit::getUnit(ItemsTabSeparated, i, "\t");
            if (!item || item[0] == '\0') continue;// ignore empty
            const bool isSelected = (index == static_cast<S32>(i));
            if (ImGui::Selectable(item, isSelected)) {
                index = i;
                valueChanged = true;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }
    if (valueChanged) {
        Con::setIntVariable(currentItemIndexVarName, index);
    }
    return valueChanged;
}
// -----------------------------------------------------------------------------
// =============================================================================
// Popups
// =============================================================================
DefineEngineFunction(ImBeginPopupContextItem, bool, (String contextId, S32 popupFlags),("",0),"") {
    return ImGui::BeginPopupContextItem(!contextId.isEmpty() ? contextId.c_str() : nullptr, popupFlags);
}
DefineEngineFunction(ImBeginPopupContextWindow, bool, (String contextId, S32 popupFlags),("",0),"") {
    return  ImGui::BeginPopupContextWindow(!contextId.isEmpty() ? contextId.c_str() : nullptr, popupFlags);
}

DefineEngineFunction(ImBeginPopup, bool, (String contextId, S32 popupFlags),("",0),"") {
    return ImGui::BeginPopup(!contextId.isEmpty() ? contextId.c_str() : nullptr, popupFlags);
}

DefineEngineFunction(ImBeginPopupModal, bool, (String name, String openVarName, S32 windowFlags),("", 0 ),"")
{
    if (!openVarName.isEmpty()) {
        bool value = Con::getBoolVariable(openVarName.c_str(), true);
        if (ImGui::BeginPopupModal(name.c_str(), &value, windowFlags)) {
            Con::setBoolVariable(openVarName, value);
            return true;
        }
        return false;
    }
    return ImGui::BeginPopupModal(name.c_str());
}


DefineEngineFunction(ImIsPopupOpen, bool, (String contextId, S32 popupFlags),(0),"") {
    return ImGui::IsPopupOpen(contextId.c_str(), popupFlags);
}
DefineEngineFunction(ImOpenPopup, void, (String contextId, S32 popupFlags),("",0),"call to mark popup as open (don't call every frame!).") {
    ImGui::OpenPopup(!contextId.isEmpty() ? contextId.c_str() : nullptr, popupFlags);
}

DefineEngineFunction(ImOpenPopupOnItemClick, void, (String contextId, S32 popupFlags),("",1),
                     "helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1.\n"
                     "(note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)") {
    ImGui::OpenPopupOnItemClick(!contextId.isEmpty() ? contextId.c_str() : nullptr, popupFlags);
}

DefineEngineFunction(ImCloseCurrentPopup, void, (String contextId, S32 popupFlags),("",0),"close the current popup") {
    ImGui::CloseCurrentPopup();
}

DefineEngineFunction(ImEndPopup, void, (),,"") { ImGui::EndPopup();}
// -----------------------------------------------------------------------------
// =============================================================================
// Window Menu Bars
// =============================================================================
DefineEngineFunction(ImBeginMenuBar, bool, (), ,
                     "Append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).\n"
                     "Only call ImEndMenuBar() if this returns true.\n") {
    return ImGui::BeginMenuBar();
}
DefineEngineFunction(ImEndMenuBar, void, (), ,
                     "Only call if ImBeginMenuBar() returned true.\n") {
    ImGui::EndMenuBar();
}
// =============================================================================
// Main Menu Bars (Full Screen)
// =============================================================================
DefineEngineFunction(ImBeginMainMenuBar, bool, (), ,
                     "Create and append to a full screen menu-bar.\n"
                     "Only call ImEndMainMenuBar() if this returns true.\n") {
    return ImGui::BeginMainMenuBar();
}
DefineEngineFunction(ImEndMainMenuBar, void, (), ,
                     "Only call if ImBeginMainMenuBar() returned true.\n") {
    ImGui::EndMainMenuBar();
}
// =============================================================================
// Sub-Menus
// =============================================================================
DefineEngineFunction(ImBeginMenu, bool, (const char* label, bool enabled), (true),
                     "Create a sub-menu entry. Only call ImEndMenu() if this returns true.\n") {
    return ImGui::BeginMenu(label, enabled);
}
DefineEngineFunction(ImEndMenu, void, (), ,
                     "Only call if ImBeginMenu() returned true.\n") {
    ImGui::EndMenu();
}
// =============================================================================
// Menu Items
// =============================================================================
// Standard variant (returns true when clicked/activated)
DefineEngineFunction(ImMenuItem, bool, (const char* label, const char* shortcut, bool selected, bool enabled), ("", false, true),
                     "Renders a standard menu item. Returns true when activated.\n") {
    const char* shortcutPtr = (shortcut && shortcut[0] != '\0') ? shortcut : nullptr;
    return ImGui::MenuItem(label, shortcutPtr, selected, enabled);
}
// Toggle variant (binds directly to an engine/script variable name)
DefineEngineFunction(ImMenuItemToggle, bool, (const char* label, const char* shortcut, const char* boolVarName, bool enabled), ("", "", true),
                     "Renders a menu item with a checkbox toggle tied to a script variable.\n"
                     "Returns true if the state changed.\n") {
    const char* shortcutPtr = (shortcut && shortcut[0] != '\0') ? shortcut : nullptr;

    bool value = Con::getBoolVariable(boolVarName, false);
    bool result = ImGui::MenuItem(label, shortcutPtr, &value, enabled);

    if (result) {
        Con::setBoolVariable(boolVarName, value);
    }
    return result;
}
// -----------------------------------------------------------------------------
// wrapped Context menu adding menuitems and do a callback
DefineEngineFunction(ImContextMenu, void, (
    const char* contextId
    , const char* ItemsTabSeparated
    , const char* callbackFunctionName),
    ("", ""), // Default to empty string if not provided
                     "Opens a context menu on right-click for the previous widget.\n"
                     "@param contextId Unique ID for the popup (optional)\n"
                     "@param ItemsTabSeparated TAB-separated list of menu items\n"
                     "@param callbackFunctionName Script function  (not method!) called on click (receives index and item name)\n"
) {
    if (!ItemsTabSeparated || ItemsTabSeparated[0] == '\0') {
        return;
    }
    const char* popupId = (contextId && contextId[0] != '\0') ? contextId : nullptr;
    if (ImGui::BeginPopupContextItem(popupId)) {
        U32 count = StringUnit::getUnitCount(ItemsTabSeparated, "\t");

        for (U32 i = 0; i < count; ++i) {
            const char* item = StringUnit::getUnit(ItemsTabSeparated, i, "\t");
            if (!item || item[0] == '\0') {
                continue;
            }
            if (dStrcmp(item, "-") == 0) {
                ImGui::Separator();
                continue;
            }
            if (ImGui::MenuItem(item)) {
                if (callbackFunctionName && callbackFunctionName[0] != '\0') {
                    char indexStr[16];
                    std::snprintf(indexStr, sizeof(indexStr), "%u", i);
                    Con::executef(callbackFunctionName, indexStr, item);
                }
            }
        }
        ImGui::EndPopup();
    }
}
// -----------------------------------------------------------------------------
// another wrapper for menuitems
DefineEngineFunction(ImMenuRows, S32, (const char* ItemsTabSeparated), ,
                     "Renders a TAB-separated list of items as MenuItems.\n"
                     "Returns the index of the clicked item, or -1 if nothing was clicked.\n"
){
    if (!ItemsTabSeparated || ItemsTabSeparated[0] == '\0') {
        return 0;
    }

    U32 count = StringUnit::getUnitCount(ItemsTabSeparated, "\t");
    S32 clickedIndex = -1;

    for (U32 i = 0; i < count; ++i) {
        const char* item = StringUnit::getUnit(ItemsTabSeparated, i, "\t");
        if (!item || item[0] == '\0') {
            continue;
        }
        if (dStrcmp(item, "-") == 0) {
            ImGui::Separator();
            continue;
        }
        if (ImGui::MenuItem(item)) {
            clickedIndex = static_cast<S32>(i);
        }
    }
    return clickedIndex;
}
// =============================================================================
// Mouse Status (Global & Last Item)
// =============================================================================

DefineEngineFunction(ImIsItemHovered, bool, (S32 flags), (0),
                     "Returns true if the last item is hovered by the mouse.\n"
                     "@param flags ImGuiHoveredFlags configuration options.\n") {
    return ImGui::IsItemHovered(flags);
}

DefineEngineFunction(ImIsItemClicked, bool, (S32 mouseButton), (0),
                     "Returns true if the last item was clicked.\n"
                     "@param mouseButton 0 = Left, 1 = Right, 2 = Middle.\n") {
    return ImGui::IsItemClicked(mouseButton);
}

DefineEngineFunction(ImIsItemDoubleClicked, bool, (), ,
                     "Returns true if the last item was double-clicked.\n") {
    // ImGui lacks a direct 'IsItemDoubleClicked', we check hover + double click status
    return ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left);
}

DefineEngineFunction(ImIsMouseClicked, bool, (S32 mouseButton, bool repeat), (0, false),
                     "Returns true if the mouse button went from down to up in this frame globally.\n") {
    return ImGui::IsMouseClicked(mouseButton, repeat);
}

DefineEngineFunction(ImIsMouseDown, bool, (S32 mouseButton), (0),
                     "Returns true if the mouse button is currently held down globally.\n") {
    return ImGui::IsMouseDown(mouseButton);
}
// =============================================================================
// Mouse Status (Global & Positional)
// =============================================================================

DefineEngineFunction(ImIsMouseReleased, bool, (S32 mouseButton), (0),
                     "Returns true if the mouse button went from down to up in this frame globally.\n") {
    return ImGui::IsMouseReleased(mouseButton);
}

DefineEngineFunction(ImIsMouseDoubleClicked, bool, (S32 mouseButton), (0),
                     "Returns true if the mouse button was double-clicked globally.\n") {
    return ImGui::IsMouseDoubleClicked(mouseButton);
}

DefineEngineFunction(ImIsMouseReleasedWithDelay, bool, (S32 mouseButton, F32 delay), (0, -1.0f),
                     "Returns true for a delayed mouse release event.\n") {
    // If delay is negative or left default, automatically match ImGui's double-click window timing
    if (delay < 0.0f) {
        delay = ImGui::GetIO().MouseDoubleClickTime;
    }
    return ImGui::IsMouseReleasedWithDelay(mouseButton, delay);
}

DefineEngineFunction(ImGetMouseClickedCount, S32, (S32 mouseButton), (0),
                     "Returns the number of successive mouse clicks recorded at the moment a click happens.\n") {
    return ImGui::GetMouseClickedCount(mouseButton);
}

DefineEngineFunction(ImIsMouseHoveringRect, bool, (ImVec2 r_min, ImVec2 r_max, bool clip), (true),
                     "Checks if the mouse is hovering a specific global bounding box.\n") {
    return ImGui::IsMouseHoveringRect(r_min, r_max, clip);
}

DefineEngineFunction(ImIsMousePosValid, bool, (String mousePosStr), (""),
                     "Returns true if the specified position (or current frame coordinate) is valid.\n") {
    if (mousePosStr.isEmpty()) {
        return ImGui::IsMousePosValid(nullptr);
    }

    // Parse vector manually if a specific coordinate string was provided to script
    ImVec2 pos(0.0f, 0.0f);
    dSscanf(mousePosStr.c_str(), "%f %f", &pos.x, &pos.y);
    return ImGui::IsMousePosValid(&pos);
}

DefineEngineFunction(ImGetMousePos, ImVec2, (), ,
                     "Returns the global screen coordinates of the mouse cursor.\n") {
    return ImGui::GetMousePos();
}

DefineEngineFunction(ImGetMousePosOnOpeningCurrentPopup, ImVec2, (), ,
                     "Returns the mouse coordinates captured exactly at the moment the current popup opened.\n") {
    return ImGui::GetMousePosOnOpeningCurrentPopup();
}

DefineEngineFunction(ImIsMouseDragging, bool, (S32 mouseButton, F32 lockThreshold), (0, -1.0f),
                     "Returns true if the mouse is actively dragging past a specified motion threshold.\n") {
    return ImGui::IsMouseDragging(mouseButton, lockThreshold);
}

DefineEngineFunction(ImGetMouseDragDelta, ImVec2, (S32 mouseButton, F32 lockThreshold), (0, -1.0f),
                     "Returns the total pixel distance shifted since dragging began.\n") {
    return ImGui::GetMouseDragDelta(mouseButton, lockThreshold);
}

DefineEngineFunction(ImResetMouseDragDelta, void, (S32 mouseButton), (0),
                     "Resets the mathematical baseline origin for the current drag session to the current cursor spot.\n") {
    ImGui::ResetMouseDragDelta(mouseButton);
}

DefineEngineFunction(ImSetNextFrameWantCaptureMouse, void, (bool wantCaptureMouse), ,
                     "Force-overrides the application-wide io.WantCaptureMouse layout flag for the next viewport pass.\n") {
    ImGui::SetNextFrameWantCaptureMouse(wantCaptureMouse);
}

// =============================================================================
// Keyboard & Shortcuts
// =============================================================================

DefineEngineFunction(ImIsKeyDown, bool, (S32 imguiKey), ,
                     "Returns true if the specific ImGuiKey is currently held down.\n"
                     "@param imguiKey The native ImGuiKey enum integer value.\n") {
    return ImGui::IsKeyDown(static_cast<ImGuiKey>(imguiKey));
}

DefineEngineFunction(ImIsKeyPressed, bool, (S32 imguiKey, bool repeat), (true),
                     "Returns true if the specific ImGuiKey was pressed down this frame.\n") {
    return ImGui::IsKeyPressed(static_cast<ImGuiKey>(imguiKey), repeat);
}

DefineEngineFunction(ImShortcut, bool, (S32 imguiKeyChord),,
                     "Evaluates a full key chord shortcut (e.g., Ctrl+S).\n"
                     "Automatically handles modifier routing and avoids execution if an input text field is active.\n"
                     "@param imguiKeyChord ImGuiKey combined with modifiers like ImGuiMod_Ctrl.\n") {
    ImGuiKey key = static_cast<ImGuiKey>(imguiKeyChord & ~ImGuiMod_Mask_);

    if (!ImGui::IsKeyPressed(key)) {
        return false;
    }

    bool reqCtrl  = (imguiKeyChord & ImGuiMod_Ctrl)  != 0;
    bool reqShift = (imguiKeyChord & ImGuiMod_Shift) != 0;
    bool reqAlt   = (imguiKeyChord & ImGuiMod_Alt)   != 0;
    bool reqSuper = (imguiKeyChord & ImGuiMod_Super) != 0;

    ImGuiIO& io = ImGui::GetIO();

    if (io.KeyCtrl  != reqCtrl)  return false;
    if (io.KeyShift != reqShift) return false;
    if (io.KeyAlt   != reqAlt)   return false;
    if (io.KeySuper != reqSuper) return false;

    if (ImGui::GetActiveID() != 0) {
        return false;
    }

    return true;
}


// =============================================================================
// Active Focus / State
// =============================================================================

DefineEngineFunction(ImIsItemActive, bool, (), ,
                     "Returns true if the last item is currently active (e.g., being dragged, slider adjusting, input typed into).\n") {
    return ImGui::IsItemActive();
}

DefineEngineFunction(ImIsItemFocused, bool, (), ,
                     "Returns true if the last item has keyboard focus.\n") {
    return ImGui::IsItemFocused();
}

// =============================================================================
// Window DrawList API
// =============================================================================
DefineEngineFunction(ImDrawLine, void, (F32 p1_x, F32 p1_y, F32 p2_x, F32 p2_y, ImVec4 color, F32 thickness), (1.0f),
                     "Draws a line using raw coordinates and a native ImVec4 struct.\n") {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // Direct translation using your inline helper and ImGui's internal packing
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    drawList->AddLine(ImVec2(p1_x, p1_y), ImVec2(p2_x, p2_y), packedColor, thickness);
}

DefineEngineFunction(ImDrawRect, void, (F32 min_x, F32 min_y, F32 max_x, F32 max_y, ImVec4 color, F32 rounding, S32 flags, F32 thickness), (0.0f, 0, 1.0f),
                     "Draws an unfilled rectangle using flat coordinates.\n") {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    drawList->AddRect(ImVec2(min_x, min_y), ImVec2(max_x, max_y), packedColor, rounding, flags, thickness);
}

DefineEngineFunction(ImDrawRectFilled, void, (F32 min_x, F32 min_y, F32 max_x, F32 max_y, ImVec4 color, F32 rounding, S32 flags), (0.0f, 0),
                     "Draws a filled rectangle using flat coordinates.\n") {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    drawList->AddRectFilled(ImVec2(min_x, min_y), ImVec2(max_x, max_y), packedColor, rounding, flags);
}

DefineEngineFunction(ImDrawCircle, void, (F32 center_x, F32 center_y, F32 radius, ImVec4 color, S32 segments, F32 thickness), (0, 1.0f),
                     "Draws an unfilled circle using flat coordinates.\n") {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    drawList->AddCircle(ImVec2(center_x, center_y), radius, packedColor, segments, thickness);
}

DefineEngineFunction(ImDrawCircleFilled, void, (F32 center_x, F32 center_y, F32 radius, ImVec4 color, S32 segments), (0),
                     "Draws a filled circle using flat coordinates.\n") {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    drawList->AddCircleFilled(ImVec2(center_x, center_y), radius, packedColor, segments);
}

DefineEngineFunction(ImDrawText, void, (F32 pos_x, F32 pos_y, ImVec4 color, const char* text), ,
    "Draws a text string directly onto the current window draw list using flat coordinates.\n"
    "@param pos_x X position on screen.\n"
    "@param pos_y Y position on screen.\n"
    "@param color Native ImVec4 struct.\n"
    "@param text The string message to draw.\n") {
    if (!text || text[0] == '\0') {
        return;
    }

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 packedColor = ImGui::ColorConvertFloat4ToU32(color);

    // Renders using the default active font and font size
    drawList->AddText(ImVec2(pos_x, pos_y), packedColor, text);
}


// =============================================================================
//  ImGui Tables
// =============================================================================
DefineEngineFunction(ImBeginTable, bool, (const char* str_id, S32 column, S32 flags, F32 outer_size_x, F32 outer_size_y, F32 inner_width), (0, 0.0f, 0.0f, 0.0f),
            "Begins a ImGui table framework.\n"
            "Only call ImEndTable() if this returns true.\n"
            "@param flags Combination of ImGuiTableFlags enums.\n") {
    return ImGui::BeginTable(str_id, column, flags, ImVec2(outer_size_x, outer_size_y), inner_width);
}

DefineEngineFunction(ImEndTable, void, (), ,
        "Only call if ImBeginTable() returned true.\n") {
    ImGui::EndTable();
}

DefineEngineFunction(ImTableSetupColumn, void, (const char* label, S32 flags, F32 init_width_or_weight, S32 user_id), (0, 0.0f, 0),
        "Submits configuration properties for a single column. Must be called before ImTableHeadersRow().\n"
        "@param flags Combination of ImGuiTableColumnFlags enums.\n") {
    ImGui::TableSetupColumn(label, flags, init_width_or_weight, static_cast<ImGuiID>(user_id));
}

DefineEngineFunction(ImTableHeadersRow, void, (), ,
        "Submits a header row layout automatically based on your ImTableSetupColumn definitions.\n") {
    ImGui::TableHeadersRow();
}

DefineEngineFunction(ImTableNextRow, void, (S32 row_flags, F32 min_row_height), (0, 0.0f),
        "Appends a new row to the table grid layout.\n") {
    ImGui::TableNextRow(row_flags, min_row_height);
}

DefineEngineFunction(ImTableSetColumnIndex, bool, (S32 column_index), ,
        "Moves the cell cursor to the specific column index within the current row.\n"
        "Returns true if the column is visible and should be rendered.\n") {
    return ImGui::TableSetColumnIndex(column_index);
}

DefineEngineFunction(ImTableSetupScrollFreeze, void, (S32 cols, S32 rows), ,
        "Freezes specific top rows or left columns so they stay visible when scrolling.\n") {
    ImGui::TableSetupScrollFreeze(cols, rows);
}

// =============================================================================
//  ImGui TreeNode / CollapsingHeader
// =============================================================================

DefineEngineFunction(ImCollapsingHeader, bool, (const char* label, S32 treeNodeFlags), (0),
        "Creates a banner that toggles the visibility of the elements inside it.\n"
        "@param label The text displayed on the header.\n"
        "@param treeNodeFlags Example: ImGuiTreeNodeFlags_DefaultOpen, the header starts opened.\n") {

    return ImGui::CollapsingHeader(label, treeNodeFlags);
}

DefineEngineFunction(ImTreeNode, bool, (const char* label,  S32 treeNodeFlags), (0),
        "Creates a tree node with an arrow that can be expanded or collapsed.\n"
        "Must be paired with ImGuiTreePop if it returns true.\n"
        "@param label The text displayed on the node.\n"
        "@param treeNodeFlags Example: ImGuiTreeNodeFlags_DefaultOpen, the node starts expanded.\n") {

    // default ?! ImGuiTreeNodeFlags_DefaultOpen;

    return ImGui::TreeNodeEx(label, treeNodeFlags);
}

DefineEngineFunction(ImTreePop, void, (), ,
        "Closes a previously opened ImGuiTreeNode. Must be called if ImGuiTreeNode returned true.\n") {
    ImGui::TreePop();
}
// ============================================================================
// Parameters stacks (shared)
// ============================================================================

DefineEngineFunction(ImPushStyleColor, void, (S32 idx, ImVec4 col), ,
        "Modifies a style color using an ImVec4.\n"
        "@param idx The ImGuiCol_ constant.\n"
        "@param col The color vector (RGBA) as ImVec4.\n") {
    ImGui::PushStyleColor((ImGuiCol)idx, col);
}

DefineEngineFunction(ImPopStyleColor, void, (S32 count), (1),
        "Pops one or multiple colors from the style color stack.\n"
        "@param count Optional. Number of colors to pop from the stack.\n") {
    ImGui::PopStyleColor(count);
}

DefineEngineFunction(ImPushStyleVar, void, (S32 idx, F32 val), ,
        "Modifies a style F32 variable.\n"
        "@param idx The ImGuiStyleVar_ constant.\n"
        "@param val The F32 value to set.\n") {
    ImGui::PushStyleVar((ImGuiStyleVar)idx, val);
}

DefineEngineFunction(ImPushStyleVarVec, void, (S32 idx, ImVec2 val), ,
        "Modifies a style ImVec2 variable.\n"
        "@param idx The ImGuiStyleVar_ constant.\n"
        "@param val The ImVec2 vector value to set.\n") {
    ImGui::PushStyleVar((ImGuiStyleVar)idx, val);
}

DefineEngineFunction(ImPushStyleVarX, void, (S32 idx, F32 val_x), ,
        "Modifies the X component of a style ImVec2 variable.\n"
        "@param idx The ImGuiStyleVar_ constant.\n"
        "@param val_x The F32 value for the X component.\n") {
    ImGui::PushStyleVarX((ImGuiStyleVar)idx, val_x);
}

DefineEngineFunction(ImPushStyleVarY, void, (S32 idx, F32 val_y), ,
        "Modifies the Y component of a style ImVec2 variable.\n"
        "@param idx The ImGuiStyleVar_ constant.\n"
        "@param val_y The F32 value for the Y component.\n") {
    ImGui::PushStyleVarY((ImGuiStyleVar)idx, val_y);
}

DefineEngineFunction(ImPopStyleVar, void, (S32 count), (1),
        "Pops one or multiple variables from the style variable stack.\n"
        "@param count Optional. Number of variables to pop from the stack.\n") {
    ImGui::PopStyleVar(count);
}

DefineEngineFunction(ImPushItemFlag, void, (S32 option, bool enabled), ,
        "Modifies a specified shared item flag (internal/advanced ImGui features).\n"
        "@param option The ImGuiItemFlags_ constant.\n"
        "@param enabled Whether the flag should be active or inactive.\n") {
    ImGui::PushItemFlag((ImGuiItemFlags)option, enabled);
}

DefineEngineFunction(ImPopItemFlag, void, (), ,
        "Pops an item flag from the item flags stack.\n") {
    ImGui::PopItemFlag();
}

// ============================================================================
// Parameters stacks (current window)
// ============================================================================

DefineEngineFunction(ImPushItemWidth, void, (F32 item_width), ,
        "Pushes the width of items for common large widgets. >0.0f: pixels, <0.0f: align to right.\n"
        "@param item_width The width configuration.\n") {
    ImGui::PushItemWidth(item_width);
}

DefineEngineFunction(ImPopItemWidth, void, (), ,
        "Pops an item width from the item width stack.\n") {
    ImGui::PopItemWidth();
}

DefineEngineFunction(ImSetNextItemWidth, void, (F32 item_width), ,
        "Sets the width of the NEXT common large widget only.\n"
        "@param item_width The width configuration.\n") {
    ImGui::SetNextItemWidth(item_width);
}

DefineEngineFunction(ImCalcItemWidth, F32, (), ,
        "Calculates the width of the item given pushed settings and current cursor position.\n") {
    return ImGui::CalcItemWidth();
}

DefineEngineFunction(ImPushTextWrapPos, void, (F32 wrap_local_pos_x), (0.0f),
        "Pushes word-wrapping position for text commands. <0.0f: no wrap, 0.0f: wrap to window end.\n"
        "@param wrap_local_pos_x Optional. Position in window local space.\n") {
    ImGui::PushTextWrapPos(wrap_local_pos_x);
}

DefineEngineFunction(ImPopTextWrapPos, void, (), ,
        "Pops a text wrap position from the stack.\n") {
    ImGui::PopTextWrapPos();
}

// -----------------------------------------------------------------------------
DefineEngineFunction(ImPushFontSize, void, (F32 sizeInPixels),
    , "Push a dynamic pixel size for the current font context.\n"
      " - replacement for SetWindowFontScale, dont forget to call ImPopFontSize")
{
    ImGui::PushFont(nullptr, sizeInPixels);
}
// -----------------------------------------------------------------------------
DefineEngineFunction(ImPopFontSize, void, (), , "Pop the current dynamic font size context.")
{
    ImGui::PopFont();
}
// -----------------------------------------------------------------------------
// Text Utilities
// IMGUI_API ImVec2        CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
// -----------------------------------------------------------------------------
DefineEngineFunction(ImCalcTextSize, ImVec2, (const char* text, bool hideTextAfterDoubleHash, F32 wrapWidth), (false, -1.0f),
                     "Calculate the bounding size of a text string in pixels based on the current font and scale configuration.")
{
    if (!text || text[0] == '\0') {
        return ImVec2(0.0f, 0.0f);
    }

    return ImGui::CalcTextSize(text, nullptr, hideTextAfterDoubleHash, wrapWidth);
}


// ============================================================================
// Cursor
// ============================================================================
// IMGUI_API ImVec2        GetCursorScreenPos();                                           // cursor position, absolute coordinates. THIS IS YOUR BEST FRIEND (prefer using this rather than GetCursorPos(), also more useful to work with ImDrawList API).
DefineEngineFunction(ImGetCursorScreenPos, ImVec2, (), , "Get absolute cursor position in screen coordinates.")
{
    return ImGui::GetCursorScreenPos();
}

// -----------------------------------------------------------------------------
// IMGUI_API void          SetCursorScreenPos(const ImVec2& pos);                          // cursor position, absolute coordinates. THIS IS YOUR BEST FRIEND.
DefineEngineFunction(ImSetCursorScreenPos, void, (ImVec2 pos), , "Set absolute cursor position in screen coordinates.")
{
    ImGui::SetCursorScreenPos(pos);
}
DefineEngineFunction(ImSetCursorScreenPosXY, void, (F32 x, F32 y), , "Set absolute cursor position in screen coordinates.")
{
    ImGui::SetCursorScreenPos({x,y});
}
// -----------------------------------------------------------------------------
// IMGUI_API ImVec2        GetContentRegionAvail();                                        // available space from current position. THIS IS YOUR BEST FRIEND.
DefineEngineFunction(ImGetContentRegionAvail, ImVec2, (), , "Get available space from the current layout position.")
{
    return ImGui::GetContentRegionAvail();
}

// -----------------------------------------------------------------------------
// IMGUI_API ImVec2        GetCursorStartPos();                                            // [window-local] initial cursor position, in window-local coordinates. Call GetCursorScreenPos() after Begin() to get the absolute coordinates version.
DefineEngineFunction(ImGetCursorStartPos, ImVec2, (), , "Get initial cursor placement in window-local coordinates.")
{
    return ImGui::GetCursorStartPos();
}
// -----------------------------------------------------------------------------
// IMGUI_API ImVec2        GetCursorPos();                                                 // [window-local] cursor position in window-local coordinates. This is not your best friend.
DefineEngineFunction(ImGetCursorPos, ImVec2, (), , "Get window-local cursor position.")
{
    return ImGui::GetCursorPos();
}
// -----------------------------------------------------------------------------
// IMGUI_API void          SetCursorPos(const ImVec2& local_pos);                          // [window-local] "
DefineEngineFunction(ImSetCursorPos, void, (ImVec2 local_pos), , "Set window-local cursor position.")
{
    ImGui::SetCursorPos(local_pos);
}
// -----------------------------------------------------------------------------
// IMGUI_API float         GetCursorPosX();                                                // [window-local] "
DefineEngineFunction(ImGetCursorPosX, F32, (), , "Get window-local cursor X position.")
{
    return ImGui::GetCursorPosX();
}

// -----------------------------------------------------------------------------
// IMGUI_API void          SetCursorPosX(float local_x);                                   // [window-local] "
DefineEngineFunction(ImSetCursorPosX, void, (F32 local_x), , "Set window-local cursor X position.")
{
    ImGui::SetCursorPosX(local_x);
}

// -----------------------------------------------------------------------------
// IMGUI_API float         GetCursorPosY();                                                // [window-local] "
DefineEngineFunction(ImGetCursorPosY, F32, (), , "Get window-local cursor Y position.")
{
    return ImGui::GetCursorPosY();
}

// -----------------------------------------------------------------------------
// IMGUI_API void          SetCursorPosY(float local_y);                                   // [window-local] "
DefineEngineFunction(ImSetCursorPosY, void, (F32 local_y), , "Set window-local cursor Y position.")
{
    ImGui::SetCursorPosY(local_y);
}


// -----------------------------------------------------------------------------
ConsoleFunctionGroupEnd(ImGui);
// -----------------------------------------------------------------------------
