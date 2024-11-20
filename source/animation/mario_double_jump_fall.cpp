﻿#include "resource/animation.h"

f32 const mario_double_jump_fall[][17][7] = { {{ 0.0000f, 0.5114f, 0.0000f, 0.5021f, -0.4979f, -0.5021f, 0.4979f },
{ 0.0000f, 0.7159f, 0.0017f, 0.4783f, -0.5233f, -0.4676f, 0.5280f },
{ -0.0040f, 0.9761f, -0.0258f, 0.3409f, -0.6270f, -0.3558f, 0.6033f },
{ 0.1416f, 0.2834f, -0.0293f, -0.2686f, -0.5305f, 0.4081f, 0.6928f },
{ 0.1206f, 0.1121f, -0.1332f, -0.4143f, -0.4351f, 0.5782f, 0.5520f },
{ -0.1587f, 0.3082f, 0.0850f, -0.3034f, -0.7517f, 0.2274f, 0.5396f },
{ -0.1116f, 0.1668f, -0.0507f, -0.6523f, -0.4813f, 0.4763f, 0.3407f },
{ -0.2405f, 0.9094f, -0.0506f, 0.5760f, 0.4704f, -0.2857f, -0.6044f },
{ -0.3176f, 0.7359f, -0.0975f, 0.6763f, 0.3093f, -0.4295f, -0.5124f },
{ 0.2347f, 0.9199f, -0.0485f, -0.2118f, -0.5948f, 0.6074f, 0.4821f },
{ 0.3218f, 0.7561f, -0.1103f, -0.3042f, -0.5533f, 0.6767f, 0.3788f },
{ 0.1263f, 0.5507f, -0.0237f, -0.4021f, -0.4380f, 0.5803f, 0.5565f },
{ -0.1264f, 0.5507f, -0.0237f, -0.6816f, -0.4388f, 0.4971f, 0.3094f },
{ -0.3969f, 0.5810f, -0.0498f, 0.7127f, 0.3100f, -0.3581f, -0.5174f },
{ 0.4170f, 0.6028f, -0.1117f, -0.2846f, -0.5336f, 0.7187f, 0.3430f },
{ -0.3969f, 0.5810f, -0.0498f, 0.7127f, 0.3100f, -0.3581f, -0.5174f },
{ 0.4170f, 0.6028f, -0.1117f, -0.2846f, -0.5336f, 0.7187f, 0.3430f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4966f, -0.5033f, -0.4967f, 0.5034f },
{ 0.0000f, 0.7159f, -0.0027f, 0.4811f, -0.5202f, -0.4708f, 0.5256f },
{ -0.0041f, 0.9764f, -0.0273f, 0.3576f, -0.6171f, -0.3723f, 0.5938f },
{ 0.1391f, 0.2830f, -0.0374f, -0.2823f, -0.5159f, 0.4325f, 0.6834f },
{ 0.1203f, 0.1052f, -0.1303f, -0.4161f, -0.4278f, 0.5854f, 0.5487f },
{ -0.1657f, 0.3188f, 0.1043f, -0.3151f, -0.7538f, 0.2373f, 0.5255f },
{ -0.1155f, 0.1728f, -0.0252f, -0.6576f, -0.4846f, 0.4733f, 0.3297f },
{ -0.2406f, 0.9099f, -0.0526f, 0.6257f, 0.5030f, -0.2244f, -0.5523f },
{ -0.3175f, 0.7384f, -0.1063f, 0.7505f, 0.2852f, -0.3840f, -0.4560f },
{ 0.2346f, 0.9204f, -0.0509f, -0.1745f, -0.5883f, 0.6146f, 0.4957f },
{ 0.3221f, 0.7612f, -0.1230f, -0.2550f, -0.5581f, 0.6778f, 0.4050f },
{ 0.1263f, 0.5501f, -0.0246f, -0.3915f, -0.4389f, 0.5756f, 0.5681f },
{ -0.1264f, 0.5501f, -0.0246f, -0.7044f, -0.4140f, 0.5051f, 0.2779f },
{ -0.4153f, 0.5979f, -0.0493f, 0.7958f, 0.2443f, -0.3466f, -0.4323f },
{ 0.4199f, 0.6107f, -0.1422f, -0.2464f, -0.5391f, 0.7247f, 0.3513f },
{ -0.4153f, 0.5979f, -0.0493f, 0.7958f, 0.2443f, -0.3466f, -0.4323f },
{ 0.4199f, 0.6107f, -0.1422f, -0.2464f, -0.5391f, 0.7247f, 0.3513f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4887f, -0.5110f, -0.4887f, 0.5111f },
{ 0.0000f, 0.7157f, -0.0091f, 0.4900f, -0.5113f, -0.4803f, 0.5175f },
{ -0.0042f, 0.9769f, -0.0244f, 0.3877f, -0.5975f, -0.4025f, 0.5750f },
{ 0.1373f, 0.2823f, -0.0405f, -0.2982f, -0.4989f, 0.4585f, 0.6723f },
{ 0.1208f, 0.0981f, -0.1206f, -0.4212f, -0.4176f, 0.5947f, 0.5428f },
{ -0.1748f, 0.3369f, 0.1298f, -0.3270f, -0.7563f, 0.2521f, 0.5075f },
{ -0.1202f, 0.1857f, 0.0083f, -0.6632f, -0.4884f, 0.4728f, 0.3133f },
{ -0.2407f, 0.9113f, -0.0516f, 0.6768f, 0.5287f, -0.1149f, -0.4993f },
{ -0.3218f, 0.7490f, -0.1245f, 0.8238f, 0.2427f, -0.2904f, -0.4221f },
{ 0.2345f, 0.9219f, -0.0504f, -0.1118f, -0.5874f, 0.6213f, 0.5063f },
{ 0.3248f, 0.7732f, -0.1395f, -0.1834f, -0.5692f, 0.6790f, 0.4259f },
{ 0.1263f, 0.5494f, -0.0258f, -0.3860f, -0.4345f, 0.5759f, 0.5749f },
{ -0.1264f, 0.5494f, -0.0258f, -0.7324f, -0.3776f, 0.5167f, 0.2326f },
{ -0.4505f, 0.6326f, -0.0751f, 0.8705f, 0.1334f, -0.2888f, -0.3756f },
{ 0.4277f, 0.6311f, -0.1821f, -0.1905f, -0.5537f, 0.7320f, 0.3483f },
{ -0.4505f, 0.6326f, -0.0751f, 0.8705f, 0.1334f, -0.2888f, -0.3756f },
{ 0.4277f, 0.6311f, -0.1821f, -0.1905f, -0.5537f, 0.7320f, 0.3483f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4797f, -0.5195f, -0.4797f, 0.5195f },
{ -0.0001f, 0.7153f, -0.0163f, 0.5035f, -0.4974f, -0.4946f, 0.5045f },
{ -0.0042f, 0.9769f, -0.0173f, 0.4262f, -0.5690f, -0.4414f, 0.5475f },
{ 0.1366f, 0.2812f, -0.0389f, -0.3135f, -0.4813f, 0.4834f, 0.6605f },
{ 0.1226f, 0.0916f, -0.1059f, -0.4283f, -0.4049f, 0.6063f, 0.5339f },
{ -0.1853f, 0.3624f, 0.1562f, -0.3371f, -0.7591f, 0.2705f, 0.4868f },
{ -0.1250f, 0.2061f, 0.0440f, -0.6687f, -0.4919f, 0.4753f, 0.2914f },
{ -0.2408f, 0.9128f, -0.0475f, 0.7174f, 0.5278f, 0.0047f, -0.4547f },
{ -0.3274f, 0.7656f, -0.1427f, 0.8702f, 0.1899f, -0.1809f, -0.4172f },
{ 0.2343f, 0.9235f, -0.0467f, -0.0236f, -0.5932f, 0.6273f, 0.5039f },
{ 0.3303f, 0.7944f, -0.1578f, -0.0906f, -0.5868f, 0.6804f, 0.4297f },
{ 0.1263f, 0.5484f, -0.0271f, -0.3851f, -0.4262f, 0.5810f, 0.5766f },
{ -0.1264f, 0.5484f, -0.0271f, -0.7606f, -0.3338f, 0.5279f, 0.1774f },
{ -0.4830f, 0.6787f, -0.1145f, 0.9050f, 0.0179f, -0.2099f, -0.3696f },
{ 0.4412f, 0.6697f, -0.2266f, -0.1171f, -0.5791f, 0.7383f, 0.3252f },
{ -0.4830f, 0.6787f, -0.1145f, 0.9050f, 0.0179f, -0.2099f, -0.3696f },
{ 0.4412f, 0.6697f, -0.2266f, -0.1171f, -0.5791f, 0.7383f, 0.3252f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4710f, -0.5274f, -0.4710f, 0.5274f },
{ -0.0001f, 0.7146f, -0.0230f, 0.5201f, -0.4795f, -0.5119f, 0.4874f },
{ -0.0043f, 0.9757f, -0.0060f, 0.4679f, -0.5331f, -0.4840f, 0.5124f },
{ 0.1377f, 0.2801f, -0.0329f, -0.3262f, -0.4655f, 0.5045f, 0.6499f },
{ 0.1261f, 0.0867f, -0.0885f, -0.4363f, -0.3903f, 0.6207f, 0.5215f },
{ -0.1963f, 0.3932f, 0.1790f, -0.3444f, -0.7619f, 0.2909f, 0.4650f },
{ -0.1298f, 0.2329f, 0.0765f, -0.6744f, -0.4935f, 0.4810f, 0.2650f },
{ -0.2409f, 0.9138f, -0.0401f, 0.7485f, 0.5011f, 0.1160f, -0.4186f },
{ -0.3330f, 0.7861f, -0.1561f, 0.8860f, 0.1621f, -0.0601f, -0.4302f },
{ 0.2342f, 0.9245f, -0.0395f, 0.0847f, -0.6068f, 0.6321f, 0.4745f },
{ 0.3389f, 0.8273f, -0.1730f, 0.0165f, -0.6124f, 0.6810f, 0.4011f },
{ 0.1263f, 0.5475f, -0.0283f, -0.3882f, -0.4153f, 0.5906f, 0.5728f },
{ -0.1264f, 0.5475f, -0.0283f, -0.7854f, -0.2869f, 0.5358f, 0.1175f },
{ -0.5027f, 0.7250f, -0.1620f, 0.9079f, -0.0293f, -0.1070f, -0.4043f },
{ 0.4612f, 0.7324f, -0.2658f, -0.0326f, -0.6166f, 0.7389f, 0.2698f },
{ -0.5027f, 0.7250f, -0.1620f, 0.9079f, -0.0293f, -0.1070f, -0.4043f },
{ 0.4612f, 0.7324f, -0.2658f, -0.0326f, -0.6166f, 0.7389f, 0.2698f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4642f, -0.5334f, -0.4642f, 0.5334f },
{ -0.0001f, 0.7139f, -0.0282f, 0.5385f, -0.4586f, -0.5305f, 0.4671f },
{ -0.0044f, 0.9729f, 0.0092f, 0.5088f, -0.4920f, -0.5255f, 0.4721f },
{ 0.1410f, 0.2795f, -0.0231f, -0.3339f, -0.4541f, 0.5194f, 0.6422f },
{ 0.1314f, 0.0840f, -0.0707f, -0.4440f, -0.3743f, 0.6382f, 0.5055f },
{ -0.2073f, 0.4256f, 0.1954f, -0.3485f, -0.7645f, 0.3107f, 0.4444f },
{ -0.1343f, 0.2625f, 0.1021f, -0.6812f, -0.4913f, 0.4891f, 0.2354f },
{ -0.2410f, 0.9138f, -0.0293f, 0.7824f, 0.4383f, 0.2313f, -0.3771f },
{ -0.3405f, 0.8138f, -0.1647f, 0.8826f, 0.1594f, 0.0958f, -0.4319f },
{ 0.2341f, 0.9246f, -0.0286f, 0.1981f, -0.6288f, 0.6345f, 0.4035f },
{ 0.3506f, 0.8732f, -0.1770f, 0.1209f, -0.6481f, 0.6785f, 0.3241f },
{ 0.1263f, 0.5468f, -0.0292f, -0.3943f, -0.4028f, 0.6044f, 0.5630f },
{ -0.1264f, 0.5468f, -0.0292f, -0.8047f, -0.2416f, 0.5390f, 0.0591f },
{ -0.5085f, 0.7779f, -0.2201f, 0.8970f, -0.0028f, 0.0503f, -0.4391f },
{ 0.4879f, 0.8221f, -0.2824f, 0.0461f, -0.6643f, 0.7266f, 0.1694f },
{ -0.5085f, 0.7779f, -0.2201f, 0.8970f, -0.0028f, 0.0503f, -0.4391f },
{ 0.4879f, 0.8221f, -0.2824f, 0.0461f, -0.6643f, 0.7266f, 0.1694f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4609f, -0.5362f, -0.4609f, 0.5363f },
{ -0.0001f, 0.7136f, -0.0307f, 0.5572f, -0.4361f, -0.5492f, 0.4447f },
{ -0.0044f, 0.9686f, 0.0279f, 0.5452f, -0.4491f, -0.5624f, 0.4299f },
{ 0.1472f, 0.2803f, -0.0097f, -0.3345f, -0.4494f, 0.5262f, 0.6398f },
{ 0.1387f, 0.0840f, -0.0547f, -0.4498f, -0.3569f, 0.6592f, 0.4855f },
{ -0.2174f, 0.4550f, 0.2049f, -0.3502f, -0.7670f, 0.3267f, 0.4270f },
{ -0.1388f, 0.2905f, 0.1190f, -0.6909f, -0.4830f, 0.4976f, 0.2043f },
{ -0.2410f, 0.9128f, -0.0152f, 0.8055f, 0.3507f, 0.3167f, -0.3576f },
{ -0.3492f, 0.8466f, -0.1640f, 0.8662f, 0.1466f, 0.2214f, -0.4233f },
{ 0.2341f, 0.9236f, -0.0139f, 0.2891f, -0.6598f, 0.6330f, 0.2836f },
{ 0.3655f, 0.9280f, -0.1587f, 0.1923f, -0.6942f, 0.6669f, 0.1906f },
{ 0.1263f, 0.5464f, -0.0297f, -0.4024f, -0.3897f, 0.6222f, 0.5468f },
{ -0.1264f, 0.5464f, -0.0297f, -0.8185f, -0.2024f, 0.5376f, 0.0095f },
{ -0.5043f, 0.8346f, -0.2556f, 0.8745f, 0.0282f, 0.1879f, -0.4462f },
{ 0.5195f, 0.9303f, -0.2527f, 0.0893f, -0.7143f, 0.6938f, 0.0207f },
{ -0.5043f, 0.8346f, -0.2556f, 0.8745f, 0.0282f, 0.1879f, -0.4462f },
{ 0.5195f, 0.9303f, -0.2527f, 0.0893f, -0.7143f, 0.6938f, 0.0207f } }, {{ 0.0000f, 0.5114f, 0.0000f, 0.4626f, -0.5348f, -0.4626f, 0.5348f },
{ -0.0001f, 0.7138f, -0.0295f, 0.5750f, -0.4134f, -0.5665f, 0.4214f },
{ -0.0043f, 0.9631f, 0.0498f, 0.5748f, -0.4089f, -0.5919f, 0.3901f },
{ 0.1568f, 0.2831f, 0.0065f, -0.3248f, -0.4534f, 0.5228f, 0.6447f },
{ 0.1483f, 0.0878f, -0.0428f, -0.4523f, -0.3384f, 0.6843f, 0.4612f },
{ -0.2262f, 0.4766f, 0.2089f, -0.3511f, -0.7697f, 0.3348f, 0.4149f },
{ -0.1437f, 0.3117f, 0.1276f, -0.7062f, -0.4659f, 0.5040f, 0.1739f },
{ -0.2410f, 0.9111f, 0.0022f, 0.7951f, 0.2858f, 0.3464f, -0.4076f },
{ -0.3577f, 0.8774f, -0.1510f, 0.8376f, 0.1112f, 0.2523f, -0.4716f },
{ 0.2341f, 0.9216f, 0.0046f, 0.3220f, -0.6996f, 0.6251f, 0.1270f },
{ 0.3828f, 0.9787f, -0.1089f, 0.1915f, -0.7460f, 0.6377f, 0.0131f },
{ 0.1263f, 0.5466f, -0.0295f, -0.4110f, -0.3770f, 0.6440f, 0.5236f },
{ -0.1264f, 0.5466f, -0.0294f, -0.8281f, -0.1731f, 0.5326f, -0.0239f },
{ -0.5107f, 0.8867f, -0.2462f, 0.8404f, 0.0121f, 0.2213f, -0.4946f },
{ 0.5500f, 1.0272f, -0.1565f, 0.0597f, -0.7518f, 0.6374f, -0.1579f },
{ -0.5107f, 0.8867f, -0.2462f, 0.8404f, 0.0121f, 0.2213f, -0.4946f },
{ 0.5500f, 1.0272f, -0.1565f, 0.0597f, -0.7518f, 0.6374f, -0.1579f } },};


