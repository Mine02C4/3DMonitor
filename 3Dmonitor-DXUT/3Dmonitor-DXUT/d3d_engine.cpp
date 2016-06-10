// Copyright 2011 MineStudio.
// D3DEngineクラスの定義を行います。

#include "d3d_engine.h"

#include <d3dx10.h>
#include <d3dx9math.h>

#include "DXUT.h"
#include "SDKmisc.h"

#include "file_names.h"

D3DEngine::D3DEngine() {
	// 変数初期化
	effect_					= NULL;
	vertex_layout_			= NULL;
	technique_				= NULL;
	diffuse_variable_		= NULL;
	world_variable_			= NULL;
	view_variable_			= NULL;
	projection_variable_	= NULL;
}

D3DEngine::~D3DEngine() {
	// 解放
	SAFE_RELEASE( vertex_layout_ );
    SAFE_RELEASE( effect_ );
    mesh_.Destroy();
}

HRESULT D3DEngine::OnCreateDevice(ID3D10Device* d3d_device) {
	HRESULT hr;

	// Find the D3DX effect file
    WCHAR str[MAX_PATH];
	V_RETURN(DXUTFindDXSDKMediaFileCch(str, MAX_PATH, kFileTutFX));
    DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3D10_SHADER_DEBUG;
    #endif
    V_RETURN( D3DX10CreateEffectFromFile( str, NULL, NULL, "fx_4_0", dwShaderFlags, 0, d3d_device, NULL,
                                              NULL, &effect_, NULL, NULL ) );

	// techniqueを入手
	technique_				= effect_->GetTechniqueByName( "Render" );
	diffuse_variable_		= effect_->GetVariableByName( "g_txDiffuse" )->AsShaderResource();
	world_variable_			= effect_->GetVariableByName( "World" )->AsMatrix();
	view_variable_			= effect_->GetVariableByName( "View" )->AsMatrix();
	projection_variable_	= effect_->GetVariableByName( "Projection" )->AsMatrix();

	// Define the input layout
    const D3D10_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = sizeof( layout ) / sizeof( layout[0] );

    // Create the input layout
    D3D10_PASS_DESC PassDesc;
    technique_->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    V_RETURN( d3d_device->CreateInputLayout( layout, numElements, PassDesc.pIAInputSignature,
		PassDesc.IAInputSignatureSize, &vertex_layout_ ) );

    // Set the input layout
    d3d_device->IASetInputLayout( vertex_layout_ );

	// Load the mesh
	V_RETURN(mesh_.Create(d3d_device, kFileTinyMesh, true));

    // Initialize the world matrices
    D3DXMatrixIdentity( &world_ );

    // Initialize the view matrix
    D3DXVECTOR3 Eye( 0.0f, 3.0f, -500.0f );
    D3DXVECTOR3 At( 0.0f, 1.0f, 0.0f );
    D3DXVECTOR3 Up( 0.0f, 1.0f, 0.0f );
    D3DXMatrixLookAtLH( &view_, &Eye, &At, &Up );

    // Update Variables that never change
    view_variable_->SetMatrix( ( float* )&view_ );

	return S_OK;
}

HRESULT D3DEngine::OnResizedSwapChain(const DXGI_SURFACE_DESC* buffer_surface_desc) {
	// Setup the projection parameters again
    float fAspect = static_cast<float>( buffer_surface_desc->Width ) / static_cast<float>( buffer_surface_desc->Height );
	D3DXMatrixPerspectiveFovLH( &projection_, D3DX_PI * 0.25f, fAspect, 0.5f, 1000.0f );
	projection_variable_->SetMatrix( ( float* )&projection_ );

	return S_OK;
}

void D3DEngine::OnFrameRender(ID3D10Device* d3d_device, float elapsed_time) {
	//
	// Clear the back buffer
	//
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
	ID3D10RenderTargetView* pRTV = DXUTGetD3D10RenderTargetView();
	d3d_device->ClearRenderTargetView( pRTV, ClearColor );

	//
	// Clear the depth stencil
	//
	ID3D10DepthStencilView* pDSV = DXUTGetD3D10DepthStencilView();
	d3d_device->ClearDepthStencilView( pDSV, D3D10_CLEAR_DEPTH, 1.0, 0 );

	//
	// Update variables that change once per frame
	//
	world_variable_->SetMatrix( ( float* )&world_ );

	//
	// Set the Vertex Layout
	//
	d3d_device->IASetInputLayout( vertex_layout_ );

	//
	// Render the mesh
	//
	UINT Strides[1];
	UINT Offsets[1];
	ID3D10Buffer* pVB[1];
	pVB[0] = mesh_.GetVB10( 0, 0 );
	Strides[0] = ( UINT )mesh_.GetVertexStride( 0, 0 );
	Offsets[0] = 0;
	d3d_device->IASetVertexBuffers( 0, 1, pVB, Strides, Offsets );
	d3d_device->IASetIndexBuffer( mesh_.GetIB10( 0 ), mesh_.GetIBFormat10( 0 ), 0 );

	D3D10_TECHNIQUE_DESC techDesc;
	technique_->GetDesc( &techDesc );
	SDKMESH_SUBSET* pSubset = NULL;
	ID3D10ShaderResourceView* pDiffuseRV = NULL;
	D3D10_PRIMITIVE_TOPOLOGY PrimType;

	for( UINT p = 0; p < techDesc.Passes; ++p )
	{
		for( UINT subset = 0; subset < mesh_.GetNumSubsets( 0 ); ++subset )
		{
			pSubset = mesh_.GetSubset( 0, subset );

			PrimType = mesh_.GetPrimitiveType10( ( SDKMESH_PRIMITIVE_TYPE )pSubset->PrimitiveType );
			d3d_device->IASetPrimitiveTopology( PrimType );

			pDiffuseRV = mesh_.GetMaterial( pSubset->MaterialID )->pDiffuseRV10;
			diffuse_variable_->SetResource( pDiffuseRV );

			technique_->GetPassByIndex( p )->Apply( 0 );
			d3d_device->DrawIndexed( ( UINT )pSubset->IndexCount, 0, ( UINT )pSubset->VertexStart );
		}
	}

	//the mesh class also had a render method that allows rendering the mesh with the most common options
	mesh_.Render(d3d_device, technique_, diffuse_variable_);
}

void D3DEngine::OnFrameMove(double time) {
	// Rotate cube around the origin
    D3DXMatrixRotationY( &world_, 60.0f * D3DXToRadian((float)time) );
}

void D3DEngine::CreateViews(ID3D10Device* d3d_device) {

}