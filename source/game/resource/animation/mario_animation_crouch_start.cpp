#include "game/component/Animator.h"
#include "game/resource/animation.h"

// 17 bones
AnimationMatrix const mario_animation_crouch_start[] = { // 5 frames
	{
	-0.000001f, 0.000096f, -1.000000f, -0.000049f,
	-0.999881f, -0.015435f, 0.000000f, 0.511360f,
	-0.015435f, 0.999881f, 0.000096f, 0.000000f
	},
	{
	-0.000021f, 0.000093f, -1.000000f, -0.000049f,
	-0.974919f, -0.222561f, 0.000000f, 0.715879f,
	-0.222561f, 0.974919f, 0.000096f, 0.003157f
	},
	{
	0.894784f, 0.053226f, -0.443316f, -0.237679f,
	0.321307f, 0.612664f, 0.722083f, 0.919055f,
	0.310037f, -0.788549f, 0.531100f, 0.018709f
	},
	{
	0.275514f, -0.852973f, -0.443316f, -0.412627f,
	0.673589f, -0.157716f, 0.722083f, 0.856233f,
	-0.685835f, -0.497556f, 0.531100f, -0.041910f
	},
	{
	-0.053316f, -0.887535f, -0.457645f, -0.462352f,
	0.414832f, -0.436565f, 0.798326f, 0.734664f,
	-0.908334f, -0.147282f, 0.391454f, 0.081870f
	},
	{
	-0.053316f, -0.887535f, -0.457645f, -0.462352f,
	0.414833f, -0.436565f, 0.798326f, 0.734664f,
	-0.908334f, -0.147282f, 0.391455f, 0.081870f
	},
	{
	-0.880020f, -0.061725f, -0.470908f, 0.237585f,
	0.397709f, 0.446191f, -0.801711f, 0.921988f,
	0.259600f, -0.892807f, -0.368109f, 0.019333f
	},
	{
	-0.229365f, 0.851843f, -0.470908f, 0.409647f,
	0.514187f, -0.304746f, -0.801711f, 0.844228f,
	-0.826440f, -0.426020f, -0.368109f, -0.031425f
	},
	{
	-0.000033f, 0.882182f, -0.470908f, 0.451042f,
	0.417287f, -0.427938f, -0.801711f, 0.751427f,
	-0.908775f, -0.196530f, -0.368109f, 0.117731f
	},
	{
	-0.000033f, 0.882182f, -0.470908f, 0.451042f,
	0.417287f, -0.427938f, -0.801711f, 0.751427f,
	-0.908775f, -0.196530f, -0.368109f, 0.117731f
	},
	{
	0.465870f, 0.755669f, -0.460358f, -0.126387f,
	0.856266f, -0.516177f, 0.019224f, 0.550831f,
	-0.223099f, -0.403145f, -0.887525f, -0.023445f
	},
	{
	-0.313495f, 0.830537f, -0.460358f, -0.251106f,
	0.931830f, 0.362385f, 0.019224f, 0.321598f,
	0.182793f, -0.422948f, -0.887525f, 0.036281f
	},
	{
	0.836167f, 0.298155f, -0.460358f, -0.187926f,
	0.345172f, -0.938343f, 0.019224f, 0.133800f,
	-0.426241f, -0.174977f, -0.887525f, -0.000559f
	},
	{
	-0.411234f, -0.561489f, -0.718065f, 0.126285f,
	0.806698f, -0.590964f, 0.000109f, 0.550831f,
	-0.424411f, -0.579217f, 0.695976f, -0.023469f
	},
	{
	0.077278f, -0.691673f, -0.718065f, 0.236377f,
	0.993829f, 0.110924f, 0.000109f, 0.334868f,
	0.079575f, -0.713642f, 0.695976f, 0.090151f
	},
	{
	-0.638646f, -0.240522f, -0.730945f, 0.220803f,
	0.345413f, -0.938425f, 0.006998f, 0.134575f,
	-0.687620f, -0.248009f, 0.682400f, 0.074113f
	},
	{
	-0.000013f, 0.000095f, -1.000000f, -0.000043f,
	-0.990812f, -0.135246f, 0.000000f, 0.971012f,
	-0.135246f, 0.990812f, 0.000096f, 0.061401f
	},
	{
	-0.000005f, 0.000096f, -1.000000f, -0.000049f,
	-0.998373f, -0.057014f, 0.000000f, 0.490304f,
	-0.057014f, 0.998373f, 0.000096f, -0.021056f
	},
	{
	-0.000032f, 0.000090f, -1.000000f, -0.000048f,
	-0.943847f, -0.330383f, 0.000000f, 0.694515f,
	-0.330382f, 0.943847f, 0.000096f, -0.009394f
	},
	{
	0.900859f, 0.047822f, -0.431469f, -0.237676f,
	0.302911f, 0.642714f, 0.703678f, 0.894672f,
	0.310963f, -0.764611f, 0.564509f, 0.028822f
	},
	{
	0.503076f, -0.748832f, -0.431469f, -0.413812f,
	0.707103f, 0.069589f, 0.703678f, 0.835447f,
	-0.496911f, -0.659096f, 0.564509f, -0.031978f
	},
	{
	0.191794f, -0.893470f, -0.406110f, -0.504607f,
	0.545709f, -0.246843f, 0.800793f, 0.707829f,
	-0.815730f, -0.375206f, 0.440232f, 0.057705f
	},
	{
	0.191794f, -0.893470f, -0.406110f, -0.504607f,
	0.545709f, -0.246842f, 0.800793f, 0.707829f,
	-0.815730f, -0.375206f, 0.440232f, 0.057705f
	},
	{
	-0.874961f, -0.088590f, -0.476019f, 0.237588f,
	0.382633f, 0.475932f, -0.791884f, 0.897511f,
	0.296706f, -0.875009f, -0.382525f, 0.029770f
	},
	{
	-0.490653f, 0.729839f, -0.476020f, 0.408660f,
	0.600117f, -0.113042f, -0.791884f, 0.822699f,
	-0.631758f, -0.674208f, -0.382525f, -0.028242f
	},
	{
	-0.284055f, 0.832297f, -0.476020f, 0.497214f,
	0.550098f, -0.265163f, -0.791884f, 0.714390f,
	-0.785305f, -0.486796f, -0.382525f, 0.085778f
	},
	{
	-0.284055f, 0.832297f, -0.476019f, 0.497214f,
	0.550098f, -0.265163f, -0.791884f, 0.714390f,
	-0.785305f, -0.486796f, -0.382525f, 0.085778f
	},
	{
	0.484079f, 0.668565f, -0.564525f, -0.126387f,
	0.790779f, -0.610454f, -0.044868f, 0.530716f,
	-0.374614f, -0.424695f, -0.824195f, -0.042839f
	},
	{
	-0.364698f, 0.740477f, -0.564525f, -0.255981f,
	0.909328f, 0.413653f, -0.044868f, 0.319015f,
	0.200294f, -0.529702f, -0.824195f, 0.057450f
	},
	{
	0.759583f, 0.286098f, -0.584108f, -0.182481f,
	0.357516f, -0.933877f, 0.007504f, 0.135753f,
	-0.543338f, -0.214528f, -0.811641f, 0.017083f
	},
	{
	-0.420570f, -0.513045f, -0.748269f, 0.126285f,
	0.754909f, -0.655352f, 0.025034f, 0.530716f,
	-0.503223f, -0.554346f, 0.662923f, -0.042863f
	},
	{
	0.102733f, -0.655393f, -0.748269f, 0.238877f,
	0.991605f, 0.126852f, 0.025034f, 0.328618f,
	0.078512f, -0.744559f, 0.662923f, 0.091856f
	},
	{
	-0.602387f, -0.221795f, -0.766771f, 0.218173f,
	0.335198f, -0.942103f, 0.009174f, 0.128774f,
	-0.724411f, -0.251494f, 0.641856f, 0.076032f
	},
	{
	-0.000016f, 0.000094f, -1.000000f, -0.000039f,
	-0.986466f, -0.163968f, 0.000000f, 0.941516f,
	-0.163968f, 0.986466f, 0.000096f, 0.077066f
	},
	{
	-0.000022f, 0.000093f, -1.000000f, -0.000049f,
	-0.973491f, -0.228725f, 0.000000f, 0.421120f,
	-0.228725f, 0.973491f, 0.000096f, -0.057152f
	},
	{
	-0.000067f, 0.000068f, -1.000000f, -0.000044f,
	-0.710825f, -0.703368f, 0.000000f, 0.620242f,
	-0.703368f, 0.710825f, 0.000096f, -0.010367f
	},
	{
	0.921426f, -0.081031f, -0.380011f, -0.237665f,
	0.282587f, 0.811005f, 0.512265f, 0.784656f,
	0.266682f, -0.579401f, 0.770179f, 0.110028f
	},
	{
	0.568105f, -0.729964f, -0.380011f, -0.417822f,
	0.786350f, 0.345309f, 0.512265f, 0.729404f,
	-0.242714f, -0.589842f, 0.770179f, 0.057886f
	},
	{
	0.230902f, -0.939824f, -0.251822f, -0.520354f,
	0.784910f, 0.026977f, 0.619021f, 0.587484f,
	-0.574977f, -0.340591f, 0.743907f, 0.101691f
	},
	{
	0.230902f, -0.939824f, -0.251823f, -0.520354f,
	0.784911f, 0.026978f, 0.619021f, 0.587484f,
	-0.574977f, -0.340592f, 0.743908f, 0.101691f
	},
	{
	-0.846762f, -0.057528f, -0.528853f, 0.237599f,
	0.372149f, 0.646320f, -0.666165f, 0.786794f,
	0.380131f, -0.760895f, -0.525870f, 0.112098f
	},
	{
	-0.596758f, 0.603485f, -0.528853f, 0.403158f,
	0.732450f, 0.140505f, -0.666165f, 0.714031f,
	-0.327714f, -0.784897f, -0.525870f, 0.037775f
	},
	{
	-0.390182f, 0.791567f, -0.470297f, 0.510861f,
	0.770781f, 0.001414f, -0.637099f, 0.581839f,
	-0.503641f, -0.611080f, -0.610677f, 0.096921f
	},
	{
	-0.390182f, 0.791567f, -0.470297f, 0.510861f,
	0.770781f, 0.001414f, -0.637099f, 0.581839f,
	-0.503641f, -0.611080f, -0.610677f, 0.096921f
	},
	{
	0.564252f, 0.419625f, -0.711010f, -0.126386f,
	0.581294f, -0.813476f, -0.018788f, 0.464691f,
	-0.586274f, -0.402705f, -0.702931f, -0.071622f
	},
	{
	-0.385307f, 0.588221f, -0.711010f, -0.277443f,
	0.846623f, 0.531861f, -0.018788f, 0.309072f,
	0.367107f, -0.609197f, -0.702931f, 0.085331f
	},
	{
	0.644847f, 0.179568f, -0.742919f, -0.199790f,
	0.340767f, -0.937600f, 0.069158f, 0.138447f,
	-0.684142f, -0.297759f, -0.665799f, 0.011346f
	},
	{
	-0.458397f, -0.300100f, -0.836548f, 0.126286f,
	0.473192f, -0.879171f, 0.056099f, 0.464691f,
	-0.752304f, -0.370132f, 0.545014f, -0.071646f
	},
	{
	0.138725f, -0.530040f, -0.836548f, 0.249004f,
	0.984018f, 0.169002f, 0.056099f, 0.338012f,
	0.111644f, -0.830960f, 0.545014f, 0.129755f
	},
	{
	-0.474001f, -0.199416f, -0.857646f, 0.221046f,
	0.359845f, -0.932838f, 0.018021f, 0.139697f,
	-0.803638f, -0.300077f, 0.513925f, 0.107255f
	},
	{
	-0.000025f, 0.000093f, -1.000000f, -0.000027f,
	-0.966215f, -0.257739f, 0.000000f, 0.806262f,
	-0.257738f, 0.966215f, 0.000096f, 0.173701f
	},
	{
	-0.000036f, 0.000089f, -1.000000f, -0.000049f,
	-0.925921f, -0.377718f, 0.000000f, 0.336896f,
	-0.377718f, 0.925921f, 0.000096f, -0.081216f
	},
	{
	-0.000090f, 0.000032f, -1.000000f, -0.000041f,
	-0.335716f, -0.941963f, 0.000000f, 0.526287f,
	-0.941963f, 0.335716f, 0.000096f, -0.003956f
	},
	{
	0.943010f, 0.012669f, -0.332523f, -0.237656f,
	0.166969f, 0.846363f, 0.505758f, 0.622280f,
	0.287842f, -0.532455f, 0.796013f, 0.175808f
	},
	{
	-0.193368f, -0.923059f, -0.332523f, -0.422034f,
	0.789549f, -0.347594f, 0.505758f, 0.589635f,
	-0.582427f, -0.164745f, 0.796013f, 0.119529f
	},
	{
	-0.517465f, -0.745380f, -0.420285f, -0.387134f,
	0.470190f, -0.658042f, 0.588134f, 0.447137f,
	-0.714948f, 0.106725f, 0.690983f, 0.224646f
	},
	{
	-0.517464f, -0.745380f, -0.420285f, -0.387134f,
	0.470191f, -0.658041f, 0.588134f, 0.447137f,
	-0.714948f, 0.106724f, 0.690984f, 0.224645f
	},
	{
	-0.831203f, -0.318401f, -0.455766f, 0.237608f,
	0.145871f, 0.666153f, -0.731411f, 0.623290f,
	0.536492f, -0.674434f, -0.507262f, 0.178596f
	},
	{
	-0.067236f, 0.887557f, -0.455766f, 0.400125f,
	0.596555f, -0.330393f, -0.731411f, 0.594770f,
	-0.799750f, -0.321066f, -0.507262f, 0.073701f
	},
	{
	0.165806f, 0.874520f, -0.455766f, 0.412259f,
	0.490156f, -0.474115f, -0.731411f, 0.487103f,
	-0.855719f, -0.102124f, -0.507262f, 0.218040f
	},
	{
	0.165806f, 0.874520f, -0.455766f, 0.412260f,
	0.490156f, -0.474115f, -0.731411f, 0.487103f,
	-0.855719f, -0.102124f, -0.507262f, 0.218040f
	},
	{
	0.459947f, 0.056119f, -0.886171f, -0.126386f,
	0.278600f, -0.956725f, 0.084014f, 0.382192f,
	-0.843108f, -0.285529f, -0.455678f, -0.088715f
	},
	{
	-0.173428f, 0.429678f, -0.886171f, -0.249519f,
	0.851804f, 0.517080f, 0.084014f, 0.307608f,
	0.494320f, -0.740274f, -0.455678f, 0.136995f
	},
	{
	0.458715f, 0.165310f, -0.873072f, -0.214567f,
	0.347120f, -0.937808f, 0.004811f, 0.135939f,
	-0.817978f, -0.305267f, -0.487568f, 0.037372f
	},
	{
	-0.492980f, -0.090356f, -0.865336f, 0.126286f,
	0.138714f, -0.990033f, 0.024352f, 0.382192f,
	-0.858911f, -0.108030f, 0.500600f, -0.088739f
	},
	{
	0.117662f, -0.487185f, -0.865336f, 0.258263f,
	0.980775f, 0.193618f, 0.024351f, 0.345057f,
	0.155681f, -0.851565f, 0.500600f, 0.141202f
	},
	{
	-0.441436f, -0.192053f, -0.876499f, 0.234550f,
	0.361899f, -0.931959f, 0.021941f, 0.147396f,
	-0.821075f, -0.307519f, 0.480904f, 0.109827f
	},
	{
	-0.000037f, 0.000088f, -1.000000f, -0.000018f,
	-0.922627f, -0.385693f, 0.000000f, 0.614143f,
	-0.385693f, 0.922627f, 0.000096f, 0.242552f
	},
	{
	-0.000040f, 0.000087f, -1.000000f, -0.000049f,
	-0.909986f, -0.414640f, 0.000000f, 0.315840f,
	-0.414640f, 0.909985f, 0.000096f, -0.096256f
	},
	{
	-0.000096f, 0.000001f, -1.000000f, -0.000041f,
	-0.009350f, -0.999956f, 0.000000f, 0.501972f,
	-0.999956f, 0.009350f, 0.000096f, -0.011444f
	},
	{
	0.967192f, 0.136839f, 0.214044f, -0.237653f,
	-0.220604f, 0.034539f, 0.974752f, 0.533935f,
	0.125991f, -0.989991f, 0.063593f, 0.189825f
	},
	{
	0.213929f, -0.953110f, 0.214044f, -0.426759f,
	0.016744f, 0.222662f, 0.974752f, 0.577067f,
	-0.976706f, -0.204944f, 0.063593f, 0.165191f
	},
	{
	-0.227247f, -0.639464f, -0.734468f, -0.465369f,
	-0.326835f, -0.660375f, 0.676079f, 0.574045f,
	-0.917353f, 0.393687f, -0.058931f, 0.341467f
	},
	{
	-0.227247f, -0.639465f, -0.734468f, -0.465369f,
	-0.326834f, -0.660375f, 0.676079f, 0.574045f,
	-0.917353f, 0.393687f, -0.058931f, 0.341467f
	},
	{
	-0.879013f, 0.100132f, 0.466164f, 0.237611f,
	-0.475710f, -0.118204f, -0.871624f, 0.533963f,
	-0.032175f, -0.987928f, 0.151537f, 0.192788f
	},
	{
	0.031976f, 0.884120f, 0.466164f, 0.409476f,
	-0.154574f, 0.465165f, -0.871624f, 0.626974f,
	-0.987463f, -0.044186f, 0.151537f, 0.199078f
	},
	{
	0.352827f, 0.825348f, -0.440811f, 0.403705f,
	-0.386099f, -0.300710f, -0.872067f, 0.654871f,
	-0.852315f, 0.477885f, 0.212567f, 0.377296f
	},
	{
	0.352827f, 0.825348f, -0.440811f, 0.403705f,
	-0.386099f, -0.300710f, -0.872067f, 0.654871f,
	-0.852315f, 0.477885f, 0.212567f, 0.377296f
	},
	{
	0.443007f, -0.041607f, -0.895552f, -0.126385f,
	0.192348f, -0.971249f, 0.140273f, 0.361402f,
	-0.875641f, -0.234399f, -0.422268f, -0.101928f
	},
	{
	-0.096627f, 0.434338f, -0.895552f, -0.244984f,
	0.865051f, 0.481674f, 0.140273f, 0.309908f,
	0.492290f, -0.761144f, -0.422268f, 0.132492f
	},
	{
	0.446949f, 0.150730f, -0.881769f, -0.225510f,
	0.350185f, -0.936519f, 0.017412f, 0.135569f,
	-0.823168f, -0.316565f, -0.471360f, 0.033278f
	},
	{
	-0.499391f, -0.051312f, -0.864856f, 0.126287f,
	0.083558f, -0.996444f, 0.010870f, 0.361402f,
	-0.862338f, -0.066837f, 0.501902f, -0.101952f
	},
	{
	0.113839f, -0.488942f, -0.864856f, 0.259980f,
	0.977968f, 0.208469f, 0.010870f, 0.339032f,
	0.174981f, -0.847039f, 0.501902f, 0.128907f
	},
	{
	-0.447163f, -0.191835f, -0.873639f, 0.237037f,
	0.362161f, -0.931917f, 0.019264f, 0.141937f,
	-0.817854f, -0.307784f, 0.486194f, 0.093641f
	},
	{
	-0.000058f, 0.000076f, -1.000000f, -0.000016f,
	-0.792430f, -0.609963f, 0.000000f, 0.504419f,
	-0.609963f, 0.792430f, 0.000096f, 0.250241f
	},
};

