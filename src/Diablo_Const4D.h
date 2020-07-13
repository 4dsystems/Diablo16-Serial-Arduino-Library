// undef windows definitions that are also 4DGL definitions
#ifdef TRANSPARENT
    #undef TRANSPARENT
#endif
#ifdef OPAQUE
    #undef OPAQUE
#endif
#ifdef BAUD_110
    #undef BAUD_110
#endif
#ifdef BAUD_300
    #undef BAUD_300
#endif
#ifdef BAUD_600
    #undef BAUD_600
#endif
#ifdef BAUD_1200
    #undef BAUD_1200
#endif
#ifdef BAUD_2400
    #undef BAUD_2400
#endif
#ifdef BAUD_4800
    #undef BAUD_4800
#endif
#ifdef BAUD_9600
    #undef BAUD_9600
#endif
#ifdef BAUD_14400
    #undef BAUD_14400
#endif
#ifdef BAUD_19200
    #undef BAUD_19200
#endif
#ifdef BAUD_38400
    #undef BAUD_38400
#endif
#ifdef BAUD_57600
    #undef BAUD_57600
#endif
#ifdef BAUD_115200
    #undef BAUD_115200
#endif

//------------------------------------------------------------------------------
//txt_Set() related constants
//------------------------------------------------------------------------------
#define TEXT_COLOUR             0 // text foreground colr
#define TEXT_BACKGROUND         1 // text background colr
#define TEXT_HIGHLIGHT          1 // text background colr
#define FONT_ID                 2 // default 0, else points to data statement font
#define FONT_SIZE               2 // compatibility
#define TEXT_WIDTH              3 // text width multiplier
#define TEXT_HEIGHT             4 // text height multiplier
#define TEXT_XGAP               5 // horizontal text gap (default 1)
#define TEXT_YGAP               6 // vertical text gap (default 1)
#define TEXT_PRINTDELAY         7 // for 'teletype' like effect when printing
#define TEXT_OPACITY            8 // text mode flag, TRANSPARENT or OPAQUE
#define TEXT_BOLD               9 // embolden text (auto reset)
#define TEXT_ITALIC             10 // italicize text (auto reset)
#define TEXT_INVERSE            11 // invert text (auto reset)
#define TEXT_UNDERLINED         12 // underline text (auto reset)
#define TEXT_ATTRIBUTES         13 // controls BOLD/ITALIC/INVERSE/UNDERLINE simultaneously
#define TEXT_WRAP               14 // Sets the pixel position where text wrap will occur at RHS
#define TEXT_ANGLE              15 // Sets the text angle, only for plotted font

//------------------------------------------------------------------------------
//txt_Set() related arguments
//------------------------------------------------------------------------------
    // (legacy compatibility)
#define FONT1                   1 // font_System_5x7
#define FONT2                   2 // font_System_8x8
#define FONT3                   3 // font_System_8x12

    // new font constants
#define FONT_1                  1 // font_System_5x7
#define FONT_2                  2 // font_System_8x8
#define FONT_3                  3 // font_System_8x12
#define FONT_4                  4 // font_System_12x16
#define FONT_5                  5 // font_MS_SanSerif8x12
#define FONT_6                  6 // font_dejaVuSansCondensed9pt
#define FONT_7                  7 // font_dejaVuSans9pt
#define FONT_8                  8 // font_dejaVuSansBold9pt
#define FONT_9                  9 // font_System_3x6
#define FONT_10                 10 // font_plotted
#define FONT_11                 11 // EGA 8x12 font

#define TRANSPARENT             0 // TEXT_OPACITY  transparent  text
#define OPAQUE                  1 // TEXT_OPACITY  opaque text

#define BOLD                    16 // TEXT_ATTRIBUTES bold text
#define ITALIC                  32 // TEXT_ATTRIBUTES italic text
#define INVERSE                 64 // TEXT_ATTRIBUTES inverse text
#define UNDERLINED              128 // TEXT_ATTRIBUTES underlined

// single word array operations
#define OP1_NOP                 0 // no operation
#define OP1_SET                 1 // "set" the entire array with "value"
#define OP1_AND                 2 // "and" the entire array with "value"
#define OP1_IOR                 3 // "inclsuve or" the entire array with "value"
#define OP1_XOR                 4 // "exclusive or" the entire array with "value"
#define OP1_ADD                 5 // signed add each element of entire array with "value"
#define OP1_SUB                 6 // signed subtract "value" from each element of entire array.
#define OP1_MUL                 7 // signed multiply each element of entire array by "value"
#define OP1_DIV                 8 // signed divide each element of entire array by "value"
#define OP1_REV                 9 // reverse the elements of an array (value is ignored)
#define OP1_SHL                 10 // shift an array left by "value" positions
#define OP1_SHR                 11 // shift an array right by "value" positions
#define OP1_ROL                 12 // rotate an array left by "value" positions
#define OP1_ROR                 13 // rotate an array right by "value" positions
    // graphics only operations
#define OP1_GRAY                14 // convert an array of RGB565 elements to grayscale, "value" is ignored
#define OP1_WHITEN              15 // saturate an array of RGB565 elements to white, "value" determines saturation
#define OP1_BLACKEN             16 // saturate an array of RGB565 elements to black, "value" determines saturation
#define OP1_LIGHTEN             17 // increase luminance of an array of RGB565 elements, "value" determines saturation
#define OP1_DARKEN              18 // decrease luminance of an array of RGB565 elements, "value" determines saturation

// dual word array operations
    // boolean and math operations
#define OP2_AND                 1 // "and" arrays, result to array1 (value is ignored)
#define OP2_IOR                 2 // "inclusive or" arrays, result to array1 (value is ignored)
#define OP2_XOR                 3 // "exclusive or" arrays, result to array1 (value is ignored)
#define OP2_ADD                 4 // "add" arrays, result to array1, array1 + (array2+value)
#define OP2_SUB                 5 // "subtract" array2 from array1, result to array1, array1 - (array2+value)
#define OP2_MUL                 6 // "multiply" arrays, result to array1 (value is ignored)
#define OP2_DIV                 7 // "divide array1 by array2" , result to array1 (value is ignored)
#define OP2_COPY                8 // "copy" array2 to array1 (value is ignored)
    // graphics only operations
#define OP2_BLEND               9 // blend arrays, blend percentage determined by "value", result to "array1"


//------------------------------------------------------------------//
// Pin related constants                                            //
//------------------------------------------------------------------//

// pin_Set(...) pin modes
#define PIN_INP                 0 // pin is input, no pullup or pulldown
#define PIN_INP_HI              1 // pin is input with pullup to Vcc
#define PIN_INP_LO              2 // pin is input with pulldown to Gnd
#define PIN_OUT                 3 // pin is output
#define PIN_OUT_OD              4 // pin is output with open drain
#define PIN_AN                  5 // pin is analogue (PA0 to PA3 only)
#define PIN_ANAVG               6 // pin is analogue (PA0 to PA3 only), averaged - 16 samples


// pin name             constant    connector H1 I/O Pin referencesnumbers
#define PA0                     1 // pin 1
#define PA1                     2 // pin 3
#define PA2                     3 // pin 5
#define BUS_WR_PIN              3 // pin 5 (alias PA2_PIN)
#define PA3                     4 // pin 7
#define BUS_RD_PIN              4 // pin 7 (alias PA3_PIN)
#define PA4                     5 // pin 29
#define PA5                     6 // pin 27
#define PA6                     7 // pin 25
#define PA7                     8 // pin 23
#define PA8                     9 // pin 21
#define PA9                     10 // pin 19
#define PA10                    11 // pin 8  (LCD power control)
#define PA11                    12 // pin 6
#define PA12                    13 // pin 28 (TX1)
#define PA13                    14 // pin 30 (RX1)
#define PA14                    15 // pin 10 (input only)
#define PA15                    16 // pin 12 (input only)
#define AUDIO_ENABLE            17 // pin 45 (Output only)

// bit position masks
#define M_PA0                   0x0001 // pin 1
#define M_PA1                   0x0002 // pin 3
#define M_PA2                   0x0004 // pin 5
#define M_PA3                   0x0008 // pin 7
#define M_PA4                   0x0010 // pin 29
#define M_PA5                   0x0020 // pin 27
#define M_PA6                   0x0040 // pin 25
#define M_PA7                   0x0080 // pin 23
#define M_PA8                   0x0100 // pin 21
#define M_PA9                   0x0200 // pin 19 (LCD power control)
#define M_PA10                  0x0400 // pin 8
#define M_PA11                  0x0800 // pin 6
#define M_PA12                  0x1000 // pin 28
#define M_PA13                  0x2000 // pin 30
#define M_PA14                  0x4000 // pin 10 (input only)
#define M_PA15                  0x8000 // pin 12 (input only)



//------------------------------------------------------------------------------
//gfx_Set() related constants
//------------------------------------------------------------------------------
#define PEN_SIZE                16 // not necessary to use (legacy mode)
#define BACKGROUND_COLOUR       17 
#define OBJECT_COLOUR           18 // line / circle / rectangle generic colour
#define CLIPPING                19 // clipping ON / OFF
#define TRANSPARENT_COLOUR      20 // (only on displays with specific hware feature)
#define TRANSPARENCY            21 // 0 = OFF, 1 = ON (only on displays with specific hware feature)
#define FRAME_DELAY             22 // legacy mode, see pokeB(IMAGE_DELAY, n);
#define SCREEN_MODE             23 // LANDSCAPE, LANDSCAPE_R, PORTRAIT, PORTRAIT_R
#define OUTLINE_COLOUR          24 // if not BLACK (0) , used for outline around circles,rectangles and filled polygons
#define CONTRAST                25 // for OLED,cahnge contrast, for LCD on or off only
#define LINE_PATTERN            26 // used for patterned lines, 16bit value (0 = no pattern, '1's = pattern)
#define BEVEL_RADIUS            27 // button bevel radius
#define BEVEL_WIDTH             28 // button bevel width
#define BEVEL_SHADOW            29 // button bevel shadow depth
#define X_ORIGIN                30 // display position X offset
#define Y_ORIGIN                31 // display position X offset

// built in fill pattern constants for function gfx_FillPattern
#define FILLPATTERN_0           0xFFE0 
#define FILLPATTERN_1           0xFFE1 
#define FILLPATTERN_2           0xFFE2 
#define FILLPATTERN_3           0xFFE3 
#define FILLPATTERN_4           0xFFE4 
#define FILLPATTERN_5           0xFFE5 
#define FILLPATTERN_6           0xFFE6 
#define FILLPATTERN_7           0xFFE7 
#define FILLPATTERN_8           0xFFE8 
#define FILLPATTERN_9           0xFFE9 
#define FILLPATTERN_10          0xFFEA 
#define FILLPATTERN_11          0xFFEB 
#define FILLPATTERN_12          0xFFEC 
#define FILLPATTERN_13          0xFFED 
#define FILLPATTERN_14          0xFFEE 
#define FILLPATTERN_15          0xFFEF 
#define FILLPATTERN_16          0xFFF0 
#define FILLPATTERN_17          0xFFF1 
#define FILLPATTERN_18          0xFFF2 
#define FILLPATTERN_19          0xFFF3 
#define FILLPATTERN_20          0xFFF4 
#define FILLPATTERN_21          0xFFF5 
#define FILLPATTERN_22          0xFFF6 
#define FILLPATTERN_23          0xFFF7 
#define FILLPATTERN_24          0xFFF8 
#define FILLPATTERN_25          0xFFF9 
#define FILLPATTERN_26          0xFFFA 
#define FILLPATTERN_27          0xFFFB 
#define FILLPATTERN_28          0xFFFC 
#define FILLPATTERN_29          0xFFFD 
#define FILLPATTERN_30          0xFFFE 
#define FILLPATTERN_31          0xFFFF 

#define PTN_EMPTY               0xFFE0 
#define PTN_SOLID               0xFFE1 
#define PTN_FINE_DOTS           0xFFE2 
#define PTN_MEDIUM_DOTS         0xFFE3 
#define PTN_COURSE_DOTS         0xFFE4 
#define PTN_BS_VERTICAL         0xFFE5 
#define PTN_BS_HORIZONTAL       0xFFE6 
#define PTN_COURSE_F_DIAGONAL   0xFFE7 
#define PTN_COURSE_B_DIAGONAL   0xFFE8 
#define PTN_COURSE_CROSS        0xFFE9 
#define PTN_COURSE_DIAGONALCROSS  0xFFEA 
#define PTN_BSVERTICAL          0xFFEB 
#define PTN_BSHORIZONTAL        0xFFEC 
#define PTN_FDIAGONAL           0xFFED 
#define PTN_BDIAGONAL           0xFFEE 
#define PTN_FINE_CROSS          0xFFEF 
#define PTN_FINE_DIAGONAL_CROSS  0xFFF0 
#define PTN_BRICKS              0xFFF1 
#define PTN_CARGONET            0xFFF2 
#define PTN_CIRCUITS            0xFFF3 
#define PTN_COBBLESTONES        0xFFF4 
#define PTN_DAISIES             0xFFF5 
#define PTN_DIZZY               0xFFF6 
#define PTN_FIELDEFFECT         0xFFF7 
#define PTN_KEY                 0xFFF8 
#define PTN_ROUNDER             0xFFF9 
#define PTN_SCALES              0xFFFA 
#define PTN_STONE               0xFFFB 
#define PTN_THATCHES            0xFFFC 
#define PTN_TILE                0xFFFD 
#define PTN_WAFFLESREVENGE      0xFFFE 
#define PTN_CROSSES             0xFFFF 

//------------------------------------------------------------------//
//     gradient control constants                                   //
//------------------------------------------------------------------//
#define GRAD_DOWN               0x20 // gradient changes in the vertical direction
#define GRAD_RIGHT              0x30 // gradient change in the horizontal direction
#define GRAD_UP                 0x40 // gradient changes in the vertical direction
#define GRAD_LEFT               0x50 // gradient change in the horizontal direction
#define GRAD_WAVE_VER           0x60 // gradient wave in the vertical direction
#define GRAD_WAVE_HOR           0x70 // gradient wave in the horizontal direction

// baud divisor rates for legacy setbaud(n);
#define MIDI                    9 
#define BAUD_110                0 
#define BAUD_300                1 
#define BAUD_600                2 
#define BAUD_1200               3 
#define BAUD_2400               4 
#define BAUD_4800               5 
#define BAUD_9600               6 
#define BAUD_14400              7 
#define BAUD_19200              8 
#define BAUD_31250              9 
#define BAUD_38400              10 
#define BAUD_56000              11 
#define BAUD_57600              12 
#define BAUD_115200             13 
#define BAUD_128000             14 
#define BAUD_256000             15 
#define BAUD_300000             16 
#define BAUD_375000             17 
#define BAUD_500000             18 
#define BAUD_600000             19 


// I2C software emulation timing related constants
#define I2C_SLOW                0 // 100Khz
#define I2C_MED                 1 // 400Khz
#define I2C_FAST                2 // 5Mhz
#define I2C_10KHZ               3 // 10khz
#define I2C_20HZ                4 // 20khz
#define I2C_50KHZ               5 // 50khz
#define I2C_250KHZ              6 // 250khz


//------------------------------------------------------------------------------
// Constants for SPI1, SPI2 an SPI3 "mode"
//------------------------------------------------------------------------------
#define SPI8_MODE_0             0 //    8bit mode    SCK idles low,    SDO stable for first falling edge, SDI sampled on first falling edge
#define SPI8_MODE_1             1 //    8bit mode    SCK idles low,    SDO stable for first rising edge,  SDI sampled on first rising edge
#define SPI8_MODE_2             2 //    8bit mode    SCK idles high,    SDO stable for first falling edge, SDI sampled on first falling edge
#define SPI8_MODE_3             3 //    8bit mode    SCK idles high,    SDO stable for first rising edge,  SDI sampled on first falling edge
#define SPI8_MODE_4             4 //    8bit mode    SCK idles low,    SDO stable for first falling edge, SDI sampled on next rising edge
#define SPI8_MODE_5             5 //    8bit mode    SCK idles low,    SDO stable for first rising edge,  SDI sampled on next falling edge
#define SPI8_MODE_6             6 //    8bit mode    SCK idles high,    SDO stable for first falling edge, SDI sampled on next rising edge
#define SPI8_MODE_7             7 //    8bit mode    SCK idles high,    SDO stable for first rising edge,  SDI sampled on next rising edge
#define SPI16_MODE_0            8 //    16bit mode    SCK idles low,    SDO stable for first falling edge, SDI sampled on first falling edge
#define SPI16_MODE_1            9 //    16bit mode    SCK idles low,    SDO stable for first rising edge,  SDI sampled on first rising edge
#define SPI16_MODE_2            10 //    16bit mode    SCK idles high,    SDO stable for first falling edge, SDI sampled on first falling edge
#define SPI16_MODE_3            11 //    16bit mode    SCK idles high,    SDO stable for first rising edge,  SDI sampled on first falling edge
#define SPI16_MODE_4            12 //    16bit mode    SCK idles low,    SDO stable for first falling edge, SDI sampled on next rising edge
#define SPI16_MODE_5            13 //    16bit mode    SCK idles low,    SDO stable for first rising edge,  SDI sampled on next falling edge
#define SPI16_MODE_6            14 //    16bit mode    SCK idles high,    SDO stable for first falling edge, SDI sampled on next rising edge
#define SPI16_MODE_7            15 //    16bit mode    SCK idles high,    SDO stable for first rising edge,  SDI sampled on next rising edge

//------------------------------------------------------------------------------
// Constants for SPI1, SPI2 an SPI3 "speed"
//------------------------------------------------------------------------------
#define SPI_SPEED0              0 // 78.125 khz
#define SPI_SPEED1              1 // 109.375 khz
#define SPI_SPEED2              2 // 273.4375 khz
#define SPI_SPEED3              3 // 312.5 khz
#define SPI_SPEED4              4 // 437.5 khz
#define SPI_SPEED5              5 // 729.166 khz
#define SPI_SPEED6              6 // 1.09375 mhz
#define SPI_SPEED7              7 // 1.25 mhz
#define SPI_SPEED8              8 // 1.75 mhz
#define SPI_SPEED9              9 // 2.1875 mhaz
#define SPI_SPEED10             10 // 4.375 mhz
#define SPI_SPEED11             11 // 5.00 mhz
#define SPI_SPEED12             12 // 7.00 mhz
#define SPI_SPEED13             13 // 8.75 mhz
#define SPI_SPEED14             14 // 11.666 mhz
#define SPI_SPEED15             15 // 17.5 mhz

// image control header offsets
#define IMG_COUNT               0 
#define IMG_ENTRYLEN            1 
#define IMG_MODE                2 
#define IMG_GCI_FILENAME        3 
#define IMG_DAT_FILENAME        4 
#define IMG_GCIFILE_HANDLE      5 

// image control entry offsets
#define IMAGE_LOWORD            0 // WORD image address LO
#define IMAGE_HIWORD            1 // WORD image address HI
#define IMAGE_XPOS              2 // WORD image location X
#define IMAGE_YPOS              3 // WORD image location Y
#define IMAGE_WIDTH             4 // WORD image width
#define IMAGE_HEIGHT            5 // WORD image height
#define IMAGE_FLAGS             6 // WORD image flags
#define IMAGE_DELAY             7 // WORD inter frame delay
#define IMAGE_FRAMES            8 // WORD number of frames
#define IMAGE_INDEX             9 // WORD current frame
#define IMAGE_CLUSTER           10 // WORD image start cluster  pos (for FAT16 only)
#define IMAGE_SECTOR            11 // WORD image start sector in cluster pos (for FAT16 only)
#define IMAGE_TAG               12 // WORD user variable #1
#define IMAGE_TAG2              13 // WORD user variable #2

// image attribute flags (in IMAGE_FLAGS)
// for img_SetAttributes(...) and img_ClearAttributes(...)
#define I_ENABLED               0x8000 // bit 15,  set for image enabled
#define I_DARKEN                0x4000 // bit 14,  display dimmed
#define I_LIGHTEN               0x2000 // bit 13,  display bright
#define I_TOUCHED               0x1000 // bit 12,  touch test result
#define I_Y_LOCK                0x0800 // bit 11,  stop Y movement
#define I_X_LOCK                0x0400 // bit 10,  stop X movement
#define I_TOPMOST               0x0200 // bit 9,   draw on top of other images next update (auto reset)
#define I_STAYONTOP             0x0100 // bit 8,   draw on top of other images always
#define I_MOVIE                 0x0080 // bit 7,   image is a movie
#define I_NOGROUP               0x0040 // bit 6,   set to exclude image refresh when using img_Show(hndl, ALL);
#define I_TOUCH_DISABLE         0x0020 // bit 5,   set to disable touch for this image, default=1 for movie, 0 for image
#define I_COLOUR16              0x0010 // bit 4,   indicates 16 bit colour mode
    // bits 0-3 reserved



//touch_Set() related constants
#define TOUCH_ENABLE            0 
#define TOUCH_DISABLE           1 
#define TOUCH_REGIONDEFAULT     2 

//touch_Get() related constants
#define TOUCH_STATUS            0 
#define TOUCH_GETX              1 
#define TOUCH_GETY              2 
#define NOTOUCH                 0 
#define TOUCH_PRESSED           1 
#define TOUCH_RELEASED          2 
#define TOUCH_MOVING            3 

//------------------------------------------------------------------------------
// FILEIO Error Code Constants
//------------------------------------------------------------------------------
#define FE_OK                   0 // IDE function succeeded
#define FE_IDE_ERROR            1 // IDE command execution error
#define FE_NOT_PRESENT          2 // CARD not present
#define FE_PARTITION_TYPE       3 // WRONG partition type, not FAT16
#define FE_INVALID_MBR          4 // MBR sector invalid signature
#define FE_INVALID_BR           5 // Boot Record invalid signature
#define FE_DISK_NOT_MNTD        6 // Media not mounted
#define FE_FILE_NOT_FOUND       7 // File not found in open for read
#define FE_INVALID_FILE         8 // File not open
#define FE_FAT_EOF              9 // Fat attempt to read beyond EOF
#define FE_EOF                  10 // Reached the end of file
#define FE_INVALID_CLUSTER      11 // Invalid cluster value > maxcls
#define FE_DIR_FULL             12 // All root dir entry are taken
#define FE_DISK_FULL            13 // All clusters in partition are taken
#define FE_FILE_OVERWRITE       14 // A file with same name exist already
#define FE_CANNOT_INIT          15 // Cannot init the CARD
#define FE_CANNOT_READ_MBR      16 // Cannot read the MBR
#define FE_MALLOC_FAILED        17 // Malloc could not allocate the FILE struct
#define FE_INVALID_MODE         18 // Mode was not r.w.
#define FE_FIND_ERROR           19 // Failure during FILE search
#define FE_INVALID_FNAME        20 // bad filename
#define FE_INVALID_MEDIA        21 // bad media
#define FE_SECTOR_READ_FAIL     22 // sector read failed
#define FE_SECTOR_WRITE_FAIL    23 // sector write failed
#define FE_FILE_TIMEOUT         26 // Timeout during file I/O, probable unexpected media removal

//------------------------------------------------------------------------------
// DISK struct offsets
//------------------------------------------------------------------------------
#define DISK_FIRST_SECT_LO      0 // DWORD address of the first sector of the FAT partition (LO word)
#define DISK_FIRST_SECT_HI      1 //       address of the first sector of the FAT partition (HI word)
#define DISK_FAT_LO             2 // DWORD address of FAT (LO word)
#define DISK_FAT_HI             3 //       address of FAT (HI word)
#define DISK_ROOT_LO            4 // DWORD address of root directory (LO word)
#define DISK_ROOT_HI            5 //       address of root directory (HI word)
#define DISK_DATA_LO            6 // DWORD address of data area (LO word)
#define DISK_DATA_HI            7 //       address of data area (HI word)
#define DISK_MAXCLUS_LO         8 // DWORD max number of clusters in partition (LO word)
#define DISK_MAXCLUS_HI         9 //       max number of clusters in partition (HI word)
#define DISK_MAXROOT            10 // WORD  max entries in root directory
#define DISK_FATSIZE            11 // WORD  number of sectors in FAT
#define DISK_FATCOPIES          12 // WORD  number of fat copies
#define DISK_SECT_PER_CLUS      13 // WORD  number of sectors per cluster
#define DISK_TYPE               14 // WORD  type of fat
#define DISK_BUF                15 // WORD  pointer to 512 byte info buffer

//------------------------------------------------------------------------------
// FILE struct offsets
//------------------------------------------------------------------------------
#define FILE_FIRST_CLUSTER      0 // WORD  first cluster
#define FILE_CURR_CLUSTER       1 // WORD  current cluster in file
#define FILE_CURR_SECTOR        2 // WORD  sector in current cluster
#define FILE_CURR_SECTOR_POS    3 // WORD  position in current sector
#define FILE_CURR_SECTOR_TOP    4 // WORD  number bytes in current sector buffer
#define FILE_SEEK_POS_LO        5 // DWORD position in the file (LO word)
#define FILE_SEEK_POS_HI        6 //       position in the file (HI word)
#define FILE_SIZE_LO            7 // DWORD file size (LO word)
#define FILE_SIZE_HI            8 //       file size (HI word)
#define FILE_TIME               9 // WORD  last update time
#define FILE_DATE               10 // WORD  last update date
#define FILE_NAME               11 // WORD  12 byte buffer for filename
#define FILE_MODE               17 // WORD  file mode 'r', 'w', 'a'
#define FILE_ATTRIBUTES         18 // WORD  files attributes
#define FILE_PAGEFLAG           19 // WORD  cache check flag
#define FILE_ENTRY              20 // WORD  entry position in cur directory
#define FILE_DISK               21 // WORD* pointer to DISK mount media structure
#define FILE_BUFFER             22 // WORD*  sector buffer



//------------------------------------------------------------------//
// pin counter mode constants                                       //
//------------------------------------------------------------------//
#define COUNT_OFF               0 // Disconnect the counter from the pin, "OVFfunction" is therefore ignored, and counting is inhibited.
#define COUNT_RISE              1 // increment counter on every rising edge
#define COUNT_FALL              2 // increment counter on every falling edge
#define COUNT_EDGE              3 // increment on every rising and falling edge


//------------------------------------------------------------------------------
// PWM Constants
//------------------------------------------------------------------------------
#define PWM_OFF                 0 
#define PWM_PLAIN               1 
#define PWM_SERVO               2 

//------------------------------------------------------------------//
// CONSTANTS
//------------------------------------------------------------------//

#define SPI1                    1 
#define SPI2                    2 
#define SPI3                    3 

// generic constants
#define ENABLE                  1 
#define DISABLE                 0 
#define HI                      1 
#define LO                      0 
#define ON                      1 
#define OFF                     0 
#define ALL                     0xFFFF // argument for img_xxx functions to update all images (and other uses)



//gfx_Get() related constants
#define X_MAX                   0 // current orientations screen maximum X co-ordinate
#define Y_MAX                   1 // current orientations screen maximum Y co-ordinate
#define LEFT_POS                2 // last objects left co-ord
#define TOP_POS                 3 // last objects top co-ord
#define RIGHT_POS               4 // last objects right co-ord
#define BOTTOM_POS              5 // last objects bottom co-ord
#define X_ORG                   6 // display position X offset
#define Y_ORG                   7 // display position X offset




#define SOLID                   0 // PEN_SIZE
#define OUTLINE                 1 // PEN_SIZE
#define STYLE1                  2 
#define STYLE2                  3 

#define LANDSCAPE               0 // SCREEN_MODE (north)
#define LANDSCAPE_R             1 // SCREEN_MODE (south)
#define PORTRAIT                2 // SCREEN_MODE (west)
#define PORTRAIT_R              3 // SCREEN_MODE (east)

#define COLOUR8                 1 // COLOUR_MODE 8 bit colour mode (not supported)
#define COLOUR16                0 // COLOUR_MODE 16 bit colour mode


#define CHECKED                 0 
#define UNCHECKED               1 


#define DOWN                    0 
#define UP                      1 
#define HIDE                    2 
#define HYPER                   3 // text only, no frame

#define BUTTON_DOWN             0 
#define BUTTON_UP               1 

#define SLIDER_SUNKEN           0 
#define SLIDER_RAISED           1 
#define SLIDER_HIDE             2 

#define PROGRESSBAR_RAISED      0xFFFF 
#define PROGRESSBAR_SUNKEN      0xFFFE 
#define PROGRESSBAR_HIDE        2 

#define PANEL_SUNKEN            0 
#define PANEL_RAISED            1 
#define PANEL_HIDE              2 
#define PANEL_FRAME             3 




// timer control  related constants
#define TIMER0                  0 
#define TIMER1                  1 
#define TIMER2                  2 
#define TIMER3                  3 
#define TIMER4                  4 
#define TIMER5                  5 
#define TIMER6                  6 
#define TIMER7                  7 



//------------------------------------------------------------------------------
// system WORD variables accesible with peekW and pokeW or pointer access
// Note that the txt_Set variables (0-15) and gfx_set variables (16-31)
// can also be accessed with peekW and pokeW
//------------------------------------------------------------------------------

#define RANDOM_LO               32 // random number generator LO word
#define RANDOM_HI               33 // random number generator LO word
#define SYSTEM_TIMER_LO         34 // 1msec 32 bit free running timer LO word
#define SYSTEM_TIMER_HI         35 // 1msec 32 bit free running timer HI word
#define TMR0                    36 // user timer0
#define TMR1                    37 // user timer1
#define TMR2                    38 // user timer2
#define TMR3                    39 // user timer3 (10msec resolution)
#define TMR4                    40 // user timer0
#define TMR5                    41 // user timer1
#define TMR6                    42 // user timer2
#define TMR7                    43 // user timer3 (10msec resolution)
#define SYS_X_MAX               44 // display hardware X res-1
#define SYS_Y_MAX               45 // display hardware Y res-1
#define GFX_XMAX                46 // current display width-1 determined by portrait / landscape swapping
#define GFX_YMAX                47 // current display width-1 determined by portrait / landscape swapping
#define GFX_LEFT                48 // virtual left point for most recent object
#define GFX_TOP                 49 // virtual top point for most recent object
#define GFX_RIGHT               50 // virtual right point for most recent object
#define GFX_BOTTOM              51 // virtual bottom point for most recent object
#define GFX_X1                  52 // clipped left point for current object
#define GFX_Y1                  53 // clipped top point for current object
#define GFX_X2                  54 // clipped right point for current object
#define GFX_Y2                  55 // clipped bottom point for current object
#define GFX_X_ORG               56 // current X origin
#define GFX_Y_ORG               57 // current Y origin

#define GFX_THUMB_PERCENT       75 // size of slider thumb as percentage
#define GFX_THUMB_BORDER_DARK   76 // darker shadow of thumb
#define GFX_THUMB_BORDER_LIGHT  77 // lighter shadow of thumb
#define TOUCH_XMINCAL           78 // touch calibration value
#define TOUCH_YMINCAL           79 // touch calibration value
#define TOUCH_XMAXCAL           80 // touch calibration value
#define TOUCH_YMAXCAL           81 // touch calibration value
#define IMG_WIDTH               82 // width of currently loaded image
#define IMG_HEIGHT              83 // height of currently loaded image
#define IMG_FRAME_DELAY         84 // 0 if image, else inter frame delay for movie
#define IMG_FLAGS               85 // bit 4 determines colour mode, other bits reserved
#define IMG_FRAME_COUNT         86 // count of frames in a movie
#define IMG_PIXEL_COUNT_LO      87 // count of pixels in the current frame
#define IMG_PIXEL_COUNT_HI      88 // count of pixels in the current frame
#define IMG_CURRENT_FRAME       89 // last frame shown
#define MEDIA_ADDRESS_LO        90 // uSD byte address LO
#define MEDIA_ADDRESS_HI        91 // uSD byte address HI
#define MEDIA_SECTOR_LO         92 // uSD sector address LO
#define MEDIA_SECTOR_HI         93 // uSD sector address HI
#define MEDIA_SECTOR_COUNT      94 // uSD number of bytes remaining in sector
#define TEXT_XPOS               95 // text current x pixel position
#define TEXT_YPOS               96 // text current y pixel position
#define TEXT_MARGIN             97 // text left pixel pos for carriage return
#define TXT_FONT_ID             98 // font type, 0 = system font, else pointer to user font
#define TXT_FONT_MAX            99 // max number of chars in font
#define TXT_FONT_OFFSET         100 // starting offset (normally 0x20)
#define TXT_FONT_WIDTH          101 // current font width
#define TXT_FONT_HEIGHT         102 // current font height
#define GFX_TOUCH_REGION_X1     103 // touch capture region
#define GFX_TOUCH_REGION_Y1     104 
#define GFX_TOUCH_REGION_X2     105 
#define GFX_TOUCH_REGION_Y2     106 
#define GFX_CLIP_LEFT_VAL       107 // left clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_TOP_VAL        108 // top clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_RIGHT_VAL      109 // right clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_BOTTOM_VAL     110 // bottom clipping point (set with gfx_ClipWindow(...)
#define GFX_CLIP_LEFT           111 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_TOP            112 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_RIGHT          113 // current clip value (reads full size if clipping turned off)
#define GFX_CLIP_BOTTOM         114 // current clip value (reads full size if clipping turned off)
#define GRAM_PIXEL_COUNT_LO     115 // LO word of count of pixels in the set GRAM area
#define GRAM_PIXEL_COUNT_HI     116 // HI word of count of pixels in the set GRAM area
#define TOUCH_RAW_X             117 // 12 bit raw A2D X value from touch screen
#define TOUCH_RAW_Y             118 // 12 bit raw A2D Y value from touch screen
#define GFX_LAST_CHAR_WIDTH     119 // calculated char width from last call to charWidth function
#define GFX_LAST_CHAR_HEIGHT    120 // calculated height from last call to charHeight function
#define GFX_LAST_STR_WIDTH      121 // calculated width from last call to strWidth function
#define GFX_LAST_STR_HEIGHT     122 // calculated height from last call to strHeight function
#define PIN_COUNTER_PA4         123 // pin counter for PA4
#define PIN_COUNTER_PA5         124 // pin counter for PA5
#define PIN_COUNTER_PA6         125 // pin counter for PA6
#define PIN_COUNTER_PA7         126 // pin counter for PA7
#define PIN_COUNTER_PA8         127 // pin counter for PA8
#define PIN_COUNTER_PA9         128 // pin counter for PA9
#define PIN_EVENT_PA4           129 // pin counter rollover event for PA4
#define PIN_EVENT_PA5           130 // pin counter rollover event for PA5
#define PIN_EVENT_PA6           131 // pin counter rollover event for PA6
#define PIN_EVENT_PA7           132 // pin counter rollover event for PA7
#define PIN_EVENT_PA8           133 // pin counter rollover event for PA8
#define PIN_EVENT_PA9           134 // pin counter rollover event for PA9
#define QEN1_COUNTER_LO         135 // quadrature encoder #1 counter LO
#define QEN1_COUNTER_HI         136 // quadrature encoder #1 counter HI
#define QEN1_DELTA              137 // quadrature encoder #1 delta count, reset when read
#define QEN2_COUNTER_LO         138 // quadrature encoder #2 counter LO
#define QEN2_COUNTER_HI         139 // quadrature encoder #2 counter HI
#define QEN2_DELTA              140 // quadrature encoder #2 delta count, reset when read
#define FALSE_REASON            141 // explanation 'false' results, currently only for flash_ functions

//------------------------------------------------------------------//
// string processing constants                                      //
//------------------------------------------------------------------//
#define STR                     0x0080 // display as string
#define CHR                     0x0081 // display as single char


//============================================================================
// number formatting bits
//============================================================================
// bit 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1  0
//     |  |  |  |   \___ ___/  |  \  /  \_____ _____/
//     |  |  |  |       V      |   V          V
//     |  |  |  |       |      |   |          |
//     |  |  |  |  digit count |   |          |
//     |  |  |  |  (nb 0 = 16) |   |          |____BASE (usually 2,10 or 16)
//     |  |  |  |              |   |
//     |  |  |  |              |   |___reserved (not used on Goldelox)
//     |  |  |  |              |
//     |  |  |  |              |____ string indicatior
//     |  |  |  |                      0x80 = [STR]
//     |  |  |  |                      0x81 = [CHR]
//     |  |  |  |______
//     |  |  |           1 = leading zeros included
//     |  |  |           0 = leading zeros suppressed
//     |  |  |
//     |  |  |_______
//     |  |           1 = leading zero blanking
//     |  |
//     |  |_____ sign bit (0 = signed, 1 = unsigned)
//     |
//     |______ 1 = space before unsigned number



  //=======================================================
  // general number formatting constants
  // for 'print' and 'putnum'
  //=======================================================
  // binary, no leading zeroes
// #define BIN                     0x0002 // binary, 16 digits, no leading zeroes
#define BIN1                    0x0102 // binary, 1 digit, no leading zeroes
#define BIN2                    0x0202 // binary, 2 digits, no leading zeroes
#define BIN3                    0x0302 // binary, 3 digits, no leading zeroes
#define BIN4                    0x0402 // binary, 4 digits, no leading zeroes
#define BIN5                    0x0502 // binary, 5 digits, no leading zeroes
#define BIN6                    0x0602 // binary, 6 digits, no leading zeroes
#define BIN7                    0x0702 // binary, 7 digits, no leading zeroes
#define BIN8                    0x0802 // binary, 8 digits, no leading zeroes
#define BIN9                    0x0902 // binary, 9 digits, no leading zeroes
#define BIN10                   0x0A02 // binary, 10 digits, no leading zeroes
#define BIN11                   0x0B02 // binary, 11 digits, no leading zeroes
#define BIN12                   0x0C02 // binary, 12 digits, no leading zeroes
#define BIN13                   0x0D02 // binary, 13 digits, no leading zeroes
#define BIN14                   0x0E02 // binary, 14 digits, no leading zeroes
#define BIN15                   0x0F02 // binary, 15 digits, no leading zeroes
#define BIN16                   0x0002 // binary, 16 digits, no leading zeroes

  // binary, with leading zeroes
#define BINZ                    0x1002 // binary, 16 digits, leading zeroes
#define BIN1Z                   0x1102 // binary, 1 digit, leading zeroes
#define BIN2Z                   0x1202 // binary, 2 digits, leading zeroes
#define BIN3Z                   0x1302 // binary, 3 digits, leading zeroes
#define BIN4Z                   0x1402 // binary, 4 digits, leading zeroes
#define BIN5Z                   0x1502 // binary, 5 digits, leading zeroes
#define BIN6Z                   0x1602 // binary, 6 digits, leading zeroes
#define BIN7Z                   0x1702 // binary, 7 digits, leading zeroes
#define BIN8Z                   0x1802 // binary, 8 digits, leading zeroes
#define BIN9Z                   0x1902 // binary, 9 digits, leading zeroes
#define BIN10Z                  0x1A02 // binary, 10 digits, leading zeroes
#define BIN11Z                  0x1B02 // binary, 11 digits, leading zeroes
#define BIN12Z                  0x1C02 // binary, 12 digits, leading zeroes
#define BIN13Z                  0x1D02 // binary, 13 digits, leading zeroes
#define BIN14Z                  0x1E02 // binary, 14 digits, leading zeroes
#define BIN15Z                  0x1F02 // binary, 15 digits, leading zeroes
#define BIN16Z                  0x1002 // binary, 16 digits, leading zeroes

  // binary, with leading blanked
#define BINZB                   0x2002 // binary, 16 digits, leading blanks
#define BIN1ZB                  0x2102 // binary, 1 digit, leading blanks
#define BIN2ZB                  0x2202 // binary, 2 digits, leading blanks
#define BIN3ZB                  0x2302 // binary, 3 digits, leading blanks
#define BIN4ZB                  0x2402 // binary, 4 digits, leading blanks
#define BIN5ZB                  0x2502 // binary, 5 digits, leading blanks
#define BIN6ZB                  0x2602 // binary, 6 digits, leading blanks
#define BIN7ZB                  0x2702 // binary, 7 digits, leading blanks
#define BIN8ZB                  0x2802 // binary, 8 digits, leading blanks
#define BIN9ZB                  0x2902 // binary, 9 digits, leading blanks
#define BIN10ZB                 0x2A02 // binary, 10 digits, leading blanks
#define BIN11ZB                 0x2B02 // binary, 11 digits, leading blanks
#define BIN12ZB                 0x2C02 // binary, 12 digits, leading blanks
#define BIN13ZB                 0x2D02 // binary, 13 digits, leading blanks
#define BIN14ZB                 0x2E02 // binary, 14 digits, leading blanks
#define BIN15ZB                 0x2F02 // binary, 15 digits, leading blanks
#define BIN16ZB                 0x2002 // binary, 16 digits, leading blanks

  // signed decimal, no leading zeroes
// #define DEC                     0x050A // signed decimal, 5 digits, no leading zeroes
#define DEC1                    0x010A // signed decimal, 1 digit, no leading zeroes
#define DEC2                    0x020A // signed decimal, 2 digits, no leading zeroes
#define DEC3                    0x030A // signed decimal, 3 digits, no leading zeroes
#define DEC4                    0x040A // signed decimal, 4 digits, no leading zeroes
#define DEC5                    0x050A // signed decimal, 5 digits, no leading zeroes

  // signed decimal, with leading zeroes
#define DECZ                    0x150A // signed decimal, 5 digits, leading zeroes
#define DEC1Z                   0x110A // signed decimal, 1 digit, leading zeroes
#define DEC2Z                   0x120A // signed decimal, 2 digits, leading zeroes
#define DEC3Z                   0x130A // signed decimal, 3 digits, leading zeroes
#define DEC4Z                   0x140A // signed decimal, 4 digits, leading zeroes
#define DEC5Z                   0x150A // signed decimal, 5 digits, leading zeroes

  // signed decimal, leading zeroes blanked
#define DECZB                   0x250A // signed decimal, 5 digits, leading blanks
#define DEC1ZB                  0x210A // signed decimal, 1 digit, leading blanks
#define DEC2ZB                  0x220A // signed decimal, 2 digits, leading blanks
#define DEC3ZB                  0x230A // signed decimal, 3 digits, leading blanks
#define DEC4ZB                  0x240A // signed decimal, 4 digits, leading blanks
#define DEC5ZB                  0x250A // signed decimal, 5 digits, leading blanks

  // unsigned decimal, no leading zeroes
#define UDEC                    0x450A // unsigned decimal, 5 digits, no leading zeroes
#define UDEC1                   0x410A // unsigned decimal, 1 digit, no leading zeroes
#define UDEC2                   0x420A // unsigned decimal, 2 digits, no leading zeroes
#define UDEC3                   0x430A // unsigned decimal, 3 digits, no leading zeroes
#define UDEC4                   0x440A // unsigned decimal, 4 digits, no leading zeroes
#define UDEC5                   0x450A // unsigned decimal, 5 digits, no leading zeroes

  // unsigned decimal, with leading zero's
#define UDECZ                   0x550A // unsigned decimal, 5 digits, leading zeroes
#define UDEC1Z                  0x510A // unsigned decimal, 1 digit, leading zeroes
#define UDEC2Z                  0x520A // unsigned decimal, 2 digits, leading zeroes
#define UDEC3Z                  0x530A // unsigned decimal, 3 digits, leading zeroes
#define UDEC4Z                  0x540A // unsigned decimal, 4 digits, leading zeroes
#define UDEC5Z                  0x550A // unsigned decimal, 5 digits, leading zeroes

  // unsigned decimal, leading zeroes blanked
#define UDECZB                  0x650A // unsigned decimal, 5 digits, leading blanks
#define UDEC1ZB                 0x610A // unsigned decimal, 1 digit, leading blanks
#define UDEC2ZB                 0x620A // unsigned decimal, 2 digits, leading blanks
#define UDEC3ZB                 0x630A // unsigned decimal, 3 digits, leading blanks
#define UDEC4ZB                 0x640A // unsigned decimal, 4 digits, leading blanks
#define UDEC5ZB                 0x650A // unsigned decimal, 5 digits, leading blanks

  // hex, with leading zero's
// #define HEX                     0x1410 // hex, 4 digits, leading zeroes
#define HEX1                    0x1110 // hex, 1 digit, leading zeroes
#define HEX2                    0x1210 // hex, 2 digits, leading zeroes
#define HEX3                    0x1310 // hex, 3 digits, leading zeroes
#define HEX4                    0x1410 // hex, 4 digits, leading zeroes

  // hex, no leading zero's
#define HEXZ                    0x0410 // hex, 4 digits, no leading zeroes
#define HEX1Z                   0x0110 // hex, 1 digit, no leading zeroes
#define HEX2Z                   0x0210 // hex, 2 digits, no leading zeroes
#define HEX3Z                   0x0310 // hex, 3 digits, no leading zeroes
#define HEX4Z                   0x0410 // hex, 4 digits, no leading zeroes

  // hex, leading zero's blanked
#define HEXZB                   0x2410 // hex, 4 digits, leading blanks
#define HEX1ZB                  0x2110 // hex, 1 digit, leading blanks
#define HEX2ZB                  0x2210 // hex, 2 digits, leading blanks
#define HEX3ZB                  0x2310 // hex, 3 digits, leading blanks
#define HEX4ZB                  0x2410 // hex, 4 digits, leading blanks



//==================================================================================================



/*
    16 bit RGB (565) Colour Chart
    Original work by 4D Forum Member: skadoo
*/



#define ALICEBLUE               0xF7DF 
#define ANTIQUEWHITE            0xFF5A 
#define AQUA                    0x07FF 
#define AQUAMARINE              0x7FFA 
#define AZURE                   0xF7FF 
#define BEIGE                   0xF7BB 
#define BISQUE                  0xFF38 
#define BLACK                   0x0000 
#define BLANCHEDALMOND          0xFF59 
#define BLUE                    0x001F 
#define BLUEVIOLET              0x895C 
#define BROWN                   0xA145 
#define BURLYWOOD               0xDDD0 
#define CADETBLUE               0x5CF4 
#define CHARTREUSE              0x7FE0 
#define CHOCOLATE               0xD343 
#define CORAL                   0xFBEA 
#define CORNFLOWERBLUE          0x64BD 
#define CORNSILK                0xFFDB 
#define CRIMSON                 0xD8A7 
#define CYAN                    0x07FF 
#define DARKBLUE                0x0011 
#define DARKCYAN                0x0451 
#define DARKGOLDENROD           0xBC21 
#define DARKGRAY                0xAD55 
#define DARKGREEN               0x0320 
#define DARKKHAKI               0xBDAD 
#define DARKMAGENTA             0x8811 
#define DARKOLIVEGREEN          0x5345 
#define DARKORANGE              0xFC60 
#define DARKORCHID              0x9999 
#define DARKRED                 0x8800 
#define DARKSALMON              0xECAF 
#define DARKSEAGREEN            0x8DF1 
#define DARKSLATEBLUE           0x49F1 
#define DARKSLATEGRAY           0x2A69 
#define DARKTURQUOISE           0x067A 
#define DARKVIOLET              0x901A 
#define DEEPPINK                0xF8B2 
#define DEEPSKYBLUE             0x05FF 
#define DIMGRAY                 0x6B4D 
#define DODGERBLUE              0x1C9F 
#define FIREBRICK               0xB104 
#define FLORALWHITE             0xFFDE 
#define FORESTGREEN             0x2444 
#define FUCHSIA                 0xF81F 
#define GAINSBORO               0xDEFB 
#define GHOSTWHITE              0xFFDF 
#define GOLD                    0xFEA0 
#define GOLDENROD               0xDD24 
#define GRAY                    0x8410 
#define GREEN                   0x0400 
#define GREENYELLOW             0xAFE5 
#define HONEYDEW                0xF7FE 
#define HOTPINK                 0xFB56 
#define INDIANRED               0xCAEB 
#define INDIGO                  0x4810 
#define IVORY                   0xFFFE 
#define KHAKI                   0xF731 
#define LAVENDER                0xE73F 
#define LAVENDERBLUSH           0xFF9E 
#define LAWNGREEN               0x7FE0 
#define LEMONCHIFFON            0xFFD9 
#define LIGHTBLUE               0xAEDC 
#define LIGHTCORAL              0xF410 
#define LIGHTCYAN               0xE7FF 
#define LIGHTGOLD               0xFFDA 
#define LIGHTGREEN              0x9772 
#define LIGHTGREY               0xD69A 
#define LIGHTPINK               0xFDB8 
#define LIGHTSALMON             0xFD0F 
#define LIGHTSEAGREEN           0x2595 
#define LIGHTSKYBLUE            0x867F 
#define LIGHTSLATEGRAY          0x7453 
#define LIGHTSTEELBLUE          0xB63B 
#define LIGHTYELLOW             0xFFFC 
#define LIME                    0x07E0 
#define LIMEGREEN               0x3666 
#define LINEN                   0xFF9C 
#define MAGENTA                 0xF81F 
#define MAROON                  0x8000 
#define MEDIUMAQUAMARINE        0x6675 
#define MEDIUMBLUE              0x0019 
#define MEDIUMORCHID            0xBABA 
#define MEDIUMPURPLE            0x939B 
#define MEDIUMSEAGREEN          0x3D8E 
#define MEDIUMSLATEBLUE         0x7B5D 
#define MEDIUMSPRINGGREEN       0x07D3 
#define MEDIUMTURQUOISE         0x4E99 
#define MEDIUMVIOLETRED         0xC0B0 
#define MIDNIGHTBLUE            0x18CE 
#define MINTCREAM               0xF7FF 
#define MISTYROSE               0xFF3C 
#define MOCCASIN                0xFF36 
#define NAVAJOWHITE             0xFEF5 
#define NAVY                    0x0010 
#define OLDLACE                 0xFFBC 
#define OLIVE                   0x8400 
#define OLIVEDRAB               0x6C64 
#define ORANGE                  0xFD20 
#define ORANGERED               0xFA20 
#define ORCHID                  0xDB9A 
#define PALEGOLDENROD           0xEF55 
#define PALEGREEN               0x9FD3 
#define PALETURQUOISE           0xAF7D 
#define PALEVIOLETRED           0xDB92 
#define PAPAYAWHIP              0xFF7A 
#define PEACHPUFF               0xFED7 
#define PERU                    0xCC27 
#define PINK                    0xFE19 
#define PLUM                    0xDD1B 
#define POWDERBLUE              0xB71C 
#define PURPLE                  0x8010 
#define RED                     0xF800 
#define ROSYBROWN               0xBC71 
#define ROYALBLUE               0x435C 
#define SADDLEBROWN             0x8A22 
#define SALMON                  0xFC0E 
#define SANDYBROWN              0xF52C 
#define SEAGREEN                0x2C4A 
#define SEASHELL                0xFFBD 
#define SIENNA                  0xA285 
#define SILVER                  0xC618 
#define SKYBLUE                 0x867D 
#define SLATEBLUE               0x6AD9 
#define SLATEGRAY               0x7412 
#define SNOW                    0xFFDF 
#define SPRINGGREEN             0x07EF 
#define STEELBLUE               0x4416 
#define TAN                     0xD5B1 
#define TEAL                    0x0410 
#define THISTLE                 0xDDFB 
#define TOMATO                  0xFB08 
#define TURQUOISE               0x471A 
#define VIOLET                  0xEC1D 
#define WHEAT                   0xF6F6 
#define WHITE                   0xFFFF 
#define WHITESMOKE              0xF7BE 
#define YELLOW                  0xFFE0 
#define YELLOWGREEN             0x9E66 

#define Err4D_OK 		0
#define Err4D_Timeout		1
#define Err4D_NAK		2 // other than ACK received

#define t4DWordArray 			word *
#define t4DByteArray 			char *
#define t4DSector 				char *

#define F_blitComtoDisplay 35
#define F_bus_Read8 -122
#define F_bus_Write8 -121
#define F_charheight 29
#define F_charwidth 30
#define F_file_CallFunction 25
#define F_file_Close -431
#define F_file_Count 1
#define F_file_Dir 2
#define F_file_Erase 3
#define F_file_Error -424
#define F_file_Exec 4
#define F_file_Exists 5
#define F_file_FindFirst 6
#define F_file_FindFirstRet 36
#define F_file_FindNext -428
#define F_file_FindNextRet 37
#define F_file_GetC -441
#define F_file_GetS 7
#define F_file_GetW -443
#define F_file_Image -438
#define F_file_Index -434
#define F_file_LoadFunction 8
#define F_file_LoadImageControl 9
#define F_file_Mount -452
#define F_file_Open 10
#define F_file_PlayWAV 11
#define F_file_PutC 31
#define F_file_PutS 32
#define F_file_PutW -442
#define F_file_Read 12
#define F_file_Rewind -447
#define F_file_Run 13
#define F_file_ScreenCapture -439
#define F_file_Seek -433
#define F_file_Size 14
#define F_file_Tell 15
#define F_file_Unmount -453
#define F_file_Write 16
#define F_gfx_BevelShadow -196
#define F_gfx_BevelWidth -195
#define F_gfx_BGcolour -184
#define F_gfx_Button 17
#define F_gfx_ChangeColour -151
#define F_gfx_Circle -136
#define F_gfx_CircleFilled -137
#define F_gfx_Clipping -186
#define F_gfx_ClipWindow -150
#define F_gfx_Cls -126
#define F_gfx_Contrast -192
#define F_gfx_Ellipse -153
#define F_gfx_EllipseFilled -154
#define F_gfx_FrameDelay -189
#define F_gfx_Get -182
#define F_gfx_GetPixel -139
#define F_gfx_Line -131
#define F_gfx_LinePattern -193
#define F_gfx_LineTo -129
#define F_gfx_MoveTo -127
#define F_gfx_Orbit 18
#define F_gfx_OutlineColour -191
#define F_gfx_Panel -161
//#define F_gfx_PenSize -183
#define F_gfx_Polygon 19
#define F_gfx_PolygonFilled 20
#define F_gfx_Polyline 21
#define F_gfx_PutPixel -138
#define F_gfx_Rectangle -134
#define F_gfx_RectangleFilled -135
#define F_gfx_ScreenCopyPaste -163
#define F_gfx_ScreenMode -190
#define F_gfx_Set -125
#define F_gfx_SetClipRegion -152
#define F_gfx_Slider -162
#define F_gfx_Transparency -188
#define F_gfx_TransparentColour -187
#define F_gfx_Triangle -140
#define F_gfx_TriangleFilled -167
#define F_img_ClearAttributes -383
#define F_img_Darken -377
#define F_img_Disable -376
#define F_img_Enable -375
#define F_img_GetWord -380
#define F_img_Lighten -378
#define F_img_SetAttributes -382
#define F_img_SetPosition -374
#define F_img_SetWord -379
#define F_img_Show -381
#define F_img_Touched -384
#define F_media_Flush -218
#define F_media_Image -217
#define F_media_Init -219
#define F_media_RdSector 22
#define F_media_ReadByte -213
#define F_media_ReadWord -214
#define F_media_SetAdd -209
#define F_media_SetSector -210
#define F_media_Video -207
#define F_media_VideoFrame -208
#define F_media_WriteByte -215
#define F_media_WriteWord -216
#define F_media_WrSector 23
#define F_mem_Free -417
#define F_mem_Heap -418
#define F_peekM 39
#define F_pin_HI -113
#define F_pin_LO -114
#define F_pin_Read -116
#define F_pin_Set -112
#define F_pokeM 40
#define F_putCH -2
#define F_putstr 24
#define F_readString 34
#define F_setbaudWait 38
#define F_snd_BufSize -461
#define F_snd_Continue -464
#define F_snd_Pause -463
#define F_snd_Pitch -460
#define F_snd_Playing -465
#define F_snd_Stop -462
#define F_snd_Volume -459
#define F_sys_GetModel 26
#define F_sys_GetPmmC 28
#define F_sys_GetVersion 27
#define F_sys_Sleep -403
#define F_touch_DetectRegion -406
#define F_touch_Get -408
#define F_touch_Set -407
#define F_txt_Attributes -31
#define F_txt_BGcolour -19
#define F_txt_Bold -27
#define F_txt_FGcolour -18
#define F_txt_FontID -20
#define F_txt_Height -22
#define F_txt_Inverse -29
#define F_txt_Italic -28
#define F_txt_MoveCursor -16
#define F_txt_Opacity -26
#define F_txt_Set -17
#define F_txt_Underline -30
#define F_txt_Width -21
#define F_txt_Wrap -32
#define F_txt_Xgap -23
#define F_txt_Ygap -24
#define F_writeString 33

