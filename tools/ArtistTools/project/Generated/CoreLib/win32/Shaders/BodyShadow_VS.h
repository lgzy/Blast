#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /T vs_5_0 /I..\..\..\..\src /Fh
//    ..\..\project\Generated\CoreLib\win32\Shaders\BodyShadow_VS.h /Evs_main
//    ..\..\source\Shaders\BodyShadow.hlsl
//
//
// Buffer Definitions: 
//
// cbuffer cbPerFrame
// {
//
//   row_major float4x4 g_ViewProjection;// Offset:    0 Size:    64
//   row_major float4x4 g_ViewMatrix;   // Offset:   64 Size:    64
//   row_major float4x4 g_BodyTransformation;// Offset:  128 Size:    64
//   int g_useDQs;                      // Offset:  192 Size:     4
//   int g_usePinPos;                   // Offset:  196 Size:     4
//   float _reserved2;                  // Offset:  200 Size:     4 [unused]
//   float _reserved3;                  // Offset:  204 Size:     4 [unused]
//   row_major float4x4 g_boneMatrices[512];// Offset:  208 Size: 32768
//   
//   struct DQ
//   {
//       
//       float4 q0;                     // Offset: 32976
//       float4 q1;                     // Offset: 32992
//
//   } g_boneDQs[512];                  // Offset: 32976 Size: 16384
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_BoneIndices                     texture  float4         buf    0        1
// g_BoneWeights                     texture  float4         buf    1        1
// cbPerFrame                        cbuffer      NA          NA    0        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// POSITION                 0   xyz         0     NONE  float   xyz 
// VERTEX_NORMAL            0   xyz         1     NONE  float       
// FACE_NORMAL              0   xyz         2     NONE  float       
// TANGENT                  0   xyz         3     NONE  float       
// TEXCOORD                 0   xy          4     NONE  float       
// VERTEX_ID                0   x           5     NONE  float   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Position              0   xyzw        0      POS  float   xyzw
// texcoord                 0   x           1     NONE  float   x   
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer cb0[3085], dynamicIndexed
dcl_resource_buffer (float,float,float,float) t0
dcl_resource_buffer (float,float,float,float) t1
dcl_input v0.xyz
dcl_input v5.x
dcl_output_siv o0.xyzw, position
dcl_output o1.x
dcl_temps 7
ftoi r0.x, v5.x
ld_indexable(buffer)(float,float,float,float) r1.xyzw, r0.xxxx, t0.xyzw
ld_indexable(buffer)(float,float,float,float) r0.xyzw, r0.xxxx, t1.xyzw
if_nz cb0[12].x
  ftou r2.xyzw, r1.xyzw
  ishl r2.xyzw, r2.xyzw, l(1, 1, 1, 1)
  mul r3.xyzw, r0.xxxx, cb0[r2.x + 2061].xyzw
  mul r4.xyzw, r0.yyyy, cb0[r2.y + 2061].xyzw
  mul r5.xyzw, r0.yyyy, cb0[r2.y + 2062].xyzw
  dp4 r2.y, r3.xyzw, r4.xyzw
  lt r2.y, r2.y, l(-0.000000)
  movc r2.y, r2.y, l(-1.000000), l(1.000000)
  mad r3.xyzw, r2.yyyy, r4.xyzw, r3.xyzw
  mul r4.xyzw, r5.xyzw, r2.yyyy
  mad r4.xyzw, cb0[r2.x + 2062].xyzw, r0.xxxx, r4.xyzw
  mul r5.xyzw, r0.zzzz, cb0[r2.z + 2061].xyzw
  mul r6.xyzw, r0.zzzz, cb0[r2.z + 2062].xyzw
  dp4 r2.x, r3.xyzw, r5.xyzw
  lt r2.x, r2.x, l(-0.000000)
  movc r2.x, r2.x, l(-1.000000), l(1.000000)
  mad r3.xyzw, r2.xxxx, r5.xyzw, r3.xyzw
  mad r4.xyzw, r2.xxxx, r6.xyzw, r4.xyzw
  mul r5.xyzw, r0.wwww, cb0[r2.w + 2061].xyzw
  mul r2.xyzw, r0.wwww, cb0[r2.w + 2062].xyzw
  dp4 r6.x, r3.xyzw, r5.xyzw
  lt r6.x, r6.x, l(-0.000000)
  movc r6.x, r6.x, l(-1.000000), l(1.000000)
  mad r3.xyzw, r6.xxxx, r5.xyzw, r3.xyzw
  mad r2.xyzw, r6.xxxx, r2.xyzw, r4.xyzw
  dp4 r4.x, r3.xyzw, r3.xyzw
  add r4.x, r4.x, l(0.000000)
  sqrt r4.x, r4.x
  div r4.x, l(1.000000, 1.000000, 1.000000, 1.000000), r4.x
  mul r3.xyzw, r3.xyzw, r4.xxxx
  mul r2.xyzw, r2.xyzw, r4.xxxx
  mul r4.xyz, r3.xyzx, v0.zxyz
  mad r4.xyz, r3.zxyz, v0.xyzx, -r4.xyzx
  mad r4.xyz, r3.wwww, v0.yzxy, r4.xyzx
  mul r5.xyz, r2.wwww, r3.xyzx
  mad r5.xyz, r2.xyzx, r3.wwww, -r5.xyzx
  mul r6.xyz, r2.yzxy, r3.zxyz
  mad r2.xyz, r3.yzxy, r2.zxyz, -r6.xyzx
  add r2.xyz, r2.xyzx, r5.xyzx
  mad r2.xyz, r2.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), v0.xyzx
  add r3.xyz, r3.zxyz, r3.zxyz
  mul r5.xyz, r4.xyzx, r3.xyzx
  mad r3.xyz, r3.zxyz, r4.yzxy, -r5.xyzx
  add r2.xyz, r2.xyzx, r3.xyzx
else 
  add r2.w, r0.y, r0.x
  add r2.w, r0.z, r2.w
  add r2.w, r0.w, r2.w
  add r2.w, r2.w, l(0.000000)
  div r2.w, l(1.000000, 1.000000, 1.000000, 1.000000), r2.w
  ftou r1.xyzw, r1.xyzw
  ishl r1.xyzw, r1.xyzw, l(2, 2, 2, 2)
  mul r0.xyzw, r0.xyzw, r2.wwww
  mul r3.xyz, v0.yyyy, cb0[r1.x + 14].xyzx
  mad r3.xyz, v0.xxxx, cb0[r1.x + 13].xyzx, r3.xyzx
  mad r3.xyz, v0.zzzz, cb0[r1.x + 15].xyzx, r3.xyzx
  add r3.xyz, r3.xyzx, cb0[r1.x + 16].xyzx
  mul r4.xyz, v0.yyyy, cb0[r1.y + 14].xyzx
  mad r4.xyz, v0.xxxx, cb0[r1.y + 13].xyzx, r4.xyzx
  mad r4.xyz, v0.zzzz, cb0[r1.y + 15].xyzx, r4.xyzx
  add r4.xyz, r4.xyzx, cb0[r1.y + 16].xyzx
  mul r4.xyz, r0.yyyy, r4.xyzx
  mad r3.xyz, r0.xxxx, r3.xyzx, r4.xyzx
  mul r4.xyz, v0.yyyy, cb0[r1.z + 14].xyzx
  mad r4.xyz, v0.xxxx, cb0[r1.z + 13].xyzx, r4.xyzx
  mad r4.xyz, v0.zzzz, cb0[r1.z + 15].xyzx, r4.xyzx
  add r1.xyz, r4.xyzx, cb0[r1.z + 16].xyzx
  mad r0.xyz, r0.zzzz, r1.xyzx, r3.xyzx
  mul r1.xyz, v0.yyyy, cb0[r1.w + 14].xyzx
  mad r1.xyz, v0.xxxx, cb0[r1.w + 13].xyzx, r1.xyzx
  mad r1.xyz, v0.zzzz, cb0[r1.w + 15].xyzx, r1.xyzx
  add r1.xyz, r1.xyzx, cb0[r1.w + 16].xyzx
  mad r2.xyz, r0.wwww, r1.xyzx, r0.xyzx
endif 
movc r0.xyz, cb0[12].yyyy, v0.xyzx, r2.xyzx
mul r1.xyz, r0.yyyy, cb0[9].xyzx
mad r0.xyw, r0.xxxx, cb0[8].xyxz, r1.xyxz
mad r0.xyz, r0.zzzz, cb0[10].xyzx, r0.xywx
add r0.xyz, r0.xyzx, cb0[11].xyzx
mul r1.xyzw, r0.yyyy, cb0[1].xyzw
mad r1.xyzw, r0.xxxx, cb0[0].xyzw, r1.xyzw
mad r1.xyzw, r0.zzzz, cb0[2].xyzw, r1.xyzw
add o0.xyzw, r1.xyzw, cb0[3].xyzw
mul r0.y, r0.y, cb0[5].z
mad r0.x, r0.x, cb0[4].z, r0.y
mad r0.x, r0.z, cb0[6].z, r0.x
add o1.x, r0.x, cb0[7].z
ret 
// Approximately 92 instruction slots used
#endif

const BYTE g_vs_main[] =
{
     68,  88,  66,  67,  94, 192, 
    214,   0, 141, 225, 175,  32, 
    164,  25, 116, 198, 255, 171, 
    192, 173,   1,   0,   0,   0, 
    240,  18,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     72,   4,   0,   0,  40,   5, 
      0,   0, 128,   5,   0,   0, 
     84,  18,   0,   0,  82,  68, 
     69,  70,  12,   4,   0,   0, 
      1,   0,   0,   0, 196,   0, 
      0,   0,   3,   0,   0,   0, 
     60,   0,   0,   0,   0,   5, 
    254, 255,   0,   1,   0,   0, 
    216,   3,   0,   0,  82,  68, 
     49,  49,  60,   0,   0,   0, 
     24,   0,   0,   0,  32,   0, 
      0,   0,  40,   0,   0,   0, 
     36,   0,   0,   0,  12,   0, 
      0,   0,   0,   0,   0,   0, 
    156,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      1,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 170,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   1,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 184,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    103,  95,  66, 111, 110, 101, 
     73, 110, 100, 105,  99, 101, 
    115,   0, 103,  95,  66, 111, 
    110, 101,  87, 101, 105, 103, 
    104, 116, 115,   0,  99,  98, 
     80, 101, 114,  70, 114,  97, 
    109, 101,   0, 171, 184,   0, 
      0,   0,   9,   0,   0,   0, 
    220,   0,   0,   0, 208, 192, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  68,   2, 
      0,   0,   0,   0,   0,   0, 
     64,   0,   0,   0,   2,   0, 
      0,   0,  96,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 132,   2,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,   2,   0,   0,   0, 
     96,   2,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    145,   2,   0,   0, 128,   0, 
      0,   0,  64,   0,   0,   0, 
      2,   0,   0,   0,  96,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 166,   2, 
      0,   0, 192,   0,   0,   0, 
      4,   0,   0,   0,   2,   0, 
      0,   0, 180,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 216,   2,   0,   0, 
    196,   0,   0,   0,   4,   0, 
      0,   0,   2,   0,   0,   0, 
    180,   2,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    228,   2,   0,   0, 200,   0, 
      0,   0,   4,   0,   0,   0, 
      0,   0,   0,   0, 248,   2, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  28,   3, 
      0,   0, 204,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0, 248,   2,   0,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,  39,   3,   0,   0, 
    208,   0,   0,   0,   0, 128, 
      0,   0,   2,   0,   0,   0, 
     56,   3,   0,   0,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
     92,   3,   0,   0, 208, 128, 
      0,   0,   0,  64,   0,   0, 
      2,   0,   0,   0, 180,   3, 
      0,   0,   0,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0, 103,  95, 
     86, 105, 101, 119,  80, 114, 
    111, 106, 101,  99, 116, 105, 
    111, 110,   0, 102, 108, 111, 
     97, 116,  52, 120,  52,   0, 
    171, 171,   2,   0,   3,   0, 
      4,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  85,   2, 
      0,   0, 103,  95,  86, 105, 
    101, 119,  77,  97, 116, 114, 
    105, 120,   0, 103,  95,  66, 
    111, 100, 121,  84, 114,  97, 
    110, 115, 102, 111, 114, 109, 
     97, 116, 105, 111, 110,   0, 
    103,  95, 117, 115, 101,  68, 
     81, 115,   0, 105, 110, 116, 
      0, 171,   0,   0,   2,   0, 
      1,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 175,   2, 
      0,   0, 103,  95, 117, 115, 
    101,  80, 105, 110,  80, 111, 
    115,   0,  95, 114, 101, 115, 
    101, 114, 118, 101, 100,  50, 
      0, 102, 108, 111,  97, 116, 
      0, 171, 171, 171,   0,   0, 
      3,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
    239,   2,   0,   0,  95, 114, 
    101, 115, 101, 114, 118, 101, 
    100,  51,   0, 103,  95,  98, 
    111, 110, 101,  77,  97, 116, 
    114, 105,  99, 101, 115,   0, 
    171, 171,   2,   0,   3,   0, 
      4,   0,   4,   0,   0,   2, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  85,   2, 
      0,   0, 103,  95,  98, 111, 
    110, 101,  68,  81, 115,   0, 
     68,  81,   0, 113,  48,   0, 
    102, 108, 111,  97, 116,  52, 
      0, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 108,   3, 
      0,   0, 113,  49,   0, 171, 
    105,   3,   0,   0, 116,   3, 
      0,   0,   0,   0,   0,   0, 
    152,   3,   0,   0, 116,   3, 
      0,   0,  16,   0,   0,   0, 
      5,   0,   0,   0,   1,   0, 
      8,   0,   0,   2,   2,   0, 
    156,   3,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 102,   3,   0,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171, 171, 171,  73,  83, 
     71,  78, 216,   0,   0,   0, 
      6,   0,   0,   0,   8,   0, 
      0,   0, 152,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   7,   7, 
      0,   0, 161,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   7,   0, 
      0,   0, 175,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      2,   0,   0,   0,   7,   0, 
      0,   0, 187,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0, 195,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      4,   0,   0,   0,   3,   0, 
      0,   0, 204,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      5,   0,   0,   0,   1,   1, 
      0,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0,  86, 
     69,  82,  84,  69,  88,  95, 
     78,  79,  82,  77,  65,  76, 
      0,  70,  65,  67,  69,  95, 
     78,  79,  82,  77,  65,  76, 
      0,  84,  65,  78,  71,  69, 
     78,  84,   0,  84,  69,  88, 
     67,  79,  79,  82,  68,   0, 
     86,  69,  82,  84,  69,  88, 
     95,  73,  68,   0, 171, 171, 
     79,  83,  71,  78,  80,   0, 
      0,   0,   2,   0,   0,   0, 
      8,   0,   0,   0,  56,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  68,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
      1,  14,   0,   0,  83,  86, 
     95,  80, 111, 115, 105, 116, 
    105, 111, 110,   0, 116, 101, 
    120,  99, 111, 111, 114, 100, 
      0, 171, 171, 171,  83,  72, 
     69,  88, 204,  12,   0,   0, 
     80,   0,   1,   0,  51,   3, 
      0,   0, 106,   8,   0,   1, 
     89,   8,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     13,  12,   0,   0,  88,   8, 
      0,   4,   0, 112,  16,   0, 
      0,   0,   0,   0,  85,  85, 
      0,   0,  88,   8,   0,   4, 
      0, 112,  16,   0,   1,   0, 
      0,   0,  85,  85,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3,  18,  16, 
     16,   0,   5,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 101,   0, 
      0,   3,  18,  32,  16,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,   7,   0,   0,   0, 
     27,   0,   0,   5,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,  16,  16,   0,   5,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,  45,   0,   0, 137, 
     66,   0,   0, 128,  67,  85, 
     21,   0, 242,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,  31,   0,   4,   4, 
     10, 128,  32,   0,   0,   0, 
      0,   0,  12,   0,   0,   0, 
     28,   0,   0,   5, 242,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  41,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,   2,  64, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     56,   0,   0,  10, 242,   0, 
     16,   0,   3,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,  13,   8, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,  10, 242,   0,  16,   0, 
      4,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  13,   8,   0,   0, 
     26,   0,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,  10, 
    242,   0,  16,   0,   5,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
     14,   8,   0,   0,  26,   0, 
     16,   0,   2,   0,   0,   0, 
     17,   0,   0,   7,  34,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  49,   0, 
      0,   7,  34,   0,  16,   0, 
      2,   0,   0,   0,  26,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0, 149, 191, 
    214, 179,  55,   0,   0,   9, 
     34,   0,  16,   0,   2,   0, 
      0,   0,  26,   0,  16,   0, 
      2,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128, 191, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,   9, 
    242,   0,  16,   0,   3,   0, 
      0,   0,  86,   5,  16,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  56,   0,   0,   7, 
    242,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      5,   0,   0,   0,  86,   5, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,  12, 242,   0, 
     16,   0,   4,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  14,   8,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   4,   0,   0,   0, 
     56,   0,   0,  10, 242,   0, 
     16,   0,   5,   0,   0,   0, 
    166,  10,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   6, 
      0,   0,   0,   0,  13,   8, 
      0,   0,  42,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,  10, 242,   0,  16,   0, 
      6,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  14,   8,   0,   0, 
     42,   0,  16,   0,   2,   0, 
      0,   0,  17,   0,   0,   7, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   5,   0,   0,   0, 
     49,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,   1,  64,   0,   0, 
    149, 191, 214, 179,  55,   0, 
      0,   9,  18,   0,  16,   0, 
      2,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
    128, 191,   1,  64,   0,   0, 
      0,   0, 128,  63,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      3,   0,   0,   0,   6,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   5,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,   9, 242,   0,  16,   0, 
      4,   0,   0,   0,   6,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   6,   0, 
      0,   0,  70,  14,  16,   0, 
      4,   0,   0,   0,  56,   0, 
      0,  10, 242,   0,  16,   0, 
      5,   0,   0,   0, 246,  15, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   6,   0,   0, 
      0,   0,  13,   8,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,  10, 
    242,   0,  16,   0,   2,   0, 
      0,   0, 246,  15,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   6,   0,   0,   0,   0, 
     14,   8,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
     17,   0,   0,   7,  18,   0, 
     16,   0,   6,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  70,  14,  16,   0, 
      5,   0,   0,   0,  49,   0, 
      0,   7,  18,   0,  16,   0, 
      6,   0,   0,   0,  10,   0, 
     16,   0,   6,   0,   0,   0, 
      1,  64,   0,   0, 149, 191, 
    214, 179,  55,   0,   0,   9, 
     18,   0,  16,   0,   6,   0, 
      0,   0,  10,   0,  16,   0, 
      6,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128, 191, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,   9, 
    242,   0,  16,   0,   3,   0, 
      0,   0,   6,   0,  16,   0, 
      6,   0,   0,   0,  70,  14, 
     16,   0,   5,   0,   0,   0, 
     70,  14,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,   9, 
    242,   0,  16,   0,   2,   0, 
      0,   0,   6,   0,  16,   0, 
      6,   0,   0,   0,  70,  14, 
     16,   0,   2,   0,   0,   0, 
     70,  14,  16,   0,   4,   0, 
      0,   0,  17,   0,   0,   7, 
     18,   0,  16,   0,   4,   0, 
      0,   0,  70,  14,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
      0,   0,   0,   7,  18,   0, 
     16,   0,   4,   0,   0,   0, 
     10,   0,  16,   0,   4,   0, 
      0,   0,   1,  64,   0,   0, 
    149, 191, 214,  51,  75,   0, 
      0,   5,  18,   0,  16,   0, 
      4,   0,   0,   0,  10,   0, 
     16,   0,   4,   0,   0,   0, 
     14,   0,   0,  10,  18,   0, 
     16,   0,   4,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
    128,  63,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,  10,   0,  16,   0, 
      4,   0,   0,   0,  56,   0, 
      0,   7, 242,   0,  16,   0, 
      3,   0,   0,   0,  70,  14, 
     16,   0,   3,   0,   0,   0, 
      6,   0,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,   7, 
    242,   0,  16,   0,   2,   0, 
      0,   0,  70,  14,  16,   0, 
      2,   0,   0,   0,   6,   0, 
     16,   0,   4,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  38,  25,  16,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  10, 114,   0,  16,   0, 
      4,   0,   0,   0,  38,   9, 
     16,   0,   3,   0,   0,   0, 
     70,  18,  16,   0,   0,   0, 
      0,   0,  70,   2,  16, 128, 
     65,   0,   0,   0,   4,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   4,   0, 
      0,   0, 246,  15,  16,   0, 
      3,   0,   0,   0, 150,  20, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   5,   0, 
      0,   0, 246,  15,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   5,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0, 246,  15,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      5,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      6,   0,   0,   0, 150,   4, 
     16,   0,   2,   0,   0,   0, 
     38,   9,  16,   0,   3,   0, 
      0,   0,  50,   0,   0,  10, 
    114,   0,  16,   0,   2,   0, 
      0,   0, 150,   4,  16,   0, 
      3,   0,   0,   0,  38,   9, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16, 128,  65,   0, 
      0,   0,   6,   0,   0,   0, 
      0,   0,   0,   7, 114,   0, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  70,   2,  16,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  12, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
      2,  64,   0,   0,   0,   0, 
      0,  64,   0,   0,   0,  64, 
      0,   0,   0,  64,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 114,   0,  16,   0, 
      3,   0,   0,   0,  38,   9, 
     16,   0,   3,   0,   0,   0, 
     38,   9,  16,   0,   3,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   5,   0, 
      0,   0,  70,   2,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     50,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     38,   9,  16,   0,   3,   0, 
      0,   0, 150,   4,  16,   0, 
      4,   0,   0,   0,  70,   2, 
     16, 128,  65,   0,   0,   0, 
      5,   0,   0,   0,   0,   0, 
      0,   7, 114,   0,  16,   0, 
      2,   0,   0,   0,  70,   2, 
     16,   0,   2,   0,   0,   0, 
     70,   2,  16,   0,   3,   0, 
      0,   0,  18,   0,   0,   1, 
      0,   0,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 130,   0,  16,   0, 
      2,   0,   0,   0,  42,   0, 
     16,   0,   0,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,   7, 
    130,   0,  16,   0,   2,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   2,   0,   0,   0, 
      0,   0,   0,   7, 130,   0, 
     16,   0,   2,   0,   0,   0, 
     58,   0,  16,   0,   2,   0, 
      0,   0,   1,  64,   0,   0, 
    149, 191, 214,  51,  14,   0, 
      0,  10, 130,   0,  16,   0, 
      2,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128,  63, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0, 128,  63, 
     58,   0,  16,   0,   2,   0, 
      0,   0,  28,   0,   0,   5, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  70,  14,  16,   0, 
      1,   0,   0,   0,  41,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
      2,  64,   0,   0,   2,   0, 
      0,   0,   2,   0,   0,   0, 
      2,   0,   0,   0,   2,   0, 
      0,   0,  56,   0,   0,   7, 
    242,   0,  16,   0,   0,   0, 
      0,   0,  70,  14,  16,   0, 
      0,   0,   0,   0, 246,  15, 
     16,   0,   2,   0,   0,   0, 
     56,   0,   0,  10, 114,   0, 
     16,   0,   3,   0,   0,   0, 
     86,  21,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  14,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  12, 114,   0,  16,   0, 
      3,   0,   0,   0,   6,  16, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,  13,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  50,   0, 
      0,  12, 114,   0,  16,   0, 
      3,   0,   0,   0, 166,  26, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,  15,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,   0,   0, 
      0,  10, 114,   0,  16,   0, 
      3,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,  16,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   4,   0, 
      0,   0,  86,  21,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     14,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  12, 114,   0, 
     16,   0,   4,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,  12, 114,   0, 
     16,   0,   4,   0,   0,   0, 
    166,  26,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
      0,   0,   0,  10, 114,   0, 
     16,   0,   4,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  16,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 114,   0,  16,   0, 
      4,   0,   0,   0,  86,   5, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  50,   0,   0,   9, 
    114,   0,  16,   0,   3,   0, 
      0,   0,   6,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   3,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  56,   0,   0,  10, 
    114,   0,  16,   0,   4,   0, 
      0,   0,  86,  21,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     14,   0,   0,   0,  42,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,  12, 114,   0, 
     16,   0,   4,   0,   0,   0, 
      6,  16,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  13,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
     50,   0,   0,  12, 114,   0, 
     16,   0,   4,   0,   0,   0, 
    166,  26,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   4,   0,   0,   0, 
      0,   0,   0,  10, 114,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   4,   0, 
      0,   0,  70, 130,  32,   6, 
      0,   0,   0,   0,  16,   0, 
      0,   0,  42,   0,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,   9, 114,   0,  16,   0, 
      0,   0,   0,   0, 166,  10, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      3,   0,   0,   0,  56,   0, 
      0,  10, 114,   0,  16,   0, 
      1,   0,   0,   0,  86,  21, 
     16,   0,   0,   0,   0,   0, 
     70, 130,  32,   6,   0,   0, 
      0,   0,  14,   0,   0,   0, 
     58,   0,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  12, 
    114,   0,  16,   0,   1,   0, 
      0,   0,   6,  16,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     13,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  12, 
    114,   0,  16,   0,   1,   0, 
      0,   0, 166,  26,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     15,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,   0,   0,   0,  10, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   6,   0,   0,   0,   0, 
     16,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   2,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     21,   0,   0,   1,  55,   0, 
      0,  10, 114,   0,  16,   0, 
      0,   0,   0,   0,  86, 133, 
     32,   0,   0,   0,   0,   0, 
     12,   0,   0,   0,  70,  18, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   2,   0, 
      0,   0,  56,   0,   0,   8, 
    114,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      9,   0,   0,   0,  50,   0, 
      0,  10, 178,   0,  16,   0, 
      0,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 136,  32,   0,   0,   0, 
      0,   0,   8,   0,   0,   0, 
     70,   8,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    114,   0,  16,   0,   0,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
     10,   0,   0,   0,  70,   3, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   8, 114,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      0,   0,   0,   0,  11,   0, 
      0,   0,  56,   0,   0,   8, 
    242,   0,  16,   0,   1,   0, 
      0,   0,  86,   5,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  10, 242,   0,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  50,   0,   0,  10, 
    242,   0,  16,   0,   1,   0, 
      0,   0, 166,  10,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  70,  14, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,   8, 242,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   1,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  56,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  26,   0,  16,   0, 
      0,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      5,   0,   0,   0,  50,   0, 
      0,  10,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     42, 128,  32,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     26,   0,  16,   0,   0,   0, 
      0,   0,  50,   0,   0,  10, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  42,   0,  16,   0, 
      0,   0,   0,   0,  42, 128, 
     32,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
      0,   0,   0,   8,  18,  32, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  42, 128,  32,   0, 
      0,   0,   0,   0,   7,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 148,   0, 
      0,   0,  92,   0,   0,   0, 
      7,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     48,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   4,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0
};
