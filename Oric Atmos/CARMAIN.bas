#labels
#optimize

Start:+1:0
    X=5: Y=13
    REPEAT
        USER 1, DEF #6500
        USER 1, X X, Y Y
        GET K$
        IF K$=CHR$(8) AND X>0 THEN X=X-1
        IF K$=CHR$(9) AND X<5 THEN X=X+1
        IF K$=CHR$(11) AND Y>0 THEN Y=Y-1
        IF K$=CHR$(10) AND Y<13 THEN Y=Y+1
    UNTIL K$=CHR$(13)
    INK 7
    END