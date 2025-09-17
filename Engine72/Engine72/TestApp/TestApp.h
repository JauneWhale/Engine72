#pragma once

//**************************************************************
// 这个文件下面都是各种章节的测试App
//**************************************************************

#include "../Core/GameLoopApp.h"
#include "../Core/D3D12/D3D12Renderer.h"
#include "../Core/UploadBuffer.h"
#include "../Core/FrameResource.h"
#include "../Core/Mesh/Waves.h"

//**************************************************************
// Chapter 4: 初始化一个最小Renderer
//**************************************************************
namespace InitDirect3DApp
{
    class InitDirect3DMinimalRenderer : public D3D12Renderer
    {
    public:
        InitDirect3DMinimalRenderer() = default;
        ~InitDirect3DMinimalRenderer() = default;

        virtual void Render(const GameTimer& gt, const CameraBase* camera) override;
    };

    class InitDirect3DApp : public GameLoopApp
    {
    public:
        InitDirect3DApp(HINSTANCE hInstance)
            : GameLoopApp(hInstance, new InitDirect3DMinimalRenderer()) {}
        InitDirect3DApp(const InitDirect3DApp& rhs) = delete;
        InitDirect3DApp& operator=(const InitDirect3DApp& rhs) = delete;
        ~InitDirect3DApp() = default;
    };
}

//**************************************************************
// Chapter 6: 绘制一个Box，都是临时的数据结构
//**************************************************************
using namespace DirectX;
using namespace DirectX::PackedVector;

namespace BoxApp
{
    struct Vertex
    {
        XMFLOAT3 Pos;
        XMFLOAT4 Color;
    };

    struct ObjectConstants
    {
        XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
    };

    class BoxApp : public GameLoopApp
    {
    public:
        BoxApp(HINSTANCE hInstance);
        BoxApp(const BoxApp& rhs) = delete;
        BoxApp& operator=(const BoxApp& rhs) = delete;
        ~BoxApp() = default;

    private:
        virtual void LogicUpdate(const GameTimer& gt) override;
        virtual void OnResize() override;

        DragMouseRotateInput* inputData = nullptr;
        RotatScaleCamera* mRSCamera;
    };

    class Box3DMinimalRenderer : public D3D12Renderer
    {
    public:
        virtual void Render(const GameTimer& gt, const CameraBase* camera)override;
        virtual bool InitializeRenderer(int clientWidth, int clientHeight, HWND targetWnd) override;
    private:
        // Self Functions
        void BuildDescriptorHeaps();
        void BuildConstantBuffers();
        void BuildRootSignature();
        void BuildShadersAndInputLayout();
        void BuildBoxGeometry();
        void BuildPSO();

    private:

        ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
        ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

        std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

        std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

        ComPtr<ID3DBlob> mvsByteCode = nullptr;
        ComPtr<ID3DBlob> mpsByteCode = nullptr;

        std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

        ComPtr<ID3D12PipelineState> mPSO = nullptr;
    };
}

//
//class LandAndWavesApp : public GameLoopApp
//{
//public:
//	LandAndWavesApp(HINSTANCE hInstance);
//	LandAndWavesApp(const LandAndWavesApp& rhs) = delete;
//	LandAndWavesApp& operator=(const LandAndWavesApp& rhs) = delete;
//	~LandAndWavesApp();
//
//	virtual bool Initialize()override;
//
//private:
//	virtual void OnResize()override;
//	virtual void Update(const GameTimer& gt)override;
//	virtual void Render(const GameTimer& gt)override;
//
//	void OnKeyboardInput(const GameTimer& gt);
//	void UpdateCamera(const GameTimer& gt);
//	void UpdateObjectCBs(const GameTimer& gt);
//	void UpdateMainPassCB(const GameTimer& gt);
//	void UpdateWaves(const GameTimer& gt);
//
//	void BuildRootSignature();
//	void BuildShadersAndInputLayout();
//	void BuildLandGeometry();
//	void BuildWavesGeometryBuffers();
//	void BuildPSOs();
//	void BuildFrameResources();
//	void BuildRenderItems();
//	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);
//
//	float GetHillsHeight(float x, float z)const;
//	XMFLOAT3 GetHillsNormal(float x, float z)const;
//
//private:
//
//	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
//	FrameResource* mCurrFrameResource = nullptr;
//	int mCurrFrameResourceIndex = 0;
//
//	UINT mCbvSrvDescriptorSize = 0;
//
//	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
//
//	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
//	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
//	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
//
//	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
//
//	RenderItem* mWavesRitem = nullptr;
//
//	// List of all the render items.
//	std::vector<std::unique_ptr<RenderItem>> mAllRitems;
//
//	// Render items divided by PSO.
//	std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];
//
//	std::unique_ptr<Waves> mWaves;
//
//	PassConstants mMainPassCB;
//
//	bool mIsWireframe = false;
//
//	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };
//	XMFLOAT4X4 mView = MathHelper::Identity4x4();
//	XMFLOAT4X4 mProj = MathHelper::Identity4x4();
//
//	float mSunTheta = 1.25f * XM_PI;
//	float mSunPhi = XM_PIDIV4;
//
//	POINT mLastMousePos;
//
//	DragMouseRotateCommand* mRotateData = nullptr;
//};