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
    //For further information:
    //https://en.wikipedia.org/wiki/Phong_reflection_model
    //https://en.wikipedia.org/wiki/Phong_reflection_model
    
    float3 lightDir = normalize(INPUT.position - lightPosition);
    float4 color = MainTexture.Sample(MainSampler, INPUT.uv);

    //N
    float3 normal = normalize(INPUT.normal);
    //Lm = "direction vector from the point on the surface toward (each) light source"
    float3 pointToLightPos = -lightDir;

    //R = 2(Lm * N)N - Lm
    float3 reflection = 2 * dot(pointToLightPos, normal) * INPUT.normal - pointToLightPos;

    float4 camPos = { 0,0,-6, 0 };

    //V = "direction pointing towards the viewer(such as a virtual camera)."
    float3 view = normalize(camPos - INPUT.position);


    //Iambient = Ia * Kambient
    //Ia = surrounding lights intensity
    //Kambient = ambient of material
    float4 lightAmbient = surrLightIntensity * matAmbient;

    //Idiffus = Iin * Kdiffus * (L * N)
    //Kdiffus = diffuse of material
    float4 lightDiffuse = lightIntensity * matDiffuse * max(dot(lightDir,normal),0);

    //normalizing factor
    float normFactor = (surfaceTex + 2) / (2 * 3.14159f);

    //Ispecular = Ia * Kambient * normFactor * (R * V)^n * surfaceTex
    //Kspecular = specular of material
    float4 lightSpecular = lightIntensity * matSpecular * normFactor * pow(max(dot(reflection, view),0), surfaceTex);
    
    //Iout = Iambient + Idiffuse + Ispecular;
    float4 light = lightAmbient  + lightDiffuse + lightSpecular;

    return light * color;
}