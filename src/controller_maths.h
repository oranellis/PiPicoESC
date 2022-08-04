#define N_POLES 2
#define V_S_FALLBACK 400

// 1024 values of sin ranging between -32768 and 32767
int fastsin[] = {
0, 17, 34, 50, 67, 84, 101, 117, 134, 151, 168, 184, 201, 218, 234, 251, 268, 285, 301, 318, 335, 351, 368, 385, 401, 418, 435, 451, 468, 485, 501, 518, 535, 551, 568, 584, 601, 618, 634, 651, 667, 684, 700, 717, 733, 750, 766, 783, 799, 816, 832, 848, 865, 881, 897, 914, 930, 946, 963, 979, 995, 1011, 1028, 1044, 1060, 1076, 1092, 1109, 1125, 1141, 1157, 1173, 1189, 1205, 1221, 1237, 1253, 1269, 1285, 1301, 1317, 1332, 1348, 1364, 1380, 1396, 1411, 1427, 1443, 1458, 1474, 1490, 1505, 1521, 1536, 1552, 1567, 1583, 1598, 1614, 1629, 1645, 1660, 1675, 1690, 1706, 1721, 1736, 1751, 1766, 1781, 1797, 1812, 1827, 1842, 1857, 1871, 1886, 1901, 1916, 1931, 1946, 1960, 1975, 1990, 2004, 2019, 2033, 2048, 2062, 2077, 2091, 2106, 2120, 2134, 2149, 2163, 2177, 2191, 2205, 2220, 2234, 2248, 2262, 2276, 2290, 2303, 2317, 2331, 2345, 2359, 2372, 2386, 2399, 2413, 2427, 2440, 2453, 2467, 2480, 2493, 2507, 2520, 2533, 2546, 2559, 2572, 2586, 2598, 2611, 2624, 2637, 2650, 2663, 2675, 2688, 2701, 2713, 2726, 2738, 2751, 2763, 2775, 2788, 2800, 2812, 2824, 2836, 2849, 2861, 2873, 2884, 2896, 2908, 2920, 2932, 2943, 2955, 2967, 2978, 2990, 3001, 3012, 3024, 3035, 3046, 3057, 3068, 3080, 3091, 3102, 3112, 3123, 3134, 3145, 3156, 3166, 3177, 3187, 3198, 3208, 3219, 3229, 3239, 3250, 3260, 3270, 3280, 3290, 3300, 3310, 3320, 3329, 3339, 3349, 3358, 3368, 3378, 3387, 3396, 3406, 3415, 3424, 3433, 3442, 3452, 3461, 3469, 3478, 3487, 3496, 3505, 3513, 3522, 3530, 3539, 3547, 3556, 3564, 3572, 3580, 3588, 3596, 3604, 3612, 3620, 3628, 3636, 3643, 3651, 3659, 3666, 3674, 3681, 3688, 3696, 3703, 3710, 3717, 3724, 3731, 3738, 3745, 3751, 3758, 3765, 3771, 3778, 3784, 3791, 3797, 3803, 3809, 3815, 3822, 3828, 3833, 3839, 3845, 3851, 3857, 3862, 3868, 3873, 3879, 3884, 3889, 3894, 3900, 3905, 3910, 3915, 3920, 3924, 3929, 3934, 3939, 3943, 3948, 3952, 3956, 3961, 3965, 3969, 3973, 3977, 3981, 3985, 3989, 3993, 3996, 4000, 4004, 4007, 4011, 4014, 4017, 4021, 4024, 4027, 4030, 4033, 4036, 4039, 4041, 4044, 4047, 4049, 4052, 4054, 4056, 4059, 4061, 4063, 4065, 4067, 4069, 4071, 4073, 4075, 4076, 4078, 4079, 4081, 4082, 4084, 4085, 4086, 4087, 4088, 4089, 4090, 4091, 4092, 4093, 4093, 4094, 4094, 4095, 4095, 4095, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4095, 4095, 4095, 4094, 4094, 4093, 4093, 4092, 4091, 4090, 4089, 4088, 4087, 4086, 4085, 4084, 4082, 4081, 4079, 4078, 4076, 4075, 4073, 4071, 4069, 4067, 4065, 4063, 4061, 4059, 4056, 4054, 4052, 4049, 4047, 4044, 4041, 4039, 4036, 4033, 4030, 4027, 4024, 4021, 4017, 4014, 4011, 4007, 4004, 4000, 3996, 3993, 3989, 3985, 3981, 3977, 3973, 3969, 3965, 3961, 3956, 3952, 3948, 3943, 3939, 3934, 3929, 3924, 3920, 3915, 3910, 3905, 3900, 3894, 3889, 3884, 3879, 3873, 3868, 3862, 3857, 3851, 3845, 3839, 3833, 3828, 3822, 3815, 3809, 3803, 3797, 3791, 3784, 3778, 3771, 3765, 3758, 3751, 3745, 3738, 3731, 3724, 3717, 3710, 3703, 3696, 3688, 3681, 3674, 3666, 3659, 3651, 3643, 3636, 3628, 3620, 3612, 3604, 3596, 3588, 3580, 3572, 3564, 3556, 3547, 3539, 3530, 3522, 3513, 3505, 3496, 3487, 3478, 3469, 3461, 3452, 3442, 3433, 3424, 3415, 3406, 3396, 3387, 3378, 3368, 3358, 3349, 3339, 3329, 3320, 3310, 3300, 3290, 3280, 3270, 3260, 3250, 3239, 3229, 3219, 3208, 3198, 3187, 3177, 3166, 3156, 3145, 3134, 3123, 3112, 3102, 3091, 3080, 3068, 3057, 3046, 3035, 3024, 3012, 3001, 2990, 2978, 2967, 2955, 2943, 2932, 2920, 2908, 2896, 2884, 2873, 2861, 2849, 2836, 2824, 2812, 2800, 2788, 2775, 2763, 2751, 2738, 2726, 2713, 2701, 2688, 2675, 2663, 2650, 2637, 2624, 2611, 2598, 2586, 2572, 2559, 2546, 2533, 2520, 2507, 2493, 2480, 2467, 2453, 2440, 2427, 2413, 2399, 2386, 2372, 2359, 2345, 2331, 2317, 2303, 2290, 2276, 2262, 2248, 2234, 2220, 2205, 2191, 2177, 2163, 2149, 2134, 2120, 2106, 2091, 2077, 2062, 2048, 2033, 2019, 2004, 1990, 1975, 1960, 1946, 1931, 1916, 1901, 1886, 1871, 1857, 1842, 1827, 1812, 1797, 1781, 1766, 1751, 1736, 1721, 1706, 1690, 1675, 1660, 1645, 1629, 1614, 1598, 1583, 1567, 1552, 1536, 1521, 1505, 1490, 1474, 1458, 1443, 1427, 1411, 1396, 1380, 1364, 1348, 1332, 1317, 1301, 1285, 1269, 1253, 1237, 1221, 1205, 1189, 1173, 1157, 1141, 1125, 1109, 1092, 1076, 1060, 1044, 1028, 1011, 995, 979, 963, 946, 930, 914, 897, 881, 865, 848, 832, 816, 799, 783, 766, 750, 733, 717, 700, 684, 667, 651, 634, 618, 601, 584, 568, 551, 535, 518, 501, 485, 468, 451, 435, 418, 401, 385, 368, 351, 335, 318, 301, 285, 268, 251, 234, 218, 201, 184, 168, 151, 134, 117, 101, 84, 67, 50, 34, 17, 0, -17, -34, -50, -67, -84, -101, -117, -134, -151, -168, -184, -201, -218, -234, -251, -268, -285, -301, -318, -335, -351, -368, -385, -401, -418, -435, -451, -468, -485, -501, -518, -535, -551, -568, -584, -601, -618, -634, -651, -667, -684, -700, -717, -733, -750, -766, -783, -799, -816, -832, -848, -865, -881, -897, -914, -930, -946, -963, -979, -995, -1011, -1028, -1044, -1060, -1076, -1092, -1109, -1125, -1141, -1157, -1173, -1189, -1205, -1221, -1237, -1253, -1269, -1285, -1301, -1317, -1332, -1348, -1364, -1380, -1396, -1411, -1427, -1443, -1458, -1474, -1490, -1505, -1521, -1536, -1552, -1567, -1583, -1598, -1614, -1629, -1645, -1660, -1675, -1690, -1706, -1721, -1736, -1751, -1766, -1781, -1797, -1812, -1827, -1842, -1857, -1871, -1886, -1901, -1916, -1931, -1946, -1960, -1975, -1990, -2004, -2019, -2033, -2048, -2062, -2077, -2091, -2106, -2120, -2134, -2149, -2163, -2177, -2191, -2205, -2220, -2234, -2248, -2262, -2276, -2290, -2303, -2317, -2331, -2345, -2359, -2372, -2386, -2399, -2413, -2427, -2440, -2453, -2467, -2480, -2493, -2507, -2520, -2533, -2546, -2559, -2572, -2586, -2598, -2611, -2624, -2637, -2650, -2663, -2675, -2688, -2701, -2713, -2726, -2738, -2751, -2763, -2775, -2788, -2800, -2812, -2824, -2836, -2849, -2861, -2873, -2884, -2896, -2908, -2920, -2932, -2943, -2955, -2967, -2978, -2990, -3001, -3012, -3024, -3035, -3046, -3057, -3068, -3080, -3091, -3102, -3112, -3123, -3134, -3145, -3156, -3166, -3177, -3187, -3198, -3208, -3219, -3229, -3239, -3250, -3260, -3270, -3280, -3290, -3300, -3310, -3320, -3329, -3339, -3349, -3358, -3368, -3378, -3387, -3396, -3406, -3415, -3424, -3433, -3442, -3452, -3461, -3469, -3478, -3487, -3496, -3505, -3513, -3522, -3530, -3539, -3547, -3556, -3564, -3572, -3580, -3588, -3596, -3604, -3612, -3620, -3628, -3636, -3643, -3651, -3659, -3666, -3674, -3681, -3688, -3696, -3703, -3710, -3717, -3724, -3731, -3738, -3745, -3751, -3758, -3765, -3771, -3778, -3784, -3791, -3797, -3803, -3809, -3815, -3822, -3828, -3833, -3839, -3845, -3851, -3857, -3862, -3868, -3873, -3879, -3884, -3889, -3894, -3900, -3905, -3910, -3915, -3920, -3924, -3929, -3934, -3939, -3943, -3948, -3952, -3956, -3961, -3965, -3969, -3973, -3977, -3981, -3985, -3989, -3993, -3996, -4000, -4004, -4007, -4011, -4014, -4017, -4021, -4024, -4027, -4030, -4033, -4036, -4039, -4041, -4044, -4047, -4049, -4052, -4054, -4056, -4059, -4061, -4063, -4065, -4067, -4069, -4071, -4073, -4075, -4076, -4078, -4079, -4081, -4082, -4084, -4085, -4086, -4087, -4088, -4089, -4090, -4091, -4092, -4093, -4093, -4094, -4094, -4095, -4095, -4095, -4096, -4096, -4096, -4096, -4096, -4096, -4096, -4095, -4095, -4095, -4094, -4094, -4093, -4093, -4092, -4091, -4090, -4089, -4088, -4087, -4086, -4085, -4084, -4082, -4081, -4079, -4078, -4076, -4075, -4073, -4071, -4069, -4067, -4065, -4063, -4061, -4059, -4056, -4054, -4052, -4049, -4047, -4044, -4041, -4039, -4036, -4033, -4030, -4027, -4024, -4021, -4017, -4014, -4011, -4007, -4004, -4000, -3996, -3993, -3989, -3985, -3981, -3977, -3973, -3969, -3965, -3961, -3956, -3952, -3948, -3943, -3939, -3934, -3929, -3924, -3920, -3915, -3910, -3905, -3900, -3894, -3889, -3884, -3879, -3873, -3868, -3862, -3857, -3851, -3845, -3839, -3833, -3828, -3822, -3815, -3809, -3803, -3797, -3791, -3784, -3778, -3771, -3765, -3758, -3751, -3745, -3738, -3731, -3724, -3717, -3710, -3703, -3696, -3688, -3681, -3674, -3666, -3659, -3651, -3643, -3636, -3628, -3620, -3612, -3604, -3596, -3588, -3580, -3572, -3564, -3556, -3547, -3539, -3530, -3522, -3513, -3505, -3496, -3487, -3478, -3469, -3461, -3452, -3442, -3433, -3424, -3415, -3406, -3396, -3387, -3378, -3368, -3358, -3349, -3339, -3329, -3320, -3310, -3300, -3290, -3280, -3270, -3260, -3250, -3239, -3229, -3219, -3208, -3198, -3187, -3177, -3166, -3156, -3145, -3134, -3123, -3112, -3102, -3091, -3080, -3068, -3057, -3046, -3035, -3024, -3012, -3001, -2990, -2978, -2967, -2955, -2943, -2932, -2920, -2908, -2896, -2884, -2873, -2861, -2849, -2836, -2824, -2812, -2800, -2788, -2775, -2763, -2751, -2738, -2726, -2713, -2701, -2688, -2675, -2663, -2650, -2637, -2624, -2611, -2598, -2586, -2572, -2559, -2546, -2533, -2520, -2507, -2493, -2480, -2467, -2453, -2440, -2427, -2413, -2399, -2386, -2372, -2359, -2345, -2331, -2317, -2303, -2290, -2276, -2262, -2248, -2234, -2220, -2205, -2191, -2177, -2163, -2149, -2134, -2120, -2106, -2091, -2077, -2062, -2048, -2033, -2019, -2004, -1990, -1975, -1960, -1946, -1931, -1916, -1901, -1886, -1871, -1857, -1842, -1827, -1812, -1797, -1781, -1766, -1751, -1736, -1721, -1706, -1690, -1675, -1660, -1645, -1629, -1614, -1598, -1583, -1567, -1552, -1536, -1521, -1505, -1490, -1474, -1458, -1443, -1427, -1411, -1396, -1380, -1364, -1348, -1332, -1317, -1301, -1285, -1269, -1253, -1237, -1221, -1205, -1189, -1173, -1157, -1141, -1125, -1109, -1092, -1076, -1060, -1044, -1028, -1011, -995, -979, -963, -946, -930, -914, -897, -881, -865, -848, -832, -816, -799, -783, -766, -750, -733, -717, -700, -684, -667, -651, -634, -618, -601, -584, -568, -551, -535, -518, -501, -485, -468, -451, -435, -418, -401, -385, -368, -351, -335, -318, -301, -285, -268, -251, -234, -218, -201, -184, -168, -151, -134, -117, -101, -84, -67, -50, -34, -17, 0
};
