struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(input.color.x, input.color.y, input.color.z, 1.0f) * 0.5;
}