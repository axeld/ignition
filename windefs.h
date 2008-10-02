/*
 * Copyright ©1996-2008 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */
#ifndef IGN_WINDEFS_H
#define IGN_WINDEFS_H
 

#include "windows.h"


// handlewindows.c
extern void __asm closeNotesWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm handleNotesIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseFormelWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleFormelIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseBorderWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleBorderIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePreviewIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseDiagramWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleDiagramIDCMP(reg (a0) struct TagItem *);
extern void __asm HandlePageSetupIDCMP(reg (a0) struct TagItem *tag);
extern void __asm HandleDocInfoIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseDocumentWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleDocumentIDCMP(reg (a0) struct TagItem *);
extern void __asm HandlePageIDCMP(reg (a0) struct TagItem *);
extern void __asm handleCellSizeIDCMP(reg (a0) struct TagItem *);
extern void __asm handleZoomIDCMP(reg (a0) struct TagItem *);
extern void __asm closeGClassesWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm handleGClassesIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseObjectWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleObjectIDCMP(reg (a0) struct TagItem *);
extern void __asm handleCommandIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseFileTypeWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closeCellWin(reg (a0) struct Window *win,reg (d0) BOOL clean);
extern void __asm handleCellIDCMP(reg (a0) struct TagItem *);
extern void __asm handleSetNameIDCMP(reg (a0) struct TagItem *tag);
extern void __asm handleSetTitleIDCMP(reg (a0) struct TagItem *tag);
extern void __asm CloseScriptsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleScriptsIDCMP(reg (a0) struct TagItem *tag);

// handleprefs.c
extern void __asm handlePrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm HandlePrefChoiceIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefDispIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefMenuIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefIconIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePressKeyIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleKeyboardPrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefScreenIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefCmdsIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefNamesIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleFormatPrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleFilePrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleTablePrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefColorsIDCMP(reg (a0) struct TagItem *);
extern void __asm handleDefineCmdIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleSystemPrefsIDCMP(reg (a0) struct TagItem *);
extern void __asm handlePrefContextIDCMP(reg (a0) struct TagItem *tag);
extern void __asm closePrefsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm ClosePrefChoiceWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefDispWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm CloseKeyboardPrefsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefMenuWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefIconWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefColorsWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm CloseFilePrefsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm CloseTablePrefsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefNamesWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm CloseFormatPrefsWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefCmdsWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closeDefineCmdWin(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm closePrefContextWindow(reg (a0) struct Window *win,reg (d0) BOOL clean);

// database.c
extern void __asm CloseDatabaseWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleDatabaseIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseMaskWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleMaskIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseIndexWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandleIndexIDCMP(reg (a0) struct TagItem *);
extern void __asm HandleFilterIDCMP(reg (a0) struct TagItem *);
extern void __asm CloseFilterWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm CreateDatabaseGadgets(reg (a0) struct winData *wd);
extern void __asm CreateMaskGadgets(reg (a0) struct winData *wd);
extern void __asm CreateIndexGadgets(reg (a0) struct winData *wd);
extern void __asm CreateFilterGadgets(reg (a0) struct winData *wd);

// search.c
extern void __asm CreateFindReplaceGadgets(reg (a0) struct winData *wd);
extern void __asm CloseFindReplaceWindow(reg (a0) struct Window *win,reg (d0) BOOL clean);
extern void __asm HandleFindReplaceIDCMP(reg (a0) struct TagItem *);

// paste.c
extern void CreateClipboardGadgets(struct winData *wd, long wid, long hei);
extern void __asm handleClipIDCMP(reg (a0) struct TagItem *);

// printer.c
extern void __asm ClosePrinterWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandlePrinterIDCMP(reg (a0) struct TagItem *);
extern void __asm CreatePrinterGadgets(reg (a0) struct winData *wd);
extern void __asm ClosePrintStatusWindow(reg (a0) struct Window *,reg (d0) BOOL);
extern void __asm HandlePrintStatusIDCMP(reg (a0) struct TagItem *);
extern void __asm CreatePrintStatusGadgets(reg (a0) struct winData *wd);

// prefsgadgets.c
extern void CreatePrefsGadgets(struct winData *wd, long wid, long hei);
extern void __asm CreatePrefChoiceGads(reg (a0) struct winData *wd);
extern void __asm CreatePrefDispGads(reg (a0) struct winData *wd);
extern void __asm CreatePrefScreenGads(reg (a0) struct winData *wd);
extern void __asm CreatePrefMenuGads(reg (a0) struct winData *wd);
extern void CreateKeyboardPrefsGadgets(struct winData *wd, long width, long height);
extern void __asm CreatePrefIconGads(reg (a0) struct winData *wd);
extern void __asm CreatePrefCmdsGads(reg (a0) struct winData *wd);
extern void __asm CreatePrefNamesGads(reg (a0) struct winData *wd);
extern void __asm CreateFormatPrefsGadgets(reg (a0) struct winData *wd);
extern void __asm CreateFilePrefsGadgets(reg (a0) struct winData *wd);
extern void __asm CreateTablePrefsGadgets(reg (a0) struct winData *wd);
extern void __asm CreatePrefColorsGads(reg (a0) struct winData *wd);
extern void __asm CreateDefineCmdGads(reg (a0) struct winData *wd);
extern void __asm CreatePressKeyGads(reg (a0) struct winData *wd);
extern void __asm CreateSystemPrefsGadgets(reg (a0) struct winData *wd);
extern void __asm CreatePrefContextGads(reg (a0) struct winData *wd);

// gadgets.c
extern void __asm CreateInfoGadgets(reg (a0) struct winData *wd);
extern void __asm CreateBorderGadgets(reg (a0) struct winData *wd);
extern void __asm CreateDiagramGadgets(reg (a0) struct winData *wd);
extern void __asm CreatePaletteGadgets(reg (a0) struct winData *wd);
extern void __asm CreateFormelGadgets(reg (a0) struct winData *wd);
extern void __asm CreateFormatGadgets(reg (a0) struct winData *wd);
extern void __asm CreatePageSetupGadgets(reg (a0) struct winData *wd);
extern void __asm CreateDocInfoGadgets(reg (a0) struct winData *wd);
extern void __asm CreateDocumentGadgets(reg (a0) struct winData *wd);
extern void __asm CreatePageGadgets(reg (a0) struct winData *wd);
extern void __asm CreateAlignGadgets(reg (a0) struct winData *wd);
extern void __asm CreateCellSizeGadgets(reg (a0) struct winData *wd);
extern void __asm CreateZoomGadgets(reg (a0) struct winData *wd);
extern void __asm CreateColorsGadgets(reg (a0) struct winData *wd);
extern void __asm CreateObjectGadgets(reg (a0) struct winData *wd);
extern void __asm CreateCommandGadgets(reg (a0) struct winData *wd);
extern void __asm CreateFileTypeGadgets(reg (a0) struct winData *wd);
extern void __asm CreateCellGadgets(reg (a0) struct winData *wd);
extern void __asm CreateSetNameGadgets(reg (a0) struct winData *wd);

extern void CreateGClassesGadgets(struct winData *wd, long wid, long hei);
extern void CreateScriptsGadgets(struct winData *wd, long wid, long hei);
extern void CreateNotesGadgets(struct winData *wd, long wid, long hei);

// initwindows.c
extern void __asm InitBorderWindow(reg (a0) struct winData *wd);
extern void __asm InitDatabaseWindow(reg (a0) struct winData *wd);
extern void __asm InitDiagramWindow(reg (a0) struct winData *wd);
extern void __asm InitDocumentWindow(reg (a0) struct winData *wd);
extern void __asm InitFileTypeWindow(reg (a0) struct winData *wd);
extern void __asm InitFindReplaceWindow(reg (a0) struct winData *wd);
extern void __asm InitFormelWindow(reg (a0) struct winData *wd);
extern void __asm InitIndexWindow(reg (a0) struct winData *wd);
extern void __asm InitFilterWindow(reg (a0) struct winData *wd);
extern void __asm InitMaskWindow(reg (a0) struct winData *wd);
extern void __asm initPrefNames(reg (a0) struct winData *wd);
extern void __asm initNotes(reg (a0) struct winData *wd);
extern void __asm InitObjectWindow(reg (a0) struct winData *wd);
extern void __asm initPrefChoiceWindow(reg (a0) struct winData *wd);
extern void __asm initPrefColors(reg (a0) struct winData *wd);
extern void __asm InitFilePrefsWindow(reg (a0) struct winData *wd);
extern void __asm InitFormatPrefsWindow(reg (a0) struct winData *wd);
extern void __asm initPrefIcon(reg (a0) struct winData *wd);
extern void __asm InitKeyboardPrefsWindow(reg (a0) struct winData *wd);
extern void __asm initPrefContext(reg (a0) struct winData *wd);
extern void __asm initPrefMenu(reg (a0) struct winData *wd);
extern void __asm InitTablePrefsWindow(reg (a0) struct winData *wd);
extern void __asm InitPrinterWindow(reg (a0) struct winData *wd);
extern void __asm InitPrintStatusWindow(reg (a0) struct winData *wd);


struct CreateWinData gCreateWinData[] = {
/**************************** misc ****************************/

	{MSG_INFO_TITLE, NULL,													/* WDT_INFO */
	 NULL, NULL, NULL, CreateInfoGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_MOUSEBUTTONS},
	{MSG_CLIPBOARD_TITLE, "clibboard",										/* WDT_CLIP */
	 handleClipIDCMP, NULL, NULL, NULL, CreateClipboardGadgets,
     APPIDCMP | LISTVIEWIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE},
	{MSG_FIND_TITLE, "search",												/* WDT_FIND */
	 HandleFindReplaceIDCMP, CloseFindReplaceWindow, InitFindReplaceWindow, CreateFindReplaceGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_SEARCH_REPLACE_TITLE, "replace",									/* WDT_REPLACE */
	 HandleFindReplaceIDCMP, CloseFindReplaceWindow, InitFindReplaceWindow, CreateFindReplaceGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PRINT_TITLE, "print",												/* WDT_PRINTER */
	 HandlePrinterIDCMP, ClosePrinterWindow, InitPrinterWindow, CreatePrinterGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PRINT_STATUS_TITLE, "printstatus",									/* WDT_PRINTSTATUS */
	 HandlePrintStatusIDCMP, ClosePrintStatusWindow, InitPrintStatusWindow, CreatePrintStatusGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_FILE_TYPE_TITLE, "filetype",										/* WDT_FILETYPE */
	 NULL, CloseFileTypeWindow, InitFileTypeWindow, CreateFileTypeGadgets, NULL,
     LISTVIEWIDCMP | IDCMP_VANILLAKEY | IDCMP_RAWKEY},
	{MSG_EXECUTE_COMMAND_TITLE, "command",									/* WDT_COMMAND */
	 handleCommandIDCMP,NULL,NULL,CreateCommandGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},

/**************************** prefs ****************************/

	{MSG_PREFS_TITLE, "prefs",												/* WDT_PREFS */
	 handlePrefsIDCMP, closePrefsWindow, NULL, NULL, CreatePrefsGadgets,
     APPIDCMP | LISTVIEWIDCMP | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE | IDCMP_RAWKEY | IDCMP_VANILLAKEY},
	{MSG_PREFS_DISPLAY_TITLE, "prefs_display",								/* WDT_PREFDISP */
	 handlePrefDispIDCMP,closePrefDispWin,NULL,CreatePrefDispGads, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{MSG_PREFS_SCREEN_TITLE, "prefs_screen",								/* WDT_PREFSCREEN */
	 handlePrefScreenIDCMP,NULL,NULL,CreatePrefScreenGads, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{MSG_PREFS_PALETTE_TITLE, "prefs_palette",								/* WDT_PREFCOLORS */
	 handlePrefColorsIDCMP,closePrefColorsWin,initPrefColors,CreatePrefColorsGads, NULL,
     APPIDCMP | LISTVIEWIDCMP | IDCMP_IDCMPUPDATE},
	{MSG_PREFS_ICONBAR_TITLE, "prefs_iconbar",								/* WDT_PREFICON */
	 handlePrefIconIDCMP,closePrefIconWin,initPrefIcon,CreatePrefIconGads, NULL,
     APPIDCMP | LISTVIEWIDCMP | DRAGIDCMP},
	{MSG_PREFS_SHEET_TITLE, "prefs_table",									/* WDT_PREFTABLE */
	 HandleTablePrefsIDCMP, CloseTablePrefsWindow, InitTablePrefsWindow, CreateTablePrefsGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_FILE_TITLE, "prefs_file",									/* WDT_PREFFILE */
	 HandleFilePrefsIDCMP, CloseFilePrefsWindow, InitFilePrefsWindow, CreateFilePrefsGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{NULL},																	/* WDT_PREFPRINTER */
	{MSG_PREFS_COMMANDS_TITLE, "prefs_commands",							/* WDT_PREFCMDS */
	 handlePrefCmdsIDCMP,closePrefCmdsWin,NULL,CreatePrefCmdsGads, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_FORMATS_TITLE, "prefs_formats",								/* WDT_PREFFORMAT */
	 HandleFormatPrefsIDCMP, CloseFormatPrefsWindow, InitFormatPrefsWindow, CreateFormatPrefsGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_DEFINE_COMMAND_TITLE, "prefs_define_command",				/* WDT_DEFINECMD */
	 handleDefineCmdIDCMP,closeDefineCmdWin,NULL,CreateDefineCmdGads, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_RECORD_KEY_TITLE, "prefs_record_key",						/* WDT_PRESSKEY */
	 handlePressKeyIDCMP,NULL,NULL,CreatePressKeyGads, NULL,
     APPIDCMP | IDCMP_GADGETUP},
	{MSG_PREFS_MENU_TITLE, "prefs_menu",									/* WDT_PREFMENU */
	 handlePrefMenuIDCMP,closePrefMenuWin,initPrefMenu,CreatePrefMenuGads, NULL,
     APPIDCMP | LISTVIEWIDCMP | DRAGIDCMP},
	{MSG_PREFS_KEYBOARD_TITLE, "prefs_keyboard",							/* WDT_PREFKEYS */
	 HandleKeyboardPrefsIDCMP, CloseKeyboardPrefsWindow, InitKeyboardPrefsWindow, NULL, CreateKeyboardPrefsGadgets,
	 APPIDCMP | LISTVIEWIDCMP | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE | DRAGIDCMP},
	{MSG_PREFS_SYSTEM_TITLE, "prefs_system",								/* WDT_PREFSYS */
	 HandleSystemPrefsIDCMP, NULL, NULL, CreateSystemPrefsGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_NAMES_TITLE, "prefs_names",									/* WDT_PREFNAMES */
	 handlePrefNamesIDCMP, closePrefNamesWin, initPrefNames, CreatePrefNamesGads, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PREFS_CONTEXT_MENUS_TITLE, "prefs_context_menus",					/* WDT_PREFCONTEXT */
	 handlePrefContextIDCMP,closePrefContextWindow,initPrefContext,CreatePrefContextGads, NULL,
     APPIDCMP | LISTVIEWIDCMP},
//  {NULL},                                                        /* WDT_PREFFONT/WDT_PREFTOOL */
    {NULL, "prefs_add_prefs",                                      /* WDT_PREFCHOICE */
	 HandlePrefChoiceIDCMP,ClosePrefChoiceWindow,initPrefChoiceWindow,CreatePrefChoiceGads, NULL,
     APPIDCMP | LISTVIEWIDCMP},

/**************************** map ****************************/

	{MSG_PAGE_TITLE, "page",												/* WDT_PAGE */
	 HandlePageIDCMP, NULL, NULL, CreatePageGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{MSG_DOCUMENT_TITLE, "document",										/* WDT_DOCUMENT */
	 HandleDocumentIDCMP, CloseDocumentWindow, InitDocumentWindow, CreateDocumentGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_PAGE_SETUP_TITLE, "page_setup",									/* WDT_PAGESETUP */
	 HandlePageSetupIDCMP,NULL,NULL,CreatePageSetupGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_DOCUMENT_INFO_TITLE, "doc_info",									/* WDT_DOCINFO */
	 HandleDocInfoIDCMP,NULL,NULL,CreateDocInfoGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_ZOOM_TITLE, "zoom",												/* WDT_ZOOM */
	 handleZoomIDCMP,NULL,NULL,CreateZoomGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{MSG_SCRIPTS_TITLE, "scripts",                                         	/* WDT_SCRIPTS */
	 HandleScriptsIDCMP, CloseScriptsWindow, NULL, NULL, CreateScriptsGadgets,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE},
	{MSG_CELL_TITLE_TITLE, "set_cell_title",								/* WDT_SETTITLE */
	 handleSetTitleIDCMP,NULL,NULL,CreateSetNameGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP},

/**************************** objects ****************************/

	{MSG_INSERT_OBJECT_TITLE, "insert_object",								/* WDT_GCLASSES */
	 handleGClassesIDCMP, closeGClassesWindow, NULL, NULL, CreateGClassesGadgets,
     APPIDCMP | LISTVIEWIDCMP | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE},
	{MSG_OBJECT_TITLE, "object",											/* WDT_OBJECT */
	 HandleObjectIDCMP, CloseObjectWindow, InitObjectWindow, CreateObjectGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_INTUITICKS},
	{MSG_DIAGRAM_TITLE, "create_diagram",									/* WDT_DIAGRAM */
	 HandleDiagramIDCMP, CloseDiagramWindow, InitDiagramWindow, CreateDiagramGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP | SLIDERIDCMP},
	{MSG_DIAGRAM_PREVIEW_TITLE, "diagram_preview",							/* WDT_PREVIEW */
	 handlePreviewIDCMP,NULL,NULL,NULL, NULL,
     APPIDCMP | IDCMP_NEWSIZE},
	{MSG_OBJECT_LIST_TITLE, "object_list",									/* WDT_GOBJECTS */
	 NULL,NULL,NULL,NULL, NULL,												/* not yet implemented */
     APPIDCMP | LISTVIEWIDCMP | SLIDERIDCMP},

/**************************** cell properties ****************************/

	{MSG_CELL_TITLE, "cell",												/* WDT_CELL */
	 handleCellIDCMP, closeCellWin, NULL, CreateCellGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_FRAME_TITLE, "frame",												/* WDT_BORDER */
	 HandleBorderIDCMP, CloseBorderWindow, InitBorderWindow, CreateBorderGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_INTUITICKS | IDCMP_MOUSEBUTTONS},
	{MSG_CELL_SIZE_TITLE, "cell_size",										/* WDT_CELLSIZE */
	 handleCellSizeIDCMP,NULL,NULL,CreateCellSizeGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP | IDCMP_GADGETDOWN},
	{MSG_NOTES_TITLE, "notes",												/* WDT_NOTES */
	 handleNotesIDCMP, closeNotesWin, NULL, NULL, CreateNotesGadgets,
     APPIDCMP | LISTVIEWIDCMP | IDCMP_SIZEVERIFY | IDCMP_NEWSIZE},

/**************************** database ****************************/

	{MSG_DBASE_INDEX_TITLE, "database_index",								/* WDT_INDEX */
	 HandleIndexIDCMP, CloseIndexWindow, InitIndexWindow, CreateIndexGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_DBASE_TITLE, "database",											/* WDT_DATABASE */
	 HandleDatabaseIDCMP, CloseDatabaseWindow, InitDatabaseWindow, CreateDatabaseGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_DBASE_MASK_TITLE, "database_mask",									/* WDT_MASK */
	 HandleMaskIDCMP, CloseMaskWindow, InitMaskWindow,CreateMaskGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_DBASE_FILTER_TITLE, "database_filter",								/* WDT_FILTER */
	 HandleFilterIDCMP, CloseFilterWindow, InitFilterWindow, CreateFilterGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},

/**************************** calculation ****************************/

	{MSG_FORMULA_TITLE, "formula",											/* WDT_FORMEL */
	 HandleFormelIDCMP, CloseFormelWindow, InitFormelWindow, CreateFormelGadgets, NULL,
     APPIDCMP | LISTVIEWIDCMP},
	{MSG_SET_NAME_TITLE, "set_name",										/* WDT_SETNAME */
	 handleSetNameIDCMP, NULL, NULL, CreateSetNameGadgets, NULL,
     APPIDCMP | IDCMP_GADGETUP}
};

#endif	/* IGN_WINDEFS_H */
																																							
