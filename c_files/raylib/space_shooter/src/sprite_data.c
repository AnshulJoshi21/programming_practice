#include "../include/sprite_data.h"

const Rectangle sprite_db[SPRITE_COUNT] = {
    [SPRITE_BEAM0] = (Rectangle){.x = 143, .y = 377, .width = 43, .height = 31},
    [SPRITE_BEAM1] = (Rectangle){.x = 327, .y = 644, .width = 40, .height = 20},
    [SPRITE_BEAM2] = (Rectangle){.x = 262, .y = 907, .width = 38, .height = 31},
    [SPRITE_BEAM3] = (Rectangle){.x = 396, .y = 384, .width = 29, .height = 29},
    [SPRITE_BEAM4] = (Rectangle){.x = 177, .y = 496, .width = 41, .height = 17},
    [SPRITE_BEAM5] = (Rectangle){.x = 186, .y = 377, .width = 40, .height = 25},
    [SPRITE_BEAM6] = (Rectangle){.x = 120, .y = 688, .width = 43, .height = 23},
    [SPRITE_BEAMLONG1] =
        (Rectangle){.x = 828, .y = 943, .width = 15, .height = 67},
    [SPRITE_BEAMLONG2] =
        (Rectangle){.x = 307, .y = 309, .width = 25, .height = 64},
    [SPRITE_BOLD_SILVER] =
        (Rectangle){.x = 810, .y = 837, .width = 19, .height = 30},
    [SPRITE_BOLT_BRONZE] =
        (Rectangle){.x = 810, .y = 467, .width = 19, .height = 30},
    [SPRITE_BOLT_GOLD] =
        (Rectangle){.x = 809, .y = 437, .width = 19, .height = 30},
    [SPRITE_BUTTONBLUE] =
        (Rectangle){.x = 0, .y = 78, .width = 222, .height = 39},
    [SPRITE_BUTTONGREEN] =
        (Rectangle){.x = 0, .y = 117, .width = 222, .height = 39},
    [SPRITE_BUTTONRED] =
        (Rectangle){.x = 0, .y = 0, .width = 222, .height = 39},
    [SPRITE_BUTTONYELLOW] =
        (Rectangle){.x = 0, .y = 39, .width = 222, .height = 39},
    [SPRITE_COCKPITBLUE_0] =
        (Rectangle){.x = 586, .y = 0, .width = 51, .height = 75},
    [SPRITE_COCKPITBLUE_1] =
        (Rectangle){.x = 736, .y = 862, .width = 40, .height = 40},
    [SPRITE_COCKPITBLUE_2] =
        (Rectangle){.x = 684, .y = 67, .width = 42, .height = 56},
    [SPRITE_COCKPITBLUE_3] =
        (Rectangle){.x = 336, .y = 384, .width = 60, .height = 61},
    [SPRITE_COCKPITBLUE_4] =
        (Rectangle){.x = 637, .y = 0, .width = 47, .height = 67},
    [SPRITE_COCKPITBLUE_5] =
        (Rectangle){.x = 627, .y = 144, .width = 48, .height = 75},
    [SPRITE_COCKPITBLUE_6] =
        (Rectangle){.x = 684, .y = 0, .width = 42, .height = 67},
    [SPRITE_COCKPITBLUE_7] =
        (Rectangle){.x = 737, .y = 542, .width = 41, .height = 71},
    [SPRITE_COCKPITGREEN_0] =
        (Rectangle){.x = 576, .y = 225, .width = 51, .height = 75},
    [SPRITE_COCKPITGREEN_1] =
        (Rectangle){.x = 734, .y = 977, .width = 40, .height = 40},
    [SPRITE_COCKPITGREEN_2] =
        (Rectangle){.x = 696, .y = 659, .width = 42, .height = 56},
    [SPRITE_COCKPITGREEN_3] =
        (Rectangle){.x = 346, .y = 234, .width = 60, .height = 61},
    [SPRITE_COCKPITGREEN_4] =
        (Rectangle){.x = 627, .y = 219, .width = 47, .height = 67},
    [SPRITE_COCKPITGREEN_5] =
        (Rectangle){.x = 694, .y = 364, .width = 42, .height = 67},
    [SPRITE_COCKPITGREEN_6] =
        (Rectangle){.x = 737, .y = 471, .width = 41, .height = 71},
    [SPRITE_COCKPITGREEN_7] =
        (Rectangle){.x = 602, .y = 525, .width = 48, .height = 75},
    [SPRITE_COCKPITRED_0] =
        (Rectangle){.x = 535, .y = 75, .width = 51, .height = 75},
    [SPRITE_COCKPITRED_1] =
        (Rectangle){.x = 351, .y = 982, .width = 40, .height = 40},
    [SPRITE_COCKPITRED_2] =
        (Rectangle){.x = 718, .y = 197, .width = 42, .height = 56},
    [SPRITE_COCKPITRED_3] =
        (Rectangle){.x = 520, .y = 661, .width = 60, .height = 61},
    [SPRITE_COCKPITRED_4] =
        (Rectangle){.x = 647, .y = 857, .width = 47, .height = 67},
    [SPRITE_COCKPITRED_5] =
        (Rectangle){.x = 605, .y = 707, .width = 48, .height = 75},
    [SPRITE_COCKPITRED_6] =
        (Rectangle){.x = 736, .y = 795, .width = 42, .height = 67},
    [SPRITE_COCKPITRED_7] =
        (Rectangle){.x = 736, .y = 329, .width = 41, .height = 71},
    [SPRITE_COCKPITYELLOW_0] =
        (Rectangle){.x = 726, .y = 80, .width = 40, .height = 40},
    [SPRITE_COCKPITYELLOW_1] =
        (Rectangle){.x = 247, .y = 309, .width = 60, .height = 61},
    [SPRITE_COCKPITYELLOW_2] =
        (Rectangle){.x = 637, .y = 67, .width = 47, .height = 67},
    [SPRITE_COCKPITYELLOW_3] =
        (Rectangle){.x = 607, .y = 782, .width = 48, .height = 75},
    [SPRITE_COCKPITYELLOW_4] =
        (Rectangle){.x = 696, .y = 262, .width = 42, .height = 67},
    [SPRITE_COCKPITYELLOW_5] =
        (Rectangle){.x = 736, .y = 400, .width = 41, .height = 71},
    [SPRITE_COCKPITYELLOW_6] =
        (Rectangle){.x = 734, .y = 921, .width = 42, .height = 56},
    [SPRITE_COCKPITYELLOW_7] =
        (Rectangle){.x = 600, .y = 375, .width = 51, .height = 75},
    [SPRITE_CURSOR] =
        (Rectangle){.x = 797, .y = 173, .width = 30, .height = 33},
    [SPRITE_ENEMYBLACK1] =
        (Rectangle){.x = 423, .y = 728, .width = 93, .height = 84},
    [SPRITE_ENEMYBLACK2] =
        (Rectangle){.x = 120, .y = 604, .width = 104, .height = 84},
    [SPRITE_ENEMYBLACK3] =
        (Rectangle){.x = 144, .y = 156, .width = 103, .height = 84},
    [SPRITE_ENEMYBLACK4] =
        (Rectangle){.x = 518, .y = 325, .width = 82, .height = 84},
    [SPRITE_ENEMYBLACK5] =
        (Rectangle){.x = 346, .y = 150, .width = 97, .height = 84},
    [SPRITE_ENEMYBLUE1] =
        (Rectangle){.x = 425, .y = 468, .width = 93, .height = 84},
    [SPRITE_ENEMYBLUE2] =
        (Rectangle){.x = 143, .y = 293, .width = 104, .height = 84},
    [SPRITE_ENEMYBLUE3] =
        (Rectangle){.x = 222, .y = 0, .width = 103, .height = 84},
    [SPRITE_ENEMYBLUE4] =
        (Rectangle){.x = 518, .y = 409, .width = 82, .height = 84},
    [SPRITE_ENEMYBLUE5] =
        (Rectangle){.x = 421, .y = 814, .width = 97, .height = 84},
    [SPRITE_ENEMYGREEN1] =
        (Rectangle){.x = 425, .y = 552, .width = 93, .height = 84},
    [SPRITE_ENEMYGREEN2] =
        (Rectangle){.x = 133, .y = 412, .width = 104, .height = 84},
    [SPRITE_ENEMYGREEN3] =
        (Rectangle){.x = 224, .y = 496, .width = 103, .height = 84},
    [SPRITE_ENEMYGREEN4] =
        (Rectangle){.x = 518, .y = 493, .width = 82, .height = 84},
    [SPRITE_ENEMYGREEN5] =
        (Rectangle){.x = 408, .y = 907, .width = 97, .height = 84},
    [SPRITE_ENEMYRED1] =
        (Rectangle){.x = 425, .y = 384, .width = 93, .height = 84},
    [SPRITE_ENEMYRED2] =
        (Rectangle){.x = 120, .y = 520, .width = 104, .height = 84},
    [SPRITE_ENEMYRED3] =
        (Rectangle){.x = 224, .y = 580, .width = 103, .height = 84},
    [SPRITE_ENEMYRED4] =
        (Rectangle){.x = 520, .y = 577, .width = 82, .height = 84},
    [SPRITE_ENEMYRED5] =
        (Rectangle){.x = 423, .y = 644, .width = 97, .height = 84},
    [SPRITE_ENGINE1] =
        (Rectangle){.x = 224, .y = 907, .width = 38, .height = 23},
    [SPRITE_ENGINE2] =
        (Rectangle){.x = 163, .y = 688, .width = 42, .height = 28},
    [SPRITE_ENGINE3] =
        (Rectangle){.x = 644, .y = 1002, .width = 27, .height = 22},
    [SPRITE_ENGINE4] =
        (Rectangle){.x = 144, .y = 240, .width = 49, .height = 45},
    [SPRITE_ENGINE5] =
        (Rectangle){.x = 133, .y = 496, .width = 44, .height = 24},
    [SPRITE_FIRE00] =
        (Rectangle){.x = 827, .y = 125, .width = 16, .height = 40},
    [SPRITE_FIRE01] =
        (Rectangle){.x = 828, .y = 206, .width = 14, .height = 31},
    [SPRITE_FIRE02] =
        (Rectangle){.x = 827, .y = 663, .width = 14, .height = 32},
    [SPRITE_FIRE03] =
        (Rectangle){.x = 829, .y = 437, .width = 14, .height = 34},
    [SPRITE_FIRE04] = (Rectangle){.x = 831, .y = 0, .width = 14, .height = 31},
    [SPRITE_FIRE05] =
        (Rectangle){.x = 834, .y = 299, .width = 14, .height = 31},
    [SPRITE_FIRE06] =
        (Rectangle){.x = 835, .y = 502, .width = 14, .height = 31},
    [SPRITE_FIRE07] =
        (Rectangle){.x = 835, .y = 330, .width = 14, .height = 31},
    [SPRITE_FIRE08] =
        (Rectangle){.x = 827, .y = 867, .width = 16, .height = 40},
    [SPRITE_FIRE09] =
        (Rectangle){.x = 811, .y = 663, .width = 16, .height = 40},
    [SPRITE_FIRE10] =
        (Rectangle){.x = 812, .y = 206, .width = 16, .height = 40},
    [SPRITE_FIRE11] =
        (Rectangle){.x = 835, .y = 395, .width = 14, .height = 31},
    [SPRITE_FIRE12] =
        (Rectangle){.x = 835, .y = 533, .width = 14, .height = 32},
    [SPRITE_FIRE13] =
        (Rectangle){.x = 835, .y = 361, .width = 14, .height = 34},
    [SPRITE_FIRE14] = (Rectangle){.x = 831, .y = 31, .width = 14, .height = 31},
    [SPRITE_FIRE15] =
        (Rectangle){.x = 829, .y = 471, .width = 14, .height = 31},
    [SPRITE_FIRE16] =
        (Rectangle){.x = 828, .y = 268, .width = 14, .height = 31},
    [SPRITE_FIRE17] =
        (Rectangle){.x = 828, .y = 237, .width = 14, .height = 31},
    [SPRITE_FIRE18] =
        (Rectangle){.x = 827, .y = 165, .width = 16, .height = 41},
    [SPRITE_FIRE19] =
        (Rectangle){.x = 812, .y = 246, .width = 16, .height = 41},
    [SPRITE_GUN00] = (Rectangle){.x = 827, .y = 907, .width = 16, .height = 36},
    [SPRITE_GUN01] = (Rectangle){.x = 810, .y = 867, .width = 17, .height = 33},
    [SPRITE_GUN02] = (Rectangle){.x = 829, .y = 611, .width = 14, .height = 36},
    [SPRITE_GUN03] = (Rectangle){.x = 809, .y = 796, .width = 20, .height = 41},
    [SPRITE_GUN04] = (Rectangle){.x = 827, .y = 84, .width = 16, .height = 41},
    [SPRITE_GUN05] = (Rectangle){.x = 423, .y = 0, .width = 21, .height = 41},
    [SPRITE_GUN06] = (Rectangle){.x = 810, .y = 900, .width = 17, .height = 38},
    [SPRITE_GUN07] = (Rectangle){.x = 829, .y = 796, .width = 14, .height = 41},
    [SPRITE_GUN08] = (Rectangle){.x = 848, .y = 263, .width = 10, .height = 47},
    [SPRITE_GUN09] = (Rectangle){.x = 809, .y = 611, .width = 20, .height = 52},
    [SPRITE_GUN10] = (Rectangle){.x = 808, .y = 961, .width = 20, .height = 52},
    [SPRITE_LASERBLUE01] =
        (Rectangle){.x = 856, .y = 421, .width = 9, .height = 54},
    [SPRITE_LASERBLUE02] =
        (Rectangle){.x = 841, .y = 647, .width = 13, .height = 37},
    [SPRITE_LASERBLUE03] =
        (Rectangle){.x = 856, .y = 57, .width = 9, .height = 37},
    [SPRITE_LASERBLUE04] =
        (Rectangle){.x = 835, .y = 565, .width = 13, .height = 37},
    [SPRITE_LASERBLUE05] =
        (Rectangle){.x = 858, .y = 475, .width = 9, .height = 37},
    [SPRITE_LASERBLUE06] =
        (Rectangle){.x = 835, .y = 752, .width = 13, .height = 37},
    [SPRITE_LASERBLUE07] =
        (Rectangle){.x = 856, .y = 775, .width = 9, .height = 37},
    [SPRITE_LASERBLUE08] =
        (Rectangle){.x = 596, .y = 961, .width = 48, .height = 46},
    [SPRITE_LASERBLUE09] =
        (Rectangle){.x = 434, .y = 325, .width = 48, .height = 46},
    [SPRITE_LASERBLUE10] =
        (Rectangle){.x = 740, .y = 724, .width = 37, .height = 37},
    [SPRITE_LASERBLUE11] =
        (Rectangle){.x = 698, .y = 795, .width = 38, .height = 37},
    [SPRITE_LASERBLUE12] =
        (Rectangle){.x = 835, .y = 695, .width = 13, .height = 57},
    [SPRITE_LASERBLUE13] =
        (Rectangle){.x = 856, .y = 869, .width = 9, .height = 57},
    [SPRITE_LASERBLUE14] =
        (Rectangle){.x = 842, .y = 206, .width = 13, .height = 57},
    [SPRITE_LASERBLUE15] =
        (Rectangle){.x = 849, .y = 480, .width = 9, .height = 57},
    [SPRITE_LASERBLUE16] =
        (Rectangle){.x = 843, .y = 62, .width = 13, .height = 54},
    [SPRITE_LASERGREEN01] =
        (Rectangle){.x = 740, .y = 686, .width = 37, .height = 38},
    [SPRITE_LASERGREEN02] =
        (Rectangle){.x = 843, .y = 116, .width = 13, .height = 57},
    [SPRITE_LASERGREEN03] =
        (Rectangle){.x = 855, .y = 173, .width = 9, .height = 57},
    [SPRITE_LASERGREEN04] =
        (Rectangle){.x = 848, .y = 565, .width = 13, .height = 37},
    [SPRITE_LASERGREEN05] =
        (Rectangle){.x = 854, .y = 639, .width = 9, .height = 37},
    [SPRITE_LASERGREEN06] =
        (Rectangle){.x = 845, .y = 0, .width = 13, .height = 57},
    [SPRITE_LASERGREEN07] =
        (Rectangle){.x = 849, .y = 364, .width = 9, .height = 57},
    [SPRITE_LASERGREEN08] =
        (Rectangle){.x = 848, .y = 738, .width = 13, .height = 37},
    [SPRITE_LASERGREEN09] =
        (Rectangle){.x = 856, .y = 94, .width = 9, .height = 37},
    [SPRITE_LASERGREEN10] =
        (Rectangle){.x = 843, .y = 426, .width = 13, .height = 54},
    [SPRITE_LASERGREEN11] =
        (Rectangle){.x = 849, .y = 310, .width = 9, .height = 54},
    [SPRITE_LASERGREEN12] =
        (Rectangle){.x = 843, .y = 602, .width = 13, .height = 37},
    [SPRITE_LASERGREEN13] =
        (Rectangle){.x = 858, .y = 0, .width = 9, .height = 37},
    [SPRITE_LASERGREEN14] =
        (Rectangle){.x = 193, .y = 240, .width = 48, .height = 46},
    [SPRITE_LASERGREEN15] =
        (Rectangle){.x = 443, .y = 182, .width = 48, .height = 46},
    [SPRITE_LASERGREEN16] =
        (Rectangle){.x = 760, .y = 192, .width = 37, .height = 37},
    [SPRITE_LASERRED01] =
        (Rectangle){.x = 858, .y = 230, .width = 9, .height = 54},
    [SPRITE_LASERRED02] =
        (Rectangle){.x = 843, .y = 977, .width = 13, .height = 37},
    [SPRITE_LASERRED03] =
        (Rectangle){.x = 856, .y = 602, .width = 9, .height = 37},
    [SPRITE_LASERRED04] =
        (Rectangle){.x = 843, .y = 940, .width = 13, .height = 37},
    [SPRITE_LASERRED05] =
        (Rectangle){.x = 856, .y = 983, .width = 9, .height = 37},
    [SPRITE_LASERRED06] =
        (Rectangle){.x = 843, .y = 903, .width = 13, .height = 37},
    [SPRITE_LASERRED07] =
        (Rectangle){.x = 856, .y = 131, .width = 9, .height = 37},
    [SPRITE_LASERRED08] =
        (Rectangle){.x = 580, .y = 661, .width = 48, .height = 46},
    [SPRITE_LASERRED09] =
        (Rectangle){.x = 602, .y = 600, .width = 48, .height = 46},
    [SPRITE_LASERRED10] =
        (Rectangle){.x = 738, .y = 650, .width = 37, .height = 36},
    [SPRITE_LASERRED11] =
        (Rectangle){.x = 737, .y = 613, .width = 37, .height = 37},
    [SPRITE_LASERRED12] =
        (Rectangle){.x = 843, .y = 846, .width = 13, .height = 57},
    [SPRITE_LASERRED13] =
        (Rectangle){.x = 856, .y = 812, .width = 9, .height = 57},
    [SPRITE_LASERRED14] =
        (Rectangle){.x = 843, .y = 789, .width = 13, .height = 57},
    [SPRITE_LASERRED15] =
        (Rectangle){.x = 856, .y = 926, .width = 9, .height = 57},
    [SPRITE_LASERRED16] =
        (Rectangle){.x = 848, .y = 684, .width = 13, .height = 54},
    [SPRITE_METEORBROWN_BIG1] =
        (Rectangle){.x = 224, .y = 664, .width = 101, .height = 84},
    [SPRITE_METEORBROWN_BIG2] =
        (Rectangle){.x = 0, .y = 520, .width = 120, .height = 98},
    [SPRITE_METEORBROWN_BIG3] =
        (Rectangle){.x = 518, .y = 810, .width = 89, .height = 82},
    [SPRITE_METEORBROWN_BIG4] =
        (Rectangle){.x = 327, .y = 452, .width = 98, .height = 96},
    [SPRITE_METEORBROWN_MED1] =
        (Rectangle){.x = 651, .y = 447, .width = 43, .height = 43},
    [SPRITE_METEORBROWN_MED3] =
        (Rectangle){.x = 237, .y = 452, .width = 45, .height = 40},
    [SPRITE_METEORBROWN_SMALL1] =
        (Rectangle){.x = 406, .y = 234, .width = 28, .height = 28},
    [SPRITE_METEORBROWN_SMALL2] =
        (Rectangle){.x = 778, .y = 587, .width = 29, .height = 26},
    [SPRITE_METEORBROWN_TINY1] =
        (Rectangle){.x = 346, .y = 814, .width = 18, .height = 18},
    [SPRITE_METEORBROWN_TINY2] =
        (Rectangle){.x = 399, .y = 814, .width = 16, .height = 15},
    [SPRITE_METEORGREY_BIG1] =
        (Rectangle){.x = 224, .y = 748, .width = 101, .height = 84},
    [SPRITE_METEORGREY_BIG2] =
        (Rectangle){.x = 0, .y = 618, .width = 120, .height = 98},
    [SPRITE_METEORGREY_BIG3] =
        (Rectangle){.x = 516, .y = 728, .width = 89, .height = 82},
    [SPRITE_METEORGREY_BIG4] =
        (Rectangle){.x = 327, .y = 548, .width = 98, .height = 96},
    [SPRITE_METEORGREY_MED1] =
        (Rectangle){.x = 674, .y = 219, .width = 43, .height = 43},
    [SPRITE_METEORGREY_MED2] =
        (Rectangle){.x = 282, .y = 452, .width = 45, .height = 40},
    [SPRITE_METEORGREY_SMALL1] =
        (Rectangle){.x = 406, .y = 262, .width = 28, .height = 28},
    [SPRITE_METEORGREY_SMALL2] =
        (Rectangle){.x = 396, .y = 413, .width = 29, .height = 26},
    [SPRITE_METEORGREY_TINY1] =
        (Rectangle){.x = 364, .y = 814, .width = 18, .height = 18},
    [SPRITE_METEORGREY_TINY2] =
        (Rectangle){.x = 602, .y = 646, .width = 16, .height = 15},
    [SPRITE_NUMERAL0] =
        (Rectangle){.x = 367, .y = 644, .width = 19, .height = 19},
    [SPRITE_NUMERAL1] =
        (Rectangle){.x = 205, .y = 688, .width = 19, .height = 19},
    [SPRITE_NUMERAL2] =
        (Rectangle){.x = 406, .y = 290, .width = 19, .height = 19},
    [SPRITE_NUMERAL3] =
        (Rectangle){.x = 580, .y = 707, .width = 19, .height = 19},
    [SPRITE_NUMERAL4] =
        (Rectangle){.x = 386, .y = 644, .width = 19, .height = 19},
    [SPRITE_NUMERAL5] =
        (Rectangle){.x = 628, .y = 646, .width = 19, .height = 19},
    [SPRITE_NUMERAL6] =
        (Rectangle){.x = 671, .y = 1002, .width = 19, .height = 19},
    [SPRITE_NUMERAL7] =
        (Rectangle){.x = 690, .y = 1004, .width = 19, .height = 19},
    [SPRITE_NUMERAL8] =
        (Rectangle){.x = 709, .y = 1004, .width = 19, .height = 19},
    [SPRITE_NUMERAL9] =
        (Rectangle){.x = 491, .y = 215, .width = 19, .height = 19},
    [SPRITE_NUMERALX] =
        (Rectangle){.x = 382, .y = 814, .width = 17, .height = 17},
    [SPRITE_PILL_BLUE] =
        (Rectangle){.x = 674, .y = 262, .width = 22, .height = 21},
    [SPRITE_PILL_GREEN] =
        (Rectangle){.x = 573, .y = 989, .width = 22, .height = 21},
    [SPRITE_PILL_RED] =
        (Rectangle){.x = 222, .y = 108, .width = 22, .height = 21},
    [SPRITE_PILL_YELLOW] =
        (Rectangle){.x = 222, .y = 129, .width = 22, .height = 21},
    [SPRITE_PLAYERLIFE1_BLUE] =
        (Rectangle){.x = 482, .y = 358, .width = 33, .height = 26},
    [SPRITE_PLAYERLIFE1_GREEN] =
        (Rectangle){.x = 535, .y = 150, .width = 33, .height = 26},
    [SPRITE_PLAYERLIFE1_ORANGE] =
        (Rectangle){.x = 777, .y = 327, .width = 33, .height = 26},
    [SPRITE_PLAYERLIFE1_RED] =
        (Rectangle){.x = 775, .y = 301, .width = 33, .height = 26},
    [SPRITE_PLAYERLIFE2_BLUE] =
        (Rectangle){.x = 465, .y = 991, .width = 37, .height = 26},
    [SPRITE_PLAYERLIFE2_GREEN] =
        (Rectangle){.x = 391, .y = 991, .width = 37, .height = 26},
    [SPRITE_PLAYERLIFE2_ORANGE] =
        (Rectangle){.x = 428, .y = 991, .width = 37, .height = 26},
    [SPRITE_PLAYERLIFE2_RED] =
        (Rectangle){.x = 502, .y = 991, .width = 37, .height = 26},
    [SPRITE_PLAYERLIFE3_BLUE] =
        (Rectangle){.x = 777, .y = 385, .width = 32, .height = 26},
    [SPRITE_PLAYERLIFE3_GREEN] =
        (Rectangle){.x = 778, .y = 469, .width = 32, .height = 26},
    [SPRITE_PLAYERLIFE3_ORANGE] =
        (Rectangle){.x = 777, .y = 712, .width = 32, .height = 26},
    [SPRITE_PLAYERLIFE3_RED] =
        (Rectangle){.x = 777, .y = 443, .width = 32, .height = 26},
    [SPRITE_PLAYERSHIP1_BLUE] =
        (Rectangle){.x = 211, .y = 941, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_DAMAGE1] =
        (Rectangle){.x = 112, .y = 941, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_DAMAGE2] =
        (Rectangle){.x = 247, .y = 234, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_DAMAGE3] =
        (Rectangle){.x = 247, .y = 159, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_GREEN] =
        (Rectangle){.x = 237, .y = 377, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_ORANGE] =
        (Rectangle){.x = 247, .y = 84, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP1_RED] =
        (Rectangle){.x = 224, .y = 832, .width = 99, .height = 75},
    [SPRITE_PLAYERSHIP2_BLUE] =
        (Rectangle){.x = 112, .y = 791, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_DAMAGE1] =
        (Rectangle){.x = 0, .y = 866, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_DAMAGE2] =
        (Rectangle){.x = 0, .y = 791, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_DAMAGE3] =
        (Rectangle){.x = 0, .y = 716, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_GREEN] =
        (Rectangle){.x = 112, .y = 866, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_ORANGE] =
        (Rectangle){.x = 112, .y = 716, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP2_RED] =
        (Rectangle){.x = 0, .y = 941, .width = 112, .height = 75},
    [SPRITE_PLAYERSHIP3_BLUE] =
        (Rectangle){.x = 325, .y = 739, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_DAMAGE1] =
        (Rectangle){.x = 323, .y = 832, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_DAMAGE2] =
        (Rectangle){.x = 310, .y = 907, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_DAMAGE3] =
        (Rectangle){.x = 325, .y = 664, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_GREEN] =
        (Rectangle){.x = 346, .y = 75, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_ORANGE] =
        (Rectangle){.x = 336, .y = 309, .width = 98, .height = 75},
    [SPRITE_PLAYERSHIP3_RED] =
        (Rectangle){.x = 325, .y = 0, .width = 98, .height = 75},
    [SPRITE_POWERUPBLUE] =
        (Rectangle){.x = 696, .y = 329, .width = 34, .height = 33},
    [SPRITE_POWERUPBLUE_BOLT] =
        (Rectangle){.x = 539, .y = 989, .width = 34, .height = 33},
    [SPRITE_POWERUPBLUE_SHIELD] =
        (Rectangle){.x = 777, .y = 679, .width = 34, .height = 33},
    [SPRITE_POWERUPBLUE_STAR] =
        (Rectangle){.x = 776, .y = 895, .width = 34, .height = 33},
    [SPRITE_POWERUPGREEN] =
        (Rectangle){.x = 774, .y = 613, .width = 34, .height = 33},
    [SPRITE_POWERUPGREEN_BOLT] =
        (Rectangle){.x = 766, .y = 80, .width = 34, .height = 33},
    [SPRITE_POWERUPGREEN_SHIELD] =
        (Rectangle){.x = 776, .y = 862, .width = 34, .height = 33},
    [SPRITE_POWERUPGREEN_STAR] =
        (Rectangle){.x = 651, .y = 490, .width = 34, .height = 33},
    [SPRITE_POWERUPRED] =
        (Rectangle){.x = 491, .y = 182, .width = 34, .height = 33},
    [SPRITE_POWERUPRED_BOLT] =
        (Rectangle){.x = 775, .y = 646, .width = 34, .height = 33},
    [SPRITE_POWERUPRED_SHIELD] =
        (Rectangle){.x = 776, .y = 928, .width = 34, .height = 33},
    [SPRITE_POWERUPRED_STAR] =
        (Rectangle){.x = 774, .y = 977, .width = 34, .height = 33},
    [SPRITE_POWERUPYELLOW] =
        (Rectangle){.x = 774, .y = 761, .width = 34, .height = 33},
    [SPRITE_POWERUPYELLOW_BOLT] =
        (Rectangle){.x = 740, .y = 761, .width = 34, .height = 33},
    [SPRITE_POWERUPYELLOW_SHIELD] =
        (Rectangle){.x = 482, .y = 325, .width = 34, .height = 33},
    [SPRITE_POWERUPYELLOW_STAR] =
        (Rectangle){.x = 607, .y = 857, .width = 34, .height = 33},
    [SPRITE_SCRATCH1] =
        (Rectangle){.x = 325, .y = 814, .width = 21, .height = 16},
    [SPRITE_SCRATCH2] =
        (Rectangle){.x = 423, .y = 41, .width = 21, .height = 16},
    [SPRITE_SCRATCH3] =
        (Rectangle){.x = 346, .y = 295, .width = 16, .height = 12},
    [SPRITE_SHIELD1] =
        (Rectangle){.x = 0, .y = 412, .width = 133, .height = 108},
    [SPRITE_SHIELD2] =
        (Rectangle){.x = 0, .y = 293, .width = 143, .height = 119},
    [SPRITE_SHIELD3] =
        (Rectangle){.x = 0, .y = 156, .width = 144, .height = 137},
    [SPRITE_SHIELD_BRONZE] =
        (Rectangle){.x = 797, .y = 143, .width = 30, .height = 30},
    [SPRITE_SHIELD_GOLD] =
        (Rectangle){.x = 797, .y = 113, .width = 30, .height = 30},
    [SPRITE_SHIELD_SILVER] =
        (Rectangle){.x = 778, .y = 824, .width = 30, .height = 30},
    [SPRITE_SPEED] = (Rectangle){.x = 858, .y = 284, .width = 7, .height = 108},
    [SPRITE_STAR1] = (Rectangle){.x = 628, .y = 681, .width = 25, .height = 24},
    [SPRITE_STAR2] = (Rectangle){.x = 222, .y = 84, .width = 25, .height = 24},
    [SPRITE_STAR3] = (Rectangle){.x = 576, .y = 300, .width = 24, .height = 24},
    [SPRITE_STAR_BRONZE] =
        (Rectangle){.x = 778, .y = 794, .width = 31, .height = 30},
    [SPRITE_STAR_GOLD] =
        (Rectangle){.x = 778, .y = 557, .width = 31, .height = 30},
    [SPRITE_STAR_SILVER] =
        (Rectangle){.x = 778, .y = 527, .width = 31, .height = 30},
    [SPRITE_THINGS_BRONZE] =
        (Rectangle){.x = 778, .y = 495, .width = 32, .height = 32},
    [SPRITE_THINGS_GOLD] =
        (Rectangle){.x = 777, .y = 411, .width = 32, .height = 32},
    [SPRITE_THINGS_SILVER] =
        (Rectangle){.x = 777, .y = 353, .width = 32, .height = 32},
    [SPRITE_TURRETBASE_BIG] =
        (Rectangle){.x = 310, .y = 982, .width = 41, .height = 41},
    [SPRITE_TURRETBASE_SMALL] =
        (Rectangle){.x = 808, .y = 301, .width = 26, .height = 26},
    [SPRITE_UFOBLUE] =
        (Rectangle){.x = 444, .y = 91, .width = 91, .height = 91},
    [SPRITE_UFOGREEN] =
        (Rectangle){.x = 434, .y = 234, .width = 91, .height = 91},
    [SPRITE_UFORED] = (Rectangle){.x = 444, .y = 0, .width = 91, .height = 91},
    [SPRITE_UFOYELLOW] =
        (Rectangle){.x = 505, .y = 898, .width = 91, .height = 91},
    [SPRITE_WINGBLUE_0] =
        (Rectangle){.x = 647, .y = 924, .width = 45, .height = 78},
    [SPRITE_WINGBLUE_1] =
        (Rectangle){.x = 738, .y = 253, .width = 37, .height = 72},
    [SPRITE_WINGBLUE_2] =
        (Rectangle){.x = 805, .y = 0, .width = 26, .height = 84},
    [SPRITE_WINGBLUE_3] =
        (Rectangle){.x = 600, .y = 450, .width = 51, .height = 75},
    [SPRITE_WINGBLUE_4] =
        (Rectangle){.x = 692, .y = 924, .width = 42, .height = 80},
    [SPRITE_WINGBLUE_5] =
        (Rectangle){.x = 596, .y = 892, .width = 51, .height = 69},
    [SPRITE_WINGBLUE_6] =
        (Rectangle){.x = 694, .y = 847, .width = 42, .height = 74},
    [SPRITE_WINGBLUE_7] =
        (Rectangle){.x = 675, .y = 134, .width = 43, .height = 83},
    [SPRITE_WINGGREEN_0] =
        (Rectangle){.x = 650, .y = 525, .width = 45, .height = 78},
    [SPRITE_WINGGREEN_1] =
        (Rectangle){.x = 775, .y = 229, .width = 37, .height = 72},
    [SPRITE_WINGGREEN_2] =
        (Rectangle){.x = 809, .y = 527, .width = 26, .height = 84},
    [SPRITE_WINGGREEN_3] =
        (Rectangle){.x = 535, .y = 0, .width = 51, .height = 75},
    [SPRITE_WINGGREEN_4] =
        (Rectangle){.x = 694, .y = 431, .width = 42, .height = 80},
    [SPRITE_WINGGREEN_5] =
        (Rectangle){.x = 525, .y = 251, .width = 51, .height = 69},
    [SPRITE_WINGGREEN_6] =
        (Rectangle){.x = 695, .y = 511, .width = 42, .height = 74},
    [SPRITE_WINGGREEN_7] =
        (Rectangle){.x = 655, .y = 764, .width = 43, .height = 83},
    [SPRITE_WINGRED_0] =
        (Rectangle){.x = 809, .y = 712, .width = 26, .height = 84},
    [SPRITE_WINGRED_1] =
        (Rectangle){.x = 768, .y = 0, .width = 37, .height = 72},
    [SPRITE_WINGRED_2] =
        (Rectangle){.x = 600, .y = 300, .width = 51, .height = 75},
    [SPRITE_WINGRED_3] =
        (Rectangle){.x = 698, .y = 715, .width = 42, .height = 80},
    [SPRITE_WINGRED_4] =
        (Rectangle){.x = 586, .y = 75, .width = 51, .height = 69},
    [SPRITE_WINGRED_5] =
        (Rectangle){.x = 718, .y = 123, .width = 42, .height = 74},
    [SPRITE_WINGRED_6] =
        (Rectangle){.x = 653, .y = 681, .width = 43, .height = 83},
    [SPRITE_WINGRED_7] =
        (Rectangle){.x = 651, .y = 286, .width = 45, .height = 78},
    [SPRITE_WINGYELLOW_0] =
        (Rectangle){.x = 650, .y = 603, .width = 45, .height = 78},
    [SPRITE_WINGYELLOW_1] =
        (Rectangle){.x = 760, .y = 120, .width = 37, .height = 72},
    [SPRITE_WINGYELLOW_2] =
        (Rectangle){.x = 809, .y = 353, .width = 26, .height = 84},
    [SPRITE_WINGYELLOW_3] =
        (Rectangle){.x = 576, .y = 150, .width = 51, .height = 75},
    [SPRITE_WINGYELLOW_4] =
        (Rectangle){.x = 726, .y = 0, .width = 42, .height = 80},
    [SPRITE_WINGYELLOW_5] =
        (Rectangle){.x = 525, .y = 182, .width = 51, .height = 69},
    [SPRITE_WINGYELLOW_6] =
        (Rectangle){.x = 695, .y = 585, .width = 42, .height = 74},
    [SPRITE_WINGYELLOW_7] =
        (Rectangle){.x = 651, .y = 364, .width = 43, .height = 83},
};
