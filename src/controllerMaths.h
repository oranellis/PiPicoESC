#include "pico/types.h"

#define N_POLES 2
#define V_S_FALLBACK 400


int fastsin[] = {0, 201, 402, 603, 804, 1005, 1206, 1407, 1608, 1809, 2009, 2210, 2411, 2611, 2811, 3012, 
    3212, 3412, 3612, 3812, 4011, 4211, 4410, 4609, 4808, 5007, 5205, 5404, 5602, 5800, 5998, 6195, 
    6393, 6590, 6787, 6983, 7180, 7376, 7571, 7767, 7962, 8157, 8351, 8546, 8740, 8933, 9127, 9319, 
    9512, 9704, 9896, 10088, 10279, 10469, 10660, 10850, 11039, 11228, 11417, 11605, 11793, 11980, 12167, 12354, 
    12540, 12725, 12910, 13095, 13279, 13463, 13646, 13828, 14010, 14192, 14373, 14553, 14733, 14912, 15091, 15269, 
    15447, 15624, 15800, 15976, 16151, 16326, 16500, 16673, 16846, 17018, 17190, 17361, 17531, 17700, 17869, 18037, 
    18205, 18372, 18538, 18703, 18868, 19032, 19195, 19358, 19520, 19681, 19841, 20001, 20160, 20318, 20475, 20632, 
    20788, 20943, 21097, 21251, 21403, 21555, 21706, 21856, 22006, 22154, 22302, 22449, 22595, 22740, 22884, 23028, 
    23170, 23312, 23453, 23593, 23732,23870, 24008, 24144, 24279, 24414, 24548, 24680, 24812, 24943, 25073, 25202, 
    25330, 25457, 25583, 25708, 25833, 25956, 26078, 26199, 26320, 26439, 26557, 26674, 26791, 26906, 27020, 27133, 
    27246, 27357, 27467, 27576, 27684, 27791, 27897, 28002, 28106, 28209, 28311, 28411, 28511, 28610, 28707, 28803, 
    28899, 28993, 29086, 29178, 29269, 29359, 29448, 29535, 29622, 29707, 29792, 29875, 29957, 30038, 30118, 30196, 
    30274, 30350, 30425, 30499, 30572, 30644, 30715, 30784, 30853, 30920, 30986, 31050, 31114, 31177, 31238, 31298, 
    31357, 31415, 31471, 31527, 31581, 31634, 31686, 31737, 31786, 31834, 31881, 31927, 31972, 32015, 32058, 32099, 
    32138, 32177, 32214, 32251, 32286, 32319,32352, 32383, 32413, 32442, 32470, 32496, 32522, 32546, 32568, 32590, 
    32610, 32629, 32647, 32664, 32679, 32693, 32706, 32718, 32729, 32738, 32746, 32753, 32758, 32762, 32766, 32767, 
    32768, 32767, 32766, 32762, 32758, 32753, 32746, 32738, 32729, 32718, 32706, 32693, 32679, 32664, 32647, 32629, 
    32610, 32590, 32568, 32546, 32522, 32496, 32470, 32442, 32413, 32383, 32352, 32319, 32286, 32251, 32214, 32177, 
    32138, 32099, 32058, 32015, 31972, 31927, 31881, 31834, 31786, 31737, 31686, 31634, 31581, 31527, 31471, 31415, 
    31357, 31298, 31238, 31177, 31114, 31050, 30986, 30920, 30853, 30784, 30715, 30644, 30572, 30499, 30425, 30350, 
    30274, 30196, 30118, 30038, 29957, 29875, 29792,29707, 29622, 29535, 29448, 29359, 29269, 29178, 29086, 28993, 
    28899, 28803, 28707, 28610, 28511, 28411, 28311, 28209, 28106, 28002, 27897, 27791, 27684, 27576, 27467, 27357, 
    27246, 27133, 27020, 26906, 26791, 26674, 26557, 26439, 26320, 26199, 26078, 25956, 25833, 25708, 25583, 25457, 
    25330, 25202, 25073, 24943, 24812, 24680, 24548, 24414, 24279, 24144, 24008, 23870, 23732, 23593, 23453, 23312, 
    23170, 23028, 22884, 22740, 22595, 22449, 22302, 22154, 22006, 21856, 21706, 21555, 21403, 21251, 21097, 20943, 
    20788, 20632, 20475, 20318, 20160, 20001, 19841, 19681, 19520, 19358, 19195, 19032, 18868, 18703, 18538, 18372, 
    18205, 18037, 17869, 17700, 17531, 17361, 17190, 17018,16846, 16673, 16500, 16326, 16151, 15976, 15800, 15624, 
    15447, 15269, 15091, 14912, 14733, 14553, 14373, 14192, 14010, 13828, 13646, 13463, 13279, 13095, 12910, 12725, 
    12540, 12354, 12167, 11980, 11793, 11605, 11417, 11228, 11039, 10850, 10660, 10469, 10279, 10088, 9896, 9704, 
    9512, 9319, 9127, 8933, 8740, 8546, 8351, 8157, 7962, 7767, 7571, 7376, 7180, 6983, 6787, 6590, 
    6393, 6195, 5998, 5800, 5602, 5404, 5205, 5007, 4808, 4609, 4410, 4211, 4011, 3812, 3612, 3412, 
    3212, 3012, 2811, 2611, 2411, 2210, 2009, 1809, 1608, 1407, 1206, 1005, 804, 603, 402, 201, 
    0, -201, -402, -603, -804, -1005, -1206, -1407, -1608, -1809, -2009, -2210, -2411, -2611, -2811, -3012, 
    -3212, -3412, -3612, -3812, -4011, -4211, -4410, -4609, -4808, -5007, -5205, -5404, -5602, -5800, -5998, -6195, 
    -6393, -6590, -6787, -6983, -7180, -7376, -7571, -7767, -7962, -8157, -8351, -8546, -8740, -8933, -9127, -9319, 
    -9512, -9704, -9896, -10088, -10279, -10469, -10660, -10850, -11039, -11228, -11417, -11605, -11793, -11980, -12167, -12354, 
    -12540, -12725, -12910, -13095, -13279, -13463, -13646, -13828, -14010, -14192, -14373, -14553, -14733, -14912, -15091, -15269, 
    -15447, -15624, -15800, -15976, -16151, -16326, -16500, -16673, -16846, -17018, -17190, -17361, -17531, -17700, -17869, -18037, 
    -18205, -18372, -18538, -18703, -18868, -19032, -19195, -19358, -19520, -19681, -19841, -20001, -20160, -20318, -20475, -20632, 
    -20788, -20943, -21097, -21251, -21403, -21555, -21706,-21856, -22006, -22154, -22302, -22449, -22595, -22740, -22884, -23028, 
    -23170, -23312, -23453, -23593, -23732, -23870, -24008, -24144, -24279, -24414, -24548, -24680, -24812, -24943, -25073, -25202, 
    -25330, -25457, -25583, -25708, -25833, -25956, -26078, -26199, -26320, -26439, -26557, -26674, -26791, -26906, -27020, -27133, 
    -27246, -27357, -27467, -27576, -27684, -27791, -27897, -28002, -28106, -28209, -28311, -28411, -28511, -28610, -28707, -28803, 
    -28899, -28993, -29086, -29178, -29269, -29359, -29448, -29535, -29622, -29707, -29792, -29875, -29957, -30038, -30118, -30196, 
    -30274, -30350, -30425, -30499, -30572, -30644, -30715, -30784, -30853, -30920, -30986, -31050, -31114, -31177, -31238, -31298, 
    -31357, -31415, -31471, -31527, -31581, -31634, -31686, -31737,-31786, -31834, -31881, -31927, -31972, -32015, -32058, -32099, 
    -32138, -32177, -32214, -32251, -32286, -32319, -32352, -32383, -32413, -32442, -32470, -32496, -32522, -32546, -32568, -32590, 
    -32610, -32629, -32647, -32664, -32679, -32693, -32706, -32718, -32729, -32738, -32746, -32753, -32758, -32762, -32766, -32767, 
    -32768, -32767, -32766, -32762, -32758, -32753, -32746, -32738, -32729, -32718, -32706, -32693, -32679, -32664, -32647, -32629, 
    -32610, -32590, -32568, -32546, -32522, -32496, -32470, -32442, -32413, -32383, -32352, -32319, -32286, -32251, -32214, -32177, 
    -32138, -32099, -32058, -32015, -31972, -31927, -31881, -31834, -31786, -31737, -31686, -31634, -31581, -31527, -31471, -31415, 
    -31357, -31298, -31238, -31177, -31114, -31050, -30986, -30920, -30853,-30784, -30715, -30644, -30572, -30499, -30425, -30350, 
    -30274, -30196, -30118, -30038, -29957, -29875, -29792, -29707, -29622, -29535, -29448, -29359, -29269, -29178, -29086, -28993, 
    -28899, -28803, -28707, -28610, -28511, -28411, -28311, -28209, -28106, -28002, -27897, -27791, -27684, -27576, -27467, -27357, 
    -27246, -27133, -27020, -26906, -26791, -26674, -26557, -26439, -26320, -26199, -26078, -25956, -25833, -25708, -25583, -25457, 
    -25330, -25202, -25073, -24943, -24812, -24680, -24548, -24414, -24279, -24144, -24008, -23870, -23732, -23593, -23453, -23312, 
    -23170, -23028, -22884, -22740, -22595, -22449, -22302, -22154, -22006, -21856, -21706, -21555, -21403, -21251, -21097, -20943, 
    -20788, -20632, -20475, -20318, -20160, -20001, -19841, -19681, -19520, -19358,-19195, -19032, -18868, -18703, -18538, -18372, 
    -18205, -18037, -17869, -17700, -17531, -17361, -17190, -17018, -16846, -16673, -16500, -16326, -16151, -15976, -15800, -15624, 
    -15447, -15269, -15091, -14912, -14733, -14553, -14373, -14192, -14010, -13828, -13646, -13463, -13279, -13095, -12910, -12725, 
    -12540, -12354, -12167, -11980, -11793, -11605, -11417, -11228, -11039, -10850, -10660, -10469, -10279, -10088, -9896, -9704, 
    -9512, -9319, -9127, -8933, -8740, -8546, -8351, -8157, -7962, -7767, -7571, -7376, -7180, -6983, -6787, -6590, 
    -6393, -6195, -5998, -5800, -5602, -5404, -5205, -5007, -4808, -4609, -4410, -4211, -4011, -3812, -3612, -3412, 
    -3212, -3012, -2811, -2611, -2411, -2210, -2009, -1809, -1608, -1407, -1206, -1005, -804, -603, -402, -201, 0, 0};


void generatePWMs() {

    int va = 0;
    int vb = 0;
    int vc = 0;

    // Target phase voltages for phases a, b and c

    int v1; unsigned short pw1;
    int v2; unsigned short pw2;
    int v3; unsigned short pw3;

    double vCommand;

    // The voltages at terminals 1, 2, and 3. Pulse width fraction at terminals 1, 2 and 3
    //
    // pulse width goes from 0 to 8,192 (2^13)

    if (va <= vb) {
        if (va <= vc) {
            v1 = 0;
            v2 = vb - va;
            v3 = vc - va;
        }
        else {
            v1 = va - vc;
            v2 = vb - vc;
            v3 = 0;
        }
    }
    else {
        if (vb <= vc) {
            v1 = va - vb;
            v2 = 0;
            v3 = vc - vb;
        }
        else {
            v1 = va - vc;
            v2 = vb - vc;
            v3 = 0;
        }
    }

    pw1 = v1 * vCommand;
    pw2 = v2 * vCommand;
    pw3 = v3 * vCommand;

}
