DEFINE VARIABLE cVar AS CHARACTER NO-UNDO. 
DEFINE VARIABLE iVar AS INTEGER INIT 3 NO-UNDO.

ASSIGN 
    cVar = "  Hello, Omphulusa!  ":U.
    
DISPLAY 
    "cVar: ":U + cVar FORMAT "x(50)":U SKIP
    "iVar: ":U + STRING(iVar) SKIP
    "Trimmed cVar: ":U + TRIM (cVar) FORMAT "x(50)":U
    "Right Trim: ":U + RIGHT-TRIM (cVar) FORMAT "x(50)":U
    "Left Trim: ":U + LEFT-TRIM (cVar) FORMAT "x(50)":U SKIP 
    "Replace: ":U + REPLACE ("&1
    ", cVar, "New cVar":U)
    .