﻿#include "resource/animation.h"

f32 const mario_stopping[][17][7] = { {{ 0.0000f, 0.2707f, -0.1684f, 0.6598f, -0.6445f, -0.1082f, 0.3709f },
{ -0.0299f, 0.4611f, -0.2370f, 0.7370f, -0.5592f, -0.2291f, 0.3026f },
{ -0.1004f, 0.7131f, -0.2372f, 0.5915f, -0.4059f, -0.3583f, 0.5974f },
{ 0.0668f, 0.2485f, 0.1389f, -0.7092f, -0.2614f, 0.6359f, 0.1559f },
{ 0.0558f, 0.1339f, 0.3043f, -0.6970f, 0.3158f, 0.5240f, -0.3741f },
{ -0.2680f, 0.2751f, -0.1106f, -0.4084f, -0.8249f, 0.3241f, 0.2186f },
{ -0.1530f, 0.1107f, -0.1300f, -0.9219f, -0.0520f, 0.3492f, -0.1596f },
{ -0.2243f, 0.6158f, -0.4274f, -0.4162f, -0.7892f, -0.1899f, 0.4096f },
{ -0.1621f, 0.5178f, -0.5848f, -0.8365f, -0.3106f, 0.1316f, 0.4319f },
{ 0.0963f, 0.7089f, -0.0891f, 0.0103f, -0.6651f, 0.7027f, -0.2525f },
{ 0.2668f, 0.7810f, -0.0263f, -0.4101f, -0.5236f, 0.3877f, -0.6382f },
{ 0.0912f, 0.3488f, -0.1081f, -0.7339f, -0.1807f, 0.6493f, 0.0841f },
{ -0.0657f, 0.2604f, -0.2853f, -0.9196f, -0.0378f, 0.3474f, -0.1793f },
{ -0.3015f, 0.4035f, -0.5935f, -0.8966f, -0.1147f, 0.1398f, 0.4043f },
{ 0.2396f, 0.7928f, 0.1517f, -0.5172f, -0.4182f, 0.2345f, -0.7089f },
{ -0.3015f, 0.4035f, -0.5935f, -0.8966f, -0.1147f, 0.1398f, 0.4043f },
{ 0.2396f, 0.7928f, 0.1517f, -0.5172f, -0.4182f, 0.2345f, -0.7089f } }, {{ 0.0000f, 0.2705f, -0.1647f, 0.6597f, -0.6437f, -0.1166f, 0.3698f },
{ -0.0295f, 0.4619f, -0.2307f, 0.7360f, -0.5581f, -0.2376f, 0.3006f },
{ -0.0986f, 0.7143f, -0.2269f, 0.5920f, -0.4020f, -0.3662f, 0.5948f },
{ 0.0695f, 0.2447f, 0.1419f, -0.7057f, -0.2633f, 0.6370f, 0.1638f },
{ 0.0595f, 0.1278f, 0.3057f, -0.6964f, 0.3119f, 0.5305f, -0.3692f },
{ -0.2675f, 0.2764f, -0.1043f, -0.4086f, -0.8241f, 0.3206f, 0.2261f },
{ -0.1538f, 0.1114f, -0.1266f, -0.9213f, -0.0513f, 0.3537f, -0.1531f },
{ -0.2252f, 0.6201f, -0.4169f, -0.4173f, -0.7839f, -0.1937f, 0.4169f },
{ -0.1657f, 0.5237f, -0.5763f, -0.8335f, -0.3066f, 0.1333f, 0.4399f },
{ 0.0998f, 0.7072f, -0.0812f, 0.0118f, -0.6707f, 0.6995f, -0.2464f },
{ 0.2715f, 0.7777f, -0.0198f, -0.4119f, -0.5295f, 0.3897f, -0.6310f },
{ 0.0923f, 0.3474f, -0.1043f, -0.7310f, -0.1815f, 0.6515f, 0.0905f },
{ -0.0669f, 0.2620f, -0.2810f, -0.9191f, -0.0370f, 0.3522f, -0.1728f },
{ -0.3059f, 0.4103f, -0.5849f, -0.8932f, -0.1108f, 0.1432f, 0.4117f },
{ 0.2470f, 0.7877f, 0.1588f, -0.5206f, -0.4227f, 0.2375f, -0.7028f },
{ -0.3059f, 0.4103f, -0.5849f, -0.8932f, -0.1108f, 0.1432f, 0.4117f },
{ 0.2470f, 0.7877f, 0.1588f, -0.5206f, -0.4227f, 0.2375f, -0.7028f } }, {{ 0.0000f, 0.2674f, -0.1513f, 0.6593f, -0.6412f, -0.1393f, 0.3671f },
{ -0.0285f, 0.4612f, -0.2100f, 0.7288f, -0.5460f, -0.2786f, 0.3053f },
{ -0.0935f, 0.7140f, -0.1910f, 0.5836f, -0.3778f, -0.4138f, 0.5877f },
{ 0.0690f, 0.2519f, 0.1601f, -0.6925f, -0.2965f, 0.6259f, 0.2019f },
{ 0.0608f, 0.1182f, 0.3107f, -0.7196f, 0.2723f, 0.5472f, -0.3296f },
{ -0.2642f, 0.2766f, -0.0817f, -0.3984f, -0.8256f, 0.3071f, 0.2556f },
{ -0.1530f, 0.1123f, -0.1175f, -0.9198f, -0.0583f, 0.3654f, -0.1303f },
{ -0.2355f, 0.6289f, -0.3744f, -0.4351f, -0.7349f, -0.1981f, 0.4811f },
{ -0.2044f, 0.5412f, -0.5463f, -0.8058f, -0.2830f, 0.1577f, 0.4958f },
{ 0.1152f, 0.6988f, -0.0613f, 0.0671f, -0.6871f, 0.6945f, -0.2025f },
{ 0.2929f, 0.7718f, -0.0251f, -0.3529f, -0.5934f, 0.4397f, -0.5745f },
{ 0.0951f, 0.3408f, -0.0911f, -0.7368f, -0.1570f, 0.6531f, 0.0771f },
{ -0.0703f, 0.2636f, -0.2658f, -0.9161f, -0.0348f, 0.3697f, -0.1515f },
{ -0.3470f, 0.4307f, -0.5511f, -0.8646f, -0.0894f, 0.1801f, 0.4605f },
{ 0.3093f, 0.7874f, 0.1540f, -0.4923f, -0.4684f, 0.2756f, -0.6799f },
{ -0.3470f, 0.4307f, -0.5511f, -0.8646f, -0.0894f, 0.1801f, 0.4605f },
{ 0.3093f, 0.7874f, 0.1540f, -0.4923f, -0.4684f, 0.2756f, -0.6799f } }, {{ 0.0000f, 0.2647f, -0.1322f, 0.6583f, -0.6361f, -0.1728f, 0.3636f },
{ -0.0269f, 0.4617f, -0.1803f, 0.7137f, -0.5133f, -0.3538f, 0.3194f },
{ -0.0851f, 0.7126f, -0.1339f, 0.5604f, -0.3268f, -0.5012f, 0.5727f },
{ 0.0691f, 0.2846f, 0.1887f, -0.6558f, -0.3665f, 0.6007f, 0.2734f },
{ 0.0672f, 0.1215f, 0.3071f, -0.7610f, 0.1808f, 0.5724f, -0.2461f },
{ -0.2582f, 0.2796f, -0.0485f, -0.3783f, -0.8276f, 0.2840f, 0.3021f },
{ -0.1511f, 0.1188f, -0.1060f, -0.9178f, -0.0711f, 0.3790f, -0.0945f },
{ -0.2544f, 0.6410f, -0.2989f, -0.4621f, -0.6195f, -0.1882f, 0.6061f },
{ -0.2860f, 0.5736f, -0.4797f, -0.7383f, -0.2286f, 0.2048f, 0.6006f },
{ 0.1407f, 0.6879f, -0.0390f, 0.1971f, -0.7042f, 0.6709f, -0.1231f },
{ 0.3151f, 0.7745f, -0.0568f, -0.1880f, -0.7067f, 0.5153f, -0.4469f },
{ 0.0991f, 0.3333f, -0.0728f, -0.7451f, -0.0957f, 0.6594f, 0.0299f },
{ -0.0752f, 0.2679f, -0.2436f, -0.9095f, -0.0285f, 0.3968f, -0.1204f },
{ -0.4325f, 0.4683f, -0.4747f, -0.7940f, -0.0424f, 0.2521f, 0.5516f },
{ 0.4108f, 0.8096f, 0.0921f, -0.4066f, -0.5670f, 0.3335f, -0.6340f },
{ -0.4325f, 0.4683f, -0.4747f, -0.7940f, -0.0424f, 0.2521f, 0.5516f },
{ 0.4108f, 0.8096f, 0.0921f, -0.4066f, -0.5670f, 0.3335f, -0.6340f } }, {{ 0.0000f, 0.2647f, -0.1138f, 0.6565f, -0.6275f, -0.2132f, 0.3602f },
{ -0.0249f, 0.4647f, -0.1490f, 0.6947f, -0.4610f, -0.4415f, 0.3315f },
{ -0.0733f, 0.7089f, -0.0684f, 0.5298f, -0.2611f, -0.5932f, 0.5471f },
{ 0.0845f, 0.3273f, 0.2108f, -0.5873f, -0.4372f, 0.5721f, 0.3695f },
{ 0.0919f, 0.1386f, 0.2811f, -0.7800f, 0.0652f, 0.6079f, -0.1330f },
{ -0.2512f, 0.2821f, -0.0137f, -0.3521f, -0.8288f, 0.2571f, 0.3508f },
{ -0.1492f, 0.1282f, -0.0944f, -0.9143f, -0.0880f, 0.3919f, -0.0519f },
{ -0.2701f, 0.6507f, -0.2058f, -0.4686f, -0.4647f, -0.1546f, 0.7352f },
{ -0.3719f, 0.6100f, -0.3677f, -0.6426f, -0.1504f, 0.2534f, 0.7073f },
{ 0.1661f, 0.6790f, -0.0193f, 0.3508f, -0.7111f, 0.6075f, -0.0459f },
{ 0.3127f, 0.7874f, -0.0899f, 0.0308f, -0.7924f, 0.5362f, -0.2893f },
{ 0.1038f, 0.3277f, -0.0563f, -0.7318f, -0.0232f, 0.6807f, -0.0237f },
{ -0.0811f, 0.2759f, -0.2204f, -0.9000f, -0.0279f, 0.4263f, -0.0863f },
{ -0.5210f, 0.5104f, -0.3473f, -0.6916f, 0.0231f, 0.3285f, 0.6429f },
{ 0.4626f, 0.8522f, -0.0131f, -0.2939f, -0.6820f, 0.3569f, -0.5666f },
{ -0.5210f, 0.5104f, -0.3473f, -0.6916f, 0.0231f, 0.3285f, 0.6429f },
{ 0.4626f, 0.8522f, -0.0131f, -0.2939f, -0.6820f, 0.3569f, -0.5666f } }, {{ 0.0000f, 0.2665f, -0.0996f, 0.6538f, -0.6154f, -0.2571f, 0.3575f },
{ -0.0226f, 0.4687f, -0.1209f, 0.6768f, -0.3979f, -0.5225f, 0.3325f },
{ -0.0586f, 0.7005f, -0.0050f, 0.5063f, -0.1996f, -0.6648f, 0.5117f },
{ 0.1142f, 0.3589f, 0.2202f, -0.5055f, -0.4813f, 0.5355f, 0.4754f },
{ 0.1216f, 0.1582f, 0.2370f, -0.7645f, -0.0340f, 0.6438f, -0.0040f },
{ -0.2456f, 0.2799f, 0.0161f, -0.3256f, -0.8294f, 0.2344f, 0.3889f },
{ -0.1477f, 0.1343f, -0.0832f, -0.9087f, -0.1076f, 0.4031f, -0.0104f },
{ -0.2755f, 0.6530f, -0.1130f, -0.4418f, -0.3199f, -0.1082f, 0.8312f },
{ -0.4265f, 0.6329f, -0.2357f, -0.5405f, -0.0732f, 0.2974f, 0.7836f },
{ 0.1860f, 0.6720f, -0.0010f, 0.4700f, -0.7153f, 0.5169f, 0.0163f },
{ 0.2950f, 0.8001f, -0.1006f, 0.2076f, -0.8304f, 0.4933f, -0.1551f },
{ 0.1086f, 0.3239f, -0.0452f, -0.6972f, 0.0333f, 0.7137f, -0.0590f },
{ -0.0875f, 0.2857f, -0.1999f, -0.8900f, -0.0405f, 0.4506f, -0.0557f },
{ -0.5731f, 0.5345f, -0.1984f, -0.5821f, 0.0847f, 0.3957f, 0.7053f },
{ 0.4513f, 0.8900f, -0.0911f, -0.2072f, -0.7779f, 0.3435f, -0.4837f },
{ -0.5731f, 0.5345f, -0.1984f, -0.5821f, 0.0847f, 0.3957f, 0.7053f },
{ 0.4513f, 0.8900f, -0.0911f, -0.2072f, -0.7779f, 0.3435f, -0.4837f } }, {{ 0.0000f, 0.2760f, -0.0932f, 0.6499f, -0.6002f, -0.3004f, 0.3565f },
{ -0.0203f, 0.4794f, -0.1009f, 0.6699f, -0.3384f, -0.5859f, 0.3056f },
{ -0.0424f, 0.6918f, 0.0504f, 0.5168f, -0.1617f, -0.7063f, 0.4560f },
{ 0.1435f, 0.3703f, 0.2195f, -0.4467f, -0.4932f, 0.4986f, 0.5556f },
{ 0.1402f, 0.1699f, 0.1989f, -0.7338f, -0.0915f, 0.6664f, 0.0954f },
{ -0.2466f, 0.2763f, 0.0322f, -0.3081f, -0.8336f, 0.2252f, 0.3994f },
{ -0.1476f, 0.1365f, -0.0740f, -0.9033f, -0.1286f, 0.4087f, 0.0229f },
{ -0.2702f, 0.6575f, -0.0387f, -0.3811f, -0.2332f, -0.0853f, 0.8906f },
{ -0.4416f, 0.6524f, -0.1326f, -0.4455f, -0.0342f, 0.3294f, 0.8318f },
{ 0.2010f, 0.6660f, 0.0232f, 0.5103f, -0.7435f, 0.4268f, 0.0676f },
{ 0.2929f, 0.8031f, -0.0816f, 0.2559f, -0.8648f, 0.4268f, -0.0675f },
{ 0.1131f, 0.3285f, -0.0431f, -0.6633f, 0.0538f, 0.7443f, -0.0569f },
{ -0.0937f, 0.3025f, -0.1859f, -0.8856f, -0.0735f, 0.4572f, -0.0351f },
{ -0.5825f, 0.5480f, -0.0899f, -0.4850f, 0.1089f, 0.4456f, 0.7446f },
{ 0.4481f, 0.8934f, -0.0999f, -0.1997f, -0.8368f, 0.3259f, -0.3919f },
{ -0.5825f, 0.5480f, -0.0899f, -0.4850f, 0.1089f, 0.4456f, 0.7446f },
{ 0.4481f, 0.8934f, -0.0999f, -0.1997f, -0.8368f, 0.3259f, -0.3919f } }, {{ 0.0000f, 0.2969f, -0.0982f, 0.6448f, -0.5836f, -0.3399f, 0.3580f },
{ -0.0180f, 0.5006f, -0.0940f, 0.6777f, -0.2893f, -0.6362f, 0.2288f },
{ -0.0241f, 0.6794f, 0.0970f, 0.5671f, -0.1547f, -0.7301f, 0.3484f },
{ 0.1612f, 0.3616f, 0.2103f, -0.4324f, -0.4815f, 0.4789f, 0.5932f },
{ 0.1456f, 0.1632f, 0.1786f, -0.7103f, -0.1126f, 0.6821f, 0.1323f },
{ -0.2603f, 0.2750f, 0.0241f, -0.3131f, -0.8473f, 0.2299f, 0.3622f },
{ -0.1512f, 0.1345f, -0.0706f, -0.9051f, -0.1465f, 0.3964f, 0.0469f },
{ -0.2560f, 0.6740f, 0.0123f, -0.2867f, -0.1917f, -0.1115f, 0.9320f },
{ -0.4323f, 0.6931f, -0.0701f, -0.3427f, -0.0385f, 0.3293f, 0.8790f },
{ 0.2166f, 0.6485f, 0.0553f, 0.4796f, -0.8057f, 0.3307f, 0.1076f },
{ 0.3177f, 0.7857f, -0.0406f, 0.1928f, -0.9176f, 0.3477f, -0.0053f },
{ 0.1169f, 0.3456f, -0.0533f, -0.6460f, 0.0391f, 0.7624f, -0.0061f },
{ -0.0994f, 0.3291f, -0.1828f, -0.8943f, -0.1275f, 0.4280f, -0.0300f },
{ -0.5731f, 0.5839f, -0.0415f, -0.3859f, 0.0898f, 0.4645f, 0.7919f },
{ 0.4847f, 0.8502f, -0.0631f, -0.2697f, -0.8665f, 0.3032f, -0.2907f },
{ -0.5731f, 0.5839f, -0.0415f, -0.3859f, 0.0898f, 0.4645f, 0.7919f },
{ 0.4847f, 0.8502f, -0.0631f, -0.2697f, -0.8665f, 0.3032f, -0.2907f } }, {{ 0.0000f, 0.3256f, -0.1109f, 0.6383f, -0.5682f, -0.3719f, 0.3625f },
{ -0.0160f, 0.5291f, -0.0981f, 0.6746f, -0.2548f, -0.6755f, 0.1538f },
{ -0.0048f, 0.6734f, 0.1199f, 0.6027f, -0.1827f, -0.7430f, 0.2266f },
{ 0.1720f, 0.3487f, 0.1900f, -0.4333f, -0.4594f, 0.4765f, 0.6117f },
{ 0.1471f, 0.1510f, 0.1600f, -0.6883f, -0.1168f, 0.7022f, 0.1397f },
{ -0.2799f, 0.2791f, -0.0036f, -0.3444f, -0.8615f, 0.2322f, 0.2923f },
{ -0.1605f, 0.1322f, -0.0729f, -0.9156f, -0.1535f, 0.3659f, 0.0650f },
{ -0.2385f, 0.6975f, 0.0437f, -0.2020f, -0.1579f, -0.1443f, 0.9558f },
{ -0.4161f, 0.7389f, -0.0267f, -0.2524f, -0.0446f, 0.3213f, 0.9116f },
{ 0.2320f, 0.6342f, 0.0652f, 0.4235f, -0.8582f, 0.2382f, 0.1652f },
{ 0.3467f, 0.7609f, -0.0297f, 0.0971f, -0.9521f, 0.2809f, 0.0716f },
{ 0.1199f, 0.3718f, -0.0716f, -0.6314f, 0.0085f, 0.7729f, 0.0626f },
{ -0.1041f, 0.3616f, -0.1880f, -0.9094f, -0.1835f, 0.3717f, -0.0342f },
{ -0.5586f, 0.6291f, -0.0121f, -0.2986f, 0.0701f, 0.4728f, 0.8261f },
{ 0.5220f, 0.7870f, -0.0641f, -0.3473f, -0.8726f, 0.2955f, -0.1750f },
{ -0.5586f, 0.6291f, -0.0121f, -0.2986f, 0.0701f, 0.4728f, 0.8261f },
{ 0.5220f, 0.7870f, -0.0641f, -0.3473f, -0.8726f, 0.2955f, -0.1750f } }, {{ 0.0000f, 0.3526f, -0.1237f, 0.6294f, -0.5557f, -0.3962f, 0.3716f },
{ -0.0140f, 0.5560f, -0.1061f, 0.6572f, -0.2306f, -0.7012f, 0.1525f },
{ 0.0094f, 0.6912f, 0.1166f, 0.6093f, -0.2350f, -0.7379f, 0.1705f },
{ 0.1835f, 0.3418f, 0.1642f, -0.4217f, -0.4421f, 0.4850f, 0.6257f },
{ 0.1556f, 0.1443f, 0.1351f, -0.6619f, -0.1189f, 0.7253f, 0.1472f },
{ -0.2921f, 0.2846f, -0.0309f, -0.3825f, -0.8650f, 0.2264f, 0.2329f },
{ -0.1714f, 0.1300f, -0.0772f, -0.9261f, -0.1534f, 0.3361f, 0.0763f },
{ -0.2290f, 0.7149f, 0.0568f, -0.1695f, -0.1300f, -0.1258f, 0.9688f },
{ -0.4117f, 0.7539f, -0.0008f, -0.2112f, -0.0316f, 0.3595f, 0.9084f },
{ 0.2427f, 0.6579f, 0.0451f, 0.3789f, -0.8682f, 0.1960f, 0.2536f },
{ 0.3570f, 0.7671f, -0.0700f, 0.0167f, -0.9471f, 0.2783f, 0.1589f },
{ 0.1222f, 0.3975f, -0.0904f, -0.6105f, -0.0252f, 0.7835f, 0.1133f },
{ -0.1082f, 0.3906f, -0.1940f, -0.9178f, -0.2284f, 0.3229f, -0.0360f },
{ -0.5452f, 0.6336f, 0.0162f, -0.2584f, 0.0747f, 0.5161f, 0.8132f },
{ 0.5282f, 0.7569f, -0.1260f, -0.3801f, -0.8584f, 0.3371f, -0.0712f },
{ -0.5452f, 0.6336f, 0.0162f, -0.2584f, 0.0747f, 0.5161f, 0.8132f },
{ 0.5282f, 0.7569f, -0.1260f, -0.3801f, -0.8584f, 0.3371f, -0.0712f } }, {{ 0.0000f, 0.3781f, -0.1347f, 0.6161f, -0.5445f, -0.4175f, 0.3867f },
{ -0.0120f, 0.5814f, -0.1156f, 0.6272f, -0.2041f, -0.7196f, 0.2170f },
{ 0.0192f, 0.7302f, 0.0975f, 0.6054f, -0.2840f, -0.7204f, 0.1841f },
{ 0.1972f, 0.3375f, 0.1343f, -0.4024f, -0.4256f, 0.5002f, 0.6378f },
{ 0.1695f, 0.1399f, 0.1060f, -0.6303f, -0.1181f, 0.7515f, 0.1549f },
{ -0.2917f, 0.2889f, -0.0460f, -0.4053f, -0.8622f, 0.2210f, 0.2086f },
{ -0.1739f, 0.1294f, -0.0824f, -0.9298f, -0.1596f, 0.3227f, 0.0764f },
{ -0.2252f, 0.7258f, 0.0623f, -0.1747f, -0.0990f, -0.0551f, 0.9781f },
{ -0.4157f, 0.7401f, 0.0207f, -0.2008f, 0.0025f, 0.4450f, 0.8727f },
{ 0.2462f, 0.7173f, 0.0031f, 0.3482f, -0.8442f, 0.2066f, 0.3513f },
{ 0.3461f, 0.8038f, -0.1410f, -0.0428f, -0.9122f, 0.3361f, 0.2305f },
{ 0.1243f, 0.4223f, -0.1089f, -0.5827f, -0.0592f, 0.7954f, 0.1559f },
{ -0.1122f, 0.4168f, -0.1979f, -0.9135f, -0.2704f, 0.3027f, -0.0265f },
{ -0.5247f, 0.6001f, 0.0537f, -0.2469f, 0.1024f, 0.5971f, 0.7564f },
{ 0.5067f, 0.7618f, -0.2117f, -0.3760f, -0.8283f, 0.4154f, 0.0031f },
{ -0.5247f, 0.6001f, 0.0537f, -0.2469f, 0.1024f, 0.5971f, 0.7564f },
{ 0.5067f, 0.7618f, -0.2117f, -0.3760f, -0.8283f, 0.4154f, 0.0031f } }, {{ 0.0000f, 0.4036f, -0.1364f, 0.5988f, -0.5338f, -0.4377f, 0.4063f },
{ -0.0097f, 0.6071f, -0.1179f, 0.5830f, -0.1823f, -0.7320f, 0.3016f },
{ 0.0265f, 0.7783f, 0.0767f, 0.5964f, -0.3227f, -0.6982f, 0.2297f },
{ 0.2112f, 0.3326f, 0.1067f, -0.3807f, -0.4036f, 0.5202f, 0.6493f },
{ 0.1844f, 0.1345f, 0.0810f, -0.5924f, -0.1123f, 0.7816f, 0.1600f },
{ -0.2843f, 0.2906f, -0.0496f, -0.4228f, -0.8578f, 0.2143f, 0.1988f },
{ -0.1707f, 0.1272f, -0.0818f, -0.9316f, -0.1711f, 0.3131f, 0.0694f },
{ -0.2177f, 0.7414f, 0.0736f, -0.1961f, -0.0607f, 0.0285f, 0.9783f },
{ -0.4114f, 0.7258f, 0.0526f, -0.1988f, 0.0512f, 0.5374f, 0.8179f },
{ 0.2407f, 0.7836f, -0.0447f, 0.3095f, -0.8092f, 0.2485f, 0.4332f },
{ 0.3254f, 0.8394f, -0.2118f, -0.1046f, -0.8600f, 0.4222f, 0.2668f },
{ 0.1259f, 0.4474f, -0.1196f, -0.5472f, -0.0918f, 0.8067f, 0.2034f },
{ -0.1161f, 0.4425f, -0.1921f, -0.9023f, -0.3170f, 0.2922f, -0.0079f },
{ -0.4867f, 0.5708f, 0.1063f, -0.2404f, 0.1445f, 0.6800f, 0.6775f },
{ 0.4762f, 0.7663f, -0.2787f, -0.3707f, -0.7804f, 0.5014f, 0.0458f },
{ -0.4867f, 0.5708f, 0.1063f, -0.2404f, 0.1445f, 0.6800f, 0.6775f },
{ 0.4762f, 0.7663f, -0.2787f, -0.3707f, -0.7804f, 0.5014f, 0.0458f } }, {{ 0.0000f, 0.4248f, -0.1226f, 0.5788f, -0.5237f, -0.4560f, 0.4277f },
{ -0.0074f, 0.6286f, -0.1063f, 0.5386f, -0.1832f, -0.7350f, 0.3689f },
{ 0.0313f, 0.8221f, 0.0656f, 0.5854f, -0.3606f, -0.6723f, 0.2745f },
{ 0.2235f, 0.3250f, 0.0894f, -0.3565f, -0.3784f, 0.5424f, 0.6600f },
{ 0.1982f, 0.1263f, 0.0666f, -0.5498f, -0.1031f, 0.8126f, 0.1633f },
{ -0.2750f, 0.2881f, -0.0413f, -0.4449f, -0.8511f, 0.2020f, 0.1920f },
{ -0.1681f, 0.1199f, -0.0710f, -0.9351f, -0.1807f, 0.2987f, 0.0617f },
{ -0.2082f, 0.7671f, 0.0898f, -0.2248f, -0.0310f, 0.0865f, 0.9701f },
{ -0.4004f, 0.7316f, 0.0857f, -0.2053f, 0.0968f, 0.6022f, 0.7654f },
{ 0.2327f, 0.8302f, -0.0758f, 0.2474f, -0.7871f, 0.3014f, 0.4779f },
{ 0.3150f, 0.8500f, -0.2521f, -0.1888f, -0.8032f, 0.5030f, 0.2572f },
{ 0.1270f, 0.4681f, -0.1153f, -0.5058f, -0.1201f, 0.8159f, 0.2531f },
{ -0.1195f, 0.4636f, -0.1705f, -0.8889f, -0.3637f, 0.2782f, 0.0165f },
{ -0.4467f, 0.5724f, 0.1570f, -0.2405f, 0.1859f, 0.7349f, 0.6062f },
{ 0.4587f, 0.7486f, -0.2924f, -0.3947f, -0.7200f, 0.5681f, 0.0555f },
{ -0.4467f, 0.5724f, 0.1570f, -0.2405f, 0.1859f, 0.7349f, 0.6062f },
{ 0.4587f, 0.7486f, -0.2924f, -0.3947f, -0.7200f, 0.5681f, 0.0555f } }, {{ 0.0000f, 0.4485f, -0.0966f, 0.5577f, -0.5146f, -0.4720f, 0.4487f },
{ -0.0051f, 0.6526f, -0.0834f, 0.5158f, -0.2256f, -0.7208f, 0.4043f },
{ 0.0318f, 0.8660f, 0.0635f, 0.5758f, -0.4016f, -0.6405f, 0.3114f },
{ 0.2323f, 0.3229f, 0.0814f, -0.3304f, -0.3524f, 0.5644f, 0.6694f },
{ 0.2092f, 0.1237f, 0.0615f, -0.5053f, -0.0925f, 0.8420f, 0.1648f },
{ -0.2659f, 0.2914f, -0.0246f, -0.4708f, -0.8416f, 0.1846f, 0.1896f },
{ -0.1682f, 0.1176f, -0.0539f, -0.9399f, -0.1854f, 0.2812f, 0.0558f },
{ -0.2073f, 0.8123f, 0.0943f, -0.2665f, -0.0361f, 0.1003f, 0.9579f },
{ -0.3984f, 0.7710f, 0.0913f, -0.2401f, 0.1212f, 0.6254f, 0.7325f },
{ 0.2332f, 0.8585f, -0.0779f, 0.1538f, -0.7919f, 0.3568f, 0.4711f },
{ 0.3327f, 0.8403f, -0.2452f, -0.3073f, -0.7459f, 0.5572f, 0.1971f },
{ 0.1275f, 0.4910f, -0.0986f, -0.4615f, -0.1426f, 0.8218f, 0.3021f },
{ -0.1223f, 0.4873f, -0.1370f, -0.8753f, -0.4047f, 0.2607f, 0.0451f },
{ -0.4324f, 0.6161f, 0.1775f, -0.2696f, 0.2151f, 0.7504f, 0.5639f },
{ 0.4651f, 0.7180f, -0.2365f, -0.4635f, -0.6524f, 0.5990f, 0.0269f },
{ -0.4324f, 0.6161f, 0.1775f, -0.2696f, 0.2151f, 0.7504f, 0.5639f },
{ 0.4651f, 0.7180f, -0.2365f, -0.4635f, -0.6524f, 0.5990f, 0.0269f } }, {{ 0.0000f, 0.4715f, -0.0630f, 0.5375f, -0.5070f, -0.4852f, 0.4675f },
{ -0.0031f, 0.6758f, -0.0533f, 0.5152f, -0.2983f, -0.6823f, 0.4244f },
{ 0.0254f, 0.9078f, 0.0644f, 0.5643f, -0.4340f, -0.6039f, 0.3585f },
{ 0.2368f, 0.3245f, 0.0819f, -0.3046f, -0.3282f, 0.5842f, 0.6769f },
{ 0.2163f, 0.1248f, 0.0640f, -0.4628f, -0.0825f, 0.8671f, 0.1650f },
{ -0.2587f, 0.2989f, -0.0026f, -0.4986f, -0.8293f, 0.1645f, 0.1912f },
{ -0.1721f, 0.1196f, -0.0335f, -0.9457f, -0.1839f, 0.2629f, 0.0524f },
{ -0.2165f, 0.8612f, 0.0812f, -0.3245f, -0.0776f, 0.0926f, 0.9381f },
{ -0.4063f, 0.8174f, 0.0645f, -0.3086f, 0.1267f, 0.6236f, 0.7070f },
{ 0.2382f, 0.8782f, -0.0559f, 0.0505f, -0.8066f, 0.4172f, 0.4157f },
{ 0.3652f, 0.8264f, -0.1952f, -0.4306f, -0.6839f, 0.5815f, 0.0933f },
{ 0.1274f, 0.5131f, -0.0735f, -0.4187f, -0.1587f, 0.8242f, 0.3467f },
{ -0.1242f, 0.5104f, -0.0967f, -0.8635f, -0.4368f, 0.2410f, 0.0743f },
{ -0.4406f, 0.6724f, 0.1663f, -0.3337f, 0.2344f, 0.7397f, 0.5353f },
{ 0.4756f, 0.7005f, -0.1279f, -0.5480f, -0.5849f, 0.5966f, -0.0408f },
{ -0.4406f, 0.6724f, 0.1663f, -0.3337f, 0.2344f, 0.7397f, 0.5353f },
{ 0.4756f, 0.7005f, -0.1279f, -0.5480f, -0.5849f, 0.5966f, -0.0408f } }, {{ 0.0000f, 0.4912f, -0.0306f, 0.5203f, -0.5011f, -0.4953f, 0.4826f },
{ -0.0015f, 0.6956f, -0.0241f, 0.5282f, -0.3709f, -0.6272f, 0.4359f },
{ 0.0147f, 0.9413f, 0.0647f, 0.5507f, -0.4536f, -0.5689f, 0.4090f },
{ 0.2378f, 0.3282f, 0.0860f, -0.2819f, -0.3085f, 0.5999f, 0.6822f },
{ 0.2197f, 0.1282f, 0.0694f, -0.4268f, -0.0741f, 0.8863f, 0.1639f },
{ -0.2541f, 0.3085f, 0.0180f, -0.5244f, -0.8160f, 0.1454f, 0.1950f },
{ -0.1788f, 0.1246f, -0.0154f, -0.9512f, -0.1779f, 0.2468f, 0.0511f },
{ -0.2280f, 0.8963f, 0.0561f, -0.3807f, -0.1377f, 0.0833f, 0.9106f },
{ -0.4134f, 0.8461f, 0.0194f, -0.3873f, 0.1179f, 0.6123f, 0.6791f },
{ 0.2408f, 0.8968f, -0.0222f, -0.0333f, -0.8170f, 0.4701f, 0.3324f },
{ 0.3927f, 0.8251f, -0.1223f, -0.5261f, -0.6259f, 0.5752f, -0.0246f },
{ 0.1269f, 0.5318f, -0.0479f, -0.3822f, -0.1690f, 0.8237f, 0.3832f },
{ -0.1255f, 0.5303f, -0.0589f, -0.8545f, -0.4589f, 0.2218f, 0.0999f },
{ -0.4535f, 0.7125f, 0.1339f, -0.4102f, 0.2422f, 0.7176f, 0.5081f },
{ 0.4730f, 0.7113f, -0.0075f, -0.6165f, -0.5306f, 0.5680f, -0.1258f },
{ -0.4535f, 0.7125f, 0.1339f, -0.4102f, 0.2422f, 0.7176f, 0.5081f },
{ 0.4730f, 0.7113f, -0.0075f, -0.6165f, -0.5306f, 0.5680f, -0.1258f } }, {{ 0.0000f, 0.5046f, -0.0073f, 0.5083f, -0.4974f, -0.5017f, 0.4925f },
{ -0.0004f, 0.7091f, -0.0032f, 0.5447f, -0.4220f, -0.5756f, 0.4403f },
{ 0.0045f, 0.9621f, 0.0637f, 0.5382f, -0.4626f, -0.5429f, 0.4490f },
{ 0.2370f, 0.3316f, 0.0900f, -0.2659f, -0.2953f, 0.6102f, 0.6854f },
{ 0.2207f, 0.1314f, 0.0738f, -0.4019f, -0.0686f, 0.8985f, 0.1628f },
{ -0.2518f, 0.3166f, 0.0325f, -0.5433f, -0.8049f, 0.1314f, 0.1991f },
{ -0.1853f, 0.1298f, -0.0034f, -0.9553f, -0.1710f, 0.2358f, 0.0509f },
{ -0.2354f, 0.9131f, 0.0313f, -0.4195f, -0.1923f, 0.0783f, 0.8837f },
{ -0.4140f, 0.8545f, -0.0224f, -0.4499f, 0.1028f, 0.6001f, 0.6534f },
{ 0.2393f, 0.9131f, 0.0081f, -0.0849f, -0.8204f, 0.5043f, 0.2556f },
{ 0.4065f, 0.8355f, -0.0572f, -0.5823f, -0.5841f, 0.5528f, -0.1188f },
{ 0.1265f, 0.5444f, -0.0291f, -0.3570f, -0.1745f, 0.8221f, 0.4076f },
{ -0.1262f, 0.5440f, -0.0320f, -0.8490f, -0.4715f, 0.2073f, 0.1180f },
{ -0.4607f, 0.7297f, 0.0993f, -0.4725f, 0.2403f, 0.6957f, 0.4848f },
{ 0.4595f, 0.7364f, 0.0840f, -0.6570f, -0.4966f, 0.5321f, -0.1967f },
{ -0.4607f, 0.7297f, 0.0993f, -0.4725f, 0.2403f, 0.6957f, 0.4848f },
{ 0.4595f, 0.7364f, 0.0840f, -0.6570f, -0.4966f, 0.5321f, -0.1967f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.5038f, -0.4961f, -0.5039f, 0.4962f },
{ 0.0000f, 0.7159f, 0.0032f, 0.5528f, -0.4408f, -0.5529f, 0.4409f },
{ 0.0000f, 0.9710f, 0.0614f, 0.5327f, -0.4649f, -0.5328f, 0.4650f },
{ 0.2364f, 0.3349f, 0.0902f, -0.2600f, -0.2905f, 0.6140f, 0.6863f },
{ 0.2208f, 0.1346f, 0.0741f, -0.3929f, -0.0667f, 0.9027f, 0.1623f },
{ -0.2511f, 0.3216f, 0.0363f, -0.5504f, -0.8005f, 0.1261f, 0.2009f },
{ -0.1879f, 0.1338f, -0.0006f, -0.9568f, -0.1681f, 0.2317f, 0.0507f },
{ -0.2377f, 0.9191f, 0.0187f, -0.4333f, -0.2161f, 0.0768f, 0.8716f },
{ -0.4126f, 0.8563f, -0.0419f, -0.4749f, 0.0944f, 0.5943f, 0.6421f },
{ 0.2376f, 0.9220f, 0.0193f, -0.1025f, -0.8207f, 0.5161f, 0.2225f },
{ 0.4096f, 0.8442f, -0.0314f, -0.6008f, -0.5684f, 0.5399f, -0.1563f },
{ 0.1263f, 0.5508f, -0.0235f, -0.3478f, -0.1763f, 0.8213f, 0.4165f },
{ -0.1264f, 0.5508f, -0.0234f, -0.8470f, -0.4758f, 0.2017f, 0.1247f },
{ -0.4624f, 0.7347f, 0.0818f, -0.4980f, 0.2374f, 0.6857f, 0.4749f },
{ 0.4510f, 0.7514f, 0.1178f, -0.6702f, -0.4847f, 0.5147f, -0.2258f },
{ -0.4624f, 0.7347f, 0.0818f, -0.4980f, 0.2374f, 0.6857f, 0.4749f },
{ 0.4510f, 0.7514f, 0.1178f, -0.6702f, -0.4847f, 0.5147f, -0.2258f } },};


