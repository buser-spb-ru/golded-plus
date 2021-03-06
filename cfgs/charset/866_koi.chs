; $Id$
;
; This file is a charset conversion module in text form.
;
; This module converts russian codepages 866 to KOI8-R.
;
; Format: ID, version, level,
;         from charset, to charset,
;         128 entries: first & second byte
;	  "END"
; Lines beginning with a ";" or a ";" after the entries are comments
;
; Unkown characters are mapped to the "?" character.
;
; \ is the escape character: \0 means decimal zero,
; \dnnn where nnn is a decimal number is the ordinal value of the character
; \xnn where nn is a hexadecimal number
; e.g.: \d32 is the ASCII space character
; Two \\ is the character "\" itself.
;
0       ; ID number
0       ; version number
;
2       ; level number
CP866	; from charset
KOI8-R	; to charset
;
\0 \xe1	; CYRILLIC CAPITAL LETTER A
\0 \xe2	; CYRILLIC CAPITAL LETTER BE
\0 \xf7	; CYRILLIC CAPITAL LETTER VE
\0 \xe7	; CYRILLIC CAPITAL LETTER GHE
\0 \xe4	; CYRILLIC CAPITAL LETTER DE
\0 \xe5	; CYRILLIC CAPITAL LETTER IE
\0 \xf6	; CYRILLIC CAPITAL LETTER ZHE
\0 \xfa	; CYRILLIC CAPITAL LETTER ZE
\0 \xe9	; CYRILLIC CAPITAL LETTER I
\0 \xea	; CYRILLIC CAPITAL LETTER SHORT I
\0 \xeb	; CYRILLIC CAPITAL LETTER KA
\0 \xec	; CYRILLIC CAPITAL LETTER EL
\0 \xed	; CYRILLIC CAPITAL LETTER EM
\0 \xee	; CYRILLIC CAPITAL LETTER EN
\0 \xef	; CYRILLIC CAPITAL LETTER O
\0 \xf0	; CYRILLIC CAPITAL LETTER PE
\0 \xf2	; CYRILLIC CAPITAL LETTER ER
\0 \xf3	; CYRILLIC CAPITAL LETTER ES
\0 \xf4	; CYRILLIC CAPITAL LETTER TE
\0 \xf5	; CYRILLIC CAPITAL LETTER U
\0 \xe6	; CYRILLIC CAPITAL LETTER EF
\0 \xe8	; CYRILLIC CAPITAL LETTER HA
\0 \xe3	; CYRILLIC CAPITAL LETTER TSE
\0 \xfe	; CYRILLIC CAPITAL LETTER CHE
\0 \xfb	; CYRILLIC CAPITAL LETTER SHA
\0 \xfd	; CYRILLIC CAPITAL LETTER SHCHA
\0 \xff	; CYRILLIC CAPITAL LETTER HARD SIGN
\0 \xf9	; CYRILLIC CAPITAL LETTER YERU
\0 \xf8	; CYRILLIC CAPITAL LETTER SOFT SIGN
\0 \xfc	; CYRILLIC CAPITAL LETTER E
\0 \xe0	; CYRILLIC CAPITAL LETTER YU
\0 \xf1	; CYRILLIC CAPITAL LETTER YA
\0 \xc1	; CYRILLIC SMALL LETTER A
\0 \xc2	; CYRILLIC SMALL LETTER BE
\0 \xd7	; CYRILLIC SMALL LETTER VE
\0 \xc7	; CYRILLIC SMALL LETTER GHE
\0 \xc4	; CYRILLIC SMALL LETTER DE
\0 \xc5	; CYRILLIC SMALL LETTER IE
\0 \xd6	; CYRILLIC SMALL LETTER ZHE
\0 \xda	; CYRILLIC SMALL LETTER ZE
\0 \xc9	; CYRILLIC SMALL LETTER I
\0 \xca	; CYRILLIC SMALL LETTER SHORT I
\0 \xcb	; CYRILLIC SMALL LETTER KA
\0 \xcc	; CYRILLIC SMALL LETTER EL
\0 \xcd	; CYRILLIC SMALL LETTER EM
\0 \xce	; CYRILLIC SMALL LETTER EN
\0 \xcf	; CYRILLIC SMALL LETTER O
\0 \xd0	; CYRILLIC SMALL LETTER PE
\0 \x90	; LIGHT SHADE
\0 \x91	; MEDIUM SHADE
\0 \x92	; DARK SHADE
\0 \x81	; BOX DRAWINGS LIGHT VERTICAL
\0 \x87	; BOX DRAWINGS LIGHT VERTICAL AND LEFT
\0 \xb2	; BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE
\0 \xb4	; BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE
\0 \xa7	; BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE
\0 \xa6	; BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE
\0 \xb5	; BOX DRAWINGS DOUBLE VERTICAL AND LEFT
\0 \xa1	; BOX DRAWINGS DOUBLE VERTICAL
\0 \xa8	; BOX DRAWINGS DOUBLE DOWN AND LEFT
\0 \xae	; BOX DRAWINGS DOUBLE UP AND LEFT
\0 \xad	; BOX DRAWINGS UP DOUBLE AND LEFT SINGLE
\0 \xac	; BOX DRAWINGS UP SINGLE AND LEFT DOUBLE
\0 \x83	; BOX DRAWINGS LIGHT DOWN AND LEFT
\0 \x84	; BOX DRAWINGS LIGHT UP AND RIGHT
\0 \x89	; BOX DRAWINGS LIGHT UP AND HORIZONTAL
\0 \x88	; BOX DRAWINGS LIGHT DOWN AND HORIZONTAL
\0 \x86	; BOX DRAWINGS LIGHT VERTICAL AND RIGHT
\0 \x80	; BOX DRAWINGS LIGHT HORIZONTAL
\0 \x8a	; BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL
\0 \xaf	; BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE
\0 \xb0	; BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE
\0 \xab	; BOX DRAWINGS DOUBLE UP AND RIGHT
\0 \xa5	; BOX DRAWINGS DOUBLE DOWN AND RIGHT
\0 \xbb	; BOX DRAWINGS DOUBLE UP AND HORIZONTAL
\0 \xb8	; BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL
\0 \xb1	; BOX DRAWINGS DOUBLE VERTICAL AND RIGHT
\0 \xa0	; BOX DRAWINGS DOUBLE HORIZONTAL
\0 \xbe	; BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL
\0 \xb9	; BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE
\0 \xba	; BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE
\0 \xb6	; BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE
\0 \xb7	; BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE
\0 \xaa	; BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE
\0 \xa9	; BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE
\0 \xa2	; BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE
\0 \xa4	; BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE
\0 \xbd	; BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE
\0 \xbc	; BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE
\0 \x85	; BOX DRAWINGS LIGHT UP AND LEFT
\0 \x82	; BOX DRAWINGS LIGHT DOWN AND RIGHT
\0 \x8d	; FULL BLOCK
\0 \x8c	; LOWER HALF BLOCK
\0 \x8e	; LEFT HALF BLOCK
\0 \x8f	; RIGHT HALF BLOCK
\0 \x8b	; UPPER HALF BLOCK
\0 \xd2	; CYRILLIC SMALL LETTER ER
\0 \xd3	; CYRILLIC SMALL LETTER ES
\0 \xd4	; CYRILLIC SMALL LETTER TE
\0 \xd5	; CYRILLIC SMALL LETTER U
\0 \xc6	; CYRILLIC SMALL LETTER EF
\0 \xc8	; CYRILLIC SMALL LETTER HA
\0 \xc3	; CYRILLIC SMALL LETTER TSE
\0 \xde	; CYRILLIC SMALL LETTER CHE
\0 \xdb	; CYRILLIC SMALL LETTER SHA
\0 \xdd	; CYRILLIC SMALL LETTER SHCHA
\0 \xdf	; CYRILLIC SMALL LETTER HARD SIGN
\0 \xd9	; CYRILLIC SMALL LETTER YERU
\0 \xd8	; CYRILLIC SMALL LETTER SOFT SIGN
\0 \xdc	; CYRILLIC SMALL LETTER E
\0 \xc0	; CYRILLIC SMALL LETTER YU
\0 \xd1	; CYRILLIC SMALL LETTER YA
\0 \xb3	; CYRILLIC CAPITAL LETTER IO
\0 \xa3	; CYRILLIC SMALL LETTER IO
\0 ?	; unable to convert adequately
\0 ?	; unable to convert adequately
\0 ?	; unable to convert adequately
\0 ?	; unable to convert adequately
\0 ?	; unable to convert adequately
\0 ?	; unable to convert adequately
\0 \x9c	; DEGREE SIGN
\0 \x95	; BULLET
\0 \x9e	; MIDDLE DOT
\0 \x96	; SQUARE ROOT
\x4e \x6f	; LATIN CAPITAL LETTER N + LATIN SMALL LETTER O
\0 ?	; unable to convert adequately
\0 \x94	; BLACK SQUARE
\0 \x20	; NO-BREAK SPACE
END
