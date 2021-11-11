
SECTION BANK_20

PUBLIC _chessboard_0_nxi
PUBLIC _chessboard_0_nxi_end

_chessboard_0_nxi:

	BINARY "binary/chessboard_0.nxi"	; 16384 bytes

_chessboard_0_nxi_end:

SECTION BANK_21

PUBLIC _chessboard_1_nxi
PUBLIC _chessboard_1_nxi_end

_chessboard_1_nxi:

	BINARY "binary/chessboard_1.nxi"	; 16384 bytes

_chessboard_1_nxi_end:

SECTION BANK_22

PUBLIC _chessboard_2_nxi
PUBLIC _chessboard_2_nxi_end

_chessboard_2_nxi:

	BINARY "binary/chessboard_2.nxi"	; 16384 bytes

_chessboard_2_nxi_end:

SECTION BANK_23

PUBLIC _chessboard_3_nxi
PUBLIC _chessboard_3_nxi_end

_chessboard_3_nxi:

	BINARY "binary/chessboard_3.nxi"	; 16384 bytes

_chessboard_3_nxi_end:

SECTION BANK_24

PUBLIC _chessboard_4_nxi
PUBLIC _chessboard_4_nxi_end

_chessboard_4_nxi:

	BINARY "binary/chessboard_4.nxi"	; 16384 bytes

_chessboard_4_nxi_end:

SECTION rodata_user

PUBLIC _chessboard_sequence

_chessboard_sequence:
	DEFW _chessboard_0_nxi,_chessboard_1_nxi,_chessboard_2_nxi,_chessboard_3_nxi,_chessboard_4_nxi