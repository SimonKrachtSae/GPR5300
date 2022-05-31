Texture2D MainTexture;
sampler MainSampler;

cbuffer LightData // has to be aligned in 16 byte blocks
{
    float3 lightPosition;
    float lightIntensity;

    float4 matAmbient;
    float4 matDiffuse;
    float4 matSpecular;

    float surfaceTex;
    float surrLightIntensity;
    float padding;
};

struct PixelInput
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    //Lambertian diffuse
    float3 normal = normalize(INPUT.normal);
    float4 color = MainTexture.Sample(MainSampler, INPUT.uv);

    float3 pointToLight = normalize(lightPosition - INPUT.position);

    //Lout = L * NCLi
    //L = vector, pointing from surface to light source
    //N = surface normal
    //C = color
    //Li = LightIntensity
    float4 Lout = dot(pointToLight, normal) * color * lightIntensity;
    return Lout;

}